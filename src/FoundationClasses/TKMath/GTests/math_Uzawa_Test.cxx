

#include <gtest/gtest.h>
#include <math_Uzawa.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_ConstructionError.hpp>

namespace
{
  const double TOLERANCE = 1.0e-6;
}

TEST(math_Uzawa, SimpleEqualityConstraints)
{

  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 2.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = 2.0;

  math_Vector b(1, 2);
  b(1) = 5.0;
  b(2) = 4.0;

  math_Vector x0(1, 2);
  x0(1) = 0.0;
  x0(2) = 0.0;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& solution = solver.Value();
  EXPECT_NEAR(solution(1), 2.0, TOLERANCE);
  EXPECT_NEAR(solution(2), 1.0, TOLERANCE);
}

TEST(math_Uzawa, OverdeterminedSystem)
{

  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = -1.0;

  math_Vector b(1, 2);
  b(1) = 3.0;
  b(2) = 1.0;

  math_Vector x0(1, 2);
  x0(1) = 0.0;
  x0(2) = 0.0;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& solution = solver.Value();
  EXPECT_NEAR(solution(1), 2.0, TOLERANCE);
  EXPECT_NEAR(solution(2), 1.0, TOLERANCE);
}

TEST(math_Uzawa, WithInequalityConstraints)
{

  math_Matrix C(1, 1, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;

  math_Vector b(1, 1);
  b(1) = 2.0;

  math_Vector x0(1, 2);
  x0(1) = 1.0;
  x0(2) = 1.0;

  math_Uzawa solver(C, b, x0, 0, 1);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& solution = solver.Value();
  EXPECT_NEAR(solution(1) + solution(2), 2.0, TOLERANCE);
}

TEST(math_Uzawa, CustomTolerances)
{

  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = -1.0;

  math_Vector b(1, 2);
  b(1) = 2.0;
  b(2) = 0.0;

  math_Vector x0(1, 2);
  x0(1) = 0.0;
  x0(2) = 0.0;

  math_Uzawa solver(C, b, x0, 1.0e-8, 1.0e-8);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& solution = solver.Value();
  EXPECT_NEAR(solution(1), 1.0, 1.0e-6);
  EXPECT_NEAR(solution(2), 1.0, 1.0e-6);
}

TEST(math_Uzawa, CustomIterations)
{

  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = -1.0;

  math_Vector b(1, 2);
  b(1) = 2.0;
  b(2) = 0.0;

  math_Vector x0(1, 2);
  x0(1) = 10.0;
  x0(2) = 10.0;

  math_Uzawa solver(C, b, x0, 1.0e-6, 1.0e-6, 50);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_LE(solver.NbIterations(), 50);
}

TEST(math_Uzawa, InitialError)
{
  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = -1.0;

  math_Vector b(1, 2);
  b(1) = 2.0;
  b(2) = 0.0;

  math_Vector x0(1, 2);
  x0(1) = 5.0;
  x0(2) = 3.0;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& initialError = solver.InitialError();

  EXPECT_NEAR(initialError(1), 6.0, TOLERANCE);
  EXPECT_NEAR(initialError(2), 2.0, TOLERANCE);
}

TEST(math_Uzawa, ErrorVector)
{
  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = -1.0;

  math_Vector b(1, 2);
  b(1) = 2.0;
  b(2) = 0.0;

  math_Vector x0(1, 2);
  x0(1) = 0.0;
  x0(2) = 0.0;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& error    = solver.Error();
  const math_Vector& solution = solver.Value();

  EXPECT_NEAR(error(1), solution(1) - x0(1), TOLERANCE);
  EXPECT_NEAR(error(2), solution(2) - x0(2), TOLERANCE);
}

TEST(math_Uzawa, DualVariables)
{
  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = -1.0;

  math_Vector b(1, 2);
  b(1) = 2.0;
  b(2) = 0.0;

  math_Vector x0(1, 2);
  x0(1) = 0.0;
  x0(2) = 0.0;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());

  math_Vector dualVar(1, 2);
  solver.Duale(dualVar);

  EXPECT_TRUE(std::isfinite(dualVar(1)));
  EXPECT_TRUE(std::isfinite(dualVar(2)));
}

