#include <AppDef_BSplineCompute.hpp>
#include <AppDef_MultiLine.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <BRep_Builder.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepApprox_Approx.hpp>
#include <BRepApprox_ApproxLine.hpp>
#include <BRepExtrema_ExtPC.hpp>
#include <BRepTopAdaptor_HVertex.hpp>
#include <BRepTopAdaptor_TopolTool.hpp>
#include <Contap_Contour.hpp>
#include <Contap_Line.hpp>
#include <Contap_Point.hpp>
#include <Extrema_LocateExtPC.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Line.hpp>
#include <Geom_Surface.hpp>
#include <GeomProjLib.hpp>
#include <HLRTopoBRep_Data.hpp>
#include <HLRTopoBRep_DSFiller.hpp>
#include <HLRTopoBRep_FaceIsoLiner.hpp>
#include <math_Vector.hpp>
#include <Precision.hpp>
#include <Standard_ProgramError.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Integer.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

void HLRTopoBRep_DSFiller::Insert(
  const TopoDS_Shape&                                                              S,
  Contap_Contour&                                                                  FO,
  HLRTopoBRep_Data&                                                                DS,
  NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST,
  const int                                                                        nbIso)
{
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> ShapeMap;
  TopExp_Explorer                                        ex(S, TopAbs_FACE);
  DS.Clear();
  bool withPCurve = true;
  int  f          = 0;

  while (ex.More())
  {
    if (ShapeMap.Add(ex.Current()))
    {
      f++;
      TopoDS_Face S1 = TopoDS::Face(ex.Current());
      S1.Orientation(TopAbs_FORWARD);
      occ::handle<BRepTopAdaptor_TopolTool> Domain;
      occ::handle<Adaptor3d_Surface>        Surface;
      if (MST.IsBound(S1))
      {
        BRepTopAdaptor_Tool& BRT = MST.ChangeFind(S1);
        Domain                   = BRT.GetTopolTool();
        Surface                  = BRT.GetSurface();
      }
      else
      {
        BRepTopAdaptor_Tool BRT(S1, Precision::PConfusion());
        MST.Bind(S1, BRT);
        Domain  = BRT.GetTopolTool();
        Surface = BRT.GetSurface();
      }
      FO.Perform(Surface, Domain);
      if (FO.IsDone())
      {
        if (!FO.IsEmpty())
          InsertFace(f, S1, FO, DS, withPCurve);
      }
      if (nbIso != 0)
        HLRTopoBRep_FaceIsoLiner::Perform(f, S1, DS, nbIso);
    }
    ex.Next();
  }
  ProcessEdges(DS);
}

