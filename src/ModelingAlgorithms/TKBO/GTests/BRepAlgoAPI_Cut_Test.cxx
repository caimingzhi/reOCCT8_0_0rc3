

#include "BOPTest_Utilities.hpp"

#ifndef M_SQRT2
  #define M_SQRT2 1.41421356237309504880168872420969808
#endif

class BCutSimpleTest : public BRepAlgoAPI_TestBase
{
};

TEST_F(BCutSimpleTest, SphereMinusBox_A1)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();

  const TopoDS_Shape aResult = PerformCut(aSphere, aBox);
  ValidateResult(aResult, 13.3518);
}

TEST_F(BCutSimpleTest, RotatedSphereMinusBox_A2)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();

  const TopoDS_Shape aRotatedSphere = BOPTest_Utilities::RotateStandard(aSphere);

  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();
  const TopoDS_Shape aResult = PerformCut(aRotatedSphere, aBox);
  ValidateResult(aResult, 13.3517);
}

TEST_F(BCutSimpleTest, BoxMinusRotatedSphere_A3)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateUnitSphere();

  const TopoDS_Shape aRotatedSphere = BOPTest_Utilities::RotateStandard(aSphere);

  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateUnitBox();
  const TopoDS_Shape aResult = PerformCut(aBox, aRotatedSphere);
  ValidateResult(aResult, 5.2146);
}

TEST_F(BCutSimpleTest, SphereMinusRotatedBox_A4)
{
  const TopoDS_Shape aSphere     = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox        = BOPTest_Utilities::CreateUnitBox();
  const TopoDS_Shape aRotatedBox = BOPTest_Utilities::RotateY90(aBox);

  const TopoDS_Shape aResult = PerformCut(aSphere, aRotatedBox);
  ValidateResult(aResult, 13.3517);
}

TEST_F(BCutSimpleTest, RotatedBoxMinusSphere_A5)
{
  const TopoDS_Shape aSphere     = BOPTest_Utilities::CreateUnitSphere();
  const TopoDS_Shape aBox        = BOPTest_Utilities::CreateUnitBox();
  const TopoDS_Shape aRotatedBox = BOPTest_Utilities::RotateY90(aBox);

  const TopoDS_Shape aResult = PerformCut(aRotatedBox, aSphere);
  ValidateResult(aResult, 5.2146);
}

TEST_F(BCutSimpleTest, IdenticalNurbsBoxMinusBox_A6)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aBox);
  ValidateResult(aResult, -1.0, -1.0, true);
}

TEST_F(BCutSimpleTest, IdenticalBoxMinusNurbsBox_A7)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformCut(aBox, aNurbsBox);
  ValidateResult(aResult, -1.0, -1.0, true);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusLargerBox_A8)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aLargerBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aLargerBox);
  ValidateResult(aResult, -1.0, -1.0, true);
}

TEST_F(BCutSimpleTest, LargerBoxMinusNurbsBox_A9)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aLargerBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aLargerBox, aNurbsBox);
  ValidateResult(aResult, 4.0);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusBox_B1)
{

  TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox1              = BOPTest_Utilities::ConvertToNurbs(aBox1);
  EXPECT_FALSE(aBox1.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 1, 0), 1.0, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aBox1, aBox2);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, BoxMinusNurbsBox_B2)
{

  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 1, 0), 1.0, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aBox, aNurbsBox);
  ValidateResult(aResult, 4.0);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusAdjacentBox_B3)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aAdjacentBox = BOPTest_Utilities::CreateBox(gp_Pnt(1, 1, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aAdjacentBox);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, AdjacentBoxMinusNurbsBox_B4)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aAdjacentBox = BOPTest_Utilities::CreateBox(gp_Pnt(1, 1, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformCut(aAdjacentBox, aNurbsBox);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusSmallerBox_B5)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aSmallerBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 0.5, 1.0, 0.5);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aSmallerBox);
  ValidateResult(aResult, 5.5);
}

