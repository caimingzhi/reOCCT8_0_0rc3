

#include <math_DoubleTab.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <Precision.hpp>

TEST(MathDoubleTabTest, DefaultConstructor)
{

  math_DoubleTab aTab(1, 3, 1, 3);

  aTab.Init(5.0);

  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      EXPECT_DOUBLE_EQ(aTab.Value(anI, aJ), 5.0);
      EXPECT_DOUBLE_EQ(aTab(anI, aJ), 5.0);
    }
  }
}

TEST(MathDoubleTabTest, ExternalArrayConstructor)
{

  double anArray[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

  math_DoubleTab aTab(anArray, 1, 3, 1, 3);

  int anIndex = 0;
  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      EXPECT_DOUBLE_EQ(aTab.Value(anI, aJ), anArray[anIndex]);
      anIndex++;
    }
  }
}

TEST(MathDoubleTabTest, CopyConstructor)
{

  math_DoubleTab aOriginal(1, 3, 1, 3);
  aOriginal.Init(10.0);

  aOriginal.Value(1, 1) = 1.5;
  aOriginal.Value(2, 2) = 2.5;
  aOriginal.Value(3, 3) = 3.5;

  math_DoubleTab aCopy(aOriginal);

  EXPECT_DOUBLE_EQ(aCopy.Value(1, 1), 1.5);
  EXPECT_DOUBLE_EQ(aCopy.Value(2, 2), 2.5);
  EXPECT_DOUBLE_EQ(aCopy.Value(3, 3), 3.5);
  EXPECT_DOUBLE_EQ(aCopy.Value(1, 2), 10.0);
}

TEST(MathDoubleTabTest, InitOperation)
{
  math_DoubleTab aTab(0, 2, 0, 2);

  aTab.Init(7.5);

  for (int anI = 0; anI <= 2; anI++)
  {
    for (int aJ = 0; aJ <= 2; aJ++)
    {
      EXPECT_DOUBLE_EQ(aTab.Value(anI, aJ), 7.5);
    }
  }
}

TEST(MathDoubleTabTest, ValueAccess)
{
  math_DoubleTab aTab(1, 2, 1, 2);

  aTab.Value(1, 1) = 11.0;
  aTab.Value(1, 2) = 12.0;
  aTab.Value(2, 1) = 21.0;
  aTab.Value(2, 2) = 22.0;

  EXPECT_DOUBLE_EQ(aTab(1, 1), 11.0);
  EXPECT_DOUBLE_EQ(aTab(1, 2), 12.0);
  EXPECT_DOUBLE_EQ(aTab(2, 1), 21.0);
  EXPECT_DOUBLE_EQ(aTab(2, 2), 22.0);
}

TEST(MathDoubleTabTest, OperatorAccess)
{
  math_DoubleTab aTab(-1, 1, -1, 1);

  aTab(-1, -1) = -11.0;
  aTab(-1, 0)  = -10.0;
  aTab(-1, 1)  = -9.0;
  aTab(0, -1)  = -1.0;
  aTab(0, 0)   = 0.0;
  aTab(0, 1)   = 1.0;
  aTab(1, -1)  = 9.0;
  aTab(1, 0)   = 10.0;
  aTab(1, 1)   = 11.0;

  EXPECT_DOUBLE_EQ(aTab.Value(-1, -1), -11.0);
  EXPECT_DOUBLE_EQ(aTab.Value(-1, 0), -10.0);
  EXPECT_DOUBLE_EQ(aTab.Value(-1, 1), -9.0);
  EXPECT_DOUBLE_EQ(aTab.Value(0, -1), -1.0);
  EXPECT_DOUBLE_EQ(aTab.Value(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(aTab.Value(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(aTab.Value(1, -1), 9.0);
  EXPECT_DOUBLE_EQ(aTab.Value(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(aTab.Value(1, 1), 11.0);
}

TEST(MathDoubleTabTest, CopyMethod)
{

  math_DoubleTab aSource(1, 2, 1, 2);
  aSource.Value(1, 1) = 100.0;
  aSource.Value(1, 2) = 200.0;
  aSource.Value(2, 1) = 300.0;
  aSource.Value(2, 2) = 400.0;

  math_DoubleTab aDest(1, 2, 1, 2);
  aDest.Init(0.0);

  aSource.Copy(aDest);

  EXPECT_DOUBLE_EQ(aDest.Value(1, 1), 100.0);
  EXPECT_DOUBLE_EQ(aDest.Value(1, 2), 200.0);
  EXPECT_DOUBLE_EQ(aDest.Value(2, 1), 300.0);
  EXPECT_DOUBLE_EQ(aDest.Value(2, 2), 400.0);
}

TEST(MathDoubleTabTest, SmallArrayOptimization)
{

  math_DoubleTab aSmallTab(1, 4, 1, 4);
  aSmallTab.Init(42.0);

  aSmallTab.Value(2, 3) = 123.45;
  EXPECT_DOUBLE_EQ(aSmallTab.Value(2, 3), 123.45);
  EXPECT_DOUBLE_EQ(aSmallTab.Value(1, 1), 42.0);
}

TEST(MathDoubleTabTest, LargeArrayAllocation)
{

  math_DoubleTab aLargeTab(1, 5, 1, 5);
  aLargeTab.Init(99.99);

  aLargeTab.Value(3, 4) = 987.65;
  EXPECT_DOUBLE_EQ(aLargeTab.Value(3, 4), 987.65);
  EXPECT_DOUBLE_EQ(aLargeTab.Value(1, 1), 99.99);
}

TEST(MathDoubleTabTest, SingleElement)
{

  math_DoubleTab aSingle(5, 5, 10, 10);
  aSingle.Value(5, 10) = 777.0;

  EXPECT_DOUBLE_EQ(aSingle.Value(5, 10), 777.0);
  EXPECT_DOUBLE_EQ(aSingle(5, 10), 777.0);
}

TEST(MathDoubleTabTest, NegativeIndices)
{

  math_DoubleTab aNegTab(-5, -1, -3, -1);
  aNegTab.Init(-1.0);

  aNegTab.Value(-3, -2) = -999.0;
  EXPECT_DOUBLE_EQ(aNegTab.Value(-3, -2), -999.0);
  EXPECT_DOUBLE_EQ(aNegTab.Value(-5, -3), -1.0);
}
