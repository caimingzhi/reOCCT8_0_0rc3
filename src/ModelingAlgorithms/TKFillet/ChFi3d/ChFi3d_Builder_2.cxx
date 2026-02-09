#include <Adaptor2d_Curve2d.hpp>
#include <Blend_FuncInv.hpp>
#include <BRepBlend_Line.hpp>
#include <BRepLib_MakeFace.hpp>
#include <BRepLProp_SLProps.hpp>
#include <BRepTools.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <BRepTopAdaptor_TopolTool.hpp>
#include <ChFi3d.hpp>
#include <ChFi3d_Builder.hpp>
#include <ChFi3d_Builder_0.hpp>
#include <ChFiDS_ChamfSpine.hpp>
#include <ChFiDS_CommonPoint.hpp>
#include <ChFiDS_ElSpine.hpp>
#include <ChFiDS_ErrorStatus.hpp>
#include <ChFiDS_FaceInterference.hpp>
#include <ChFiDS_SurfData.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_List.hpp>
#include <ChFiDS_Spine.hpp>
#include <ChFiDS_State.hpp>
#include <ChFiDS_Stripe.hpp>
#include <ChFiKPart_ComputeData.hpp>
#include <ElCLib.hpp>
#include <Extrema_ExtPS.hpp>
#include <Extrema_LocateExtPC.hpp>
#include <Extrema_POnCurv.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <GeomFill_ConstrainedFilling.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <math_Vector.hpp>
#include <Precision.hpp>
#include <Standard_NotImplemented.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>

namespace
{

  static inline occ::handle<Geom2d_Curve> getCurveOnSurface(const TopoDS_Edge& theEdge,
                                                            const TopoDS_Face& theFace)
  {
    double aFirstParam = 0.;
    double aLastParam  = 0.;
    return BRep_Tool::CurveOnSurface(theEdge, theFace, aFirstParam, aLastParam);
  }

  static void ChFi3d_CoupeParPlan(const ChFiDS_CommonPoint&         compoint1,
                                  const ChFiDS_CommonPoint&         compoint2,
                                  occ::handle<GeomAdaptor_Surface>& HConge,
                                  const gp_Pnt2d&                   UV1,
                                  const gp_Pnt2d&                   UV2,
                                  const double                      tol3d,
                                  const double                      tol2d,
                                  occ::handle<Geom_Curve>&          C3d,
                                  occ::handle<Geom2d_Curve>&        pcurve,
                                  double&                           tolreached,
                                  double&                           Pardeb,
                                  double&                           Parfin,
                                  bool&                             plane)
  {
    plane = true;
    if (compoint1.IsOnArc() && compoint2.IsOnArc())
    {
      gp_Pnt            P1, P2;
      BRepAdaptor_Curve BCurv1(compoint1.Arc());
      BRepAdaptor_Curve BCurv2(compoint2.Arc());
      double            parE1, parE2;
      parE1 = compoint1.ParameterOnArc();
      parE2 = compoint2.ParameterOnArc();
      gp_Vec t1, t2;
      BCurv1.D1(parE1, P1, t1);
      BCurv2.D1(parE2, P2, t2);
      gp_Dir                  tgt1(t1);
      gp_Dir                  tgt2(t2);
      gp_Vec                  v12(P2.X() - P1.X(), P2.Y() - P1.Y(), P2.Z() - P1.Z());
      gp_Dir                  d12(v12);
      gp_Dir                  nor  = tgt1.Crossed(d12);
      occ::handle<Geom_Plane> Plan = new Geom_Plane(P1, nor);
      double                  scal;
      scal = std::abs(nor.Dot(tgt2));
      if (scal < 0.01)
      {
        occ::handle<GeomAdaptor_Surface> HPlan = new GeomAdaptor_Surface(Plan);
        occ::handle<Geom2d_Curve>        C2dint2;
        NCollection_Array1<double>       Pdeb(1, 4), Pfin(1, 4);
        GeomAdaptor_Surface              AS(Plan);
        Extrema_ExtPS                    anExtPS(P1,
                              AS,
                              AS.FirstUParameter(),
                              AS.LastUParameter(),
                              AS.FirstVParameter(),
                              AS.LastVParameter(),
                              1.e-3,
                              1.e-3,
                              Extrema_ExtFlag_MIN);
        double                           u1, v1;
        anExtPS.Point(1).Parameter(u1, v1);
        Pdeb(1) = UV1.X();
        Pdeb(2) = UV1.Y();
        Pdeb(3) = u1;
        Pdeb(4) = v1;
        anExtPS.Perform(P2);
        anExtPS.Point(1).Parameter(u1, v1);
        Pfin(1) = UV2.X();
        Pfin(2) = UV2.Y();
        Pfin(3) = u1;
        Pfin(4) = v1;
        if (ChFi3d_ComputeCurves(HConge,
                                 HPlan,
                                 Pdeb,
                                 Pfin,
                                 C3d,
                                 pcurve,
                                 C2dint2,
                                 tol3d,
                                 tol2d,
                                 tolreached))
        {
          Pardeb = C3d->FirstParameter();
          Parfin = C3d->LastParameter();
        }
        else
          plane = false;
      }
      else
        plane = false;
    }
    else
      plane = false;
  }

  static bool isTangentToArc(const ChFiDS_CommonPoint& aCommonPoint,
                             const double              anAngularTolerance)
  {
    if (!aCommonPoint.HasVector())
    {
      return false;
    }

    double                        aDummyParam1, aDummyParam2;
    const occ::handle<Geom_Curve> anArcCurve =
      BRep_Tool::Curve(aCommonPoint.Arc(), aDummyParam1, aDummyParam2);

    gp_Pnt aDummyPoint;
    gp_Vec anArcTangent;
    anArcCurve->D1(aCommonPoint.ParameterOnArc(), aDummyPoint, anArcTangent);

    const gp_Vec aCommonPointVector = aCommonPoint.Vector();
    return aCommonPointVector.IsParallel(anArcTangent, anAngularTolerance);
  }

  static bool BonVoisin(const gp_Pnt&                     Point,
                        occ::handle<BRepAdaptor_Surface>& HS,
                        TopoDS_Face&                      F,
                        occ::handle<GeomAdaptor_Surface>& plane,
                        const TopoDS_Edge&                cured,
                        double&                           XDep,
                        double&                           YDep,
                        const ChFiDS_Map&                 EFMap,
                        const double                      tol3d)
  {
    bool                           bonvoisin = true;
    double                         winter;
    gp_Pnt                         papp = HS->Value(XDep, YDep);
    double                         dist = RealLast();
    occ::handle<BRepAdaptor_Curve> hc   = new BRepAdaptor_Curve();
    occ::handle<Geom2d_Curve>      PC;
    bool                           found = false;

    TopExp_Explorer Ex;
    for (Ex.Init(F, TopAbs_EDGE); Ex.More(); Ex.Next())
    {
      const TopoDS_Edge& ecur = TopoDS::Edge(Ex.Current());
      if (!ecur.IsSame(cured))
      {
        hc->Initialize(ecur);
        double tolc = hc->Resolution(tol3d);
        if (ChFi3d_InterPlaneEdge(plane, hc, winter, true, tolc))
        {
          gp_Pnt np    = hc->Value(winter);
          double ndist = np.SquareDistance(papp);
          if (ndist < dist)
          {
            NCollection_List<TopoDS_Shape>::Iterator It;
            TopoDS_Face                              ff;
            bool                                     isclosed = BRep_Tool::IsClosed(ecur, F);
            bool isreallyclosed                               = BRepTools::IsReallyClosed(ecur, F);
            for (It.Initialize(EFMap(ecur)); It.More(); It.Next())
            {
              ff          = TopoDS::Face(It.Value());
              bool issame = ff.IsSame(F);

              bool istg = ChFi3d::IsTangentFaces(ecur, ff, F);

              if ((!issame || (issame && isreallyclosed)) && istg)
              {
                found            = true;
                TopoDS_Edge newe = ecur;
                newe.Orientation(TopAbs_FORWARD);
                dist = ndist;
                HS->Initialize(ff);
                if (isclosed && !isreallyclosed)
                {
                  TopoDS_Face fff = ff;
                  fff.Orientation(TopAbs_FORWARD);
                  TopExp_Explorer Ex2;
                  for (Ex2.Init(fff, TopAbs_EDGE); Ex2.More(); Ex2.Next())
                  {
                    if (newe.IsSame(Ex2.Current()))
                    {
                      newe = TopoDS::Edge(Ex2.Current());
                      PC   = getCurveOnSurface(newe, fff);
                      break;
                    }
                  }
                }
                else
                  PC = getCurveOnSurface(newe, ff);
                PC->Value(winter).Coord(XDep, YDep);
                if (issame)
                {
                  gp_Pnt spt;
                  gp_Vec sdu, sdv, nors;
                  HS->D1(XDep, YDep, spt, sdu, sdv);
                  nors = sdu.Crossed(sdv);
                  gp_Pnt cpt;
                  gp_Vec cd;
                  hc->D1(winter, cpt, cd);
                  gp_Vec      vref(Point, cpt);
                  TopoDS_Face fff = ff;
                  fff.Orientation(TopAbs_FORWARD);
                  if (vref.Dot(nors.Crossed(cd)) < 0.)
                  {
                    newe.Orientation(TopAbs_REVERSED);
                  }
                  PC = getCurveOnSurface(newe, fff);
                  PC->Value(winter).Coord(XDep, YDep);
                }
                break;
              }
            }
          }
        }
      }
    }
    if (!found)
      bonvoisin = false;
    return bonvoisin;
  }

  static bool Projection(Extrema_ExtPC&         PExt,
                         const gp_Pnt&          P,
                         const Adaptor3d_Curve& C,
                         double&                W,
                         double                 Tol)
  {
    double Dist2, daux2;
    Dist2 = C.Value(W).SquareDistance(P);

    if (Dist2 < Tol * Tol)
      return true;

    bool Ok = false;

    Extrema_LocateExtPC ext(P, C, W, Tol / 10);
    if (ext.IsDone())
    {
      daux2 = C.Value(ext.Point().Parameter()).SquareDistance(P);
      if (daux2 < Dist2)
      {
        W     = ext.Point().Parameter();
        Dist2 = daux2;
        Ok    = true;
        if (Dist2 < Tol * Tol)
          return true;
      }
    }

    PExt.Perform(P);
    if (PExt.IsDone())
    {
      for (int ii = 1; ii <= PExt.NbExt(); ii++)
      {
        if (PExt.SquareDistance(ii) < Dist2)
        {
          Dist2 = PExt.SquareDistance(ii);
          W     = PExt.Point(ii).Parameter();
          Ok    = true;
        }
      }
    }
    return Ok;
  }

  static void TgtKP(const occ::handle<ChFiDS_SurfData>& CD,
                    const occ::handle<ChFiDS_Spine>&    Spine,
                    const int                           iedge,
                    const bool                          isfirst,
                    gp_Pnt&                             ped,
                    gp_Vec&                             ded)
  {
    double                   wtg = CD->InterferenceOnS1().Parameter(isfirst);
    const BRepAdaptor_Curve& bc  = Spine->CurrentElementarySpine(iedge);
    if (Spine->Edges(iedge).Orientation() == TopAbs_FORWARD)
      bc.D1(wtg + bc.FirstParameter(), ped, ded);
    else
    {
      bc.D1(-wtg + bc.LastParameter(), ped, ded);
      ded.Reverse();
    }
    ded.Normalize();
  }

  static bool IsInput(const gp_Vec& Vec, const TopoDS_Vertex& Ve, const TopoDS_Face& Fa)
  {
    TopExp_Explorer        FaceExp(Fa, TopAbs_WIRE);
    BRepTools_WireExplorer WireExp;
    int                    Trouve = 0;
    TopoDS_Wire            W;
    TopoDS_Edge            E;
    TopoDS_Vertex          Vf, Vl;
    gp_Vec                 Vec3d[2];
    gp_Pnt                 Point;

    for (; (FaceExp.More() && (Trouve < 2)); FaceExp.Next())
    {
      W = TopoDS::Wire(FaceExp.Current());
      for (Trouve = 0, WireExp.Init(W); WireExp.More() && (Trouve < 2); WireExp.Next())
      {
        E = TopoDS::Edge(WireExp.Current());
        TopExp::Vertices(E, Vf, Vl);
        if (Vf.IsSame(Ve))
        {
          BRepAdaptor_Curve Cb(E);
          Cb.D1(BRep_Tool::Parameter(Ve, E), Point, Vec3d[Trouve]);
          Trouve++;
        }
        else if (Vl.IsSame(Ve))
        {
          BRepAdaptor_Curve Cb(E);
          Cb.D1(BRep_Tool::Parameter(Ve, E), Point, Vec3d[Trouve]);
          Vec3d[Trouve].Reverse();
          Trouve++;
        }
      }
    }
    if (Trouve < 2)
      return false;

    gp_Vec Normal;
    Normal = Vec3d[0] ^ Vec3d[1];
    if (Normal.SquareMagnitude() < Precision::Confusion())
    {
      return (Vec.IsParallel(Vec3d[0], Precision::Confusion()));
    }

    double amin, amax;
    amax = Vec3d[1].AngleWithRef(Vec3d[0], Normal);
    if (amax < 0)
    {
      amin = amax;
      amax = 0;
    }
    else
      amin = 0;

    gp_Ax3  Axe(Point, Normal, Vec3d[0]);
    gp_Trsf Transf;
    Transf.SetTransformation(Axe);
    gp_XYZ coord = Vec.XYZ();
    Transf.Transforms(coord);
    coord.SetZ(0);
    Transf.Invert();
    Transf.Transforms(coord);
    gp_Vec theProj(coord);

    double Angle = theProj.AngleWithRef(Vec3d[0], Normal);
    return ((Angle >= amin) && (Angle <= amax));
  }

  static bool IsG1(const ChFiDS_Map&  TheMap,
                   const TopoDS_Edge& E,
                   const TopoDS_Face& FRef,
                   TopoDS_Face&       FVoi)
  {
    NCollection_List<TopoDS_Shape>::Iterator It;

    for (It.Initialize(TheMap(E)); It.More(); It.Next())
    {
      if (!TopoDS::Face(It.Value()).IsSame(FRef))
      {
        FVoi = TopoDS::Face(It.Value());

        if (ChFi3d::IsTangentFaces(E, FRef, FVoi))
        {

          return true;
        }
      }
    }

    TopExp_Explorer    Ex;
    bool               orset  = false;
    TopAbs_Orientation orient = TopAbs_FORWARD;
    TopoDS_Edge        ed;
    for (Ex.Init(FRef, TopAbs_EDGE); Ex.More(); Ex.Next())
    {
      ed = TopoDS::Edge(Ex.Current());
      if (ed.IsSame(E))
      {
        if (!orset)
        {
          orient = ed.Orientation();
          orset  = true;
        }
        else if (ed.Orientation() == TopAbs::Reverse(orient))
        {
          FVoi = FRef;

          return ChFi3d::IsTangentFaces(E, FRef, FRef);
        }
      }
    }
    return false;
  }

