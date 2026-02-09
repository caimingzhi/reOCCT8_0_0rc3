

#include "BOPTest_Utilities.hpp"

class BOPAlgo_DirectOperationsTest : public BOPAlgo_TestBase
{
};

TEST_F(BOPAlgo_DirectOperationsTest, DirectCut_SphereMinusBox)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();

  const TopoDS_Shape aResult = PerformDirectBOP(aSphere, aBox, BOPAlgo_CUT);
  EXPECT_FALSE(aResult.IsNull()) << "Result shape should not be null";

  const double aSurfaceArea = BOPTest_Utilities::GetSurfaceArea(aResult);
  EXPECT_GT(aSurfaceArea, 0.0) << "Cut result should have positive surface area";
}

TEST_F(BOPAlgo_DirectOperationsTest, DirectFuse_SpherePlusBox)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();

  const TopoDS_Shape aResult = PerformDirectBOP(aSphere, aBox, BOPAlgo_FUSE);
  EXPECT_FALSE(aResult.IsNull()) << "Result shape should not be null";

  const double aVolume       = BOPTest_Utilities::GetVolume(aResult);
  const double aSphereVolume = BOPTest_Utilities::GetVolume(aSphere);
  const double aBoxVolume    = BOPTest_Utilities::GetVolume(aBox);
  EXPECT_GT(aVolume, aSphereVolume) << "Fuse result should be larger than sphere alone";
  EXPECT_GT(aVolume, aBoxVolume) << "Fuse result should be larger than box alone";
}

TEST_F(BOPAlgo_DirectOperationsTest, DirectCommon_OverlappingBoxes)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 2.0, 2.0, 2.0);
  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(1, 1, 1), 2.0, 2.0, 2.0);

  const TopoDS_Shape aResult = PerformDirectBOP(aBox1, aBox2, BOPAlgo_COMMON);
  ValidateResult(aResult, -1.0, 1.0);
}

TEST_F(BOPAlgo_DirectOperationsTest, DirectTUC_IdenticalBoxes)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformDirectBOP(aBox1, aBox2, BOPAlgo_CUT21);
  ValidateResult(aResult, -1.0, -1.0, true);
}

TEST_F(BOPAlgo_DirectOperationsTest, DirectCut_NurbsBoxMinusBox)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 1, 0), 1.0, 0.5, 1.0);

  const TopoDS_Shape aResult      = PerformDirectBOP(aBox1, aBox2, BOPAlgo_CUT);
  const double       aSurfaceArea = BOPTest_Utilities::GetSurfaceArea(aResult);
  EXPECT_GT(aSurfaceArea, 0.0) << "NURBS cut result should have positive surface area";
}

class BOPAlgo_TwoStepOperationsTest : public BOPAlgo_TestBase
{
};

TEST_F(BOPAlgo_TwoStepOperationsTest, TwoStepCut_SphereMinusBox)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();

  const TopoDS_Shape aResult      = PerformTwoStepBOP(aSphere, aBox, BOPAlgo_CUT);
  const double       aSurfaceArea = BOPTest_Utilities::GetSurfaceArea(aResult);
  EXPECT_GT(aSurfaceArea, 0.0) << "Two-step cut result should have positive surface area";
}

TEST_F(BOPAlgo_TwoStepOperationsTest, TwoStepFuse_SpherePlusBox)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();

  const TopoDS_Shape aResult = PerformTwoStepBOP(aSphere, aBox, BOPAlgo_FUSE);
  EXPECT_FALSE(aResult.IsNull()) << "Result shape should not be null";

  const double aVolume       = BOPTest_Utilities::GetVolume(aResult);
  const double aSphereVolume = BOPTest_Utilities::GetVolume(aSphere);
  const double aBoxVolume    = BOPTest_Utilities::GetVolume(aBox);
  EXPECT_GT(aVolume, aSphereVolume) << "Two-step fuse result should be larger than sphere alone";
  EXPECT_GT(aVolume, aBoxVolume) << "Two-step fuse result should be larger than box alone";
}

TEST_F(BOPAlgo_TwoStepOperationsTest, TwoStepCommon_OverlappingBoxes)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 2.0, 2.0, 2.0);
  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(1, 1, 1), 2.0, 2.0, 2.0);

  const TopoDS_Shape aResult = PerformTwoStepBOP(aBox1, aBox2, BOPAlgo_COMMON);
  ValidateResult(aResult, -1.0, 1.0);
}

TEST_F(BOPAlgo_TwoStepOperationsTest, TwoStepTUC_IdenticalBoxes)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformTwoStepBOP(aBox1, aBox2, BOPAlgo_CUT21);
  ValidateResult(aResult, -1.0, -1.0, true);
}

class BOPAlgo_ComplexOperationsTest : public BOPAlgo_TestBase
{
};

TEST_F(BOPAlgo_ComplexOperationsTest, MultipleIntersectingPrimitives)
{
  const TopoDS_Shape aSphere   = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.5);
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinder(0.8, 3.0);
  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(-0.5, -0.5, -0.5), 1.0, 1.0, 1.0);

  const TopoDS_Shape aIntermediate = PerformDirectBOP(aSphere, aCylinder, BOPAlgo_COMMON);
  EXPECT_FALSE(aIntermediate.IsNull()) << "Intermediate result should not be null";

  const TopoDS_Shape aFinalResult = PerformDirectBOP(aIntermediate, aBox, BOPAlgo_FUSE);
  const double       aVolume      = BOPTest_Utilities::GetVolume(aFinalResult);
  EXPECT_GT(aVolume, 0.0) << "Complex operation result should have positive volume";
}

TEST_F(BOPAlgo_ComplexOperationsTest, DirectVsTwoStepComparison)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();

  const TopoDS_Shape aDirectResult = PerformDirectBOP(aSphere, aBox, BOPAlgo_FUSE);

  const TopoDS_Shape aTwoStepResult = PerformTwoStepBOP(aSphere, aBox, BOPAlgo_FUSE);

  const double aDirectVolume  = BOPTest_Utilities::GetVolume(aDirectResult);
  const double aTwoStepVolume = BOPTest_Utilities::GetVolume(aTwoStepResult);

  EXPECT_NEAR(aDirectVolume, aTwoStepVolume, myTolerance)
    << "Direct and two-step operations should produce equivalent results";
}
