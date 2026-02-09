

#include "BOPTest_Utilities.hpp"

#ifndef M_SQRT2
  #define M_SQRT2 1.41421356237309504880168872420969808
#endif

class BFuseSimpleTest : public BRepAlgoAPI_TestBase
{
};

TEST_F(BFuseSimpleTest, SpherePlusBox_A1)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();

  const TopoDS_Shape aResult = PerformFuse(aSphere, aBox);
  ValidateResult(aResult, 14.6394);
}

TEST_F(BFuseSimpleTest, RotatedSpherePlusBox_A2)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();

  const TopoDS_Shape aRotatedSphere = BOPTest_Utilities::RotateStandard(aSphere);

  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();
  const TopoDS_Shape aResult = PerformFuse(aRotatedSphere, aBox);
  ValidateResult(aResult, 14.6393);
}

TEST_F(BFuseSimpleTest, BoxPlusRotatedSphere_A3)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();

  const TopoDS_Shape aRotatedSphere = BOPTest_Utilities::RotateStandard(aSphere);

  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();
  const TopoDS_Shape aResult = PerformFuse(aBox, aRotatedSphere);
  ValidateResult(aResult, 14.6393);
}

TEST_F(BFuseSimpleTest, SpherePlusRotatedBox_A4)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();

  const TopoDS_Shape aRotatedBox = BOPTest_Utilities::RotateY(aBox, 90.0);

  const TopoDS_Shape aResult = PerformFuse(aSphere, aRotatedBox);
  ValidateResult(aResult, 14.6393);
}

TEST_F(BFuseSimpleTest, RotatedBoxPlusSphere_A5)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();

  const TopoDS_Shape aRotatedBox = BOPTest_Utilities::RotateY(aBox, 90.0);

  const TopoDS_Shape aResult = PerformFuse(aRotatedBox, aSphere);
  ValidateResult(aResult, 14.6393);
}

TEST_F(BFuseSimpleTest, IdenticalNurbsBoxPlusBox_A6)
{

  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.0);
}

TEST_F(BFuseSimpleTest, IdenticalBoxPlusNurbsBox_A7)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox2              = BOPTest_Utilities::ConvertToNurbs(aBox2);
  EXPECT_FALSE(aBox2.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.0);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusLargerBox_A8)
{

  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(-0.5, -0.5, -0.5), 2.0, 2.0, 2.0);

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 24.0);
}

TEST_F(BFuseSimpleTest, LargerBoxPlusNurbsBox_A9)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(-0.5, -0.5, -0.5), 2.0, 2.0, 2.0);

  TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox2              = BOPTest_Utilities::ConvertToNurbs(aBox2);
  EXPECT_FALSE(aBox2.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 24.0);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusBox_B1)
{

  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 0.5, 1.0, 0.5);

  const TopoDS_Shape aResult = PerformFuse(aBox2, aBox1);
  ValidateResult(aResult, 6.0);
}

TEST_F(BFuseSimpleTest, BoxPlusNurbsBox_B2)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 0.5, 0.5, 1.0);

  TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox2              = BOPTest_Utilities::ConvertToNurbs(aBox2);
  EXPECT_FALSE(aBox2.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 7.5);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusAdjacentBox_B3)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 0.5, 1.5, 1.0);

  const TopoDS_Shape aResult = PerformFuse(aBox2, aBox1);
  ValidateResult(aResult, 7.5);
}

TEST_F(BFuseSimpleTest, AdjacentBoxPlusNurbsBox_B4)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0.5, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformFuse(aBox2, aBox1);
  ValidateResult(aResult, 8.0);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusSmallerBox_B5)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0.25, 0.25, 0.25), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.0);
}

TEST_F(BFuseSimpleTest, SmallerBoxPlusNurbsBox_B6)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0.25, 0.25, 0.25), 0.5, 0.5, 0.5);

  TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox2              = BOPTest_Utilities::ConvertToNurbs(aBox2);
  EXPECT_FALSE(aBox2.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.0);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusPartiallyOverlappingBox_B7)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0.5, 0.5, 0.5), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 7.75);
}

