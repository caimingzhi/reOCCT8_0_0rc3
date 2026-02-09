

#include <math_Crout.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>
#include <math_NotSquare.hpp>
#include <Precision.hpp>

namespace
{

}

TEST(MathCroutTest, SimpleSymmetricMatrix)
{

  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix(1, 1) = 4.0;
  aMatrix(1, 2) = 2.0;
  aMatrix(1, 3) = 1.0;
  aMatrix(2, 1) = 2.0;
  aMatrix(2, 2) = 3.0;
  aMatrix(2, 3) = 0.5;
  aMatrix(3, 1) = 1.0;
  aMatrix(3, 2) = 0.5;
  aMatrix(3, 3) = 2.0;

  math_Crout aCrout(aMatrix);

  EXPECT_TRUE(aCrout.IsDone()) << "Crout decomposition should succeed";

  math_Vector aB(1, 3);
  aB(1) = 7.0;
  aB(2) = 5.5;
  aB(3) = 3.5;

  math_Vector aX(1, 3);
  aCrout.Solve(aB, aX);

  EXPECT_NEAR(aX(1), 1.0, 1.0e-10) << "Solution X(1) should be 1";
  EXPECT_NEAR(aX(2), 1.0, 1.0e-10) << "Solution X(2) should be 1";
  EXPECT_NEAR(aX(3), 1.0, 1.0e-10) << "Solution X(3) should be 1";
}

TEST(MathCroutTest, IdentityMatrix)
{

  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 0.0;
  aMatrix(1, 3) = 0.0;
  aMatrix(2, 1) = 0.0;
  aMatrix(2, 2) = 1.0;
  aMatrix(2, 3) = 0.0;
  aMatrix(3, 1) = 0.0;
  aMatrix(3, 2) = 0.0;
  aMatrix(3, 3) = 1.0;

  math_Crout aCrout(aMatrix);

  EXPECT_TRUE(aCrout.IsDone()) << "Identity matrix decomposition should succeed";

  math_Vector aB(1, 3);
  aB(1) = 5.0;
  aB(2) = 7.0;
  aB(3) = 9.0;

  math_Vector aX(1, 3);
  aCrout.Solve(aB, aX);

  EXPECT_NEAR(aX(1), 5.0, 1.0e-12) << "Identity matrix solution X(1)";
  EXPECT_NEAR(aX(2), 7.0, 1.0e-12) << "Identity matrix solution X(2)";
  EXPECT_NEAR(aX(3), 9.0, 1.0e-12) << "Identity matrix solution X(3)";

  const math_Matrix& aInverse = aCrout.Inverse();
  EXPECT_NEAR(aInverse(1, 1), 1.0, 1.0e-12) << "Inverse should be identity";
  EXPECT_NEAR(aInverse(2, 2), 1.0, 1.0e-12) << "Inverse should be identity";
  EXPECT_NEAR(aInverse(3, 3), 1.0, 1.0e-12) << "Inverse should be identity";
}

TEST(MathCroutTest, DiagonalMatrix)
{

  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix(1, 1) = 2.0;
  aMatrix(1, 2) = 0.0;
  aMatrix(1, 3) = 0.0;
  aMatrix(2, 1) = 0.0;
  aMatrix(2, 2) = 3.0;
  aMatrix(2, 3) = 0.0;
  aMatrix(3, 1) = 0.0;
  aMatrix(3, 2) = 0.0;
  aMatrix(3, 3) = 4.0;

  math_Crout aCrout(aMatrix);

  EXPECT_TRUE(aCrout.IsDone()) << "Diagonal matrix decomposition should succeed";

  math_Vector aB(1, 3);
  aB(1) = 4.0;
  aB(2) = 9.0;
  aB(3) = 12.0;

  math_Vector aX(1, 3);
  aCrout.Solve(aB, aX);

  EXPECT_NEAR(aX(1), 2.0, 1.0e-12) << "Diagonal solution X(1)";
  EXPECT_NEAR(aX(2), 3.0, 1.0e-12) << "Diagonal solution X(2)";
  EXPECT_NEAR(aX(3), 3.0, 1.0e-12) << "Diagonal solution X(3)";
}

TEST(MathCroutTest, LowerTriangularInput)
{

  math_Matrix aMatrix(1, 3, 1, 3);

  aMatrix(1, 1) = 4.0;
  aMatrix(1, 2) = 0.0;
  aMatrix(1, 3) = 0.0;
  aMatrix(2, 1) = 2.0;
  aMatrix(2, 2) = 3.0;
  aMatrix(2, 3) = 0.0;
  aMatrix(3, 1) = 1.0;
  aMatrix(3, 2) = 0.5;
  aMatrix(3, 3) = 2.0;

  math_Crout aCrout(aMatrix);

  EXPECT_TRUE(aCrout.IsDone()) << "Lower triangular input should work";
}

TEST(MathCroutTest, CustomMinPivot)
{

  math_Matrix aMatrix(1, 2, 1, 2);
  aMatrix(1, 1) = 1.0e-15;
  aMatrix(1, 2) = 1.0;
  aMatrix(2, 1) = 1.0;
  aMatrix(2, 2) = 1.0;

  math_Crout aCrout1(aMatrix, 1.0e-10);
  EXPECT_FALSE(aCrout1.IsDone()) << "Should fail with large MinPivot";

  math_Crout aCrout2(aMatrix, 1.0e-20);
  EXPECT_TRUE(aCrout2.IsDone()) << "Should succeed with small MinPivot";
}