  static int SearchFaceOnV(const ChFiDS_CommonPoint& Pc,
                           const TopoDS_Face&        FRef,
                           const ChFiDS_Map&         VEMap,
                           const ChFiDS_Map&         EFMap,
                           TopoDS_Face&              F1,
                           TopoDS_Face&              F2)
  {

    bool FindFace = IsInput(Pc.Vector(), Pc.Vertex(), FRef);
    if (FindFace)
    {
      FindFace = IsInput(Pc.Vector().Reversed(), Pc.Vertex(), FRef);
    }

    if (FindFace)
    {
      F1 = FRef;
      return 1;
    }
    int                                      Num = 0;
    bool                                     Trouve;
    NCollection_List<TopoDS_Shape>::Iterator ItE, ItF;
    TopoDS_Edge                              E;
    TopoDS_Face                              FVoi;

    for (ItE.Initialize(VEMap(Pc.Vertex())); ItE.More() && (Num < 2); ItE.Next())
    {
      E = TopoDS::Edge(ItE.Value());
      for (ItF.Initialize(EFMap(E)), Trouve = false; ItF.More() && (!Trouve); ItF.Next())
      {
        if (TopoDS::Face(ItF.Value()).IsSame(FRef))
        {
          Trouve = true;
        }
      }
      if (Trouve)
        Trouve = IsG1(EFMap, E, FRef, FVoi);
      if (Trouve)
        Trouve = IsInput(Pc.Vector(), Pc.Vertex(), FVoi);
      if (Trouve)
      {
        if (Num == 0)
          F1 = FVoi;
        else
          F2 = FVoi;
        Num++;
      }
    }
    return Num;
  }

  static void ChangeTransition(const ChFiDS_CommonPoint&                       Precedant,
                               ChFiDS_CommonPoint&                             Courant,
                               int                                             FaceIndex,
                               const occ::handle<TopOpeBRepDS_HDataStructure>& DS)
  {
    bool                      tochange = true;
    const TopoDS_Face&        F        = TopoDS::Face(DS->Shape(FaceIndex));
    const TopoDS_Edge&        Arc      = Precedant.Arc();
    occ::handle<Geom2d_Curve> PCurve1, PCurve2;
    PCurve1                  = getCurveOnSurface(Arc, F);
    TopoDS_Shape aLocalShape = Arc.Reversed();
    PCurve2                  = getCurveOnSurface(TopoDS::Edge(aLocalShape), F);
    if (PCurve1 != PCurve2)
    {

      gp_Vec            tgarc;
      gp_Pnt            P;
      BRepAdaptor_Curve AC(Arc);
      AC.D1(Precedant.ParameterOnArc(), P, tgarc);
      tochange = tgarc.IsParallel(Precedant.Vector(), Precision::Confusion());
    }

    if (tochange)
      Courant.SetArc(Precision::Confusion(),
                     Arc,
                     Precedant.ParameterOnArc(),
                     TopAbs::Reverse(Precedant.TransitionOnArc()));
  }
} // namespace

void ChFi3d_Builder::CallPerformSurf(occ::handle<ChFiDS_Stripe>&                         Stripe,
                                     const bool                                          Simul,
                                     NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqSD,
                                     occ::handle<ChFiDS_SurfData>&                       SD,
                                     const occ::handle<ChFiDS_ElSpine>&                  HGuide,
                                     const occ::handle<ChFiDS_Spine>&                    Spine,
                                     const occ::handle<BRepAdaptor_Surface>&             HS1,
                                     const occ::handle<BRepAdaptor_Surface>&             HS3,
                                     const gp_Pnt2d&                                     pp1,
                                     const gp_Pnt2d&                                     pp3,
                                     const occ::handle<Adaptor3d_TopolTool>&             It1,
                                     const occ::handle<BRepAdaptor_Surface>&             HS2,
                                     const occ::handle<BRepAdaptor_Surface>&             HS4,
                                     const gp_Pnt2d&                                     pp2,
                                     const gp_Pnt2d&                                     pp4,
                                     const occ::handle<Adaptor3d_TopolTool>&             It2,
                                     const double                                        MaxStep,
                                     const double                                        Fleche,
                                     const double,
                                     double&    First,
                                     double&    Last,
                                     const bool Inside,
                                     const bool,
                                     const bool                        forward,
                                     const bool                        RecOnS1,
                                     const bool                        RecOnS2,
                                     math_Vector&                      Soldep,
                                     int&                              intf,
                                     int&                              intl,
                                     occ::handle<BRepAdaptor_Surface>& Surf1,
                                     occ::handle<BRepAdaptor_Surface>& Surf2)
{
  occ::handle<BRepAdaptor_Surface> HSon1, HSon2;
  HSon1 = HS1;
  HSon2 = HS2;

  It1->Initialize((const occ::handle<Adaptor3d_Surface>&)HSon1);
  It2->Initialize((const occ::handle<Adaptor3d_Surface>&)HSon2);

  TopAbs_Orientation Or1   = HS1->Face().Orientation();
  TopAbs_Orientation Or2   = HS2->Face().Orientation();
  int                Choix = ChFi3d::NextSide(Or1,
                               Or2,
                               Stripe->OrientationOnFace1(),
                               Stripe->OrientationOnFace2(),
                               Stripe->Choix());
  Soldep(1)                = pp1.X();
  Soldep(2)                = pp1.Y();
  Soldep(3)                = pp2.X();
  Soldep(4)                = pp2.Y();

  double thef = First, thel = Last;
  bool   isdone;

  if (Simul)
  {
    isdone = SimulSurf(SD,
                       HGuide,
                       Spine,
                       Choix,
                       HS1,
                       It1,
                       HS2,
                       It2,
                       tolesp,
                       First,
                       Last,
                       Inside,
                       Inside,
                       forward,
                       RecOnS1,
                       RecOnS2,
                       Soldep,
                       intf,
                       intl);
  }
  else
  {
    isdone = PerformSurf(SeqSD,
                         HGuide,
                         Spine,
                         Choix,
                         HS1,
                         It1,
                         HS2,
                         It2,
                         MaxStep,
                         Fleche,
                         tolesp,
                         First,
                         Last,
                         Inside,
                         Inside,
                         forward,
                         RecOnS1,
                         RecOnS2,
                         Soldep,
                         intf,
                         intl);
  }

  if (!isdone)
  {
    First        = thef;
    Last         = thel;
    bool reprise = false;
    if (!HS3.IsNull())
    {
      HSon1 = HS3;
      It1->Initialize((const occ::handle<Adaptor3d_Surface>&)HS3);
      Or1       = HS3->Face().Orientation();
      Soldep(1) = pp3.X();
      Soldep(2) = pp3.Y();
      reprise   = true;
    }
    else if (!HS4.IsNull())
    {
      HSon2 = HS4;
      It2->Initialize((const occ::handle<Adaptor3d_Surface>&)HS4);
      Or2       = HS4->Face().Orientation();
      Soldep(3) = pp4.X();
      Soldep(4) = pp4.Y();
      reprise   = true;
    }

    if (reprise)
    {
      Choix = ChFi3d::NextSide(Or1,
                               Or2,
                               Stripe->OrientationOnFace1(),
                               Stripe->OrientationOnFace2(),
                               Stripe->Choix());
      if (Simul)
      {
        isdone = SimulSurf(SD,
                           HGuide,
                           Spine,
                           Choix,
                           HSon1,
                           It1,
                           HSon2,
                           It2,
                           tolesp,
                           First,
                           Last,
                           Inside,
                           Inside,
                           forward,
                           RecOnS1,
                           RecOnS2,
                           Soldep,
                           intf,
                           intl);
      }
      else
      {
        isdone = PerformSurf(SeqSD,
                             HGuide,
                             Spine,
                             Choix,
                             HSon1,
                             It1,
                             HSon2,
                             It2,
                             MaxStep,
                             Fleche,
                             tolesp,
                             First,
                             Last,
                             Inside,
                             Inside,
                             forward,
                             RecOnS1,
                             RecOnS2,
                             Soldep,
                             intf,
                             intl);
      }
    }
  }
  Surf1 = HSon1;
  Surf2 = HSon2;
}

bool ChFi3d_Builder::StripeOrientations(const occ::handle<ChFiDS_Spine>& Spine,
                                        TopAbs_Orientation&              Or1,
                                        TopAbs_Orientation&              Or2,
                                        int&                             ChoixConge) const
{

  BRepAdaptor_Surface Sb1, Sb2;
  TopAbs_Orientation  Of1, Of2;
  TopoDS_Face         ff1, ff2;
  TopoDS_Edge         anEdge    = Spine->Edges(1);
  TopoDS_Face         FirstFace = TopoDS::Face(myEdgeFirstFace(anEdge));
  ChFi3d_conexfaces(anEdge, ff1, ff2, myEFMap);
  if (ff2.IsSame(FirstFace))
  {
    TopoDS_Face TmpFace = ff1;
    ff1                 = ff2;
    ff2                 = TmpFace;
  }
  Of1 = ff1.Orientation();
  ff1.Orientation(TopAbs_FORWARD);
  Sb1.Initialize(ff1);
  Of2 = ff2.Orientation();
  ff2.Orientation(TopAbs_FORWARD);
  Sb2.Initialize(ff2);

  ChoixConge = ChFi3d::ConcaveSide(Sb1, Sb2, Spine->Edges(1), Or1, Or2);
  Or1        = TopAbs::Compose(Or1, Of1);
  Or2        = TopAbs::Compose(Or2, Of2);
  return true;
}

void ChFi3d_Builder::ConexFaces(const occ::handle<ChFiDS_Spine>&  Spine,
                                const int                         IEdge,
                                occ::handle<BRepAdaptor_Surface>& HS1,
                                occ::handle<BRepAdaptor_Surface>& HS2) const
{
  if (HS1.IsNull())
    HS1 = new BRepAdaptor_Surface();
  if (HS2.IsNull())
    HS2 = new BRepAdaptor_Surface();
  BRepAdaptor_Surface& Sb1 = *HS1;
  BRepAdaptor_Surface& Sb2 = *HS2;

  TopoDS_Face ff1, ff2;
  TopoDS_Edge anEdge = Spine->Edges(IEdge);
  ChFi3d_conexfaces(Spine->Edges(IEdge), ff1, ff2, myEFMap);

  TopoDS_Face FirstFace = TopoDS::Face(myEdgeFirstFace(anEdge));
  if (ff2.IsSame(FirstFace))
  {
    TopoDS_Face TmpFace = ff1;
    ff1                 = ff2;
    ff2                 = TmpFace;
  }

  Sb1.Initialize(ff1);
  Sb2.Initialize(ff2);
}

void ChFi3d_Builder::StartSol(const occ::handle<ChFiDS_Stripe>&      Stripe,
                              const occ::handle<ChFiDS_ElSpine>&     HGuide,
                              occ::handle<BRepAdaptor_Surface>&      HS1,
                              occ::handle<BRepAdaptor_Surface>&      HS2,
                              occ::handle<BRepTopAdaptor_TopolTool>& I1,
                              occ::handle<BRepTopAdaptor_TopolTool>& I2,
                              gp_Pnt2d&                              P1,
                              gp_Pnt2d&                              P2,
                              double&                                First) const
{
  occ::handle<ChFiDS_Spine>& Spine      = Stripe->ChangeSpine();
  ChFiDS_ElSpine&            els        = *HGuide;
  int                        nbed       = Spine->NbEdges();
  int                        nbessaimax = 3 * nbed;
  if (nbessaimax < 10)
    nbessaimax = 10;
  double unsurnbessaimax = 1. / nbessaimax;
  double wf              = 0.9981 * Spine->FirstParameter(1) + 0.0019 * Spine->LastParameter(1);
  double wl = 0.9973 * Spine->LastParameter(nbed) + 0.0027 * Spine->FirstParameter(nbed);

  double              TolE = 1.0e-7;
  BRepAdaptor_Surface AS;

  int                       nbessai;
  int                       iedge = 0;
  int                       RC    = Stripe->Choix();
  gp_Vec2d                  derive;
  gp_Pnt2d                  P2d;
  TopoDS_Edge               cured;
  TopoDS_Face               f1, f2;
  TopAbs_Orientation        Or1, Or2;
  int                       Choix = 0;
  math_Vector               SolDep(1, 4);
  occ::handle<Geom2d_Curve> PC;
  Extrema_ExtPC             PExt;
  PExt.Initialize(els,
                  Spine->FirstParameter(1),
                  Spine->LastParameter(nbed),
                  Precision::Confusion());
  TopAbs_State Pos1, Pos2;
  for (nbessai = 0; nbessai <= nbessaimax; nbessai++)
  {
    double t  = nbessai * unsurnbessaimax;
    double w  = wf * (1. - t) + wl * t;
    int    ie = Spine->Index(w);
    if (iedge != ie)
    {
      iedge = ie;
      cured = Spine->Edges(iedge);
      TolE  = BRep_Tool::Tolerance(cured);
      ConexFaces(Spine, iedge, HS1, HS2);
      f1  = HS1->Face();
      f2  = HS2->Face();
      Or1 = f1.Orientation();
      Or2 = f2.Orientation();
      Choix =
        ChFi3d::NextSide(Or1, Or2, Stripe->OrientationOnFace1(), Stripe->OrientationOnFace2(), RC);
    }

    double woned, ResU, ResV;
    Spine->Parameter(iedge, w, woned, true);
    cured.Orientation(TopAbs_FORWARD);
    TopoDS_Face f1forward = f1, f2forward = f2;
    f1forward.Orientation(TopAbs_FORWARD);
    f2forward.Orientation(TopAbs_FORWARD);
    PC = getCurveOnSurface(cured, f1forward);
    I1->Initialize((const occ::handle<Adaptor3d_Surface>&)HS1);
    PC->D1(woned, P1, derive);

    if (derive.Magnitude() > Precision::PConfusion())
    {
      derive.Normalize();
      derive.Rotate(M_PI / 2);
      AS.Initialize(f1);
      ResU = AS.UResolution(TolE);
      ResV = AS.VResolution(TolE);
      derive *= 2 * (std::abs(derive.X()) * ResU + std::abs(derive.Y()) * ResV);
      P2d = P1.Translated(derive);
      if (I1->Classify(P2d, std::min(ResU, ResV), false) == TopAbs_IN)
      {
        P1 = P2d;
      }
      else
      {
        P2d = P1.Translated(-derive);
        if (I1->Classify(P2d, std::min(ResU, ResV), false) == TopAbs_IN)
        {
          P1 = P2d;
        }
      }
    }
    if (f1.IsSame(f2))
      cured.Orientation(TopAbs_REVERSED);
    PC                                          = getCurveOnSurface(cured, f2forward);
    P2                                          = PC->Value(woned);
    const occ::handle<Adaptor3d_Surface>& HSon2 = HS2;
    I2->Initialize(HSon2);

    SolDep(1)                    = P1.X();
    SolDep(2)                    = P1.Y();
    SolDep(3)                    = P2.X();
    SolDep(4)                    = P2.Y();
    const BRepAdaptor_Curve& Ced = Spine->CurrentElementarySpine(iedge);
    gp_Pnt                   pnt = Ced.Value(woned);

    if (Projection(PExt, pnt, els, w, tolapp3d)
        && PerformFirstSection(Spine, HGuide, Choix, HS1, HS2, I1, I2, w, SolDep, Pos1, Pos2))
    {
      P1.SetCoord(SolDep(1), SolDep(2));
      P2.SetCoord(SolDep(3), SolDep(4));
      First = w;
      return;
    }
  }

  iedge = 0;
  for (nbessai = 0; nbessai <= nbessaimax; nbessai++)
  {
    double t = nbessai * unsurnbessaimax;
    double w = wf * (1. - t) + wl * t;
    iedge    = Spine->Index(w);
    cured    = Spine->Edges(iedge);
    ConexFaces(Spine, iedge, HS1, HS2);
    f1  = HS1->Face();
    f2  = HS2->Face();
    Or1 = f1.Orientation();
    Or2 = f2.Orientation();
    Choix =
      ChFi3d::NextSide(Or1, Or2, Stripe->OrientationOnFace1(), Stripe->OrientationOnFace2(), RC);
    double woned;
    Spine->Parameter(iedge, w, woned, true);
    TopoDS_Face f1forward = f1, f2forward = f2;
    f1forward.Orientation(TopAbs_FORWARD);
    f2forward.Orientation(TopAbs_FORWARD);
    PC                                          = getCurveOnSurface(cured, f1forward);
    P1                                          = PC->Value(woned);
    PC                                          = getCurveOnSurface(cured, f2forward);
    P2                                          = PC->Value(woned);
    const occ::handle<Adaptor3d_Surface>& HSon1 = HS1;
    const occ::handle<Adaptor3d_Surface>& HSon2 = HS2;
    I1->Initialize(HSon1);
    I2->Initialize(HSon2);
    SolDep(1)                    = P1.X();
    SolDep(2)                    = P1.Y();
    SolDep(3)                    = P2.X();
    SolDep(4)                    = P2.Y();
    const BRepAdaptor_Curve& Ced = Spine->CurrentElementarySpine(iedge);
    gp_Pnt                   pnt = Ced.Value(woned);

    if (Projection(PExt, pnt, els, w, tolapp3d))
    {
      PerformFirstSection(Spine, HGuide, Choix, HS1, HS2, I1, I2, w, SolDep, Pos1, Pos2);
      gp_Pnt P;
      gp_Vec V;
      HGuide->D1(w, P, V);
      occ::handle<Geom_Plane>          pl    = new Geom_Plane(P, V);
      occ::handle<GeomAdaptor_Surface> plane = new GeomAdaptor_Surface(pl);

      bool bonvoisin = true, found = false;
      int  NbChangement;
      for (NbChangement = 1; bonvoisin && (!found) && (NbChangement < 5); NbChangement++)
      {
        if (Pos1 != TopAbs_IN)
        {
          bonvoisin = BonVoisin(P, HS1, f1, plane, cured, SolDep(1), SolDep(2), myEFMap, tolapp3d);
        }
        if (Pos2 != TopAbs_IN && bonvoisin)
        {
          bonvoisin = BonVoisin(P, HS2, f2, plane, cured, SolDep(3), SolDep(4), myEFMap, tolapp3d);
        }
        if (bonvoisin)
        {
          f1                                             = HS1->Face();
          f2                                             = HS2->Face();
          Or1                                            = f1.Orientation();
          Or2                                            = f2.Orientation();
          Choix                                          = ChFi3d::NextSide(Or1,
                                   Or2,
                                   Stripe->OrientationOnFace1(),
                                   Stripe->OrientationOnFace2(),
                                   RC);
          const occ::handle<Adaptor3d_Surface>& HSon1new = HS1;
          const occ::handle<Adaptor3d_Surface>& HSon2new = HS2;
          I1->Initialize(HSon1new);
          I2->Initialize(HSon2new);
          if (PerformFirstSection(Spine, HGuide, Choix, HS1, HS2, I1, I2, w, SolDep, Pos1, Pos2))
          {
            P1.SetCoord(SolDep(1), SolDep(2));
            P2.SetCoord(SolDep(3), SolDep(4));
            First = w;
            found = true;
          }
        }
      }
      if (found)
        return;
    }
  }
  Spine->SetErrorStatus(ChFiDS_StartsolFailure);
  throw Standard_Failure("StartSol echec");
}