TEST_F(BCutSimpleTest, SmallerBoxMinusNurbsBox_B6)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aSmallerBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 0.5, 1.0, 0.5);

  const TopoDS_Shape aResult = PerformCut(aSmallerBox, aNurbsBox);
  ValidateResult(aResult, -1.0, -1.0, true);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusPartiallyOverlappingBox_B7)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aPartialBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 0.5, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aPartialBox);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, PartiallyOverlappingBoxMinusNurbsBox_B8)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aPartialBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 0.5, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aPartialBox, aNurbsBox);
  ValidateResult(aResult, 2.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusExtendedBox_B9)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aExtendedBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 0.5, 1.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aExtendedBox);
  ValidateResult(aResult, 4.0);
}

TEST_F(BCutSimpleTest, ExtendedBoxMinusNurbsBox_C1)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aExtendedBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 0.5, 1.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aExtendedBox, aNurbsBox);
  ValidateResult(aResult, 2.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusShiftedBox_C2)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aShiftedBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0.5, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aShiftedBox);
  ValidateResult(aResult, 4.0);
}

TEST_F(BCutSimpleTest, ShiftedBoxMinusNurbsBox_C3)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aShiftedBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0.5, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformCut(aShiftedBox, aNurbsBox);
  ValidateResult(aResult, 4.0);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusNarrowBox_C4)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aNarrowBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0.25, 0), 1.0, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aNarrowBox);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, NarrowBoxMinusNurbsBox_C5)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aNarrowBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0.25, 0), 1.0, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNarrowBox, aNurbsBox);
  ValidateResult(aResult, -1.0, -1.0, true);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusCornerCube_C6)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aCornerCube = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aCornerCube);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, CornerCubeMinusNurbsBox_C7)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aCornerCube = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aCornerCube, aNurbsBox);
  ValidateResult(aResult, -1.0, -1.0, true);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusOffsetCube_C8)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetCube = BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aOffsetCube);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, OffsetCubeMinusNurbsBox_C9)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetCube = BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aOffsetCube, aNurbsBox);
  ValidateResult(aResult, 1.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusOffsetCornerCube_D1)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetCornerCube =
    BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, -0.5), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aOffsetCornerCube);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, OffsetCornerCubeMinusNurbsBox_D2)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetCornerCube =
    BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, -0.5), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aOffsetCornerCube, aNurbsBox);
  ValidateResult(aResult, 1.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusShiftedCornerCube_D3)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aShiftedCornerCube =
    BOPTest_Utilities::CreateBox(gp_Pnt(-0.5, -0.5, -0.5), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aShiftedCornerCube);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, ShiftedCornerCubeMinusNurbsBox_D4)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aShiftedCornerCube =
    BOPTest_Utilities::CreateBox(gp_Pnt(-0.5, -0.5, -0.5), 0.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aShiftedCornerCube, aNurbsBox);
  ValidateResult(aResult, 1.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusExtendedXBox_D5)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aExtendedXBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aExtendedXBox);
  ValidateResult(aResult, 5.5);
}

TEST_F(BCutSimpleTest, ExtendedXBoxMinusNurbsBox_D6)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aExtendedXBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aExtendedXBox, aNurbsBox);
  ValidateResult(aResult, 1.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusOffsetExtendedXBox_D7)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetExtendedXBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 1.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aOffsetExtendedXBox);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, OffsetExtendedXBoxMinusNurbsBox_D8)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetExtendedXBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0, -0.5, 0), 1.5, 0.5, 0.5);

  const TopoDS_Shape aResult = PerformCut(aOffsetExtendedXBox, aNurbsBox);
  ValidateResult(aResult, 3.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusShiftedNarrowBox_D9)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aShiftedNarrowBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0.25, 0, 0), 0.5, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aShiftedNarrowBox);
  ValidateResult(aResult, 6.5);
}