TEST(math_Uzawa, InverseMatrix)
{
  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = -1.0;

  math_Vector b(1, 2);
  b(1) = 2.0;
  b(2) = 0.0;

  math_Vector x0(1, 2);
  x0(1) = 0.0;
  x0(2) = 0.0;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());

  const math_Matrix& invMatrix = solver.InverseCont();

  EXPECT_EQ(invMatrix.RowNumber(), 2);
  EXPECT_EQ(invMatrix.ColNumber(), 2);

  for (int i = 1; i <= 2; i++)
  {
    for (int j = 1; j <= 2; j++)
    {
      EXPECT_TRUE(std::isfinite(invMatrix(i, j)));
    }
  }
}

TEST(math_Uzawa, LargeSystem)
{

  int         n = 4;
  math_Matrix C(1, n, 1, n);
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      C(i, j) = (i == j) ? 2.0 : 0.5;
    }
  }

  math_Vector b(1, n);
  for (int i = 1; i <= n; i++)
  {
    b(i) = i;
  }

  math_Vector x0(1, n);
  for (int i = 1; i <= n; i++)
  {
    x0(i) = 0.0;
  }

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& solution = solver.Value();
  for (int i = 1; i <= n; i++)
  {
    EXPECT_TRUE(std::isfinite(solution(i)));
  }
}

TEST(math_Uzawa, StartingPointNearSolution)
{

  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = -1.0;

  math_Vector b(1, 2);
  b(1) = 2.0;
  b(2) = 0.0;

  math_Vector x0(1, 2);
  x0(1) = 1.001;
  x0(2) = 0.999;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_LE(solver.NbIterations(), 10);

  const math_Vector& solution = solver.Value();
  EXPECT_NEAR(solution(1), 1.0, TOLERANCE);
  EXPECT_NEAR(solution(2), 1.0, TOLERANCE);
}

TEST(math_Uzawa, ConsistentSystem)
{

  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 2.0;
  C(2, 1) = 2.0;
  C(2, 2) = 1.0;

  math_Vector b(1, 2);
  b(1) = 5.0;
  b(2) = 7.0;

  math_Vector x0(1, 2);
  x0(1) = 0.0;
  x0(2) = 0.0;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& solution = solver.Value();
  double             eq1      = solution(1) + 2.0 * solution(2);
  double             eq2      = 2.0 * solution(1) + solution(2);
  EXPECT_NEAR(eq1, 5.0, TOLERANCE);
  EXPECT_NEAR(eq2, 7.0, TOLERANCE);
}

TEST(math_Uzawa, SingleVariable)
{

  math_Matrix C(1, 1, 1, 1);
  C(1, 1) = 2.0;

  math_Vector b(1, 1);
  b(1) = 4.0;

  math_Vector x0(1, 1);
  x0(1) = 0.0;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());

  const math_Vector& solution = solver.Value();
  EXPECT_NEAR(solution(1), 2.0, TOLERANCE);
}

TEST(math_Uzawa, IterationCount)
{
  math_Matrix C(1, 2, 1, 2);
  C(1, 1) = 1.0;
  C(1, 2) = 1.0;
  C(2, 1) = 1.0;
  C(2, 2) = -1.0;

  math_Vector b(1, 2);
  b(1) = 2.0;
  b(2) = 0.0;

  math_Vector x0(1, 2);
  x0(1) = 0.0;
  x0(2) = 0.0;

  math_Uzawa solver(C, b, x0);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_GT(solver.NbIterations(), 0);
  EXPECT_LE(solver.NbIterations(), 500);
}