TEST_F(BFuseSimpleTest, PartiallyOverlappingBoxPlusNurbsBox_B8)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0.5, 0.5, 0.5), 1.0, 1.0, 1.0);

  TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox2              = BOPTest_Utilities::ConvertToNurbs(aBox2);
  EXPECT_FALSE(aBox2.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 7.75);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusExtendedBox_B9)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(-0.5, -0.5, -0.5), 2.0, 2.0, 2.0);

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 24.0);
}

TEST_F(BFuseSimpleTest, ExtendedBoxPlusNurbsBox_C1)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformFuse(aBox2, aBox1);
  ValidateResult(aResult, 7.0);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusShiftedBox_C2)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 1.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformFuse(aBox2, aBox1);
  ValidateResult(aResult, 8.5);
}

TEST_F(BFuseSimpleTest, ShiftedBoxPlusNurbsBox_C3)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0.25, 0, 0), 0.5, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformFuse(aBox2, aBox1);
  ValidateResult(aResult, 6.0);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusNarrowBox_C4)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0.25, 0.25, 0), 0.5, 0.5, 1.5);

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.75);
}

TEST_F(BFuseSimpleTest, NarrowBoxPlusNurbsBox_C5)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0.25, 0.25, 0), 0.5, 0.5, 1.5);

  TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox2              = BOPTest_Utilities::ConvertToNurbs(aBox2);
  EXPECT_FALSE(aBox2.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.75);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusCornerCube_C6)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0.5, 0.5, 0.5), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.0);
}

TEST_F(BFuseSimpleTest, CornerCubePlusNurbsBox_C7)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0.5, 0.5, 0.5), 0.5, 0.5, 0.5);

  TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox2              = BOPTest_Utilities::ConvertToNurbs(aBox2);
  EXPECT_FALSE(aBox2.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.0);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusOffsetCube_C8)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(1, 1, 0), 0.5, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.25);
}

TEST_F(BFuseSimpleTest, OffsetCubePlusNurbsBox_C9)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(1, 1, 0), 0.5, 0.5, 1.0);

  TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox2              = BOPTest_Utilities::ConvertToNurbs(aBox2);
  EXPECT_FALSE(aBox2.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 6.25);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusRotatedNarrowBox_D1)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);

  constexpr double r     = M_SQRT2;
  TopoDS_Shape     aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r, 0.25, 1.0);
  gp_Trsf          aTrsf;
  aTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)), M_PI / 4.0);
  aBox2.Move(aTrsf);

  const TopoDS_Shape aResult = PerformFuse(aBox2, aBox1);
  ValidateResult(aResult, 6.41789);
}

TEST_F(BFuseSimpleTest, NurbsBoxPlusRotatedNarrowBoxVariation_D2)
{
  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);

  constexpr double r     = 5.5677643628300219;
  TopoDS_Shape     aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r / 4.0, 0.25, 1.0);
  gp_Trsf          aTrsf;
  aTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)), 34.73 * M_PI / 180.0);
  aBox2.Move(aTrsf);

  const TopoDS_Shape aResult = PerformFuse(aBox2, aBox1);
  ValidateResult(aResult, 6.32953);
}

TEST_F(BFuseSimpleTest, SpherePlusBox_D3)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformFuse(aSphere, aBox);
  ValidateResult(aResult, 14.6394);
}

TEST_F(BFuseSimpleTest, BoxPlusSphere_D4)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformFuse(aBox, aSphere);
  ValidateResult(aResult, 14.6394);
}

TEST_F(BFuseSimpleTest, RotatedSpherePlusBox_D5)
{
  TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);

  gp_Trsf aTrsf1, aTrsf2, aTrsfCombined;
  aTrsf1.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)), -M_PI / 2.0);
  aTrsf2.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Y)), -M_PI / 4.0);
  aTrsfCombined = aTrsf2 * aTrsf1;
  aSphere.Move(aTrsfCombined);

  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aResult = PerformFuse(aSphere, aBox);
  ValidateResult(aResult, 14.6393);
}

TEST_F(BFuseSimpleTest, BoxPlusRotatedSphere_D6)
{
  TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);

  gp_Trsf aTrsf1, aTrsf2, aTrsfCombined;
  aTrsf1.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)), -M_PI / 2.0);
  aTrsf2.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Y)), -M_PI / 4.0);
  aTrsfCombined = aTrsf2 * aTrsf1;
  aSphere.Move(aTrsfCombined);

  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aResult = PerformFuse(aBox, aSphere);
  ValidateResult(aResult, 14.6393);
}

