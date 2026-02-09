#include <LocOpe.hpp>

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <Geom_Curve.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

#define NECHANT 10

bool LocOpe::Closed(const TopoDS_Wire& W, const TopoDS_Face& F)
{
  TopoDS_Vertex Vf, Vl;
  TopExp::Vertices(W, Vf, Vl);
  if (!Vf.IsSame(Vl))
  {
    return false;
  }

  TopExp_Explorer exp, exp2;
  for (exp.Init(W.Oriented(TopAbs_FORWARD), TopAbs_EDGE); exp.More(); exp.Next())
  {
    for (exp2.Init(exp.Current(), TopAbs_VERTEX); exp2.More(); exp2.Next())
    {
      if (exp2.Current().IsSame(Vf) && exp2.Current().Orientation() == TopAbs_FORWARD)
      {
        break;
      }
    }
    if (exp2.More())
    {
      break;
    }
  }
  TopoDS_Edge Ef = TopoDS::Edge(exp.Current());

  for (exp.Init(W.Oriented(TopAbs_FORWARD), TopAbs_EDGE); exp.More(); exp.Next())
  {
    for (exp2.Init(exp.Current(), TopAbs_VERTEX); exp2.More(); exp2.Next())
    {
      if (exp2.Current().IsSame(Vl) && exp2.Current().Orientation() == TopAbs_REVERSED)
      {
        break;
      }
    }
    if (exp2.More())
    {
      break;
    }
  }
  TopoDS_Edge El = TopoDS::Edge(exp.Current());

  double                    f, l;
  gp_Pnt2d                  pf, pl;
  occ::handle<Geom2d_Curve> C2d = BRep_Tool::CurveOnSurface(Ef, F, f, l);
  if (Ef.Orientation() == TopAbs_FORWARD)
  {
    pf = C2d->Value(f);
  }
  else
  {
    pf = C2d->Value(l);
  }
  C2d = BRep_Tool::CurveOnSurface(El, F, f, l);
  if (El.Orientation() == TopAbs_FORWARD)
  {
    pl = C2d->Value(l);
  }
  else
  {
    pl = C2d->Value(f);
  }

  if (pf.Distance(pl) <= Precision::PConfusion(Precision::Confusion()))
  {
    return true;
  }
  return false;
}

bool LocOpe::Closed(const TopoDS_Edge& E, const TopoDS_Face& F)
{
  BRep_Builder B;
  TopoDS_Wire  W;
  B.MakeWire(W);
  B.Add(W, E.Oriented(TopAbs_FORWARD));
  return LocOpe::Closed(W, F);
}

bool LocOpe::TgtFaces(const TopoDS_Edge& E, const TopoDS_Face& F1, const TopoDS_Face& F2)
{
  BRepAdaptor_Surface bs(F1, false);
  double              u;
  double              ta = 0.0001;

  TopoDS_Edge e = E;

  occ::handle<BRepAdaptor_Surface> HS1 = new BRepAdaptor_Surface(F1);
  occ::handle<BRepAdaptor_Surface> HS2 = new BRepAdaptor_Surface(F2);
  e.Orientation(TopAbs_FORWARD);
  occ::handle<BRepAdaptor_Curve2d> HC2d  = new BRepAdaptor_Curve2d();
  occ::handle<BRepAdaptor_Curve2d> HC2d2 = new BRepAdaptor_Curve2d();
  HC2d->Initialize(e, F1);
  HC2d2->Initialize(e, F2);

  bool   rev1 = (F1.Orientation() == TopAbs_REVERSED);
  bool   rev2 = (F2.Orientation() == TopAbs_REVERSED);
  double f, l, eps, angmin = M_PI, angmax = -M_PI, ang;
  BRep_Tool::Range(e, f, l);

  eps = (l - f) / 100.;
  f += eps;
  l -= eps;
  gp_Pnt2d p;
  gp_Pnt   pp1;
  gp_Vec   du, dv;
  gp_Vec   d1, d2;

  double uu, vv;

  int i;
  for (i = 0; i <= 20; i++)
  {
    u = f + (l - f) * i / 20;
    HC2d->D0(u, p);
    HS1->D1(p.X(), p.Y(), pp1, du, dv);
    d1 = (du.Crossed(dv)).Normalized();
    if (rev1)
      d1.Reverse();
    HC2d2->D0(u, p);
    p.Coord(uu, vv);
    HS2->D1(uu, vv, pp1, du, dv);
    d2 = (du.Crossed(dv)).Normalized();
    if (rev2)
      d2.Reverse();
    ang = d1.Angle(d2);
    if (ang <= angmin)
      angmin = ang;
    if (ang >= angmax)
      angmax = ang;
  }
  return (angmax <= ta);
}

void LocOpe::SampleEdges(const TopoDS_Shape& theShape, NCollection_Sequence<gp_Pnt>& theSeq)
{
  theSeq.Clear();
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> theMap;

  TopExp_Explorer         exp(theShape, TopAbs_EDGE);
  TopLoc_Location         Loc;
  occ::handle<Geom_Curve> C;
  double                  f, l, prm;
  int                     i;

  for (; exp.More(); exp.Next())
  {
    const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
    if (!theMap.Add(edg))
    {
      continue;
    }
    if (!BRep_Tool::Degenerated(edg))
    {
      C            = BRep_Tool::Curve(edg, Loc, f, l);
      C            = occ::down_cast<Geom_Curve>(C->Transformed(Loc.Transformation()));
      double delta = (l - f) / NECHANT * 0.123456;
      for (i = 1; i < NECHANT; i++)
      {
        prm = delta + ((NECHANT - i) * f + i * l) / NECHANT;
        theSeq.Append(C->Value(prm));
      }
    }
  }

  for (exp.Init(theShape, TopAbs_VERTEX); exp.More(); exp.Next())
  {
    if (theMap.Add(exp.Current()))
    {
      theSeq.Append(BRep_Tool::Pnt(TopoDS::Vertex(exp.Current())));
    }
  }
}
