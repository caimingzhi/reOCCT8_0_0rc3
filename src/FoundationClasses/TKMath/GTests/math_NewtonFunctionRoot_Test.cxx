

#include <math_NewtonFunctionRoot.hpp>
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
      theF = theX * theX - 4.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 2.0 * theX;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = theX * theX - 4.0;
      theD = 2.0 * theX;
      return true;
    }
  };

  class CubicWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX * theX - 6.0 * theX * theX + 11.0 * theX - 6.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 3.0 * theX * theX - 12.0 * theX + 11.0;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = theX * theX * theX - 6.0 * theX * theX + 11.0 * theX - 6.0;
      theD = 3.0 * theX * theX - 12.0 * theX + 11.0;
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

  class ExponentialWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = exp(theX) - 2.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = exp(theX);
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = exp(theX) - 2.0;
      theD = exp(theX);
      return true;
    }
  };

  class CubicWithZeroDerivative : public math_FunctionWithDerivative
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

  class LinearWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = 2.0 * theX - 4.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      (void)theX;
      theD = 2.0;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = 2.0 * theX - 4.0;
      theD = 2.0;
      return true;
    }
  };

} // namespace

TEST(MathNewtonFunctionRootTest, QuadraticRootFinding)
{

  QuadraticWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 3.0, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for quadratic function";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-8) << "Root should be x = 2";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be near 0";
  EXPECT_NEAR(aSolver.Derivative(), 4.0, 1.0e-8) << "Derivative at root should be 4";
  EXPECT_GT(aSolver.NbIterations(), 0) << "Should have performed some iterations";
}

TEST(MathNewtonFunctionRootTest, QuadraticNegativeRoot)
{

  QuadraticWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, -3.0, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find negative root for quadratic function";
  EXPECT_NEAR(aSolver.Root(), -2.0, 1.0e-8) << "Root should be x = -2";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be near 0";
  EXPECT_NEAR(aSolver.Derivative(), -4.0, 1.0e-8) << "Derivative at root should be -4";
}

TEST(MathNewtonFunctionRootTest, CubicRootFinding)
{

  CubicWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 1.1, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for cubic function";

  double aRoot = aSolver.Root();
  bool   aFoundValidRoot =
    (fabs(aRoot - 1.0) < 1.0e-6) || (fabs(aRoot - 2.0) < 1.0e-6) || (fabs(aRoot - 3.0) < 1.0e-6);
  EXPECT_TRUE(aFoundValidRoot) << "Root should be one of: 1, 2, or 3, found: " << aRoot;
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be near 0";
}

TEST(MathNewtonFunctionRootTest, SineRootFinding)
{

  SineWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 3.0, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for sine function";
  EXPECT_NEAR(aSolver.Root(), M_PI, 1.0e-8) << "Root should be PI";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be near 0";
  EXPECT_NEAR(aSolver.Derivative(), -1.0, 1.0e-8) << "Derivative at root should be -1";
}

TEST(MathNewtonFunctionRootTest, ExponentialRootFinding)
{

  ExponentialWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 1.0, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for exponential function";
  EXPECT_NEAR(aSolver.Root(), log(2.0), 1.0e-8) << "Root should be ln(2)";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be near 0";
  EXPECT_NEAR(aSolver.Derivative(), 2.0, 1.0e-8) << "Derivative at root should be 2";
}

TEST(MathNewtonFunctionRootTest, LinearRootFinding)
{

  LinearWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 1.0, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root for linear function";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-10) << "Root should be x = 2";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value at root should be near 0";
  EXPECT_NEAR(aSolver.Derivative(), 2.0, 1.0e-10) << "Derivative should be 2";
  EXPECT_GT(aSolver.NbIterations(), 0) << "Should have performed some iterations";
  EXPECT_LE(aSolver.NbIterations(), 5) << "Linear function should converge quickly";
}

TEST(MathNewtonFunctionRootTest, BoundedInterval)
{

  QuadraticWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 1.5, 1.0e-10, 1.0e-10, 0.0, 3.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find root within bounds";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-8) << "Root should be x = 2";
  EXPECT_GE(aSolver.Root(), 0.0) << "Root should be within lower bound";
  EXPECT_LE(aSolver.Root(), 3.0) << "Root should be within upper bound";
}

TEST(MathNewtonFunctionRootTest, CustomTolerances)
{

  QuadraticWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver1(aFunc, 3.0, 1.0e-3, 1.0e-3);
  EXPECT_TRUE(aSolver1.IsDone()) << "Should converge with loose tolerance";
  EXPECT_NEAR(aSolver1.Root(), 2.0, 1.0e-2) << "Root should be approximately correct";

  math_NewtonFunctionRoot aSolver2(aFunc, 3.0, 1.0e-12, 1.0e-12);
  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with tight tolerance";
  EXPECT_NEAR(aSolver2.Root(), 2.0, 1.0e-10) << "Root should be very accurate";
}

