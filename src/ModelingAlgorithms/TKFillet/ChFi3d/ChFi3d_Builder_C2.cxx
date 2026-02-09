#include <Adaptor2d_Curve2d.hpp>
#include <Blend_CurvPointFuncInv.hpp>
#include <Blend_FuncInv.hpp>
#include <BRepBlend_Line.hpp>
#include <BRepTopAdaptor_TopolTool.hpp>
#include <ChFi3d_Builder.hpp>
#include <ChFi3d_Builder_0.hpp>
#include <ChFiDS_CommonPoint.hpp>
#include <ChFiDS_FaceInterference.hpp>
#include <ChFiDS_SurfData.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <ChFiDS_Stripe.hpp>
#include <NCollection_List.hpp>
#include <ChFiDS_Spine.hpp>
#include <Extrema_ExtPC.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom_BoundedCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Surface.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomLib.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_NotImplemented.hpp>
#include <NCollection_Array1.hpp>
#include <TopAbs.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>
#include <TopOpeBRepDS_Curve.hpp>
#include <TopOpeBRepDS_CurvePointInterference.hpp>
#include <TopOpeBRepDS_DataStructure.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_SurfaceCurveInterference.hpp>

static void Reduce(const double&                     p1,
                   const double&                     p2,
                   occ::handle<GeomAdaptor_Surface>& hs1,
                   occ::handle<GeomAdaptor_Surface>& hs2)
{
  GeomAdaptor_Surface&             s1   = *hs1;
  GeomAdaptor_Surface&             s2   = *hs2;
  const occ::handle<Geom_Surface>& surf = s1.Surface();
  double                           ud, uf, vd, vf;
  surf->Bounds(ud, uf, vd, vf);
  double milmoins = 0.51 * vd + 0.49 * vf, milplus = 0.49 * vd + 0.51 * vf;
  if (p1 < p2)
  {
    s1.Load(surf, ud, uf, vd, milmoins);
    s2.Load(surf, ud, uf, milplus, vf);
  }
  else
  {
    s1.Load(surf, ud, uf, milplus, vf);
    s2.Load(surf, ud, uf, vd, milmoins);
  }
}

static void Reduce(const double& p1, const double& p2, occ::handle<GeomAdaptor_Curve>& hc)
{
  GeomAdaptor_Curve& c        = *hc;
  double             f        = c.FirstParameter();
  double             l        = c.LastParameter();
  double             milmoins = 0.51 * f + 0.49 * l, milplus = 0.49 * f + 0.51 * l;
  if (p1 < p2)
  {
    c.Load(c.Curve(), f, milmoins);
  }
  else
  {
    c.Load(c.Curve(), milplus, l);
  }
}

bool ChFi3d_Builder::PerformTwoCornerbyInter(const int Index)

