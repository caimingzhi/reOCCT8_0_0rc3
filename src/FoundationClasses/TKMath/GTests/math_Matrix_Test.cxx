

#include <math_Matrix.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <math_Vector.hpp>
#include <Precision.hpp>

namespace
{

  void checkMatricesEqual(const math_Matrix& theM1,
                          const math_Matrix& theM2,
                          const double       theTolerance = Precision::Confusion())
  {
    ASSERT_EQ(theM1.RowNumber(), theM2.RowNumber());
    ASSERT_EQ(theM1.ColNumber(), theM2.ColNumber());
    ASSERT_EQ(theM1.LowerRow(), theM2.LowerRow());
    ASSERT_EQ(theM1.LowerCol(), theM2.LowerCol());

    for (int anI = theM1.LowerRow(); anI <= theM1.UpperRow(); anI++)
    {
      for (int aJ = theM1.LowerCol(); aJ <= theM1.UpperCol(); aJ++)
      {
        EXPECT_NEAR(theM1(anI, aJ), theM2(anI, aJ), theTolerance);
      }
    }
  }
} // namespace

TEST(MathMatrixTest, Constructors)
{

  math_Matrix aMatrix1(1, 3, 1, 4);
  EXPECT_EQ(aMatrix1.RowNumber(), 3);
  EXPECT_EQ(aMatrix1.ColNumber(), 4);
  EXPECT_EQ(aMatrix1.LowerRow(), 1);
  EXPECT_EQ(aMatrix1.UpperRow(), 3);
  EXPECT_EQ(aMatrix1.LowerCol(), 1);
  EXPECT_EQ(aMatrix1.UpperCol(), 4);

  math_Matrix aMatrix2(2, 4, 3, 5, 2.5);
  EXPECT_EQ(aMatrix2.RowNumber(), 3);
  EXPECT_EQ(aMatrix2.ColNumber(), 3);

  for (int anI = 2; anI <= 4; anI++)
  {
    for (int aJ = 3; aJ <= 5; aJ++)
    {
      EXPECT_EQ(aMatrix2(anI, aJ), 2.5);
    }
  }

  math_Matrix aMatrix3(aMatrix2);
  checkMatricesEqual(aMatrix2, aMatrix3);
}

TEST(MathMatrixTest, InitAndAccess)
{
  math_Matrix aMatrix(1, 3, 1, 3);

  aMatrix.Init(5.0);

  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      EXPECT_EQ(aMatrix(anI, aJ), 5.0);
    }
  }

  aMatrix(2, 2) = 10.0;
  EXPECT_EQ(aMatrix(2, 2), 10.0);

  aMatrix.Value(3, 3) = 15.0;
  EXPECT_EQ(aMatrix(3, 3), 15.0);
}

TEST(MathMatrixTest, MatrixOperations)
{
  math_Matrix aMatrix1(1, 3, 1, 3);
  math_Matrix aMatrix2(1, 3, 1, 3);

  aMatrix1.Init(2.0);
  aMatrix2.Init(3.0);

  math_Matrix anAddResult = aMatrix1.Added(aMatrix2);
  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      EXPECT_EQ(anAddResult(anI, aJ), 5.0);
    }
  }

  math_Matrix aSubResult = aMatrix1.Subtracted(aMatrix2);
  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      EXPECT_EQ(aSubResult(anI, aJ), -1.0);
    }
  }

  math_Matrix aMulResult = aMatrix1.Multiplied(2.5);
  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      EXPECT_EQ(aMulResult(anI, aJ), 5.0);
    }
  }

  math_Matrix aDivResult = aMatrix1.Divided(0.5);
  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      EXPECT_EQ(aDivResult(anI, aJ), 4.0);
    }
  }

  math_Matrix aInPlaceMul(1, 3, 1, 3);
  aInPlaceMul.Init(3.0);
  aInPlaceMul.Multiply(2.0);

  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      EXPECT_EQ(aInPlaceMul(anI, aJ), 6.0);
    }
  }

  math_Matrix aInPlaceOp(1, 3, 1, 3);
  aInPlaceOp.Init(2.0);
  aInPlaceOp *= 3.0;

  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      EXPECT_EQ(aInPlaceOp(anI, aJ), 6.0);
    }
  }
}

