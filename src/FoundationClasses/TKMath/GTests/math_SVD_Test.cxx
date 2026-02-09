

#include <math_SVD.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  void checkSolution(const math_Matrix& theA,
                     const math_Vector& theX,
                     const math_Vector& theB,
                     const double       theTolerance = 1.0e-10)
  {
    ASSERT_EQ(theA.ColNumber(), theX.Length())
      << "Matrix and solution vector dimensions must match";
    ASSERT_EQ(theA.RowNumber(), theB.Length()) << "Matrix and RHS vector dimensions must match";

    math_Vector aResult(theB.Lower(), theB.Upper());
    for (int anI = theA.LowerRow(); anI <= theA.UpperRow(); anI++)
    {
      double aSum = 0.0;
      for (int aJ = theA.LowerCol(); aJ <= theA.UpperCol(); aJ++)
      {
        aSum += theA(anI, aJ) * theX(aJ - theA.LowerCol() + theX.Lower());
      }
      aResult(anI - theA.LowerRow() + theB.Lower()) = aSum;
    }

    for (int anI = theB.Lower(); anI <= theB.Upper(); anI++)
    {
      EXPECT_NEAR(aResult(anI), theB(anI), theTolerance)
        << "Solution verification failed at index " << anI;
    }
  }

  math_Matrix createWellConditionedMatrix()
  {
    math_Matrix aMatrix(1, 3, 1, 3);
    aMatrix(1, 1) = 2.0;
    aMatrix(1, 2) = 1.0;
    aMatrix(1, 3) = 0.0;
    aMatrix(2, 1) = 1.0;
    aMatrix(2, 2) = 2.0;
    aMatrix(2, 3) = 1.0;
    aMatrix(3, 1) = 0.0;
    aMatrix(3, 2) = 1.0;
    aMatrix(3, 3) = 2.0;
    return aMatrix;
  }
} // namespace

TEST(MathSVDTest, WellConditionedSquareMatrix)
{
  math_Matrix aMatrix = createWellConditionedMatrix();
  math_SVD    aSVD(aMatrix);

  EXPECT_TRUE(aSVD.IsDone()) << "SVD decomposition should succeed for well-conditioned matrix";

  math_Vector aB(1, 3);
  aB(1) = 6.0;
  aB(2) = 9.0;
  aB(3) = 8.0;

  math_Vector aX(1, 3);
  aSVD.Solve(aB, aX);

  checkSolution(aMatrix, aX, aB);
}

TEST(MathSVDTest, IdentityMatrix)
{

  math_Matrix anIdentity(1, 3, 1, 3);
  anIdentity(1, 1) = 1.0;
  anIdentity(1, 2) = 0.0;
  anIdentity(1, 3) = 0.0;
  anIdentity(2, 1) = 0.0;
  anIdentity(2, 2) = 1.0;
  anIdentity(2, 3) = 0.0;
  anIdentity(3, 1) = 0.0;
  anIdentity(3, 2) = 0.0;
  anIdentity(3, 3) = 1.0;

  math_SVD aSVD(anIdentity);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should succeed for identity matrix";

  math_Vector aB(1, 3);
  aB(1) = 5.0;
  aB(2) = 7.0;
  aB(3) = 9.0;

  math_Vector aX(1, 3);
  aSVD.Solve(aB, aX);

  EXPECT_NEAR(aX(1), aB(1), Precision::Confusion()) << "Identity matrix solution X(1)";
  EXPECT_NEAR(aX(2), aB(2), Precision::Confusion()) << "Identity matrix solution X(2)";
  EXPECT_NEAR(aX(3), aB(3), Precision::Confusion()) << "Identity matrix solution X(3)";
}

TEST(MathSVDTest, DiagonalMatrix)
{

  math_Matrix aDiagonal(1, 3, 1, 3);
  aDiagonal(1, 1) = 3.0;
  aDiagonal(1, 2) = 0.0;
  aDiagonal(1, 3) = 0.0;
  aDiagonal(2, 1) = 0.0;
  aDiagonal(2, 2) = 5.0;
  aDiagonal(2, 3) = 0.0;
  aDiagonal(3, 1) = 0.0;
  aDiagonal(3, 2) = 0.0;
  aDiagonal(3, 3) = 2.0;

  math_SVD aSVD(aDiagonal);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should succeed for diagonal matrix";

  math_Vector aB(1, 3);
  aB(1) = 12.0;
  aB(2) = 20.0;
  aB(3) = 8.0;

  math_Vector aX(1, 3);
  aSVD.Solve(aB, aX);

  EXPECT_NEAR(aX(1), 4.0, Precision::Confusion()) << "Diagonal solution X(1) = 12/3";
  EXPECT_NEAR(aX(2), 4.0, Precision::Confusion()) << "Diagonal solution X(2) = 20/5";
  EXPECT_NEAR(aX(3), 4.0, Precision::Confusion()) << "Diagonal solution X(3) = 8/2";
}

