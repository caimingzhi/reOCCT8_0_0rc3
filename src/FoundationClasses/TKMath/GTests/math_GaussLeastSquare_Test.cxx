

#include <gtest/gtest.h>
#include <math_GaussLeastSquare.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>

namespace
{
  const double TOLERANCE = 1.0e-6;
}

TEST(math_GaussLeastSquare, SimpleLinearSystem)
{

  math_Matrix A(1, 2, 1, 2);
  A(1, 1) = 2.0;
  A(1, 2) = 1.0;
  A(2, 1) = 1.0;
  A(2, 2) = 2.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 2);
  B(1) = 5.0;
  B(2) = 4.0;

  math_Vector X(1, 2);
  solver.Solve(B, X);

  EXPECT_NEAR(X(1), 2.0, TOLERANCE);
  EXPECT_NEAR(X(2), 1.0, TOLERANCE);
}

TEST(math_GaussLeastSquare, OverdeterminedSystem)
{

  math_Matrix A(1, 3, 1, 2);
  A(1, 1) = 1.0;
  A(1, 2) = 1.0;
  A(2, 1) = 2.0;
  A(2, 2) = -1.0;
  A(3, 1) = 1.0;
  A(3, 2) = 2.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 3);
  B(1) = 3.0;
  B(2) = 1.0;
  B(3) = 5.0;

  math_Vector X(1, 2);
  solver.Solve(B, X);

  EXPECT_TRUE(std::isfinite(X(1)));
  EXPECT_TRUE(std::isfinite(X(2)));
  EXPECT_NEAR(X(1), 1.4, 0.2);
  EXPECT_NEAR(X(2), 1.8, 0.2);
}

TEST(math_GaussLeastSquare, SingleVariable)
{

  math_Matrix A(1, 1, 1, 1);
  A(1, 1) = 2.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 1);
  B(1) = 4.0;

  math_Vector X(1, 1);
  solver.Solve(B, X);

  EXPECT_NEAR(X(1), 2.0, TOLERANCE);
}

TEST(math_GaussLeastSquare, ThreeByThreeSystem)
{

  math_Matrix A(1, 3, 1, 3);
  A(1, 1) = 2.0;
  A(1, 2) = 1.0;
  A(1, 3) = 1.0;
  A(2, 1) = 1.0;
  A(2, 2) = 2.0;
  A(2, 3) = 1.0;
  A(3, 1) = 1.0;
  A(3, 2) = 1.0;
  A(3, 3) = 2.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 3);
  B(1) = 8.0;
  B(2) = 7.0;
  B(3) = 6.0;

  math_Vector X(1, 3);
  solver.Solve(B, X);

  EXPECT_NEAR(X(1), 2.75, 0.1);
  EXPECT_NEAR(X(2), 1.75, 0.1);
  EXPECT_NEAR(X(3), 0.75, 0.1);
}

TEST(math_GaussLeastSquare, IdentityMatrix)
{

  math_Matrix A(1, 3, 1, 3);
  A(1, 1) = 1.0;
  A(1, 2) = 0.0;
  A(1, 3) = 0.0;
  A(2, 1) = 0.0;
  A(2, 2) = 1.0;
  A(2, 3) = 0.0;
  A(3, 1) = 0.0;
  A(3, 2) = 0.0;
  A(3, 3) = 1.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 3);
  B(1) = 5.0;
  B(2) = 3.0;
  B(3) = 7.0;

  math_Vector X(1, 3);
  solver.Solve(B, X);

  EXPECT_NEAR(X(1), 5.0, TOLERANCE);
  EXPECT_NEAR(X(2), 3.0, TOLERANCE);
  EXPECT_NEAR(X(3), 7.0, TOLERANCE);
}

TEST(math_GaussLeastSquare, CustomMinPivot)
{

  math_Matrix A(1, 2, 1, 2);
  A(1, 1) = 1.0;
  A(1, 2) = 0.0;
  A(2, 1) = 0.0;
  A(2, 2) = 1.0;

  math_GaussLeastSquare solver(A, 1.0e-15);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 2);
  B(1) = 2.0;
  B(2) = 3.0;

  math_Vector X(1, 2);
  solver.Solve(B, X);

  EXPECT_NEAR(X(1), 2.0, TOLERANCE);
  EXPECT_NEAR(X(2), 3.0, TOLERANCE);
}

TEST(math_GaussLeastSquare, LargeDiagonalValues)
{

  math_Matrix A(1, 2, 1, 2);
  A(1, 1) = 100.0;
  A(1, 2) = 1.0;
  A(2, 1) = 1.0;
  A(2, 2) = 100.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 2);
  B(1) = 101.0;
  B(2) = 102.0;

  math_Vector X(1, 2);
  solver.Solve(B, X);

  EXPECT_NEAR(X(1), 1.0, 0.02);
  EXPECT_NEAR(X(2), 1.01, 0.02);
}

TEST(math_GaussLeastSquare, ScaledSystem)
{

  math_Matrix A(1, 2, 1, 2);
  A(1, 1) = 0.001;
  A(1, 2) = 0.002;
  A(2, 1) = 0.003;
  A(2, 2) = 0.004;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 2);
  B(1) = 0.005;
  B(2) = 0.007;

  math_Vector X(1, 2);
  solver.Solve(B, X);

  EXPECT_TRUE(std::isfinite(X(1)));
  EXPECT_TRUE(std::isfinite(X(2)));
}

