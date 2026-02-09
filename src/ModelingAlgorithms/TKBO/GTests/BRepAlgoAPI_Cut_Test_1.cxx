

#include "BOPTest_Utilities.hpp"

class BCutSimpleTest1 : public BRepAlgoAPI_TestBase
{
};

TEST_F(BCutSimpleTest1, ComplexProfileReversedReversedVariation3_J1)
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
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -3));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 53000.0);
}

TEST_F(BCutSimpleTest1, ComplexMultiCutProfileForwardForwardForward_J2)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 175, 250, -40);

  const TopoDS_Shape aPrism2 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(25, 25, 50), 50, 75, -30);

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate1 = aCutOp1.Shape();

  const TopoDS_Shape aPrism3 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(100, 150, 50), 50, 75, -30);

  BRepAlgoAPI_Cut aCutOp2(aIntermediate1, aPrism3);
  EXPECT_TRUE(aCutOp2.IsDone()) << "Second cut operation failed";
  const TopoDS_Shape aIntermediate2 = aCutOp2.Shape();

  const TopoDS_Shape aPrism4 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(50, -75, 50), 75, 100, -30);

  const TopoDS_Shape aResult = PerformCut(aIntermediate2, aPrism4);
  ValidateResult(aResult, 134500.0);
}

TEST_F(BCutSimpleTest1, ComplexProfileWithTranslationForwardReversedForward_J3)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 175, 250, -40);

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate1 = aCutOp1.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 100.0, -150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp2(aIntermediate1, aPrism3);
  EXPECT_TRUE(aCutOp2.IsDone()) << "Second cut operation failed";
  const TopoDS_Shape aIntermediate2 = aCutOp2.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps4 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile4 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps4);
  TopoDS_Shape       aPrism4   = BOPTest_Utilities::CreatePrism(aProfile4, gp_Vec(0, 0, -30));

  aPrism4 = BOPTest_Utilities::TranslateShape(aPrism4, gp_Vec(-10, 0, 0));

  const TopoDS_Shape aResult = PerformCut(aIntermediate2, aPrism4);
  ValidateResult(aResult, 134500.0);
}

TEST_F(BCutSimpleTest1, ComplexProfileReversedReversedForward_J4)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 175, 250, -40);

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 100.0, -150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate1 = aCutOp1.Shape();

  BRepAlgoAPI_Cut aCutOp2(aIntermediate1, aPrism3);
  EXPECT_TRUE(aCutOp2.IsDone()) << "Second cut operation failed";
  const TopoDS_Shape aIntermediate2 = aCutOp2.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps4 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile4 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps4);
  const TopoDS_Shape aPrism4   = BOPTest_Utilities::CreatePrism(aProfile4, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate2, aPrism4);
  ValidateResult(aResult, 134500.0);
}

TEST_F(BCutSimpleTest1, ComplexProfileForwardForwardForwardVariation_J5)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 175, 250, -40);

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 100.0, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate1 = aCutOp1.Shape();

  BRepAlgoAPI_Cut aCutOp2(aIntermediate1, aPrism3);
  EXPECT_TRUE(aCutOp2.IsDone()) << "Second cut operation failed";
  const TopoDS_Shape aIntermediate2 = aCutOp2.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps4 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile4 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps4);
  const TopoDS_Shape aPrism4   = BOPTest_Utilities::CreatePrism(aProfile4, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate2, aPrism4);
  ValidateResult(aResult, 134500.0);
}

TEST_F(BCutSimpleTest1, ComplexProfileForwardReversedForwardVariation_J6)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 175, 250, -40);

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 100.0, -150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate1 = aCutOp1.Shape();

  BRepAlgoAPI_Cut aCutOp2(aIntermediate1, aPrism3);
  EXPECT_TRUE(aCutOp2.IsDone()) << "Second cut operation failed";
  const TopoDS_Shape aIntermediate2 = aCutOp2.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps4 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile4 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps4);
  const TopoDS_Shape aPrism4   = BOPTest_Utilities::CreatePrism(aProfile4, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate2, aPrism4);
  ValidateResult(aResult, 134500.0);
}

TEST_F(BCutSimpleTest1, ComplexProfileReversedReversedForwardVariation_J7)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 175, 250, -40);

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 100.0, -150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate1 = aCutOp1.Shape();

  BRepAlgoAPI_Cut aCutOp2(aIntermediate1, aPrism3);
  EXPECT_TRUE(aCutOp2.IsDone()) << "Second cut operation failed";
  const TopoDS_Shape aIntermediate2 = aCutOp2.Shape();

  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps4 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile4 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps4);
  const TopoDS_Shape aPrism4   = BOPTest_Utilities::CreatePrism(aProfile4, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate2, aPrism4);
  ValidateResult(aResult, 134500.0);
}