TEST_F(BCutSimpleTest, ShiftedNarrowBoxMinusNurbsBox_E1)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aShiftedNarrowBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0.25, 0, 0), 0.5, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aShiftedNarrowBox, aNurbsBox);
  ValidateResult(aResult, -1.0, -1.0, true);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusOffsetShiftedNarrowBox_E2)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetShiftedNarrowBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0.25, -0.5, 0), 0.5, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aOffsetShiftedNarrowBox);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, OffsetShiftedNarrowBoxMinusNurbsBox_E3)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetShiftedNarrowBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0.25, -0.5, 0), 0.5, 0.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aOffsetShiftedNarrowBox, aNurbsBox);
  ValidateResult(aResult, 2.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusExtendedYShiftedNarrowBox_E4)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aExtendedYShiftedNarrowBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0.25, 0, 0), 0.5, 1.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aExtendedYShiftedNarrowBox);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, ExtendedYShiftedNarrowBoxMinusNurbsBox_E5)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aExtendedYShiftedNarrowBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0.25, 0, 0), 0.5, 1.5, 1.0);

  const TopoDS_Shape aResult = PerformCut(aExtendedYShiftedNarrowBox, aNurbsBox);
  ValidateResult(aResult, 2.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusRightHalfBox_E6)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aRightHalfBox = BOPTest_Utilities::CreateBox(gp_Pnt(0.5, 0, 0), 1.0, 1.0, 0.5);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aRightHalfBox);
  ValidateResult(aResult, 5.5);
}

TEST_F(BCutSimpleTest, RightHalfBoxMinusNurbsBox_E7)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aRightHalfBox = BOPTest_Utilities::CreateBox(gp_Pnt(0.5, 0, 0), 1.0, 1.0, 0.5);

  const TopoDS_Shape aResult = PerformCut(aRightHalfBox, aNurbsBox);
  ValidateResult(aResult, 2.5);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusOffsetRightHalfBox_E8)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetRightHalfBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0.5, 0, -0.5), 1.0, 1.0, 0.5);

  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aOffsetRightHalfBox);
  ValidateResult(aResult, 6.0);
}

TEST_F(BCutSimpleTest, OffsetRightHalfBoxMinusNurbsBox_E9)
{
  TopoDS_Shape aNurbsBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox              = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  EXPECT_FALSE(aNurbsBox.IsNull()) << "Failed to convert to NURBS";

  const TopoDS_Shape aOffsetRightHalfBox =
    BOPTest_Utilities::CreateBox(gp_Pnt(0.5, 0, -0.5), 1.0, 1.0, 0.5);

  const TopoDS_Shape aResult = PerformCut(aOffsetRightHalfBox, aNurbsBox);
  ValidateResult(aResult, 4.0);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusRotatedRectangularBox_F1)
{
  TopoDS_Shape aNurbsBox           = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox                        = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  constexpr double r               = M_SQRT2;
  TopoDS_Shape     aRectangularBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r, r / 2.0, 1.0);
  aRectangularBox                  = BOPTest_Utilities::RotateShape(aRectangularBox,
                                                   gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                                   45.0 * M_PI / 180.0);
  const TopoDS_Shape aResult       = PerformCut(aNurbsBox, aRectangularBox);
  ValidateResult(aResult, 4.41421);
}

TEST_F(BCutSimpleTest, RotatedRectangularBoxMinusNurbsBox_F2)
{
  TopoDS_Shape aNurbsBox           = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox                        = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  constexpr double r               = M_SQRT2;
  TopoDS_Shape     aRectangularBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r, r / 2.0, 1.0);
  aRectangularBox                  = BOPTest_Utilities::RotateShape(aRectangularBox,
                                                   gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                                   45.0 * M_PI / 180.0);
  const TopoDS_Shape aResult       = PerformCut(aRectangularBox, aNurbsBox);
  ValidateResult(aResult, 5.82843);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusRotatedSquareBox_F3)
{
  TopoDS_Shape aNurbsBox     = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox                  = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  const double r             = sqrt(2.0) / 2.0;
  TopoDS_Shape aSquareBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r, r, 1.0);
  aSquareBox                 = BOPTest_Utilities::RotateShape(aSquareBox,
                                              gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                              45.0 * M_PI / 180.0);
  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aSquareBox);
  ValidateResult(aResult, 5.91421);
}

