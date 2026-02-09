

#include <math_BracketedRoot.hpp>
#include <math_Function.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  class QuadraticFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = (theX - 2.0) * (theX - 2.0) - 1.0;
      return true;
    }
  };

  class CubicFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX * theX - theX - 2.0;
      return true;
    }
  };

  class SineFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = sin(theX);
      return true;
    }
  };

  class LinearFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = 2.0 * theX - 4.0;
      return true;
    }
  };

} // namespace

TEST(MathBracketedRootTest, QuadraticRootFinding)
{

  QuadraticFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 0.0, 1.5, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for quadratic function";
  EXPECT_NEAR(aSolver.Root(), 1.0, 1.0e-8) << "Root should be x = 1";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-9) << "Function value at root should be near zero";
  EXPECT_GT(aSolver.NbIterations(), 0) << "Should have performed some iterations";
}

TEST(MathBracketedRootTest, QuadraticSecondRoot)
{

  QuadraticFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 2.5, 4.0, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find second root for quadratic function";
  EXPECT_NEAR(aSolver.Root(), 3.0, 1.0e-8) << "Root should be x = 3";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-9) << "Function value at root should be near zero";
}

TEST(MathBracketedRootTest, CubicRootFinding)
{

  CubicFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 1.0, 2.0, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for cubic function";
  double aRoot = aSolver.Root();
  EXPECT_GT(aRoot, 1.52) << "Root should be approximately 1.521";
  EXPECT_LT(aRoot, 1.53) << "Root should be approximately 1.521";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-8) << "Function value at root should be near zero";
}

TEST(MathBracketedRootTest, SineFunctionRoot)
{

  SineFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 3.0, 3.5, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for sine function";
  EXPECT_NEAR(aSolver.Root(), M_PI, 1.0e-8) << "Root should be PI";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-9) << "Function value at root should be near zero";
}

TEST(MathBracketedRootTest, LinearFunctionRoot)
{

  LinearFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 1.0, 3.0, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for linear function";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-12) << "Root should be x = 2 (exact)";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-12) << "Function value should be exactly zero";
}

TEST(MathBracketedRootTest, CustomTolerance)
{

  QuadraticFunction aFunc;

  math_BracketedRoot aSolver1(aFunc, 0.5, 1.5, 1.0e-3);
  EXPECT_TRUE(aSolver1.IsDone()) << "Should converge with loose tolerance";
  EXPECT_NEAR(aSolver1.Root(), 1.0, 1.0e-2) << "Root should be approximately correct";

  math_BracketedRoot aSolver2(aFunc, 0.5, 1.5, 1.0e-12);
  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with tight tolerance";
  EXPECT_NEAR(aSolver2.Root(), 1.0, 1.0e-10) << "Root should be very accurate";
}

TEST(MathBracketedRootTest, CustomIterationLimit)
{

  CubicFunction aFunc;

  math_BracketedRoot aSolver1(aFunc, 1.0, 2.0, 1.0e-12, 5);
  if (aSolver1.IsDone())
  {
    EXPECT_LE(aSolver1.NbIterations(), 5) << "Should respect iteration limit";
  }

  math_BracketedRoot aSolver2(aFunc, 1.0, 2.0, 1.0e-15, 200);
  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with many iterations allowed";
}

TEST(MathBracketedRootTest, InvalidBounds)
{

  QuadraticFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 3.5, 4.0, 1.0e-10);

  EXPECT_FALSE(aSolver.IsDone()) << "Should fail when bounds don't bracket root";
}

TEST(MathBracketedRootTest, ZeroAtBoundary)
{

  LinearFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 2.0, 3.0, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should handle root at boundary";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-12) << "Should find root at boundary";
}

TEST(MathBracketedRootTest, VeryNarrowBounds)
{

  LinearFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 1.999, 2.001, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should handle narrow bounds";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-8) << "Root should be accurate";
}

TEST(MathBracketedRootTest, ReverseBounds)
{

  QuadraticFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 1.5, 0.0, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should handle reverse bounds";
  EXPECT_NEAR(aSolver.Root(), 1.0, 1.0e-8) << "Should still find correct root";
}

TEST(MathBracketedRootTest, NotDoneState)
{

  QuadraticFunction  aFunc;
  math_BracketedRoot aSolver(aFunc, 3.5, 4.0, 1.0e-10);

  EXPECT_FALSE(aSolver.IsDone()) << "Should not be done for invalid bounds";
}

TEST(MathBracketedRootTest, HighPrecisionRequirement)
{

  SineFunction       aFunc;
  math_BracketedRoot aSolver(aFunc, 3.0, 3.5, 1.0e-15, 200);

  EXPECT_TRUE(aSolver.IsDone()) << "Should converge with high precision requirement";
  EXPECT_NEAR(aSolver.Root(), M_PI, 1.0e-10) << "Root should be very accurate";
  EXPECT_GT(aSolver.NbIterations(), 5) << "Should require several iterations for high precision";
}

TEST(MathBracketedRootTest, CustomZEPS)
{

  QuadraticFunction aFunc;

  math_BracketedRoot aSolver(aFunc, 0.5, 1.5, 1.0e-10, 100, 1.0e-15);

  EXPECT_TRUE(aSolver.IsDone()) << "Should work with custom ZEPS";
  EXPECT_NEAR(aSolver.Root(), 1.0, 1.0e-8) << "Root should be accurate";
}