TEST(math_GaussLeastSquare, RectangularMatrix)
{

  math_Matrix A(1, 4, 1, 2);
  A(1, 1) = 1.0;
  A(1, 2) = 1.0;
  A(2, 1) = 1.0;
  A(2, 2) = 2.0;
  A(3, 1) = 2.0;
  A(3, 2) = 1.0;
  A(4, 1) = 2.0;
  A(4, 2) = 2.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 4);
  B(1) = 3.0;
  B(2) = 4.0;
  B(3) = 4.0;
  B(4) = 5.0;

  math_Vector X(1, 2);
  solver.Solve(B, X);

  EXPECT_TRUE(std::isfinite(X(1)));
  EXPECT_TRUE(std::isfinite(X(2)));
  EXPECT_GT(X(1), 0.0);
  EXPECT_GT(X(2), 0.0);
}

TEST(math_GaussLeastSquare, PolynomialFitting)
{

  math_Matrix A(1, 4, 1, 3);

  A(1, 1) = 1.0;
  A(1, 2) = 0.0;
  A(1, 3) = 0.0;
  A(2, 1) = 1.0;
  A(2, 2) = 1.0;
  A(2, 3) = 1.0;
  A(3, 1) = 1.0;
  A(3, 2) = 2.0;
  A(3, 3) = 4.0;
  A(4, 1) = 1.0;
  A(4, 2) = 3.0;
  A(4, 3) = 9.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 4);
  B(1) = 1.0;
  B(2) = 4.0;
  B(3) = 9.0;
  B(4) = 16.0;

  math_Vector X(1, 3);
  solver.Solve(B, X);

  EXPECT_TRUE(std::isfinite(X(1)));
  EXPECT_TRUE(std::isfinite(X(2)));
  EXPECT_TRUE(std::isfinite(X(3)));
  EXPECT_GT(X(3), 0.5);
}

TEST(math_GaussLeastSquare, LinearFitting)
{

  math_Matrix A(1, 3, 1, 2);

  A(1, 1) = 1.0;
  A(1, 2) = 1.0;
  A(2, 1) = 1.0;
  A(2, 2) = 2.0;
  A(3, 1) = 1.0;
  A(3, 2) = 3.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 3);
  B(1) = 2.0;
  B(2) = 4.0;
  B(3) = 6.0;

  math_Vector X(1, 2);
  solver.Solve(B, X);

  EXPECT_NEAR(X(1), 0.0, TOLERANCE);
  EXPECT_NEAR(X(2), 2.0, TOLERANCE);
}

TEST(math_GaussLeastSquare, NoisyData)
{

  math_Matrix A(1, 5, 1, 2);
  A(1, 1) = 1.0;
  A(1, 2) = 1.0;
  A(2, 1) = 1.0;
  A(2, 2) = 2.0;
  A(3, 1) = 1.0;
  A(3, 2) = 3.0;
  A(4, 1) = 1.0;
  A(4, 2) = 4.0;
  A(5, 1) = 1.0;
  A(5, 2) = 5.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 5);
  B(1) = 2.1;
  B(2) = 2.9;
  B(3) = 4.1;
  B(4) = 4.9;
  B(5) = 6.1;

  math_Vector X(1, 2);
  solver.Solve(B, X);

  EXPECT_NEAR(X(1), 1.0, 0.2);
  EXPECT_NEAR(X(2), 1.0, 0.2);
}

TEST(math_GaussLeastSquare, ZeroRightHandSide)
{

  math_Matrix A(1, 2, 1, 2);
  A(1, 1) = 1.0;
  A(1, 2) = 0.0;
  A(2, 1) = 0.0;
  A(2, 2) = 1.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B(1, 2);
  B(1) = 0.0;
  B(2) = 0.0;

  math_Vector X(1, 2);
  solver.Solve(B, X);

  EXPECT_NEAR(X(1), 0.0, TOLERANCE);
  EXPECT_NEAR(X(2), 0.0, TOLERANCE);
}

TEST(math_GaussLeastSquare, MultipleRightHandSides)
{

  math_Matrix A(1, 2, 1, 2);
  A(1, 1) = 2.0;
  A(1, 2) = 1.0;
  A(2, 1) = 1.0;
  A(2, 2) = 2.0;

  math_GaussLeastSquare solver(A);

  EXPECT_TRUE(solver.IsDone());

  math_Vector B1(1, 2);
  B1(1) = 3.0;
  B1(2) = 3.0;

  math_Vector X1(1, 2);
  solver.Solve(B1, X1);

  EXPECT_NEAR(X1(1), 1.0, TOLERANCE);
  EXPECT_NEAR(X1(2), 1.0, TOLERANCE);

  math_Vector B2(1, 2);
  B2(1) = 5.0;
  B2(2) = 4.0;

  math_Vector X2(1, 2);
  solver.Solve(B2, X2);

  EXPECT_NEAR(X2(1), 2.0, TOLERANCE);
  EXPECT_NEAR(X2(2), 1.0, TOLERANCE);
}
