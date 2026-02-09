

#include <gtest/gtest.h>

#include <HelixGeom_Tools.hpp>
#include <HelixGeom_HelixCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Pnt.hpp>

class HelixGeom_Tools_Test : public ::testing::Test
{
protected:
  void SetUp() override { myTolerance = 1.e-6; }

  double myTolerance;
};

TEST_F(HelixGeom_Tools_Test, ApprHelix)
{
  occ::handle<Geom_BSplineCurve> aBSpline;
  double                         aMaxError;

  int aResult = HelixGeom_Tools::ApprHelix(0.0,
                                           2.0 * M_PI,
                                           10.0,
                                           5.0,
                                           0.0,
                                           true,
                                           myTolerance,
                                           aBSpline,
                                           aMaxError);

  EXPECT_EQ(aResult, 0);
  EXPECT_FALSE(aBSpline.IsNull());
  EXPECT_LE(aMaxError, myTolerance);

  EXPECT_GT(aBSpline->Degree(), 0);
  EXPECT_GT(aBSpline->NbPoles(), 0);
}

TEST_F(HelixGeom_Tools_Test, ApprCurve3D)
{

  HelixGeom_HelixCurve aHelix;
  aHelix.Load(0.0, 2.0 * M_PI, 10.0, 3.0, 0.0, true);
  occ::handle<HelixGeom_HelixCurve> aHAdaptor = new HelixGeom_HelixCurve(aHelix);

  occ::handle<Geom_BSplineCurve> aBSpline;
  double                         aMaxError;

  int aResult =
    HelixGeom_Tools::ApprCurve3D(aHAdaptor, myTolerance, GeomAbs_C1, 50, 6, aBSpline, aMaxError);

  EXPECT_EQ(aResult, 0);
  EXPECT_FALSE(aBSpline.IsNull());
  EXPECT_LE(aMaxError, myTolerance * 10);

  int aNbSamples = 10;
  for (int i = 0; i <= aNbSamples; i++)
  {
    double aParam =
      aHelix.FirstParameter() + i * (aHelix.LastParameter() - aHelix.FirstParameter()) / aNbSamples;

    gp_Pnt aOrigPnt = aHelix.Value(aParam);

    double aBSplineParam =
      aBSpline->FirstParameter()
      + i * (aBSpline->LastParameter() - aBSpline->FirstParameter()) / aNbSamples;

    gp_Pnt aApproxPnt;
    aBSpline->D0(aBSplineParam, aApproxPnt);

    double aDistance = aOrigPnt.Distance(aApproxPnt);
    EXPECT_LE(aDistance, aMaxError * 2);
  }
}

TEST_F(HelixGeom_Tools_Test, DifferentContinuity)
{
  HelixGeom_HelixCurve aHelix;
  aHelix.Load(0.0, 6.0 * M_PI, 15.0, 4.0, 0.05, true);
  occ::handle<HelixGeom_HelixCurve> aHAdaptor = new HelixGeom_HelixCurve(aHelix);

  occ::handle<Geom_BSplineCurve> aBSplineC0;
  double                         aMaxErrorC0;
  int                            aResultC0 = HelixGeom_Tools::ApprCurve3D(aHAdaptor,
                                               myTolerance,
                                               GeomAbs_C0,
                                               30,
                                               4,
                                               aBSplineC0,
                                               aMaxErrorC0);

  EXPECT_EQ(aResultC0, 0);
  EXPECT_FALSE(aBSplineC0.IsNull());

  occ::handle<Geom_BSplineCurve> aBSplineC2;
  double                         aMaxErrorC2;
  int                            aResultC2 = HelixGeom_Tools::ApprCurve3D(aHAdaptor,
                                               myTolerance,
                                               GeomAbs_C2,
                                               30,
                                               6,
                                               aBSplineC2,
                                               aMaxErrorC2);

  EXPECT_EQ(aResultC2, 0);
  EXPECT_FALSE(aBSplineC2.IsNull());

  EXPECT_GE(aBSplineC2->Degree(), aBSplineC0->Degree());
}
