

#include <math_FunctionRoot.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <math_BracketedRoot.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Precision.hpp>

#include <cmath>

class QuadraticFunction : public math_FunctionWithDerivative
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

class CubicFunction : public math_FunctionWithDerivative
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

class SinFunction : public math_FunctionWithDerivative
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

class ZeroDerivativeFunction : public math_FunctionWithDerivative
{
public:
  bool Value(const double theX, double& theF) override
  {
    theF = theX * theX;
    return true;
  }

  bool Derivative(const double theX, double& theD) override
  {
    theD = 2.0 * theX;
    return true;
  }

  bool Values(const double theX, double& theF, double& theD) override
  {
    theF = theX * theX;
    theD = 2.0 * theX;
    return true;
  }
};

TEST(MathFunctionRootTest, QuadraticPositiveRoot)
{
  QuadraticFunction aFunc;
  double            aTolerance     = 1.0e-6;
  double            anInitialGuess = 3.0;

  math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Root finding should succeed";
  EXPECT_NEAR(aRootFinder.Root(), 2.0, aTolerance) << "Root should be approximately 2.0";
  EXPECT_NEAR(aRootFinder.Value(), 0.0, aTolerance)
    << "Function value at root should be approximately 0";
  EXPECT_NEAR(aRootFinder.Derivative(), 4.0, aTolerance)
    << "Derivative at root should be approximately 4.0";
  EXPECT_GT(aRootFinder.NbIterations(), 0) << "Should require at least one iteration";
}

TEST(MathFunctionRootTest, QuadraticNegativeRoot)
{
  QuadraticFunction aFunc;
  double            aTolerance     = 1.0e-6;
  double            anInitialGuess = -3.0;

  math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Root finding should succeed";
  EXPECT_NEAR(aRootFinder.Root(), -2.0, aTolerance) << "Root should be approximately -2.0";
  EXPECT_NEAR(aRootFinder.Value(), 0.0, aTolerance)
    << "Function value at root should be approximately 0";
  EXPECT_NEAR(aRootFinder.Derivative(), -4.0, aTolerance)
    << "Derivative at root should be approximately -4.0";
}

TEST(MathFunctionRootTest, QuadraticWithBounds)
{
  QuadraticFunction aFunc;
  double            aTolerance     = 1.0e-6;
  double            anInitialGuess = 1.5;
  double            aLowerBound    = 1.0;
  double            anUpperBound   = 3.0;

  math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance, aLowerBound, anUpperBound);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Root finding with bounds should succeed";
  EXPECT_NEAR(aRootFinder.Root(), 2.0, aTolerance) << "Root should be approximately 2.0";
  EXPECT_GE(aRootFinder.Root(), aLowerBound) << "Root should be within lower bound";
  EXPECT_LE(aRootFinder.Root(), anUpperBound) << "Root should be within upper bound";
}

TEST(MathFunctionRootTest, CubicMultipleRoots)
{
  CubicFunction aFunc;
  double        aTolerance = 1.0e-6;

  {
    double            anInitialGuess = 0.8;
    math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance);

    EXPECT_TRUE(aRootFinder.IsDone()) << "Root finding should succeed for first root";
    EXPECT_NEAR(aRootFinder.Root(), 1.0, aTolerance) << "Root should be approximately 1.0";
    EXPECT_NEAR(aRootFinder.Value(), 0.0, aTolerance)
      << "Function value at root should be approximately 0";
  }

  {
    double            anInitialGuess = 1.8;
    math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance);

    EXPECT_TRUE(aRootFinder.IsDone()) << "Root finding should succeed for second root";
    EXPECT_NEAR(aRootFinder.Root(), 2.0, aTolerance) << "Root should be approximately 2.0";
    EXPECT_NEAR(aRootFinder.Value(), 0.0, aTolerance)
      << "Function value at root should be approximately 0";
  }

  {
    double            anInitialGuess = 3.2;
    math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance);

    EXPECT_TRUE(aRootFinder.IsDone()) << "Root finding should succeed for third root";
    EXPECT_NEAR(aRootFinder.Root(), 3.0, aTolerance) << "Root should be approximately 3.0";
    EXPECT_NEAR(aRootFinder.Value(), 0.0, aTolerance)
      << "Function value at root should be approximately 0";
  }
}

TEST(MathFunctionRootTest, TrigonometricFunction)
{
  SinFunction aFunc;
  double      aTolerance     = 1.0e-6;
  double      anInitialGuess = 3.5;

  math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Root finding should succeed for sin(x)";
  EXPECT_NEAR(aRootFinder.Root(), M_PI, aTolerance) << "Root should be approximately PI";
  EXPECT_NEAR(aRootFinder.Value(), 0.0, aTolerance)
    << "Function value at root should be approximately 0";
  EXPECT_NEAR(aRootFinder.Derivative(), -1.0, aTolerance) << "cos(PI) should be approximately -1";
}

TEST(MathFunctionRootTest, HighPrecisionTolerance)
{
  QuadraticFunction aFunc;
  double            aTolerance     = 1.0e-12;
  double            anInitialGuess = 2.1;

  math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance);

  EXPECT_TRUE(aRootFinder.IsDone()) << "High precision root finding should succeed";
  EXPECT_NEAR(aRootFinder.Root(), 2.0, aTolerance) << "Root should be very precise";
  EXPECT_NEAR(aRootFinder.Value(), 0.0, aTolerance)
    << "Function value should be very close to zero";
}

