

#include <Geom2dHash_CurveHasher.hpp>

#include <Standard_CStringHasher.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2d_OffsetCurve.hpp>

#include <Geom2dHash_LineHasher.hpp>
#include <Geom2dHash_CircleHasher.hpp>
#include <Geom2dHash_EllipseHasher.hpp>
#include <Geom2dHash_HyperbolaHasher.hpp>
#include <Geom2dHash_ParabolaHasher.hpp>
#include <Geom2dHash_BezierCurveHasher.hpp>
#include <Geom2dHash_BSplineCurveHasher.hpp>
#include <Geom2dHash_TrimmedCurveHasher.hpp>
#include <Geom2dHash_OffsetCurveHasher.hpp>

std::size_t Geom2dHash_CurveHasher::operator()(
  const occ::handle<Geom2d_Curve>& theCurve) const noexcept
{
  if (theCurve.IsNull())
  {
    return 0;
  }

  if (occ::handle<Geom2d_Line> aLine = occ::down_cast<Geom2d_Line>(theCurve))
  {
    return Geom2dHash_LineHasher{}(aLine);
  }
  if (occ::handle<Geom2d_Circle> aCircle = occ::down_cast<Geom2d_Circle>(theCurve))
  {
    return Geom2dHash_CircleHasher{}(aCircle);
  }
  if (occ::handle<Geom2d_Ellipse> anEllipse = occ::down_cast<Geom2d_Ellipse>(theCurve))
  {
    return Geom2dHash_EllipseHasher{}(anEllipse);
  }
  if (occ::handle<Geom2d_Hyperbola> aHyperbola = occ::down_cast<Geom2d_Hyperbola>(theCurve))
  {
    return Geom2dHash_HyperbolaHasher{}(aHyperbola);
  }
  if (occ::handle<Geom2d_Parabola> aParabola = occ::down_cast<Geom2d_Parabola>(theCurve))
  {
    return Geom2dHash_ParabolaHasher{}(aParabola);
  }
  if (occ::handle<Geom2d_BezierCurve> aBezier = occ::down_cast<Geom2d_BezierCurve>(theCurve))
  {
    return Geom2dHash_BezierCurveHasher{}(aBezier);
  }
  if (occ::handle<Geom2d_BSplineCurve> aBSpline = occ::down_cast<Geom2d_BSplineCurve>(theCurve))
  {
    return Geom2dHash_BSplineCurveHasher{}(aBSpline);
  }
  if (occ::handle<Geom2d_TrimmedCurve> aTrimmed = occ::down_cast<Geom2d_TrimmedCurve>(theCurve))
  {
    return Geom2dHash_TrimmedCurveHasher{}(aTrimmed);
  }
  if (occ::handle<Geom2d_OffsetCurve> anOffset = occ::down_cast<Geom2d_OffsetCurve>(theCurve))
  {
    return Geom2dHash_OffsetCurveHasher{}(anOffset);
  }

  return Standard_CStringHasher{}(theCurve->DynamicType()->Name());
}

bool Geom2dHash_CurveHasher::operator()(const occ::handle<Geom2d_Curve>& theCurve1,
                                        const occ::handle<Geom2d_Curve>& theCurve2) const noexcept
{
  if (theCurve1.IsNull() || theCurve2.IsNull())
  {
    return theCurve1.IsNull() && theCurve2.IsNull();
  }

  if (theCurve1 == theCurve2)
  {
    return true;
  }

  if (theCurve1->DynamicType() != theCurve2->DynamicType())
  {
    return false;
  }

  if (occ::handle<Geom2d_Line> aLine1 = occ::down_cast<Geom2d_Line>(theCurve1))
  {
    return Geom2dHash_LineHasher{}(aLine1, occ::down_cast<Geom2d_Line>(theCurve2));
  }
  if (occ::handle<Geom2d_Circle> aCircle1 = occ::down_cast<Geom2d_Circle>(theCurve1))
  {
    return Geom2dHash_CircleHasher{}(aCircle1, occ::down_cast<Geom2d_Circle>(theCurve2));
  }
  if (occ::handle<Geom2d_Ellipse> anEllipse1 = occ::down_cast<Geom2d_Ellipse>(theCurve1))
  {
    return Geom2dHash_EllipseHasher{}(anEllipse1, occ::down_cast<Geom2d_Ellipse>(theCurve2));
  }
  if (occ::handle<Geom2d_Hyperbola> aHyp1 = occ::down_cast<Geom2d_Hyperbola>(theCurve1))
  {
    return Geom2dHash_HyperbolaHasher{}(aHyp1, occ::down_cast<Geom2d_Hyperbola>(theCurve2));
  }
  if (occ::handle<Geom2d_Parabola> aPar1 = occ::down_cast<Geom2d_Parabola>(theCurve1))
  {
    return Geom2dHash_ParabolaHasher{}(aPar1, occ::down_cast<Geom2d_Parabola>(theCurve2));
  }
  if (occ::handle<Geom2d_BezierCurve> aBez1 = occ::down_cast<Geom2d_BezierCurve>(theCurve1))
  {
    return Geom2dHash_BezierCurveHasher{}(aBez1, occ::down_cast<Geom2d_BezierCurve>(theCurve2));
  }
  if (occ::handle<Geom2d_BSplineCurve> aBSpl1 = occ::down_cast<Geom2d_BSplineCurve>(theCurve1))
  {
    return Geom2dHash_BSplineCurveHasher{}(aBSpl1, occ::down_cast<Geom2d_BSplineCurve>(theCurve2));
  }
  if (occ::handle<Geom2d_TrimmedCurve> aTrim1 = occ::down_cast<Geom2d_TrimmedCurve>(theCurve1))
  {
    return Geom2dHash_TrimmedCurveHasher{}(aTrim1, occ::down_cast<Geom2d_TrimmedCurve>(theCurve2));
  }
  if (occ::handle<Geom2d_OffsetCurve> aOff1 = occ::down_cast<Geom2d_OffsetCurve>(theCurve1))
  {
    return Geom2dHash_OffsetCurveHasher{}(aOff1, occ::down_cast<Geom2d_OffsetCurve>(theCurve2));
  }

  return theCurve1.get() == theCurve2.get();
}