TEST(MathSVDTest, OverdeterminedSystem)
{

  math_Matrix aMatrix(1, 4, 1, 3);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 0.0;
  aMatrix(1, 3) = 0.0;
  aMatrix(2, 1) = 0.0;
  aMatrix(2, 2) = 1.0;
  aMatrix(2, 3) = 0.0;
  aMatrix(3, 1) = 0.0;
  aMatrix(3, 2) = 0.0;
  aMatrix(3, 3) = 1.0;
  aMatrix(4, 1) = 1.0;
  aMatrix(4, 2) = 1.0;
  aMatrix(4, 3) = 1.0;

  math_SVD aSVD(aMatrix);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should succeed for overdetermined system";

  math_Vector aB(1, 4);
  aB(1) = 2.0;
  aB(2) = 3.0;
  aB(3) = 4.0;
  aB(4) = 9.0;

  math_Vector aX(1, 3);
  aSVD.Solve(aB, aX);

  checkSolution(aMatrix, aX, aB, 1.0e-8);
}

TEST(MathSVDTest, UnderdeterminedSystem)
{

  math_Matrix aMatrix(1, 2, 1, 3);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 2.0;
  aMatrix(1, 3) = 3.0;
  aMatrix(2, 1) = 4.0;
  aMatrix(2, 2) = 5.0;
  aMatrix(2, 3) = 6.0;

  math_SVD aSVD(aMatrix);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should succeed for underdetermined system";

  math_Vector aB(1, 2);
  aB(1) = 14.0;
  aB(2) = 32.0;

  math_Vector aX(1, 3);
  aSVD.Solve(aB, aX);

  checkSolution(aMatrix, aX, aB, 1.0e-8);
}

TEST(MathSVDTest, RankDeficientMatrix)
{

  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 2.0;
  aMatrix(1, 3) = 3.0;
  aMatrix(2, 1) = 2.0;
  aMatrix(2, 2) = 4.0;
  aMatrix(2, 3) = 6.0;
  aMatrix(3, 1) = 1.0;
  aMatrix(3, 2) = 1.0;
  aMatrix(3, 3) = 1.0;

  math_SVD aSVD(aMatrix);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should handle rank deficient matrix";

  math_Vector aB(1, 3);
  aB(1) = 6.0;
  aB(2) = 12.0;
  aB(3) = 3.0;

  math_Vector aX(1, 3);
  aSVD.Solve(aB, aX);

  checkSolution(aMatrix, aX, aB, 1.0e-6);
}

TEST(MathSVDTest, SingleRowMatrix)
{

  math_Matrix aMatrix(1, 1, 1, 3);
  aMatrix(1, 1) = 2.0;
  aMatrix(1, 2) = 3.0;
  aMatrix(1, 3) = 4.0;

  math_SVD aSVD(aMatrix);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should succeed for single row matrix";

  math_Vector aB(1, 1);
  aB(1) = 20.0;

  math_Vector aX(1, 3);
  aSVD.Solve(aB, aX);

  checkSolution(aMatrix, aX, aB);
}

TEST(MathSVDTest, SingleColumnMatrix)
{

  math_Matrix aMatrix(1, 3, 1, 1);
  aMatrix(1, 1) = 2.0;
  aMatrix(2, 1) = 3.0;
  aMatrix(3, 1) = 4.0;

  math_SVD aSVD(aMatrix);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should succeed for single column matrix";

  math_Vector aB(1, 3);
  aB(1) = 4.0;
  aB(2) = 6.0;
  aB(3) = 8.0;

  math_Vector aX(1, 1);
  aSVD.Solve(aB, aX);

  EXPECT_NEAR(aX(1), 2.0, 1.0e-10) << "Least squares solution should be approximately 2.0";
}

TEST(MathSVDTest, PseudoInverseMethod)
{
  math_Matrix aMatrix = createWellConditionedMatrix();
  math_SVD    aSVD(aMatrix);

  EXPECT_TRUE(aSVD.IsDone()) << "SVD decomposition should succeed";

  math_Matrix aPseudoInv(aMatrix.LowerCol(),
                         aMatrix.UpperCol(),
                         aMatrix.LowerRow(),
                         aMatrix.UpperRow());
  aSVD.PseudoInverse(aPseudoInv);

  math_Matrix aProduct(aMatrix.LowerRow(),
                       aMatrix.UpperRow(),
                       aMatrix.LowerRow(),
                       aMatrix.UpperRow());

  for (int anI = aMatrix.LowerRow(); anI <= aMatrix.UpperRow(); anI++)
  {
    for (int aJ = aMatrix.LowerRow(); aJ <= aMatrix.UpperRow(); aJ++)
    {
      double aSum = 0.0;
      for (int aK = aMatrix.LowerCol(); aK <= aMatrix.UpperCol(); aK++)
      {
        aSum += aPseudoInv(anI, aK) * aMatrix(aK, aJ);
      }
      aProduct(anI, aJ) = aSum;
    }
  }

  for (int anI = aMatrix.LowerRow(); anI <= aMatrix.UpperRow(); anI++)
  {
    for (int aJ = aMatrix.LowerRow(); aJ <= aMatrix.UpperRow(); aJ++)
    {
      double anExpected = (anI == aJ) ? 1.0 : 0.0;
      EXPECT_NEAR(aProduct(anI, aJ), anExpected, 1.0e-10)
        << "PseudoInverse * Matrix should approximate identity at (" << anI << "," << aJ << ")";
    }
  }
}