void HLRTopoBRep_DSFiller::InsertFace(const int,
                                      const TopoDS_Face& F,
                                      Contap_Contour&    FO,
                                      HLRTopoBRep_Data&  DS,
                                      const bool         withPCurve)
{

  const double                    tol  = BRep_Tool::Tolerance(F);
  NCollection_List<TopoDS_Shape>& IntL = DS.AddIntL(F);
  NCollection_List<TopoDS_Shape>& OutL = DS.AddOutL(F);

  TopoDS_Vertex VF, VL;

  const int NbLines = FO.NbLines();
  int       CurLine;
  for (CurLine = 1; CurLine <= NbLines; CurLine++)
  {
    const Contap_Line& Line     = FO.Line(CurLine);
    const int          NbPoints = Line.NbVertex();
    int                CurPoint;
    if (Line.TypeContour() == Contap_Restriction)
    {

      TopoDS_Edge E = (*(BRepAdaptor_Curve2d*)(Line.Arc().get())).Edge();
      OutL.Append(E);
      TopExp::Vertices(E, VF, VL);

      for (CurPoint = 1; CurPoint <= NbPoints; CurPoint++)
      {
        Contap_Point P = Line.Vertex(CurPoint);
        if (P.IsInternal())
        {
          if (P.Value().IsEqual(BRep_Tool::Pnt(VF), BRep_Tool::Tolerance(VF)))
          {
            if (P.Value().IsEqual(BRep_Tool::Pnt(VL), BRep_Tool::Tolerance(VL)))
            {
              InsertVertex(P, tol, E, DS);
            }
          }
        }
      }
    }
    else
    {
      for (CurPoint = 1; CurPoint <= NbPoints; CurPoint++)
      {

        const Contap_Point PF = Line.Vertex(CurPoint);
        if (PF.IsInternal() && CurPoint != 1)
          VF = VL;
        else
          VF = MakeVertex(PF, tol, DS);
        const double parF = PF.ParameterOnLine();

        if (CurPoint < NbPoints)
        {
          const Contap_Point PL = Line.Vertex(CurPoint + 1);
          VL                    = MakeVertex(PL, tol, DS);
          const double parL     = PL.ParameterOnLine();

          if ((parL - parF) > Precision::PConfusion())
          {

            occ::handle<Geom_Curve>   C;
            occ::handle<Geom2d_Curve> C2d;
            double                    first                     = parF;
            double                    last                      = parL;
            bool                      InsuffisantNumberOfPoints = false;

            switch (Line.TypeContour())
            {

              case Contap_Lin:
              {
                C = new Geom_Line(Line.Line());
                if (withPCurve)
                {
                  occ::handle<Geom_Surface> S   = BRep_Tool::Surface(F);
                  double                    Tol = 1e-7;
                  C2d                           = GeomProjLib::Curve2d(C, first, last, S, Tol);
                }
              }
              break;

              case Contap_Circle:
              {
                C = new Geom_Circle(Line.Circle());
                if (withPCurve)
                {
                  TopLoc_Location           Loc;
                  occ::handle<Geom_Surface> S = BRep_Tool::Surface(F, Loc);
                  if (!Loc.IsIdentity())
                  {
                    S = occ::down_cast<Geom_Surface>(S->Transformed(Loc.Transformation()));
                  }
                  double Tol = 1e-7;
                  C2d        = GeomProjLib::Curve2d(C, first, last, S, Tol);
                }
              }
              break;

              case Contap_Walking:
              {

                int ipF = int(parF);
                int ipL = int(parL);

                if (ipL - ipF < 1)
                {
                  InsuffisantNumberOfPoints = true;
                }

                else if (ipL - ipF < 5)
                {
                  const int                  nbp = ipL - ipF + 1;
                  NCollection_Array1<double> knots(1, nbp);
                  NCollection_Array1<int>    mults(1, nbp);
                  NCollection_Array1<gp_Pnt> Points(1, nbp);

                  for (int i = 1; i <= nbp; i++)
                  {
                    knots.SetValue(i, (double)i);
                    mults.SetValue(i, 1);
                    Points.SetValue(i, Line.Point(i + ipF - 1).Value());
                  }
                  mults(1) = mults(nbp) = 2;
                  C                     = new Geom_BSplineCurve(Points, knots, mults, 1);

                  if (withPCurve)
                  {
                    NCollection_Array1<gp_Pnt2d> Points2d(1, nbp);
                    for (int i = 1; i <= nbp; i++)
                    {
                      double u, v;
                      Line.Point(i + ipF - 1).ParametersOnS2(u, v);
                      Points2d.SetValue(i, gp_Pnt2d(u, v));
                    }
                    C2d = new Geom2d_BSplineCurve(Points2d, knots, mults, 1);
                  }
                  first = 1;
                  last  = nbp;
                }
                else
                {
                  const int                  nbp = ipL - ipF + 1;
                  NCollection_Array1<double> knots(1, nbp);
                  NCollection_Array1<int>    mults(1, nbp);
                  NCollection_Array1<gp_Pnt> Points(1, nbp);

                  double Maxx, Maxy, Maxz, Maxu, Maxv;
                  double Minx, Miny, Minz, Minu, Minv;
                  Maxx = Maxy = Maxz = Maxu = Maxv = -RealLast();
                  Minx = Miny = Minz = Minu = Minv = RealLast();

                  for (int i = 1; i <= nbp; i++)
                  {
                    knots.SetValue(i, (double)i);
                    mults.SetValue(i, 1);
                    const gp_Pnt& P = Line.Point(i + ipF - 1).Value();
                    if (P.X() < Minx)
                      Minx = P.X();
                    if (P.Y() < Miny)
                      Miny = P.Y();
                    if (P.Z() < Minz)
                      Minz = P.Z();
                    if (P.X() > Maxx)
                      Maxx = P.X();
                    if (P.Y() > Maxy)
                      Maxy = P.Y();
                    if (P.Z() > Maxz)
                      Maxz = P.Z();
                    Points.SetValue(i, P);
                  }
                  mults(1) = mults(nbp) = 2;
                  occ::handle<Geom_BSplineCurve>   AppC;
                  occ::handle<Geom2d_BSplineCurve> AppC2d;
                  AppC = new Geom_BSplineCurve(Points, knots, mults, 1);

                  if (withPCurve)
                  {
                    NCollection_Array1<gp_Pnt2d> Points2d(1, nbp);
                    for (int i = 1; i <= nbp; i++)
                    {
                      double u, v;
                      Line.Point(i + ipF - 1).ParametersOnS2(u, v);
                      if (u < Minu)
                        Minu = u;
                      if (v < Minv)
                        Minv = v;
                      if (u > Maxu)
                        Maxu = u;
                      if (v > Maxv)
                        Maxv = v;
                      Points2d.SetValue(i, gp_Pnt2d(u, v));
                    }
                    AppC2d = new Geom2d_BSplineCurve(Points2d, knots, mults, 1);
                  }
                  first = 1;
                  last  = nbp;

                  occ::handle<BRepApprox_ApproxLine> AppLine;
                  occ::handle<Geom2d_BSplineCurve>   CNull;
                  AppLine = new BRepApprox_ApproxLine(AppC, AppC2d, CNull);

                  int               dmin = 4, dmax = 8, niter = 0;
                  bool              tg = false;
                  BRepApprox_Approx Approx;
                  double            TOL3d, TOL2d, TOL = 0.0001;

                  Maxx -= Minx;
                  Maxy -= Miny;
                  Maxz -= Minz;
                  Maxu -= Minu;
                  Maxv -= Minv;
                  if (Maxy > Maxx)
                    Maxx = Maxy;
                  if (Maxz > Maxx)
                    Maxx = Maxy;
                  if (Maxv > Maxu)
                    Maxu = Maxv;

                  TOL3d = TOL * Maxx;
                  if (TOL3d < 1e-12)
                    TOL3d = 1e-12;
                  else if (TOL3d > 0.1)
                    TOL3d = 0.1;
                  TOL2d = TOL * Maxu;
                  if (TOL2d < 1e-12)
                    TOL2d = 1e-12;
                  else if (TOL2d > 0.1)
                    TOL2d = 0.1;

                  Approx.SetParameters(TOL3d, TOL2d, dmin, dmax, niter, 30, tg);
                  Approx.Perform(AppLine, true, true, false, 1, nbp);
                  if (!Approx.IsDone())
                  {
                    C     = AppC;
                    C2d   = AppC2d;
                    first = 1;
                    last  = nbp;
                  }
                  else
                  {
                    const AppParCurves_MultiBSpCurve& AppVal = Approx.Value(1);
                    NCollection_Array1<gp_Pnt>        poles3d(1, AppVal.NbPoles());
                    AppVal.Curve(1, poles3d);
                    C = new Geom_BSplineCurve(poles3d,
                                              AppVal.Knots(),
                                              AppVal.Multiplicities(),
                                              AppVal.Degree());

                    const AppParCurves_MultiBSpCurve& AppVal2 = Approx.Value(2);
                    NCollection_Array1<gp_Pnt2d>      poles2d(1, AppVal2.NbPoles());
                    AppVal2.Curve(2, poles2d);
                    C2d   = new Geom2d_BSplineCurve(poles2d,
                                                  AppVal2.Knots(),
                                                  AppVal2.Multiplicities(),
                                                  AppVal2.Degree());
                    first = C2d->FirstParameter();
                    last  = C2d->LastParameter();
                  }
                }
              }
              break;

              case Contap_Restriction:
              {
                throw Standard_ProgramError("HLRTopoBRep_DSFiller::InsertFace : Restriction");
              }
              break;
            }

            if (!InsuffisantNumberOfPoints)
            {
              TopoDS_Edge  E;
              BRep_Builder B;
              B.MakeEdge(E, C, tol);
              VF.Orientation(TopAbs_FORWARD);
              VL.Orientation(TopAbs_REVERSED);
              B.Add(E, VF);
              B.Add(E, VL);
              B.Range(E, first, last);

              if (!C2d.IsNull())
              {
                B.UpdateEdge(E, C2d, F, BRep_Tool::Tolerance(F));
              }

              if (!E.IsNull())
                IntL.Append(E);
            }
          }
        }
      }
    }
  }

  const double                             SqTol = tol * tol;
  NCollection_List<TopoDS_Shape>::Iterator itl1(IntL);
  for (; itl1.More(); itl1.Next())
  {
    TopoDS_Edge anIntLine = TopoDS::Edge(itl1.Value());
    anIntLine.Orientation(TopAbs_FORWARD);
    TopoDS_Vertex aVer[2];
    TopExp::Vertices(anIntLine, aVer[0], aVer[1]);
    NCollection_List<TopoDS_Shape>::Iterator itl2 = itl1;
    for (; itl2.More(); itl2.Next())
    {
      TopoDS_Edge anIntLine2 = TopoDS::Edge(itl2.Value());
      anIntLine2.Orientation(TopAbs_FORWARD);
      if (anIntLine2.IsSame(anIntLine))
        continue;
      TopoDS_Vertex aVer2[2];
      TopExp::Vertices(anIntLine2, aVer2[0], aVer2[1]);
      for (int i = 0; i < 2; i++)
      {
        if (i == 1 && aVer[0].IsSame(aVer[1]))
          continue;
        gp_Pnt Pnt1 = BRep_Tool::Pnt(aVer[i]);
        for (int j = 0; j < 2; j++)
        {
          if (aVer[i].IsSame(aVer2[j]))
            continue;
          gp_Pnt Pnt2 = BRep_Tool::Pnt(aVer2[j]);
          if (Pnt1.SquareDistance(Pnt2) <= SqTol)
          {
            BRep_Builder aBB;
            aBB.Remove(anIntLine2, aVer2[j]);
            aVer[i].Orientation((j == 0) ? TopAbs_FORWARD : TopAbs_REVERSED);
            aBB.Add(anIntLine2, aVer[i]);
          }
        }
      }
    }
  }
}

