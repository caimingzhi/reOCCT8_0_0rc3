#include <ShapeAnalysis.hpp>

#include <Bnd_Box2d.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepGProp.hpp>
#include <BRepTools.hpp>
#include <BRepTopAdaptor_FClass2d.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <gp_Pnt2d.hpp>
#include <GProp_GProps.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeExtend_WireData.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

double ShapeAnalysis::AdjustByPeriod(const double Val, const double ToVal, const double Period)
{
  double diff = Val - ToVal;
  double D    = std::abs(diff);
  double P    = std::abs(Period);
  if (D <= 0.5 * P)
    return 0.;
  if (P < 1e-100)
    return diff;
  return (diff > 0 ? -P : P) * floor(D / P + 0.5);
}

double ShapeAnalysis::AdjustToPeriod(const double Val, const double ValMin, const double ValMax)
{
  return AdjustByPeriod(Val, 0.5 * (ValMin + ValMax), ValMax - ValMin);
}

void ShapeAnalysis::FindBounds(const TopoDS_Shape& shape, TopoDS_Vertex& V1, TopoDS_Vertex& V2)
{
  V1.Nullify();
  V2.Nullify();
  ShapeAnalysis_Edge EA;
  if (shape.ShapeType() == TopAbs_WIRE)
  {
    TopoDS_Wire W = TopoDS::Wire(shape);

    TopExp::Vertices(W, V1, V2);
  }
  else if (shape.ShapeType() == TopAbs_EDGE)
  {
    V1 = EA.FirstVertex(TopoDS::Edge(shape));
    V2 = EA.LastVertex(TopoDS::Edge(shape));
  }
  else if (shape.ShapeType() == TopAbs_VERTEX)
    V1 = V2 = TopoDS::Vertex(shape);
}

template <class HSequence>
static inline void ReverseSeq(HSequence& Seq)
{
  Seq.Reverse();
}

double ShapeAnalysis::TotCross2D(const occ::handle<ShapeExtend_WireData>& sewd,
                                 const TopoDS_Face&                       aFace)
{
  int      i, nbc = 0;
  gp_Pnt2d fuv, luv, uv0;
  double   totcross = 0;
  for (i = 1; i <= sewd->NbEdges(); i++)
  {
    TopoDS_Edge               edge = sewd->Edge(i);
    double                    f2d, l2d;
    occ::handle<Geom2d_Curve> c2d = BRep_Tool::CurveOnSurface(edge, aFace, f2d, l2d);
    if (!c2d.IsNull())
    {
      nbc++;
      NCollection_Sequence<gp_Pnt2d> SeqPnt;
      ShapeAnalysis_Curve::GetSamplePoints(c2d, f2d, l2d, SeqPnt);
      if (edge.Orientation() == 1)
        ReverseSeq(SeqPnt);
      if (nbc == 1)
      {
        fuv = SeqPnt.Value(1);
        uv0 = fuv;
      }
      int j = 1;
      for (; j <= SeqPnt.Length(); j++)
      {
        luv = SeqPnt.Value(j);
        totcross += (fuv.X() - luv.X()) * (fuv.Y() + luv.Y()) / 2;
        fuv = luv;
      }
    }
  }
  totcross += (fuv.X() - uv0.X()) * (fuv.Y() + uv0.Y()) / 2;
  return totcross;
}

double ShapeAnalysis::ContourArea(const TopoDS_Wire& theWire)

{
  int    nbc = 0;
  gp_Pnt fuv, luv, uv0;

  gp_XYZ          aTotal(0., 0., 0.);
  TopoDS_Iterator aIte(theWire, false);

  for (; aIte.More(); aIte.Next())
  {
    TopoDS_Edge             edge = TopoDS::Edge(aIte.Value());
    double                  first, last;
    occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(edge, first, last);
    if (!c3d.IsNull())
    {

      NCollection_Sequence<gp_Pnt> aSeqPnt;
      if (!ShapeAnalysis_Curve::GetSamplePoints(c3d, first, last, aSeqPnt))
        continue;
      nbc++;
      if (edge.Orientation() == TopAbs_REVERSED)
        ReverseSeq(aSeqPnt);
      if (nbc == 1)
      {
        fuv = aSeqPnt.Value(1);
        uv0 = fuv;
      }
      int j = 1;
      for (; j <= aSeqPnt.Length(); j++)
      {
        luv = aSeqPnt.Value(j);
        aTotal += luv.XYZ() ^ fuv.XYZ();
        fuv = luv;
      }
    }
  }
  aTotal += uv0.XYZ() ^ fuv.XYZ();
  double anArea = aTotal.Modulus() * 0.5;
  return anArea;
}

bool ShapeAnalysis::IsOuterBound(const TopoDS_Face& face)
{
  TopoDS_Face F = face;
  TopoDS_Wire W;
  F.Orientation(TopAbs_FORWARD);
  int nbw = 0;
  for (TopExp_Explorer exp(F, TopAbs_WIRE); exp.More(); exp.Next())
  {
    W = TopoDS::Wire(exp.Current());
    nbw++;
  }

  if (nbw == 1)
  {
    occ::handle<ShapeExtend_WireData> sewd     = new ShapeExtend_WireData(W);
    double                            totcross = TotCross2D(sewd, F);
    return (totcross >= 0);
  }
  else
  {
    BRepAdaptor_Surface     Ads(F, false);
    double                  tol   = BRep_Tool::Tolerance(F);
    double                  toluv = std::min(Ads.UResolution(tol), Ads.VResolution(tol));
    BRepTopAdaptor_FClass2d fcl(F, toluv);
    bool                    rescl = (fcl.PerformInfinitePoint() == TopAbs_OUT);
    return rescl;
  }
}

TopoDS_Wire ShapeAnalysis::OuterWire(const TopoDS_Face& theFace)
{
  TopoDS_Face aF = theFace;
  aF.Orientation(TopAbs_FORWARD);

  TopExp_Explorer anIt(aF, TopAbs_WIRE);
  while (anIt.More())
  {
    TopoDS_Wire aWire = TopoDS::Wire(anIt.Value());
    anIt.Next();

    if (!anIt.More())
      return aWire;

    occ::handle<ShapeExtend_WireData> aSEWD    = new ShapeExtend_WireData(aWire);
    double                            anArea2d = ShapeAnalysis::TotCross2D(aSEWD, aF);
    if (anArea2d >= 0.)
      return aWire;
  }
  return TopoDS_Wire();
}

void ShapeAnalysis::GetFaceUVBounds(const TopoDS_Face& F,
                                    double&            UMin,
                                    double&            UMax,
                                    double&            VMin,
                                    double&            VMax)
{
  TopoDS_Face FF = F;
  FF.Orientation(TopAbs_FORWARD);
  TopExp_Explorer ex(FF, TopAbs_EDGE);
  if (!ex.More())
  {
    TopLoc_Location L;
    BRep_Tool::Surface(F, L)->Bounds(UMin, UMax, VMin, VMax);
    return;
  }

  Bnd_Box2d           B;
  ShapeAnalysis_Edge  sae;
  ShapeAnalysis_Curve sac;
  for (; ex.More(); ex.Next())
  {
    TopoDS_Edge               edge = TopoDS::Edge(ex.Current());
    occ::handle<Geom2d_Curve> c2d;
    double                    f, l;
    if (!sae.PCurve(edge, F, c2d, f, l, false))
      continue;
    sac.FillBndBox(c2d, f, l, 20, true, B);
  }
  B.Get(UMin, VMin, UMax, VMax);
}