static void ChFi3d_BuildPlane(TopOpeBRepDS_DataStructure&         DStr,
                              occ::handle<BRepAdaptor_Surface>&   HS,
                              gp_Pnt2d&                           pons,
                              const occ::handle<ChFiDS_SurfData>& SD,
                              const bool                          isfirst,
                              const int                           ons)
{
  const TopoDS_Face F = TopoDS::Face(DStr.Shape(SD->Index(ons)));
  if (F.IsNull())
  {
    return;
  }

  if (SD->Vertex(isfirst, ons).IsOnArc())
  {
    double                          u, v;
    const occ::handle<Geom2d_Curve> Hc =
      BRep_Tool::CurveOnSurface(SD->Vertex(isfirst, ons).Arc(), F, u, v);
    Hc->Value(SD->Vertex(isfirst, ons).ParameterOnArc()).Coord(u, v);
    BRepLProp_SLProps theProp(*HS, u, v, 1, 1.e-12);
    if (theProp.IsNormalDefined())
    {
      const occ::handle<Geom_Plane> Pln  = new Geom_Plane(theProp.Value(), theProp.Normal());
      TopoDS_Face                   NewF = BRepLib_MakeFace(Pln, Precision::Confusion());
      NewF.Orientation(F.Orientation());
      pons.SetCoord(0., 0.);
      HS->Initialize(NewF);
      return;
    }
  }
  throw Standard_Failure("ChFi3d_BuildPlane : echec .");
}

bool ChFi3d_Builder::StartSol(const occ::handle<ChFiDS_Spine>&    Spine,
                              occ::handle<BRepAdaptor_Surface>&   HS,
                              gp_Pnt2d&                           pons,
                              occ::handle<BRepAdaptor_Curve2d>&   HC,
                              double&                             W,
                              const occ::handle<ChFiDS_SurfData>& SD,
                              const bool                          isfirst,
                              const int                           ons,
                              occ::handle<BRepAdaptor_Surface>&   HSref,
                              occ::handle<BRepAdaptor_Curve2d>&   HCref,
                              bool&                               RecP,
                              bool&                               RecS,
                              bool&                               RecRst,
                              bool&                               c1obstacle,
                              occ::handle<BRepAdaptor_Surface>&   HSBis,
                              gp_Pnt2d&                           PBis,
                              const bool                          decroch,
                              const TopoDS_Vertex&                Vref) const
{
  RecP       = false;
  RecS       = false;
  RecRst     = false;
  c1obstacle = false;
  TopoDS_Face               Fv;
  occ::handle<Geom2d_Curve> aPCurve;

  const TopOpeBRepDS_DataStructure& DStr = myDS->ChangeDS();
  TopoDS_Face                       Fref = !HSref.IsNull() ? HSref->Face() : TopoDS_Face();
  TopoDS_Face                       F    = TopoDS::Face(DStr.Shape(SD->Index(ons)));

  const ChFiDS_CommonPoint& aCommonPoint = SD->Vertex(isfirst, ons);
  HSBis.Nullify();

  if (aCommonPoint.IsOnArc())
  {
    const int                 notons = ons == 1 ? 2 : 1;
    const ChFiDS_CommonPoint& CPbis  = SD->Vertex(isfirst, notons);
    if (CPbis.IsOnArc())
    {

      const double ts  = SD->Interference(ons).Parameter(isfirst);
      const double tns = SD->Interference(notons).Parameter(isfirst);

      const bool isExtend = isfirst ? (ts - tns > 100 * tolesp) : (tns - ts > 100 * tolesp);
      if (isExtend && !aCommonPoint.Point().IsEqual(CPbis.Point(), 0))
      {

        HS->Initialize(F);
        aPCurve = SD->Interference(ons).PCurveOnFace();

        RecS = false;
        pons = aPCurve->Value(tns);
        return false;
      }
    }
  }

  if (aCommonPoint.IsVertex() && !HC.IsNull() && !decroch)
  {

    const TopoDS_Vertex VCP = aCommonPoint.Vertex();
    const TopoDS_Edge   EHC = HC->Edge();

    TopoDS_Edge newedge;
    TopoDS_Edge edgereg;
    TopoDS_Face facereg;
    TopoDS_Face bidface = Fref;
    bidface.Orientation(TopAbs_FORWARD);
    for (TopExp_Explorer ex1(bidface, TopAbs_EDGE); ex1.More(); ex1.Next())
    {
      const TopoDS_Edge& cured = TopoDS::Edge(ex1.Current());
      bool               found = false;
      if (!cured.IsSame(EHC))
      {
        for (TopExp_Explorer ex2(cured, TopAbs_VERTEX); ex2.More() && !found; ex2.Next())
        {
          if (ex2.Current().IsSame(VCP))
          {
            if (IsG1(myEFMap, cured, Fref, Fv))
            {
              edgereg = cured;
              facereg = Fv;
            }
            else
            {
              found = true;
            }
          }
        }
      }
      if (found)
      {
        newedge = cured;
        break;
      }
    }
    if (newedge.IsNull())
    {

      TopoDS_Vertex V1, V2;
      TopExp::Vertices(EHC, V1, V2);
      if (V1.IsSame(V2))
      {
        newedge                              = EHC;
        const double                     w1  = BRep_Tool::Parameter(V1, EHC);
        const double                     w2  = BRep_Tool::Parameter(V2, EHC);
        const ChFiDS_FaceInterference&   fi  = SD->Interference(ons);
        const occ::handle<Geom2d_Curve>& pcf = fi.PCurveOnFace();
        const double                     ww  = fi.Parameter(isfirst);
        const gp_Pnt2d pww = pcf.IsNull() ? SD->Get2dPoints(isfirst, ons) : pcf->Value(ww);
        const gp_Pnt2d p1  = HC->Value(w1);
        const gp_Pnt2d p2  = HC->Value(w2);

        if (p1.Distance(pww) > p2.Distance(pww))
        {
          W    = w1;
          pons = p1;
        }
        else
        {
          W    = w2;
          pons = p2;
        }
        RecP       = true;
        c1obstacle = true;
        return true;
      }
      else if (!edgereg.IsNull())
      {

        Fref = facereg;
        HSref->Initialize(Fref);
        for (TopExp_Explorer ex1(facereg, TopAbs_EDGE); ex1.More() && newedge.IsNull(); ex1.Next())
        {
          const TopoDS_Edge& cured = TopoDS::Edge(ex1.Current());
          if (!cured.IsSame(edgereg))
          {
            for (TopExp_Explorer ex2(cured, TopAbs_VERTEX); ex2.More(); ex2.Next())
            {
              if (ex2.Current().IsSame(VCP))
              {
                if (!IsG1(myEFMap, cured, Fref, Fv))
                {
                  newedge = cured;
                }
              }
            }
          }
        }
      }
    }

    if (newedge.IsNull())
    {
      throw Standard_Failure("StartSol : chain is not possible, new obstacle not found");
    }
    if (IsG1(myEFMap, newedge, Fref, Fv))
    {
      throw Standard_Failure("StartSol : chain is not possible, config non processed");
    }
    else if (Fv.IsNull())
    {
      throw Standard_Failure("StartSol : chain is not possible, new obstacle not found");
    }
    else
    {
      HS->Initialize(Fv);
      W = BRep_Tool::Parameter(VCP, newedge);
      HCref->Initialize(newedge, Fref);
      TopoDS_Face newface = Fv;
      newface.Orientation(TopAbs_FORWARD);
      for (TopExp_Explorer ex(newface, TopAbs_EDGE); ex.More(); ex.Next())
      {
        if (ex.Current().IsSame(newedge))
        {
          newedge = TopoDS::Edge(ex.Current());
          break;
        }
      }
      HC->Initialize(newedge, Fv);
      pons = HC->Value(W);
    }
    RecP       = true;
    c1obstacle = true;
    return true;
  }
  else if (aCommonPoint.IsOnArc() && !HC.IsNull() && !decroch)
  {

    W          = aCommonPoint.ParameterOnArc();
    c1obstacle = true;
    return true;
  }

  HC.Nullify();

  if (aCommonPoint.IsOnArc())
  {
    const TopoDS_Edge& anArcEdge = aCommonPoint.Arc();

    auto prepareDefaultReturn = [&]()
    {
      HS->Initialize(F);
      W       = aCommonPoint.ParameterOnArc();
      aPCurve = getCurveOnSurface(anArcEdge, F);
      pons    = aPCurve->Value(W);
    };

    if (decroch)
    {
      HS->Initialize(Fref);
      W       = aCommonPoint.ParameterOnArc();
      aPCurve = getCurveOnSurface(anArcEdge, Fref);
      pons    = aPCurve->Value(W);
      RecS    = true;
      return true;
    }

    if (SearchFace(Spine, aCommonPoint, F, Fv))
    {
      HS->Initialize(Fv);
      RecS = true;
      if (aCommonPoint.IsVertex())
      {

        TopoDS_Face aux;
        const int   Nb = SearchFaceOnV(aCommonPoint, F, myVEMap, myEFMap, Fv, aux);

        pons = BRep_Tool::Parameters(aCommonPoint.Vertex(), Fv);
        HS->Initialize(Fv);
        if (Nb >= 2)
        {
          HSBis = new BRepAdaptor_Surface(aux);
          PBis  = BRep_Tool::Parameters(aCommonPoint.Vertex(), aux);
        }
        return true;
      }

      if (!Fv.IsSame(F))
      {
        Fv.Orientation(TopAbs_FORWARD);
        TopoDS_Edge newedge;
        for (TopExp_Explorer ex(Fv, TopAbs_EDGE); ex.More(); ex.Next())
        {
          if (ex.Current().IsSame(anArcEdge))
          {
            newedge = TopoDS::Edge(ex.Current());
            break;
          }
        }

        if (isTangentToArc(aCommonPoint, 0.1))
        {
          aPCurve = getCurveOnSurface(aCommonPoint.Arc(), F);
          HSBis   = new BRepAdaptor_Surface(F);
          PBis    = aPCurve->Value(aCommonPoint.ParameterOnArc());
        }

        aPCurve = getCurveOnSurface(newedge, Fv);
      }
      else
      {
        TopoDS_Edge newedge = anArcEdge;
        newedge.Reverse();
        Fv.Orientation(TopAbs_FORWARD);
        aPCurve = getCurveOnSurface(newedge, Fv);
      }
      pons = aPCurve->Value(aCommonPoint.ParameterOnArc());
      return true;
    }
    else if (!Fv.IsNull())
    {
      c1obstacle = true;
      if (!Vref.IsNull())
      {
        for (TopExp_Explorer ex(anArcEdge, TopAbs_VERTEX); ex.More(); ex.Next())
        {
          if (ex.Current().IsSame(Vref))
          {
            c1obstacle = false;
            break;
          }
        }
      }
      if (c1obstacle)
      {
        HS->Initialize(Fv);
        HSref->Initialize(F);
        W  = aCommonPoint.ParameterOnArc();
        HC = new BRepAdaptor_Curve2d();
        TopoDS_Edge newedge;
        TopoDS_Face newface = Fv;
        newface.Orientation(TopAbs_FORWARD);
        for (TopExp_Explorer ex(newface, TopAbs_EDGE); ex.More(); ex.Next())
        {
          if (ex.Current().IsSame(anArcEdge))
          {
            newedge = TopoDS::Edge(ex.Current());
            break;
          }
        }

        if (!newedge.IsNull())
        {
          HC->Initialize(newedge, Fv);
          pons = HC->Value(W);
          HCref->Initialize(anArcEdge, F);
          if (aCommonPoint.IsVertex())
            RecP = true;
          else
            RecRst = true;
          return true;
        }
        else
        {
          prepareDefaultReturn();
          return false;
        }
      }
      else
      {
        prepareDefaultReturn();
        return false;
      }
    }
    else
    {

      prepareDefaultReturn();
      return false;
    }
  }
  else
  {
    HS->Initialize(F);
    const ChFiDS_FaceInterference& FI = SD->Interference(ons);
    if (FI.PCurveOnFace().IsNull())
      pons = SD->Get2dPoints(isfirst, ons);
    else
      pons = FI.PCurveOnFace()->Value(FI.Parameter(isfirst));
  }
  return true;
}

