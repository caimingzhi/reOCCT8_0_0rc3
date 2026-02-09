#include <BRep_Builder.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Geom_Curve.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeAnalysis_FreeBounds.hpp>
#include <ShapeAnalysis_FreeBoundsProperties.hpp>
#include <ShapeAnalysis_Wire.hpp>
#include <ShapeExtend_Explorer.hpp>
#include <ShapeExtend_WireData.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

#define NbControl 23

static void ContourProperties(const TopoDS_Wire& wire, double& countourArea, double& countourLength)
{
  int    nbe    = 0;
  double length = 0.0;
  gp_XYZ area(.0, .0, .0);
  gp_XYZ prev, cont;

  for (BRepTools_WireExplorer exp(wire); exp.More(); exp.Next())
  {
    const TopoDS_Edge& Edge = exp.Current();
    nbe++;

    double                  First, Last;
    occ::handle<Geom_Curve> c3d;
    ShapeAnalysis_Edge      sae;
    if (!sae.Curve3d(Edge, c3d, First, Last))
      continue;

    int ibeg = 0;
    if (nbe == 1)
    {
      gp_Pnt pntIni = c3d->Value(First);
      prev          = pntIni.XYZ();
      cont          = prev;
      ibeg          = 1;
    }

    for (int i = ibeg; i < NbControl; i++)
    {
      double prm     = ((NbControl - 1 - i) * First + i * Last) / (NbControl - 1);
      gp_Pnt pntCurr = c3d->Value(prm);
      gp_XYZ curr    = pntCurr.XYZ();
      gp_XYZ delta   = curr - prev;
      length += delta.Modulus();
      area += curr ^ prev;
      prev = curr;
    }
  }

  area += cont ^ prev;
  countourArea   = area.Modulus() / 2;
  countourLength = length;
}

ShapeAnalysis_FreeBoundsProperties::ShapeAnalysis_FreeBoundsProperties()
{
  myClosedFreeBounds = new NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>();
  myOpenFreeBounds   = new NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>();
  myTolerance        = 0.;
}

ShapeAnalysis_FreeBoundsProperties::ShapeAnalysis_FreeBoundsProperties(const TopoDS_Shape& shape,
                                                                       const double tolerance,
                                                                       const bool   splitclosed,
                                                                       const bool   splitopen)
{
  myClosedFreeBounds = new NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>();
  myOpenFreeBounds   = new NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>();
  Init(shape, tolerance, splitclosed, splitopen);
}

ShapeAnalysis_FreeBoundsProperties::ShapeAnalysis_FreeBoundsProperties(const TopoDS_Shape& shape,
                                                                       const bool splitclosed,
                                                                       const bool splitopen)
{
  myClosedFreeBounds = new NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>();
  myOpenFreeBounds   = new NCollection_HSequence<occ::handle<ShapeAnalysis_FreeBoundData>>();
  myTolerance        = 0.;
  Init(shape, splitclosed, splitopen);
}

void ShapeAnalysis_FreeBoundsProperties::Init(const TopoDS_Shape& shape,
                                              const double        tolerance,
                                              const bool          splitclosed,
                                              const bool          splitopen)
{
  Init(shape, splitclosed, splitopen);
  myTolerance = tolerance;
}

void ShapeAnalysis_FreeBoundsProperties::Init(const TopoDS_Shape& shape,
                                              const bool          splitclosed,
                                              const bool          splitopen)
{
  myShape       = shape;
  mySplitClosed = splitclosed;
  mySplitOpen   = splitopen;
}

bool ShapeAnalysis_FreeBoundsProperties::Perform()
{
  bool result = false;
  result |= DispatchBounds();
  result |= CheckNotches();
  result |= CheckContours();
  return result;
}

bool ShapeAnalysis_FreeBoundsProperties::DispatchBounds()
{
  if (!IsLoaded())
    return false;

  TopoDS_Compound tmpClosedBounds, tmpOpenBounds;
  if (myTolerance > 0.)
  {
    ShapeAnalysis_FreeBounds safb(myShape, myTolerance, mySplitClosed, mySplitOpen);
    tmpClosedBounds = safb.GetClosedWires();
    tmpOpenBounds   = safb.GetOpenWires();
  }
  else
  {
    ShapeAnalysis_FreeBounds safb(myShape, mySplitClosed, mySplitOpen);
    tmpClosedBounds = safb.GetClosedWires();
    tmpOpenBounds   = safb.GetOpenWires();
  }

  ShapeExtend_Explorer                             shexpl;
  occ::handle<NCollection_HSequence<TopoDS_Shape>> tmpSeq =
    shexpl.SeqFromCompound(tmpClosedBounds, false);
  int i;
  for (i = 1; i <= tmpSeq->Length(); i++)
  {
    TopoDS_Wire                              wire   = TopoDS::Wire(tmpSeq->Value(i));
    occ::handle<ShapeAnalysis_FreeBoundData> fbData = new ShapeAnalysis_FreeBoundData();
    fbData->SetFreeBound(wire);
    myClosedFreeBounds->Append(fbData);
  }

  occ::handle<NCollection_HSequence<TopoDS_Shape>> tmpSeq2 =
    shexpl.SeqFromCompound(tmpOpenBounds, false);
  for (i = 1; i <= tmpSeq2->Length(); i++)
  {
    TopoDS_Wire                              wire   = TopoDS::Wire(tmpSeq2->Value(i));
    occ::handle<ShapeAnalysis_FreeBoundData> fbData = new ShapeAnalysis_FreeBoundData;
    fbData->SetFreeBound(wire);
    myOpenFreeBounds->Append(fbData);
  }

  return true;
}