TopoDS_Vertex HLRTopoBRep_DSFiller::MakeVertex(const Contap_Point& P,
                                               const double        tol,
                                               HLRTopoBRep_Data&   DS)
{
  BRep_Builder  B;
  TopoDS_Vertex V;
  if (P.IsVertex())
  {
    V = occ::down_cast<BRepTopAdaptor_HVertex>(P.Vertex())->Vertex();
    DS.AddOutV(V);
  }
  else
  {

    if (P.IsOnArc())
    {
      const TopoDS_Edge& E   = (*(BRepAdaptor_Curve2d*)(P.Arc().get())).Edge();
      double             Par = P.ParameterOnArc();
      const gp_Pnt&      P3d = P.Value();

      for (DS.InitVertex(E); DS.MoreVertex(); DS.NextVertex())
      {
        TopoDS_Vertex curV = DS.Vertex();
        double        curP = DS.Parameter();
        const gp_Pnt& PPP  = BRep_Tool::Pnt(curV);
        double        TTT  = BRep_Tool::Tolerance(curV);
        if (P3d.IsEqual(PPP, TTT))
        {
          V = curV;
          break;
        }
        else if (Par < curP)
        {
          B.MakeVertex(V, P.Value(), tol);
          DS.InsertBefore(V, Par);
          break;
        }
      }
      if (!DS.MoreVertex())
      {
        B.MakeVertex(V, P.Value(), tol);
        DS.Append(V, Par);
      }
      DS.AddOutV(V);
    }

    else
    {
      B.MakeVertex(V, P.Value(), tol);
      if (P.IsInternal())
        DS.AddIntV(V);
      else
        DS.AddOutV(V);
    }
  }
  return V;
}

