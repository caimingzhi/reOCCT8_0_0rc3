

#include <gtest/gtest.h>

#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Line.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomConvert.hpp>
#include <GeomConvert_CompCurveToBSplineCurve.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

TEST(GeomConvert_CompCurveToBSplineCurveTest, ConcatenateClampedBSplines)
{

  NCollection_Array1<gp_Pnt> aPoles1(1, 4);
  aPoles1(1) = gp_Pnt(0., 0., 0.);
  aPoles1(2) = gp_Pnt(1., 1., 0.);
  aPoles1(3) = gp_Pnt(2., 1., 0.);
  aPoles1(4) = gp_Pnt(3., 0., 0.);

  NCollection_Array1<double> aKnots1(1, 2);
  aKnots1(1) = 0.;
  aKnots1(2) = 1.;

  NCollection_Array1<int> aMults1(1, 2);
  aMults1(1) = 4;
  aMults1(2) = 4;

  occ::handle<Geom_BSplineCurve> aCurve1 = new Geom_BSplineCurve(aPoles1, aKnots1, aMults1, 3);

  NCollection_Array1<gp_Pnt> aPoles2(1, 4);
  aPoles2(1) = gp_Pnt(3., 0., 0.);
  aPoles2(2) = gp_Pnt(4., -1., 0.);
  aPoles2(3) = gp_Pnt(5., -1., 0.);
  aPoles2(4) = gp_Pnt(6., 0., 0.);

  occ::handle<Geom_BSplineCurve> aCurve2 = new Geom_BSplineCurve(aPoles2, aKnots1, aMults1, 3);

  GeomConvert_CompCurveToBSplineCurve aConcat(aCurve1);
  const bool                          isAdded = aConcat.Add(aCurve2, Precision::Confusion());

  EXPECT_TRUE(isAdded) << "Should successfully concatenate clamped B-splines";

  occ::handle<Geom_BSplineCurve> aResult = aConcat.BSplineCurve();
  ASSERT_FALSE(aResult.IsNull()) << "Result curve should not be null";

  const gp_Pnt aStart = aResult->StartPoint();
  const gp_Pnt aEnd   = aResult->EndPoint();

  EXPECT_NEAR(aStart.Distance(gp_Pnt(0., 0., 0.)), 0., Precision::Confusion());
  EXPECT_NEAR(aEnd.Distance(gp_Pnt(6., 0., 0.)), 0., Precision::Confusion());
}

TEST(GeomConvert_CompCurveToBSplineCurveTest, ConcatenateTrimmedCircleArcs)
{

  gp_Circ aCirc(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);

  occ::handle<Geom_Circle> aGeomCircle = new Geom_Circle(aCirc);

  occ::handle<Geom_TrimmedCurve> aArc1 = new Geom_TrimmedCurve(aGeomCircle, 0., M_PI / 2.);

  occ::handle<Geom_TrimmedCurve> aArc2 = new Geom_TrimmedCurve(aGeomCircle, M_PI / 2., M_PI);

  const gp_Pnt aArc1End   = aArc1->EndPoint();
  const gp_Pnt aArc2Start = aArc2->StartPoint();
  EXPECT_NEAR(aArc1End.Distance(aArc2Start), 0., Precision::Confusion())
    << "Arcs should share an endpoint";

  GeomConvert_CompCurveToBSplineCurve aConcat(aArc1);
  const bool                          isAdded = aConcat.Add(aArc2, Precision::Confusion());

  EXPECT_TRUE(isAdded) << "Should successfully concatenate trimmed circle arcs";

  occ::handle<Geom_BSplineCurve> aResult = aConcat.BSplineCurve();
  ASSERT_FALSE(aResult.IsNull()) << "Result curve should not be null";

  const gp_Pnt aStart = aResult->StartPoint();
  const gp_Pnt aEnd   = aResult->EndPoint();

  EXPECT_NEAR(aStart.Distance(gp_Pnt(5., 0., 0.)), 0., Precision::Confusion());
  EXPECT_NEAR(aEnd.Distance(gp_Pnt(-5., 0., 0.)), 0., Precision::Confusion());
}