TEST_F(BFuseSimpleTest, SpherePlusRotatedBox_D7)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);

  TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  gp_Trsf aTrsf;
  aTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 1), gp_Dir(gp_Dir::D::Y)), M_PI / 2.0);
  aBox.Move(aTrsf);

  const TopoDS_Shape aResult = PerformFuse(aSphere, aBox);
  ValidateResult(aResult, 14.6393);
}

TEST_F(BFuseSimpleTest, RotatedBoxPlusSphere_D8)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);

  TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  gp_Trsf aTrsf;
  aTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 1), gp_Dir(gp_Dir::D::Y)), M_PI / 2.0);
  aBox.Move(aTrsf);

  const TopoDS_Shape aResult = PerformFuse(aBox, aSphere);
  ValidateResult(aResult, 14.6393);
}

TEST_F(BFuseSimpleTest, ProfileBasedPrisms_D9)
{

  gp_Pln aPlane1(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 100.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, 100));

  gp_Pln aPlane2(gp_Ax3(gp_Pnt(0, 0, 100), gp_Dir(gp_Dir::D::Z)));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 100.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, 100));

  const TopoDS_Shape aResult = PerformFuse(aPrism1, aPrism2);
  ValidateResult(aResult, 180000.0);
}

TEST_F(BFuseSimpleTest, ComplexProfileWithScaling_E1)
{
  const double SCALE = 100.0;

  gp_Pln aPlane1(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::C, 50.0 * SCALE, 180.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -100.0 * SCALE),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::C, 50.0 * SCALE, 180.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, 30.0 * SCALE));

  gp_Pln aPlane2(gp_Ax3(gp_Pnt(-200.0 * SCALE, -50.0 * SCALE, 0), gp_Dir(gp_Dir::D::Z)));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 300.0 * SCALE),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0 * SCALE),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -300.0 * SCALE),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -200.0 * SCALE)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2 =
    BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -50.0 * SCALE));

  const TopoDS_Shape aResult = PerformFuse(aPrism2, aPrism1);
  ValidateResult(aResult, 1.85425e+09);
}

TEST_F(BFuseSimpleTest, AdjacentBoxes_E2)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 3.0, 3.0, 3.0);
  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 3, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformFuse(aBox1, aBox2);
  ValidateResult(aResult, 58.0);
}

