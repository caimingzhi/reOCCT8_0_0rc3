#include <BRepApprox_ApproxLine.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <gp_Pnt2d.hpp>
#include <IntSurf_LineOn2S.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepApprox_ApproxLine, Standard_Transient)

BRepApprox_ApproxLine::BRepApprox_ApproxLine(const occ::handle<Geom_BSplineCurve>&   CurveXYZ,
                                             const occ::handle<Geom2d_BSplineCurve>& CurveUV1,
                                             const occ::handle<Geom2d_BSplineCurve>& CurveUV2)
{
  myCurveXYZ = CurveXYZ;
  myCurveUV1 = CurveUV1;
  myCurveUV2 = CurveUV2;
}

BRepApprox_ApproxLine::BRepApprox_ApproxLine(const occ::handle<IntSurf_LineOn2S>& lin, const bool)
    : myLineOn2S(lin)
{
}

int BRepApprox_ApproxLine::NbPnts() const
{
  if (!myCurveXYZ.IsNull())
    return (myCurveXYZ->NbPoles());
  if (!myCurveUV1.IsNull())
    return (myCurveUV1->NbPoles());
  if (!myCurveUV2.IsNull())
    return (myCurveUV2->NbPoles());
  return (myLineOn2S->NbPoints());
}

IntSurf_PntOn2S BRepApprox_ApproxLine::Point(const int Index)
{
  if (!myLineOn2S.IsNull())
  {
    if (myLineOn2S->NbPoints())
    {
      return (myLineOn2S->Value(Index));
    }
  }
  gp_Pnt2d P1, P2;
  gp_Pnt   P;
  if (!myCurveXYZ.IsNull())
    P = myCurveXYZ->Pole(Index);
  if (!myCurveUV1.IsNull())
    P1 = myCurveUV1->Pole(Index);
  if (!myCurveUV2.IsNull())
    P2 = myCurveUV2->Pole(Index);

  IntSurf_PntOn2S aPntOn2S;
  aPntOn2S.SetValue(P, P1.X(), P1.Y(), P2.X(), P2.Y());

  return aPntOn2S;
}
