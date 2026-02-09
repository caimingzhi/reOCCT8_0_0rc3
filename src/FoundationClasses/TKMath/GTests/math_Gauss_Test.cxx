

#include <math_Gauss.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>
#include <Precision.hpp>

namespace
{

  TEST(MathGaussTest, WellConditionedMatrix)
  {

    math_Matrix aMatrix(1, 3, 1, 3);
    aMatrix(1, 1) = 2.0;
    aMatrix(1, 2) = 1.0;
    aMatrix(1, 3) = 1.0;
    aMatrix(2, 1) = 1.0;
    aMatrix(2, 2) = 3.0;
    aMatrix(2, 3) = 2.0;
    aMatrix(3, 1) = 1.0;
    aMatrix(3, 2) = 2.0;
    aMatrix(3, 3) = 3.0;

    math_Gauss aGauss(aMatrix);

    EXPECT_TRUE(aGauss.IsDone())
      << "Gauss decomposition should succeed for well-conditioned matrix";

    math_Vector aB(1, 3);
    aB(1) = 1.0;
    aB(2) = 2.0;
    aB(3) = 3.0;

    math_Vector aX(1, 3);
    aGauss.Solve(aB, aX);

    math_Vector aVerify(1, 3);
    for (int i = 1; i <= 3; i++)
    {
      aVerify(i) = 0.0;
      for (int j = 1; j <= 3; j++)
      {
        aVerify(i) += aMatrix(i, j) * aX(j);
      }
    }

    EXPECT_NEAR(aVerify(1), aB(1), 1.0e-10) << "Solution verification A*x=b (1)";
    EXPECT_NEAR(aVerify(2), aB(2), 1.0e-10) << "Solution verification A*x=b (2)";
    EXPECT_NEAR(aVerify(3), aB(3), 1.0e-10) << "Solution verification A*x=b (3)";
  }

  TEST(MathGaussTest, IdentityMatrix)
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

    math_Gauss aGauss(aMatrix);
    EXPECT_TRUE(aGauss.IsDone()) << "Gauss decomposition should succeed for identity matrix";

    math_Vector aB(1, 3);
    aB(1) = 5.0;
    aB(2) = 7.0;
    aB(3) = 9.0;

    math_Vector aX(1, 3);
    aGauss.Solve(aB, aX);