TEST_F(BFuseSimpleTest, ComplexVertexEdgeWireRevolution_E3)
{

  std::vector<gp_Pnt> aPoints = {gp_Pnt(0, 0, 0),
                                 gp_Pnt(9, 0, 0),
                                 gp_Pnt(9, 0, 3),
                                 gp_Pnt(6.25, 0, 3),
                                 gp_Pnt(6, 0, 4),
                                 gp_Pnt(0, 0, 4)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aRevolution =
    BOPTest_Utilities::CreateRevolution(aFace,
                                        gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                        2.0 * M_PI);

  TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinder(1.0, 9.0);
  gp_Trsf      aTrsf;
  aTrsf.SetTranslation(gp_Vec(5, 0, -2));
  aCylinder.Move(aTrsf);

  const TopoDS_Shape aResult = PerformFuse(aRevolution, aCylinder);
  ValidateResult(aResult, 740.048);
}

TEST_F(BFuseSimpleTest, CylinderWithComplexWireRevolution_E4)
{

  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinder(3.0, 5.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(0, 3, 2),
                                 gp_Pnt(0, 4, 2),
                                 gp_Pnt(0, 4, 3),
                                 gp_Pnt(0, 3, 3)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aRing =
    BOPTest_Utilities::CreateRevolution(aFace,
                                        gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                        269.0 * M_PI / 180.0);

  const TopoDS_Shape aResult = PerformFuse(aCylinder, aRing);
  ValidateResult(aResult, 190.356);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromVertexEdge_E5)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 2, 0),
                                 gp_Pnt(4, 2, 0),
                                 gp_Pnt(4, 3, 0),
                                 gp_Pnt(3, 3, 0)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 0, 1));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromFront_E6)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 2, 0),
                                 gp_Pnt(4, 2, 0),
                                 gp_Pnt(4, 2, 1),
                                 gp_Pnt(3, 2, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromLeft_E7)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 2, 0),
                                 gp_Pnt(3, 3, 0),
                                 gp_Pnt(3, 3, 1),
                                 gp_Pnt(3, 2, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromTop_E8)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 2, 1),
                                 gp_Pnt(4, 2, 1),
                                 gp_Pnt(4, 3, 1),
                                 gp_Pnt(3, 3, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 0, -1));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromBack_E9)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 3, 0),
                                 gp_Pnt(4, 3, 0),
                                 gp_Pnt(4, 3, 1),
                                 gp_Pnt(3, 3, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromRight_F1)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(4, 2, 0),
                                 gp_Pnt(4, 3, 0),
                                 gp_Pnt(4, 3, 1),
                                 gp_Pnt(4, 2, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(-1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromBottomDifferent_F2)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(4, 3, 0),
                                 gp_Pnt(4, 2, 0),
                                 gp_Pnt(3, 2, 0),
                                 gp_Pnt(3, 3, 0)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 0, 1));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromBottomExternal_F3)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(8, 3, 0),
                                 gp_Pnt(9, 3, 0),
                                 gp_Pnt(9, 4, 0),
                                 gp_Pnt(8, 4, 0)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 0, 1));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromFrontExternal_F4)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(8, 3, 0),
                                 gp_Pnt(9, 3, 0),
                                 gp_Pnt(9, 3, 1),
                                 gp_Pnt(8, 3, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromLeftExternal_F5)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(8, 3, 0),
                                 gp_Pnt(8, 4, 0),
                                 gp_Pnt(8, 4, 1),
                                 gp_Pnt(8, 3, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromTopExternal_F6)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(8, 3, 1),
                                 gp_Pnt(9, 3, 1),
                                 gp_Pnt(9, 4, 1),
                                 gp_Pnt(8, 4, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 0, -1));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromBackExternal_F7)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(8, 4, 0),
                                 gp_Pnt(9, 4, 0),
                                 gp_Pnt(9, 4, 1),
                                 gp_Pnt(8, 4, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromRightExternal_F8)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(9, 3, 0),
                                 gp_Pnt(9, 4, 0),
                                 gp_Pnt(9, 4, 1),
                                 gp_Pnt(9, 3, 1)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(-1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromBottomTopPosition_F9)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 3, 4),
                                 gp_Pnt(4, 3, 4),
                                 gp_Pnt(4, 4, 4),
                                 gp_Pnt(3, 4, 4)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 0, 1));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromFrontTopLevel_G1)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 3, 4),
                                 gp_Pnt(4, 3, 4),
                                 gp_Pnt(4, 3, 5),
                                 gp_Pnt(3, 3, 5)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromLeftTopLevel_G2)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 3, 4),
                                 gp_Pnt(3, 4, 4),
                                 gp_Pnt(3, 4, 5),
                                 gp_Pnt(3, 3, 5)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromTopTopLevel_G3)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 3, 5),
                                 gp_Pnt(4, 3, 5),
                                 gp_Pnt(4, 4, 5),
                                 gp_Pnt(3, 4, 5)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 0, -1));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromBackTopLevel_G4)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(3, 4, 4),
                                 gp_Pnt(4, 4, 4),
                                 gp_Pnt(4, 4, 5),
                                 gp_Pnt(3, 4, 5)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, BoxWithPrismFromRightTopLevel_G5)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(3, 3, 0), 5.0, 7.0, 4.0);

  std::vector<gp_Pnt> aPoints = {gp_Pnt(4, 3, 4),
                                 gp_Pnt(4, 4, 4),
                                 gp_Pnt(4, 4, 5),
                                 gp_Pnt(4, 3, 5)};

  const TopoDS_Wire  aWire = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  const TopoDS_Shape aFace = BOPTest_Utilities::CreateFaceFromWire(aWire);

  const TopoDS_Shape aPrism = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(-1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBox, aPrism);
  ValidateResult(aResult, 170.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromBottom_G6)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 2, 0),
                                     gp_Pnt(4, 2, 0),
                                     gp_Pnt(4, 3, 0),
                                     gp_Pnt(3, 3, 0)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, 0, 1));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromFront_G7)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 2, 0),
                                     gp_Pnt(4, 2, 0),
                                     gp_Pnt(4, 2, 1),
                                     gp_Pnt(3, 2, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, 1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromLeft_G8)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 2, 0),
                                     gp_Pnt(3, 3, 0),
                                     gp_Pnt(3, 3, 1),
                                     gp_Pnt(3, 2, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromTop_G9)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 2, 1),
                                     gp_Pnt(4, 2, 1),
                                     gp_Pnt(4, 3, 1),
                                     gp_Pnt(3, 3, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, 0, -1));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromBackEdge_H1)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 3, 0),
                                     gp_Pnt(4, 3, 0),
                                     gp_Pnt(4, 3, 1),
                                     gp_Pnt(3, 3, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromRightEdge_H2)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(4, 2, 0),
                                     gp_Pnt(4, 3, 0),
                                     gp_Pnt(4, 3, 1),
                                     gp_Pnt(4, 2, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(-1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromBottomCorner_H3)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(8, 3, 0),
                                     gp_Pnt(9, 3, 0),
                                     gp_Pnt(9, 4, 0),
                                     gp_Pnt(8, 4, 0)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, 0, 1));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromFrontEdge_H4)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(8, 3, 0),
                                     gp_Pnt(9, 3, 0),
                                     gp_Pnt(9, 3, 1),
                                     gp_Pnt(8, 3, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, 1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromLeftEdge_H5)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(8, 3, 0),
                                     gp_Pnt(8, 4, 0),
                                     gp_Pnt(8, 4, 1),
                                     gp_Pnt(8, 3, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromTopEdge_H6)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(8, 3, 1),
                                     gp_Pnt(9, 3, 1),
                                     gp_Pnt(9, 4, 1),
                                     gp_Pnt(8, 4, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, 0, -1));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromBackEdgeCorner_H7)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(8, 4, 0),
                                     gp_Pnt(9, 4, 0),
                                     gp_Pnt(9, 4, 1),
                                     gp_Pnt(8, 4, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromRightEdgeCorner_H8)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(9, 3, 0),
                                     gp_Pnt(9, 4, 0),
                                     gp_Pnt(9, 4, 1),
                                     gp_Pnt(9, 3, 1)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(-1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromTopCorner_H9)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 3, 4),
                                     gp_Pnt(4, 3, 4),
                                     gp_Pnt(4, 4, 4),
                                     gp_Pnt(3, 4, 4)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, 0, 1));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromFrontTopLevel_I1)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 3, 4),
                                     gp_Pnt(4, 3, 4),
                                     gp_Pnt(4, 3, 5),
                                     gp_Pnt(3, 3, 5)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, 1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromLeftTopLevel_I2)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 3, 4),
                                     gp_Pnt(3, 4, 4),
                                     gp_Pnt(3, 4, 5),
                                     gp_Pnt(3, 3, 5)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromTopAbove_I3)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 3, 5),
                                     gp_Pnt(4, 3, 5),
                                     gp_Pnt(4, 4, 5),
                                     gp_Pnt(3, 4, 5)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, 0, -1));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromBackTopLevel_I4)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(3, 4, 4),
                                     gp_Pnt(4, 4, 4),
                                     gp_Pnt(4, 4, 5),
                                     gp_Pnt(3, 4, 5)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithSmallPrismFromRightTopLevel_I5)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 4));

  std::vector<gp_Pnt> aSmallPts   = {gp_Pnt(4, 3, 4),
                                     gp_Pnt(4, 4, 4),
                                     gp_Pnt(4, 4, 5),
                                     gp_Pnt(4, 3, 5)};
  const TopoDS_Wire   aSmallWire  = BOPTest_Utilities::CreatePolygonWire(aSmallPts, true);
  const TopoDS_Shape  aSmallFace  = BOPTest_Utilities::CreateFaceFromWire(aSmallWire);
  const TopoDS_Shape  aSmallPrism = BOPTest_Utilities::CreatePrism(aSmallFace, gp_Vec(-1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aSmallPrism);
  ValidateResult(aResult, 152.0);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismProfile_I6)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {4, 3, 0}},
    {BOPTest_Utilities::ProfileCmd::P, {0, 1, 0, 1, 0, 0}},
    {BOPTest_Utilities::ProfileCmd::D, {-1, 0}},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::X, 2},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const TopoDS_Shape aProfileFace = BOPTest_Utilities::CreateProfileFromOperations(aOps);
  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreatePrism(aProfileFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismYDirection_I7)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {3, 3, 3}},
    {BOPTest_Utilities::ProfileCmd::P, {0, 1, 0, 1, 0, 0}},
    {BOPTest_Utilities::ProfileCmd::D, {0, -1}},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::Y, 2},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const TopoDS_Shape aProfileFace = BOPTest_Utilities::CreateProfileFromOperations(aOps);
  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreatePrism(aProfileFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismXDirection_I8)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {5, 3, 0}},
    {BOPTest_Utilities::ProfileCmd::P, {0, 1, 0, 1, 0, 0}},
    {BOPTest_Utilities::ProfileCmd::D, {-1, 0}},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::X, 2},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const TopoDS_Shape aProfileFace = BOPTest_Utilities::CreateProfileFromOperations(aOps);
  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreatePrism(aProfileFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismYDirectionFinal_I9)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {6, 3, 3}},
    {BOPTest_Utilities::ProfileCmd::P, {0, 1, 0, 1, 0, 0}},
    {BOPTest_Utilities::ProfileCmd::D, {0, -1}},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::Y, 2},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const TopoDS_Shape aProfileFace = BOPTest_Utilities::CreateProfileFromOperations(aOps);
  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreatePrism(aProfileFace, gp_Vec(0, -1, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismRightSide_J1)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {8, 4, 0}},
    {BOPTest_Utilities::ProfileCmd::P, {-1, 0, 0, 0, 1, 0}},
    {BOPTest_Utilities::ProfileCmd::D, {-1, 0}},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::X, 2},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const TopoDS_Shape aProfileFace = BOPTest_Utilities::CreateProfileFromOperations(aOps);
  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreatePrism(aProfileFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismRightSideY_J2)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {8, 3, 3}},
    {BOPTest_Utilities::ProfileCmd::P, {-1, 0, 0, 0, 1, 0}},
    {BOPTest_Utilities::ProfileCmd::D, {0, -1}},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::Y, 2},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const TopoDS_Shape aProfileFace = BOPTest_Utilities::CreateProfileFromOperations(aOps);
  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreatePrism(aProfileFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismRightSideX_J3)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {8, 6, 0}},
    {BOPTest_Utilities::ProfileCmd::P, {-1, 0, 0, 0, 1, 0}},
    {BOPTest_Utilities::ProfileCmd::D, {-1, 0}},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::X, 2},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const TopoDS_Shape aProfileFace = BOPTest_Utilities::CreateProfileFromOperations(aOps);
  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreatePrism(aProfileFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismRightSideY2_J4)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {8, 7, 3}},
    {BOPTest_Utilities::ProfileCmd::P, {-1, 0, 0, 0, 1, 0}},
    {BOPTest_Utilities::ProfileCmd::D, {0, -1}},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::Y, 2},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const TopoDS_Shape aProfileFace = BOPTest_Utilities::CreateProfileFromOperations(aOps);
  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreatePrism(aProfileFace, gp_Vec(1, 0, 0));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismRightSide_J5)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreateBox(gp_Pnt(8, 4, 1), 1.0, 2.0, 2.0);

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismRightSide_J6)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreateBox(gp_Pnt(8, 5, 2), 1.0, 2.0, 2.0);

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismRightSide_J7)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreateBox(gp_Pnt(8, 6, 1), 1.0, 2.0, 2.0);

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, LargePrismWithOblongPrismTop_J8)
{

  std::vector<gp_Pnt> aBasePts   = {gp_Pnt(3, 3, 0),
                                    gp_Pnt(8, 3, 0),
                                    gp_Pnt(8, 9, 0),
                                    gp_Pnt(3, 9, 0)};
  const TopoDS_Wire   aBaseWire  = BOPTest_Utilities::CreatePolygonWire(aBasePts, true);
  const TopoDS_Shape  aBaseFace  = BOPTest_Utilities::CreateFaceFromWire(aBaseWire);
  const TopoDS_Shape  aBasePrism = BOPTest_Utilities::CreatePrism(aBaseFace, gp_Vec(0, 0, 5));

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {8, 4, 5}},
    {BOPTest_Utilities::ProfileCmd::P, {0, 0, -1, 1, 0, 0}},
    {BOPTest_Utilities::ProfileCmd::D, {0, 1}},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::Y, -2},
    {BOPTest_Utilities::ProfileCmd::C, {1, 180}},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const TopoDS_Shape aProfileFace = BOPTest_Utilities::CreateProfileFromOperations(aOps);
  const TopoDS_Shape aOblongPrism = BOPTest_Utilities::CreatePrism(aProfileFace, gp_Vec(0, 0, 1));

  const TopoDS_Shape aResult = PerformFuse(aBasePrism, aOblongPrism);
  ValidateResult(aResult, 180.283);
}

