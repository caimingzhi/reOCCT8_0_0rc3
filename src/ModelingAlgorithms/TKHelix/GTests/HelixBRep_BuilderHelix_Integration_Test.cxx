

#include <gtest/gtest.h>

#include <HelixBRep_BuilderHelix.hpp>

#include <BRep_Tool.hpp>
#include <BRepGProp.hpp>
#include <BRepCheck_Analyzer.hpp>
#include <gp_Ax3.hpp>
#include <GProp_GProps.hpp>
#include <NCollection_Array1.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Wire.hpp>
#include <TopExp_Explorer.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_ConstructionError.hpp>

class HelixBRepTest : public ::testing::Test
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

  void ValidateHelixWire(const TopoDS_Wire& theWire,
                         double             theExpectedLength,
                         double             theTolerance = 0.05) const
  {
    EXPECT_FALSE(theWire.IsNull());
    EXPECT_EQ(theWire.ShapeType(), TopAbs_WIRE);

    int aNbEdges = CountShapes(theWire, TopAbs_EDGE);
    EXPECT_GT(aNbEdges, 0);

    double aWireLength = ComputeWireLength(theWire);
    if (theExpectedLength > 0)
    {
      EXPECT_NEAR(aWireLength, theExpectedLength, theExpectedLength * theTolerance);
    }
  }

  gp_Ax3 myAxis;
  double myTolerance;
};

TEST_F(HelixBRepTest, TCL_Test_A1_PureCylindricalHelix)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aHeights(1, 1);
  aHeights(1) = 100.0;

  NCollection_Array1<double> aPitches(1, 1);
  aPitches(1) = 5.0;

  NCollection_Array1<bool> aIsPitches(1, 1);
  aIsPitches(1) = false;

  aBuilder.SetParameters(myAxis, 100.0, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aHelixWire = aBuilder.Shape();
  EXPECT_FALSE(aHelixWire.IsNull());
  EXPECT_EQ(aHelixWire.ShapeType(), TopAbs_WIRE);

  double aCircumference  = M_PI * 100.0;
  double aTurns          = 100.0 / 20.0;
  double aExpectedLength = aTurns * sqrt(aCircumference * aCircumference + 20.0 * 20.0);

  ValidateHelixWire(TopoDS::Wire(aHelixWire), aExpectedLength);
}

TEST_F(HelixBRepTest, TCL_Test_B1_CompositeCylindricalHelix)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aDiams(1, 2);
  aDiams(1) = 100.0;
  aDiams(2) = 100.0;

  NCollection_Array1<double> aHeights(1, 1);
  aHeights(1) = 100.0;

  NCollection_Array1<double> aPitches(1, 1);
  aPitches(1) = 20.0;

  NCollection_Array1<bool> aIsPitches(1, 1);
  aIsPitches(1) = true;

  aBuilder.SetParameters(myAxis, aDiams, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aHelixWire = aBuilder.Shape();
  EXPECT_FALSE(aHelixWire.IsNull());

  double aCircumference  = M_PI * 100.0;
  double aTurns          = 100.0 / 20.0;
  double aExpectedLength = aTurns * sqrt(aCircumference * aCircumference + 20.0 * 20.0);

  ValidateHelixWire(TopoDS::Wire(aHelixWire), aExpectedLength);
}

TEST_F(HelixBRepTest, TCL_Test_C1_SpiralHelix)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aHeights(1, 3);
  aHeights(1) = 20.0;
  aHeights(2) = 60.0;
  aHeights(3) = 20.0;

  NCollection_Array1<double> aPitches(1, 3);
  aPitches(1) = 2.0;
  aPitches(2) = 6.0;
  aPitches(3) = 2.0;

  NCollection_Array1<bool> aIsPitches(1, 3);
  aIsPitches(1) = false;
  aIsPitches(2) = false;
  aIsPitches(3) = false;

  aBuilder.SetParameters(myAxis, 100.0, 20.0, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aHelixWire = aBuilder.Shape();
  EXPECT_FALSE(aHelixWire.IsNull());

  ValidateHelixWire(TopoDS::Wire(aHelixWire), 0);
}

TEST_F(HelixBRepTest, TCL_Test_F1_Helix2Interface)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aPitches(1, 3);
  aPitches(1) = 10.0;
  aPitches(2) = 10.0;
  aPitches(3) = 10.0;

  NCollection_Array1<double> aNbTurns(1, 3);
  aNbTurns(1) = 2.0;
  aNbTurns(2) = 6.0;
  aNbTurns(3) = 2.0;

  aBuilder.SetParameters(myAxis, 100.0, aPitches, aNbTurns);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aHelixWire = aBuilder.Shape();
  EXPECT_FALSE(aHelixWire.IsNull());

  double aCircumference  = M_PI * 100.0;
  double aTotalTurns     = 2.0 + 6.0 + 2.0;
  double aExpectedLength = aTotalTurns * sqrt(aCircumference * aCircumference + 10.0 * 10.0);

  ValidateHelixWire(TopoDS::Wire(aHelixWire), aExpectedLength);
}

