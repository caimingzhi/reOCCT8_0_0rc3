

#include <math_PSO.hpp>
#include <math_PSOParticlesPool.hpp>
#include <math_MultipleVarFunction.hpp>
#include <math_Vector.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>

#include <cmath>

namespace
{

  class QuadraticFunction : public math_MultipleVarFunction
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double dx = theX(1) - 1.0;
      double dy = theX(2) - 2.0;
      theF      = dx * dx + dy * dy;
      return true;
    }
  };

  class Quadratic1DFunction : public math_MultipleVarFunction
  {
  public:
    int NbVariables() const override { return 1; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double dx = theX(1) - 3.0;
      theF      = dx * dx;
      return true;
    }
  };

  class RosenbrockFunction : public math_MultipleVarFunction
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double x  = theX(1);
      double y  = theX(2);
      double dx = 1.0 - x;
      double dy = y - x * x;
      theF      = dx * dx + 100.0 * dy * dy;
      return true;
    }
  };

  class MultiModalFunction : public math_MultipleVarFunction
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double x  = theX(1);
      double y  = theX(2);
      double dx = x - M_PI;
      double dy = y - M_PI;
      theF      = -cos(x) * cos(y) * exp(-(dx * dx + dy * dy));
      return true;
    }
  };

  class Quadratic3DFunction : public math_MultipleVarFunction
  {
  public:
    int NbVariables() const override { return 3; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double x = theX(1);
      double y = theX(2);
      double z = theX(3);
      theF     = x * x + 2.0 * y * y + 3.0 * z * z;
      return true;
    }
  };

} // namespace

TEST(MathPSOTest, QuadraticFunctionOptimization)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 4.0;
  aUpperBorder(2) = 5.0;

  math_Vector aSteps(1, 2);
  aSteps(1) = 0.1;
  aSteps(2) = 0.1;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 20, 50);

  double      aValue;
  math_Vector aSolution(1, 2);

  aSolver.Perform(aSteps, aValue, aSolution);

  EXPECT_NEAR(aSolution(1), 1.0, 0.5) << "PSO should find solution near x = 1";
  EXPECT_NEAR(aSolution(2), 2.0, 0.5) << "PSO should find solution near y = 2";
  EXPECT_LT(aValue, 1.0) << "Function value should be small near minimum";
}

TEST(MathPSOTest, OneDimensionalOptimization)
{

  Quadratic1DFunction aFunc;

  math_Vector aLowerBorder(1, 1);
  aLowerBorder(1) = 0.0;

  math_Vector aUpperBorder(1, 1);
  aUpperBorder(1) = 6.0;

  math_Vector aSteps(1, 1);
  aSteps(1) = 0.1;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 15, 30);

  double      aValue;
  math_Vector aSolution(1, 1);

  aSolver.Perform(aSteps, aValue, aSolution);

  EXPECT_NEAR(aSolution(1), 3.0, 0.5) << "PSO should find solution near x = 3";
  EXPECT_LT(aValue, 0.5) << "Function value should be small near minimum";
}

TEST(MathPSOTest, ThreeDimensionalOptimization)
{

  Quadratic3DFunction aFunc;

  math_Vector aLowerBorder(1, 3);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -2.0;
  aLowerBorder(3) = -2.0;

  math_Vector aUpperBorder(1, 3);
  aUpperBorder(1) = 2.0;
  aUpperBorder(2) = 2.0;
  aUpperBorder(3) = 2.0;

  math_Vector aSteps(1, 3);
  aSteps(1) = 0.1;
  aSteps(2) = 0.1;
  aSteps(3) = 0.1;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 25, 40);

  double      aValue;
  math_Vector aSolution(1, 3);

  aSolver.Perform(aSteps, aValue, aSolution);

  EXPECT_NEAR(aSolution(1), 0.0, 0.5) << "PSO should find solution near x = 0";
  EXPECT_NEAR(aSolution(2), 0.0, 0.5) << "PSO should find solution near y = 0";
  EXPECT_NEAR(aSolution(3), 0.0, 0.5) << "PSO should find solution near z = 0";
  EXPECT_LT(aValue, 1.0) << "Function value should be small near minimum";
}

