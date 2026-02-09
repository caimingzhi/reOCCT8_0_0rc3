

#include <gtest/gtest.h>

#include <MathSys_Newton.hpp>
#include <math_NewtonFunctionSetRoot.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-8;

  class SimpleCircleLineSystem : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 2; }

    int NbEquations() const override { return 2; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = X(1) * X(1) + X(2) * X(2) - 1.0;
      F(2) = X(1) - X(2);
      return true;
    }

    bool Derivatives(const math_Vector& X, math_Matrix& D) override
    {
      D(1, 1) = 2.0 * X(1);
      D(1, 2) = 2.0 * X(2);
      D(2, 1) = 1.0;
      D(2, 2) = -1.0;
      return true;
    }

    bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override
    {
      return Value(X, F) && Derivatives(X, D);
    }
  };

  class RosenbrockSystem : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 2; }

    int NbEquations() const override { return 2; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = 10.0 * (X(2) - X(1) * X(1));
      F(2) = 1.0 - X(1);
      return true;
    }

    bool Derivatives(const math_Vector& X, math_Matrix& D) override
    {
      D(1, 1) = -20.0 * X(1);
      D(1, 2) = 10.0;
      D(2, 1) = -1.0;
      D(2, 2) = 0.0;
      return true;
    }

    bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override
    {
      return Value(X, F) && Derivatives(X, D);
    }
  };

  class Linear3System : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 3; }

    int NbEquations() const override { return 3; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = 2.0 * X(1) + X(2) - 2.0;
      F(2) = X(1) + 3.0 * X(2) - 5.0;
      F(3) = X(3) - 1.0;
      return true;
    }

    bool Derivatives(const math_Vector&, math_Matrix& D) override
    {
      D(1, 1) = 2.0;
      D(1, 2) = 1.0;
      D(1, 3) = 0.0;
      D(2, 1) = 1.0;
      D(2, 2) = 3.0;
      D(2, 3) = 0.0;
      D(3, 1) = 0.0;
      D(3, 2) = 0.0;
      D(3, 3) = 1.0;
      return true;
    }

    bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override
    {
      return Value(X, F) && Derivatives(X, D);
    }
  };

  class PolynomialSystem : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 2; }

    int NbEquations() const override { return 2; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = X(1) * X(1) * X(1) - X(2);
      F(2) = X(2) * X(2) * X(2) - X(1);
      return true;
    }

    bool Derivatives(const math_Vector& X, math_Matrix& D) override
    {
      D(1, 1) = 3.0 * X(1) * X(1);
      D(1, 2) = -1.0;
      D(2, 1) = -1.0;
      D(2, 2) = 3.0 * X(2) * X(2);
      return true;
    }

    bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override
    {
      return Value(X, F) && Derivatives(X, D);
    }
  };
} // namespace

TEST(MathSys_ComparisonTest, Newton_CircleLineSystem)
{
  SimpleCircleLineSystem aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.5;
  aStart(2) = 0.5;

  math_Vector aTolX(1, 2, 1.0e-10);
  double      aTolF = 1.0e-10;

  auto aNewResult = MathSys::Newton(aFunc, aStart, aTolX, aTolF);
  ASSERT_TRUE(aNewResult.IsDone());

  math_NewtonFunctionSetRoot aOldSolver(aFunc, aTolX, aTolF);
  aOldSolver.Perform(aFunc, aStart);
  ASSERT_TRUE(aOldSolver.IsDone());

  const math_Vector& aOldRoot = aOldSolver.Root();

  const double aExpected = std::sqrt(0.5);

  EXPECT_NEAR((*aNewResult.Solution)(1), aExpected, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), aExpected, THE_TOLERANCE);
  EXPECT_NEAR(aOldRoot(1), aExpected, THE_TOLERANCE);
  EXPECT_NEAR(aOldRoot(2), aExpected, THE_TOLERANCE);

  EXPECT_NEAR((*aNewResult.Solution)(1), aOldRoot(1), THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), aOldRoot(2), THE_TOLERANCE);
}

