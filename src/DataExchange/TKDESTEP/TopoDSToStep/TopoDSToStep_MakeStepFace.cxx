#include <Bnd_Box2d.hpp>
#include <BRep_Tool.hpp>
#include <BRepTools.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dConvert.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_ElementarySurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <GeomToStep_MakeCurve.hpp>
#include <GeomToStep_MakeSurface.hpp>
#include <Precision.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_GeometricRepresentationContextAndParametricRepresentationContext.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepGeom_SeamCurve.hpp>
#include <StepGeom_SurfaceCurve.hpp>
#include <StepGeom_ToroidalSurface.hpp>
#include <Geom_OffsetSurface.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_AdvancedFace.hpp>
#include <StepShape_EdgeCurve.hpp>
#include <StepShape_FaceBound.hpp>
#include <StepShape_Loop.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDSToStep.hpp>
#include <TopoDSToStep_MakeStepFace.hpp>
#include <TopoDSToStep_MakeStepWire.hpp>
#include <TopoDSToStep_Tool.hpp>
#include <Transfer_FinderProcess.hpp>
#include <TransferBRep.hpp>
#include <TransferBRep_ShapeMapper.hpp>
#include <GeomConvert_Units.hpp>

TopoDSToStep_MakeStepFace::TopoDSToStep_MakeStepFace()
    : myError(TopoDSToStep_FaceOther)
{
  done = false;
}

TopoDSToStep_MakeStepFace::TopoDSToStep_MakeStepFace(const TopoDS_Face&                         F,
                                                     TopoDSToStep_Tool&                         T,
                                                     const occ::handle<Transfer_FinderProcess>& FP,
                                                     const StepData_Factors& theLocalFactors)
{
  done = false;
  Init(F, T, FP, theLocalFactors);
}