{
  done                             = false;
  const TopoDS_Vertex&        Vtx  = myVDataMap.FindKey(Index);
  TopOpeBRepDS_DataStructure& DStr = myDS->ChangeDS();

  NCollection_List<occ::handle<ChFiDS_Stripe>>::Iterator It;
  It.Initialize(myVDataMap(Index));
  occ::handle<ChFiDS_Stripe>& Corner1 = It.ChangeValue();
  int                         Sens1;
  int                         IFd1 = ChFi3d_IndexOfSurfData(Vtx, Corner1, Sens1);
  NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqFil1 =
    Corner1->ChangeSetOfSurfData()->ChangeSequence();
  occ::handle<ChFiDS_SurfData>& Fd1 = SeqFil1.ChangeValue(IFd1);

  It.Next();
  occ::handle<ChFiDS_Stripe>& Corner2 = It.ChangeValue();
  int                         Sens2;
  int                         IFd2;
  if (Corner2 == Corner1)
  {
    Sens2 = -1;
    IFd2  = Corner2->SetOfSurfData()->Length();
  }
  else
  {
    IFd2 = ChFi3d_IndexOfSurfData(Vtx, Corner2, Sens2);
  }
  NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqFil2 =
    Corner2->ChangeSetOfSurfData()->ChangeSequence();
  occ::handle<ChFiDS_SurfData>& Fd2 = SeqFil2.ChangeValue(IFd2);

  bool        isfirst1 = (Sens1 == 1);
  bool        isfirst2 = (Sens2 == 1);
  bool        OkinterCC, Okvisavis, SameSide;
  int         IFaCo1, IFaCo2;
  double      UIntPC1, UIntPC2;
  TopoDS_Face FaCo;
  OkinterCC = ChFi3d_IsInFront(DStr,
                               Corner1,
                               Corner2,
                               IFd1,
                               IFd2,
                               Sens1,
                               Sens2,
                               UIntPC1,
                               UIntPC2,
                               FaCo,
                               SameSide,
                               IFaCo1,
                               IFaCo2,
                               Okvisavis,
                               Vtx,
                               true);
  if (!Okvisavis)
  {
#ifdef OCCT_DEBUG
    std::cout << "TwoCorner : pas de face commune" << std::endl;
#endif
    done = false;
    return done;
  }
  if (!OkinterCC)
  {

    OkinterCC = ChFi3d_IsInFront(DStr,
                                 Corner1,
                                 Corner2,
                                 IFd1,
                                 IFd2,
                                 Sens1,
                                 Sens2,
                                 UIntPC1,
                                 UIntPC2,
                                 FaCo,
                                 SameSide,
                                 IFaCo1,
                                 IFaCo2,
                                 Okvisavis,
                                 Vtx,
                                 true,
                                 true);
  }

  if (!Okvisavis)
  {
#ifdef OCCT_DEBUG
    std::cout << "TwoCorner : no common face" << std::endl;
#endif
    done = false;
    return done;
  }
  if (!OkinterCC)
  {
#ifdef OCCT_DEBUG
    std::cout << "biseau : failed intersection of tangency lines on common face" << std::endl;
#endif
    done = false;
    return done;
  }
  int IFaArc1 = 3 - IFaCo1, IFaArc2 = 3 - IFaCo2;

  ChFiDS_CommonPoint& CP1 = Fd1->ChangeVertex(isfirst1, IFaArc1);
  ChFiDS_CommonPoint& CP2 = Fd2->ChangeVertex(isfirst2, IFaArc2);

  if (!CP1.IsOnArc() || !CP2.IsOnArc())
  {
#ifdef OCCT_DEBUG
    std::cout << "fail 1 of 2 fillets are not on arc" << std::endl;
#endif
    done = false;
    return done;
  }
  if (!CP1.Arc().IsSame(CP2.Arc()))
  {

#ifdef OCCT_DEBUG
    std::cout << "PerformTwoCornerbyInter(): fillets are not on the same arc" << std::endl;
#endif
    done = true;
    PerformMoreThreeCorner(Index, 2);
    return done;
  }

  TopoDS_Edge pivot;
  pivot                                 = CP1.Arc();
  double                         parCP1 = CP1.ParameterOnArc();
  double                         parCP2 = CP2.ParameterOnArc();
  occ::handle<BRepAdaptor_Curve> Hpivot = new BRepAdaptor_Curve(pivot);
  if (!pivot.IsSame(CP2.Arc()))
  {
    occ::handle<Geom_Curve> csau;
    double                  ubid, vbid;
    csau                              = BRep_Tool::Curve(pivot, ubid, vbid);
    occ::handle<Geom_BoundedCurve> C1 = occ::down_cast<Geom_BoundedCurve>(csau);
    if (!C1.IsNull())
    {
      GeomLib::ExtendCurveToPoint(C1, CP2.Point(), 1, false);
      GeomAdaptor_Curve cad;
      cad.Load(C1);
      Extrema_ExtPC ext(CP2.Point(), cad, 1.e-4);
      parCP2 = ext.Point(1).Parameter();
    }
  }
  gp_Pnt psp1      = Hpivot->Value(parCP1);
  gp_Pnt psp2      = Hpivot->Value(parCP2);
  double sameparam = (psp1.Distance(psp2) < 10.0 * tolapp3d);

  TopoDS_Face                              FF1 = TopoDS::Face(DStr.Shape(Fd1->Index(IFaArc1)));
  TopoDS_Face                              FF2 = TopoDS::Face(DStr.Shape(Fd2->Index(IFaArc2)));
  NCollection_List<TopoDS_Shape>::Iterator Kt;
  bool                                     ok1 = false, ok2 = false;
  for (Kt.Initialize(myEFMap(pivot)); Kt.More(); Kt.Next())
  {
    TopoDS_Face F = TopoDS::Face(Kt.Value());
    if (!ok1 && FF1.IsSame(F))
    {
      ok1 = true;
    }
    if (!ok2 && FF2.IsSame(F))
    {
      ok2 = true;
    }
  }
  if (!ok1 || !ok2)
  {
#ifdef OCCT_DEBUG
    std::cout << "fail one of surfaces has no common base face with the pivot edge" << std::endl;
#endif
    done = false;
    return done;
  }

  occ::handle<GeomAdaptor_Surface> HS1, HS2;
  HS1 = ChFi3d_BoundSurf(DStr, Fd1, IFaCo1, IFaArc1);
  HS2 = ChFi3d_BoundSurf(DStr, Fd2, IFaCo2, IFaArc2);

  NCollection_Array1<double> Pardeb(1, 4), Parfin(1, 4);

  occ::handle<Geom2d_Curve> PGc1, PGc2;
  occ::handle<Geom_Curve>   Gc;

  if (sameparam)
  {

    ChFi3d_ComputesIntPC(Fd1->Interference(IFaCo1),
                         Fd2->Interference(IFaCo2),
                         HS1,
                         HS2,
                         UIntPC1,
                         UIntPC2);
    gp_Pnt2d UV;
    UV           = Fd1->Interference(IFaCo1).PCurveOnSurf()->Value(UIntPC1);
    Pardeb(1)    = UV.X();
    Pardeb(2)    = UV.Y();
    UV           = Fd2->Interference(IFaCo2).PCurveOnSurf()->Value(UIntPC2);
    Pardeb(3)    = UV.X();
    Pardeb(4)    = UV.Y();
    gp_Pnt PFaCo = HS1->Value(Pardeb(1), Pardeb(2));

    double UIntArc1 = Fd1->Interference(IFaArc1).Parameter(isfirst1);
    double UIntArc2 = Fd2->Interference(IFaArc2).Parameter(isfirst2);

    ChFi3d_ComputesIntPC(Fd1->Interference(IFaArc1),
                         Fd2->Interference(IFaArc2),
                         HS1,
                         HS2,
                         UIntArc1,
                         UIntArc2);
    UV        = Fd1->Interference(IFaArc1).PCurveOnSurf()->Value(UIntArc1);
    Parfin(1) = UV.X();
    Parfin(2) = UV.Y();
    UV        = Fd2->Interference(IFaArc2).PCurveOnSurf()->Value(UIntArc2);
    Parfin(3) = UV.X();
    Parfin(4) = UV.Y();

    if (Fd1->Surf() == Fd2->Surf())
    {
      Reduce(UIntPC1, UIntPC2, HS1, HS2);
    }

    double tolreached = tolapp3d;
    if (IFaCo1 == 1
        && !ChFi3d_ComputeCurves(HS1,
                                 HS2,
                                 Pardeb,
                                 Parfin,
                                 Gc,
                                 PGc1,
                                 PGc2,
                                 tolapp3d,
                                 tol2d,
                                 tolreached))
    {
#ifdef OCCT_DEBUG
      std::cout << "failed to calculate bevel error interSS" << std::endl;
#endif
      done = false;
      return done;
    }
    else if (IFaCo1 == 2
             && !ChFi3d_ComputeCurves(HS1,
                                      HS2,
                                      Parfin,
                                      Pardeb,
                                      Gc,
                                      PGc1,
                                      PGc2,
                                      tolapp3d,
                                      tol2d,
                                      tolreached))
    {
#ifdef OCCT_DEBUG
      std::cout << "failed to calculate bevel error interSS" << std::endl;
#endif
      done = false;
      return done;
    }

    double              WFirst = Gc->FirstParameter();
    double              WLast  = Gc->LastParameter();
    int                 Ipoin1;
    int                 Ipoin2;
    ChFiDS_CommonPoint& cpco1   = Fd1->ChangeVertex(isfirst1, IFaCo1);
    ChFiDS_CommonPoint& cpco2   = Fd2->ChangeVertex(isfirst2, IFaCo2);
    double              tolpco  = std::max(cpco1.Tolerance(), cpco2.Tolerance());
    ChFiDS_CommonPoint& cparc1  = Fd1->ChangeVertex(isfirst1, IFaArc1);
    ChFiDS_CommonPoint& cparc2  = Fd2->ChangeVertex(isfirst2, IFaArc2);
    double              tolparc = std::max(cparc1.Tolerance(), cparc2.Tolerance());
    int                 ICurv   = DStr.AddCurve(TopOpeBRepDS_Curve(Gc, tolreached));

    Corner1->SetParameters(isfirst1, WFirst, WLast);
    Corner1->SetCurve(ICurv, isfirst1);
    Corner1->ChangePCurve(isfirst1) = PGc1;
    cpco1.Reset();
    cpco1.SetPoint(PFaCo);
    cpco1.SetTolerance(std::max(tolreached, tolpco));
    Fd1->ChangeInterference(IFaCo1).SetParameter(UIntPC1, isfirst1);
    tolparc = std::max(tolparc, tolreached);
    cparc1.SetTolerance(std::max(tolparc, tolreached));
    Ipoin1 = ChFi3d_IndexPointInDS(Fd1->Vertex(isfirst1, 1), DStr);
    Corner1->SetIndexPoint(Ipoin1, isfirst1, 1);
    Ipoin2 = ChFi3d_IndexPointInDS(Fd1->Vertex(isfirst1, 2), DStr);
    Corner1->SetIndexPoint(Ipoin2, isfirst1, 2);

    Corner2->SetParameters(isfirst2, WFirst, WLast);
    Corner2->SetCurve(ICurv, isfirst2);
    Corner2->ChangePCurve(isfirst2) = PGc2;
    Fd2->ChangeInterference(IFaCo2).SetParameter(UIntPC2, isfirst2);
    Fd2->ChangeVertex(isfirst2, IFaCo2)  = Fd1->Vertex(isfirst1, IFaCo1);
    Fd2->ChangeVertex(isfirst2, IFaArc2) = Fd1->Vertex(isfirst1, IFaArc1);
    if (IFaCo1 != IFaCo2)
      Corner2->SetOrientation(TopAbs_REVERSED, isfirst2);
    Corner2->SetIndexPoint(Corner1->IndexPoint(isfirst1, IFaCo1), isfirst2, IFaCo2);
    Corner2->SetIndexPoint(Corner1->IndexPoint(isfirst1, IFaArc1), isfirst2, IFaArc2);

    Bnd_Box bco, barc;
    if (IFaCo1 == 1)
      ChFi3d_EnlargeBox(DStr, Corner1, Fd1, bco, barc, isfirst1);
    else
      ChFi3d_EnlargeBox(DStr, Corner1, Fd1, barc, bco, isfirst1);
    if (IFaCo2 == 1)
      ChFi3d_EnlargeBox(DStr, Corner2, Fd2, bco, barc, isfirst2);
    else
      ChFi3d_EnlargeBox(DStr, Corner2, Fd2, barc, bco, isfirst2);
    const ChFiDS_CommonPoint& cparc = Fd1->Vertex(isfirst1, IFaArc1);
    ChFi3d_EnlargeBox(cparc.Arc(), myEFMap(cparc.Arc()), cparc.ParameterOnArc(), barc);
    ChFi3d_SetPointTolerance(DStr, barc, Corner1->IndexPoint(isfirst1, IFaArc1));
    ChFi3d_SetPointTolerance(DStr, bco, Corner1->IndexPoint(isfirst1, IFaCo1));
  }
  else
  {

    bool            parcrois = false;
    TopExp_Explorer Expl;
    for (Expl.Init(pivot.Oriented(TopAbs_FORWARD), TopAbs_VERTEX); Expl.More(); Expl.Next())
    {
      if (Expl.Current().IsSame(Vtx))
      {
        parcrois = (Expl.Current().Orientation() == TopAbs_FORWARD);
        break;
      }
    }
    occ::handle<ChFiDS_Stripe>       BigCD, SmaCD;
    occ::handle<ChFiDS_SurfData>     BigFD, SmaFD;
    occ::handle<GeomAdaptor_Surface> BigHS, SmaHS;
    int                              IFaCoBig, IFaCoSma, IFaArcBig, IFaArcSma;
    bool                             isfirstBig, isfirstSma;
    double                           UIntPCBig, UIntPCSma;

    if ((parcrois && parCP2 > parCP1) || (!parcrois && parCP2 < parCP1))
    {
      UIntPCBig  = UIntPC2;
      UIntPCSma  = UIntPC1;
      BigHS      = HS2;
      SmaHS      = HS1;
      BigCD      = Corner2;
      SmaCD      = Corner1;
      BigFD      = Fd2;
      SmaFD      = Fd1;
      IFaCoBig   = IFaCo2;
      IFaCoSma   = IFaCo1;
      IFaArcBig  = IFaArc2;
      IFaArcSma  = IFaArc1;
      isfirstBig = isfirst2;
      isfirstSma = isfirst1;
    }
    else
    {
      UIntPCBig = UIntPC1, UIntPCSma = UIntPC2;
      BigHS      = HS1;
      SmaHS      = HS2;
      BigCD      = Corner1;
      SmaCD      = Corner2;
      BigFD      = Fd1;
      SmaFD      = Fd2;
      IFaCoBig   = IFaCo1;
      IFaCoSma   = IFaCo2;
      IFaArcBig  = IFaArc1;
      IFaArcSma  = IFaArc2;
      isfirstBig = isfirst1;
      isfirstSma = isfirst2;
    }

    ChFi3d_ComputesIntPC(SmaFD->Interference(IFaCoSma),
                         BigFD->Interference(IFaCoBig),
                         SmaHS,
                         BigHS,
                         UIntPCSma,
                         UIntPCBig);
    gp_Pnt2d UVi;
    UVi          = BigFD->Interference(IFaCoBig).PCurveOnSurf()->Value(UIntPCBig);
    Pardeb(3)    = UVi.X();
    Pardeb(4)    = UVi.Y();
    UVi          = SmaFD->Interference(IFaCoSma).PCurveOnSurf()->Value(UIntPCSma);
    Pardeb(1)    = UVi.X();
    Pardeb(2)    = UVi.Y();
    gp_Pnt PFaCo = SmaHS->Value(UVi.X(), UVi.Y());

    const ChFiDS_FaceInterference& FiArcSma = SmaFD->Interference(IFaArcSma);
    occ::handle<Geom_Curve>        ctg      = DStr.Curve(FiArcSma.LineIndex()).Curve();
    occ::handle<GeomAdaptor_Curve> Hctg     = new GeomAdaptor_Curve();
    GeomAdaptor_Curve&             bid      = *Hctg;
    double                         temp, wi;

    if (isfirstSma)
    {
      wi = temp = FiArcSma.FirstParameter();
      if (UIntPCSma < temp)
        temp = UIntPCSma;
      bid.Load(ctg, temp, FiArcSma.LastParameter());
    }
    else
    {
      wi = temp = FiArcSma.LastParameter();
      if (UIntPCSma > temp)
        temp = UIntPCSma;
      bid.Load(ctg, FiArcSma.FirstParameter(), temp);
    }
    if (SmaFD->Surf() == BigFD->Surf())
    {
      Reduce(UIntPCSma, UIntPCBig, SmaHS, BigHS);
      Reduce(UIntPCSma, UIntPCBig, Hctg);
    }
    if (!ChFi3d_IntCS(BigHS, Hctg, UVi, wi))
    {
#ifdef OCCT_DEBUG
      std::cout << "bevel : failed inter C S" << std::endl;
#endif
      done = false;
      return done;
    }
    Parfin(3)   = UVi.X();
    Parfin(4)   = UVi.Y();
    UVi         = FiArcSma.PCurveOnSurf()->Value(wi);
    Parfin(1)   = UVi.X();
    Parfin(2)   = UVi.Y();
    gp_Pnt PMil = SmaHS->Value(Parfin(1), Parfin(2));

    double tolreached;
    if (!ChFi3d_ComputeCurves(SmaHS,
                              BigHS,
                              Pardeb,
                              Parfin,
                              Gc,
                              PGc1,
                              PGc2,
                              tolapp3d,
                              tol2d,
                              tolreached))
    {
#ifdef OCCT_DEBUG
      std::cout << "failed to calculate bevel failed interSS" << std::endl;
#endif
      done = false;
      return done;
    }

    double              WFirst = Gc->FirstParameter();
    double              WLast  = Gc->LastParameter();
    int                 IpointCo, IpointMil, IpointArc;
    ChFiDS_CommonPoint& psmaco  = SmaFD->ChangeVertex(isfirstSma, IFaCoSma);
    ChFiDS_CommonPoint& pbigco  = BigFD->ChangeVertex(isfirstBig, IFaCoBig);
    double              tolpco  = std::max(psmaco.Tolerance(), pbigco.Tolerance());
    ChFiDS_CommonPoint& psmamil = SmaFD->ChangeVertex(isfirstSma, IFaArcSma);
    double              tolpmil = psmamil.Tolerance();
    int                 ICurv   = DStr.AddCurve(TopOpeBRepDS_Curve(Gc, tolreached));

    SmaCD->SetParameters(isfirstSma, WFirst, WLast);
    SmaCD->SetCurve(ICurv, isfirstSma);
    SmaCD->ChangePCurve(isfirstSma) = PGc1;
    psmaco.Reset();
    psmaco.SetPoint(PFaCo);
    psmaco.SetTolerance(std::max(tolpco, tolreached));
    SmaFD->ChangeInterference(IFaCoSma).SetParameter(UIntPCSma, isfirstSma);
    psmamil.Reset();
    psmamil.SetPoint(PMil);
    psmamil.SetTolerance(std::max(tolpmil, tolreached));
    SmaFD->ChangeInterference(IFaArcSma).SetParameter(wi, isfirstSma);
    IpointCo = ChFi3d_IndexPointInDS(psmaco, DStr);
    SmaCD->SetIndexPoint(IpointCo, isfirstSma, IFaCoSma);
    IpointMil = ChFi3d_IndexPointInDS(psmamil, DStr);
    SmaCD->SetIndexPoint(IpointMil, isfirstSma, IFaArcSma);
    if (IFaCoSma == 2)
      SmaCD->SetOrientation(TopAbs_REVERSED, isfirstSma);

    BigCD->SetIndexPoint(IpointCo, isfirstBig, IFaCoBig);
    BigFD->ChangeVertex(isfirstBig, IFaCoBig) = psmaco;
    BigFD->ChangeInterference(IFaCoBig).SetParameter(UIntPCBig, isfirstBig);

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& Li =
      DStr.ChangeCurveInterferences(ICurv);
    occ::handle<TopOpeBRepDS_CurvePointInterference> Interfp;
    Interfp = ChFi3d_FilPointInDS(TopAbs_FORWARD, ICurv, IpointCo, WFirst);
    Li.Append(Interfp);
    Interfp = ChFi3d_FilPointInDS(TopAbs_REVERSED, ICurv, IpointMil, WLast);
    Li.Append(Interfp);

    TopAbs_Orientation tra     = BigFD->InterferenceOnS1().Transition();
    TopAbs_Orientation ofac    = DStr.Shape(BigFD->IndexOfS1()).Orientation();
    TopAbs_Orientation ofil    = BigFD->Orientation();
    TopAbs_Orientation tracurv = TopAbs::Compose(ofac, ofil);
    tracurv                    = TopAbs::Compose(tracurv, tra);
    if (!isfirstBig)
      tracurv = TopAbs::Reverse(tracurv);
    if (IFaCoBig != 1)
      tracurv = TopAbs::Reverse(tracurv);

    occ::handle<TopOpeBRepDS_SurfaceCurveInterference> Interfc;
    int                                                ISurf = BigFD->Surf();
    Interfc = ChFi3d_FilCurveInDS(ICurv, ISurf, PGc2, tracurv);
    DStr.ChangeSurfaceInterferences(ISurf).Append(Interfc);

    Bnd_Box bco, bmil, barc;
    if (IFaCoSma == 1)
      ChFi3d_EnlargeBox(DStr, SmaCD, SmaFD, bco, bmil, isfirstSma);
    else
      ChFi3d_EnlargeBox(DStr, SmaCD, SmaFD, bmil, bco, isfirstSma);
    ChFi3d_EnlargeBox(BigHS, PGc2, WFirst, WLast, bco, bmil);

    TopoDS_Face                      F       = TopoDS::Face(DStr.Shape(SmaFD->Index(IFaArcSma)));
    occ::handle<BRepAdaptor_Surface> HF      = new BRepAdaptor_Surface(F);
    double                           fsma    = FiArcSma.FirstParameter();
    double                           lsma    = FiArcSma.LastParameter();
    double                           deltSma = 0.05 * (lsma - fsma);
    occ::handle<Geom2d_Curve>        pcpc    = SmaFD->Interference(IFaArcSma).PCurveOnFace();
    fsma                                     = std::max(pcpc->FirstParameter(), wi - deltSma);
    lsma                                     = std::min(pcpc->LastParameter(), wi + deltSma);
    if (lsma < fsma)
    {
      done = false;
      return done;
    }
    occ::handle<Geom2dAdaptor_Curve> c2df =
      new Geom2dAdaptor_Curve(SmaFD->Interference(IFaArcSma).PCurveOnFace(), fsma, lsma);
    Adaptor3d_CurveOnSurface              consf(c2df, HF);
    occ::handle<Adaptor3d_CurveOnSurface> Hconsf = new Adaptor3d_CurveOnSurface(consf);
    if (!ChFi3d_IntCS(BigHS, Hconsf, UVi, wi))
    {
#ifdef OCCT_DEBUG
      std::cout << "bevel : failed inter C S" << std::endl;
#endif
      done = false;
      return done;
    }
    Pardeb(3)      = UVi.X();
    Pardeb(4)      = UVi.Y();
    UVi            = SmaFD->Interference(IFaArcSma).PCurveOnFace()->Value(wi);
    Pardeb(1)      = UVi.X();
    Pardeb(2)      = UVi.Y();
    gp_Pnt2d ppff1 = UVi;

    double ptg                = BigFD->Interference(IFaArcBig).Parameter(isfirstBig);
    UVi                       = BigFD->Interference(IFaArcBig).PCurveOnSurf()->Value(ptg);
    Parfin(3)                 = UVi.X();
    Parfin(4)                 = UVi.Y();
    ChFiDS_CommonPoint& cpend = BigFD->ChangeVertex(isfirstBig, IFaArcBig);
    TopoDS_Edge         etest = cpend.Arc();
    if (BRep_Tool::IsClosed(etest, F))
      etest.Reverse();
    BRepAdaptor_Curve2d arc(etest, F);
    UVi            = arc.Value(cpend.ParameterOnArc());
    Parfin(1)      = UVi.X();
    Parfin(2)      = UVi.Y();
    gp_Pnt2d ppff2 = UVi;

    double uu1, uu2, vv1, vv2;
    ChFi3d_Boite(ppff1, ppff2, uu1, uu2, vv1, vv2);

    ChFi3d_BoundFac(*HF, uu1, uu2, vv1, vv2, true);

    if (!ChFi3d_ComputeCurves(HF,
                              BigHS,
                              Pardeb,
                              Parfin,
                              Gc,
                              PGc1,
                              PGc2,
                              tolapp3d,
                              tol2d,
                              tolreached))
    {
#ifdef OCCT_DEBUG
      std::cout << "fail calculation bevel fail interSS" << std::endl;
#endif
      done = false;
      return done;
    }

    WFirst = Gc->FirstParameter();
    WLast  = Gc->LastParameter();
    ICurv  = DStr.AddCurve(TopOpeBRepDS_Curve(Gc, tolreached));
    cpend.SetTolerance(std::max(cpend.Tolerance(), tolreached));
    IpointArc = ChFi3d_IndexPointInDS(cpend, DStr);
    BigCD->SetIndexPoint(IpointArc, isfirstBig, IFaArcBig);

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& Li7 =
      DStr.ChangeCurveInterferences(ICurv);
    Interfp = ChFi3d_FilPointInDS(TopAbs_FORWARD, ICurv, IpointMil, WFirst);
    Li7.Append(Interfp);
    Interfp = ChFi3d_FilPointInDS(TopAbs_REVERSED, ICurv, IpointArc, WLast);
    Li7.Append(Interfp);
    Interfc = ChFi3d_FilCurveInDS(ICurv, ISurf, PGc2, tracurv);
    DStr.ChangeSurfaceInterferences(ISurf).Append(Interfc);
    BigCD->InDS(isfirstBig);

    int IShape = DStr.AddShape(F);
    if (SmaFD->Surf() == BigFD->Surf())
    {
      tracurv = TopAbs::Compose(etest.Orientation(), cpend.TransitionOnArc());
    }
    else
    {
      TopExp_Explorer Exp;
      for (Exp.Init(F.Oriented(TopAbs_FORWARD), TopAbs_EDGE); Exp.More(); Exp.Next())
      {
        if (Exp.Current().IsSame(etest))
        {
          tracurv = TopAbs::Compose(Exp.Current().Orientation(), cpend.TransitionOnArc());
          break;
        }
      }
    }
    Interfc = ChFi3d_FilCurveInDS(ICurv, IShape, PGc1, tracurv);
    DStr.ChangeShapeInterferences(IShape).Append(Interfc);

    occ::handle<ChFiDS_Stripe> bidst;
    if (IFaCoBig == 1)
      ChFi3d_EnlargeBox(DStr, bidst, BigFD, bco, barc, isfirstBig);
    else
      ChFi3d_EnlargeBox(DStr, bidst, BigFD, barc, bco, isfirstBig);
    ChFi3d_EnlargeBox(BigHS, PGc2, WFirst, WLast, bmil, barc);
    ChFi3d_EnlargeBox(HF, PGc1, WFirst, WLast, bmil, barc);
    ChFi3d_EnlargeBox(Gc, WFirst, WLast, bmil, barc);
    const ChFiDS_CommonPoint& cparc = BigFD->Vertex(isfirstBig, IFaArcBig);
    ChFi3d_EnlargeBox(cparc.Arc(), myEFMap(cparc.Arc()), cparc.ParameterOnArc(), barc);

    ChFi3d_SetPointTolerance(DStr, bco, SmaCD->IndexPoint(isfirstSma, IFaCoSma));
    ChFi3d_SetPointTolerance(DStr, bmil, SmaCD->IndexPoint(isfirstSma, IFaArcSma));
    ChFi3d_SetPointTolerance(DStr, barc, BigCD->IndexPoint(isfirstBig, IFaArcBig));
  }
  done = true;

  return done;
}

void ChFi3d_Builder::UpdateTolesp()
{
  NCollection_List<occ::handle<ChFiDS_Stripe>>::Iterator itel;

  for (itel.Initialize(myListStripe); itel.More(); itel.Next())
  {
    occ::handle<ChFiDS_Stripe>& curStripe             = itel.ChangeValue();
    occ::handle<ChFiDS_Spine>&  Spine                 = curStripe->ChangeSpine();
    const double                current_stripe_tolesp = Spine->GetTolesp();
    if (tolesp > current_stripe_tolesp)
    {
      tolesp = current_stripe_tolesp;
    }
  }
}
