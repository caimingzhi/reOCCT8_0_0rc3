

#include <gtest/gtest.h>

#include <MathLin_Gauss.hpp>
#include <math_Gauss.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-10;
}

TEST(MathLin_ComparisonTest, Solve_3x3System)
{

  math_Matrix aA(1, 3, 1, 3);
  aA(1, 1) = 3.0;
  aA(1, 2) = 2.0;
  aA(1, 3) = -1.0;
  aA(2, 1) = 2.0;
  aA(2, 2) = -2.0;
  aA(2, 3) = 4.0;
  aA(3, 1) = -1.0;
  aA(3, 2) = 0.5;
  aA(3, 3) = -1.0;

  math_Vector aB(1, 3);
  aB(1) = 1.0;
  aB(2) = -2.0;
  aB(3) = 0.0;

  auto aNewResult = MathLin::Solve(aA, aB);
  ASSERT_TRUE(aNewResult.IsDone());
  ASSERT_TRUE(aNewResult.Solution.has_value());

  math_Gauss aOldGauss(aA);
  ASSERT_TRUE(aOldGauss.IsDone());
  math_Vector aOldX(1, 3);
  aOldGauss.Solve(aB, aOldX);

  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR((*aNewResult.Solution)(i), aOldX(i), THE_TOLERANCE)
      << "Solution differs at index " << i;
  }
}

TEST(MathLin_ComparisonTest, Solve_5x5System)
{

  math_Matrix aA(1, 5, 1, 5, 0.0);
  for (int i = 1; i <= 5; ++i)
  {
    aA(i, i) = 10.0;
    if (i > 1)
    {
      aA(i, i - 1) = -2.0;
    }
    if (i < 5)
    {
      aA(i, i + 1) = -3.0;
    }
  }

  math_Vector aB(1, 5);
  for (int i = 1; i <= 5; ++i)
  {
    aB(i) = static_cast<double>(i);
  }

  auto aNewResult = MathLin::Solve(aA, aB);
  ASSERT_TRUE(aNewResult.IsDone());

  math_Gauss aOldGauss(aA);
  ASSERT_TRUE(aOldGauss.IsDone());
  math_Vector aOldX(1, 5);
  aOldGauss.Solve(aB, aOldX);

  for (int i = 1; i <= 5; ++i)
  {
    EXPECT_NEAR((*aNewResult.Solution)(i), aOldX(i), THE_TOLERANCE)
      << "Solution differs at index " << i;
  }
}

TEST(MathLin_ComparisonTest, Determinant_3x3Matrix)
{

  math_Matrix aA(1, 3, 1, 3);
  aA(1, 1) = 6.0;
  aA(1, 2) = 1.0;
  aA(1, 3) = 1.0;
  aA(2, 1) = 4.0;
  aA(2, 2) = -2.0;
  aA(2, 3) = 5.0;
  aA(3, 1) = 2.0;
  aA(3, 2) = 8.0;
  aA(3, 3) = 7.0;

  auto aNewResult = MathLin::Determinant(aA);
  ASSERT_TRUE(aNewResult.IsDone());
  ASSERT_TRUE(aNewResult.Determinant.has_value());

  math_Gauss aOldGauss(aA);
  ASSERT_TRUE(aOldGauss.IsDone());
  double aOldDet = aOldGauss.Determinant();

  EXPECT_NEAR(*aNewResult.Determinant, aOldDet, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Determinant, -306.0, THE_TOLERANCE);
}

TEST(MathLin_ComparisonTest, Determinant_IdentityMatrix)
{

  math_Matrix aI(1, 4, 1, 4, 0.0);
  for (int i = 1; i <= 4; ++i)
  {
    aI(i, i) = 1.0;
  }

  auto aNewResult = MathLin::Determinant(aI);
  ASSERT_TRUE(aNewResult.IsDone());

  math_Gauss aOldGauss(aI);
  ASSERT_TRUE(aOldGauss.IsDone());
  double aOldDet = aOldGauss.Determinant();

  EXPECT_NEAR(*aNewResult.Determinant, 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aOldDet, 1.0, THE_TOLERANCE);
}