bool ChFi3d_Builder::SearchFace(const occ::handle<ChFiDS_Spine>& Spine,
                                const ChFiDS_CommonPoint&        Pc,
                                const TopoDS_Face&               FRef,
                                TopoDS_Face&                     FVoi) const
{
  bool Trouve = false;
  if (!Pc.IsOnArc())
    return false;
  FVoi.Nullify();
  TopoDS_Edge E;
  if (Pc.IsVertex())
  {

    if (Pc.HasVector())
    {
      TopoDS_Face Fbis;
      int         nb_faces;
      nb_faces = SearchFaceOnV(Pc, FRef, myVEMap, myEFMap, FVoi, Fbis);
      return (nb_faces > 0);
    }
    else
    {
      bool   FindFace = false;
      gp_Pnt Point;
      gp_Vec VecSpine;
      Spine->D1(Pc.Parameter(), Point, VecSpine);

      FindFace = IsInput(VecSpine, Pc.Vertex(), FRef);
      if (FindFace)
      {
        VecSpine.Reverse();
        FindFace = IsInput(VecSpine, Pc.Vertex(), FRef);
      }

      if (FindFace)
      {
        FVoi = FRef;
        return true;
      }

      NCollection_List<TopoDS_Shape>::Iterator ItE, ItF;
      for (ItE.Initialize(myVEMap(Pc.Vertex())); ItE.More() && (!FindFace); ItE.Next())
      {
        E      = TopoDS::Edge(ItE.Value());
        Trouve = false;
        for (ItF.Initialize(myEFMap(E)); ItF.More() && (!Trouve); ItF.Next())
        {
          if (TopoDS::Face(ItF.Value()).IsSame(FRef))
          {
            Trouve = true;
          }
        }
        if (Trouve)
          FindFace = IsG1(myEFMap, E, FRef, FVoi);
        if (FindFace)
        {
          FindFace = false;
          if (Spine.IsNull())
          {

            return false;
          }

          Trouve = false;
          for (int IE = 1; (IE <= Spine->NbEdges()) && (!Trouve); IE++)
          {
            E = Spine->Edges(IE);
            if ((TopExp::FirstVertex(E).IsSame(Pc.Vertex()))
                || (TopExp::LastVertex(E).IsSame(Pc.Vertex())))
            {
              for (ItF.Initialize(myEFMap(E)), Trouve = false; ItF.More() && (!Trouve); ItF.Next())
              {
                if (TopoDS::Face(ItF.Value()).IsSame(FVoi))
                {
                  Trouve = true;
                }
              }
            }
          }
          FindFace = Trouve;
        }
      }
    }
  }
  else
  {
    return IsG1(myEFMap, Pc.Arc(), FRef, FVoi);
  }
  return false;
}

static void ChFi3d_SingularExtremity(occ::handle<ChFiDS_Stripe>& stripe,
                                     TopOpeBRepDS_DataStructure& DStr,
                                     const TopoDS_Vertex&        Vtx,
                                     const double                tol3d,
                                     const double                tol2d)
{
  occ::handle<ChFiDS_SurfData> Fd;
  double                       tolreached;
  double                       Pardeb, Parfin;
  gp_Pnt2d                     VOnS1, VOnS2;
  occ::handle<Geom_Curve>      C3d;
  occ::handle<Geom2d_Curve>    PCurv;
  TopOpeBRepDS_Curve           Crv;

  int  Ivtx, Icurv;
  bool isfirst;

  if (stripe->Spine()->IsPeriodic())
  {
    isfirst = true;
    Fd      = stripe->SetOfSurfData()->Sequence().First();
  }
  else
  {
    int sens;
    int num = ChFi3d_IndexOfSurfData(Vtx, stripe, sens);
    Fd      = stripe->SetOfSurfData()->Sequence().Value(num);
    isfirst = (sens == 1);
  }

  const ChFiDS_CommonPoint& CV1 = Fd->Vertex(isfirst, 1);
  const ChFiDS_CommonPoint& CV2 = Fd->Vertex(isfirst, 2);

  if (CV1.Point().IsEqual(CV2.Point(), 0))
  {
    Ivtx = ChFi3d_IndexPointInDS(CV1, DStr);
    if (isfirst)
    {
      VOnS1 = Fd->InterferenceOnS1().PCurveOnSurf()->Value(Fd->InterferenceOnS1().FirstParameter());
      VOnS2 = Fd->InterferenceOnS2().PCurveOnSurf()->Value(Fd->InterferenceOnS2().FirstParameter());
    }
    else
    {
      VOnS1 = Fd->InterferenceOnS1().PCurveOnSurf()->Value(Fd->InterferenceOnS1().LastParameter());
      VOnS2 = Fd->InterferenceOnS2().PCurveOnSurf()->Value(Fd->InterferenceOnS2().LastParameter());
    }

    ChFi3d_ComputeArete(CV1,
                        VOnS1,
                        CV2,
                        VOnS2,
                        DStr.Surface(Fd->Surf()).Surface(),
                        C3d,
                        PCurv,
                        Pardeb,
                        Parfin,
                        tol3d,
                        tol2d,
                        tolreached,
                        0);
    Crv   = TopOpeBRepDS_Curve(C3d, tolreached);
    Icurv = DStr.AddCurve(Crv);

    stripe->SetCurve(Icurv, isfirst);
    stripe->SetParameters(isfirst, Pardeb, Parfin);
    stripe->ChangePCurve(isfirst) = PCurv;
    stripe->SetIndexPoint(Ivtx, isfirst, 1);
    stripe->SetIndexPoint(Ivtx, isfirst, 2);

    if (stripe->Spine()->IsPeriodic())
    {

      isfirst = false;
      Fd      = stripe->SetOfSurfData()->Sequence().Last();
      VOnS1 = Fd->InterferenceOnS1().PCurveOnSurf()->Value(Fd->InterferenceOnS1().LastParameter());
      VOnS2 = Fd->InterferenceOnS2().PCurveOnSurf()->Value(Fd->InterferenceOnS2().LastParameter());

      ChFi3d_ComputeArete(CV1,
                          VOnS1,
                          CV2,
                          VOnS2,
                          DStr.Surface(Fd->Surf()).Surface(),
                          C3d,
                          PCurv,
                          Pardeb,
                          Parfin,
                          tol3d,
                          tol2d,
                          tolreached,
                          0);
      Crv   = TopOpeBRepDS_Curve(C3d, tolreached);
      Icurv = DStr.AddCurve(Crv);

      stripe->SetCurve(Icurv, isfirst);
      stripe->SetParameters(isfirst, Pardeb, Parfin);
      stripe->ChangePCurve(isfirst) = PCurv;
      stripe->SetIndexPoint(Ivtx, isfirst, 1);
      stripe->SetIndexPoint(Ivtx, isfirst, 2);
    }
  }
}

static bool IsFree(const TopoDS_Shape& E, const ChFiDS_Map& EFMap)
{
  if (!EFMap.Contains(E))
    return false;
  NCollection_List<TopoDS_Shape>::Iterator It;
  TopoDS_Shape                             Fref;
  for (It.Initialize(EFMap(E)); It.More(); It.Next())
  {
    if (Fref.IsNull())
      Fref = It.Value();
    else if (!Fref.IsSame(It.Value()))
      return false;
  }
  return true;
}

static void ChFi3d_MakeExtremities(occ::handle<ChFiDS_Stripe>& Stripe,
                                   TopOpeBRepDS_DataStructure& DStr,
                                   const ChFiDS_Map&           EFMap,
                                   const double                tol3d,
                                   const double                tol2d)
{
  occ::handle<ChFiDS_Spine>& sp = Stripe->ChangeSpine();
  double                     Pardeb, Parfin;
  occ::handle<Geom_Curve>    C3d;
  double                     tolreached;
  if (sp->IsPeriodic())
  {
    Bnd_Box                             b1, b2;
    const occ::handle<ChFiDS_SurfData>& SDF = Stripe->SetOfSurfData()->Sequence().First();
    const ChFiDS_CommonPoint&           CV1 = SDF->VertexFirstOnS1();
    const ChFiDS_CommonPoint&           CV2 = SDF->VertexFirstOnS2();
    if (!CV1.Point().IsEqual(CV2.Point(), 0))
    {
      ChFi3d_ComputeArete(
        CV1,
        SDF->InterferenceOnS1().PCurveOnSurf()->Value(SDF->InterferenceOnS1().FirstParameter()),
        CV2,
        SDF->InterferenceOnS2().PCurveOnSurf()->Value(SDF->InterferenceOnS2().FirstParameter()),
        DStr.Surface(SDF->Surf()).Surface(),
        C3d,
        Stripe->ChangeFirstPCurve(),
        Pardeb,
        Parfin,
        tol3d,
        tol2d,
        tolreached,
        0);
      TopOpeBRepDS_Curve Crv(C3d, tolreached);
      Stripe->ChangeFirstCurve(DStr.AddCurve(Crv));
      Stripe->ChangeFirstParameters(Pardeb, Parfin);
      Stripe->ChangeIndexFirstPointOnS1(ChFi3d_IndexPointInDS(SDF->VertexFirstOnS1(), DStr));
      Stripe->ChangeIndexFirstPointOnS2(ChFi3d_IndexPointInDS(SDF->VertexFirstOnS2(), DStr));
      int ICurv = Stripe->FirstCurve();
      Stripe->ChangeLastParameters(Pardeb, Parfin);
      Stripe->ChangeLastCurve(ICurv);
      Stripe->ChangeIndexLastPointOnS1(Stripe->IndexFirstPointOnS1());
      Stripe->ChangeIndexLastPointOnS2(Stripe->IndexFirstPointOnS2());

      const occ::handle<ChFiDS_SurfData>& SDL = Stripe->SetOfSurfData()->Sequence().Last();

      ChFi3d_ComputePCurv(
        C3d,
        SDL->InterferenceOnS1().PCurveOnSurf()->Value(SDL->InterferenceOnS1().LastParameter()),
        SDL->InterferenceOnS2().PCurveOnSurf()->Value(SDL->InterferenceOnS2().LastParameter()),
        Stripe->ChangeLastPCurve(),
        DStr.Surface(SDL->Surf()).Surface(),
        Pardeb,
        Parfin,
        tol3d,
        tolreached);
      double oldtol = DStr.ChangeCurve(ICurv).Tolerance();
      DStr.ChangeCurve(ICurv).Tolerance(std::max(oldtol, tolreached));
      if (CV1.IsOnArc())
      {
        ChFi3d_EnlargeBox(CV1.Arc(), EFMap(CV1.Arc()), CV1.ParameterOnArc(), b1);
      }

      if (CV2.IsOnArc())
      {
        ChFi3d_EnlargeBox(CV2.Arc(), EFMap(CV2.Arc()), CV2.ParameterOnArc(), b2);
      }
      ChFi3d_EnlargeBox(DStr, Stripe, SDF, b1, b2, true);
      ChFi3d_EnlargeBox(DStr, Stripe, SDL, b1, b2, false);
      if (!CV1.IsVertex())
        ChFi3d_SetPointTolerance(DStr, b1, Stripe->IndexFirstPointOnS1());
      if (!CV2.IsVertex())
        ChFi3d_SetPointTolerance(DStr, b2, Stripe->IndexFirstPointOnS2());
    }
    else
    {

      if (CV1.IsVertex())
      {
        ChFi3d_SingularExtremity(Stripe, DStr, CV1.Vertex(), tol3d, tol2d);
      }
#ifdef CHFI3D_DEB
      else
      {
        std::cout << "MakeExtremities : Singularity out of Vertex !!" << std::endl;
      }
#endif
    }
    return;
  }

  const occ::handle<ChFiDS_SurfData>& SDdeb = Stripe->SetOfSurfData()->Sequence().First();

  const ChFiDS_CommonPoint& cpdeb1  = SDdeb->VertexFirstOnS1();
  const ChFiDS_CommonPoint& cpdeb2  = SDdeb->VertexFirstOnS2();
  bool                      freedeb = sp->FirstStatus() == ChFiDS_FreeBoundary;
  if (!freedeb && cpdeb1.IsOnArc() && cpdeb2.IsOnArc())
  {
    freedeb = (IsFree(cpdeb1.Arc(), EFMap) && IsFree(cpdeb2.Arc(), EFMap));
  }
  if (freedeb)
  {
    sp->SetFirstStatus(ChFiDS_FreeBoundary);
    Bnd_Box b1, b2;
    if (!cpdeb1.Point().IsEqual(cpdeb2.Point(), 0))
    {
      bool     plane;
      gp_Pnt2d UV1, UV2;
      UV1 =
        SDdeb->InterferenceOnS1().PCurveOnSurf()->Value(SDdeb->InterferenceOnS1().FirstParameter());
      UV2 =
        SDdeb->InterferenceOnS2().PCurveOnSurf()->Value(SDdeb->InterferenceOnS2().FirstParameter());

      occ::handle<GeomAdaptor_Surface> HConge = ChFi3d_BoundSurf(DStr, SDdeb, 1, 2);
      ChFi3d_CoupeParPlan(cpdeb1,
                          cpdeb2,
                          HConge,
                          UV1,
                          UV2,
                          tol3d,
                          tol2d,
                          C3d,
                          Stripe->ChangeFirstPCurve(),
                          tolreached,
                          Pardeb,
                          Parfin,
                          plane);
      if (!plane)
        ChFi3d_ComputeArete(cpdeb1,
                            SDdeb->InterferenceOnS1().PCurveOnSurf()->Value(
                              SDdeb->InterferenceOnS1().FirstParameter()),
                            cpdeb2,
                            SDdeb->InterferenceOnS2().PCurveOnSurf()->Value(
                              SDdeb->InterferenceOnS2().FirstParameter()),
                            DStr.Surface(SDdeb->Surf()).Surface(),
                            C3d,
                            Stripe->ChangeFirstPCurve(),
                            Pardeb,
                            Parfin,
                            tol3d,
                            tol2d,
                            tolreached,
                            0);
      TopOpeBRepDS_Curve Crv(C3d, tolreached);
      Stripe->ChangeFirstCurve(DStr.AddCurve(Crv));
      Stripe->ChangeFirstParameters(Pardeb, Parfin);
      Stripe->ChangeIndexFirstPointOnS1(ChFi3d_IndexPointInDS(SDdeb->VertexFirstOnS1(), DStr));
      Stripe->ChangeIndexFirstPointOnS2(ChFi3d_IndexPointInDS(SDdeb->VertexFirstOnS2(), DStr));
      if (cpdeb1.IsOnArc())
      {
        ChFi3d_EnlargeBox(cpdeb1.Arc(), EFMap(cpdeb1.Arc()), cpdeb1.ParameterOnArc(), b1);
      }
      if (cpdeb2.IsOnArc())
      {
        ChFi3d_EnlargeBox(cpdeb2.Arc(), EFMap(cpdeb2.Arc()), cpdeb2.ParameterOnArc(), b2);
      }
      ChFi3d_EnlargeBox(DStr, Stripe, SDdeb, b1, b2, true);
      if (!cpdeb1.IsVertex())
        ChFi3d_SetPointTolerance(DStr, b1, Stripe->IndexFirstPointOnS1());
      if (!cpdeb2.IsVertex())
        ChFi3d_SetPointTolerance(DStr, b2, Stripe->IndexFirstPointOnS2());
    }
    else
    {
      if (cpdeb1.IsVertex())
      {
        ChFi3d_SingularExtremity(Stripe, DStr, cpdeb1.Vertex(), tol3d, tol2d);
      }
#ifdef CHFI3D_DEB
      else
      {
        std::cout << "MakeExtremities : Singularity out of Vertex !!" << std::endl;
      }
#endif
    }
  }
  const occ::handle<ChFiDS_SurfData>& SDfin   = Stripe->SetOfSurfData()->Sequence().Last();
  const ChFiDS_CommonPoint&           cpfin1  = SDfin->VertexLastOnS1();
  const ChFiDS_CommonPoint&           cpfin2  = SDfin->VertexLastOnS2();
  bool                                freefin = sp->LastStatus() == ChFiDS_FreeBoundary;
  if (!freefin && cpfin1.IsOnArc() && cpfin2.IsOnArc())
  {
    freefin = (IsFree(cpfin1.Arc(), EFMap) && IsFree(cpfin2.Arc(), EFMap));
  }
  if (freefin)
  {
    sp->SetLastStatus(ChFiDS_FreeBoundary);
    Bnd_Box b1, b2;
    if (!cpfin1.Point().IsEqual(cpfin2.Point(), 0))
    {
      bool     plane;
      gp_Pnt2d UV1, UV2;
      UV1 =
        SDfin->InterferenceOnS1().PCurveOnSurf()->Value(SDfin->InterferenceOnS1().LastParameter());
      UV2 =
        SDfin->InterferenceOnS2().PCurveOnSurf()->Value(SDfin->InterferenceOnS2().LastParameter());

      occ::handle<GeomAdaptor_Surface> HConge = ChFi3d_BoundSurf(DStr, SDfin, 1, 2);
      ChFi3d_CoupeParPlan(cpfin1,
                          cpfin2,
                          HConge,
                          UV1,
                          UV2,
                          tol3d,
                          tol2d,
                          C3d,
                          Stripe->ChangeLastPCurve(),
                          tolreached,
                          Pardeb,
                          Parfin,
                          plane);
      if (!plane)
        ChFi3d_ComputeArete(cpfin1,
                            SDfin->InterferenceOnS1().PCurveOnSurf()->Value(
                              SDfin->InterferenceOnS1().LastParameter()),
                            cpfin2,
                            SDfin->InterferenceOnS2().PCurveOnSurf()->Value(
                              SDfin->InterferenceOnS2().LastParameter()),
                            DStr.Surface(SDfin->Surf()).Surface(),
                            C3d,
                            Stripe->ChangeLastPCurve(),
                            Pardeb,
                            Parfin,
                            tol3d,
                            tol2d,
                            tolreached,
                            0);
      TopOpeBRepDS_Curve Crv(C3d, tolreached);
      Stripe->ChangeLastCurve(DStr.AddCurve(Crv));
      Stripe->ChangeLastParameters(Pardeb, Parfin);
      Stripe->ChangeIndexLastPointOnS1(ChFi3d_IndexPointInDS(SDfin->VertexLastOnS1(), DStr));
      Stripe->ChangeIndexLastPointOnS2(ChFi3d_IndexPointInDS(SDfin->VertexLastOnS2(), DStr));
      if (cpfin1.IsOnArc())
      {
        ChFi3d_EnlargeBox(cpfin1.Arc(), EFMap(cpfin1.Arc()), cpfin1.ParameterOnArc(), b1);
      }
      if (cpfin2.IsOnArc())
      {
        ChFi3d_EnlargeBox(cpfin2.Arc(), EFMap(cpfin2.Arc()), cpfin2.ParameterOnArc(), b2);
      }
      ChFi3d_EnlargeBox(DStr, Stripe, SDfin, b1, b2, false);
      if (!cpfin1.IsVertex())
        ChFi3d_SetPointTolerance(DStr, b1, Stripe->IndexLastPointOnS1());
      if (!cpfin2.IsVertex())
        ChFi3d_SetPointTolerance(DStr, b2, Stripe->IndexLastPointOnS2());
    }
    else
    {
      if (cpfin1.IsVertex())
      {
        ChFi3d_SingularExtremity(Stripe, DStr, cpfin1.Vertex(), tol3d, tol2d);
      }
#ifdef CHFI3D_DEB
      else
      {
        std::cout << "MakeExtremities : Singularity out of Vertex !!" << std::endl;
      }
#endif
    }
  }
}