TEST_F(BFuseSimpleTest, CylinderWithRevolutionRing_J9)
{

  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinder(3.0, 5.0);

  std::vector<gp_Pnt> aRingPts  = {gp_Pnt(0, 3, 2),
                                   gp_Pnt(0, 4, 2),
                                   gp_Pnt(0, 4, 3),
                                   gp_Pnt(0, 3, 3)};
  const TopoDS_Wire   aRingWire = BOPTest_Utilities::CreatePolygonWire(aRingPts, true);
  const TopoDS_Shape  aRingFace = BOPTest_Utilities::CreateFaceFromWire(aRingWire);

  const gp_Ax1       aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  const TopoDS_Shape aRing =
    BOPTest_Utilities::CreateRevolution(aRingFace, aAxis, 269.0 * M_PI / 180.0);

  const TopoDS_Shape aResult = PerformFuse(aCylinder, aRing);
  ValidateResult(aResult, 190.356);
}

TEST_F(BFuseSimpleTest, ComplexProfileWithRevolution_K1)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 200.0, 200.0, 100.0);

  const std::vector<BOPTest_Utilities::ProfileOperation> aOps = {
    {BOPTest_Utilities::ProfileCmd::O, {50, 0, 0}},
    {BOPTest_Utilities::ProfileCmd::F, {50, -80}},
    {BOPTest_Utilities::ProfileCmd::X, 50},
    {BOPTest_Utilities::ProfileCmd::Y, 5},
    {BOPTest_Utilities::ProfileCmd::X, 10},
    {BOPTest_Utilities::ProfileCmd::Y, -25},
    {BOPTest_Utilities::ProfileCmd::X, -60},
    {BOPTest_Utilities::ProfileCmd::W, {}}};
  const gp_Pln       aPlane(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::X));
  const TopoDS_Shape aProfile = BOPTest_Utilities::CreateProfile(aPlane, aOps);

  const gp_Ax1       aRevAxis(gp_Pnt(50, 100, 50), gp_Dir(gp_Dir::D::Z));
  const TopoDS_Shape aRevolution =
    BOPTest_Utilities::CreateRevolution(aProfile, aRevAxis, 2 * M_PI);

  const TopoDS_Shape aResult = PerformFuse(aBox, aRevolution);
  ValidateResult(aResult, 161571);
}