TEST(MathSys_ComparisonTest, Newton_RosenbrockSystem)
{
  RosenbrockSystem aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  math_Vector aTolX(1, 2, 1.0e-10);
  double      aTolF = 1.0e-10;

  auto aNewResult = MathSys::Newton(aFunc, aStart, aTolX, aTolF);
  ASSERT_TRUE(aNewResult.IsDone());

  math_NewtonFunctionSetRoot aOldSolver(aFunc, aTolX, aTolF);
  aOldSolver.Perform(aFunc, aStart);
  ASSERT_TRUE(aOldSolver.IsDone());

  const math_Vector& aOldRoot = aOldSolver.Root();

  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aOldRoot(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aOldRoot(2), 1.0, THE_TOLERANCE);

  EXPECT_NEAR((*aNewResult.Solution)(1), aOldRoot(1), THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), aOldRoot(2), THE_TOLERANCE);
}

TEST(MathSys_ComparisonTest, Newton_Linear3System)
{
  Linear3System aFunc;

  math_Vector aStart(1, 3);
  aStart(1) = 0.0;
  aStart(2) = 0.0;
  aStart(3) = 0.0;

  math_Vector aTolX(1, 3, 1.0e-10);
  double      aTolF = 1.0e-10;

  auto aNewResult = MathSys::Newton(aFunc, aStart, aTolX, aTolF);
  ASSERT_TRUE(aNewResult.IsDone());

  math_NewtonFunctionSetRoot aOldSolver(aFunc, aTolX, aTolF);
  aOldSolver.Perform(aFunc, aStart);
  ASSERT_TRUE(aOldSolver.IsDone());

  const math_Vector& aOldRoot = aOldSolver.Root();

  EXPECT_NEAR((*aNewResult.Solution)(1), 0.2, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), 1.6, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(3), 1.0, THE_TOLERANCE);

  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR((*aNewResult.Solution)(i), aOldRoot(i), THE_TOLERANCE);
  }
}

TEST(MathSys_ComparisonTest, Newton_PolynomialSystem)
{
  PolynomialSystem aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.9;
  aStart(2) = 0.9;

  math_Vector aTolX(1, 2, 1.0e-10);
  double      aTolF = 1.0e-10;

  auto aNewResult = MathSys::Newton(aFunc, aStart, aTolX, aTolF);
  ASSERT_TRUE(aNewResult.IsDone());

  math_NewtonFunctionSetRoot aOldSolver(aFunc, aTolX, aTolF);
  aOldSolver.Perform(aFunc, aStart);
  ASSERT_TRUE(aOldSolver.IsDone());

  const math_Vector& aOldRoot = aOldSolver.Root();

  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), 1.0, THE_TOLERANCE);

  EXPECT_NEAR((*aNewResult.Solution)(1), aOldRoot(1), THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), aOldRoot(2), THE_TOLERANCE);
}

TEST(MathSys_ComparisonTest, NewtonBounded_CircleLineSystem)
{
  SimpleCircleLineSystem aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.5;
  aStart(2) = 0.5;

  math_Vector aInfBound(1, 2);
  aInfBound(1) = 0.0;
  aInfBound(2) = 0.0;

  math_Vector aSupBound(1, 2);
  aSupBound(1) = 2.0;
  aSupBound(2) = 2.0;

  math_Vector aTolX(1, 2, 1.0e-10);
  double      aTolF = 1.0e-10;

  auto aNewResult = MathSys::NewtonBounded(aFunc, aStart, aInfBound, aSupBound, aTolX, aTolF);
  ASSERT_TRUE(aNewResult.IsDone());

  math_NewtonFunctionSetRoot aOldSolver(aFunc, aTolX, aTolF);
  aOldSolver.Perform(aFunc, aStart, aInfBound, aSupBound);
  ASSERT_TRUE(aOldSolver.IsDone());

  const math_Vector& aOldRoot = aOldSolver.Root();

  const double aExpected = std::sqrt(0.5);

  EXPECT_NEAR((*aNewResult.Solution)(1), aExpected, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), aExpected, THE_TOLERANCE);

  EXPECT_NEAR((*aNewResult.Solution)(1), aOldRoot(1), THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), aOldRoot(2), THE_TOLERANCE);
}