TEST_F(BCutSimpleTest, RotatedSquareBoxMinusNurbsBox_F4)
{
  TopoDS_Shape aNurbsBox     = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox                  = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  const double r             = sqrt(2.0) / 2.0;
  TopoDS_Shape aSquareBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r, r, 1.0);
  aSquareBox                 = BOPTest_Utilities::RotateShape(aSquareBox,
                                              gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                              45.0 * M_PI / 180.0);
  const TopoDS_Shape aResult = PerformCut(aSquareBox, aNurbsBox);
  ValidateResult(aResult, 2.91421);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusRotatedThinBox_F5)
{
  TopoDS_Shape aNurbsBox     = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox                  = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  constexpr double r         = M_SQRT2;
  TopoDS_Shape     aThinBox  = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r, 0.25, 1.0);
  aThinBox                   = BOPTest_Utilities::RotateShape(aThinBox,
                                            gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                            45.0 * M_PI / 180.0);
  const TopoDS_Shape aResult = PerformCut(aNurbsBox, aThinBox);
  ValidateResult(aResult, 7.03921);
}

TEST_F(BCutSimpleTest, RotatedThinBoxMinusNurbsBox_F6)
{
  TopoDS_Shape aNurbsBox     = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox                  = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  constexpr double r         = M_SQRT2;
  TopoDS_Shape     aThinBox  = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r, 0.25, 1.0);
  aThinBox                   = BOPTest_Utilities::RotateShape(aThinBox,
                                            gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                            45.0 * M_PI / 180.0);
  const TopoDS_Shape aResult = PerformCut(aThinBox, aNurbsBox);
  ValidateResult(aResult, 1.83211);
}

TEST_F(BCutSimpleTest, NurbsBoxMinusRotatedNarrowBox_F7)
{
  TopoDS_Shape aNurbsBox      = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox                   = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  constexpr double r          = 5.5677643628300219;
  TopoDS_Shape     aNarrowBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r / 4.0, 0.25, 1.0);
  aNarrowBox                  = BOPTest_Utilities::RotateShape(aNarrowBox,
                                              gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                              34.73 * M_PI / 180.0);
  const TopoDS_Shape aResult  = PerformCut(aNurbsBox, aNarrowBox);
  ValidateResult(aResult, 7.21677);
}

TEST_F(BCutSimpleTest, RotatedNarrowBoxMinusNurbsBox_F8)
{
  TopoDS_Shape aNurbsBox      = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aNurbsBox                   = BOPTest_Utilities::ConvertToNurbs(aNurbsBox);
  constexpr double r          = 5.5677643628300219;
  TopoDS_Shape     aNarrowBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), r / 4.0, 0.25, 1.0);
  aNarrowBox                  = BOPTest_Utilities::RotateShape(aNarrowBox,
                                              gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                              34.73 * M_PI / 180.0);
  const TopoDS_Shape aResult  = PerformCut(aNarrowBox, aNurbsBox);
  ValidateResult(aResult, 1.54631);
}

TEST_F(BCutSimpleTest, SphereMinusBox_F9)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aResult = PerformCut(aSphere, aBox);
  ValidateResult(aResult, 13.3518);
}

TEST_F(BCutSimpleTest, BoxMinusSphere_G1)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aResult = PerformCut(aBox, aSphere);
  ValidateResult(aResult, 5.2146);
}

TEST_F(BCutSimpleTest, RotatedSphereMinusBox_G2)
{
  TopoDS_Shape aSphere       = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);
  aSphere                    = BOPTest_Utilities::RotateShape(aSphere,
                                           gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                           -90.0 * M_PI / 180.0);
  aSphere                    = BOPTest_Utilities::RotateShape(aSphere,
                                           gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Y)),
                                           -45.0 * M_PI / 180.0);
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aResult = PerformCut(aSphere, aBox);
  ValidateResult(aResult, 13.3517);
}

TEST_F(BCutSimpleTest, BoxMinusRotatedSphere_G3)
{
  TopoDS_Shape aSphere       = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);
  aSphere                    = BOPTest_Utilities::RotateShape(aSphere,
                                           gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                                           -90.0 * M_PI / 180.0);
  aSphere                    = BOPTest_Utilities::RotateShape(aSphere,
                                           gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Y)),
                                           -45.0 * M_PI / 180.0);
  const TopoDS_Shape aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aResult = PerformCut(aBox, aSphere);
  ValidateResult(aResult, 5.2146);
}