TEST(MathCroutTest, SingularMatrix)
{

  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 2.0;
  aMatrix(1, 3) = 3.0;
  aMatrix(2, 1) = 2.0;
  aMatrix(2, 2) = 4.0;
  aMatrix(2, 3) = 6.0;
  aMatrix(3, 1) = 3.0;
  aMatrix(3, 2) = 6.0;
  aMatrix(3, 3) = 9.0;

  math_Crout aCrout(aMatrix);

  EXPECT_FALSE(aCrout.IsDone()) << "Should fail for singular matrix";
}

TEST(MathCroutTest, NonSquareMatrixCheck)
{

  math_Matrix aMatrix(1, 2, 1, 3);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 2.0;
  aMatrix(1, 3) = 3.0;
  aMatrix(2, 1) = 4.0;
  aMatrix(2, 2) = 5.0;
  aMatrix(2, 3) = 6.0;

  EXPECT_NE(aMatrix.RowNumber(), aMatrix.ColNumber())
    << "Matrix should be non-square for this test";
}

TEST(MathCroutTest, DimensionCompatibilityInSolve)
{

  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 0.0;
  aMatrix(1, 3) = 0.0;
  aMatrix(2, 1) = 0.0;
  aMatrix(2, 2) = 1.0;
  aMatrix(2, 3) = 0.0;
  aMatrix(3, 1) = 0.0;
  aMatrix(3, 2) = 0.0;
  aMatrix(3, 3) = 1.0;

  math_Crout aCrout(aMatrix);
  EXPECT_TRUE(aCrout.IsDone()) << "Decomposition should succeed";

  math_Vector aB_correct(1, 3);
  aB_correct(1) = 1.0;
  aB_correct(2) = 2.0;
  aB_correct(3) = 3.0;

  math_Vector aX(1, 3);
  aCrout.Solve(aB_correct, aX);

  EXPECT_EQ(aX.Length(), 3) << "Solution vector should have correct dimension";
}

TEST(MathCroutTest, SingularMatrixState)
{

  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 2.0;
  aMatrix(1, 3) = 3.0;
  aMatrix(2, 1) = 2.0;
  aMatrix(2, 2) = 4.0;
  aMatrix(2, 3) = 6.0;
  aMatrix(3, 1) = 3.0;
  aMatrix(3, 2) = 6.0;
  aMatrix(3, 3) = 9.0;

  math_Crout aCrout(aMatrix);
  EXPECT_FALSE(aCrout.IsDone()) << "Should fail for singular matrix";
}

TEST(MathCroutTest, LargerMatrix)
{

  math_Matrix aMatrix(1, 4, 1, 4);
  aMatrix(1, 1) = 10.0;
  aMatrix(1, 2) = 1.0;
  aMatrix(1, 3) = 2.0;
  aMatrix(1, 4) = 3.0;
  aMatrix(2, 1) = 1.0;
  aMatrix(2, 2) = 10.0;
  aMatrix(2, 3) = 1.0;
  aMatrix(2, 4) = 4.0;
  aMatrix(3, 1) = 2.0;
  aMatrix(3, 2) = 1.0;
  aMatrix(3, 3) = 10.0;
  aMatrix(3, 4) = 1.0;
  aMatrix(4, 1) = 3.0;
  aMatrix(4, 2) = 4.0;
  aMatrix(4, 3) = 1.0;
  aMatrix(4, 4) = 10.0;

  math_Crout aCrout(aMatrix);

  EXPECT_TRUE(aCrout.IsDone()) << "4x4 matrix decomposition should succeed";

  math_Vector aB(1, 4);
  aB(1) = 16.0;
  aB(2) = 16.0;
  aB(3) = 14.0;
  aB(4) = 18.0;

  math_Vector aX(1, 4);
  aCrout.Solve(aB, aX);

  math_Vector aResidual(1, 4);
  for (int i = 1; i <= 4; i++)
  {
    aResidual(i) = 0.0;
    for (int j = 1; j <= 4; j++)
    {
      aResidual(i) += aMatrix(i, j) * aX(j);
    }
    aResidual(i) -= aB(i);
  }

  double aResidualNorm = 0.0;
  for (int i = 1; i <= 4; i++)
  {
    aResidualNorm += aResidual(i) * aResidual(i);
  }

  EXPECT_LT(aResidualNorm, 1.0e-20) << "Residual should be very small";
}

TEST(MathCroutTest, CustomBounds)
{

  math_Matrix aMatrix(2, 4, 3, 5);
  aMatrix(2, 3) = 4.0;
  aMatrix(2, 4) = 2.0;
  aMatrix(2, 5) = 1.0;
  aMatrix(3, 3) = 2.0;
  aMatrix(3, 4) = 3.0;
  aMatrix(3, 5) = 0.5;
  aMatrix(4, 3) = 1.0;
  aMatrix(4, 4) = 0.5;
  aMatrix(4, 5) = 2.0;

  math_Crout aCrout(aMatrix);

  EXPECT_TRUE(aCrout.IsDone()) << "Custom bounds matrix should work";

  math_Vector aB(2, 4);
  aB(2) = 7.0;
  aB(3) = 5.5;
  aB(4) = 3.5;

  math_Vector aX(3, 5);
  aCrout.Solve(aB, aX);

  EXPECT_GT(aX(3), 0.0) << "Solution should be reasonable";
  EXPECT_GT(aX(4), 0.0) << "Solution should be reasonable";
  EXPECT_GT(aX(5), 0.0) << "Solution should be reasonable";
}