TEST(MathSVDTest, DimensionCompatibility)
{
  math_Matrix aMatrix = createWellConditionedMatrix();
  math_SVD    aSVD(aMatrix);

  ASSERT_TRUE(aSVD.IsDone()) << "SVD should succeed for dimension compatibility tests";

  math_Vector aCorrectB(1, 3);
  aCorrectB(1) = 1.0;
  aCorrectB(2) = 2.0;
  aCorrectB(3) = 3.0;

  math_Vector aX(1, 3);
  aSVD.Solve(aCorrectB, aX);

  EXPECT_EQ(aX.Length(), 3) << "Solution vector should have correct dimension";
  EXPECT_EQ(aCorrectB.Length(), 3) << "RHS vector should have correct dimension";

  EXPECT_EQ(aMatrix.RowNumber(), 3) << "Matrix should have 3 rows";
  EXPECT_EQ(aMatrix.ColNumber(), 3) << "Matrix should have 3 columns";
}

TEST(MathSVDTest, SingularValues)
{

  math_Matrix aMatrix(1, 2, 1, 2);
  aMatrix(1, 1) = 3.0;
  aMatrix(1, 2) = 0.0;
  aMatrix(2, 1) = 0.0;
  aMatrix(2, 2) = 4.0;

  math_SVD aSVD(aMatrix);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should succeed for diagonal matrix";

  math_Vector aB1(1, 2);
  aB1(1) = 6.0;
  aB1(2) = 0.0;
  math_Vector aX1(1, 2);
  aSVD.Solve(aB1, aX1);
  EXPECT_NEAR(aX1(1), 2.0, 1.0e-10) << "Solution should be 6/3 = 2";
  EXPECT_NEAR(aX1(2), 0.0, 1.0e-10) << "Solution should be 0/4 = 0";

  math_Vector aB2(1, 2);
  aB2(1) = 0.0;
  aB2(2) = 12.0;
  math_Vector aX2(1, 2);
  aSVD.Solve(aB2, aX2);
  EXPECT_NEAR(aX2(1), 0.0, 1.0e-10) << "Solution should be 0/3 = 0";
  EXPECT_NEAR(aX2(2), 3.0, 1.0e-10) << "Solution should be 12/4 = 3";
}

TEST(MathSVDTest, DifferentMatrixBounds)
{

  math_Matrix aMatrix(2, 4, 3, 5);

  aMatrix(2, 3) = 1.0;
  aMatrix(2, 4) = 0.0;
  aMatrix(2, 5) = 0.0;
  aMatrix(3, 3) = 0.0;
  aMatrix(3, 4) = 1.0;
  aMatrix(3, 5) = 0.0;
  aMatrix(4, 3) = 0.0;
  aMatrix(4, 4) = 0.0;
  aMatrix(4, 5) = 1.0;

  math_SVD aSVD(aMatrix);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should succeed for custom bounds matrix";

  math_Vector aB(2, 4);
  aB(2) = 5.0;
  aB(3) = 7.0;
  aB(4) = 9.0;

  math_Vector aX(3, 5);
  aSVD.Solve(aB, aX);

  EXPECT_NEAR(aX(3), 5.0, Precision::Confusion()) << "Custom bounds solution X(3)";
  EXPECT_NEAR(aX(4), 7.0, Precision::Confusion()) << "Custom bounds solution X(4)";
  EXPECT_NEAR(aX(5), 9.0, Precision::Confusion()) << "Custom bounds solution X(5)";
}

TEST(MathSVDTest, LargerMatrix)
{

  math_Matrix aMatrix(1, 5, 1, 5);

  for (int anI = 1; anI <= 5; anI++)
  {
    for (int aJ = 1; aJ <= 5; aJ++)
    {
      if (anI == aJ)
        aMatrix(anI, aJ) = 10.0;
      else
        aMatrix(anI, aJ) = 1.0 / (abs(anI - aJ) + 1.0);
    }
  }

  math_SVD aSVD(aMatrix);
  EXPECT_TRUE(aSVD.IsDone()) << "SVD should succeed for larger matrix";

  math_Vector aB(1, 5);
  for (int anI = 1; anI <= 5; anI++)
  {
    aB(anI) = double(anI) * 2.0;
  }

  math_Vector aX(1, 5);
  aSVD.Solve(aB, aX);

  checkSolution(aMatrix, aX, aB, 1.0e-8);
}