TEST_F(BFuseSimpleTest, BlendBoxWithCylinder_K2)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 300.0, 300.0, 100.0);

  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinder(100.0, 50.0);

  const TopoDS_Shape aResult = PerformFuse(aBox, aCylinder);
  ValidateResult(aResult, 360686);
}

TEST_F(BFuseSimpleTest, BlendBoxWithCylinderNegX_K3)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 300.0, 300.0, 100.0);

  const TopoDS_Shape aBlendedBox = BOPTest_Utilities::CreateBlend(aBox, 1, 100.0);
  EXPECT_FALSE(aBlendedBox.IsNull()) << "Blend operation failed";

  const gp_Ax3       anAx3(gp_Pnt(100, 100, 100), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::NX));
  const gp_Pln       aPlane(anAx3);
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinderOnPlane(aPlane, 100.0, 50.0);
  EXPECT_FALSE(aCylinder.IsNull()) << "Cylinder creation failed";

  const TopoDS_Shape aResult = PerformFuse(aBlendedBox, aCylinder);
  ValidateResult(aResult, 322832);
}

TEST_F(BFuseSimpleTest, BlendBoxWithCylinderY_K4)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 300.0, 300.0, 100.0);

  const TopoDS_Shape aBlendedBox = BOPTest_Utilities::CreateBlend(aBox, 1, 100.0);

  const gp_Ax3       anAx3(gp_Pnt(100, 100, 100), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::Y));
  const gp_Pln       aPlane(anAx3);
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinderOnPlane(aPlane, 100.0, 50.0);

  const TopoDS_Shape aResult = PerformFuse(aBlendedBox, aCylinder);
  ValidateResult(aResult, 322832);
}