static void ChFi3d_Purge(occ::handle<ChFiDS_Stripe>&   Stripe,
                         occ::handle<ChFiDS_SurfData>& SD,
                         const ChFiDS_CommonPoint&     VRef,
                         const bool                    isfirst,
                         const int                     ons,
                         int&                          intf,
                         int&                          intl)
{
  if (isfirst)
    intf = 1;
  else
    intl = 1;
  int opp = 3 - ons;
  if (!SD->Vertex(isfirst, opp).IsOnArc() || SD->TwistOnS1() || SD->TwistOnS2())
  {
    NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Seq =
      Stripe->ChangeSetOfSurfData()->ChangeSequence();
    if (isfirst)
      Seq.Remove(1);
    else
      Seq.Remove(Seq.Length());
    return;
  }
  if (ons == 1)
    SD->ChangeIndexOfS1(0);
  else
    SD->ChangeIndexOfS2(0);

  SD->ChangeVertex(!isfirst, ons) = VRef;
  SD->ChangeVertex(isfirst, ons)  = VRef;

  ChFiDS_FaceInterference& fi = SD->ChangeInterference(ons);
  if (isfirst)
    fi.SetFirstParameter(fi.LastParameter());
  else
    fi.SetLastParameter(fi.FirstParameter());
  fi.SetLineIndex(0);
}

static void InsertAfter(occ::handle<ChFiDS_Stripe>&   Stripe,
                        occ::handle<ChFiDS_SurfData>& Ref,
                        occ::handle<ChFiDS_SurfData>& Item)
{
  if (Ref == Item)
    throw Standard_Failure("InsertAfter : twice the same surfdata.");

  NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Seq =
    Stripe->ChangeSetOfSurfData()->ChangeSequence();

  if (Seq.IsEmpty() || Ref.IsNull())
  {
    Seq.Prepend(Item);
  }
  for (int i = 1; i <= Seq.Length(); i++)
  {
    if (Seq.Value(i) == Ref)
    {
      Seq.InsertAfter(i, Item);
      break;
    }
  }
}

static void RemoveSD(occ::handle<ChFiDS_Stripe>&   Stripe,
                     occ::handle<ChFiDS_SurfData>& Prev,
                     occ::handle<ChFiDS_SurfData>& Next)
{
  NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Seq =
    Stripe->ChangeSetOfSurfData()->ChangeSequence();
  if (Seq.IsEmpty())
    return;
  int iprev = 0, inext = 0;
  for (int i = 1; i <= Seq.Length(); i++)
  {
    if (Seq.Value(i) == Prev)
      iprev = i + 1;
    if (Seq.Value(i) == Next)
    {
      inext = i - 1;
      break;
    }
  }
  if (Prev.IsNull())
    iprev = 1;
  if (Next.IsNull())
    inext = Seq.Length();
  if (iprev <= inext)
    Seq.Remove(iprev, inext);
}

static void InsertBefore(occ::handle<ChFiDS_Stripe>&   Stripe,
                         occ::handle<ChFiDS_SurfData>& Ref,
                         occ::handle<ChFiDS_SurfData>& Item)
{
  if (Ref == Item)
    throw Standard_Failure("InsertBefore : twice the same surfdata.");

  NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Seq =
    Stripe->ChangeSetOfSurfData()->ChangeSequence();

  if (Seq.IsEmpty() || Ref.IsNull())
  {
    Seq.Append(Item);
  }
  for (int i = 1; i <= Seq.Length(); i++)
  {
    if (Seq.Value(i) == Ref)
    {
      Seq.InsertBefore(i, Item);
      break;
    }
  }
}

