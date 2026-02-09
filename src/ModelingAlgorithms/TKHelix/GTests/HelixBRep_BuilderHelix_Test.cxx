

#include <gtest/gtest.h>

#include <HelixBRep_BuilderHelix.hpp>
#include <HelixGeom_BuilderHelix.hpp>
#include <HelixGeom_BuilderHelixCoil.hpp>
#include <HelixGeom_HelixCurve.hpp>
#include <HelixGeom_Tools.hpp>

#include <BRep_Tool.hpp>
#include <BRepGProp.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Ax3.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <GProp_GProps.hpp>
#include <Precision.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Wire.hpp>
#include <TopExp_Explorer.hpp>
#include <TopAbs_ShapeEnum.hpp>

class TKHelixTest : public ::testing::Test
{
protected:
  void SetUp() override
  {

    myAxis      = gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));
    myTolerance = 1.e-4;
  }

  int CountShapes(const TopoDS_Shape& theShape, const TopAbs_ShapeEnum theType) const
  {
    int aCount = 0;
    for (TopExp_Explorer anExp(theShape, theType); anExp.More(); anExp.Next())
    {
      aCount++;
    }
    return aCount;
  }

  double ComputeWireLength(const TopoDS_Shape& theWire) const
  {
    GProp_GProps aLProps;
    BRepGProp::LinearProperties(theWire, aLProps);
    return aLProps.Mass();
  }

  gp_Ax3 myAxis;
  double myTolerance;
};

TEST_F(TKHelixTest, HelixGeomHelixCurve_Basic)
{
  HelixGeom_HelixCurve aHelix;

  EXPECT_DOUBLE_EQ(aHelix.FirstParameter(), 0.0);
  EXPECT_DOUBLE_EQ(aHelix.LastParameter(), 2.0 * M_PI);

  gp_Pnt aP0 = aHelix.Value(0.0);
  EXPECT_DOUBLE_EQ(aP0.X(), 1.0);
  EXPECT_DOUBLE_EQ(aP0.Y(), 0.0);
  EXPECT_DOUBLE_EQ(aP0.Z(), 0.0);

  gp_Pnt aP1 = aHelix.Value(M_PI);
  EXPECT_DOUBLE_EQ(aP1.X(), -1.0);
  EXPECT_NEAR(aP1.Y(), 0.0, 1e-15);
  EXPECT_DOUBLE_EQ(aP1.Z(), M_PI / (2.0 * M_PI));
}

TEST_F(TKHelixTest, HelixGeomHelixCurve_CustomParameters)
{
  HelixGeom_HelixCurve aHelix;
  aHelix.Load(0.0, 4.0 * M_PI, 10.0, 5.0, 0.0, true);

  EXPECT_DOUBLE_EQ(aHelix.FirstParameter(), 0.0);
  EXPECT_DOUBLE_EQ(aHelix.LastParameter(), 4.0 * M_PI);

  gp_Pnt aP0 = aHelix.Value(0.0);
  EXPECT_DOUBLE_EQ(aP0.X(), 5.0);
  EXPECT_DOUBLE_EQ(aP0.Y(), 0.0);
  EXPECT_DOUBLE_EQ(aP0.Z(), 0.0);

  gp_Pnt aP1 = aHelix.Value(4.0 * M_PI);
  EXPECT_DOUBLE_EQ(aP1.X(), 5.0);
  EXPECT_NEAR(aP1.Y(), 0.0, 1e-14);
  EXPECT_DOUBLE_EQ(aP1.Z(), 20.0);
}

TEST_F(TKHelixTest, HelixGeomHelixCurve_TaperedHelix)
{
  HelixGeom_HelixCurve aHelix;
  double               aTaperAngle = 0.1;
  aHelix.Load(0.0, 2.0 * M_PI, 5.0, 2.0, aTaperAngle, true);

  gp_Pnt aP0 = aHelix.Value(0.0);
  EXPECT_DOUBLE_EQ(aP0.X(), 2.0);

  gp_Pnt aP1             = aHelix.Value(2.0 * M_PI);
  double aExpectedRadius = 2.0 + (5.0 / (2.0 * M_PI)) * tan(aTaperAngle) * (2.0 * M_PI);
  EXPECT_DOUBLE_EQ(aP1.X(), aExpectedRadius);
}

TEST_F(TKHelixTest, HelixGeomBuilderHelixCoil_Basic)
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

TEST_F(TKHelixTest, HelixGeomBuilderHelix_SingleCoil)
{
  HelixGeom_BuilderHelix aBuilder;

  gp_Ax2 aPosition(gp_Pnt(0., 0., 0.), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));
  aBuilder.SetPosition(aPosition);
  aBuilder.SetTolerance(myTolerance);
  aBuilder.SetCurveParameters(0.0, 2.0 * M_PI, 10.0, 5.0, 0.0, true);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const NCollection_Sequence<occ::handle<Geom_Curve>>& aCurves = aBuilder.Curves();
  EXPECT_EQ(aCurves.Length(), 1);
}

TEST_F(TKHelixTest, HelixGeomBuilderHelix_MultipleCoils)
{
  HelixGeom_BuilderHelix aBuilder;

  gp_Ax2 aPosition(gp_Pnt(0., 0., 0.), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));
  aBuilder.SetPosition(aPosition);
  aBuilder.SetTolerance(myTolerance);

  aBuilder.SetCurveParameters(0.0, 6.0 * M_PI, 10.0, 5.0, 0.0, true);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const NCollection_Sequence<occ::handle<Geom_Curve>>& aCurves = aBuilder.Curves();
  EXPECT_EQ(aCurves.Length(), 3);
}