TEST_F(BFuseSimpleTest, BlendBoxWithCylinderNegY_K5)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 300.0, 300.0, 100.0);

  const TopoDS_Shape aBlendedBox = BOPTest_Utilities::CreateBlend(aBox, 1, 100.0);

  const gp_Ax3       anAx3(gp_Pnt(100, 100, 100), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::NY));
  const gp_Pln       aPlane(anAx3);
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinderOnPlane(aPlane, 100.0, 50.0);

  const TopoDS_Shape aResult = PerformFuse(aBlendedBox, aCylinder);
  ValidateResult(aResult, 322832);
}

TEST_F(BFuseSimpleTest, BlendBoxWithCylinderBottomX_K6)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 300.0, 300.0, 100.0);

  const TopoDS_Shape aBlendedBox = BOPTest_Utilities::CreateBlend(aBox, 1, 100.0);

  const gp_Ax3       anAx3(gp_Pnt(100, 100, 0), gp_Dir(gp_Dir::D::NZ), gp_Dir(gp_Dir::D::X));
  const gp_Pln       aPlane(anAx3);
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinderOnPlane(aPlane, 100.0, 50.0);

  const TopoDS_Shape aResult = PerformFuse(aBlendedBox, aCylinder);
  ValidateResult(aResult, 322832);
}