void ChFi3d_Builder::PerformSetOfSurfOnElSpine(const occ::handle<ChFiDS_ElSpine>&     HGuide,
                                               occ::handle<ChFiDS_Stripe>&            Stripe,
                                               occ::handle<BRepTopAdaptor_TopolTool>& It1,
                                               occ::handle<BRepTopAdaptor_TopolTool>& It2,
                                               const bool                             Simul)
{
  ChFiDS_ElSpine& Guide = *HGuide;

  occ::handle<ChFiDS_ElSpine> OffsetHGuide;
  occ::handle<ChFiDS_Spine>&  Spine = Stripe->ChangeSpine();
  if (Spine->Mode() == ChFiDS_ConstThroatWithPenetrationChamfer)
  {
    NCollection_List<occ::handle<ChFiDS_ElSpine>>& ll        = Spine->ChangeElSpines();
    NCollection_List<occ::handle<ChFiDS_ElSpine>>& ll_offset = Spine->ChangeOffsetElSpines();
    NCollection_List<occ::handle<ChFiDS_ElSpine>>::Iterator ILES(ll), ILES_offset(ll_offset);
    for (; ILES.More(); ILES.Next(), ILES_offset.Next())
    {
      const occ::handle<ChFiDS_ElSpine>& aHElSpine = ILES.Value();
      if (aHElSpine == HGuide)
        OffsetHGuide = ILES_offset.Value();
    }
  }

  double wf        = Guide.FirstParameter();
  double wl        = Guide.LastParameter();
  double locfleche = (wl - wf) * fleche;
  double wfsav = wf, wlsav = wl;
  if (!Guide.IsPeriodic())
  {

    double prab = 0.01;
    Guide.FirstParameter(wf - prab * (wl - wf));
    Guide.LastParameter(wl + prab * (wl - wf));
    if (!OffsetHGuide.IsNull())
    {
      OffsetHGuide->FirstParameter(wf - prab * (wl - wf));
      OffsetHGuide->LastParameter(wl + prab * (wl - wf));
    }
  }

  int    ii, nbed = Spine->NbEdges();
  double lastedlastp = Spine->LastParameter(nbed);

  TopOpeBRepDS_DataStructure& DStr = myDS->ChangeDS();

  occ::handle<ChFiDS_SurfData> ref = Guide.Previous();
  occ::handle<ChFiDS_SurfData> refbis, SD;
  occ::handle<ChFiDS_SurfData> raf = Guide.Next();
  RemoveSD(Stripe, ref, raf);

  occ::handle<BRepAdaptor_Surface> HS1 = new BRepAdaptor_Surface();
  occ::handle<BRepAdaptor_Surface> HS2 = new BRepAdaptor_Surface();
  occ::handle<BRepAdaptor_Surface> HS3, HS4;
  occ::handle<BRepAdaptor_Surface> HSref1 = new BRepAdaptor_Surface();
  occ::handle<BRepAdaptor_Surface> HSref2 = new BRepAdaptor_Surface();
  occ::handle<BRepAdaptor_Curve2d> HC1, HC2;
  occ::handle<BRepAdaptor_Curve2d> HCref1   = new BRepAdaptor_Curve2d();
  occ::handle<BRepAdaptor_Curve2d> HCref2   = new BRepAdaptor_Curve2d();
  bool                             decroch1 = false, decroch2 = false;
  bool        RecP1 = false, RecS1 = false, RecRst1 = false, obstacleon1 = false;
  bool        RecP2 = false, RecS2 = false, RecRst2 = false, obstacleon2 = false;
  gp_Pnt2d    pp1, pp2, pp3, pp4;
  double      w1 = 0., w2 = 0.;
  math_Vector Soldep(1, 4);
  math_Vector SoldepCS(1, 3);
  math_Vector SoldepCC(1, 2);

  bool   forward = true;
  bool   Inside  = false;
  double First   = wf;
  double Last    = wl;
  bool   Ok1 = true, Ok2 = true;

  TopoDS_Vertex Vref;
  if (ref.IsNull() && raf.IsNull())
  {

    Inside = true;

    StartSol(Stripe, HGuide, HS1, HS2, It1, It2, pp1, pp2, First);

    Last = wf;
    if (Guide.IsPeriodic())
    {
      Last = First - Guide.Period();
      Guide.SaveFirstParameter();
      Guide.FirstParameter(Last);
      Guide.SaveLastParameter();
      Guide.LastParameter(First * 1.1);
      if (!OffsetHGuide.IsNull())
      {
        OffsetHGuide->SaveFirstParameter();
        OffsetHGuide->FirstParameter(Last);
        OffsetHGuide->SaveLastParameter();
        OffsetHGuide->LastParameter(First * 1.1);
      }
    }
  }
  else
  {
    if (!Spine->IsPeriodic() && (wl - lastedlastp > -tolesp))
    {
      Vref = Spine->LastVertex();
    }
    if (ref.IsNull())
    {
      if (!Spine->IsPeriodic() && (wf < tolesp))
      {
        Vref = Spine->FirstVertex();
      }
      ref     = raf;
      forward = false;
      First   = wl;
      Last    = Guide.FirstParameter();
    }

    Ok1 = StartSol(Spine,
                   HS1,
                   pp1,
                   HC1,
                   w1,
                   ref,
                   !forward,
                   1,
                   HSref1,
                   HCref1,
                   RecP1,
                   RecS1,
                   RecRst1,
                   obstacleon1,
                   HS3,
                   pp3,
                   decroch1,
                   Vref);
    Ok2 = StartSol(Spine,
                   HS2,
                   pp2,
                   HC2,
                   w2,
                   ref,
                   !forward,
                   2,
                   HSref2,
                   HCref2,
                   RecP2,
                   RecS2,
                   RecRst2,
                   obstacleon2,
                   HS4,
                   pp4,
                   decroch2,
                   Vref);
    HC1.Nullify();
    HC2.Nullify();

    if (Ok1 == 1 && Ok2 == 1)
    {
      if (forward)
      {
        Guide.FirstParameter(wf);
        if (!OffsetHGuide.IsNull())
          OffsetHGuide->FirstParameter(wf);
      }
      else
      {
        Guide.LastParameter(wl);
        if (!OffsetHGuide.IsNull())
          OffsetHGuide->LastParameter(wl);
      }
    }
  }
  bool fini     = false;
  bool complete = Inside;
  if (!Guide.IsPeriodic())
  {
    int indf = Spine->Index(wf);
    int indl = Spine->Index(wl, false);
    if (Spine->IsPeriodic() && (indl < indf))
      indl += nbed;
    nbed = indl - indf + 1;
  }

  double bidf = wf, bidl = wl;
  if (!Spine->IsPeriodic())
  {
    bidf = std::max(0., wf);
    bidl = std::min(wl, Spine->LastParameter(Spine->NbEdges()));

    if ((bidl - bidf) < 0.01 * Spine->LastParameter(Spine->NbEdges()))
    {
      bidf = wf;
      bidl = wl;
    }
  }
  double MaxStep  = (bidl - bidf) * 0.05 / nbed;
  double Firstsov = 0.;
  int    intf = 0, intl = 0;
  while (!fini)
  {

    Ok1 = true, Ok2 = true;
    if (!Spine->IsPeriodic())
    {
      if (wf < tolesp && (complete == Inside))
      {
        if (Spine->FirstStatus() == ChFiDS_OnSame)
          intf = 2;
        else
          intf = 1;
      }
      if (Spine->IsTangencyExtremity(true))
      {
        intf = 4;
        Guide.FirstParameter(wfsav);
        if (!OffsetHGuide.IsNull())
          OffsetHGuide->FirstParameter(wfsav);
      }
      if (wl - lastedlastp > -tolesp)
      {
        if (Spine->LastStatus() == ChFiDS_OnSame)
          intl = 2;
        else
          intl = 1;
      }
      if (Spine->IsTangencyExtremity(false))
      {
        intl = 4;
        Guide.LastParameter(wlsav);
        if (!OffsetHGuide.IsNull())
          OffsetHGuide->LastParameter(wlsav);
      }
    }
    if (intf && !forward)
      Vref = Spine->FirstVertex();
    if (intl && forward)
      Vref = Spine->LastVertex();
    if (!ref.IsNull())
    {
      Ok1 = StartSol(Spine,
                     HS1,
                     pp1,
                     HC1,
                     w1,
                     ref,
                     !forward,
                     1,
                     HSref1,
                     HCref1,
                     RecP1,
                     RecS1,
                     RecRst1,
                     obstacleon1,
                     HS3,
                     pp3,
                     decroch1,
                     Vref);
      Ok2 = StartSol(Spine,
                     HS2,
                     pp2,
                     HC2,
                     w2,
                     ref,
                     !forward,
                     2,
                     HSref2,
                     HCref2,
                     RecP2,
                     RecS2,
                     RecRst2,
                     obstacleon2,
                     HS4,
                     pp4,
                     decroch2,
                     Vref);
    }

    if ((!Ok1 && HC1.IsNull()) || (!Ok2 && HC2.IsNull()))
    {
      if ((intf && !forward) || (intl && forward))
      {
        if (!Ok1)
          ChFi3d_BuildPlane(DStr, HS1, pp1, ref, !forward, 1);
        if (!Ok2)
          ChFi3d_BuildPlane(DStr, HS2, pp2, ref, !forward, 2);
        if (intf)
          intf = 5;
        else if (intl)
          intl = 5;
        if (forward)
        {
          Guide.FirstParameter(wf);
          if (!OffsetHGuide.IsNull())
            OffsetHGuide->FirstParameter(wf);
        }
        else
        {
          Guide.LastParameter(wl);
          if (!OffsetHGuide.IsNull())
            OffsetHGuide->LastParameter(wl);
        }
      }
      else
        throw Standard_Failure("PerformSetOfSurfOnElSpine : Chaining is impossible.");
    }

    const occ::handle<Adaptor3d_Surface>& HSon1 = HS1;
    const occ::handle<Adaptor3d_Surface>& HSon2 = HS2;
    It1->Initialize(HSon1);
    It2->Initialize(HSon2);

    SD = new ChFiDS_SurfData();
    NCollection_Sequence<occ::handle<ChFiDS_SurfData>> SeqSD;
    SeqSD.Append(SD);

    if (obstacleon1 && obstacleon2)
    {
      TopAbs_Orientation Or1   = HSref1->Face().Orientation();
      TopAbs_Orientation Or2   = HSref2->Face().Orientation();
      int                Choix = ChFi3d::NextSide(Or1,
                                   Or2,
                                   Stripe->OrientationOnFace1(),
                                   Stripe->OrientationOnFace2(),
                                   Stripe->Choix());

      if (Choix % 2 == 0)
        Choix = 4;
      else
        Choix = 1;

      SoldepCC(1) = w1;
      SoldepCC(2) = w2;
      if (Simul)
      {
        SimulSurf(SD,
                  HGuide,
                  Spine,
                  Choix,
                  HS1,
                  It1,
                  HC1,
                  HSref1,
                  HCref1,
                  decroch1,
                  Or1,
                  HS2,
                  It2,
                  HC2,
                  HSref2,
                  HCref2,
                  decroch2,
                  Or2,
                  locfleche,
                  tolesp,
                  First,
                  Last,
                  Inside,
                  Inside,
                  forward,
                  RecP1,
                  RecRst1,
                  RecP2,
                  RecRst2,
                  SoldepCC);
      }
      else
      {
        PerformSurf(SeqSD,
                    HGuide,
                    Spine,
                    Choix,
                    HS1,
                    It1,
                    HC1,
                    HSref1,
                    HCref1,
                    decroch1,
                    Or1,
                    HS2,
                    It2,
                    HC2,
                    HSref2,
                    HCref2,
                    decroch2,
                    Or2,
                    MaxStep,
                    locfleche,
                    tolesp,
                    First,
                    Last,
                    Inside,
                    Inside,
                    forward,
                    RecP1,
                    RecRst1,
                    RecP2,
                    RecRst2,
                    SoldepCC);
      }
      SD->ChangeIndexOfS1(DStr.AddShape(HS1->Face()));
      SD->ChangeIndexOfS2(DStr.AddShape(HS2->Face()));
    }
    else if (obstacleon1)
    {
      TopAbs_Orientation Or1   = HSref1->Face().Orientation();
      TopAbs_Orientation Or2   = HS2->Face().Orientation();
      int                Choix = ChFi3d::NextSide(Or1,
                                   Or2,
                                   Stripe->OrientationOnFace1(),
                                   Stripe->OrientationOnFace2(),
                                   -Stripe->Choix());
      if (Choix % 2 == 1)
        Choix++;
      else
        Choix--;
      SoldepCS(3) = w1;
      SoldepCS(1) = pp2.X();
      SoldepCS(2) = pp2.Y();
      if (Simul)
      {
        SimulSurf(SD,
                  HGuide,
                  Spine,
                  Choix,
                  HS1,
                  It1,
                  HC1,
                  HSref1,
                  HCref1,
                  decroch1,
                  HS2,
                  It2,
                  Or2,
                  locfleche,
                  tolesp,
                  First,
                  Last,
                  Inside,
                  Inside,
                  forward,
                  RecP1,
                  RecS2,
                  RecRst1,
                  SoldepCS);
      }
      else
      {
        PerformSurf(SeqSD,
                    HGuide,
                    Spine,
                    Choix,
                    HS1,
                    It1,
                    HC1,
                    HSref1,
                    HCref1,
                    decroch1,
                    HS2,
                    It2,
                    Or2,
                    MaxStep,
                    locfleche,
                    tolesp,
                    First,
                    Last,
                    Inside,
                    Inside,
                    forward,
                    RecP1,
                    RecS2,
                    RecRst1,
                    SoldepCS);
      }
      SD->ChangeIndexOfS1(DStr.AddShape(HS1->Face()));
      SD->ChangeIndexOfS2(DStr.AddShape(HS2->Face()));
      decroch2 = false;
    }
    else if (obstacleon2)
    {
      TopAbs_Orientation Or1   = HS1->Face().Orientation();
      TopAbs_Orientation Or2   = HSref2->Face().Orientation();
      int                Choix = ChFi3d::NextSide(Or1,
                                   Or2,
                                   Stripe->OrientationOnFace1(),
                                   Stripe->OrientationOnFace2(),
                                   Stripe->Choix());
      SoldepCS(3)              = w2;
      SoldepCS(1)              = pp1.X();
      SoldepCS(2)              = pp1.Y();
      if (Simul)
      {
        SimulSurf(SD,
                  HGuide,
                  Spine,
                  Choix,
                  HS1,
                  It1,
                  Or1,
                  HS2,
                  It2,
                  HC2,
                  HSref2,
                  HCref2,
                  decroch2,
                  locfleche,
                  tolesp,
                  First,
                  Last,
                  Inside,
                  Inside,
                  forward,
                  RecP2,
                  RecS1,
                  RecRst2,
                  SoldepCS);
      }
      else
      {
        PerformSurf(SeqSD,
                    HGuide,
                    Spine,
                    Choix,
                    HS1,
                    It1,
                    Or1,
                    HS2,
                    It2,
                    HC2,
                    HSref2,
                    HCref2,
                    decroch2,
                    MaxStep,
                    locfleche,
                    tolesp,
                    First,
                    Last,
                    Inside,
                    Inside,
                    forward,
                    RecP2,
                    RecS1,
                    RecRst2,
                    SoldepCS);
      }
      SD->ChangeIndexOfS1(DStr.AddShape(HS1->Face()));
      SD->ChangeIndexOfS2(DStr.AddShape(HS2->Face()));
      decroch1 = false;
    }
    else
    {
      const occ::handle<Adaptor3d_TopolTool>& aTT1 = It1;
      const occ::handle<Adaptor3d_TopolTool>& aTT2 = It2;
      CallPerformSurf(Stripe,
                      Simul,
                      SeqSD,
                      SD,
                      HGuide,
                      Spine,
                      HS1,
                      HS3,
                      pp1,
                      pp3,
                      aTT1,
                      HS2,
                      HS4,
                      pp2,
                      pp4,
                      aTT2,
                      MaxStep,
                      locfleche,
                      tolesp,
                      First,
                      Last,
                      Inside,
                      Inside,
                      forward,
                      RecS1,
                      RecS2,
                      Soldep,
                      intf,
                      intl,
                      HS1,
                      HS2);
      decroch1 = decroch2 = false;
    }

    if (!done)
    {
      if ((!Ok1 && !obstacleon1) || (!Ok2 && !obstacleon2))
      {

        done   = true;
        Inside = false;
        if (forward)
          intl = 1;
        else
          intf = 1;
      }
      else
      {
        Spine->SetErrorStatus(ChFiDS_WalkingFailure);
        throw Standard_Failure("CallPerformSurf : Path failed!");
      }
    }

    else
    {
      refbis = ref;
      if (forward)
      {
        for (ii = 1; ii <= SeqSD.Length(); ii++)
        {
          SD = SeqSD(ii);
          SD->ChangeIndexOfS1(DStr.AddShape(HS1->Face()));
          if (obstacleon1)
            SD->SetIndexOfC1(DStr.AddShape(HC1->Edge()));
          SD->ChangeIndexOfS2(DStr.AddShape(HS2->Face()));
          if (obstacleon2)
            SD->SetIndexOfC2(DStr.AddShape(HC2->Edge()));
          InsertAfter(Stripe, refbis, SD);
          refbis = SD;
        }
      }
      else
      {
        for (ii = SeqSD.Length(); ii >= 1; ii--)
        {
          SD = SeqSD(ii);
          SD->ChangeIndexOfS1(DStr.AddShape(HS1->Face()));
          if (obstacleon1)
            SD->SetIndexOfC1(DStr.AddShape(HC1->Edge()));
          SD->ChangeIndexOfS2(DStr.AddShape(HS2->Face()));
          if (obstacleon2)
            SD->SetIndexOfC2(DStr.AddShape(HC2->Edge()));
          InsertBefore(Stripe, refbis, SD);
          refbis = SD;
        }
      }

      if (!Ok1 && !obstacleon1)

        ChFi3d_Purge(Stripe, SD, ref->Vertex(!forward, 1), !forward, 1, intf, intl);

      if (!Ok2 && !obstacleon2)

        ChFi3d_Purge(Stripe, SD, ref->Vertex(!forward, 2), !forward, 2, intf, intl);

      ref = refbis;
    }

    if (Inside)
    {
      Inside   = false;
      Firstsov = First;
      if (Guide.IsPeriodic())
      {
        complete = false;
        wf       = Guide.FirstParameter();
        wl       = Guide.LastParameter();
      }
    }
    if (forward)
    {
      fini = ((wl - Last) <= 10. * tolesp || (intl && !(obstacleon1 || obstacleon2)));

      if (!fini && Guide.IsPeriodic() && ((wl - Last) < Guide.Period() * 1.e-3))
      {

        occ::handle<ChFiDS_SurfData> thefirst, thelast;
        thefirst = Stripe->SetOfSurfData()->Sequence().First();
        thelast  = Stripe->SetOfSurfData()->Sequence().Last();

        if (thefirst->VertexFirstOnS1().IsOnArc() && thelast->VertexLastOnS1().IsOnArc())
          fini = thefirst->VertexFirstOnS1().Arc().IsSame(thelast->VertexLastOnS1().Arc());
        if (!fini && thefirst->VertexFirstOnS2().IsOnArc() && thelast->VertexLastOnS2().IsOnArc())
          fini = thefirst->VertexFirstOnS2().Arc().IsSame(thelast->VertexLastOnS2().Arc());

        if (fini)
          return;
      }

      if (fini && complete)
      {

        ref     = Stripe->SetOfSurfData()->Sequence().First();
        forward = false;
        fini    = false;
        First   = Firstsov;
      }
      else
      {
        First = Last;
        Last  = wl;
      }
    }
    if (!forward)
    {
      fini     = ((First - wf) <= 10. * tolesp || (intf && !(obstacleon1 || obstacleon2)));
      complete = false;
      Last     = wf;
    }
  }

  if (!Guide.IsPeriodic())
  {
    Guide.FirstParameter(wfsav);
    Guide.LastParameter(wlsav);
    if (!OffsetHGuide.IsNull())
    {
      OffsetHGuide->FirstParameter(wfsav);
      OffsetHGuide->LastParameter(wlsav);
    }
  }
}

