

#include <gtest/gtest.h>
#include <math_TrigonometricFunctionRoots.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>

namespace
{
  const double PI        = M_PI;
  const double TOLERANCE = 1.0e-6;
} // namespace

TEST(math_TrigonometricFunctionRoots, FullEquationBasic)
{

  double                          a = 1.0, b = 0.0, c = 1.0, d = 0.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(a, b, c, d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GT(solver.NbSolutions(), 0);
}

TEST(math_TrigonometricFunctionRoots, LinearSineOnly)
{

  double                          d = 1.0, e = -0.5;
  math_TrigonometricFunctionRoots solver(d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GT(solver.NbSolutions(), 0);

  if (solver.NbSolutions() >= 1)
  {
    double x1      = solver.Value(1);
    double sin_val = sin(x1);
    EXPECT_NEAR(sin_val, 0.5, TOLERANCE);
  }
}

TEST(math_TrigonometricFunctionRoots, LinearCosineAndSine)
{

  double                          c = 1.0, d = 1.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(c, d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GT(solver.NbSolutions(), 0);

  if (solver.NbSolutions() >= 1)
  {
    double x1     = solver.Value(1);
    double result = cos(x1) + sin(x1);
    EXPECT_NEAR(result, 0.0, TOLERANCE);
  }
}

TEST(math_TrigonometricFunctionRoots, PureCosineEquation)
{

  double                          c = 1.0, d = 0.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(c, d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GE(solver.NbSolutions(), 1);

  if (solver.NbSolutions() >= 1)
  {
    double x1 = solver.Value(1);
    EXPECT_NEAR(fabs(cos(x1)), 0.0, TOLERANCE);
  }
}

TEST(math_TrigonometricFunctionRoots, PureSineEquation)
{

  double                          d = 1.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GE(solver.NbSolutions(), 2);

  if (solver.NbSolutions() >= 1)
  {
    double x1 = solver.Value(1);
    EXPECT_NEAR(fabs(sin(x1)), 0.0, TOLERANCE);
  }
}

TEST(math_TrigonometricFunctionRoots, NoSolution)
{

  double                          d = 1.0, e = 2.0;
  math_TrigonometricFunctionRoots solver(d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_EQ(solver.NbSolutions(), 0);
}

TEST(math_TrigonometricFunctionRoots, InfiniteSolutions)
{

  double                          d = 0.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_TRUE(solver.InfiniteRoots());
}

TEST(math_TrigonometricFunctionRoots, CustomBounds)
{

  double                          d = 1.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(d, e, PI / 2.0, 3.0 * PI / 2.0);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GE(solver.NbSolutions(), 1);

  for (int i = 1; i <= solver.NbSolutions(); i++)
  {
    double x = solver.Value(i);
    EXPECT_GE(x, PI / 2.0);
    EXPECT_LE(x, 3.0 * PI / 2.0);
    EXPECT_NEAR(fabs(sin(x)), 0.0, TOLERANCE);
  }
}

TEST(math_TrigonometricFunctionRoots, NarrowBounds)
{

  double                          c = 1.0, d = 0.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(c, d, e, 0.0, PI / 4.0);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());

  EXPECT_EQ(solver.NbSolutions(), 0);
}

TEST(math_TrigonometricFunctionRoots, QuadraticTerms)
{

  double                          a = 1.0, b = 0.0, c = 0.0, d = 0.0, e = -0.5;
  math_TrigonometricFunctionRoots solver(a, b, c, d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GE(solver.NbSolutions(), 2);

  if (solver.NbSolutions() >= 1)
  {
    double x1          = solver.Value(1);
    double cos_squared = cos(x1) * cos(x1);
    EXPECT_NEAR(cos_squared, 0.5, TOLERANCE);
  }
}

TEST(math_TrigonometricFunctionRoots, MixedTerms)
{

  double                          c = 1.0, d = 1.0, e = -sqrt(2.0);
  math_TrigonometricFunctionRoots solver(c, d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GE(solver.NbSolutions(), 1);

  if (solver.NbSolutions() >= 1)
  {
    double x1     = solver.Value(1);
    double result = cos(x1) + sin(x1);
    EXPECT_NEAR(result, sqrt(2.0), TOLERANCE);
  }
}

TEST(math_TrigonometricFunctionRoots, AllCoefficients)
{

  double                          a = 1.0, b = 0.5, c = 0.5, d = 0.5, e = -0.25;
  math_TrigonometricFunctionRoots solver(a, b, c, d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());

  for (int i = 1; i <= solver.NbSolutions(); i++)
  {
    double x      = solver.Value(i);
    double result = a * cos(x) * cos(x) + 2.0 * b * cos(x) * sin(x) + c * cos(x) + d * sin(x) + e;
    EXPECT_NEAR(result, 0.0, TOLERANCE);
  }
}

TEST(math_TrigonometricFunctionRoots, LargeBounds)
{

  double                          d = 1.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(d, e, 0.0, 4.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GE(solver.NbSolutions(), 2);
}

TEST(math_TrigonometricFunctionRoots, NegativeBounds)
{

  double                          c = 1.0, d = 0.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(c, d, e, -PI, PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GE(solver.NbSolutions(), 1);

  for (int i = 1; i <= solver.NbSolutions(); i++)
  {
    double x = solver.Value(i);
    EXPECT_GE(x, -PI);
    EXPECT_LE(x, PI);
    EXPECT_NEAR(fabs(cos(x)), 0.0, TOLERANCE);
  }
}

TEST(math_TrigonometricFunctionRoots, HighFrequencyTest)
{

  double                          d = 1.0, e = -0.5;
  math_TrigonometricFunctionRoots solver(d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());
  EXPECT_FALSE(solver.InfiniteRoots());
  EXPECT_GE(solver.NbSolutions(), 2);

  if (solver.NbSolutions() >= 2)
  {
    std::vector<double> solutions;
    for (int i = 1; i <= solver.NbSolutions(); i++)
    {
      solutions.push_back(solver.Value(i));
    }

    bool found_first = false, found_second = false;
    for (double sol : solutions)
    {
      if (fabs(sol - PI / 6.0) < 0.1)
        found_first = true;
      if (fabs(sol - 5.0 * PI / 6.0) < 0.1)
        found_second = true;
    }
    EXPECT_TRUE(found_first || found_second);
  }
}

TEST(math_TrigonometricFunctionRoots, EdgeCaseSmallCoefficients)
{

  double                          c = 1.0e-10, d = 1.0, e = 0.0;
  math_TrigonometricFunctionRoots solver(c, d, e, 0.0, 2.0 * PI);

  EXPECT_TRUE(solver.IsDone());

  if (!solver.InfiniteRoots())
  {
    EXPECT_GE(solver.NbSolutions(), 2);
  }
}