TEST_F(BFuseSimpleTest, BlendBoxWithCylinderBottomNegX_K7)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 300.0, 300.0, 100.0);

  const TopoDS_Shape aBlendedBox = BOPTest_Utilities::CreateBlend(aBox, 1, 100.0);

  const gp_Ax3       anAx3(gp_Pnt(100, 100, 0), gp_Dir(gp_Dir::D::NZ), gp_Dir(gp_Dir::D::NX));
  const gp_Pln       aPlane(anAx3);
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinderOnPlane(aPlane, 100.0, 50.0);

  const TopoDS_Shape aResult = PerformFuse(aBlendedBox, aCylinder);
  ValidateResult(aResult, 322832);
}

TEST_F(BFuseSimpleTest, BlendBoxWithCylinderBottomY_K8)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 300.0, 300.0, 100.0);

  const TopoDS_Shape aBlendedBox = BOPTest_Utilities::CreateBlend(aBox, 1, 100.0);

  const gp_Ax3       anAx3(gp_Pnt(100, 100, 0), gp_Dir(gp_Dir::D::NZ), gp_Dir(gp_Dir::D::Y));
  const gp_Pln       aPlane(anAx3);
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinderOnPlane(aPlane, 100.0, 50.0);

  const TopoDS_Shape aResult = PerformFuse(aBlendedBox, aCylinder);
  ValidateResult(aResult, 322832);
}

TEST_F(BFuseSimpleTest, BlendBoxWithCylinderBottomNegY_K9)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 300.0, 300.0, 100.0);

  const TopoDS_Shape aBlendedBox = BOPTest_Utilities::CreateBlend(aBox, 1, 100.0);

  const gp_Ax3       anAx3(gp_Pnt(100, 100, 0), gp_Dir(gp_Dir::D::NZ), gp_Dir(gp_Dir::D::NY));
  const gp_Pln       aPlane(anAx3);
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinderOnPlane(aPlane, 100.0, 50.0);

  const TopoDS_Shape aResult = PerformFuse(aBlendedBox, aCylinder);
  ValidateResult(aResult, 322832);
}

TEST_F(BFuseSimpleTest, OCC277_FuseAndCommonOfOverlappingBoxes)
{
  BRepPrimAPI_MakeBox aBox1Maker(100, 100, 100);
  BRepPrimAPI_MakeBox aBox2Maker(gp_Pnt(50, 50, 50), 200, 200, 200);

  TopoDS_Shape aShape1 = aBox1Maker.Shape();
  TopoDS_Shape aShape2 = aBox2Maker.Shape();

  BRepAlgoAPI_Fuse aFuseOp(aShape1, aShape2);
  TopoDS_Shape     aFuseResult = aFuseOp.Shape();
  EXPECT_FALSE(aFuseResult.IsNull());

  BRepAlgoAPI_Common aCommonOp(aShape1, aShape2);
  TopoDS_Shape       aCommonResult = aCommonOp.Shape();
  EXPECT_FALSE(aCommonResult.IsNull());
}