TEST(GeomConvert_CompCurveToBSplineCurveTest, ConcatenateWithReversal)
{

  NCollection_Array1<gp_Pnt> aPoles1(1, 4);
  aPoles1(1) = gp_Pnt(0., 0., 0.);
  aPoles1(2) = gp_Pnt(1., 1., 0.);
  aPoles1(3) = gp_Pnt(2., 1., 0.);
  aPoles1(4) = gp_Pnt(3., 0., 0.);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.;
  aKnots(2) = 1.;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  occ::handle<Geom_BSplineCurve> aCurve1 = new Geom_BSplineCurve(aPoles1, aKnots, aMults, 3);

  NCollection_Array1<gp_Pnt> aPoles2(1, 4);
  aPoles2(1) = gp_Pnt(6., 0., 0.);
  aPoles2(2) = gp_Pnt(5., -1., 0.);
  aPoles2(3) = gp_Pnt(4., -1., 0.);
  aPoles2(4) = gp_Pnt(3., 0., 0.);

  occ::handle<Geom_BSplineCurve> aCurve2 = new Geom_BSplineCurve(aPoles2, aKnots, aMults, 3);

  GeomConvert_CompCurveToBSplineCurve aConcat(aCurve1);
  const bool                          isAdded = aConcat.Add(aCurve2, Precision::Confusion());

  EXPECT_TRUE(isAdded) << "Should successfully concatenate curves with reversal";

  occ::handle<Geom_BSplineCurve> aResult = aConcat.BSplineCurve();
  ASSERT_FALSE(aResult.IsNull()) << "Result curve should not be null";

  const gp_Pnt aStart = aResult->StartPoint();
  const gp_Pnt aEnd   = aResult->EndPoint();

  EXPECT_NEAR(aStart.Distance(gp_Pnt(0., 0., 0.)), 0., Precision::Confusion());
  EXPECT_NEAR(aEnd.Distance(gp_Pnt(6., 0., 0.)), 0., Precision::Confusion());
}

TEST(GeomConvert_CompCurveToBSplineCurveTest, FailsForDisjointCurves)
{

  NCollection_Array1<gp_Pnt> aPoles1(1, 4);
  aPoles1(1) = gp_Pnt(0., 0., 0.);
  aPoles1(2) = gp_Pnt(1., 1., 0.);
  aPoles1(3) = gp_Pnt(2., 1., 0.);
  aPoles1(4) = gp_Pnt(3., 0., 0.);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.;
  aKnots(2) = 1.;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  occ::handle<Geom_BSplineCurve> aCurve1 = new Geom_BSplineCurve(aPoles1, aKnots, aMults, 3);

  NCollection_Array1<gp_Pnt> aPoles2(1, 4);
  aPoles2(1) = gp_Pnt(10., 0., 0.);
  aPoles2(2) = gp_Pnt(11., 1., 0.);
  aPoles2(3) = gp_Pnt(12., 1., 0.);
  aPoles2(4) = gp_Pnt(13., 0., 0.);

  occ::handle<Geom_BSplineCurve> aCurve2 = new Geom_BSplineCurve(aPoles2, aKnots, aMults, 3);

  GeomConvert_CompCurveToBSplineCurve aConcat(aCurve1);
  const bool                          isAdded = aConcat.Add(aCurve2, Precision::Confusion());

  EXPECT_FALSE(isAdded) << "Should fail to concatenate disjoint curves";
}

TEST(GeomConvert_CompCurveToBSplineCurveTest, ConcatenateNonClampedBSpline_Bug30007)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 6);
  aPoles(1) = gp_Pnt(0., 0., 0.);
  aPoles(2) = gp_Pnt(1., 2., 0.);
  aPoles(3) = gp_Pnt(2., 2., 0.);
  aPoles(4) = gp_Pnt(3., 2., 0.);
  aPoles(5) = gp_Pnt(4., 2., 0.);
  aPoles(6) = gp_Pnt(5., 0., 0.);

  NCollection_Array1<double> aKnots(1, 4);
  aKnots(1) = 0.;
  aKnots(2) = 0.33;
  aKnots(3) = 0.67;
  aKnots(4) = 1.;

  NCollection_Array1<int> aMults(1, 4);
  aMults(1) = 4;
  aMults(2) = 1;
  aMults(3) = 1;
  aMults(4) = 4;

  occ::handle<Geom_BSplineCurve> aCurve1 = new Geom_BSplineCurve(aPoles, aKnots, aMults, 3);

  const gp_Pnt aCurve1End = aCurve1->EndPoint();

  NCollection_Array1<gp_Pnt> aPoles2(1, 4);
  aPoles2(1) = aCurve1End;
  aPoles2(2) = gp_Pnt(6., -1., 0.);
  aPoles2(3) = gp_Pnt(7., -1., 0.);
  aPoles2(4) = gp_Pnt(8., 0., 0.);

  NCollection_Array1<double> aKnots2(1, 2);
  aKnots2(1) = 0.;
  aKnots2(2) = 1.;

  NCollection_Array1<int> aMults2(1, 2);
  aMults2(1) = 4;
  aMults2(2) = 4;

  occ::handle<Geom_BSplineCurve> aCurve2 = new Geom_BSplineCurve(aPoles2, aKnots2, aMults2, 3);

  GeomConvert_CompCurveToBSplineCurve aConcat(aCurve1);
  const bool                          isAdded = aConcat.Add(aCurve2, Precision::Confusion());

  EXPECT_TRUE(isAdded) << "Should concatenate using actual endpoints, not poles";

  occ::handle<Geom_BSplineCurve> aResult = aConcat.BSplineCurve();
  ASSERT_FALSE(aResult.IsNull()) << "Result curve should not be null";

  const gp_Pnt aStart = aResult->StartPoint();
  const gp_Pnt aEnd   = aResult->EndPoint();

  EXPECT_NEAR(aStart.Distance(aCurve1->StartPoint()), 0., Precision::Confusion());
  EXPECT_NEAR(aEnd.Distance(gp_Pnt(8., 0., 0.)), 0., Precision::Confusion());
}