TEST_F(BCutSimpleTest, SphereMinusRotatedBox_G4)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);
  TopoDS_Shape       aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox                       = BOPTest_Utilities::RotateShape(aBox,
                                        gp_Ax1(gp_Pnt(0, 0, 1), gp_Dir(gp_Dir::D::Y)),
                                        90.0 * M_PI / 180.0);
  const TopoDS_Shape aResult = PerformCut(aSphere, aBox);
  ValidateResult(aResult, 13.3517);
}

TEST_F(BCutSimpleTest, RotatedBoxMinusSphere_G5)
{
  const TopoDS_Shape aSphere = BOPTest_Utilities::CreateSphere(gp_Pnt(0, 0, 0), 1.0);
  TopoDS_Shape       aBox    = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  aBox                       = BOPTest_Utilities::RotateShape(aBox,
                                        gp_Ax1(gp_Pnt(0, 0, 1), gp_Dir(gp_Dir::D::Y)),
                                        90.0 * M_PI / 180.0);
  const TopoDS_Shape aResult = PerformCut(aBox, aSphere);
  ValidateResult(aResult, 5.2146);
}

TEST_F(BCutSimpleTest, ComplexProfileRevolOperation_G6)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 100.0, 100.0, 40.0);

  gp_Pln                                           aPlane(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 20.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::C, 10.0, 180.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::C, 10.0, 180.0)};
  const TopoDS_Shape aProfile = BOPTest_Utilities::CreateProfile(aPlane, aProfileOps);

  const TopoDS_Shape aRevolution =
    BOPTest_Utilities::CreateRevolution(aProfile,
                                        gp_Ax1(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Y)),
                                        2.0 * M_PI);

  const TopoDS_Shape aResult = PerformCut(aBox, aRevolution);
  ValidateResult(aResult, 41187.4);
}

TEST_F(BCutSimpleTest, BoxMinusTranslatedBox_G7)
{
  const TopoDS_Shape aBox1   = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 3.0, 3.0, 3.0);
  const TopoDS_Shape aBox2   = BOPTest_Utilities::CreateBox(gp_Pnt(0, 3, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aResult = PerformCut(aBox1, aBox2);
  ValidateResult(aResult, 54.0);
}

TEST_F(BCutSimpleTest, BoxMinusPrism_G8)
{

  const TopoDS_Shape aBoxMb = BOPTest_Utilities::CreateBox(gp_Pnt(-0.5, -0.5, -0.5), 1.0, 1.0, 1.0);

  const TopoDS_Face aFace = BOPTest_Utilities::GetFaceByIndex(aBoxMb, 1);

  const TopoDS_Shape aSemiInfPrism =
    BOPTest_Utilities::CreatePrism(aFace, gp_Vec(1000.0, 0.0, 0.0));

  const TopoDS_Shape aBoxAb = BOPTest_Utilities::CreateBox(gp_Pnt(0, -1, -1), 2.0, 2.0, 2.0);

  const TopoDS_Shape aResult = PerformCut(aBoxAb, aSemiInfPrism);
  ValidateResult(aResult, 30.0);
}

TEST_F(BCutSimpleTest, ComplexCylinderConeOperation_G9)
{

  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinder(9.0, 3.0);
  const TopoDS_Shape aCone     = BOPTest_Utilities::CreateCone(7.0, 6.0, 4.0);

  BRepAlgoAPI_Fuse aFuseOp(aCylinder, aCone);
  EXPECT_TRUE(aFuseOp.IsDone()) << "Fuse operation failed";
  const TopoDS_Shape aBody = aFuseOp.Shape();

  TopoDS_Shape aSmallCylinder = BOPTest_Utilities::CreateCylinder(1.0, 9.0);
  aSmallCylinder = BOPTest_Utilities::TranslateShape(aSmallCylinder, gp_Vec(5.0, 0.0, -2.0));

  const TopoDS_Shape aResult = PerformCut(aBody, aSmallCylinder);
  ValidateResult(aResult, 727.481);
}

TEST_F(BCutSimpleTest, ComplexPolygonPrismMinusBox_H1)
{

  std::vector<gp_Pnt> aPoints;
  aPoints.push_back(gp_Pnt(0, 0, 0));
  aPoints.push_back(gp_Pnt(1, 0, 0));
  aPoints.push_back(gp_Pnt(1, 3, 0));
  aPoints.push_back(gp_Pnt(2, 3, 0));
  aPoints.push_back(gp_Pnt(2, 0, 0));
  aPoints.push_back(gp_Pnt(3, 0, 0));
  aPoints.push_back(gp_Pnt(3, 5, 0));
  aPoints.push_back(gp_Pnt(0, 5, 0));

  TopoDS_Wire        aWire  = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  TopoDS_Shape       aFace  = BOPTest_Utilities::CreateFaceFromWire(aWire);
  const TopoDS_Shape aSolid = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 0, 2));

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(-1, 2, 1), 5.0, 1.0, 3.0);

  const TopoDS_Shape aResult = PerformCut(aSolid, aBox);
  ValidateResult(aResult, 68.0);
}