TEST(MathMatrixTest, MatrixMultiplication)
{

  math_Matrix anIdentity(1, 3, 1, 3);
  anIdentity.Init(0.0);
  anIdentity(1, 1) = 1.0;
  anIdentity(2, 2) = 1.0;
  anIdentity(3, 3) = 1.0;

  math_Matrix aMatrix(1, 3, 1, 3);
  for (int anI = 1; anI <= 3; anI++)
  {
    for (int aJ = 1; aJ <= 3; aJ++)
    {
      aMatrix(anI, aJ) = anI + aJ;
    }
  }

  math_Matrix aResult = aMatrix.Multiplied(anIdentity);
  checkMatricesEqual(aResult, aMatrix);

  math_Matrix aMatA(1, 2, 1, 3);
  math_Matrix aMatB(1, 3, 1, 2);

  aMatA(1, 1) = 1.0;
  aMatA(1, 2) = 2.0;
  aMatA(1, 3) = 3.0;
  aMatA(2, 1) = 4.0;
  aMatA(2, 2) = 5.0;
  aMatA(2, 3) = 6.0;

  aMatB(1, 1) = 7.0;
  aMatB(1, 2) = 8.0;
  aMatB(2, 1) = 9.0;
  aMatB(2, 2) = 10.0;
  aMatB(3, 1) = 11.0;
  aMatB(3, 2) = 12.0;

  math_Matrix aMatC = aMatA.Multiplied(aMatB);

  EXPECT_EQ(aMatC(1, 1), 1 * 7 + 2 * 9 + 3 * 11);
  EXPECT_EQ(aMatC(1, 2), 1 * 8 + 2 * 10 + 3 * 12);
  EXPECT_EQ(aMatC(2, 1), 4 * 7 + 5 * 9 + 6 * 11);
  EXPECT_EQ(aMatC(2, 2), 4 * 8 + 5 * 10 + 6 * 12);

  math_Matrix aInPlaceMulMat1(1, 2, 1, 2);
  math_Matrix aInPlaceMulMat2(1, 2, 1, 2);

  aInPlaceMulMat1(1, 1) = 1.0;
  aInPlaceMulMat1(1, 2) = 2.0;
  aInPlaceMulMat1(2, 1) = 3.0;
  aInPlaceMulMat1(2, 2) = 4.0;

  aInPlaceMulMat2(1, 1) = 2.0;
  aInPlaceMulMat2(1, 2) = 0.0;
  aInPlaceMulMat2(2, 1) = 1.0;
  aInPlaceMulMat2(2, 2) = 3.0;

  math_Matrix aOrigMat(aInPlaceMulMat1);

  aInPlaceMulMat1.Multiply(aInPlaceMulMat2);

  EXPECT_EQ(aInPlaceMulMat1(1, 1), 1 * 2 + 2 * 1);
  EXPECT_EQ(aInPlaceMulMat1(1, 2), 1 * 0 + 2 * 3);
  EXPECT_EQ(aInPlaceMulMat1(2, 1), 3 * 2 + 4 * 1);
  EXPECT_EQ(aInPlaceMulMat1(2, 2), 3 * 0 + 4 * 3);

  math_Matrix aInPlaceOpMat(aOrigMat);
  aInPlaceOpMat *= aInPlaceMulMat2;

  EXPECT_EQ(aInPlaceOpMat(1, 1), 4);
  EXPECT_EQ(aInPlaceOpMat(1, 2), 6);
  EXPECT_EQ(aInPlaceOpMat(2, 1), 10);
  EXPECT_EQ(aInPlaceOpMat(2, 2), 12);
}

TEST(MathMatrixTest, TransposeAndInverse)
{

  math_Matrix aMatrix(1, 2, 1, 3);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 2.0;
  aMatrix(1, 3) = 3.0;
  aMatrix(2, 1) = 4.0;
  aMatrix(2, 2) = 5.0;
  aMatrix(2, 3) = 6.0;

  math_Matrix aTransposed = aMatrix.Transposed();

  EXPECT_EQ(aTransposed.RowNumber(), aMatrix.ColNumber());
  EXPECT_EQ(aTransposed.ColNumber(), aMatrix.RowNumber());
  EXPECT_EQ(aTransposed(1, 1), aMatrix(1, 1));
  EXPECT_EQ(aTransposed(2, 1), aMatrix(1, 2));
  EXPECT_EQ(aTransposed(3, 1), aMatrix(1, 3));
  EXPECT_EQ(aTransposed(1, 2), aMatrix(2, 1));
  EXPECT_EQ(aTransposed(2, 2), aMatrix(2, 2));
  EXPECT_EQ(aTransposed(3, 2), aMatrix(2, 3));

  math_Matrix anInvertible(1, 3, 1, 3);
  anInvertible(1, 1) = 1.0;
  anInvertible(1, 2) = 0.0;
  anInvertible(1, 3) = 0.0;
  anInvertible(2, 1) = 0.0;
  anInvertible(2, 2) = 2.0;
  anInvertible(2, 3) = 0.0;
  anInvertible(3, 1) = 0.0;
  anInvertible(3, 2) = 0.0;
  anInvertible(3, 3) = 4.0;

  math_Matrix anInverse = anInvertible.Inverse();

  EXPECT_EQ(anInverse(1, 1), 1.0);
  EXPECT_EQ(anInverse(2, 2), 0.5);
  EXPECT_EQ(anInverse(3, 3), 0.25);

  math_Matrix anIdentity = anInvertible.Multiplied(anInverse);

  EXPECT_NEAR(anIdentity(1, 1), 1.0, Precision::Confusion());
  EXPECT_NEAR(anIdentity(2, 2), 1.0, Precision::Confusion());
  EXPECT_NEAR(anIdentity(3, 3), 1.0, Precision::Confusion());
  EXPECT_NEAR(anIdentity(1, 2), 0.0, Precision::Confusion());
  EXPECT_NEAR(anIdentity(1, 3), 0.0, Precision::Confusion());
  EXPECT_NEAR(anIdentity(2, 1), 0.0, Precision::Confusion());
  EXPECT_NEAR(anIdentity(2, 3), 0.0, Precision::Confusion());
  EXPECT_NEAR(anIdentity(3, 1), 0.0, Precision::Confusion());
  EXPECT_NEAR(anIdentity(3, 2), 0.0, Precision::Confusion());
}