bool ShapeAnalysis_FreeBoundsProperties::CheckNotches(const double prec)
{
  int i;
  for (i = 1; i <= myClosedFreeBounds->Length(); i++)
  {
    occ::handle<ShapeAnalysis_FreeBoundData> fbData = myClosedFreeBounds->Value(i);
    CheckNotches(fbData, prec);
  }
  for (i = 1; i <= myOpenFreeBounds->Length(); i++)
  {
    occ::handle<ShapeAnalysis_FreeBoundData> fbData = myOpenFreeBounds->Value(i);
    CheckNotches(fbData, prec);
  }

  return true;
}

bool ShapeAnalysis_FreeBoundsProperties::CheckNotches(
  occ::handle<ShapeAnalysis_FreeBoundData>& fbData,
  const double                              prec)
{
  ShapeExtend_WireData swd(fbData->FreeBound());
  if (swd.NbEdges() > 1)
    for (int j = 1; j <= swd.NbEdges(); j++)
    {
      TopoDS_Wire notch;
      double      dMax;
      if (CheckNotches(fbData->FreeBound(), j, notch, dMax, prec))
        fbData->AddNotch(notch, dMax);
    }

  return true;
}

bool ShapeAnalysis_FreeBoundsProperties::CheckContours(const double prec)
{
  bool status = false;
  int  i;
  for (i = 1; i <= myClosedFreeBounds->Length(); i++)
  {
    occ::handle<ShapeAnalysis_FreeBoundData> fbData = myClosedFreeBounds->Value(i);
    status |= FillProperties(fbData, prec);
  }
  for (i = 1; i <= myOpenFreeBounds->Length(); i++)
  {
    occ::handle<ShapeAnalysis_FreeBoundData> fbData = myOpenFreeBounds->Value(i);
    status |= FillProperties(fbData, prec);
  }

  return status;
}

bool ShapeAnalysis_FreeBoundsProperties::CheckNotches(const TopoDS_Wire& wire,
                                                      const int          num,
                                                      TopoDS_Wire&       notch,
                                                      double&            distMax,
                                                      const double)
{
  double                            tol = std::max(myTolerance, Precision::Confusion());
  occ::handle<ShapeExtend_WireData> wdt = new ShapeExtend_WireData(wire);
  BRep_Builder                      B;
  B.MakeWire(notch);

  if ((num <= 0) || (num > wdt->NbEdges()))
    return false;

  int n1 = (num > 0 ? num : wdt->NbEdges());
  int n2 = (n1 < wdt->NbEdges() ? n1 + 1 : 1);

  TopoDS_Edge E1 = wdt->Edge(n1);
  B.Add(notch, E1);

  occ::handle<ShapeAnalysis_Wire> saw = new ShapeAnalysis_Wire;
  saw->Load(wdt);
  saw->SetPrecision(myTolerance);
  if (saw->CheckSmall(n2, tol))
  {
    B.Add(notch, wdt->Edge(n2));
    n2 = (n2 < wdt->NbEdges() ? n2 + 1 : 1);
  }

  TopoDS_Edge E2 = wdt->Edge(n2);
  B.Add(notch, E2);

  double                  First1, Last1, First2, Last2;
  occ::handle<Geom_Curve> c3d1, c3d2;
  ShapeAnalysis_Edge      sae;

  if (!sae.Curve3d(E1, c3d1, First1, Last1) || !sae.Curve3d(E2, c3d2, First2, Last2))
    return false;

  gp_Pnt pnt;
  gp_Vec vec1, vec2;
  c3d1->D1(Last1, pnt, vec1);
  c3d2->D1(First2, pnt, vec2);
  if (E1.Orientation() == TopAbs_REVERSED)
    vec1.Reverse();
  if (E2.Orientation() == TopAbs_REVERSED)
    vec2.Reverse();

  double angl = std::abs(vec1.Angle(vec2));
  if (angl > 0.95 * M_PI)
  {
    distMax = .0;
    for (int i = 0; i < NbControl; i++)
    {
      double prm     = ((NbControl - 1 - i) * First1 + i * Last1) / (NbControl - 1);
      gp_Pnt pntCurr = c3d1->Value(prm);

      double p1, p2;
      if (First2 < Last2)
      {
        p1 = First2;
        p2 = Last2;
      }
      else
      {
        p1 = Last2;
        p2 = First2;
      }

      GeomAPI_ProjectPointOnCurve ppc(pntCurr, c3d2, p1, p2);
      double                      newDist = (ppc.NbPoints() ? ppc.LowerDistance() : 0);
      if (newDist > distMax)
        distMax = newDist;
    }

    return true;
  }

  return false;
}

bool ShapeAnalysis_FreeBoundsProperties::FillProperties(
  occ::handle<ShapeAnalysis_FreeBoundData>& fbData,
  const double)
{
  double area, length;
  ContourProperties(fbData->FreeBound(), area, length);

  double r    = 0;
  double aver = 0;

  if (length != 0.)
  {
    double k = area / (length * length);

    if (k != 0.)
    {
      double aux = 1. - 16. * k;
      if (aux >= 0.)
      {
        r    = (1. + sqrt(aux)) / (8. * k);
        aver = length / (2. * r);
        r -= 1.;
      }
    }
  }

  fbData->SetArea(area);
  fbData->SetPerimeter(length);
  fbData->SetRatio(r);
  fbData->SetWidth(aver);

  return true;
}