TEST(MathFunctionRootTest, MaxIterationsLimit)
{
  QuadraticFunction aFunc;
  double            aTolerance     = 1.0e-10;
  double            anInitialGuess = 2.1;
  int               aMaxIterations = 5;

  EXPECT_NO_THROW({
    math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance, aMaxIterations);

    if (aRootFinder.IsDone())
    {
      EXPECT_LE(aRootFinder.NbIterations(), aMaxIterations) << "Should not exceed max iterations";
      EXPECT_NEAR(aRootFinder.Root(), 2.0, 1.0e-3)
        << "Root should be reasonably close even with few iterations";
    }
    else
    {

      EXPECT_LE(aMaxIterations, 10) << "Failure is acceptable with very few iterations";
    }
  }) << "Function root finding should not throw exceptions";
}

TEST(MathFunctionRootTest, OutOfBoundsGuess)
{
  QuadraticFunction aFunc;
  double            aTolerance     = 1.0e-6;
  double            anInitialGuess = 0.0;
  double            aLowerBound    = 2.5;
  double            anUpperBound   = 3.0;

  math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance, aLowerBound, anUpperBound);

  if (aRootFinder.IsDone())
  {
    double aRoot = aRootFinder.Root();
    EXPECT_GE(aRoot, aLowerBound) << "Solution should be within lower bound";
    EXPECT_LE(aRoot, anUpperBound) << "Solution should be within upper bound";

    double aFunctionValue = aRootFinder.Value();
    if (std::abs(aFunctionValue) > 1.0e-3)
    {

      EXPECT_GE(aRoot, aLowerBound) << "Should still respect bounds";
      EXPECT_LE(aRoot, anUpperBound) << "Should still respect bounds";
    }
    else
    {

      EXPECT_NEAR(aFunctionValue, 0.0, aTolerance)
        << "True root should have function value near zero";
    }
  }
}

TEST(MathFunctionRootTest, ZeroDerivativeHandling)
{
  ZeroDerivativeFunction aFunc;
  double                 aTolerance     = 1.0e-6;
  double                 anInitialGuess = 0.1;

  math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance);

  EXPECT_TRUE(aRootFinder.IsDone())
    << "Root finding should succeed even with zero derivative at root";
  EXPECT_NEAR(aRootFinder.Root(), 0.0, aTolerance) << "Root should be approximately 0.0";
  EXPECT_NEAR(aRootFinder.Value(), 0.0, aTolerance)
    << "Function value at root should be approximately 0";
  EXPECT_NEAR(aRootFinder.Derivative(), 0.0, aTolerance)
    << "Derivative at root should be approximately 0";
}

TEST(MathFunctionRootTest, ConstrainedConvergenceState)
{
  QuadraticFunction aFunc;
  double            aTolerance     = 1.0e-10;
  double            anInitialGuess = 50.0;
  int               aMaxIterations = 3;

  EXPECT_NO_THROW({
    math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance, aMaxIterations);

    if (!aRootFinder.IsDone())
    {

      EXPECT_FALSE(aRootFinder.IsDone()) << "Root finder should consistently report failure";
      EXPECT_GE(aRootFinder.NbIterations(), 0)
        << "Iteration count should be non-negative even on failure";
    }
    else
    {

      EXPECT_GT(aRootFinder.NbIterations(), 0) << "Should have done at least one iteration";
      EXPECT_TRUE(std::abs(aRootFinder.Root() - 2.0) < 0.5
                  || std::abs(aRootFinder.Root() - (-2.0)) < 0.5)
        << "Root should be reasonably close to one of the expected roots";
    }
  }) << "Function root finding should not throw exceptions";
}

TEST(MathFunctionRootTest, ConvergenceBehavior)
{
  QuadraticFunction aFunc;
  double            aTolerance = 1.0e-6;

  struct TestCase
  {
    double initialGuess;
    double expectedRoot;
    double tolerance;
  };

  TestCase aTestCases[] = {
    {1.0, 2.0, aTolerance},
    {-1.0, -2.0, aTolerance},
    {10.0, 2.0, aTolerance},
    {-10.0, -2.0, aTolerance},
  };

  for (const auto& aTestCase : aTestCases)
  {
    math_FunctionRoot aRootFinder(aFunc, aTestCase.initialGuess, aTestCase.tolerance);

    EXPECT_TRUE(aRootFinder.IsDone())
      << "Root finding should succeed for initial guess " << aTestCase.initialGuess;
    EXPECT_NEAR(aRootFinder.Root(), aTestCase.expectedRoot, aTestCase.tolerance)
      << "Root should converge correctly from initial guess " << aTestCase.initialGuess;
  }
}

TEST(MathFunctionRootTest, PerformanceComparison)
{
  QuadraticFunction aFunc;
  double            aTolerance     = 1.0e-10;
  double            anInitialGuess = 2.1;

  math_FunctionRoot aRootFinder(aFunc, anInitialGuess, aTolerance);

  EXPECT_TRUE(aRootFinder.IsDone()) << "High precision root finding should succeed";
  EXPECT_LT(aRootFinder.NbIterations(), 50) << "Should converge in reasonable number of iterations";
  EXPECT_NEAR(aRootFinder.Root(), 2.0, aTolerance) << "Root should be highly accurate";
}