void ChFi3d_Builder::PerformSetOfKPart(occ::handle<ChFiDS_Stripe>& Stripe, const bool Simul)
{
  TopOpeBRepDS_DataStructure&      DStr  = myDS->ChangeDS();
  occ::handle<ChFiDS_Spine>&       Spine = Stripe->ChangeSpine();
  occ::handle<BRepAdaptor_Surface> HS1, HS2;
  TopAbs_Orientation               Or1, Or2, RefOr1, RefOr2;
  int                              RefChoix;

  Stripe->Reset();
  occ::handle<NCollection_HSequence<occ::handle<ChFiDS_SurfData>>>& HData =
    Stripe->ChangeSetOfSurfData();
  HData = new NCollection_HSequence<occ::handle<ChFiDS_SurfData>>();
  NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqSurf = HData->ChangeSequence();

  StripeOrientations(Spine, RefOr1, RefOr2, RefChoix);
  Stripe->OrientationOnFace1(RefOr1);
  Stripe->OrientationOnFace2(RefOr2);
  Stripe->Choix(RefChoix);

  occ::handle<BRepTopAdaptor_TopolTool> It1 = new BRepTopAdaptor_TopolTool();
  occ::handle<BRepTopAdaptor_TopolTool> It2 = new BRepTopAdaptor_TopolTool();

  double WFirst, WLast = 0.;
  gp_Vec TFirst, TLast, TEndPeriodic;
  gp_Pnt PFirst, PLast, PEndPeriodic;
  bool   intf = false, intl = false;

  ChFiDS_ElSpine              anElSpine, anOffsetElSpine;
  occ::handle<ChFiDS_ElSpine> CurrentHE       = new ChFiDS_ElSpine(anElSpine);
  occ::handle<ChFiDS_ElSpine> CurrentOffsetHE = new ChFiDS_ElSpine(anOffsetElSpine);
  Spine->D1(Spine->FirstParameter(), PFirst, TFirst);
  CurrentHE->FirstParameter(Spine->FirstParameter());
  CurrentHE->SetFirstPointAndTgt(PFirst, TFirst);
  CurrentOffsetHE->FirstParameter(Spine->FirstParameter());
  CurrentOffsetHE->SetFirstPointAndTgt(PFirst, TFirst);

  bool YaKPart        = false;
  int  iedgelastkpart = 0;

  double WStartPeriodic = 0.;
  double WEndPeriodic   = Spine->LastParameter(Spine->NbEdges());
  Spine->D1(WEndPeriodic, PEndPeriodic, TEndPeriodic);

  for (int iedge = 1; iedge <= Spine->NbEdges(); iedge++)
  {

    ConexFaces(Spine, iedge, HS1, HS2);

    if (ChFi3d_KParticular(Spine, iedge, *HS1, *HS2))
    {
      intf = ((iedge == 1) && !Spine->IsPeriodic());
      intl = ((iedge == Spine->NbEdges()) && !Spine->IsPeriodic());
      Or1  = HS1->Face().Orientation();
      Or2  = HS2->Face().Orientation();
      ChFi3d::NextSide(Or1, Or2, RefOr1, RefOr2, RefChoix);
      const occ::handle<Adaptor3d_Surface>& HSon1 = HS1;
      const occ::handle<Adaptor3d_Surface>& HSon2 = HS2;
      It1->Initialize(HSon1);
      It2->Initialize(HSon2);

      occ::handle<ChFiDS_SurfData>                       SD = new ChFiDS_SurfData();
      NCollection_Sequence<occ::handle<ChFiDS_SurfData>> LSD;

      if (!ChFiKPart_ComputeData::Compute(DStr, SD, HS1, HS2, Or1, Or2, Spine, iedge))
      {
      }
      else if (!SplitKPart(SD, LSD, Spine, iedge, HS1, It1, HS2, It2, intf, intl))
      {
        LSD.Clear();
      }
      else
        iedgelastkpart = iedge;
      if (Spine->IsPeriodic())
      {
        int    nbsd   = LSD.Length();
        double period = Spine->Period();
        double wfp = WStartPeriodic, wlp = WEndPeriodic;

        if (!YaKPart && nbsd > 0)
        {

          occ::handle<ChFiDS_SurfData> firstSD = LSD.ChangeValue(1);
          double                       wwf     = firstSD->FirstSpineParam();
          double                       wwl     = firstSD->LastSpineParam();
          wwf                                  = ChFi3d_InPeriod(wwf, wfp, wlp, tolesp);
          wwl                                  = ChFi3d_InPeriod(wwl, wfp, wlp, tolesp);
          if (wwl <= wwf + tolesp)
            wwl += period;
          wfp = wwf;
          wlp = wfp + period;
        }
        for (int j = 1; j < nbsd; j++)
        {
          occ::handle<ChFiDS_SurfData> jSD = LSD.Value(j);
          for (int k = j + 1; k <= nbsd; k++)
          {
            occ::handle<ChFiDS_SurfData> kSD = LSD.Value(k);
            double                       jwf = jSD->FirstSpineParam();
            jwf                              = ChFi3d_InPeriod(jwf, wfp, wlp, tolesp);
            double kwf                       = kSD->FirstSpineParam();
            kwf                              = ChFi3d_InPeriod(kwf, wfp, wlp, tolesp);
            if (kwf < jwf)
            {
              LSD.SetValue(j, kSD);
              LSD.SetValue(k, jSD);
            }
          }
        }
      }
      NCollection_List<int> li;
      for (int j = 1; j <= LSD.Length(); j++)
      {
        occ::handle<ChFiDS_SurfData>& curSD = LSD.ChangeValue(j);
        if (Simul)
          SimulKPart(curSD);
        SeqSurf.Append(curSD);
        if (!Simul)
          li.Append(curSD->Surf());
        WFirst = LSD.Value(j)->FirstSpineParam();
        WLast  = LSD.Value(j)->LastSpineParam();
        if (Spine->IsPeriodic())
        {
          WFirst = ChFi3d_InPeriod(WFirst, WStartPeriodic, WEndPeriodic, tolesp);
          WLast  = ChFi3d_InPeriod(WLast, WStartPeriodic, WEndPeriodic, tolesp);
          if (WLast <= WFirst + tolesp)
            WLast += Spine->Period();
        }
        TgtKP(LSD.Value(j), Spine, iedge, true, PFirst, TFirst);
        TgtKP(LSD.Value(j), Spine, iedge, false, PLast, TLast);

        if (!YaKPart)
        {
          if (Spine->IsPeriodic())
          {
            WStartPeriodic = WFirst;
            WEndPeriodic   = WStartPeriodic + Spine->Period();
            WLast          = ElCLib::InPeriod(WLast, WStartPeriodic, WEndPeriodic);
            if (WLast <= WFirst + tolesp)
              WLast += Spine->Period();
            PEndPeriodic = PFirst;
            TEndPeriodic = TFirst;
            Spine->SetFirstParameter(WStartPeriodic);
            Spine->SetLastParameter(WEndPeriodic);
          }
          else if (!intf || (iedge > 1))
          {

            Spine->SetFirstTgt(std::min(0., WFirst));
            CurrentHE->LastParameter(WFirst);
            CurrentHE->SetLastPointAndTgt(PFirst, TFirst);
            Spine->AppendElSpine(CurrentHE);
            CurrentHE->ChangeNext() = LSD.Value(j);
            CurrentHE               = new ChFiDS_ElSpine();

            CurrentOffsetHE->LastParameter(WFirst);
            CurrentOffsetHE->SetLastPointAndTgt(PFirst, TFirst);
            Spine->AppendOffsetElSpine(CurrentOffsetHE);
            CurrentOffsetHE->ChangeNext() = LSD.Value(j);
            CurrentOffsetHE               = new ChFiDS_ElSpine();
          }
          CurrentHE->FirstParameter(WLast);
          CurrentHE->SetFirstPointAndTgt(PLast, TLast);
          CurrentHE->ChangePrevious() = LSD.Value(j);
          CurrentOffsetHE->FirstParameter(WLast);
          CurrentOffsetHE->SetFirstPointAndTgt(PLast, TLast);
          CurrentOffsetHE->ChangePrevious() = LSD.Value(j);
          YaKPart                           = true;
        }
        else
        {
          if (WFirst - CurrentHE->FirstParameter() > tolesp)
          {

            CurrentHE->LastParameter(WFirst);
            CurrentHE->SetLastPointAndTgt(PFirst, TFirst);
            Spine->AppendElSpine(CurrentHE);
            CurrentHE->ChangeNext() = LSD.Value(j);
            CurrentHE               = new ChFiDS_ElSpine();

            CurrentOffsetHE->LastParameter(WFirst);
            CurrentOffsetHE->SetLastPointAndTgt(PFirst, TFirst);
            Spine->AppendOffsetElSpine(CurrentOffsetHE);
            CurrentOffsetHE->ChangeNext() = LSD.Value(j);
            CurrentOffsetHE               = new ChFiDS_ElSpine();
          }
          CurrentHE->FirstParameter(WLast);
          CurrentHE->SetFirstPointAndTgt(PLast, TLast);
          CurrentHE->ChangePrevious() = LSD.Value(j);
          CurrentOffsetHE->FirstParameter(WLast);
          CurrentOffsetHE->SetFirstPointAndTgt(PLast, TLast);
          CurrentOffsetHE->ChangePrevious() = LSD.Value(j);
        }
      }
      if (!li.IsEmpty())
        myEVIMap.Bind(Spine->Edges(iedge), li);
    }
  }

  if (!intl || (iedgelastkpart < Spine->NbEdges()))
  {

    if (Spine->IsPeriodic())
    {
      if (WEndPeriodic - WLast > tolesp)
      {
        CurrentHE->LastParameter(WEndPeriodic);
        CurrentHE->SetLastPointAndTgt(PEndPeriodic, TEndPeriodic);
        if (!YaKPart)
          CurrentHE->SetPeriodic(true);
        Spine->AppendElSpine(CurrentHE);

        CurrentOffsetHE->LastParameter(WEndPeriodic);
        CurrentOffsetHE->SetLastPointAndTgt(PEndPeriodic, TEndPeriodic);
        if (!YaKPart)
          CurrentOffsetHE->SetPeriodic(true);
        Spine->AppendOffsetElSpine(CurrentOffsetHE);
      }
    }
    else
    {
      Spine->D1(Spine->LastParameter(), PLast, TLast);
      Spine->SetLastTgt(std::max(Spine->LastParameter(Spine->NbEdges()), WLast));
      if (Spine->LastParameter() - WLast > tolesp)
      {
        CurrentHE->LastParameter(Spine->LastParameter());
        CurrentHE->SetLastPointAndTgt(PLast, TLast);
        Spine->AppendElSpine(CurrentHE);

        CurrentOffsetHE->LastParameter(Spine->LastParameter());
        CurrentOffsetHE->SetLastPointAndTgt(PLast, TLast);
        Spine->AppendOffsetElSpine(CurrentOffsetHE);
      }
    }
  }

  NCollection_List<occ::handle<ChFiDS_ElSpine>>&          ll = Spine->ChangeElSpines();
  NCollection_List<occ::handle<ChFiDS_ElSpine>>::Iterator ILES(ll);
  for (; ILES.More(); ILES.Next())
  {
    ChFi3d_PerformElSpine(ILES.ChangeValue(), Spine, myConti, tolesp);
  }
  if (Spine->Mode() == ChFiDS_ConstThroatWithPenetrationChamfer)
  {
    NCollection_List<occ::handle<ChFiDS_ElSpine>>& offsetll = Spine->ChangeOffsetElSpines();
    for (ILES.Initialize(offsetll); ILES.More(); ILES.Next())
      ChFi3d_PerformElSpine(ILES.ChangeValue(), Spine, myConti, tolesp, true);
  }
  Spine->SplitDone(true);
}

static double ChFi3d_BoxDiag(const Bnd_Box& box)
{
  double a, b, c, d, e, f;
  box.Get(a, b, c, d, e, f);
  d -= a;
  e -= b;
  f -= c;
  d *= d;
  e *= e;
  f *= f;
  double diag = sqrt(d + e + f);
  return diag;
}

