

#include "BOPTest_Utilities.hpp"

class BOPCommonSimpleTest : public BRepAlgoAPI_TestBase
{
};

TEST_F(BOPCommonSimpleTest, IdenticalBoxes_A1)
{
  const TopoDS_Shape aBox1 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  const TopoDS_Shape aBox2 = BOPTest_Utilities::CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);

  const TopoDS_Shape aResult = PerformCommon(aBox1, aBox2);
  ValidateResult(aResult, 6.0);
}