TEST(MathLin_ComparisonTest, Invert_3x3Matrix)
{

  math_Matrix aA(1, 3, 1, 3);
  aA(1, 1) = 1.0;
  aA(1, 2) = 2.0;
  aA(1, 3) = 3.0;
  aA(2, 1) = 0.0;
  aA(2, 2) = 1.0;
  aA(2, 3) = 4.0;
  aA(3, 1) = 5.0;
  aA(3, 2) = 6.0;
  aA(3, 3) = 0.0;

  auto aNewResult = MathLin::Invert(aA);
  ASSERT_TRUE(aNewResult.IsDone());
  ASSERT_TRUE(aNewResult.Inverse.has_value());

  math_Gauss aOldGauss(aA);
  ASSERT_TRUE(aOldGauss.IsDone());
  math_Matrix aOldInv(1, 3, 1, 3);
  aOldGauss.Invert(aOldInv);

  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      EXPECT_NEAR((*aNewResult.Inverse)(i, j), aOldInv(i, j), THE_TOLERANCE)
        << "Inverse differs at (" << i << ", " << j << ")";
    }
  }
}

TEST(MathLin_ComparisonTest, Invert_VerifyByMultiplication)
{

  math_Matrix aA(1, 3, 1, 3);
  aA(1, 1) = 2.0;
  aA(1, 2) = 1.0;
  aA(1, 3) = 1.0;
  aA(2, 1) = 1.0;
  aA(2, 2) = 3.0;
  aA(2, 3) = 2.0;
  aA(3, 1) = 1.0;
  aA(3, 2) = 2.0;
  aA(3, 3) = 2.0;

  auto aNewResult = MathLin::Invert(aA);
  ASSERT_TRUE(aNewResult.IsDone());

  math_Matrix aProduct = aA * (*aNewResult.Inverse);

  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      double aExpected = (i == j) ? 1.0 : 0.0;
      EXPECT_NEAR(aProduct(i, j), aExpected, THE_TOLERANCE)
        << "Product differs at (" << i << ", " << j << ")";
    }
  }
}

TEST(MathLin_ComparisonTest, LU_Decomposition)
{

  math_Matrix aA(1, 3, 1, 3);
  aA(1, 1) = 2.0;
  aA(1, 2) = 1.0;
  aA(1, 3) = 1.0;
  aA(2, 1) = 4.0;
  aA(2, 2) = 3.0;
  aA(2, 3) = 3.0;
  aA(3, 1) = 8.0;
  aA(3, 2) = 7.0;
  aA(3, 3) = 9.0;

  auto aLUResult = MathLin::LU(aA);
  ASSERT_TRUE(aLUResult.IsDone());
  ASSERT_TRUE(aLUResult.LU.has_value());
  ASSERT_TRUE(aLUResult.Pivot.has_value());
  ASSERT_TRUE(aLUResult.Determinant.has_value());

  const math_Matrix& aLUMat = *aLUResult.LU;

  math_Matrix aL(1, 3, 1, 3, 0.0);
  math_Matrix aU(1, 3, 1, 3, 0.0);

  for (int i = 1; i <= 3; ++i)
  {
    aL(i, i) = 1.0;
    for (int j = 1; j < i; ++j)
    {
      aL(i, j) = aLUMat(i, j);
    }
    for (int j = i; j <= 3; ++j)
    {
      aU(i, j) = aLUMat(i, j);
    }
  }

  math_Matrix aLU = aL * aU;
  (void)aLU;

  math_Vector aB(1, 3);
  aB(1) = 1.0;
  aB(2) = 2.0;
  aB(3) = 3.0;

  auto aSolveResult = MathLin::Solve(aA, aB);
  ASSERT_TRUE(aSolveResult.IsDone());

  math_Vector aResidual = aA * (*aSolveResult.Solution);
  for (int i = 1; i <= 3; ++i)
  {
    aResidual(i) -= aB(i);
    EXPECT_NEAR(aResidual(i), 0.0, THE_TOLERANCE) << "Residual at " << i;
  }
}

TEST(MathLin_ComparisonTest, SingularMatrix_Detection)
{

  math_Matrix aA(1, 3, 1, 3);
  aA(1, 1) = 1.0;
  aA(1, 2) = 2.0;
  aA(1, 3) = 3.0;
  aA(2, 1) = 4.0;
  aA(2, 2) = 5.0;
  aA(2, 3) = 6.0;
  aA(3, 1) = 1.0;
  aA(3, 2) = 2.0;
  aA(3, 3) = 3.0;

  auto aNewResult = MathLin::LU(aA);
  EXPECT_FALSE(aNewResult.IsDone());

  math_Gauss aOldGauss(aA);
  EXPECT_FALSE(aOldGauss.IsDone());
}

