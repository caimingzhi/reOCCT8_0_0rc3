

#include <math_BissecNewton.hpp>
#include <math_FunctionWithDerivative.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  class QuadraticWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = (theX - 2.0) * (theX - 2.0) - 1.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 2.0 * (theX - 2.0);
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = (theX - 2.0) * (theX - 2.0) - 1.0;
      theD = 2.0 * (theX - 2.0);
      return true;
    }
  };

  class CubicWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX * theX - theX - 2.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 3.0 * theX * theX - 1.0;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = theX * theX * theX - theX - 2.0;
      theD = 3.0 * theX * theX - 1.0;
      return true;
    }
  };

  class SineWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = sin(theX);
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = cos(theX);
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = sin(theX);
      theD = cos(theX);
      return true;
    }
  };

  class CubicZeroDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX * theX;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 3.0 * theX * theX;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = theX * theX * theX;
      theD = 3.0 * theX * theX;
      return true;
    }
  };

} // namespace

TEST(MathBissecNewtonTest, QuadraticRootFinding)
{

  QuadraticWithDerivative aFunc;

  math_BissecNewton aSolver(1.0e-10);
  aSolver.Perform(aFunc, 0.0, 1.5, 100);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for quadratic function";
  EXPECT_NEAR(aSolver.Root(), 1.0, 1.0e-8) << "Root should be x = 1";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be zero";
  EXPECT_NEAR(aSolver.Derivative(), -2.0, 1.0e-8) << "Derivative at x=1 should be -2";
}

TEST(MathBissecNewtonTest, QuadraticSecondRoot)
{

  QuadraticWithDerivative aFunc;

  math_BissecNewton aSolver(1.0e-10);
  aSolver.Perform(aFunc, 2.5, 4.0, 100);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find second root for quadratic function";
  EXPECT_NEAR(aSolver.Root(), 3.0, 1.0e-8) << "Root should be x = 3";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be zero";
  EXPECT_NEAR(aSolver.Derivative(), 2.0, 1.0e-8) << "Derivative at x=3 should be 2";
}

TEST(MathBissecNewtonTest, CubicRootFinding)
{

  CubicWithDerivative aFunc;

  math_BissecNewton aSolver(1.0e-10);
  aSolver.Perform(aFunc, 1.0, 2.0, 100);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for cubic function";
  double aRoot = aSolver.Root();
  EXPECT_GT(aRoot, 1.52) << "Root should be greater than 1.52";
  EXPECT_LT(aRoot, 1.53) << "Root should be less than 1.53";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-8) << "Function value at root should be near zero";
}

TEST(MathBissecNewtonTest, SineFunctionRoot)
{

  SineWithDerivative aFunc;

  math_BissecNewton aSolver(1.0e-10);
  aSolver.Perform(aFunc, 3.0, 3.5, 100);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for sine function";
  EXPECT_NEAR(aSolver.Root(), M_PI, 1.0e-8) << "Root should be PI";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be zero";
  EXPECT_NEAR(aSolver.Derivative(), -1.0, 1.0e-8) << "cos(PI) should be -1";
}

TEST(MathBissecNewtonTest, CustomTolerance)
{

  QuadraticWithDerivative aFunc;

  math_BissecNewton aSolver1(1.0e-3);
  aSolver1.Perform(aFunc, 0.5, 1.5, 100);

  EXPECT_TRUE(aSolver1.IsDone()) << "Should converge with loose tolerance";
  EXPECT_NEAR(aSolver1.Root(), 1.0, 1.0e-2) << "Root should be approximately correct";

  math_BissecNewton aSolver2(1.0e-12);
  aSolver2.Perform(aFunc, 0.5, 1.5, 100);

  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with tight tolerance";
  EXPECT_NEAR(aSolver2.Root(), 1.0, 1.0e-10) << "Root should be very accurate";
}

TEST(MathBissecNewtonTest, IterationLimit)
{

  CubicWithDerivative aFunc;

  math_BissecNewton aSolver(1.0e-12);
  aSolver.Perform(aFunc, 1.0, 2.0, 5);

  if (aSolver.IsDone())
  {
    EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-3) << "If converged, should be reasonably accurate";
  }
}

TEST(MathBissecNewtonTest, InvalidBounds)
{

  QuadraticWithDerivative aFunc;

  math_BissecNewton aSolver(1.0e-10);
  aSolver.Perform(aFunc, 1.5, 2.5, 100);

  if (aSolver.IsDone())
  {
    double aRoot = aSolver.Root();
    EXPECT_GT(aRoot, 1.4) << "If found, root should be reasonable";
    EXPECT_LT(aRoot, 3.1) << "If found, root should be reasonable";
  }
}

TEST(MathBissecNewtonTest, ZeroDerivativeHandling)
{

  CubicZeroDerivative aFunc;

  math_BissecNewton aSolver(1.0e-10);
  aSolver.Perform(aFunc, -0.5, 0.5, 100);

  EXPECT_TRUE(aSolver.IsDone()) << "Should handle zero derivative case";
  EXPECT_NEAR(aSolver.Root(), 0.0, 1.0e-8) << "Root should be x = 0";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be zero";
  EXPECT_NEAR(aSolver.Derivative(), 0.0, 1.0e-8) << "Derivative at x=0 should be zero";
}

TEST(MathBissecNewtonTest, NotDoneState)
{

  math_BissecNewton aSolver(1.0e-10);

  EXPECT_FALSE(aSolver.IsDone()) << "Solver should not be done before Perform()";
}

TEST(MathBissecNewtonTest, MultipleCalls)
{

  QuadraticWithDerivative aFunc;
  math_BissecNewton       aSolver(1.0e-10);

  aSolver.Perform(aFunc, 0.0, 1.5, 100);
  EXPECT_TRUE(aSolver.IsDone()) << "First call should succeed";
  EXPECT_NEAR(aSolver.Root(), 1.0, 1.0e-8) << "First root should be x = 1";

  aSolver.Perform(aFunc, 2.5, 4.0, 100);
  EXPECT_TRUE(aSolver.IsDone()) << "Second call should succeed";
  EXPECT_NEAR(aSolver.Root(), 3.0, 1.0e-8) << "Second root should be x = 3";
}

TEST(MathBissecNewtonTest, HighPrecisionRequirement)
{

  SineWithDerivative aFunc;
  math_BissecNewton  aSolver(1.0e-15);

  aSolver.Perform(aFunc, 3.0, 3.5, 200);

  EXPECT_TRUE(aSolver.IsDone()) << "Should converge with high precision requirement";
  EXPECT_NEAR(aSolver.Root(), M_PI, 1.0e-12) << "Root should be very accurate";
}

TEST(MathBissecNewtonTest, EdgeCaseBounds)
{

  QuadraticWithDerivative aFunc;
  math_BissecNewton       aSolver(1.0e-10);

  aSolver.Perform(aFunc, 0.99, 1.01, 100);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root with narrow bounds";
  EXPECT_NEAR(aSolver.Root(), 1.0, 1.0e-8) << "Root should be accurate";
}
