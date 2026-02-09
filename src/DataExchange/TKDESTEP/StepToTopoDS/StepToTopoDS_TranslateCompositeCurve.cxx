#include <BRep_Builder.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Surface.hpp>
#include <Precision.hpp>
#include <ShapeFix_Wire.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_CompositeCurve.hpp>
#include <StepGeom_CompositeCurveSegment.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepGeom_Surface.hpp>
#include <StepGeom_SurfaceCurve.hpp>
#include <StepToGeom.hpp>
#include <StepToTopoDS_TranslateCompositeCurve.hpp>
#include <StepToTopoDS_TranslateEdge.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Wire.hpp>
#include <Transfer_TransientProcess.hpp>

StepToTopoDS_TranslateCompositeCurve::StepToTopoDS_TranslateCompositeCurve()
    : myInfiniteSegment(false)
{
}

StepToTopoDS_TranslateCompositeCurve::StepToTopoDS_TranslateCompositeCurve(
  const occ::handle<StepGeom_CompositeCurve>&   CC,
  const occ::handle<Transfer_TransientProcess>& TP,
  const StepData_Factors&                       theLocalFactors)
{
  Init(CC, TP, theLocalFactors);
}

StepToTopoDS_TranslateCompositeCurve::StepToTopoDS_TranslateCompositeCurve(
  const occ::handle<StepGeom_CompositeCurve>&   CC,
  const occ::handle<Transfer_TransientProcess>& TP,
  const occ::handle<StepGeom_Surface>&          S,
  const occ::handle<Geom_Surface>&              Surf,
  const StepData_Factors&                       theLocalFactors)
{
  Init(CC, TP, S, Surf, theLocalFactors);
}

bool StepToTopoDS_TranslateCompositeCurve::Init(const occ::handle<StepGeom_CompositeCurve>&   CC,
                                                const occ::handle<Transfer_TransientProcess>& TP,
                                                const StepData_Factors& theLocalFactors)
{
  occ::handle<StepGeom_Surface> S;
  occ::handle<Geom_Surface>     Surf;
  return Init(CC, TP, S, Surf, theLocalFactors);
}