TEST_F(BCutSimpleTest1, SameOrientedProfileForwardForward_J8)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -10), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, -10.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, 30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, SameOrientedProfileForwardForwardWithReversed_J9)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -10), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, -10.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, 30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, SameOrientedProfileForwardReversed_K1)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -1), gp_Dir(gp_Dir::D::X));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, -10.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, 30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, SameOrientedProfileForwardObjectReversedTool_K2)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -1), gp_Dir(gp_Dir::D::X));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, -10.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, 30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, SameOrientedProfileReversedObjectForwardTool_K3)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -10), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, -10.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, 30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, SameOrientedProfileReversedObjectReversedTool_K4)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 40.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -200.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 200.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, -40));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::P,
                                        0.0,
                                        0.0,
                                        -1.0,
                                        1.0,
                                        0.0,
                                        0.0),
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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -10), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, -10.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, 30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, SameOrientedProfileForwardReversedRepeated_K5)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -1), gp_Dir(gp_Dir::D::X));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, -10.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, 30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, SameOrientedProfileForwardObjectReversedToolVar_K6)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -1), gp_Dir(gp_Dir::D::X));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, -10.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, 30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, ComplexMultiStepProfileAllForward_K7)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 175, 250, -40);

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 50), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate1 = aCutOp1.Shape();

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -1), gp_Dir(gp_Dir::D::X));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 20.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 100.0, -150.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  BRepAlgoAPI_Cut aCutOp2(aIntermediate1, aPrism3);
  EXPECT_TRUE(aCutOp2.IsDone()) << "Second cut operation failed";
  const TopoDS_Shape aIntermediate2 = aCutOp2.Shape();

  gp_Pln                                           aPlane4(gp_Pnt(0, 0, 25), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps4 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 100.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile4 = BOPTest_Utilities::CreateProfile(aPlane4, aProfileOps4);
  const TopoDS_Shape aPrism4   = BOPTest_Utilities::CreatePrism(aProfile4, gp_Vec(0, 0, -5));

  const TopoDS_Shape aResult = PerformCut(aIntermediate2, aPrism4);
  ValidateResult(aResult, 145250.0);
}

TEST_F(BCutSimpleTest1, DiffOrientedProfileAllForward_K8)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -1), gp_Dir(gp_Dir::D::X));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -125.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 75.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -75.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 98000.0);
}

TEST_F(BCutSimpleTest1, DiffOrientedProfileAllForwardVar_K9)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -1), gp_Dir(gp_Dir::D::X));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 25.0, -125.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -50.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, DiffOrientedProfileAllForward_L1)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -1), gp_Dir(gp_Dir::D::X));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 50.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -280.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, -25.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, DiffOrientedProfileForwardObjectReversedTool_L2)
{

  const TopoDS_Shape aPrism1 =
    BOPTest_Utilities::CreateRectangularPrism(gp_Pnt(0, 0, 40), 150, 200, -40);

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

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, 20), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 20.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, 255.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, -280.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::X, 25.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::Y, 280.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, 30));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 97000.0);
}

TEST_F(BCutSimpleTest1, RolexCaseForwardForward_L3)
{

  gp_Pln                                           aPlane1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps1 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::C, 60.0, 360.0)};
  const TopoDS_Shape aProfile1 = BOPTest_Utilities::CreateProfile(aPlane1, aProfileOps1);
  const TopoDS_Shape aPrism1   = BOPTest_Utilities::CreatePrism(aProfile1, gp_Vec(0, 0, 20));

  gp_Pln                                           aPlane2(gp_Pnt(0, 0, 20), gp_Dir(gp_Dir::D::Z));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps2 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 20.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 10.0, -20.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::C, 40.0, 360.0)};
  const TopoDS_Shape aProfile2 = BOPTest_Utilities::CreateProfile(aPlane2, aProfileOps2);
  const TopoDS_Shape aPrism2   = BOPTest_Utilities::CreatePrism(aProfile2, gp_Vec(0, 0, -6));

  BRepAlgoAPI_Cut aCutOp1(aPrism1, aPrism2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  gp_Pln                                           aPlane3(gp_Pnt(0, 0, -1), gp_Dir(gp_Dir::D::X));
  std::vector<BOPTest_Utilities::ProfileOperation> aProfileOps3 = {
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::O, 0.0, 0.0, 23.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::F, 50.0, -10.0),
    BOPTest_Utilities::ProfileOperation(BOPTest_Utilities::ProfileCmd::C, -30.0, 360.0)};
  const TopoDS_Shape aProfile3 = BOPTest_Utilities::CreateProfile(aPlane3, aProfileOps3);
  const TopoDS_Shape aPrism3   = BOPTest_Utilities::CreatePrism(aProfile3, gp_Vec(0, 0, -9));

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aPrism3);
  ValidateResult(aResult, 30153.0);
}

