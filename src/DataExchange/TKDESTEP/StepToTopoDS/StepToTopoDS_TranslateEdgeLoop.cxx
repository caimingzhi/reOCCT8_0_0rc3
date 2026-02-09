#include <BRep_Builder.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <ElCLib.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <ShapeAlgo_ToolContainer.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <Standard_ErrorHandler.hpp>
#include <ShapeBuild_Edge.hpp>
#include <ShapeExtend_WireData.hpp>
#include <ShapeFix_EdgeProjAux.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepGeom_Surface.hpp>
#include <StepGeom_SurfaceCurve.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>
#include <StepShape_EdgeCurve.hpp>
#include <StepShape_EdgeLoop.hpp>
#include <StepShape_FaceBound.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <StepShape_Vertex.hpp>
#include <StepToGeom.hpp>
#include <StepToTopoDS.hpp>
#include <StepToTopoDS_GeometricTool.hpp>
#include <StepToTopoDS_NMTool.hpp>
#include <StepToTopoDS_Tool.hpp>
#include <StepToTopoDS_TranslateEdge.hpp>
#include <StepToTopoDS_TranslateEdgeLoop.hpp>
#include <StepToTopoDS_TranslateVertex.hpp>
#include <TopAbs.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <Transfer_TransientProcess.hpp>
#include <XSAlgo.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

static void RemoveSinglePCurve(const TopoDS_Edge& aEdge, const TopoDS_Face& aFace)
{
  ShapeBuild_Edge().RemovePCurve(aEdge, aFace);
}

static void RemovePCurves(const TopoDS_Wire& aWire, const TopoDS_Face& aFace)
{
  TopExp_Explorer EdgeExp(aWire, TopAbs_EDGE);
  while (EdgeExp.More())
  {
    const TopoDS_Edge& myEdge = TopoDS::Edge(EdgeExp.Current());
    RemoveSinglePCurve(myEdge, aFace);
    EdgeExp.Next();
  }
}

static void CheckPCurves(TopoDS_Wire&       aWire,
                         const TopoDS_Face& aFace,
                         const bool         isPlane,
                         const double       preci)
{
  if (isPlane)
  {
    RemovePCurves(aWire, aFace);
    return;
  }
  BRep_Builder              B;
  double                    w1, w2, cf, cl;
  occ::handle<Geom_Surface> mySurf = BRep_Tool::Surface(aFace);

  occ::handle<ShapeExtend_WireData> sbwd = new ShapeExtend_WireData(aWire);
  for (int i = 1; i <= sbwd->NbEdges(); i++)
  {
    const TopoDS_Edge& myEdge = sbwd->Edge(i);

    occ::handle<Geom2d_Curve> thePC;
    ShapeAnalysis_Edge        sae;
    if (!sae.PCurve(myEdge, aFace, thePC, w1, w2, false))
    {
      continue;
    }
    cf = thePC->FirstParameter();
    cl = thePC->LastParameter();

    if (w1 == w2)
    {
      RemoveSinglePCurve(myEdge, aFace);
#ifdef OCCT_DEBUG
      std::cout << "Removing pcuve w1=w2" << std::endl;
#endif
      continue;
    }

    if (!thePC->IsPeriodic())
    {
      if (w1 < cf)
      {
        B.Range(myEdge, aFace, cf, w2);
        w1 = cf;
      }
      if (w2 > cl)
      {
        B.Range(myEdge, aFace, w1, cl);
        w2 = cl;
      }
    }

    if (w1 > w2 && mySurf->IsUPeriodic())
    {
      double u1, u2, v1, v2;
      mySurf->Bounds(u1, u2, v1, v2);
      ElCLib::AdjustPeriodic(u1,
                             u2,
                             std::min(std::abs(w2 - w1) / 2, Precision::PConfusion()),
                             w1,
                             w2);
      B.Range(myEdge, aFace, w1, w2);
    }

    XSAlgo_ShapeProcessor::CheckPCurve(myEdge, aFace, preci, sbwd->IsSeam(i));
  }
}