void TopoDSToStep_MakeStepFace::Init(const TopoDS_Face&                         aFace,
                                     TopoDSToStep_Tool&                         aTool,
                                     const occ::handle<Transfer_FinderProcess>& FP,
                                     const StepData_Factors&                    theLocalFactors)
{

  TopoDS_Shape      sh          = aFace.Oriented(TopAbs_FORWARD);
  const TopoDS_Face ForwardFace = TopoDS::Face(sh);
  aTool.SetCurrentFace(ForwardFace);
  occ::handle<TransferBRep_ShapeMapper> errShape = new TransferBRep_ShapeMapper(aFace);

  if (occ::down_cast<StepData_StepModel>(FP->Model())->InternalParameters.WriteNonmanifold != 0)
  {
    occ::handle<StepShape_AdvancedFace>   anAF;
    occ::handle<TransferBRep_ShapeMapper> aSTEPMapper = TransferBRep::ShapeMapper(FP, aFace);
    if (FP->FindTypedTransient(aSTEPMapper, STANDARD_TYPE(StepShape_AdvancedFace), anAF))
    {

      occ::handle<StepShape_AdvancedFace> aLinkingAF = new StepShape_AdvancedFace;
      aLinkingAF->Init(anAF->Name(), anAF->Bounds(), anAF->FaceGeometry(), !anAF->SameSense());

      myError  = TopoDSToStep_FaceDone;
      myResult = aLinkingAF;
      done     = true;
      return;
    }
  }

  if (aTool.IsBound(aFace))
  {
    myError  = TopoDSToStep_FaceDone;
    done     = true;
    myResult = aTool.Find(aFace);
    return;
  }

  if (aFace.Orientation() == TopAbs_INTERNAL || aFace.Orientation() == TopAbs_EXTERNAL)
  {
    FP->AddWarning(errShape, " Face from Non Manifold Topology");
    myError = TopoDSToStep_NonManifoldFace;
    done    = false;
    return;
  }

  const TopoDS_Wire theOuterWire = BRepTools::OuterWire(ForwardFace);
  if (theOuterWire.IsNull())
  {
    FP->AddWarning(errShape, " Face without wire not mapped");
    myError = TopoDSToStep_InfiniteFace;
    done    = false;
    return;
  }

  try
  {

    occ::handle<Geom_Surface> Su = BRep_Tool::Surface(ForwardFace);
    if (Su.IsNull())
    {
      FP->AddWarning(errShape, " Face without geometry not mapped");
      myError = TopoDSToStep_FaceOther;
      done    = false;
      return;
    }

    occ::handle<Geom_RectangularTrimmedSurface> aRTS =
      occ::down_cast<Geom_RectangularTrimmedSurface>(Su);
    if (!aRTS.IsNull())
      Su = aRTS->BasisSurface();

    aTool.SetSurfaceReversed(false);

    GeomToStep_MakeSurface        MkSurface(Su, theLocalFactors);
    occ::handle<StepGeom_Surface> Spms = MkSurface.Value();

    {

      bool                            aSurfaceIsOffset = false;
      occ::handle<Geom_OffsetSurface> anOffsetSu;
      if (Su->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
      {
        aSurfaceIsOffset = true;
        anOffsetSu       = occ::down_cast<Geom_OffsetSurface>(Su);
      }
      if ((Spms->IsKind(STANDARD_TYPE(StepGeom_ToroidalSurface)))
          || ((aSurfaceIsOffset)
              && anOffsetSu->BasisSurface()->IsKind(STANDARD_TYPE(Geom_ToroidalSurface))))
      {
        occ::handle<Geom_ToroidalSurface> TS;
        if (aSurfaceIsOffset)
          TS = occ::down_cast<Geom_ToroidalSurface>(anOffsetSu->BasisSurface());
        else
          TS = occ::down_cast<Geom_ToroidalSurface>(Su);
        double R = TS->MajorRadius();
        double r = TS->MinorRadius();
        if (R < r)
        {
          gp_Ax3 Ax3 = TS->Position();
          gp_Pnt pos = Ax3.Location();
          gp_Dir dir = Ax3.Direction();
          gp_Dir X   = Ax3.XDirection();

          double UF, VF, UL, VL;
          ShapeAlgo::AlgoContainer()->GetFaceUVBounds(aFace, UF, UL, VF, VL);
          gp_Ax2                  Ax2(pos.XYZ() + X.XYZ() * TS->MajorRadius(), X ^ dir, X);
          occ::handle<Geom_Curve> BasisCurve = new Geom_Circle(Ax2, TS->MinorRadius());

          if (VL - VF - 2 * M_PI < -Precision::PConfusion())
            BasisCurve =
              ShapeAlgo::AlgoContainer()->ConvertCurveToBSpline(BasisCurve,
                                                                VF,
                                                                VL,
                                                                Precision::Approximation(),
                                                                GeomAbs_C1,
                                                                100,
                                                                9);

          gp_Ax1 Axis = Ax3.Axis();
          if (!Ax3.Direct())
            Axis.Reverse();
          occ::handle<Geom_SurfaceOfRevolution> Rev =
            new Geom_SurfaceOfRevolution(BasisCurve, Axis);

          if (aSurfaceIsOffset)
          {
            anOffsetSu->SetBasisSurface(Rev);
            GeomToStep_MakeSurface MkRev(anOffsetSu, theLocalFactors);
            Spms = MkRev.Value();
          }
          else
          {
            GeomToStep_MakeSurface MkRev(Rev, theLocalFactors);
            Spms = MkRev.Value();
          }
        }
      }
    }

    occ::handle<StepShape_Loop> Loop;

    TopoDSToStep_MakeStepWire                             MkWire;
    NCollection_Sequence<occ::handle<Standard_Transient>> mySeq;

    TopExp_Explorer WireExp;
    for (WireExp.Init(ForwardFace, TopAbs_WIRE); WireExp.More(); WireExp.Next())
    {

      const TopoDS_Wire CurrentWire = TopoDS::Wire(WireExp.Current());
      if (!CurrentWire.IsNull())
      {
        MkWire.Init(CurrentWire, aTool, FP, theLocalFactors);
        if (MkWire.IsDone())
          Loop = occ::down_cast<StepShape_Loop>(MkWire.Value());
        else
        {
          FP->AddWarning(errShape, " a Wire not mapped");
          continue;
        }
      }

      occ::handle<StepShape_FaceBound> FaceBound = new StepShape_FaceBound();

      occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString("");

      if (!aTool.Faceted() && aFace.Orientation() == TopAbs_REVERSED)
        FaceBound->Init(aName, Loop, (CurrentWire.Orientation() == TopAbs_REVERSED));
      else
        FaceBound->Init(aName, Loop, (CurrentWire.Orientation() == TopAbs_FORWARD));

      mySeq.Append(FaceBound);
    }

    if (!aTool.Faceted() && aTool.PCurveMode() != 0)
    {

      TopExp_Explorer Ex(ForwardFace, TopAbs_EDGE);

      for (; Ex.More(); Ex.Next())
      {
        TopoDS_Edge               E = TopoDS::Edge(Ex.Current());
        double                    cf, cl;
        occ::handle<Geom2d_Curve> C2d = BRep_Tool::CurveOnSurface(E, ForwardFace, cf, cl);
        if (BRep_Tool::Degenerated(E) || C2d.IsNull())
        {

          continue;
        }

        C2d = occ::down_cast<Geom2d_Curve>(C2d->Copy());

        if (!aTool.IsBound(E))
          continue;
        occ::handle<StepGeom_Curve> Cpms =
          occ::down_cast<StepShape_EdgeCurve>(aTool.Find(E))->EdgeGeometry();
        if (Cpms.IsNull())
          continue;

        if (aTool.IsBound(E))
        {
          if (C2d->IsKind(STANDARD_TYPE(Geom2d_Hyperbola))
              || C2d->IsKind(STANDARD_TYPE(Geom2d_Parabola)))
          {
            if (Su->IsKind(STANDARD_TYPE(Geom_SphericalSurface))
                || Su->IsKind(STANDARD_TYPE(Geom_CylindricalSurface))
                || Su->IsKind(STANDARD_TYPE(Geom_ConicalSurface))
                || Su->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))
            {
              C2d = new Geom2d_TrimmedCurve(C2d, cf, cl, true);
            }
          }

          if ((C2d->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve)))
              || (C2d->IsKind(STANDARD_TYPE(Geom2d_BezierCurve))))
          {
            C2d = Geom2dConvert::CurveToBSplineCurve(C2d);
          }

          occ::handle<Geom2d_Curve> C2dMapped;
          if (Su->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
          {
            occ::handle<Geom_RectangularTrimmedSurface> alocalRTS =
              occ::down_cast<Geom_RectangularTrimmedSurface>(Su);
            C2dMapped = GeomConvert_Units::RadianToDegree(C2d,
                                                          alocalRTS->BasisSurface(),
                                                          theLocalFactors.LengthFactor(),
                                                          theLocalFactors.FactorRadianDegree());
          }
          else
          {
            C2dMapped = GeomConvert_Units::RadianToDegree(C2d,
                                                          Su,
                                                          theLocalFactors.LengthFactor(),
                                                          theLocalFactors.FactorRadianDegree());
          }

          GeomToStep_MakeCurve MkCurve(C2dMapped, theLocalFactors);

          occ::handle<StepGeom_Pcurve>                     Pc = new StepGeom_Pcurve;
          occ::handle<StepRepr_DefinitionalRepresentation> DRI =
            new StepRepr_DefinitionalRepresentation;
          occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems =
            new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
          aItems->SetValue(1, MkCurve.Value());
          occ::handle<StepGeom_GeometricRepresentationContextAndParametricRepresentationContext>
            aContext =
              new StepGeom_GeometricRepresentationContextAndParametricRepresentationContext();
          occ::handle<TCollection_HAsciiString> aContextIdentifier =
            new TCollection_HAsciiString("2D SPACE");
          occ::handle<TCollection_HAsciiString> aContextType   = new TCollection_HAsciiString("");
          int                                   aCoordSpaceDim = 2;
          aContext->Init(aContextIdentifier, aContextType, aCoordSpaceDim);

          occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString("");

          DRI->Init(aName, aItems, aContext);
          Pc->Init(aName, Spms, DRI);
          occ::handle<StepGeom_SurfaceCurve> C1pms = occ::down_cast<StepGeom_SurfaceCurve>(Cpms);
          occ::handle<NCollection_HArray1<StepGeom_PcurveOrSurface>> aGeom =
            C1pms->AssociatedGeometry();
          if (aGeom.IsNull())
            aGeom = new NCollection_HArray1<StepGeom_PcurveOrSurface>(1, 2);
          StepGeom_PcurveOrSurface PcOrSur;
          PcOrSur.SetValue(Pc);
          if ((aGeom->Value(1)).IsNull())
          {
            aGeom->SetValue(1, PcOrSur);
            if (C1pms->IsKind(STANDARD_TYPE(StepGeom_SeamCurve)))
            {
              aGeom->SetValue(2, PcOrSur);
            }
          }
          else if (aGeom->Value(2).IsNull() || C1pms->IsKind(STANDARD_TYPE(StepGeom_SeamCurve)))
          {
            aGeom->SetValue(2, PcOrSur);
          }
          C1pms->SetAssociatedGeometry(aGeom);
        }
      }
    }

    int nbWires = mySeq.Length();
    if (nbWires)
    {
      occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>> aBounds =
        new NCollection_HArray1<occ::handle<StepShape_FaceBound>>(1, nbWires);
      for (int i = 1; i <= nbWires; i++)
      {
        aBounds->SetValue(i, occ::down_cast<StepShape_FaceBound>(mySeq.Value(i)));
      }
      occ::handle<StepShape_AdvancedFace> Fpms = new StepShape_AdvancedFace;

      occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString("");

      Fpms->Init(aName, aBounds, Spms, aFace.Orientation() == TopAbs_FORWARD);

      aTool.Bind(aFace, Fpms);
      myError  = TopoDSToStep_FaceDone;
      myResult = Fpms;
      done     = true;
    }
    else
    {

      FP->AddWarning(errShape, " No Wires of this Face were mapped");
      myError = TopoDSToStep_NoWireMapped;
      done    = false;
    }
  }
  catch (Standard_Failure const& theFailure)
  {
    FP->AddFail(errShape, theFailure.what());
    myError = TopoDSToStep_FaceOther;
    done    = false;
  }
}

const occ::handle<StepShape_TopologicalRepresentationItem>& TopoDSToStep_MakeStepFace::Value() const
{
  StdFail_NotDone_Raise_if(!done, "TopoDSToStep_MakeStepFace::Value() - no result");
  return myResult;
}

TopoDSToStep_MakeFaceError TopoDSToStep_MakeStepFace::Error() const
{
  return myError;
}