TEST(MathPSOTest, CustomParticleCount)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 4.0;
  aUpperBorder(2) = 5.0;

  math_Vector aSteps(1, 2);
  aSteps(1) = 0.2;
  aSteps(2) = 0.2;

  math_PSO aSolver1(&aFunc, aLowerBorder, aUpperBorder, aSteps, 5, 20);

  double      aValue1;
  math_Vector aSolution1(1, 2);

  aSolver1.Perform(aSteps, aValue1, aSolution1);

  EXPECT_TRUE(aSolution1(1) >= -2.0 && aSolution1(1) <= 4.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSolution1(2) >= -1.0 && aSolution1(2) <= 5.0) << "Solution should be within bounds";

  math_PSO aSolver2(&aFunc, aLowerBorder, aUpperBorder, aSteps, 50, 30);

  double      aValue2;
  math_Vector aSolution2(1, 2);

  aSolver2.Perform(aSteps, aValue2, aSolution2);

  EXPECT_TRUE(aSolution2(1) >= -2.0 && aSolution2(1) <= 4.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSolution2(2) >= -1.0 && aSolution2(2) <= 5.0) << "Solution should be within bounds";
}

TEST(MathPSOTest, CustomIterationCount)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 4.0;
  aUpperBorder(2) = 5.0;

  math_Vector aSteps(1, 2);
  aSteps(1) = 0.1;
  aSteps(2) = 0.1;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 20, 10);

  double      aValue;
  math_Vector aSolution(1, 2);

  aSolver.Perform(aSteps, aValue, aSolution, 5);

  EXPECT_TRUE(aSolution(1) >= -2.0 && aSolution(1) <= 4.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSolution(2) >= -1.0 && aSolution(2) <= 5.0) << "Solution should be within bounds";

  aSolver.Perform(aSteps, aValue, aSolution, 100);

  EXPECT_TRUE(aSolution(1) >= -2.0 && aSolution(1) <= 4.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSolution(2) >= -1.0 && aSolution(2) <= 5.0) << "Solution should be within bounds";
}

TEST(MathPSOTest, RosenbrockOptimization)
{

  RosenbrockFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 2.0;
  aUpperBorder(2) = 3.0;

  math_Vector aSteps(1, 2);
  aSteps(1) = 0.1;
  aSteps(2) = 0.1;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 40, 100);

  double      aValue;
  math_Vector aSolution(1, 2);

  aSolver.Perform(aSteps, aValue, aSolution);

  EXPECT_TRUE(aSolution(1) >= -2.0 && aSolution(1) <= 2.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSolution(2) >= -1.0 && aSolution(2) <= 3.0) << "Solution should be within bounds";
  EXPECT_LT(aValue, 100.0) << "Function value should improve from random start";
}

TEST(MathPSOTest, MultiModalOptimization)
{

  MultiModalFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = 0.0;
  aLowerBorder(2) = 0.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 2.0 * M_PI;
  aUpperBorder(2) = 2.0 * M_PI;

  math_Vector aSteps(1, 2);
  aSteps(1) = 0.2;
  aSteps(2) = 0.2;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 30, 50);

  double      aValue;
  math_Vector aSolution(1, 2);

  aSolver.Perform(aSteps, aValue, aSolution);

  EXPECT_TRUE(aSolution(1) >= 0.0 && aSolution(1) <= 2.0 * M_PI)
    << "Solution should be within bounds";
  EXPECT_TRUE(aSolution(2) >= 0.0 && aSolution(2) <= 2.0 * M_PI)
    << "Solution should be within bounds";
  EXPECT_LT(aValue, 0.0) << "Should find negative value (local/global minimum)";
}

TEST(MathPSOTest, DifferentStepSizes)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 4.0;
  aUpperBorder(2) = 5.0;

  math_Vector aLargeSteps(1, 2);
  aLargeSteps(1) = 0.5;
  aLargeSteps(2) = 0.5;

  math_PSO aSolver1(&aFunc, aLowerBorder, aUpperBorder, aLargeSteps, 15, 20);

  double      aValue1;
  math_Vector aSolution1(1, 2);

  aSolver1.Perform(aLargeSteps, aValue1, aSolution1);

  EXPECT_TRUE(aSolution1(1) >= -2.0 && aSolution1(1) <= 4.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSolution1(2) >= -1.0 && aSolution1(2) <= 5.0) << "Solution should be within bounds";

  math_Vector aSmallSteps(1, 2);
  aSmallSteps(1) = 0.05;
  aSmallSteps(2) = 0.05;

  math_PSO aSolver2(&aFunc, aLowerBorder, aUpperBorder, aSmallSteps, 15, 20);

  double      aValue2;
  math_Vector aSolution2(1, 2);

  aSolver2.Perform(aSmallSteps, aValue2, aSolution2);

  EXPECT_TRUE(aSolution2(1) >= -2.0 && aSolution2(1) <= 4.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSolution2(2) >= -1.0 && aSolution2(2) <= 5.0) << "Solution should be within bounds";
}

