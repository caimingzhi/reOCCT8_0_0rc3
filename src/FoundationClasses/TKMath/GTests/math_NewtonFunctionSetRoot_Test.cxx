

#include <gtest/gtest.h>
#include <math_NewtonFunctionSetRoot.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>

#ifndef M_SQRT1_2
  #define M_SQRT1_2 0.707106781186547524400844362104849039
#endif

namespace
{
  const double TOLERANCE = 1.0e-6;

  class CircleLineSystem : public math_FunctionSetWithDerivatives
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
      Value(X, F);
      Derivatives(X, D);
      return true;
    }
  };

  class LinearSystem : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 2; }

    int NbEquations() const override { return 2; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = 2.0 * X(1) + X(2) - 3.0;
      F(2) = X(1) + 2.0 * X(2) - 3.0;
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

  class QuadraticFunction : public math_FunctionSetWithDerivatives
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

  class ThreeVariableSystem : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 3; }

    int NbEquations() const override { return 3; }

    bool Value(const math_Vector& X, math_Vector& F) override
    {
      F(1) = X(1) + X(2) + X(3) - 6.0;
      F(2) = X(1) - X(2);
      F(3) = 2.0 * X(3) - 4.0;
      return true;
    }

    bool Derivatives(const math_Vector& X, math_Matrix& D) override
    {
      (void)X;
      D(1, 1) = 1.0;
      D(1, 2) = 1.0;
      D(1, 3) = 1.0;
      D(2, 1) = 1.0;
      D(2, 2) = -1.0;
      D(2, 3) = 0.0;
      D(3, 1) = 0.0;
      D(3, 2) = 0.0;
      D(3, 3) = 2.0;
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

TEST(math_NewtonFunctionSetRoot, LinearSystemBasic)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(root(1), 1.0, TOLERANCE);
  EXPECT_NEAR(root(2), 1.0, TOLERANCE);
}

TEST(math_NewtonFunctionSetRoot, QuadraticSingleVariable)
{
  QuadraticFunction func;

  math_Vector tolerance(1, 1);
  tolerance(1) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

  math_Vector startingPoint(1, 1);
  startingPoint(1) = 1.5;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(fabs(root(1)), 2.0, TOLERANCE);
}

TEST(math_NewtonFunctionSetRoot, CircleLineIntersection)
{
  CircleLineSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.7;
  startingPoint(2) = 0.7;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(fabs(root(1)), M_SQRT1_2, 1.0e-5);
  EXPECT_NEAR(fabs(root(2)), M_SQRT1_2, 1.0e-5);
  EXPECT_NEAR(root(1), root(2), TOLERANCE);
}

TEST(math_NewtonFunctionSetRoot, ThreeVariableSystem)
{
  ThreeVariableSystem func;

  math_Vector tolerance(1, 3);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;
  tolerance(3) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

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

TEST(math_NewtonFunctionSetRoot, WithBounds)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  math_Vector lowerBound(1, 2);
  lowerBound(1) = 0.0;
  lowerBound(2) = 0.0;

  math_Vector upperBound(1, 2);
  upperBound(1) = 2.0;
  upperBound(2) = 2.0;

  solver.Perform(func, startingPoint, lowerBound, upperBound);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(root(1), 1.0, TOLERANCE);
  EXPECT_NEAR(root(2), 1.0, TOLERANCE);
  EXPECT_GE(root(1), 0.0 - TOLERANCE);
  EXPECT_LE(root(1), 2.0 + TOLERANCE);
  EXPECT_GE(root(2), 0.0 - TOLERANCE);
  EXPECT_LE(root(2), 2.0 + TOLERANCE);
}

TEST(math_NewtonFunctionSetRoot, AlternativeConstructor)
{
  LinearSystem func;

  math_NewtonFunctionSetRoot solver(func, 1.0e-6);

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
  EXPECT_NEAR(root(1), 1.0, TOLERANCE);
  EXPECT_NEAR(root(2), 1.0, TOLERANCE);
}

TEST(math_NewtonFunctionSetRoot, CustomIterations)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6, 10);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_LE(solver.NbIterations(), 10);
}

TEST(math_NewtonFunctionSetRoot, ConvergenceIterations)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_GT(solver.NbIterations(), 0);
  EXPECT_LT(solver.NbIterations(), 20);
}

TEST(math_NewtonFunctionSetRoot, DerivativeMatrix)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

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

TEST(math_NewtonFunctionSetRoot, FunctionSetErrors)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& errors = solver.FunctionSetErrors();
  EXPECT_EQ(errors.Length(), 2);

  EXPECT_LT(fabs(errors(1)), 1.0e-5);
  EXPECT_LT(fabs(errors(2)), 1.0e-5);
}

TEST(math_NewtonFunctionSetRoot, OutputMethods)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  math_Vector rootCopy(1, 2);
  solver.Root(rootCopy);
  EXPECT_NEAR(rootCopy(1), 1.0, TOLERANCE);
  EXPECT_NEAR(rootCopy(2), 1.0, TOLERANCE);

  math_Matrix derivativeCopy(1, 2, 1, 2);
  solver.Derivative(derivativeCopy);
  EXPECT_NEAR(derivativeCopy(1, 1), 2.0, TOLERANCE);
  EXPECT_NEAR(derivativeCopy(2, 2), 2.0, TOLERANCE);

  math_Vector errorsCopy(1, 2);
  solver.FunctionSetErrors(errorsCopy);
  EXPECT_LT(fabs(errorsCopy(1)), 1.0e-5);
  EXPECT_LT(fabs(errorsCopy(2)), 1.0e-5);
}

TEST(math_NewtonFunctionSetRoot, IterationCount)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  int iterations = solver.NbIterations();
  EXPECT_GT(iterations, 0);
  EXPECT_LE(iterations, 100);
}

TEST(math_NewtonFunctionSetRoot, GoodStartingPoint)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-6;
  tolerance(2) = 1.0e-6;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-6);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.99;
  startingPoint(2) = 1.01;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_LE(solver.NbIterations(), 5);
}

TEST(math_NewtonFunctionSetRoot, TightTolerances)
{
  LinearSystem func;

  math_Vector tolerance(1, 2);
  tolerance(1) = 1.0e-10;
  tolerance(2) = 1.0e-10;

  math_NewtonFunctionSetRoot solver(func, tolerance, 1.0e-10);

  math_Vector startingPoint(1, 2);
  startingPoint(1) = 0.0;
  startingPoint(2) = 0.0;

  solver.Perform(func, startingPoint);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& root = solver.Root();
  EXPECT_NEAR(root(1), 1.0, 1.0e-8);
  EXPECT_NEAR(root(2), 1.0, 1.0e-8);
}