TEST_F(TKHelixTest, HelixBRepBuilder_PureCylindricalHelix)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aHeights(1, 1);
  aHeights(1) = 100.0;

  NCollection_Array1<double> aPitches(1, 1);
  aPitches(1) = 20.0;

  NCollection_Array1<bool> aIsPitches(1, 1);
  aIsPitches(1) = true;

  aBuilder.SetParameters(myAxis, 100.0, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aResult = aBuilder.Shape();
  EXPECT_FALSE(aResult.IsNull());
  EXPECT_EQ(aResult.ShapeType(), TopAbs_WIRE);

  int aNbEdges = CountShapes(aResult, TopAbs_EDGE);
  EXPECT_GT(aNbEdges, 0);

  double aWireLength     = ComputeWireLength(aResult);
  double aCircumference  = M_PI * 100.0;
  double aTurns          = 100.0 / 20.0;
  double aExpectedLength = aTurns * sqrt(aCircumference * aCircumference + 20.0 * 20.0);

  EXPECT_NEAR(aWireLength, aExpectedLength, aExpectedLength * 0.01);
}

TEST_F(TKHelixTest, HelixBRepBuilder_SpiralHelix)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aHeights(1, 1);
  aHeights(1) = 100.0;

  NCollection_Array1<double> aPitches(1, 1);
  aPitches(1) = 10.0;

  NCollection_Array1<bool> aIsPitches(1, 1);
  aIsPitches(1) = true;

  aBuilder.SetParameters(myAxis, 100.0, 20.0, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aResult = aBuilder.Shape();
  EXPECT_FALSE(aResult.IsNull());
  EXPECT_EQ(aResult.ShapeType(), TopAbs_WIRE);

  int aNbEdges = CountShapes(aResult, TopAbs_EDGE);
  EXPECT_GT(aNbEdges, 0);
}

TEST_F(TKHelixTest, HelixBRepBuilder_MultiPartHelix)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aDiams(1, 4);
  aDiams(1) = 100.0;
  aDiams(2) = 80.0;
  aDiams(3) = 60.0;
  aDiams(4) = 40.0;

  NCollection_Array1<double> aHeights(1, 3);
  aHeights(1) = 30.0;
  aHeights(2) = 40.0;
  aHeights(3) = 30.0;

  NCollection_Array1<double> aPitches(1, 3);
  aPitches(1) = 10.0;
  aPitches(2) = 15.0;
  aPitches(3) = 10.0;

  NCollection_Array1<bool> aIsPitches(1, 3);
  aIsPitches(1) = true;
  aIsPitches(2) = true;
  aIsPitches(3) = true;

  aBuilder.SetParameters(myAxis, aDiams, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aResult = aBuilder.Shape();
  EXPECT_FALSE(aResult.IsNull());
  EXPECT_EQ(aResult.ShapeType(), TopAbs_WIRE);

  int aNbEdges = CountShapes(aResult, TopAbs_EDGE);
  EXPECT_GT(aNbEdges, 2);
}

TEST_F(TKHelixTest, HelixBRepBuilder_NumberOfTurnsInterface)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aPitches(1, 1);
  aPitches(1) = 20.0;

  NCollection_Array1<double> aNbTurns(1, 1);
  aNbTurns(1) = 5.0;

  aBuilder.SetParameters(myAxis, 100.0, aPitches, aNbTurns);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aResult = aBuilder.Shape();
  EXPECT_FALSE(aResult.IsNull());

  double aWireLength     = ComputeWireLength(aResult);
  double aCircumference  = M_PI * 100.0;
  double aExpectedLength = 5.0 * sqrt(aCircumference * aCircumference + 20.0 * 20.0);

  EXPECT_NEAR(aWireLength, aExpectedLength, aExpectedLength * 0.01);
}

TEST_F(TKHelixTest, HelixGeomTools_ApprHelix)
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

TEST_F(TKHelixTest, HelixBRepBuilder_ErrorConditions)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aHeights(1, 1);
  aHeights(1) = 1.e-6;

  NCollection_Array1<double> aPitches(1, 1);
  aPitches(1) = 10.0;

  NCollection_Array1<bool> aIsPitches(1, 1);
  aIsPitches(1) = true;

  aBuilder.SetParameters(myAxis, 100.0, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_NE(aBuilder.ErrorStatus(), 0);
}

TEST_F(TKHelixTest, HelixBRepBuilder_ZeroPitch)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aHeights(1, 1);
  aHeights(1) = 100.0;

  NCollection_Array1<double> aPitches(1, 1);
  aPitches(1) = 0.0;

  NCollection_Array1<bool> aIsPitches(1, 1);
  aIsPitches(1) = true;

  aBuilder.SetParameters(myAxis, 100.0, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_NE(aBuilder.ErrorStatus(), 0);
}

TEST_F(TKHelixTest, HelixBRepBuilder_ToleranceReached)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aHeights(1, 1);
  aHeights(1) = 100.0;

  NCollection_Array1<double> aPitches(1, 1);
  aPitches(1) = 20.0;

  NCollection_Array1<bool> aIsPitches(1, 1);
  aIsPitches(1) = true;

  double aVeryTightTolerance = 1.e-8;
  aBuilder.SetParameters(myAxis, 100.0, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(aVeryTightTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  if (aBuilder.ErrorStatus() == 0)
  {
    double aToleranceReached = aBuilder.ToleranceReached();
    EXPECT_GT(aToleranceReached, 0.0);
  }
}
