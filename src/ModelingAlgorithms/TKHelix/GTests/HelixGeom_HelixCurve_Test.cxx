

#include <gtest/gtest.h>

#include <HelixGeom_HelixCurve.hpp>
#include <HelixGeom_BuilderApproxCurve.hpp>
#include <HelixGeom_BuilderHelixCoil.hpp>
#include <HelixGeom_Tools.hpp>

#include <Geom_BSplineCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_ConstructionError.hpp>

class HelixGeomTest : public ::testing::Test
{
protected:
  void SetUp() override { myTolerance = 1.e-6; }

  double myTolerance;
};

TEST_F(HelixGeomTest, HelixCurve_Derivatives)
{
  HelixGeom_HelixCurve aHelix;
  aHelix.Load(0.0, 2.0 * M_PI, 5.0, 2.0, 0.0, true);

  double aParam = M_PI / 2.0;
  gp_Pnt aP;
  gp_Vec aV1, aV2;

  aHelix.D1(aParam, aP, aV1);
  EXPECT_NEAR(aP.X(), 0.0, 1e-15);
  EXPECT_NEAR(aP.Y(), 2.0, 1e-15);
  EXPECT_GT(aV1.Magnitude(), 0.0);

  aHelix.D2(aParam, aP, aV1, aV2);
  EXPECT_NEAR(aP.X(), 0.0, 1e-15);
  EXPECT_NEAR(aP.Y(), 2.0, 1e-15);
  EXPECT_GT(aV2.Magnitude(), 0.0);

  gp_Vec aVN1 = aHelix.DN(aParam, 1);
  gp_Vec aVN2 = aHelix.DN(aParam, 2);

  EXPECT_NEAR(aVN1.X(), aV1.X(), 1e-15);
  EXPECT_NEAR(aVN1.Y(), aV1.Y(), 1e-15);
  EXPECT_NEAR(aVN1.Z(), aV1.Z(), 1e-15);

  EXPECT_NEAR(aVN2.X(), aV2.X(), 1e-15);
  EXPECT_NEAR(aVN2.Y(), aV2.Y(), 1e-15);
  EXPECT_NEAR(aVN2.Z(), aV2.Z(), 1e-15);
}

TEST_F(HelixGeomTest, HelixCurve_ErrorConditions)
{
  HelixGeom_HelixCurve aHelix;

  EXPECT_THROW(aHelix.Load(2.0, 1.0, 5.0, 2.0, 0.0, true), Standard_ConstructionError);

  EXPECT_THROW(aHelix.Load(0.0, 2.0 * M_PI, -1.0, 2.0, 0.0, true), Standard_ConstructionError);

  EXPECT_THROW(aHelix.Load(0.0, 2.0 * M_PI, 5.0, -1.0, 0.0, true), Standard_ConstructionError);

  EXPECT_THROW(aHelix.Load(0.0, 2.0 * M_PI, 5.0, 2.0, M_PI / 2.0, true),
               Standard_ConstructionError);
}

TEST_F(HelixGeomTest, HelixCurve_CounterClockwise)
{
  HelixGeom_HelixCurve aHelix;
  aHelix.Load(0.0, 2.0 * M_PI, 5.0, 2.0, 0.0, false);

  gp_Pnt aP0 = aHelix.Value(0.0);
  gp_Pnt aP1 = aHelix.Value(M_PI / 2.0);

  EXPECT_NEAR(aP0.X(), 2.0, 1e-15);
  EXPECT_NEAR(aP0.Y(), 0.0, 1e-15);

  EXPECT_NEAR(aP1.X(), 0.0, 1e-15);
  EXPECT_NEAR(aP1.Y(), -2.0, 1e-15);
}

