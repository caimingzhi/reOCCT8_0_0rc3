

#include <gtest/gtest.h>
#include <math_FunctionSetRoot.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>

namespace
{
  const double TOLERANCE = 1.0e-6;

  class LinearSystem2D : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 2; }

    int NbEquations() const override { return 2; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = 2.0 * X(1) + X(2) - 5.0;
      F(2) = X(1) + 2.0 * X(2) - 4.0;
      return true;
    }

    bool Derivatives(const math_Vector&, math_Matrix& D) override
    {
      D(1, 1) = 2.0;
      D(1, 2) = 1.0;
      D(2, 1) = 1.0;
      D(2, 2) = 2.0;
      return true;
    }

    bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override
    {
      Value(X, F);
      Derivatives(X, D);
      return true;
    }
  };

  class NonlinearSystem : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 2; }

    int NbEquations() const override { return 2; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = X(1) * X(1) + X(2) * X(2) - 5.0;
      F(2) = X(1) * X(2) - 2.0;
      return true;
    }

    bool Derivatives(const math_Vector& X, math_Matrix& D) override
    {
      D(1, 1) = 2.0 * X(1);
      D(1, 2) = 2.0 * X(2);
      D(2, 1) = X(2);
      D(2, 2) = X(1);
      return true;
    }

    bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override
    {
      Value(X, F);
      Derivatives(X, D);
      return true;
    }
  };

  class SingleVariableSystem : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 1; }

    int NbEquations() const override { return 1; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = X(1) * X(1) - 4.0;
      return true;
    }

    bool Derivatives(const math_Vector& X, math_Matrix& D) override
    {
      D(1, 1) = 2.0 * X(1);
      return true;
    }

    bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override
    {
      Value(X, F);
      Derivatives(X, D);
      return true;
    }
  };

  class OverdeterminedSystem : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 2; }

    int NbEquations() const override { return 3; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = X(1) + X(2) - 3.0;
      F(2) = X(1) - X(2) - 1.0;
      F(3) = 2.0 * X(1) - 4.0;
      return true;
    }

    bool Derivatives(const math_Vector&, math_Matrix& D) override
    {
      D(1, 1) = 1.0;
      D(1, 2) = 1.0;
      D(2, 1) = 1.0;
      D(2, 2) = -1.0;
      D(3, 1) = 2.0;
      D(3, 2) = 0.0;
      return true;
    }

    bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override
    {
      Value(X, F);
      Derivatives(X, D);
      return true;
    }
  };

  class ThreeVariableSystem : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 3; }

    int NbEquations() const override { return 3; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = X(1) + X(2) + X(3) - 6.0;
      F(2) = 2.0 * X(1) - X(2) - 2.0;
      F(3) = X(3) - 2.0;
      return true;
    }

    bool Derivatives(const math_Vector&, math_Matrix& D) override
    {
      D(1, 1) = 1.0;
      D(1, 2) = 1.0;
      D(1, 3) = 1.0;
      D(2, 1) = 2.0;
      D(2, 2) = -1.0;
      D(2, 3) = 0.0;
      D(3, 1) = 0.0;
      D(3, 2) = 0.0;
      D(3, 3) = 1.0;
      return true;
    }

    bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override
    {
      Value(X, F);
      Derivatives(X, D);
      return true;
    }
  };
} // namespace

TEST(math_FunctionSetRoot, LinearSystemBasic)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(root(1), 2.0, TOLERANCE);
  EXPECT_NEAR(root(2), 1.0, TOLERANCE);
}

TEST(math_FunctionSetRoot, NonlinearSystem)
{
  NonlinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-5;
  tolerance(2) = 1.0e-5;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 1.5;
  startingPoint(2) = 1.5;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();

  double x = root(1);
  double y = root(2);

  EXPECT_TRUE(std::isfinite(x));
  EXPECT_TRUE(std::isfinite(y));
  EXPECT_GT(fabs(x), 0.1);
  EXPECT_GT(fabs(y), 0.1);
}

TEST(math_FunctionSetRoot, SingleVariable)
{
  SingleVariableSystem func;

  math_Vector tolerance(1, 1);
  tolerance(1) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 1);
  startingPoint(1) = 1.5;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(fabs(root(1)), 2.0, TOLERANCE);
}

TEST(math_FunctionSetRoot, OverdeterminedSystem)
{
  OverdeterminedSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-5;
  tolerance(2) = 1.0e-5;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();

  EXPECT_NEAR(root(1), 2.0, 1.0e-3);
  EXPECT_NEAR(root(2), 1.0, 1.0e-3);
}

TEST(math_FunctionSetRoot, ThreeVariableSystem)
{
  ThreeVariableSystem func;

  math_Vector tolerance(1, 3);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;
  tolerance(3) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 3);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;
  startingPoint(3) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(root(1), 2.0, TOLERANCE);
  EXPECT_NEAR(root(2), 2.0, TOLERANCE);
  EXPECT_NEAR(root(3), 2.0, TOLERANCE);
}