StepToTopoDS_TranslateEdgeLoop::StepToTopoDS_TranslateEdgeLoop()
    : myError(StepToTopoDS_TranslateEdgeLoopOther)
{
  done = false;
}

StepToTopoDS_TranslateEdgeLoop::StepToTopoDS_TranslateEdgeLoop(
  const occ::handle<StepShape_FaceBound>& FB,
  const TopoDS_Face&                      Face,
  const occ::handle<Geom_Surface>&        GeomSurf,
  const occ::handle<StepGeom_Surface>&    StepSurf,
  const bool                              sameSense,
  StepToTopoDS_Tool&                      T,
  StepToTopoDS_NMTool&                    NMTool,
  const StepData_Factors&                 theLocalFactors)
{
  Init(FB, Face, GeomSurf, StepSurf, sameSense, T, NMTool, theLocalFactors);
}

void StepToTopoDS_TranslateEdgeLoop::Init(const occ::handle<StepShape_FaceBound>& FaceBound,
                                          const TopoDS_Face&                      Face,
                                          const occ::handle<Geom_Surface>&        GeomSurf,
                                          const occ::handle<StepGeom_Surface>&    StepSurf,
                                          const bool                              sameSense,
                                          StepToTopoDS_Tool&                      aTool,
                                          StepToTopoDS_NMTool&                    NMTool,
                                          const StepData_Factors&                 theLocalFactors)
{
  done                               = true;
  occ::handle<StepShape_EdgeLoop> EL = occ::down_cast<StepShape_EdgeLoop>(FaceBound->Bound());

  if (aTool.IsBound(EL))
  {
    myResult = TopoDS::Wire(aTool.Find(EL));
    myError  = StepToTopoDS_TranslateEdgeLoopDone;
    done     = true;
    return;
  }

  BRep_Builder                           B;
  occ::handle<Transfer_TransientProcess> TP  = aTool.TransientProcess();
  occ::handle<StepData_StepModel> aStepModel = occ::down_cast<StepData_StepModel>(TP->Model());
  int                             modepcurve = aStepModel->InternalParameters.ReadSurfaceCurveMode;

  double        preci = Precision();
  TopoDS_Wire   W;
  TopoDS_Edge   E;
  TopoDS_Vertex V;

  bool isSeam, isLikeSeam;

  occ::handle<StepShape_OrientedEdge>              OrEdge1, OrEdge2;
  occ::handle<StepGeom_Curve>                      StepCurve, StepCurve1, StepCurve2;
  occ::handle<StepRepr_DefinitionalRepresentation> DRI, Dri1, Dri2;

  occ::handle<Geom2d_Curve> C2d, C2d1, C2d2, WhichC2d1, WhichC2d2;
  TopoDS_Edge               suspectE;

  int j, NbEdge = EL->NbEdgeList();
  if (NbEdge == 0)
  {
    TP->AddWarning(EL, "Wire not done. EdgeLoop does not contain edges.");
    done = false;
    return;
  }

  bool                      hasPcurve = true;
  bool                      isPlane   = GeomSurf->IsKind(STANDARD_TYPE(Geom_Plane));
  occ::handle<Geom_Surface> ConvSurf  = GeomSurf;
  if (GeomSurf->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
  {
    occ::handle<Geom_RectangularTrimmedSurface> theRTS =
      occ::down_cast<Geom_RectangularTrimmedSurface>(GeomSurf);
    ConvSurf = theRTS->BasisSurface();
  }

  aTool.ComputePCurve(false);

  bool ForwardWire = FaceBound->Orientation();

  B.MakeWire(W);

  for (j = 1; j <= NbEdge; j++)
  {
    OrEdge1 = EL->EdgeListValue(j);

    if (OrEdge1.IsNull() || OrEdge1->EdgeElement().IsNull())
    {
      TP->AddWarning(
        OrEdge1,
        "Incorrect Oriented_Edge is not translated. Oriented_Edge definition is not correct");
      continue;
    }

    if (OrEdge1->EdgeElement()->IsKind(STANDARD_TYPE(StepShape_OrientedEdge)))
      OrEdge1 = occ::down_cast<StepShape_OrientedEdge>(OrEdge1->EdgeElement());

    occ::handle<StepShape_EdgeCurve> EC =
      occ::down_cast<StepShape_EdgeCurve>(OrEdge1->EdgeElement());
    if (EC.IsNull())
    {
      TP->AddWarning(OrEdge1, "Edge does not contain EDGE_CURVE, skipped");
      continue;
    }

    occ::handle<StepGeom_Curve> C = EC->EdgeGeometry();
    if (!C.IsNull())
    {
      if (C->IsKind(STANDARD_TYPE(StepGeom_SurfaceCurve)))
      {
        occ::handle<StepGeom_SurfaceCurve> Sc = occ::down_cast<StepGeom_SurfaceCurve>(C);
        C                                     = Sc->Curve3d();
      }
    }
    occ::handle<Geom_Curve> C1;
    if (!C.IsNull())
    {
      try
      {
        OCC_CATCH_SIGNALS
        C1 = occ::down_cast<Geom_Curve>(TP->FindTransient(C));
        if (C1.IsNull())
        {
          C1 = StepToGeom::MakeCurve(C, theLocalFactors);
          if (!C1.IsNull())
            TP->BindTransient(C, C1);
          else
            TP->AddWarning(C, "Could not convert a curve. Curve definition is incorrect");
        }
      }
      catch (Standard_Failure const& anException)
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning: StepToTopoDS_TranslateEdgeLoop: Exception: ";
        anException.Print(std::cout);
        std::cout << std::endl;
#endif
        (void)anException;
        TP->AddFail(C, "Exception was raised. Curve geometry definition is incorrect");
      }
    }

    occ::handle<StepShape_Vertex> Vstart, Vend;
    if (EC->SameSense())
    {
      Vstart = EC->EdgeStart();
      Vend   = EC->EdgeEnd();
    }
    else
    {
      Vend   = EC->EdgeStart();
      Vstart = EC->EdgeEnd();
    }

    bool                         istV = aTool.IsBound(Vstart);
    bool                         iseV = aTool.IsBound(Vend);
    TopoDS_Vertex                V1, V2;
    StepToTopoDS_TranslateVertex myTranVertex1(Vstart, aTool, NMTool, theLocalFactors);
    StepToTopoDS_TranslateVertex myTranVertex2(Vend, aTool, NMTool, theLocalFactors);

    if (myTranVertex1.IsDone())
    {
      V1 = TopoDS::Vertex(myTranVertex1.Value());
    }
    if (myTranVertex2.IsDone())
    {
      V2        = TopoDS::Vertex(myTranVertex2.Value());
      gp_Pnt p1 = BRep_Tool::Pnt(V1);
      gp_Pnt p2 = BRep_Tool::Pnt(V2);
      if (p1.Distance(p2) <= Precision::Confusion())
      {
        bool Fixed = true;
        if (!iseV)
          aTool.Bind(Vend, V1);
        else if (!istV)
          aTool.Bind(Vstart, V2);
        else
          aTool.Bind(Vend, V1);
        if (!C1.IsNull() && !C1->IsClosed() && Fixed)
          TP->AddWarning(EL->EdgeListValue(j), "Vertex of same coordinates, set confused");
      }
    }
  }

  for (j = 1; j <= NbEdge; j++)
  {
    OrEdge1 = EL->EdgeListValue(j);
    OrEdge2 = EL->EdgeListValue(j < NbEdge ? j + 1 : 1);
    if (OrEdge1.IsNull() || OrEdge2.IsNull())
      continue;

    occ::handle<StepShape_EdgeCurve> EC1 =
      occ::down_cast<StepShape_EdgeCurve>(OrEdge1->EdgeElement());
    occ::handle<StepShape_EdgeCurve> EC2 =
      occ::down_cast<StepShape_EdgeCurve>(OrEdge2->EdgeElement());
    if (EC1.IsNull() || EC2.IsNull())
    {
      continue;
    }

    occ::handle<StepShape_Vertex> Vs1, Vs2, Vs11, Vs22;
    Vs1 = (OrEdge1->Orientation() ? EC1->EdgeEnd() : EC1->EdgeStart());
    Vs2 = (OrEdge2->Orientation() ? EC2->EdgeStart() : EC2->EdgeEnd());

    Vs11 = (OrEdge1->Orientation() ? EC1->EdgeStart() : EC1->EdgeEnd());
    Vs22 = (OrEdge2->Orientation() ? EC2->EdgeEnd() : EC2->EdgeStart());

    if ((Vs1 == Vs2) || (Vs1 == Vs22) || (Vs2 == Vs11) || (Vs22 == Vs11))
      continue;

    StepToTopoDS_TranslateVertex myTranVertex1(Vs1, aTool, NMTool, theLocalFactors);
    StepToTopoDS_TranslateVertex myTranVertex2(Vs2, aTool, NMTool, theLocalFactors);

    TopoDS_Vertex V1, V2;
    if (myTranVertex1.IsDone())
      V1 = TopoDS::Vertex(myTranVertex1.Value());
    if (myTranVertex2.IsDone())
      V2 = TopoDS::Vertex(myTranVertex2.Value());
    if (V1.IsNull() || V2.IsNull())
      continue;
    if (V1.IsSame(V2))
      continue;

    gp_Pnt p1       = BRep_Tool::Pnt(V1);
    gp_Pnt p2       = BRep_Tool::Pnt(V2);
    bool   locFixed = true;
    if (p1.Distance(p2) <= preci)
    {
      if (!aTool.IsBound(EC1))
        aTool.Bind(Vs1, V2);
      else if (!aTool.IsBound(EC2))
        aTool.Bind(Vs2, V1);
      else
        locFixed = false;
    }
    else
      locFixed = false;
    if (locFixed)
      TP->AddWarning(EL, "Adjacent edges do not have common vertex; set confused");
    else
      TP->AddWarning(EL, "Adjacent edges are not connected");
  }

  for (j = 1; j <= NbEdge; j++)
  {

    bool ThereIsLikeSeam = false;

#ifdef OCCT_DEBUG
    std::cout << "      Processing Edge :" << j << std::endl;
#endif

    OrEdge1 = EL->EdgeListValue(j);
    if (OrEdge1.IsNull() || OrEdge1->EdgeElement().IsNull())
      continue;

    if (OrEdge1->EdgeElement()->IsKind(STANDARD_TYPE(StepShape_OrientedEdge)))
      OrEdge1 = occ::down_cast<StepShape_OrientedEdge>(OrEdge1->EdgeElement());

    occ::handle<StepShape_EdgeCurve> EC =
      occ::down_cast<StepShape_EdgeCurve>(OrEdge1->EdgeElement());
    if (EC.IsNull())
    {
      continue;
    }

    StepToTopoDS_TranslateEdge myTranEdge;

    myTranEdge.SetPrecision(preci);
    myTranEdge.SetMaxTol(MaxTol());
    myTranEdge.Init(OrEdge1, aTool, NMTool, theLocalFactors);

    if (myTranEdge.IsDone())
    {

      E = TopoDS::Edge(myTranEdge.Value());
      if (E.IsNull())
        continue;

      occ::handle<StepGeom_Curve> C = EC->EdgeGeometry();

      if (OrEdge1->Orientation() && EC->SameSense())
        E.Orientation(TopAbs_FORWARD);
      else if (!OrEdge1->Orientation() && !EC->SameSense())
        E.Orientation(TopAbs_FORWARD);
      else
        E.Orientation(TopAbs_REVERSED);

      isSeam = isLikeSeam = false;

      if (C.IsNull())
      {
        aTool.ComputePCurve(true);
        hasPcurve = false;
      }
      else if (C->IsKind(STANDARD_TYPE(StepGeom_Pcurve)))
      {
        occ::handle<StepGeom_Pcurve> StepPCurve = occ::down_cast<StepGeom_Pcurve>(C);
        C2d = myTranEdge.MakePCurve(StepPCurve, ConvSurf, theLocalFactors);

        aTool.AddContinuity(C2d);
      }

      else if (modepcurve == 3)
      {
        aTool.ComputePCurve(true);
        hasPcurve = false;
      }
      else if (C->IsKind(STANDARD_TYPE(StepGeom_SurfaceCurve)))
      {

        occ::handle<StepGeom_SurfaceCurve> SurfCurve = occ::down_cast<StepGeom_SurfaceCurve>(C);

        occ::handle<StepGeom_Pcurve> StepPCurve, StepPCurve1, StepPCurve2;
        int lastpcurve = StepToTopoDS_GeometricTool::PCurve(SurfCurve, StepSurf, StepPCurve, 0);
        hasPcurve      = !StepPCurve.IsNull();

        if (isPlane)
          hasPcurve = false;

        isLikeSeam = StepToTopoDS_GeometricTool::IsLikeSeam(SurfCurve, StepSurf, EC, EL);

        isSeam = StepToTopoDS_GeometricTool::IsSeamCurve(SurfCurve, StepSurf, EC, EL);

        if (isSeam || isLikeSeam)
        {

          StepPCurve1 = SurfCurve->AssociatedGeometryValue(1).Pcurve();
          StepPCurve2 = SurfCurve->AssociatedGeometryValue(2).Pcurve();

          if (StepPCurve1.IsNull() || StepPCurve2.IsNull())
            hasPcurve = false;

          else
          {
            C2d1      = myTranEdge.MakePCurve(StepPCurve1, ConvSurf, theLocalFactors);
            C2d2      = myTranEdge.MakePCurve(StepPCurve2, ConvSurf, theLocalFactors);
            hasPcurve = (!C2d1.IsNull() && !C2d2.IsNull());
          }

          if (isLikeSeam)
          {
            suspectE        = E;
            ThereIsLikeSeam = true;
            hasPcurve       = true;
          }
        }
        else if (hasPcurve)
        {

          while (lastpcurve > 0)
          {
            C2d1 = myTranEdge.MakePCurve(StepPCurve, ConvSurf, theLocalFactors);
            if (C2d1.IsNull())
            {
              TP->AddWarning(
                EC,
                "Incorrect pcurve is not translated. Pcurve definition is not correct");
              hasPcurve = false;
              break;
            }
            else
              C2d = C2d1;
            lastpcurve =
              StepToTopoDS_GeometricTool::PCurve(SurfCurve, StepSurf, StepPCurve, lastpcurve);

            aTool.AddContinuity(C2d);
          }
        }
        if (!hasPcurve)
        {

          aTool.ComputePCurve(true);
        }
      }

      else
      {
        aTool.ComputePCurve(true);
        hasPcurve = false;
      }

      if (hasPcurve && (isSeam || ThereIsLikeSeam))
      {

        if ((!C2d1.IsNull()) && (!C2d2.IsNull()))
        {
          TopAbs_Orientation CumulO, EdgeO, WireO, FaceO;
          EdgeO = E.Orientation();
          if (ForwardWire)
            WireO = TopAbs_FORWARD;
          else
            WireO = TopAbs_REVERSED;
          if (sameSense)
            FaceO = TopAbs_FORWARD;
          else
            FaceO = TopAbs_REVERSED;

          CumulO = TopAbs::Compose(EdgeO, WireO);
          CumulO = TopAbs::Compose(CumulO, FaceO);

          bool ForwardEdge = (CumulO == TopAbs_FORWARD);

          int forwardPC = ShapeAnalysis_Curve().SelectForwardSeam(C2d1, C2d2);
          if (forwardPC == 0)
          {
            TP->AddFail(EC, " Seam curve not mapped");
            done    = false;
            myError = StepToTopoDS_TranslateEdgeLoopOther;
            continue;
          }
          else if (!ForwardEdge)
            forwardPC = 3 - forwardPC;

          if (forwardPC == 1)
          {
            if (isSeam)
            {

              B.UpdateEdge(E, C2d1, C2d2, Face, 0.);
            }
            else
              B.UpdateEdge(E, C2d1, Face, 0.);
          }
          else
          {
            if (isSeam)
            {

              B.UpdateEdge(E, C2d2, C2d1, Face, 0.);
            }
            else
              B.UpdateEdge(E, C2d2, Face, 0.);
          }
        }
        else
        {
          TP->AddFail(EC, " Seam curve not mapped");
          done    = false;
          myError = StepToTopoDS_TranslateEdgeLoopOther;
          continue;
        }
      }
      else
      {

        if (hasPcurve)
        {
          if (!C2d.IsNull() && !isLikeSeam)
          {
            B.UpdateEdge(E, C2d, Face, 0.);
          }
          else
          {
            TP->AddFail(EC, " Edge: Trimming of 2D curve failed");
            done    = false;
            myError = StepToTopoDS_TranslateEdgeLoopOther;
            continue;
          }
        }
      }

      if (E.IsNull())
      {
        TP->AddFail(EC, " an Edge not mapped");
        done    = false;
        myError = StepToTopoDS_TranslateEdgeLoopOther;
      }
    }
    else
    {
      TP->AddFail(EC, " an Edge not mapped");
      done    = false;
      myError = StepToTopoDS_TranslateEdgeLoopOther;
    }

    if (done)
      B.Add(W, E);
    else
    {
      occ::handle<StepShape_Vertex> Vs1, Vs2;
      Vs1 = EC->EdgeStart();
      Vs2 = EC->EdgeEnd();
      if (!Vs1.IsNull() && !Vs2.IsNull() && Vs1 == Vs2)
      {
        done = true;
        TP->AddFail(EL, " Edge with equal vertices failed, scipped");
      }
    }
  }

  if (!done)
  {
    TP->AddFail(EL, "At least one edge failed : wire not done");
    return;
  }
  W.Closed(BRep_Tool::IsClosed(W));
  aTool.Bind(EL, W);

  if (!aTool.ComputePCurve())
    for (TopoDS_Iterator EdgeIt(W); EdgeIt.More(); EdgeIt.Next())
    {
      TopoDS_Edge                       edge = TopoDS::Edge(EdgeIt.Value());
      occ::handle<ShapeFix_EdgeProjAux> myEdgePro =
        ShapeAlgo::AlgoContainer()->ToolContainer()->EdgeProjAux();
      myEdgePro->Init(Face, edge);
      myEdgePro->Compute(preci);
      if (myEdgePro->IsFirstDone() && myEdgePro->IsLastDone())
      {
        if (std::abs(myEdgePro->FirstParam() - myEdgePro->LastParam()) < Precision::PConfusion())
          continue;
        B.Range(edge, Face, myEdgePro->FirstParam(), myEdgePro->LastParam());
      }
      else
      {
        RemoveSinglePCurve(edge, Face);
#ifdef OCCT_DEBUG
        std::cout << "Removing after prj" << std::endl;
#endif
      }
    }

  myResult = W;
  myError  = StepToTopoDS_TranslateEdgeLoopDone;
  done     = true;

  CheckPCurves(W, Face, isPlane, preci);

  return;
}

const TopoDS_Shape& StepToTopoDS_TranslateEdgeLoop::Value() const
{
  StdFail_NotDone_Raise_if(!done, "StepToTopoDS_TranslateEdgeLoop::Value() - no result");
  return myResult;
}

StepToTopoDS_TranslateEdgeLoopError StepToTopoDS_TranslateEdgeLoop::Error() const
{
  return myError;
}