TEST_F(BCutSimpleTest1, RolexCaseForwardObjectReversedTool_L4)
{

  const TopoDS_Shape aCylinder1 = BOPTest_Utilities::CreateCylinder(60.0, 20.0);

  gp_Trsf aTrsf2;
  aTrsf2.SetTranslation(gp_Vec(0, 0, 20));
  const TopoDS_Shape aCylinder2 = BOPTest_Utilities::CreateCylinder(40.0, 6.0).Moved(aTrsf2);

  BRepAlgoAPI_Cut aCutOp1(aCylinder1, aCylinder2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  gp_Trsf aTrsf3;
  aTrsf3.SetTranslation(gp_Vec(0, 0, 14));
  const TopoDS_Shape aCylinder3 = BOPTest_Utilities::CreateCylinder(30.0, 9.0).Moved(aTrsf3);

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aCylinder3);
  ValidateResult(aResult, 30153.0);
}

TEST_F(BCutSimpleTest1, RolexCaseForwardReversed_L5)
{

  const TopoDS_Shape aCylinder1 = BOPTest_Utilities::CreateCylinder(60.0, 20.0);

  gp_Trsf aTrsf2;
  aTrsf2.SetTranslation(gp_Vec(0, 0, 20));
  const TopoDS_Shape aCylinder2 = BOPTest_Utilities::CreateCylinder(40.0, 6.0).Moved(aTrsf2);

  BRepAlgoAPI_Cut aCutOp1(aCylinder1, aCylinder2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  gp_Trsf aTrsf3;
  aTrsf3.SetTranslation(gp_Vec(0, 0, 23));
  const TopoDS_Shape aCylinder3 = BOPTest_Utilities::CreateCylinder(30.0, 9.0).Moved(aTrsf3);

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aCylinder3);
  ValidateResult(aResult, 30153.0);
}

TEST_F(BCutSimpleTest1, RolexCaseForwardReversedVar_L6)
{

  const TopoDS_Shape aCylinder1 = BOPTest_Utilities::CreateCylinder(60.0, 20.0);

  gp_Trsf aTrsf2;
  aTrsf2.SetTranslation(gp_Vec(0, 0, 20));
  const TopoDS_Shape aCylinder2 = BOPTest_Utilities::CreateCylinder(40.0, 6.0).Moved(aTrsf2);

  BRepAlgoAPI_Cut aCutOp1(aCylinder1, aCylinder2);
  EXPECT_TRUE(aCutOp1.IsDone()) << "First cut operation failed";
  const TopoDS_Shape aIntermediate = aCutOp1.Shape();

  gp_Trsf aTrsf3;
  aTrsf3.SetTranslation(gp_Vec(0, 0, 14));
  const TopoDS_Shape aCylinder3 = BOPTest_Utilities::CreateCylinder(30.0, 9.0).Moved(aTrsf3);

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aCylinder3);
  ValidateResult(aResult, 30153.0);
}

TEST_F(BCutSimpleTest1, SimpleCylinderCutOperation_L8)
{

  const TopoDS_Shape aCylinder1 = BOPTest_Utilities::CreateCylinder(20.0, 100.0);

  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(0, 0, 50));
  const TopoDS_Shape aCylinder2 = BOPTest_Utilities::CreateCylinder(20.0, 100.0).Moved(aTrsf);

  const TopoDS_Shape aResult = PerformCut(aCylinder1, aCylinder2);
  ValidateResult(aResult, 8796.46);
}

TEST_F(BCutSimpleTest1, ComplexFaceBasedOperation_L9)
{

  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 10.0, 10.0, 10.0);

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 10), 5.0, 5.0, 5.0);

  const TopoDS_Shape aResult = PerformCut(aBox1, aBox2);

  ValidateResult(aResult, 750.0);
}

TEST_F(BCutSimpleTest1, ComplexFaceBasedCompSolidOperation_M1)
{

  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 10.0, 10.0, 10.0);

  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(2, 2, 10), 5.0, 5.0, 5.0);

  const TopoDS_Shape aResult = PerformCut(aBox1, aBox2);

  ValidateResult(aResult, 750.0);
}

TEST_F(BCutSimpleTest1, BoxCutCylinderThenCutByBox_M2)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 10.0, 10.0, 10.0);

  const TopoDS_Shape aBoxCopy = aBox;

  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(5, 5, -2));
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinder(2.0, 4.0).Moved(aTrsf);

  const TopoDS_Shape aIntermediate = PerformCut(aBoxCopy, aCylinder);

  const TopoDS_Shape aResult = PerformCut(aIntermediate, aBox);

  EXPECT_TRUE(aResult.IsNull() || BOPTest_Utilities::GetSurfaceArea(aResult) < 0.1)
    << "Expected empty or very small result";
}

TEST_F(BCutSimpleTest1, BoxCutByPreviousResult_M3)
{

  const TopoDS_Shape aBox = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 10.0, 10.0, 10.0);

  const TopoDS_Shape aBoxCopy = aBox;

  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(5, 5, -2));
  const TopoDS_Shape aCylinder = BOPTest_Utilities::CreateCylinder(2.0, 4.0).Moved(aTrsf);

  const TopoDS_Shape aIntermediate = PerformCut(aBoxCopy, aCylinder);

  const TopoDS_Shape aResult = PerformCut(aBox, aIntermediate);

  ValidateResult(aResult, 50.2655);
}