TEST(MathSys_ComparisonTest, Newton_VerifyFunctionValues)
{
  SimpleCircleLineSystem aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.5;
  aStart(2) = 0.5;

  auto aResult = MathSys::Newton(aFunc, aStart, 1.0e-10, 1.0e-10);
  ASSERT_TRUE(aResult.IsDone());

  math_Vector aF(1, 2);
  ASSERT_TRUE(aFunc.Value(*aResult.Solution, aF));

  EXPECT_NEAR(aF(1), 0.0, 1.0e-8);
  EXPECT_NEAR(aF(2), 0.0, 1.0e-8);
}

TEST(MathSys_ComparisonTest, IterationCount_NewVsOld)
{
  RosenbrockSystem aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  math_Vector aTolX(1, 2, 1.0e-10);
  double      aTolF = 1.0e-10;

  auto aNewResult = MathSys::Newton(aFunc, aStart, aTolX, aTolF);
  ASSERT_TRUE(aNewResult.IsDone());

  math_NewtonFunctionSetRoot aOldSolver(aFunc, aTolX, aTolF);
  aOldSolver.Perform(aFunc, aStart);
  ASSERT_TRUE(aOldSolver.IsDone());

  EXPECT_GT(aNewResult.NbIterations, 0u);
  EXPECT_LE(aNewResult.NbIterations, 20u);

  int aOldIter = aOldSolver.NbIterations();
  EXPECT_NEAR(static_cast<int>(aNewResult.NbIterations), aOldIter, 5);
}

TEST(MathSys_ComparisonTest, Newton_UniformTolerance)
{
  SimpleCircleLineSystem aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.5;
  aStart(2) = 0.5;

  auto aResult = MathSys::Newton(aFunc, aStart, 1.0e-10, 1.0e-10);
  ASSERT_TRUE(aResult.IsDone());

  const double aExpected = std::sqrt(0.5);
  EXPECT_NEAR((*aResult.Solution)(1), aExpected, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), aExpected, THE_TOLERANCE);
}

TEST(MathSys_ComparisonTest, Newton_DifferentStartingPoints)
{
  SimpleCircleLineSystem aFunc;

  math_Vector aTolX(1, 2, 1.0e-10);
  double      aTolF = 1.0e-10;

  double aStartPoints[][2] = {
    {0.1, 0.1},
    {0.9, 0.9},
    {0.3, 0.7},
    {1.0, 0.0},
  };

  for (const auto& aStartPt : aStartPoints)
  {
    math_Vector aStart(1, 2);
    aStart(1) = aStartPt[0];
    aStart(2) = aStartPt[1];

    auto aNewResult = MathSys::Newton(aFunc, aStart, aTolX, aTolF);
    ASSERT_TRUE(aNewResult.IsDone())
      << "Failed for start (" << aStartPt[0] << ", " << aStartPt[1] << ")";

    math_NewtonFunctionSetRoot aOldSolver(aFunc, aTolX, aTolF);
    aOldSolver.Perform(aFunc, aStart);
    ASSERT_TRUE(aOldSolver.IsDone());

    const math_Vector& aOldRoot = aOldSolver.Root();

    EXPECT_NEAR((*aNewResult.Solution)(1), aOldRoot(1), THE_TOLERANCE);
    EXPECT_NEAR((*aNewResult.Solution)(2), aOldRoot(2), THE_TOLERANCE);
  }
}