TEST(MathLin_ComparisonTest, IllConditioned_HilbertMatrix)
{

  const int   aN = 4;
  math_Matrix aH(1, aN, 1, aN);
  for (int i = 1; i <= aN; ++i)
  {
    for (int j = 1; j <= aN; ++j)
    {
      aH(i, j) = 1.0 / static_cast<double>(i + j - 1);
    }
  }

  math_Vector aB(1, aN);
  for (int i = 1; i <= aN; ++i)
  {
    aB(i) = 1.0;
  }

  auto aNewResult = MathLin::Solve(aH, aB);
  ASSERT_TRUE(aNewResult.IsDone());

  math_Gauss aOldGauss(aH);
  ASSERT_TRUE(aOldGauss.IsDone());
  math_Vector aOldX(1, aN);
  aOldGauss.Solve(aB, aOldX);

  constexpr double aLooseTol = 1.0e-6;
  for (int i = 1; i <= aN; ++i)
  {
    EXPECT_NEAR((*aNewResult.Solution)(i), aOldX(i), aLooseTol)
      << "Solution differs at index " << i;
  }
}

TEST(MathLin_ComparisonTest, Determinant_MultipleMatrices)
{

  struct TestCase
  {
    double a11, a12, a21, a22;
    double expectedDet;
  };

  TestCase aCases[] = {
    {1.0, 0.0, 0.0, 1.0, 1.0},
    {2.0, 0.0, 0.0, 3.0, 6.0},
    {1.0, 2.0, 3.0, 4.0, -2.0},
    {0.0, 1.0, 1.0, 0.0, -1.0},
  };

  for (const auto& aCase : aCases)
  {
    math_Matrix aA(1, 2, 1, 2);
    aA(1, 1) = aCase.a11;
    aA(1, 2) = aCase.a12;
    aA(2, 1) = aCase.a21;
    aA(2, 2) = aCase.a22;

    auto aNewResult = MathLin::Determinant(aA);
    ASSERT_TRUE(aNewResult.IsDone());

    math_Gauss aOldGauss(aA);
    ASSERT_TRUE(aOldGauss.IsDone());

    EXPECT_NEAR(*aNewResult.Determinant, aOldGauss.Determinant(), THE_TOLERANCE);
    EXPECT_NEAR(*aNewResult.Determinant, aCase.expectedDet, THE_TOLERANCE);
  }
}

TEST(MathLin_ComparisonTest, Solve_KnownSolution)
{

  math_Matrix aA(1, 3, 1, 3);
  aA(1, 1) = 1.0;
  aA(1, 2) = 0.0;
  aA(1, 3) = 0.0;
  aA(2, 1) = 0.0;
  aA(2, 2) = 1.0;
  aA(2, 3) = 0.0;
  aA(3, 1) = 0.0;
  aA(3, 2) = 0.0;
  aA(3, 3) = 1.0;

  math_Vector aExpectedX(1, 3);
  aExpectedX(1) = 1.0;
  aExpectedX(2) = 2.0;
  aExpectedX(3) = 3.0;

  math_Vector aB = aA * aExpectedX;

  auto aNewResult = MathLin::Solve(aA, aB);
  ASSERT_TRUE(aNewResult.IsDone());

  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR((*aNewResult.Solution)(i), aExpectedX(i), THE_TOLERANCE);
  }
}

TEST(MathLin_ComparisonTest, Solve_ComplexKnownSolution)
{

  math_Matrix aA(1, 4, 1, 4);
  aA(1, 1) = 5.0;
  aA(1, 2) = 7.0;
  aA(1, 3) = 6.0;
  aA(1, 4) = 5.0;
  aA(2, 1) = 7.0;
  aA(2, 2) = 10.0;
  aA(2, 3) = 8.0;
  aA(2, 4) = 7.0;
  aA(3, 1) = 6.0;
  aA(3, 2) = 8.0;
  aA(3, 3) = 10.0;
  aA(3, 4) = 9.0;
  aA(4, 1) = 5.0;
  aA(4, 2) = 7.0;
  aA(4, 3) = 9.0;
  aA(4, 4) = 10.0;

  math_Vector aExpectedX(1, 4);
  aExpectedX(1) = 1.0;
  aExpectedX(2) = -1.0;
  aExpectedX(3) = 2.0;
  aExpectedX(4) = -2.0;

  math_Vector aB = aA * aExpectedX;

  auto aNewResult = MathLin::Solve(aA, aB);
  ASSERT_TRUE(aNewResult.IsDone());

  math_Gauss aOldGauss(aA);
  ASSERT_TRUE(aOldGauss.IsDone());
  math_Vector aOldX(1, 4);
  aOldGauss.Solve(aB, aOldX);

  for (int i = 1; i <= 4; ++i)
  {
    EXPECT_NEAR((*aNewResult.Solution)(i), aExpectedX(i), THE_TOLERANCE);
    EXPECT_NEAR(aOldX(i), aExpectedX(i), THE_TOLERANCE);
    EXPECT_NEAR((*aNewResult.Solution)(i), aOldX(i), THE_TOLERANCE);
  }
}