TEST(MathPSOTest, PSOParticlesPoolIntegration)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 4.0;
  aUpperBorder(2) = 5.0;

  math_Vector aSteps(1, 2);
  aSteps(1) = 0.1;
  aSteps(2) = 0.1;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 20, 30);

  int                   aNbParticles = 20;
  math_PSOParticlesPool aParticlesPool(aNbParticles, 2);

  double      aValue;
  math_Vector aSolution(1, 2);

  aSolver.Perform(aParticlesPool, aNbParticles, aValue, aSolution);

  EXPECT_TRUE(aSolution(1) >= -2.0 && aSolution(1) <= 4.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSolution(2) >= -1.0 && aSolution(2) <= 5.0) << "Solution should be within bounds";
}

TEST(MathPSOTest, SmallSearchSpace)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = 0.8;
  aLowerBorder(2) = 1.8;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 1.2;
  aUpperBorder(2) = 2.2;

  math_Vector aSteps(1, 2);
  aSteps(1) = 0.05;
  aSteps(2) = 0.05;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 10, 20);

  double      aValue;
  math_Vector aSolution(1, 2);

  aSolver.Perform(aSteps, aValue, aSolution);

  EXPECT_NEAR(aSolution(1), 1.0, 0.3) << "Should find solution close to minimum in small space";
  EXPECT_NEAR(aSolution(2), 2.0, 0.3) << "Should find solution close to minimum in small space";
  EXPECT_LT(aValue, 0.5) << "Should find small function value";
}

TEST(MathPSOTest, AsymmetricBounds)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -5.0;
  aLowerBorder(2) = 1.5;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 2.0;
  aUpperBorder(2) = 10.0;

  math_Vector aSteps(1, 2);
  aSteps(1) = 0.2;
  aSteps(2) = 0.2;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 25, 40);

  double      aValue;
  math_Vector aSolution(1, 2);

  aSolver.Perform(aSteps, aValue, aSolution);

  EXPECT_TRUE(aSolution(1) >= -5.0 && aSolution(1) <= 2.0) << "Solution should be within x bounds";
  EXPECT_TRUE(aSolution(2) >= 1.5 && aSolution(2) <= 10.0) << "Solution should be within y bounds";
  EXPECT_NEAR(aSolution(1), 1.0, 1.5) << "Should find solution reasonably close to minimum";
  EXPECT_NEAR(aSolution(2), 2.0, 2.0) << "Should find solution reasonably close to minimum";
}

TEST(MathPSOTest, MinimalConfiguration)
{

  Quadratic1DFunction aFunc;

  math_Vector aLowerBorder(1, 1);
  aLowerBorder(1) = 0.0;

  math_Vector aUpperBorder(1, 1);
  aUpperBorder(1) = 6.0;

  math_Vector aSteps(1, 1);
  aSteps(1) = 0.5;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 3, 5);

  double      aValue;
  math_Vector aSolution(1, 1);

  aSolver.Perform(aSteps, aValue, aSolution, 3);

  EXPECT_TRUE(aSolution(1) >= 0.0 && aSolution(1) <= 6.0) << "Solution should be within bounds";
}

TEST(MathPSOTest, RepeatedPerformCalls)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 4.0;
  aUpperBorder(2) = 5.0;

  math_Vector aSteps(1, 2);
  aSteps(1) = 0.1;
  aSteps(2) = 0.1;

  math_PSO aSolver(&aFunc, aLowerBorder, aUpperBorder, aSteps, 15, 20);

  double      aValue1, aValue2;
  math_Vector aSolution1(1, 2), aSolution2(1, 2);

  aSolver.Perform(aSteps, aValue1, aSolution1);

  EXPECT_TRUE(aSolution1(1) >= -2.0 && aSolution1(1) <= 4.0)
    << "First solution should be within bounds";
  EXPECT_TRUE(aSolution1(2) >= -1.0 && aSolution1(2) <= 5.0)
    << "First solution should be within bounds";

  aSolver.Perform(aSteps, aValue2, aSolution2);

  EXPECT_TRUE(aSolution2(1) >= -2.0 && aSolution2(1) <= 4.0)
    << "Second solution should be within bounds";
  EXPECT_TRUE(aSolution2(2) >= -1.0 && aSolution2(2) <= 5.0)
    << "Second solution should be within bounds";
}
