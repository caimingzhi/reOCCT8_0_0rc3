

#include <math_ComputeKronrodPointsAndWeights.hpp>

#include <gtest/gtest.h>

TEST(math_ComputeKronrodPointsAndWeights_Test, OCC33048_ComputeWithOrder125)
{

  bool isOK = true;
  try
  {
    math_ComputeKronrodPointsAndWeights aCalc(125);
    EXPECT_TRUE(aCalc.IsDone()) << "Kronrod points and weights calculation should succeed";
    isOK = aCalc.IsDone();
  }
  catch (...)
  {
    FAIL() << "Exception occurred during calculation of Kronrod points and weights";
    isOK = false;
  }

  EXPECT_TRUE(isOK);
}