TEST_F(HelixGeomTest, HelixCurve_AdaptorInterface)
{
  HelixGeom_HelixCurve aHelix;
  aHelix.Load(0.0, 4.0 * M_PI, 10.0, 3.0, 0.0, true);

  EXPECT_EQ(aHelix.Continuity(), GeomAbs_CN);

  EXPECT_EQ(aHelix.NbIntervals(GeomAbs_C0), 1);
  EXPECT_EQ(aHelix.NbIntervals(GeomAbs_C1), 1);
  EXPECT_EQ(aHelix.NbIntervals(GeomAbs_C2), 1);

  NCollection_Array1<double> anIntervals(1, 2);
  aHelix.Intervals(anIntervals, GeomAbs_C0);
  EXPECT_DOUBLE_EQ(anIntervals(1), 0.0);
  EXPECT_DOUBLE_EQ(anIntervals(2), 4.0 * M_PI);

  EXPECT_THROW(aHelix.Resolution(1.0), Standard_NotImplemented);
  EXPECT_THROW(aHelix.IsClosed(), Standard_NotImplemented);
  EXPECT_THROW(aHelix.IsPeriodic(), Standard_NotImplemented);
  EXPECT_THROW(aHelix.Period(), Standard_DomainError);
}

TEST_F(HelixGeomTest, BuilderHelixCoil_Approximation)
{
  HelixGeom_BuilderHelixCoil aBuilder;

  aBuilder.SetTolerance(myTolerance);
  aBuilder.SetApproxParameters(GeomAbs_C2, 8, 100);
  aBuilder.SetCurveParameters(0.0, 2.0 * M_PI, 20.0, 5.0, 0.05, true);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);
  EXPECT_LE(aBuilder.ToleranceReached(), 0.1);

  const NCollection_Sequence<occ::handle<Geom_Curve>>& aCurves = aBuilder.Curves();
  EXPECT_EQ(aCurves.Length(), 1);

  occ::handle<Geom_Curve> aCurve = aCurves(1);
  EXPECT_FALSE(aCurve.IsNull());

  occ::handle<Geom_BSplineCurve> aBSpline = occ::down_cast<Geom_BSplineCurve>(aCurve);
  EXPECT_FALSE(aBSpline.IsNull());

  EXPECT_LE(aBSpline->Degree(), 8);
  EXPECT_GT(aBSpline->NbPoles(), 0);
}

TEST_F(HelixGeomTest, Tools_ApprCurve3D)
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

TEST_F(HelixGeomTest, Tools_DifferentContinuity)
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

TEST_F(HelixGeomTest, BuilderHelixCoil_DefaultParameters)
{
  HelixGeom_BuilderHelixCoil aBuilder;

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  GeomAbs_Shape aCont;
  int           aMaxDegree, aMaxSeg;
  aBuilder.ApproxParameters(aCont, aMaxDegree, aMaxSeg);

  EXPECT_EQ(aCont, GeomAbs_C2);
  EXPECT_EQ(aMaxDegree, 8);
  EXPECT_EQ(aMaxSeg, 150);

  EXPECT_EQ(aBuilder.Tolerance(), 0.0001);
}

TEST_F(HelixGeomTest, BuilderHelixCoil_ParameterSymmetry)
{
  HelixGeom_BuilderHelixCoil aBuilder;

  double aT1 = 0.5, aT2 = 5.5, aPitch = 12.5, aRStart = 3.5, aTaperAngle = 0.15;
  bool   aIsClockwise = false;

  aBuilder.SetCurveParameters(aT1, aT2, aPitch, aRStart, aTaperAngle, aIsClockwise);

  double aT1_out, aT2_out, aPitch_out, aRStart_out, aTaperAngle_out;
  bool   aIsClockwise_out;

  aBuilder
    .CurveParameters(aT1_out, aT2_out, aPitch_out, aRStart_out, aTaperAngle_out, aIsClockwise_out);

  EXPECT_DOUBLE_EQ(aT1, aT1_out);
  EXPECT_DOUBLE_EQ(aT2, aT2_out);
  EXPECT_DOUBLE_EQ(aPitch, aPitch_out);
  EXPECT_DOUBLE_EQ(aRStart, aRStart_out);
  EXPECT_DOUBLE_EQ(aTaperAngle, aTaperAngle_out);
  EXPECT_EQ(aIsClockwise, aIsClockwise_out);
}