TEST(GeomConvert_CompCurveToBSplineCurveTest, PrependCurve)
{

  NCollection_Array1<gp_Pnt> aPoles1(1, 4);
  aPoles1(1) = gp_Pnt(3., 0., 0.);
  aPoles1(2) = gp_Pnt(4., 1., 0.);
  aPoles1(3) = gp_Pnt(5., 1., 0.);
  aPoles1(4) = gp_Pnt(6., 0., 0.);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.;
  aKnots(2) = 1.;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  occ::handle<Geom_BSplineCurve> aCurve1 = new Geom_BSplineCurve(aPoles1, aKnots, aMults, 3);

  NCollection_Array1<gp_Pnt> aPoles2(1, 4);
  aPoles2(1) = gp_Pnt(0., 0., 0.);
  aPoles2(2) = gp_Pnt(1., -1., 0.);
  aPoles2(3) = gp_Pnt(2., -1., 0.);
  aPoles2(4) = gp_Pnt(3., 0., 0.);

  occ::handle<Geom_BSplineCurve> aCurve2 = new Geom_BSplineCurve(aPoles2, aKnots, aMults, 3);

  GeomConvert_CompCurveToBSplineCurve aConcat(aCurve1);
  const bool                          isAdded = aConcat.Add(aCurve2, Precision::Confusion());

  EXPECT_TRUE(isAdded) << "Should successfully prepend curve";

  occ::handle<Geom_BSplineCurve> aResult = aConcat.BSplineCurve();
  ASSERT_FALSE(aResult.IsNull()) << "Result curve should not be null";

  const gp_Pnt aStart = aResult->StartPoint();
  const gp_Pnt aEnd   = aResult->EndPoint();

  EXPECT_NEAR(aStart.Distance(gp_Pnt(0., 0., 0.)), 0., Precision::Confusion());
  EXPECT_NEAR(aEnd.Distance(gp_Pnt(6., 0., 0.)), 0., Precision::Confusion());
}

TEST(GeomConvert_CompCurveToBSplineCurveTest, EmptyInitialCurve)
{

  GeomConvert_CompCurveToBSplineCurve aConcat;

  NCollection_Array1<gp_Pnt> aPoles(1, 4);
  aPoles(1) = gp_Pnt(0., 0., 0.);
  aPoles(2) = gp_Pnt(1., 1., 0.);
  aPoles(3) = gp_Pnt(2., 1., 0.);
  aPoles(4) = gp_Pnt(3., 0., 0.);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.;
  aKnots(2) = 1.;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  occ::handle<Geom_BSplineCurve> aCurve = new Geom_BSplineCurve(aPoles, aKnots, aMults, 3);

  const bool isAdded = aConcat.Add(aCurve, Precision::Confusion());

  EXPECT_TRUE(isAdded) << "Should successfully add to empty converter";

  occ::handle<Geom_BSplineCurve> aResult = aConcat.BSplineCurve();
  ASSERT_FALSE(aResult.IsNull()) << "Result curve should not be null";
}

TEST(GeomConvert_CompCurveToBSplineCurveTest, ClearAndReuse)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 4);
  aPoles(1) = gp_Pnt(0., 0., 0.);
  aPoles(2) = gp_Pnt(1., 1., 0.);
  aPoles(3) = gp_Pnt(2., 1., 0.);
  aPoles(4) = gp_Pnt(3., 0., 0.);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.;
  aKnots(2) = 1.;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  occ::handle<Geom_BSplineCurve> aCurve = new Geom_BSplineCurve(aPoles, aKnots, aMults, 3);

  GeomConvert_CompCurveToBSplineCurve aConcat(aCurve);

  ASSERT_FALSE(aConcat.BSplineCurve().IsNull());

  aConcat.Clear();
  EXPECT_TRUE(aConcat.BSplineCurve().IsNull()) << "Curve should be null after Clear()";

  const bool isAdded = aConcat.Add(aCurve, Precision::Confusion());
  EXPECT_TRUE(isAdded) << "Should successfully add after Clear()";
  EXPECT_FALSE(aConcat.BSplineCurve().IsNull()) << "Curve should exist after re-adding";
}