    EXPECT_NEAR(aX(1), 5.0, Precision::Confusion()) << "Identity matrix solution X(1)";
    EXPECT_NEAR(aX(2), 7.0, Precision::Confusion()) << "Identity matrix solution X(2)";
    EXPECT_NEAR(aX(3), 9.0, Precision::Confusion()) << "Identity matrix solution X(3)";
  }

  TEST(MathGaussTest, DiagonalMatrix)
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

    math_Gauss aGauss(aMatrix);
    EXPECT_TRUE(aGauss.IsDone()) << "Gauss decomposition should succeed for diagonal matrix";

    math_Vector aB(1, 3);
    aB(1) = 8.0;
    aB(2) = 15.0;
    aB(3) = 20.0;

    math_Vector aX(1, 3);
    aGauss.Solve(aB, aX);

    EXPECT_NEAR(aX(1), 4.0, Precision::Confusion()) << "Diagonal matrix solution X(1)";
    EXPECT_NEAR(aX(2), 5.0, Precision::Confusion()) << "Diagonal matrix solution X(2)";
    EXPECT_NEAR(aX(3), 5.0, Precision::Confusion()) << "Diagonal matrix solution X(3)";
  }

  TEST(MathGaussTest, InPlaceSolve)
  {

    math_Matrix aMatrix(1, 3, 1, 3);
    aMatrix(1, 1) = 1.0;
    aMatrix(1, 2) = 2.0;
    aMatrix(1, 3) = 3.0;
    aMatrix(2, 1) = 2.0;
    aMatrix(2, 2) = 5.0;
    aMatrix(2, 3) = 8.0;
    aMatrix(3, 1) = 3.0;
    aMatrix(3, 2) = 8.0;
    aMatrix(3, 3) = 14.0;

    math_Gauss aGauss(aMatrix);
    EXPECT_TRUE(aGauss.IsDone()) << "Gauss decomposition should succeed";

    math_Vector aB(1, 3);
    aB(1) = 14.0;
    aB(2) = 31.0;
    aB(3) = 53.0;

    aGauss.Solve(aB);

    EXPECT_NEAR(aB(1), 13.0, 1.0e-10) << "In-place solution B(1)";
    EXPECT_NEAR(aB(2), -7.0, 1.0e-10) << "In-place solution B(2)";
    EXPECT_NEAR(aB(3), 5.0, 1.0e-10) << "In-place solution B(3)";
  }

  TEST(MathGaussTest, Determinant)
  {

    math_Matrix aMatrix(1, 3, 1, 3);
    aMatrix(1, 1) = 1.0;
    aMatrix(1, 2) = 2.0;
    aMatrix(1, 3) = 3.0;
    aMatrix(2, 1) = 0.0;
    aMatrix(2, 2) = 1.0;
    aMatrix(2, 3) = 4.0;
    aMatrix(3, 1) = 5.0;
    aMatrix(3, 2) = 6.0;
    aMatrix(3, 3) = 0.0;

    math_Gauss aGauss(aMatrix);
    EXPECT_TRUE(aGauss.IsDone()) << "Gauss decomposition should succeed";

    double aDet = aGauss.Determinant();

    EXPECT_NEAR(aDet, 1.0, 1.0e-12) << "Determinant calculation";
  }

  TEST(MathGaussTest, MatrixInversion)
  {

    math_Matrix aMatrix(1, 2, 1, 2);
    aMatrix(1, 1) = 4.0;
    aMatrix(1, 2) = 7.0;
    aMatrix(2, 1) = 2.0;
    aMatrix(2, 2) = 6.0;

    math_Gauss aGauss(aMatrix);
    EXPECT_TRUE(aGauss.IsDone()) << "Gauss decomposition should succeed";

    math_Matrix aInverse(1, 2, 1, 2);
    aGauss.Invert(aInverse);

    EXPECT_NEAR(aInverse(1, 1), 0.6, 1.0e-12) << "Inverse(1,1)";
    EXPECT_NEAR(aInverse(1, 2), -0.7, 1.0e-12) << "Inverse(1,2)";
    EXPECT_NEAR(aInverse(2, 1), -0.2, 1.0e-12) << "Inverse(2,1)";
    EXPECT_NEAR(aInverse(2, 2), 0.4, 1.0e-12) << "Inverse(2,2)";

    math_Matrix aProduct(1, 2, 1, 2);
    for (int i = 1; i <= 2; i++)
    {
      for (int j = 1; j <= 2; j++)
      {
        aProduct(i, j) = 0.0;
        for (int k = 1; k <= 2; k++)
        {
          aProduct(i, j) += aMatrix(i, k) * aInverse(k, j);
        }
      }
    }

    EXPECT_NEAR(aProduct(1, 1), 1.0, 1.0e-12) << "A * A^(-1) should equal identity (1,1)";
    EXPECT_NEAR(aProduct(1, 2), 0.0, 1.0e-12) << "A * A^(-1) should equal identity (1,2)";
    EXPECT_NEAR(aProduct(2, 1), 0.0, 1.0e-12) << "A * A^(-1) should equal identity (2,1)";
    EXPECT_NEAR(aProduct(2, 2), 1.0, 1.0e-12) << "A * A^(-1) should equal identity (2,2)";
  }

  TEST(MathGaussTest, SingularMatrix)
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

    math_Gauss aGauss(aMatrix);
    if (aGauss.IsDone())
    {
      double aDet = aGauss.Determinant();
      EXPECT_NEAR(aDet, 0.0, 1.0e-12) << "Determinant of singular matrix must be zero";
    }
  }

  TEST(MathGaussTest, CustomMinPivot)
  {

    math_Matrix aMatrix(1, 2, 1, 2);
    aMatrix(1, 1) = 1.0e-15;
    aMatrix(1, 2) = 1.0;
    aMatrix(2, 1) = 1.0;
    aMatrix(2, 2) = 1.0;

    math_Gauss aGauss1(aMatrix);
    EXPECT_TRUE(aGauss1.IsDone()) << "Should succeed with default MinPivot";

    math_Matrix aSingular(1, 2, 1, 2);
    aSingular(1, 1) = 1.0e-25;
    aSingular(1, 2) = 1.0;
    aSingular(2, 1) = 1.0;
    aSingular(2, 2) = 1.0;

    math_Matrix aTrulySingular(1, 2, 1, 2);
    aTrulySingular(1, 1) = 0.0;
    aTrulySingular(1, 2) = 0.0;
    aTrulySingular(2, 1) = 0.0;
    aTrulySingular(2, 2) = 0.0;

    math_Gauss aGauss2(aTrulySingular);
    EXPECT_FALSE(aGauss2.IsDone()) << "Should fail for zero matrix";
  }

  TEST(MathGaussTest, LargerMatrix)
  {

    math_Matrix aMatrix(1, 4, 1, 4);
    aMatrix(1, 1) = 1.0;
    aMatrix(1, 2) = 2.0;
    aMatrix(1, 3) = 1.0;
    aMatrix(1, 4) = 1.0;
    aMatrix(2, 1) = 2.0;
    aMatrix(2, 2) = 1.0;
    aMatrix(2, 3) = 3.0;
    aMatrix(2, 4) = 1.0;
    aMatrix(3, 1) = 1.0;
    aMatrix(3, 2) = 3.0;
    aMatrix(3, 3) = 1.0;
    aMatrix(3, 4) = 2.0;
    aMatrix(4, 1) = 1.0;
    aMatrix(4, 2) = 1.0;
    aMatrix(4, 3) = 2.0;
    aMatrix(4, 4) = 3.0;

    math_Gauss aGauss(aMatrix);
    EXPECT_TRUE(aGauss.IsDone()) << "Gauss decomposition should succeed for 4x4 matrix";

    math_Vector aB(1, 4);
    aB(1) = 1.0;
    aB(2) = 2.0;
    aB(3) = 3.0;
    aB(4) = 4.0;

    math_Vector aX(1, 4);
    aGauss.Solve(aB, aX);

    math_Vector aVerify(1, 4);
    for (int i = 1; i <= 4; i++)
    {
      aVerify(i) = 0.0;
      for (int j = 1; j <= 4; j++)
      {
        aVerify(i) += aMatrix(i, j) * aX(j);
      }
    }

    EXPECT_NEAR(aVerify(1), aB(1), 1.0e-10) << "4x4 matrix solution verification (1)";
    EXPECT_NEAR(aVerify(2), aB(2), 1.0e-10) << "4x4 matrix solution verification (2)";
    EXPECT_NEAR(aVerify(3), aB(3), 1.0e-10) << "4x4 matrix solution verification (3)";
    EXPECT_NEAR(aVerify(4), aB(4), 1.0e-10) << "4x4 matrix solution verification (4)";
  }

  TEST(MathGaussTest, DimensionCompatibility)
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

    math_Gauss aGauss(aMatrix);
    EXPECT_TRUE(aGauss.IsDone());

    math_Vector aB(1, 3);
    aB(1) = 1.0;
    aB(2) = 2.0;
    aB(3) = 3.0;

    math_Vector aX(1, 3);
    aGauss.Solve(aB, aX);

    EXPECT_EQ(aX.Length(), 3) << "Solution vector should have correct dimension";

    math_Matrix aInv(1, 3, 1, 3);
    aGauss.Invert(aInv);

    EXPECT_EQ(aInv.RowNumber(), 3) << "Inverse matrix should have correct dimensions";
    EXPECT_EQ(aInv.ColNumber(), 3) << "Inverse matrix should have correct dimensions";
  }

  TEST(MathGaussTest, SingularMatrixState)
  {

    math_Matrix aMatrix(1, 2, 1, 2);
    aMatrix(1, 1) = 1.0;
    aMatrix(1, 2) = 2.0;
    aMatrix(2, 1) = 2.0;
    aMatrix(2, 2) = 4.0;

    math_Gauss aGauss(aMatrix);
    EXPECT_FALSE(aGauss.IsDone()) << "Should fail for singular matrix";
  }

  TEST(MathGaussTest, CustomBounds)
  {

    math_Matrix aMatrix(2, 4, 3, 5);
    aMatrix(2, 3) = 2.0;
    aMatrix(2, 4) = 1.0;
    aMatrix(2, 5) = 1.0;
    aMatrix(3, 3) = 1.0;
    aMatrix(3, 4) = 3.0;
    aMatrix(3, 5) = 2.0;
    aMatrix(4, 3) = 1.0;
    aMatrix(4, 4) = 2.0;
    aMatrix(4, 5) = 3.0;

    math_Gauss aGauss(aMatrix);
    EXPECT_TRUE(aGauss.IsDone()) << "Gauss decomposition should succeed with custom bounds";

    math_Vector aB(2, 4);
    aB(2) = 6.0;
    aB(3) = 11.0;
    aB(4) = 13.0;

    math_Vector aX(3, 5);
    aGauss.Solve(aB, aX);

    EXPECT_NEAR(aX(3), 0.75, 1.0e-10) << "Custom bounds solution X(3)";
    EXPECT_NEAR(aX(4), 1.25, 1.0e-10) << "Custom bounds solution X(4)";
    EXPECT_NEAR(aX(5), 3.25, 1.0e-10) << "Custom bounds solution X(5)";
  }

} // namespace