TEST(math_FunctionSetRoot, WithBounds)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  math_Vector lowerBound(1, 2);
  lowerBound(1) = 0.0;
  lowerBound(2) = 0.0;

  math_Vector upperBound(1, 2);
  upperBound(1) = 3.0;
  upperBound(2) = 3.0;

  solver.Perform(func, startingPoint, lowerBound, upperBound);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(root(1), 2.0, TOLERANCE);
  EXPECT_NEAR(root(2), 1.0, TOLERANCE);
  EXPECT_GE(root(1), 0.0 - TOLERANCE);
  EXPECT_LE(root(1), 3.0 + TOLERANCE);
  EXPECT_GE(root(2), 0.0 - TOLERANCE);
  EXPECT_LE(root(2), 3.0 + TOLERANCE);
}

TEST(math_FunctionSetRoot, AlternativeConstructor)
{
  LinearSystem2D func;

  math_FunctionSetRoot solver(func);

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  solver.SetTolerance(tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(root(1), 2.0, TOLERANCE);
  EXPECT_NEAR(root(2), 1.0, TOLERANCE);
}

TEST(math_FunctionSetRoot, CustomIterations)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance, 50);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_LE(solver.NbIterations(), 50);
}

TEST(math_FunctionSetRoot, StateNumber)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  int state = solver.StateNumber();
  EXPECT_GE(state, 0);
}

TEST(math_FunctionSetRoot, DerivativeMatrix)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Matrix& jacobian = solver.Derivative();
  EXPECT_EQ(jacobian.RowNumber(), 2);
  EXPECT_EQ(jacobian.ColNumber(), 2);

  EXPECT_NEAR(jacobian(1, 1), 2.0, TOLERANCE);
  EXPECT_NEAR(jacobian(1, 2), 1.0, TOLERANCE);
  EXPECT_NEAR(jacobian(2, 1), 1.0, TOLERANCE);
  EXPECT_NEAR(jacobian(2, 2), 2.0, TOLERANCE);
}

TEST(math_FunctionSetRoot, FunctionSetErrors)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& errors = solver.FunctionSetErrors();
  EXPECT_EQ(errors.Length(), 2);

  EXPECT_TRUE(std::isfinite(errors(1)));
  EXPECT_TRUE(std::isfinite(errors(2)));
}

TEST(math_FunctionSetRoot, OutputMethods)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  math_Vector rootCopy(1, 2);
  solver.Root(rootCopy);
  EXPECT_NEAR(rootCopy(1), 2.0, TOLERANCE);
  EXPECT_NEAR(rootCopy(2), 1.0, TOLERANCE);

  math_Matrix derivativeCopy(1, 2, 1, 2);
  solver.Derivative(derivativeCopy);
  EXPECT_NEAR(derivativeCopy(1, 1), 2.0, TOLERANCE);
  EXPECT_NEAR(derivativeCopy(2, 2), 2.0, TOLERANCE);

  math_Vector errorsCopy(1, 2);
  solver.FunctionSetErrors(errorsCopy);
  EXPECT_TRUE(std::isfinite(errorsCopy(1)));
  EXPECT_TRUE(std::isfinite(errorsCopy(2)));
}

TEST(math_FunctionSetRoot, IterationCount)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  int iterations = solver.NbIterations();
  EXPECT_GT(iterations, 0);
  EXPECT_LE(iterations, 100);
}

TEST(math_FunctionSetRoot, GoodStartingPoint)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 1.99;
  startingPoint(2) = 1.01;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_LE(solver.NbIterations(), 5);
}

TEST(math_FunctionSetRoot, StopOnDivergent)
{
  NonlinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 100.0;
  startingPoint(2) = 100.0;

  solver.Perform(func, startingPoint, true);

  if (!solver.IsDone())
  {
    EXPECT_TRUE(solver.IsDivergent());
  }
}

TEST(math_FunctionSetRoot, TightTolerances)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-10;
  tolerance(2) = 1.0e-10;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(root(1), 2.0, 1.0e-8);
  EXPECT_NEAR(root(2), 1.0, 1.0e-8);
}

TEST(math_FunctionSetRoot, BoundedSolution)
{
  LinearSystem2D func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_FunctionSetRoot solver(func, tolerance);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  math_Vector lowerBound(1, 2);
  lowerBound(1) = 0.5;
  lowerBound(2) = 0.5;

  math_Vector upperBound(1, 2);
  upperBound(1) = 3.0;
  upperBound(2) = 3.0;

  solver.Perform(func, startingPoint, lowerBound, upperBound);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();

  EXPECT_GE(root(1), 0.5 - TOLERANCE);
  EXPECT_LE(root(1), 3.0 + TOLERANCE);
  EXPECT_GE(root(2), 0.5 - TOLERANCE);
  EXPECT_LE(root(2), 3.0 + TOLERANCE);

  EXPECT_NEAR(root(1), 2.0, TOLERANCE);
  EXPECT_NEAR(root(2), 1.0, TOLERANCE);
}