TEST(MathMatrixTest, Determinant)
{

  math_Matrix anIdentity(1, 3, 1, 3);
  anIdentity.Init(0.0);
  anIdentity(1, 1) = 1.0;
  anIdentity(2, 2) = 1.0;
  anIdentity(3, 3) = 1.0;

  EXPECT_NEAR(anIdentity.Determinant(), 1.0, Precision::Confusion());

  math_Matrix aDiagonal(1, 3, 1, 3);
  aDiagonal.Init(0.0);
  aDiagonal(1, 1) = 2.0;
  aDiagonal(2, 2) = 3.0;
  aDiagonal(3, 3) = 4.0;

  EXPECT_NEAR(aDiagonal.Determinant(), 24.0, Precision::Confusion());

  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix(1, 1) = 3.0;
  aMatrix(1, 2) = 8.0;
  aMatrix(1, 3) = 5.0;
  aMatrix(2, 1) = 6.0;
  aMatrix(2, 2) = 2.0;
  aMatrix(2, 3) = 7.0;
  aMatrix(3, 1) = 4.0;
  aMatrix(3, 2) = 1.0;
  aMatrix(3, 3) = 9.0;

  EXPECT_NEAR(aMatrix.Determinant(), -185.0, Precision::Confusion());
}

TEST(MathMatrixTest, RowAndColumnOperations)
{
  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix.Init(0.0);

  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 2.0;
  aMatrix(1, 3) = 3.0;
  aMatrix(2, 1) = 4.0;
  aMatrix(2, 2) = 5.0;
  aMatrix(2, 3) = 6.0;
  aMatrix(3, 1) = 7.0;
  aMatrix(3, 2) = 8.0;
  aMatrix(3, 3) = 9.0;

  math_Vector aRow = aMatrix.Row(2);
  EXPECT_EQ(aRow.Length(), 3);
  EXPECT_EQ(aRow(1), 4.0);
  EXPECT_EQ(aRow(2), 5.0);
  EXPECT_EQ(aRow(3), 6.0);

  math_Vector aCol = aMatrix.Col(3);
  EXPECT_EQ(aCol.Length(), 3);
  EXPECT_EQ(aCol(1), 3.0);
  EXPECT_EQ(aCol(2), 6.0);
  EXPECT_EQ(aCol(3), 9.0);

  math_Vector aNewRow(1, 3);
  aNewRow(1) = 10.0;
  aNewRow(2) = 11.0;
  aNewRow(3) = 12.0;
  aMatrix.SetRow(2, aNewRow);

  EXPECT_EQ(aMatrix(2, 1), 10.0);
  EXPECT_EQ(aMatrix(2, 2), 11.0);
  EXPECT_EQ(aMatrix(2, 3), 12.0);

  math_Vector aNewCol(1, 3);
  aNewCol(1) = 13.0;
  aNewCol(2) = 14.0;
  aNewCol(3) = 15.0;
  aMatrix.SetCol(1, aNewCol);

  EXPECT_EQ(aMatrix(1, 1), 13.0);
  EXPECT_EQ(aMatrix(2, 1), 14.0);
  EXPECT_EQ(aMatrix(3, 1), 15.0);

  aMatrix.SwapRow(1, 3);
  EXPECT_EQ(aMatrix(1, 1), 15.0);
  EXPECT_EQ(aMatrix(1, 2), 8.0);
  EXPECT_EQ(aMatrix(1, 3), 9.0);
  EXPECT_EQ(aMatrix(3, 1), 13.0);
  EXPECT_EQ(aMatrix(3, 2), 2.0);
  EXPECT_EQ(aMatrix(3, 3), 3.0);

  aMatrix.SwapCol(2, 3);
  EXPECT_EQ(aMatrix(1, 2), 9.0);
  EXPECT_EQ(aMatrix(1, 3), 8.0);
  EXPECT_EQ(aMatrix(2, 2), 12.0);
  EXPECT_EQ(aMatrix(2, 3), 11.0);
  EXPECT_EQ(aMatrix(3, 2), 3.0);
  EXPECT_EQ(aMatrix(3, 3), 2.0);
}