bool StepToTopoDS_TranslateCompositeCurve::Init(const occ::handle<StepGeom_CompositeCurve>&   CC,
                                                const occ::handle<Transfer_TransientProcess>& TP,
                                                const occ::handle<StepGeom_Surface>&          S,
                                                const occ::handle<Geom_Surface>&              Surf,
                                                const StepData_Factors& theLocalFactors)
{
  myWire.Nullify();
  myInfiniteSegment = false;
  if (CC.IsNull())
    return false;

  bool SurfMode = (!S.IsNull() && !Surf.IsNull());
  bool isClosed = false;

  occ::handle<StepData_StepModel> aStepModel = occ::down_cast<StepData_StepModel>(TP->Model());

  if (SurfMode)
  {
    int modepcurve = aStepModel->InternalParameters.ReadSurfaceCurveMode;
    if (modepcurve == -3)
      SurfMode = false;
  }

  occ::handle<ShapeExtend_WireData> sbwd = new ShapeExtend_WireData;
  int                               nbs  = CC->NbSegments();
  for (int i = 1; i <= nbs; i++)
  {
    occ::handle<StepGeom_CompositeCurveSegment> ccs = CC->SegmentsValue(i);
    if (ccs.IsNull())
    {
      TP->AddFail(CC, "Null segment");
      return false;
    }
    occ::handle<StepGeom_Curve> crv = ccs->ParentCurve();
    if (crv.IsNull())
    {
      TP->AddFail(CC, "Segment has null parent curve");
      return false;
    }
    isClosed = (ccs->Transition() != StepGeom_tcDiscontinuous);

    if (crv->IsKind(STANDARD_TYPE(StepGeom_CompositeCurve)))
    {
      if (crv == CC)
      {
        TP->AddFail(ccs, "Cyclic reference; segment dropped");
        continue;
      }
      occ::handle<StepGeom_CompositeCurve> cc = occ::down_cast<StepGeom_CompositeCurve>(crv);
      if (!Init(cc, TP, S, Surf, theLocalFactors) || myWire.IsNull())
        continue;
      int nb = sbwd->NbEdges() + 1;
      for (TopoDS_Iterator it(myWire); it.More(); it.Next())
      {
        TopoDS_Edge edge = TopoDS::Edge(it.Value());
        if (ccs->SameSense())
          sbwd->Add(edge);
        else
        {
          edge.Reverse();
          sbwd->Add(edge, nb > sbwd->NbEdges() ? 0 : nb);
        }
      }
      myWire.Nullify();
      continue;
    }

    occ::handle<StepGeom_Pcurve> pcurve = occ::down_cast<StepGeom_Pcurve>(crv);
    if (pcurve.IsNull())
    {
      occ::handle<StepGeom_SurfaceCurve> sc = occ::down_cast<StepGeom_SurfaceCurve>(crv);
      if (!sc.IsNull())
      {
        crv = sc->Curve3d();
        if (SurfMode)
        {
          for (int j = 1; j <= sc->NbAssociatedGeometry(); j++)
          {
            StepGeom_PcurveOrSurface     PCorS = sc->AssociatedGeometryValue(j);
            occ::handle<StepGeom_Pcurve> pc    = PCorS.Pcurve();
            if (pc.IsNull() || pc->BasisSurface() != S)
              continue;
            pcurve = pc;
            if (ccs->SameSense())
              break;
          }
        }
      }
    }
    else
    {
      if (!SurfMode || pcurve->BasisSurface() != S)
        pcurve.Nullify();
      crv.Nullify();
    }

    TopoDS_Edge edge;

    if (!crv.IsNull())
    {
      try
      {
        OCC_CATCH_SIGNALS
        occ::handle<Geom_Curve> c3d = StepToGeom::MakeCurve(crv, theLocalFactors);
        if (!c3d.IsNull())
        {
          BRepBuilderAPI_MakeEdge MkEdge(c3d, c3d->FirstParameter(), c3d->LastParameter());
          if (MkEdge.IsDone())
          {
            if (Precision::IsNegativeInfinite(c3d->FirstParameter())
                || Precision::IsPositiveInfinite(c3d->LastParameter()))
            {
              myInfiniteSegment = true;
              TP->AddWarning(CC, "Segment with infinite parameters");
            }
            edge = MkEdge.Edge();
          }
        }
      }
      catch (Standard_Failure const& anException)
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning: StepToTopoDS_TranslateCompositeCurve: Exception: ";
        anException.Print(std::cout);
        std::cout << std::endl;
#endif
        (void)anException;
      }
    }

    if (!pcurve.IsNull())
    {
      try
      {
        OCC_CATCH_SIGNALS
        StepToTopoDS_TranslateEdge TrE;
        occ::handle<Geom2d_Curve>  c2d = TrE.MakePCurve(pcurve, Surf, theLocalFactors);
        if (!c2d.IsNull())
        {
          if (edge.IsNull())
          {
            BRepBuilderAPI_MakeEdge MkEdge(c2d, Surf, c2d->FirstParameter(), c2d->LastParameter());
            if (MkEdge.IsDone())
            {
              if (Precision::IsNegativeInfinite(c2d->FirstParameter())
                  || Precision::IsPositiveInfinite(c2d->LastParameter()))
              {
                myInfiniteSegment = true;
                TP->AddWarning(CC, "Segment with infinite parameters");
              }
              edge = MkEdge.Edge();
            }
          }
          else
          {
            BRep_Builder    B;
            TopLoc_Location L;
            B.UpdateEdge(edge, c2d, Surf, L, 0.);
            B.Range(edge, Surf, L, c2d->FirstParameter(), c2d->LastParameter());
            B.SameRange(edge, false);
            B.SameParameter(edge, false);
          }
        }
      }
      catch (Standard_Failure const& anException)
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning: StepToTopoDS_TranslateCompositeCurve: Exception: ";
        anException.Print(std::cout);
        std::cout << std::endl;
#endif
        (void)anException;
      }
    }

    if (edge.IsNull())
    {
      TP->AddFail(crv, "Curve can not be translated");
      continue;
    }

    if (!ccs->SameSense())
      edge.Reverse();
    sbwd->Add(edge);
  }
  if (sbwd->NbEdges() <= 0)
  {
    TP->AddFail(CC, "Translation gives no result");
    return false;
  }

  double                     preci = Precision();
  occ::handle<ShapeFix_Wire> sfw   = new ShapeFix_Wire;
  sfw->Load(sbwd);
  sfw->SetPrecision(preci);
  sfw->ClosedWireMode() = isClosed;
  sfw->FixReorder();
  if (sfw->StatusReorder(ShapeExtend_DONE))
  {
    TP->AddWarning(CC, "Segments were disordered; fixed");
  }
  sfw->FixConnected(preci);
  if (sfw->StatusConnected(ShapeExtend_FAIL))
  {
    TP->AddWarning(CC, "Segments are not connected");
  }

  myWire = sbwd->Wire();
  done   = (sbwd->NbEdges() > 0);
  return true;
}

const TopoDS_Wire& StepToTopoDS_TranslateCompositeCurve::Value() const
{
  return myWire;
}
