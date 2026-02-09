

#include <Geom2d_Circle.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAPI_InterCurveCurve.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <Precision.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>

#include <gtest/gtest.h>

TEST(Geom2dAPI_InterCurveCurve_Test, OCC24889_IntersectionParameterWithinLimits)
{

  occ::handle<Geom2d_Circle> aCircle1 =
    new Geom2d_Circle(gp_Ax22d(gp_Pnt2d(25, -25), gp_Dir2d(gp_Dir2d::D::X), gp_Dir2d(-0, 1)), 155);

  occ::handle<Geom2d_Circle> aCircle2 =
    new Geom2d_Circle(gp_Ax22d(gp_Pnt2d(25, 25), gp_Dir2d(gp_Dir2d::D::X), gp_Dir2d(-0, 1)), 155);

  occ::handle<Geom2d_TrimmedCurve> aTrim1 =
    new Geom2d_TrimmedCurve(aCircle1, 1.57079632679490, 2.97959469729228);
  occ::handle<Geom2d_TrimmedCurve> aTrim2 =
    new Geom2d_TrimmedCurve(aCircle2, 3.30359060633978, 4.71238898038469);

  constexpr double          aTol = Precision::Confusion();
  Geom2dAPI_InterCurveCurve aIntTool(aTrim1, aTrim2, aTol);

  ASSERT_GT(aIntTool.NbPoints(), 0) << "Intersection should find at least one point";

  const IntRes2d_IntersectionPoint& aIntPnt = aIntTool.Intersector().Point(1);

  double aParOnC1   = aIntPnt.ParamOnFirst();
  double aParOnC2   = aIntPnt.ParamOnSecond();
  double aFirstPar1 = aTrim1->FirstParameter();
  double aLastPar1  = aTrim1->LastParameter();
  double aFirstPar2 = aTrim2->FirstParameter();
  double aLastPar2  = aTrim2->LastParameter();

  EXPECT_GE(aParOnC1, aFirstPar1) << "IntParameter on curve 1 (" << aParOnC1
                                  << ") should be >= FirstParam (" << aFirstPar1 << ")";
  EXPECT_LE(aParOnC1, aLastPar1) << "IntParameter on curve 1 (" << aParOnC1
                                 << ") should be <= LastParam (" << aLastPar1 << ")";

  EXPECT_GE(aParOnC2, aFirstPar2) << "IntParameter on curve 2 (" << aParOnC2
                                  << ") should be >= FirstParam (" << aFirstPar2 << ")";
  EXPECT_LE(aParOnC2, aLastPar2) << "IntParameter on curve 2 (" << aParOnC2
                                 << ") should be <= LastParam (" << aLastPar2 << ")";

  gp_Pnt2d aP1 = aTrim1->Value(aParOnC1);
  gp_Pnt2d aP2 = aTrim2->Value(aParOnC2);

  double aDist2 = aP1.SquareDistance(aP2);
  EXPECT_LT(aDist2, 1.0e-14) << "Points on both curves at intersection parameters should coincide";
}