TEST(MathMatrixTest, SetDiag)
{
  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix.Init(0.0);

  aMatrix.SetDiag(5.0);

  EXPECT_EQ(aMatrix(1, 1), 5.0);
  EXPECT_EQ(aMatrix(2, 2), 5.0);
  EXPECT_EQ(aMatrix(3, 3), 5.0);

  EXPECT_EQ(aMatrix(1, 2), 0.0);
  EXPECT_EQ(aMatrix(1, 3), 0.0);
  EXPECT_EQ(aMatrix(2, 1), 0.0);
  EXPECT_EQ(aMatrix(2, 3), 0.0);
  EXPECT_EQ(aMatrix(3, 1), 0.0);
  EXPECT_EQ(aMatrix(3, 2), 0.0);
}

TEST(MathMatrixTest, VectorMatrixOperations)
{

  math_Matrix aMatrix(1, 3, 1, 3);
  aMatrix(1, 1) = 1;
  aMatrix(1, 2) = 2;
  aMatrix(1, 3) = 3;
  aMatrix(2, 1) = 4;
  aMatrix(2, 2) = 5;
  aMatrix(2, 3) = 6;
  aMatrix(3, 1) = 7;
  aMatrix(3, 2) = 8;
  aMatrix(3, 3) = 9;

  math_Vector aVector(1, 3);
  aVector(1) = 2;
  aVector(2) = 3;
  aVector(3) = 4;

  math_Vector aResult = aMatrix * aVector;

  EXPECT_EQ(aResult.Length(), 3);

  EXPECT_EQ(aResult(1), 20);

  EXPECT_EQ(aResult(2), 47);

  EXPECT_EQ(aResult(3), 74);

  math_Vector aVec1(1, 2), aVec2(1, 3);
  aVec1(1) = 1;
  aVec1(2) = 2;
  aVec2(1) = 3;
  aVec2(2) = 4;
  aVec2(3) = 5;

  math_Matrix aMat(1, 2, 1, 3);
  aMat.Multiply(aVec1, aVec2);

  EXPECT_EQ(aMat(1, 1), 1 * 3);
  EXPECT_EQ(aMat(1, 2), 1 * 4);
  EXPECT_EQ(aMat(1, 3), 1 * 5);
  EXPECT_EQ(aMat(2, 1), 2 * 3);
  EXPECT_EQ(aMat(2, 2), 2 * 4);
  EXPECT_EQ(aMat(2, 3), 2 * 5);
}