TEST_F(HelixBRepTest, TCL_Test_E1_CustomerExample)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aDiams(1, 6);
  aDiams(1) = 150.0;
  aDiams(2) = 150.0;
  aDiams(3) = 150.0;
  aDiams(4) = 123.0;
  aDiams(5) = 123.0;
  aDiams(6) = 123.0;

  NCollection_Array1<double> aHeights(1, 5);
  aHeights(1) = 0.75 * 13.0;
  aHeights(2) = 2.1 * 64.0;
  aHeights(3) = 2.25 * 50.0;
  aHeights(4) = 2.5 * 45.0;
  aHeights(5) = 0.75 * 13.0;

  NCollection_Array1<double> aPitches(1, 5);
  aPitches(1) = 0.75;
  aPitches(2) = 2.1;
  aPitches(3) = 2.25;
  aPitches(4) = 2.5;
  aPitches(5) = 0.75;

  NCollection_Array1<bool> aIsPitches(1, 5);
  aIsPitches(1) = false;
  aIsPitches(2) = false;
  aIsPitches(3) = false;
  aIsPitches(4) = false;
  aIsPitches(5) = false;

  aBuilder.SetParameters(myAxis, aDiams, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aHelixWire = aBuilder.Shape();
  EXPECT_FALSE(aHelixWire.IsNull());

  ValidateHelixWire(TopoDS::Wire(aHelixWire), 0);
}

TEST_F(HelixBRepTest, ErrorConditions_InvalidDimensions)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aDiams(1, 3);
  NCollection_Array1<double> aHeights(1, 1);
  NCollection_Array1<double> aPitches(1, 1);
  NCollection_Array1<bool>   aIsPitches(1, 1);

  aDiams(1)     = 100.0;
  aDiams(2)     = 100.0;
  aDiams(3)     = 100.0;
  aHeights(1)   = 50.0;
  aPitches(1)   = 10.0;
  aIsPitches(1) = true;

  EXPECT_THROW(aBuilder.SetParameters(myAxis, aDiams, aHeights, aPitches, aIsPitches),
               Standard_ConstructionError);
}

TEST_F(HelixBRepTest, ErrorConditions_TurnsInterface)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aPitches(1, 2);
  NCollection_Array1<double> aNbTurns(1, 1);

  aPitches(1) = 10.0;
  aPitches(2) = 10.0;
  aNbTurns(1) = 5.0;

  EXPECT_THROW(aBuilder.SetParameters(myAxis, 100.0, aPitches, aNbTurns),
               Standard_ConstructionError);
}

TEST_F(HelixBRepTest, ApproximationQuality)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aHeights(1, 1);
  aHeights(1) = 50.0;

  NCollection_Array1<double> aPitches(1, 1);
  aPitches(1) = 10.0;

  NCollection_Array1<bool> aIsPitches(1, 1);
  aIsPitches(1) = true;

  aBuilder.SetParameters(myAxis, 50.0, aHeights, aPitches, aIsPitches);

  double aTightTolerance = 1.e-6;
  aBuilder.SetApproxParameters(aTightTolerance, 8, GeomAbs_C2);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  double aToleranceReached = aBuilder.ToleranceReached();
  EXPECT_GT(aToleranceReached, 0.0);

  EXPECT_LT(aToleranceReached, aTightTolerance * 1000);
}

TEST_F(HelixBRepTest, ParameterValidation)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aHeights(1, 1);
  NCollection_Array1<double> aPitches(1, 1);
  NCollection_Array1<bool>   aIsPitches(1, 1);

  aHeights(1)   = 1.e-8;
  aPitches(1)   = 10.0;
  aIsPitches(1) = true;

  aBuilder.SetParameters(myAxis, 50.0, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_NE(aBuilder.ErrorStatus(), 0);

  aHeights(1) = 50.0;
  aPitches(1) = 0.0;

  aBuilder.SetParameters(myAxis, 50.0, aHeights, aPitches, aIsPitches);

  aBuilder.Perform();

  EXPECT_NE(aBuilder.ErrorStatus(), 0);
}

TEST_F(HelixBRepTest, MultiPartContinuity)
{
  HelixBRep_BuilderHelix aBuilder;

  NCollection_Array1<double> aDiams(1, 3);
  aDiams(1) = 80.0;
  aDiams(2) = 60.0;
  aDiams(3) = 40.0;

  NCollection_Array1<double> aHeights(1, 2);
  aHeights(1) = 40.0;
  aHeights(2) = 40.0;

  NCollection_Array1<double> aPitches(1, 2);
  aPitches(1) = 8.0;
  aPitches(2) = 12.0;

  NCollection_Array1<bool> aIsPitches(1, 2);
  aIsPitches(1) = true;
  aIsPitches(2) = true;

  aBuilder.SetParameters(myAxis, aDiams, aHeights, aPitches, aIsPitches);
  aBuilder.SetApproxParameters(myTolerance, 8, GeomAbs_C1);

  aBuilder.Perform();

  EXPECT_EQ(aBuilder.ErrorStatus(), 0);

  const TopoDS_Shape& aHelixWire = aBuilder.Shape();
  EXPECT_FALSE(aHelixWire.IsNull());
  EXPECT_EQ(aHelixWire.ShapeType(), TopAbs_WIRE);

  int aNbEdges = CountShapes(aHelixWire, TopAbs_EDGE);
  EXPECT_GT(aNbEdges, 1);

  TopoDS_Wire        aWire = TopoDS::Wire(aHelixWire);
  BRepCheck_Analyzer aCheck(aWire);
  EXPECT_TRUE(aCheck.IsValid());
}