void ChFi3d_Builder::PerformSetOfKGen(occ::handle<ChFiDS_Stripe>& Stripe, const bool Simul)
{
  occ::handle<BRepTopAdaptor_TopolTool>                   It1   = new BRepTopAdaptor_TopolTool();
  occ::handle<BRepTopAdaptor_TopolTool>                   It2   = new BRepTopAdaptor_TopolTool();
  occ::handle<ChFiDS_Spine>&                              Spine = Stripe->ChangeSpine();
  NCollection_List<occ::handle<ChFiDS_ElSpine>>&          ll    = Spine->ChangeElSpines();
  NCollection_List<occ::handle<ChFiDS_ElSpine>>::Iterator ILES(ll);
  for (; ILES.More(); ILES.Next())
  {
    PerformSetOfSurfOnElSpine(ILES.Value(), Stripe, It1, It2, Simul);
  }
  if (!Simul)
  {
    TopOpeBRepDS_DataStructure&                                       DStr = myDS->ChangeDS();
    occ::handle<NCollection_HSequence<occ::handle<ChFiDS_SurfData>>>& HData =
      Stripe->ChangeSetOfSurfData();
    NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqSurf  = HData->ChangeSequence();
    int                                                 len      = SeqSurf.Length();
    int                                                 last     = len, i;
    bool                                                periodic = Spine->IsPeriodic();
    if (periodic)
      last++;

    for (i = 1; i <= len; i++)
    {
      occ::handle<ChFiDS_SurfData>& cursd = SeqSurf.ChangeValue(i);
      bool                          tw1   = cursd->TwistOnS1();
      bool                          tw2   = cursd->TwistOnS2();
      occ::handle<ChFiDS_SurfData>  prevsd, nextsd;
      int                           iprev = i - 1;
      if (iprev == 0)
      {
        if (periodic)
          iprev = len;
      }
      int inext = i + 1;
      if (inext > len)
      {
        if (periodic)
          inext = 1;
        else
          inext = 0;
      }

      if (!tw1 && !tw2)
        continue;

      ChFiDS_FaceInterference& intf1       = cursd->ChangeInterferenceOnS1();
      ChFiDS_FaceInterference& intf2       = cursd->ChangeInterferenceOnS2();
      int                      cursurf1    = cursd->IndexOfS1();
      int                      cursurf2    = cursd->IndexOfS2();
      ChFiDS_CommonPoint&      cpd1        = cursd->ChangeVertexFirstOnS1();
      ChFiDS_CommonPoint&      cpd2        = cursd->ChangeVertexFirstOnS2();
      ChFiDS_CommonPoint&      cpf1        = cursd->ChangeVertexLastOnS1();
      ChFiDS_CommonPoint&      cpf2        = cursd->ChangeVertexLastOnS2();
      const gp_Pnt&            pd1         = cpd1.Point();
      const gp_Pnt&            pd2         = cpd2.Point();
      const gp_Pnt&            pf1         = cpf1.Point();
      const gp_Pnt&            pf2         = cpf2.Point();
      double                   ddeb        = pd1.Distance(pd2);
      double                   dfin        = pf1.Distance(pf2);
      double                   don1        = pd1.Distance(pf1);
      double                   don2        = pd2.Distance(pf2);
      bool                     possibleon1 = (don1 < 2 * (ddeb + dfin));
      bool                     possibleon2 = (don2 < 2 * (ddeb + dfin));
      if ((tw1 && !possibleon1) || (tw2 && !possibleon2))
      {
        Spine->SetErrorStatus(ChFiDS_TwistedSurface);
        throw Standard_Failure("adjustment by reprocessing the non-written points");
      }

      bool yaprevon1 = false, yaprevon2 = false;
      bool samesurfon1 = false, samesurfon2 = false;
      if (iprev)
      {
        prevsd      = SeqSurf.ChangeValue(iprev);
        yaprevon1   = !prevsd->TwistOnS1();
        samesurfon1 = (prevsd->IndexOfS1() == cursurf1);
        yaprevon2   = !prevsd->TwistOnS2();
        samesurfon2 = (prevsd->IndexOfS2() == cursurf2);
      }
      bool yanexton1 = false, yanexton2 = false;
      if (inext)
      {
        nextsd    = SeqSurf.ChangeValue(inext);
        yanexton1 = !nextsd->TwistOnS1();
        if (samesurfon1)
          samesurfon1 = (nextsd->IndexOfS1() == cursurf1);
        yanexton2 = !nextsd->TwistOnS2();
        if (samesurfon2)
          samesurfon2 = (nextsd->IndexOfS2() == cursurf2);
      }

      occ::handle<Geom2d_Curve>        PC1 = intf1.PCurveOnFace();
      occ::handle<Geom2d_Curve>        PC2 = intf2.PCurveOnFace();
      occ::handle<BRepAdaptor_Surface> S1  = new BRepAdaptor_Surface();
      TopoDS_Face                      F1  = TopoDS::Face(DStr.Shape(cursurf1));
      S1->Initialize(F1);
      occ::handle<BRepAdaptor_Surface> S2 = new BRepAdaptor_Surface();
      TopoDS_Face                      F2 = TopoDS::Face(DStr.Shape(cursurf2));
      S2->Initialize(F2);
      occ::handle<GeomFill_Boundary> Bdeb, Bfin, Bon1, Bon2;
      bool                           pointuon1 = false, pointuon2 = false;
      if (tw1)
      {
        if (!yaprevon1 || !yanexton1)
        {
          Spine->SetErrorStatus(ChFiDS_TwistedSurface);
          throw Standard_Failure("adjustment by reprocessing the non-written points: no neighbor");
        }
        ChFiDS_FaceInterference& previntf1 = prevsd->ChangeInterferenceOnS1();
        ChFiDS_FaceInterference& nextintf1 = nextsd->ChangeInterferenceOnS1();
        double                   prevpar1  = previntf1.LastParameter();
        double                   nextpar1  = nextintf1.FirstParameter();
        if (samesurfon1)
        {

          occ::handle<Geom2d_Curve> pcprev1 = previntf1.PCurveOnFace();
          occ::handle<Geom2d_Curve> pcnext1 = nextintf1.PCurveOnFace();
          double                    nprevpar1, nnextpar1;
          gp_Pnt2d                  p2d;

          if (ChFi3d_IntTraces(prevsd,
                               prevpar1,
                               nprevpar1,
                               1,
                               1,
                               nextsd,
                               nextpar1,
                               nnextpar1,
                               1,
                               -1,
                               p2d,
                               false,
                               true))
          {

            previntf1.SetLastParameter(nprevpar1);
            nextintf1.SetFirstParameter(nnextpar1);
            pointuon1 = true;
            PC1.Nullify();
          }
          else
          {
            gp_Pnt2d pdeb1, pfin1;
            gp_Vec2d vdeb1, vfin1;
            pcprev1->D1(prevpar1, pdeb1, vdeb1);
            pcnext1->D1(nextpar1, pfin1, vfin1);
            Bon1 = ChFi3d_mkbound(S1, PC1, -1, pdeb1, vdeb1, 1, pfin1, vfin1, tolapp3d, 2.e-4);
          }
        }
        else
        {

          const occ::handle<Geom_Curve>& c3dprev1 = DStr.Curve(previntf1.LineIndex()).Curve();
          const occ::handle<Geom_Curve>& c3dnext1 = DStr.Curve(nextintf1.LineIndex()).Curve();
          gp_Pnt                         Pdeb1, Pfin1;
          gp_Vec                         Vdeb1, Vfin1;
          c3dprev1->D1(prevpar1, Pdeb1, Vdeb1);
          c3dnext1->D1(nextpar1, Pfin1, Vfin1);
          gp_Pnt2d pdeb1, pfin1;
          double   pardeb1 = intf1.FirstParameter();
          double   parfin1 = intf1.LastParameter();
          pdeb1            = PC1->Value(pardeb1);
          pfin1            = PC1->Value(parfin1);
          Bon1 = ChFi3d_mkbound(S1, PC1, -1, pdeb1, Vdeb1, 1, pfin1, Vfin1, tolapp3d, 2.e-4);
        }
      }
      else
      {
        Bon1 = ChFi3d_mkbound(S1, PC1, tolapp3d, 2.e-4);
      }
      if (tw2)
      {
        if (!yaprevon2 || !yanexton2)
        {
          throw Standard_Failure("adjustment by reprocessing the non-written points: no neighbor");
        }
        ChFiDS_FaceInterference& previntf2 = prevsd->ChangeInterferenceOnS2();
        ChFiDS_FaceInterference& nextintf2 = nextsd->ChangeInterferenceOnS2();
        double                   prevpar2  = previntf2.LastParameter();
        double                   nextpar2  = nextintf2.FirstParameter();
        if (samesurfon2)
        {

          occ::handle<Geom2d_Curve> pcprev2 = previntf2.PCurveOnFace();
          occ::handle<Geom2d_Curve> pcnext2 = nextintf2.PCurveOnFace();
          double                    nprevpar2, nnextpar2;
          gp_Pnt2d                  p2d;

          if (ChFi3d_IntTraces(prevsd,
                               prevpar2,
                               nprevpar2,
                               2,
                               1,
                               nextsd,
                               nextpar2,
                               nnextpar2,
                               2,
                               -1,
                               p2d,
                               false,
                               true))
          {

            previntf2.SetLastParameter(nprevpar2);
            nextintf2.SetFirstParameter(nnextpar2);
            pointuon2 = true;
            PC2.Nullify();
          }
          else
          {
            gp_Pnt2d pdeb2, pfin2;
            gp_Vec2d vdeb2, vfin2;
            pcprev2->D1(prevpar2, pdeb2, vdeb2);
            pcnext2->D1(nextpar2, pfin2, vfin2);
            Bon2 = ChFi3d_mkbound(S2, PC2, -1, pdeb2, vdeb2, 1, pfin2, vfin2, tolapp3d, 2.e-4);
          }
        }
        else
        {

          const occ::handle<Geom_Curve>& c3dprev2 = DStr.Curve(previntf2.LineIndex()).Curve();
          const occ::handle<Geom_Curve>& c3dnext2 = DStr.Curve(nextintf2.LineIndex()).Curve();
          gp_Pnt                         Pdeb2, Pfin2;
          gp_Vec                         Vdeb2, Vfin2;
          c3dprev2->D1(prevpar2, Pdeb2, Vdeb2);
          c3dnext2->D1(nextpar2, Pfin2, Vfin2);
          gp_Pnt2d pdeb2, pfin2;
          double   pardeb2 = intf2.FirstParameter();
          double   parfin2 = intf2.LastParameter();
          pdeb2            = PC2->Value(pardeb2);
          pfin2            = PC2->Value(parfin2);
          Bon2 = ChFi3d_mkbound(S2, PC2, -1, pdeb2, Vdeb2, 1, pfin2, Vfin2, tolapp3d, 2.e-4);
        }
      }
      else
      {
        Bon2 = ChFi3d_mkbound(S2, PC2, tolapp3d, 2.e-4);
      }

      const occ::handle<Geom_Surface>& sprev     = DStr.Surface(prevsd->Surf()).Surface();
      const occ::handle<Geom_Surface>& snext     = DStr.Surface(nextsd->Surf()).Surface();
      ChFiDS_FaceInterference&         previntf1 = prevsd->ChangeInterferenceOnS1();
      ChFiDS_FaceInterference&         nextintf1 = nextsd->ChangeInterferenceOnS1();
      ChFiDS_FaceInterference&         previntf2 = prevsd->ChangeInterferenceOnS2();
      ChFiDS_FaceInterference&         nextintf2 = nextsd->ChangeInterferenceOnS2();
      occ::handle<Geom2d_Curve>        pcsprev1  = previntf1.PCurveOnSurf();
      occ::handle<Geom2d_Curve>        pcsnext1  = nextintf1.PCurveOnSurf();
      double                           prevpar1  = previntf1.LastParameter();
      double                           nextpar1  = nextintf1.FirstParameter();
      occ::handle<Geom2d_Curve>        pcsprev2  = previntf2.PCurveOnSurf();
      occ::handle<Geom2d_Curve>        pcsnext2  = nextintf2.PCurveOnSurf();
      double                           prevpar2  = previntf2.LastParameter();
      double                           nextpar2  = nextintf2.FirstParameter();
      gp_Pnt2d                         pdebs1    = pcsprev1->Value(prevpar1);
      gp_Pnt2d                         pdebs2    = pcsprev2->Value(prevpar2);
      gp_Pnt2d                         pfins1    = pcsnext1->Value(nextpar1);
      gp_Pnt2d                         pfins2    = pcsnext2->Value(nextpar2);
      Bdeb = ChFi3d_mkbound(sprev, pdebs1, pdebs2, tolapp3d, 2.e-4);
      Bfin = ChFi3d_mkbound(snext, pfins1, pfins2, tolapp3d, 2.e-4);

      GeomFill_ConstrainedFilling fil(11, 20);
      if (pointuon1)
        fil.Init(Bon2, Bfin, Bdeb, true);
      else if (pointuon2)
        fil.Init(Bon1, Bfin, Bdeb, true);
      else
        fil.Init(Bon1, Bfin, Bon2, Bdeb, true);

      ChFi3d_ReparamPcurv(0., 1., PC1);
      ChFi3d_ReparamPcurv(0., 1., PC2);
      occ::handle<Geom_Surface> newsurf = fil.Surface();
      if (pointuon1)
      {
        newsurf->VReverse();
        done = CompleteData(cursd,
                            newsurf,
                            S1,
                            PC1,
                            S2,
                            PC2,
                            F2.Orientation(),
                            false,
                            false,
                            false,
                            false,
                            false);
        cursd->ChangeIndexOfS1(0);
      }
      else
      {
        done = CompleteData(cursd,
                            newsurf,
                            S1,
                            PC1,
                            S2,
                            PC2,
                            F1.Orientation(),
                            true,
                            false,
                            false,
                            false,
                            false);
        if (pointuon2)
          cursd->ChangeIndexOfS2(0);
      }
      if (tw1)
      {
        prevsd->ChangeVertexLastOnS1().SetPoint(cpd1.Point());
        nextsd->ChangeVertexFirstOnS1().SetPoint(cpf1.Point());
      }
      if (tw2)
      {
        prevsd->ChangeVertexLastOnS2().SetPoint(cpd2.Point());
        nextsd->ChangeVertexFirstOnS2().SetPoint(cpf2.Point());
      }
    }

    for (i = 1; i < last; i++)
    {
      int                           j = i % len + 1;
      int                           curs1, curs2;
      int                           nexts1, nexts2;
      occ::handle<ChFiDS_SurfData>& cursd  = SeqSurf.ChangeValue(i);
      occ::handle<ChFiDS_SurfData>& nextsd = SeqSurf.ChangeValue(j);
      ChFiDS_CommonPoint&           curp1  = cursd->ChangeVertexLastOnS1();
      ChFiDS_CommonPoint&           nextp1 = nextsd->ChangeVertexFirstOnS1();
      if (cursd->IsOnCurve1())
        curs1 = cursd->IndexOfC1();
      else
        curs1 = cursd->IndexOfS1();
      if (cursd->IsOnCurve2())
        curs2 = cursd->IndexOfC2();
      else
        curs2 = cursd->IndexOfS2();
      double              tol1   = std::max(curp1.Tolerance(), nextp1.Tolerance());
      ChFiDS_CommonPoint& curp2  = cursd->ChangeVertexLastOnS2();
      ChFiDS_CommonPoint& nextp2 = nextsd->ChangeVertexFirstOnS2();
      double              tol2   = std::max(curp2.Tolerance(), nextp2.Tolerance());
      if (nextsd->IsOnCurve1())
        nexts1 = nextsd->IndexOfC1();
      else
        nexts1 = nextsd->IndexOfS1();
      if (nextsd->IsOnCurve2())
        nexts2 = nextsd->IndexOfC2();
      else
        nexts2 = nextsd->IndexOfS2();

      if (!curp1.IsOnArc() && nextp1.IsOnArc())
      {
        curp1 = nextp1;
        if ((curs1 == nexts1) && !nextsd->IsOnCurve1())

          ChangeTransition(nextp1, curp1, nexts1, myDS);
      }
      else if (curp1.IsOnArc() && !nextp1.IsOnArc())
      {
        nextp1 = curp1;
        if ((curs1 == nexts1) && !cursd->IsOnCurve1())
          ChangeTransition(curp1, nextp1, curs1, myDS);
      }

      if (!curp2.IsOnArc() && nextp2.IsOnArc())
      {
        curp2 = nextp2;
        if ((curs2 == nexts2) && !nextsd->IsOnCurve2())
          ChangeTransition(nextp2, curp2, curs2, myDS);
      }
      else if (curp2.IsOnArc() && !nextp2.IsOnArc())
      {
        nextp2 = curp2;
        if ((curs2 == nexts2) && !cursd->IsOnCurve2())
          ChangeTransition(curp2, nextp2, curs2, myDS);
      }

      curp1.SetTolerance(tol1);
      nextp1.SetTolerance(tol1);
      curp2.SetTolerance(tol2);
      nextp2.SetTolerance(tol2);

      Bnd_Box b1, b2;
      if (curp1.IsOnArc())
      {
        ChFi3d_EnlargeBox(curp1.Arc(), myEFMap(curp1.Arc()), curp1.ParameterOnArc(), b1);
      }
      if (curp2.IsOnArc())
      {
        ChFi3d_EnlargeBox(curp2.Arc(), myEFMap(curp2.Arc()), curp2.ParameterOnArc(), b2);
      }
      occ::handle<ChFiDS_Stripe> bidst;
      ChFi3d_EnlargeBox(DStr, bidst, cursd, b1, b2, false);
      ChFi3d_EnlargeBox(DStr, bidst, nextsd, b1, b2, true);
      tol1 = ChFi3d_BoxDiag(b1);
      tol2 = ChFi3d_BoxDiag(b2);
      curp1.SetTolerance(tol1);
      nextp1.SetTolerance(tol1);
      curp2.SetTolerance(tol2);
      nextp2.SetTolerance(tol2);
    }

    for (ILES.Initialize(ll); ILES.More(); ILES.Next())
    {
      const occ::handle<ChFiDS_ElSpine>& curhels = ILES.Value();
      double                             WF      = curhels->FirstParameter();
      double                             WL      = curhels->LastParameter();
      int                                IF, IL;
      double                             nwf = WF, nwl = WL;
      double                             period = 0.;
      int                                nbed   = Spine->NbEdges();
      if (periodic)
      {
        period = Spine->Period();
        nwf    = ElCLib::InPeriod(WF, -tolesp, period - tolesp);
        IF     = Spine->Index(nwf, true);
        nwl    = ElCLib::InPeriod(WL, tolesp, period + tolesp);
        IL     = Spine->Index(nwl, false);
        if (nwl < nwf + tolesp)
          IL += nbed;
      }
      else
      {
        IF = Spine->Index(WF, true);
        IL = Spine->Index(WL, false);
      }
      if (IF == IL)
      {

        int IFloc = IF;
        if (periodic)
          IFloc = (IF - 1) % nbed + 1;
        const TopoDS_Edge& Ej = Spine->Edges(IFloc);
        for (i = 1; i <= len; i++)
        {
          occ::handle<ChFiDS_SurfData>& cursd = SeqSurf.ChangeValue(i);
          double                        fp    = cursd->FirstSpineParam();
          double                        lp    = cursd->LastSpineParam();
          if (lp < WF + tolesp || fp > WL - tolesp)
            continue;
          if (!myEVIMap.IsBound(Ej))
          {
            NCollection_List<int> li;
            myEVIMap.Bind(Ej, li);
          }
          myEVIMap.ChangeFind(Ej).Append(cursd->Surf());
        }
      }
      else if (IF < IL)
      {
        NCollection_Array1<double> wv(IF, IL - 1);
        for (i = IF; i < IL; i++)
        {
          int iloc = i;
          if (periodic)
            iloc = (i - 1) % nbed + 1;
          double wi = Spine->LastParameter(iloc);
          if (periodic)
            wi = ElCLib::InPeriod(wi, WF, WF + period);
          gp_Pnt              pv = Spine->Value(wi);
          Extrema_LocateExtPC ext(pv, *curhels, wi, 1.e-8);
          wv(i) = wi;
          if (ext.IsDone())
          {
            wv(i) = ext.Point().Parameter();
          }
        }
        for (i = 1; i <= len; i++)
        {
          occ::handle<ChFiDS_SurfData>& cursd = SeqSurf.ChangeValue(i);
          double                        fp    = cursd->FirstSpineParam();
          double                        lp    = cursd->LastSpineParam();
          int                           j;
          int                           jf = 0, jl = 0;
          if (lp < WF + tolesp || fp > WL - tolesp)
            continue;
          for (j = IF; j < IL; j++)
          {
            jf = j;
            if (fp < wv(j) - tolesp)
              break;
          }
          for (j = IF; j < IL; j++)
          {
            jl = j;
            if (lp < wv(j) + tolesp)
              break;
          }
          for (j = jf; j <= jl; j++)
          {
            int jloc = j;
            if (periodic)
              jloc = (j - 1) % nbed + 1;
            const TopoDS_Edge& Ej = Spine->Edges(jloc);
            if (!myEVIMap.IsBound(Ej))
            {
              NCollection_List<int> li;
              myEVIMap.Bind(Ej, li);
            }
            myEVIMap.ChangeFind(Ej).Append(cursd->Surf());
          }
        }
      }
    }
  }
}

void ChFi3d_Builder::PerformSetOfSurf(occ::handle<ChFiDS_Stripe>& Stripe, const bool Simul)
{
  TopOpeBRepDS_DataStructure& DStr = myDS->ChangeDS();

  const occ::handle<ChFiDS_Spine>& sp = Stripe->Spine();
  int                              SI = ChFi3d_SolidIndex(sp, DStr, myESoMap, myEShMap);
  Stripe->SetSolidIndex(SI);
  if (!sp->SplitDone())
    PerformSetOfKPart(Stripe, Simul);

  PerformSetOfKGen(Stripe, Simul);

  if (!Simul)
    ChFi3d_MakeExtremities(Stripe, DStr, myEFMap, tolapp3d, tol2d);
}