TEST(MathNewtonFunctionRootTest, CustomIterationLimit)
{

  CubicWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver1(aFunc, 1.5, 1.0e-10, 1.0e-10, 5);
  if (aSolver1.IsDone())
  {
    EXPECT_LE(aSolver1.NbIterations(), 5) << "Should respect iteration limit";
  }

  math_NewtonFunctionRoot aSolver2(aFunc, 1.5, 1.0e-10, 1.0e-10, 100);
  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with many iterations allowed";
}

TEST(MathNewtonFunctionRootTest, ProtectedConstructorAndPerform)
{

  QuadraticWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(0.0, 5.0, 1.0e-10, 1.0e-10);
  aSolver.Perform(aFunc, 3.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should work with protected constructor";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-8) << "Should find correct root";
}

TEST(MathNewtonFunctionRootTest, UnperformedState)
{

  QuadraticWithDerivative aFunc;
  math_NewtonFunctionRoot aSolver(0.0, 5.0, 1.0e-10, 1.0e-10);

  EXPECT_FALSE(aSolver.IsDone()) << "Solver should not be done before Perform()";

  if (!aSolver.IsDone())
  {
    EXPECT_FALSE(aSolver.IsDone()) << "State should be consistent when not done";
  }
}

TEST(MathNewtonFunctionRootTest, StartingAtRoot)
{

  LinearWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 2.0, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should succeed when starting at root";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-10) << "Should find exact root";
  EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-10) << "Function value should be exactly 0";
}

TEST(MathNewtonFunctionRootTest, ZeroDerivativeAtRoot)
{

  CubicWithZeroDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 0.1, 1.0e-8, 1.0e-8);

  if (aSolver.IsDone())
  {
    EXPECT_NEAR(aSolver.Root(), 0.0, 1.0e-6) << "Should find root despite zero derivative";
    EXPECT_NEAR(aSolver.Value(), 0.0, 1.0e-8) << "Function value should be near 0";
    EXPECT_NEAR(aSolver.Derivative(), 0.0, 1.0e-6) << "Derivative should be near 0";
  }
}

TEST(MathNewtonFunctionRootTest, NarrowBounds)
{

  QuadraticWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 2.0, 1.0e-10, 1.0e-10, 1.99, 2.01);

  EXPECT_TRUE(aSolver.IsDone()) << "Should work with narrow bounds";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-8) << "Should find root within narrow bounds";
  EXPECT_GE(aSolver.Root(), 1.99) << "Root should be within lower bound";
  EXPECT_LE(aSolver.Root(), 2.01) << "Root should be within upper bound";
}

TEST(MathNewtonFunctionRootTest, MultipleCubicRoots)
{

  CubicWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver1(aFunc, 0.5, 1.0e-10, 1.0e-10);
  EXPECT_TRUE(aSolver1.IsDone()) << "Should find first root";
  double aRoot1 = aSolver1.Root();
  EXPECT_TRUE(fabs(aRoot1 - 1.0) < 1.0e-6 || fabs(aRoot1 - 2.0) < 1.0e-6
              || fabs(aRoot1 - 3.0) < 1.0e-6)
    << "First root should be one of: 1, 2, or 3, found: " << aRoot1;

  math_NewtonFunctionRoot aSolver2(aFunc, 2.8, 1.0e-10, 1.0e-10);
  EXPECT_TRUE(aSolver2.IsDone()) << "Should find second root";
  double aRoot2 = aSolver2.Root();
  EXPECT_TRUE(fabs(aRoot2 - 1.0) < 1.0e-6 || fabs(aRoot2 - 2.0) < 1.0e-6
              || fabs(aRoot2 - 3.0) < 1.0e-6)
    << "Second root should be one of: 1, 2, or 3, found: " << aRoot2;

  math_NewtonFunctionRoot aSolver3(aFunc, 1.8, 1.0e-10, 1.0e-10);
  EXPECT_TRUE(aSolver3.IsDone()) << "Should find third root";
  double aRoot3 = aSolver3.Root();
  EXPECT_TRUE(fabs(aRoot3 - 1.0) < 1.0e-6 || fabs(aRoot3 - 2.0) < 1.0e-6
              || fabs(aRoot3 - 3.0) < 1.0e-6)
    << "Third root should be one of: 1, 2, or 3, found: " << aRoot3;
}

TEST(MathNewtonFunctionRootTest, ConvergenceFromFarGuess)
{

  QuadraticWithDerivative aFunc;

  math_NewtonFunctionRoot aSolver(aFunc, 100.0, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aSolver.IsDone()) << "Should converge from far initial guess";
  EXPECT_NEAR(aSolver.Root(), 2.0, 1.0e-8) << "Should still find correct root";
  EXPECT_GT(aSolver.NbIterations(), 5) << "Should require several iterations from far guess";
}