TEST_F(BCutSimpleTest, ComplexPolygonPrismMinusBox_H2)
{

  std::vector<gp_Pnt> aPoints;
  aPoints.push_back(gp_Pnt(0, 0, 0));
  aPoints.push_back(gp_Pnt(1, 0, 0));
  aPoints.push_back(gp_Pnt(1, 3, 0));
  aPoints.push_back(gp_Pnt(2, 3, 0));
  aPoints.push_back(gp_Pnt(2, 0, 0));
  aPoints.push_back(gp_Pnt(3, 0, 0));
  aPoints.push_back(gp_Pnt(3, 5, 0));
  aPoints.push_back(gp_Pnt(0, 5, 0));

  TopoDS_Wire        aWire  = BOPTest_Utilities::CreatePolygonWire(aPoints, true);
  TopoDS_Shape       aFace  = BOPTest_Utilities::CreateFaceFromWire(aWire);
  const TopoDS_Shape aSolid = BOPTest_Utilities::CreatePrism(aFace, gp_Vec(0, 0, 2));

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(-1, 2, 1), 5.0, 1.0, 3.0);

  const TopoDS_Shape aResult = PerformCut(aSolid, aBox);
  ValidateResult(aResult, 68.0);
}

TEST_F(BCutSimpleTest, ComplexCylinderConeOperationPro13307_H3)
{

  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinder(9.0, 3.0);
  const TopoDS_Shape aCone     = BOPTest_Utilities::CreateCone(7.0, 6.0, 4.0);

  BRepAlgoAPI_Fuse aFuseOp(aCylinder, aCone);
  EXPECT_TRUE(aFuseOp.IsDone()) << "Fuse operation failed";
  const TopoDS_Shape aBody = aFuseOp.Shape();

  TopoDS_Shape aSmallCylinder = BOPTest_Utilities::CreateCylinder(1.0, 9.0);
  aSmallCylinder = BOPTest_Utilities::TranslateShape(aSmallCylinder, gp_Vec(5.0, 0.0, -2.0));

  const TopoDS_Shape aResult = PerformCut(aBody, aSmallCylinder);
  ValidateResult(aResult, 727.481);
}

TEST_F(BCutSimpleTest, ComplexProfileForwardForward_H4)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -150.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 98000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileForwardForwardVariation_H5)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -150.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 98000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileForwardReversed_H6)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -150.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 98000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileForwardReversedVariation_H7)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -150.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 98000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileReversedForward_H8)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 98000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileReversedForwardVariation_H9)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 98000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileReversedReversed_I1)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 98000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileReversedReversedVariation_I2)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 98000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileForwardForwardVariation2_I3)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -150.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 52000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileForwardForwardVariation3_I4)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -150.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -3));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 53000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileForwardReversedVariation2_I5)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -150.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 52000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileForwardReversedVariation3_I6)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -150.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 52000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileReversedForwardVariation2_I7)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 0.0, -50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 52000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileReversedForwardVariation3_I8)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 0.0, -50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 52000.0);
}

TEST_F(BCutSimpleTest, ComplexProfileReversedReversedVariation2_I9)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 40), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 0.0, -50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 52000.0);
}
