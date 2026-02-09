

#include <gtest/gtest.h>

#include <HelixGeom_BuilderHelixCoil.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Geom_BSplineCurve.hpp>
#include <gp_Pnt.hpp>

class HelixGeom_BuilderHelixCoil_Test : public ::testing::Test
{
protected:
  void SetUp() override { myTolerance = 1.e-4; }

  double myTolerance;
};

TEST_F(HelixGeom_BuilderHelixCoil_Test, BasicConstruction)
{
  HelixGeom_BuilderHelixCoil aBuilder;

  aBuilder.SetTolerance(myTolerance);
  aBuilder.SetCurveParameters(0.0, 2.0 * M_PI, 5.0, 2.0, 0.0, true);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const NCollection_Sequence<occ::handle<Geom_Curve>>& aCurves = aBuilder.Curves();
  EXPECT_EQ(aCurves.Length(), 1);

  occ::handle<Geom_Curve> aCurve = aCurves(1);
  EXPECT_FALSE(aCurve.IsNull());

  gp_Pnt aP1, aP2;
  aCurve->D0(aCurve->FirstParameter(), aP1);
  aCurve->D0(aCurve->LastParameter(), aP2);

  EXPECT_NEAR(aP1.X(), 2.0, myTolerance);
  EXPECT_NEAR(aP1.Y(), 0.0, myTolerance);
  EXPECT_NEAR(aP1.Z(), 0.0, myTolerance);

  EXPECT_NEAR(aP2.X(), 2.0, myTolerance);
  EXPECT_NEAR(aP2.Y(), 0.0, myTolerance);
  EXPECT_NEAR(aP2.Z(), 5.0, myTolerance);
}

TEST_F(HelixGeom_BuilderHelixCoil_Test, DefaultParameters)
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

TEST_F(HelixGeom_BuilderHelixCoil_Test, ParameterSymmetry)
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

TEST_F(HelixGeom_BuilderHelixCoil_Test, TaperedHelix)
{
  HelixGeom_BuilderHelixCoil aBuilder;

  aBuilder.SetTolerance(myTolerance);
  aBuilder.SetApproxParameters(GeomAbs_C2, 8, 100);
  aBuilder.SetCurveParameters(0.0, 4.0 * M_PI, 20.0, 5.0, 0.1, true);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);
  EXPECT_LE(aBuilder.ToleranceReached(), myTolerance * 10);

  const NCollection_Sequence<occ::handle<Geom_Curve>>& aCurves = aBuilder.Curves();
  EXPECT_EQ(aCurves.Length(), 1);

  occ::handle<Geom_Curve> aCurve = aCurves(1);
  EXPECT_FALSE(aCurve.IsNull());

  occ::handle<Geom_BSplineCurve> aBSpline = occ::down_cast<Geom_BSplineCurve>(aCurve);
  EXPECT_FALSE(aBSpline.IsNull());

  EXPECT_LE(aBSpline->Degree(), 8);
  EXPECT_GT(aBSpline->NbPoles(), 0);
}