void HLRTopoBRep_DSFiller::InsertVertex(const Contap_Point& P,
                                        const double        tol,
                                        const TopoDS_Edge&  E,
                                        HLRTopoBRep_Data&   DS)
{
  BRep_Builder  B;
  TopoDS_Vertex V;

  if (P.IsVertex())
  {
    V = occ::down_cast<BRepTopAdaptor_HVertex>(P.Vertex())->Vertex();
  }
  else
  {
    double Par = P.ParameterOnLine();

    for (DS.InitVertex(E); DS.MoreVertex(); DS.NextVertex())
    {
      TopoDS_Vertex curV = DS.Vertex();
      double        curP = DS.Parameter();
      if (P.Value().IsEqual(BRep_Tool::Pnt(curV), BRep_Tool::Tolerance(curV)))
      {
        V = curV;
        break;
      }
      else if (Par < curP)
      {
        B.MakeVertex(V, P.Value(), tol);
        DS.InsertBefore(V, Par);
        break;
      }
    }
    if (!DS.MoreVertex())
    {
      B.MakeVertex(V, P.Value(), tol);
      DS.Append(V, Par);
    }
  }
  DS.AddIntV(V);
}

void HLRTopoBRep_DSFiller::ProcessEdges(HLRTopoBRep_Data& DS)
{
  BRep_Builder  B;
  TopoDS_Edge   newE;
  TopoDS_Vertex VF, VL, VI;
  double        PF, PL, PI;

  for (DS.InitEdge(); DS.MoreEdge(); DS.NextEdge())
  {
    TopoDS_Edge                     E    = DS.Edge();
    NCollection_List<TopoDS_Shape>& SplE = DS.AddSplE(E);
    VF                                   = TopExp::FirstVertex(E);
    VL                                   = TopExp::LastVertex(E);
    BRep_Tool::Range(E, PF, PL);
    VF.Orientation(TopAbs_FORWARD);
    VL.Orientation(TopAbs_REVERSED);

    for (DS.InitVertex(E); DS.MoreVertex(); DS.NextVertex())
    {
      VI = DS.Vertex();
      PI = DS.Parameter();
      VI.Orientation(TopAbs_REVERSED);
      newE = E;
      newE.EmptyCopy();
      newE.Orientation(TopAbs_FORWARD);
      B.Add(newE, VF);
      B.UpdateVertex(VF, PF, newE, BRep_Tool::Tolerance(VF));
      B.Add(newE, VI);
      B.UpdateVertex(VI, PI, newE, BRep_Tool::Tolerance(VI));
      newE.Orientation(E.Orientation());
      SplE.Append(newE);
      VF = VI;
      PF = PI;
      VF.Orientation(TopAbs_FORWARD);
    }
    newE = E;
    newE.EmptyCopy();
    newE.Orientation(TopAbs_FORWARD);
    B.Add(newE, VF);
    B.UpdateVertex(VF, PF, newE, BRep_Tool::Tolerance(VF));
    B.Add(newE, VL);
    B.UpdateVertex(VL, PL, newE, BRep_Tool::Tolerance(VL));
    newE.Orientation(E.Orientation());
    SplE.Append(newE);
  }
}