TEST(MathMatrixTest, InPlaceMatrixMultiplication)
{

  math_Matrix aMatrix(1, 2, 1, 2);
  aMatrix(1, 1) = 1.0;
  aMatrix(1, 2) = 2.0;
  aMatrix(2, 1) = 3.0;
  aMatrix(2, 2) = 4.0;

  math_Matrix aMatrixCopy(aMatrix);

  math_Matrix aExpectedResult(1, 2, 1, 2);
  aExpectedResult(1, 1) = 7.0;
  aExpectedResult(1, 2) = 10.0;
  aExpectedResult(2, 1) = 15.0;
  aExpectedResult(2, 2) = 22.0;

  math_Matrix aCorrectResult = aMatrixCopy.Multiplied(aMatrixCopy);

  EXPECT_EQ(aCorrectResult(1, 1), 7.0);
  EXPECT_EQ(aCorrectResult(1, 2), 10.0);
  EXPECT_EQ(aCorrectResult(2, 1), 15.0);
  EXPECT_EQ(aCorrectResult(2, 2), 22.0);

  aMatrix.Multiply(aMatrix);

  EXPECT_NEAR(aMatrix(1, 1), aCorrectResult(1, 1), Precision::Confusion());
  EXPECT_NEAR(aMatrix(1, 2), aCorrectResult(1, 2), Precision::Confusion());
  EXPECT_NEAR(aMatrix(2, 1), aCorrectResult(2, 1), Precision::Confusion());
  EXPECT_NEAR(aMatrix(2, 2), aCorrectResult(2, 2), Precision::Confusion());

  aMatrixCopy *= aMatrixCopy;

  EXPECT_NEAR(aMatrixCopy(1, 1), aCorrectResult(1, 1), Precision::Confusion());
  EXPECT_NEAR(aMatrixCopy(1, 2), aCorrectResult(1, 2), Precision::Confusion());
  EXPECT_NEAR(aMatrixCopy(2, 1), aCorrectResult(2, 1), Precision::Confusion());
  EXPECT_NEAR(aMatrixCopy(2, 2), aCorrectResult(2, 2), Precision::Confusion());

  math_Matrix aMatrixA(1, 2, 1, 2);
  aMatrixA(1, 1) = 1.0;
  aMatrixA(1, 2) = 2.0;
  aMatrixA(2, 1) = 3.0;
  aMatrixA(2, 2) = 4.0;

  math_Matrix aMatrixB(1, 2, 1, 2);
  aMatrixB(1, 1) = 5.0;
  aMatrixB(1, 2) = 6.0;
  aMatrixB(2, 1) = 7.0;
  aMatrixB(2, 2) = 8.0;

  math_Matrix aMatrixACopy(aMatrixA);
  math_Matrix aMatrixBCopy(aMatrixB);

  math_Matrix aExpectedAB = aMatrixACopy.Multiplied(aMatrixBCopy);

  EXPECT_EQ(aExpectedAB(1, 1), 19.0);
  EXPECT_EQ(aExpectedAB(1, 2), 22.0);
  EXPECT_EQ(aExpectedAB(2, 1), 43.0);
  EXPECT_EQ(aExpectedAB(2, 2), 50.0);

  aMatrixA.Multiply(aMatrixB);

  EXPECT_NEAR(aMatrixA(1, 1), aExpectedAB(1, 1), Precision::Confusion());
  EXPECT_NEAR(aMatrixA(1, 2), aExpectedAB(1, 2), Precision::Confusion());
  EXPECT_NEAR(aMatrixA(2, 1), aExpectedAB(2, 1), Precision::Confusion());
  EXPECT_NEAR(aMatrixA(2, 2), aExpectedAB(2, 2), Precision::Confusion());

  aMatrixACopy *= aMatrixBCopy;

  EXPECT_NEAR(aMatrixACopy(1, 1), aExpectedAB(1, 1), Precision::Confusion());
  EXPECT_NEAR(aMatrixACopy(1, 2), aExpectedAB(1, 2), Precision::Confusion());
  EXPECT_NEAR(aMatrixACopy(2, 1), aExpectedAB(2, 1), Precision::Confusion());
  EXPECT_NEAR(aMatrixACopy(2, 2), aExpectedAB(2, 2), Precision::Confusion());
}

TEST(MathMatrixTest, MoveSemantics)
{

  int         aRows = 10;
  int         aCols = 10;
  math_Matrix aMat1(1, aRows, 1, aCols);
  aMat1.Init(1.0);
  aMat1(1, 1) = 2.0;

  math_Matrix aMat2(std::move(aMat1));

  EXPECT_EQ(aMat2.RowNumber(), aRows);
  EXPECT_EQ(aMat2.ColNumber(), aCols);
  EXPECT_EQ(aMat2(1, 1), 2.0);

  EXPECT_EQ(aMat1.RowNumber(), 0);

  int         aSmallRows = 4;
  int         aSmallCols = 4;
  math_Matrix aSmallMat1(1, aSmallRows, 1, aSmallCols);
  aSmallMat1.Init(1.0);

  math_Matrix aSmallMat2(std::move(aSmallMat1));

  EXPECT_EQ(aSmallMat2.RowNumber(), aSmallRows);
  EXPECT_EQ(aSmallMat2(1, 1), 1.0);

  EXPECT_EQ(aSmallMat1.RowNumber(), aSmallRows);
  EXPECT_EQ(aSmallMat1(1, 1), 1.0);

  math_Matrix aMatAssign1(1, aRows, 1, aCols);
  aMatAssign1.Init(5.0);

  math_Matrix aMatAssign2(1, aRows, 1, aCols);
  aMatAssign2.Init(0.0);

  aMatAssign2 = std::move(aMatAssign1);

  EXPECT_EQ(aMatAssign2(1, 1), 5.0);
  EXPECT_EQ(aMatAssign1.RowNumber(), 0);
}
