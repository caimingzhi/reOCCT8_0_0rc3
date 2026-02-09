

#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <Standard_DimensionError.hpp>
#include <Standard_RangeError.hpp>
#include <Standard_DivideByZero.hpp>
#include <Standard_NullValue.hpp>
#include <Precision.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>

namespace
{

  void checkVectorsEqual(const math_Vector& theV1,
                         const math_Vector& theV2,
                         const double       theTolerance = Precision::Confusion())
  {
    ASSERT_EQ(theV1.Length(), theV2.Length());
    ASSERT_EQ(theV1.Lower(), theV2.Lower());
    ASSERT_EQ(theV1.Upper(), theV2.Upper());

    for (int anI = theV1.Lower(); anI <= theV1.Upper(); anI++)
    {
      EXPECT_NEAR(theV1(anI), theV2(anI), theTolerance);
    }
  }
} // namespace

TEST(MathVectorTest, Constructors)
{

  math_Vector aVec1(1, 5);
  EXPECT_EQ(aVec1.Length(), 5);
  EXPECT_EQ(aVec1.Lower(), 1);
  EXPECT_EQ(aVec1.Upper(), 5);

  math_Vector aVec2(-2, 3, 2.5);
  EXPECT_EQ(aVec2.Length(), 6);
  EXPECT_EQ(aVec2.Lower(), -2);
  EXPECT_EQ(aVec2.Upper(), 3);

  for (int anI = -2; anI <= 3; anI++)
  {
    EXPECT_EQ(aVec2(anI), 2.5);
  }

  double      anArray[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  math_Vector aVec3(anArray, 0, 4);
  EXPECT_EQ(aVec3.Length(), 5);
  EXPECT_EQ(aVec3.Lower(), 0);
  EXPECT_EQ(aVec3.Upper(), 4);

  for (int anI = 0; anI <= 4; anI++)
  {
    EXPECT_EQ(aVec3(anI), anArray[anI]);
  }

  math_Vector aVec4(aVec2);
  checkVectorsEqual(aVec2, aVec4);
}

TEST(MathVectorTest, GeometryConstructors)
{

  gp_XY       anXY(3.5, 4.5);
  math_Vector aVecXY(anXY);
  EXPECT_EQ(aVecXY.Length(), 2);
  EXPECT_EQ(aVecXY.Lower(), 1);
  EXPECT_EQ(aVecXY.Upper(), 2);
  EXPECT_DOUBLE_EQ(aVecXY(1), 3.5);
  EXPECT_DOUBLE_EQ(aVecXY(2), 4.5);

  gp_XYZ      anXYZ(1.1, 2.2, 3.3);
  math_Vector aVecXYZ(anXYZ);
  EXPECT_EQ(aVecXYZ.Length(), 3);
  EXPECT_EQ(aVecXYZ.Lower(), 1);
  EXPECT_EQ(aVecXYZ.Upper(), 3);
  EXPECT_DOUBLE_EQ(aVecXYZ(1), 1.1);
  EXPECT_DOUBLE_EQ(aVecXYZ(2), 2.2);
  EXPECT_DOUBLE_EQ(aVecXYZ(3), 3.3);
}

TEST(MathVectorTest, InitAndAccess)
{
  math_Vector aVec(1, 4);

  aVec.Init(7.0);
  for (int anI = 1; anI <= 4; anI++)
  {
    EXPECT_EQ(aVec(anI), 7.0);
  }

  aVec(2) = 15.0;
  EXPECT_EQ(aVec(2), 15.0);

  aVec.Value(3) = 25.0;
  EXPECT_EQ(aVec(3), 25.0);
  EXPECT_EQ(aVec.Value(3), 25.0);
}

TEST(MathVectorTest, VectorProperties)
{
  math_Vector aVec(1, 4);
  aVec(1) = 3.0;
  aVec(2) = 4.0;
  aVec(3) = 0.0;
  aVec(4) = -2.0;

  double anExpectedNorm = std::sqrt(29.0);
  EXPECT_NEAR(aVec.Norm(), anExpectedNorm, Precision::Confusion());

  EXPECT_NEAR(aVec.Norm2(), 29.0, Precision::Confusion());

  EXPECT_EQ(aVec.Max(), 2);

  EXPECT_EQ(aVec.Min(), 4);
}

TEST(MathVectorTest, Normalization)
{
  math_Vector aVec(1, 3);
  aVec(1) = 3.0;
  aVec(2) = 4.0;
  aVec(3) = 0.0;

  double anOriginalNorm = aVec.Norm();
  EXPECT_NEAR(anOriginalNorm, 5.0, Precision::Confusion());

  math_Vector aNormalizedVec = aVec.Normalized();
  EXPECT_NEAR(aNormalizedVec.Norm(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aNormalizedVec(1), 3.0 / 5.0, Precision::Confusion());
  EXPECT_NEAR(aNormalizedVec(2), 4.0 / 5.0, Precision::Confusion());
  EXPECT_NEAR(aNormalizedVec(3), 0.0, Precision::Confusion());

  EXPECT_NEAR(aVec.Norm(), 5.0, Precision::Confusion());

  aVec.Normalize();
  EXPECT_NEAR(aVec.Norm(), 1.0, Precision::Confusion());
  checkVectorsEqual(aVec, aNormalizedVec);
}

TEST(MathVectorTest, ZeroVectorHandling)
{
  math_Vector aZeroVec(1, 3, 0.0);

  EXPECT_DOUBLE_EQ(aZeroVec.Norm(), 0.0) << "Zero vector should have zero norm";

  math_Vector aNonZeroVec(1, 3);
  aNonZeroVec(1) = 1.0;
  aNonZeroVec(2) = 0.0;
  aNonZeroVec(3) = 0.0;

  EXPECT_DOUBLE_EQ(aNonZeroVec.Norm(), 1.0) << "Unit vector should have norm 1";
  aNonZeroVec.Normalize();
  EXPECT_DOUBLE_EQ(aNonZeroVec.Norm(), 1.0) << "Normalized vector should have norm 1";
}

TEST(MathVectorTest, Inversion)
{
  math_Vector aVec(1, 5);
  aVec(1) = 1.0;
  aVec(2) = 2.0;
  aVec(3) = 3.0;
  aVec(4) = 4.0;
  aVec(5) = 5.0;

  math_Vector anInverseVec = aVec.Inverse();
  EXPECT_EQ(anInverseVec(1), 5.0);
  EXPECT_EQ(anInverseVec(2), 4.0);
  EXPECT_EQ(anInverseVec(3), 3.0);
  EXPECT_EQ(anInverseVec(4), 2.0);
  EXPECT_EQ(anInverseVec(5), 1.0);

  EXPECT_EQ(aVec(1), 1.0);
  EXPECT_EQ(aVec(5), 5.0);

  aVec.Invert();
  checkVectorsEqual(aVec, anInverseVec);
}

TEST(MathVectorTest, ScalarOperations)
{
  math_Vector aVec(1, 3);
  aVec(1) = 2.0;
  aVec(2) = 4.0;
  aVec(3) = 6.0;

  math_Vector aMulResult = aVec.Multiplied(2.5);
  EXPECT_EQ(aMulResult(1), 5.0);
  EXPECT_EQ(aMulResult(2), 10.0);
  EXPECT_EQ(aMulResult(3), 15.0);

  math_Vector aTMulResult = aVec.TMultiplied(2.5);
  checkVectorsEqual(aMulResult, aTMulResult);

  aVec.Multiply(0.5);
  EXPECT_EQ(aVec(1), 1.0);
  EXPECT_EQ(aVec(2), 2.0);
  EXPECT_EQ(aVec(3), 3.0);

  aVec *= 3.0;
  EXPECT_EQ(aVec(1), 3.0);
  EXPECT_EQ(aVec(2), 6.0);
  EXPECT_EQ(aVec(3), 9.0);

  math_Vector aDivResult = aVec.Divided(3.0);
  EXPECT_EQ(aDivResult(1), 1.0);
  EXPECT_EQ(aDivResult(2), 2.0);
  EXPECT_EQ(aDivResult(3), 3.0);

  aVec.Divide(3.0);
  checkVectorsEqual(aVec, aDivResult);

  aVec *= 6.0;
  aVec /= 2.0;
  EXPECT_EQ(aVec(1), 3.0);
  EXPECT_EQ(aVec(2), 6.0);
  EXPECT_EQ(aVec(3), 9.0);
}

TEST(MathVectorTest, DivisionOperations)
{
  math_Vector aVec(1, 3, 2.0);

  aVec.Divide(2.0);
  EXPECT_DOUBLE_EQ(aVec(1), 1.0) << "Division should work correctly";

  math_Vector aVec2(1, 3, 4.0);
  math_Vector aResult = aVec2.Divided(2.0);
  EXPECT_DOUBLE_EQ(aResult(1), 2.0) << "Divided method should work correctly";
}

TEST(MathVectorTest, VectorAdditionSubtraction)
{
  math_Vector aVec1(1, 3);
  aVec1(1) = 1.0;
  aVec1(2) = 2.0;
  aVec1(3) = 3.0;

  math_Vector aVec2(1, 3);
  aVec2(1) = 4.0;
  aVec2(2) = 5.0;
  aVec2(3) = 6.0;

  math_Vector anAddResult = aVec1.Added(aVec2);
  EXPECT_EQ(anAddResult(1), 5.0);
  EXPECT_EQ(anAddResult(2), 7.0);
  EXPECT_EQ(anAddResult(3), 9.0);

  math_Vector anAddResult2 = aVec1 + aVec2;
  checkVectorsEqual(anAddResult, anAddResult2);

  math_Vector aSubResult = aVec1.Subtracted(aVec2);
  EXPECT_EQ(aSubResult(1), -3.0);
  EXPECT_EQ(aSubResult(2), -3.0);
  EXPECT_EQ(aSubResult(3), -3.0);

  math_Vector aSubResult2 = aVec1 - aVec2;
  checkVectorsEqual(aSubResult, aSubResult2);

  math_Vector aVecCopy1(aVec1);
  aVecCopy1.Add(aVec2);
  checkVectorsEqual(aVecCopy1, anAddResult);

  math_Vector aVecCopy2(aVec1);
  aVecCopy2 += aVec2;
  checkVectorsEqual(aVecCopy2, anAddResult);

  math_Vector aVecCopy3(aVec1);
  aVecCopy3.Subtract(aVec2);
  checkVectorsEqual(aVecCopy3, aSubResult);

  math_Vector aVecCopy4(aVec1);
  aVecCopy4 -= aVec2;
  checkVectorsEqual(aVecCopy4, aSubResult);
}

TEST(MathVectorTest, VectorOperationsDifferentBounds)
{
  math_Vector aVec1(0, 2);
  aVec1(0) = 1.0;
  aVec1(1) = 2.0;
  aVec1(2) = 3.0;

  math_Vector aVec2(-1, 1);
  aVec2(-1) = 4.0;
  aVec2(0)  = 5.0;
  aVec2(1)  = 6.0;

  math_Vector anAddResult = aVec1.Added(aVec2);
  EXPECT_EQ(anAddResult(0), 5.0);
  EXPECT_EQ(anAddResult(1), 7.0);
  EXPECT_EQ(anAddResult(2), 9.0);
}

TEST(MathVectorTest, DotProduct)
{
  math_Vector aVec1(1, 3);
  aVec1(1) = 1.0;
  aVec1(2) = 2.0;
  aVec1(3) = 3.0;

  math_Vector aVec2(1, 3);
  aVec2(1) = 4.0;
  aVec2(2) = 5.0;
  aVec2(3) = 6.0;

  double aDotProduct = aVec1.Multiplied(aVec2);
  EXPECT_EQ(aDotProduct, 32.0);

  double aDotProduct2 = aVec1 * aVec2;
  EXPECT_EQ(aDotProduct, aDotProduct2);
}

TEST(MathVectorTest, SetOperation)
{
  math_Vector aVec(1, 6);
  aVec.Init(0.0);

  math_Vector aSubVec(1, 3);
  aSubVec(1) = 10.0;
  aSubVec(2) = 20.0;
  aSubVec(3) = 30.0;

  aVec.Set(2, 4, aSubVec);

  EXPECT_EQ(aVec(1), 0.0);
  EXPECT_EQ(aVec(2), 10.0);
  EXPECT_EQ(aVec(3), 20.0);
  EXPECT_EQ(aVec(4), 30.0);
  EXPECT_EQ(aVec(5), 0.0);
  EXPECT_EQ(aVec(6), 0.0);
}

TEST(MathVectorTest, SliceOperation)
{
  math_Vector aVec(1, 6);
  aVec(1) = 10.0;
  aVec(2) = 20.0;
  aVec(3) = 30.0;
  aVec(4) = 40.0;
  aVec(5) = 50.0;
  aVec(6) = 60.0;

  math_Vector aSlice1 = aVec.Slice(2, 4);
  EXPECT_EQ(aSlice1.Length(), 3);
  EXPECT_EQ(aSlice1.Lower(), 2);
  EXPECT_EQ(aSlice1.Upper(), 4);
  EXPECT_EQ(aSlice1(2), 20.0);
  EXPECT_EQ(aSlice1(3), 30.0);
  EXPECT_EQ(aSlice1(4), 40.0);

  math_Vector aSlice2 = aVec.Slice(4, 2);
  EXPECT_EQ(aSlice2.Length(), 3);
  EXPECT_EQ(aSlice2.Lower(), 2);
  EXPECT_EQ(aSlice2.Upper(), 4);
  EXPECT_EQ(aSlice2(2), 20.0);
  EXPECT_EQ(aSlice2(3), 30.0);
  EXPECT_EQ(aSlice2(4), 40.0);
}

TEST(MathVectorTest, VectorMatrixOperations)
{

  math_Matrix aMat(1, 2, 1, 3);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 2.0;
  aMat(1, 3) = 3.0;
  aMat(2, 1) = 4.0;
  aMat(2, 2) = 5.0;
  aMat(2, 3) = 6.0;

  math_Vector aVec1(1, 2);
  aVec1(1) = 2.0;
  aVec1(2) = 3.0;

  math_Vector aVec2(1, 3);
  aVec2(1) = 1.0;
  aVec2(2) = 2.0;
  aVec2(3) = 3.0;

  math_Vector aResult1 = aVec1.Multiplied(aMat);
  EXPECT_EQ(aResult1.Length(), 3);

  EXPECT_EQ(aResult1(1), 14.0);
  EXPECT_EQ(aResult1(2), 19.0);
  EXPECT_EQ(aResult1(3), 24.0);

  math_Vector aResult2(1, 3);
  aResult2.Multiply(aVec1, aMat);
  checkVectorsEqual(aResult1, aResult2);

  math_Vector aResult3(1, 2);
  aResult3.Multiply(aMat, aVec2);

  EXPECT_EQ(aResult3(1), 14.0);
  EXPECT_EQ(aResult3(2), 32.0);
}

TEST(MathVectorTest, TransposeMatrixOperations)
{

  math_Matrix aMat(1, 2, 1, 3);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 2.0;
  aMat(1, 3) = 3.0;
  aMat(2, 1) = 4.0;
  aMat(2, 2) = 5.0;
  aMat(2, 3) = 6.0;

  math_Vector aVec1(1, 2);
  aVec1(1) = 2.0;
  aVec1(2) = 3.0;

  math_Vector aVec2(1, 3);
  aVec2(1) = 1.0;
  aVec2(2) = 2.0;
  aVec2(3) = 3.0;

  math_Vector aResult1(1, 3);
  aResult1.TMultiply(aMat, aVec1);

  EXPECT_EQ(aResult1(1), 14.0);
  EXPECT_EQ(aResult1(2), 19.0);
  EXPECT_EQ(aResult1(3), 24.0);

  math_Vector aResult2(1, 2);
  aResult2.TMultiply(aVec2, aMat);

  EXPECT_EQ(aResult2(1), 14.0);
  EXPECT_EQ(aResult2(2), 32.0);
}

TEST(MathVectorTest, ThreeOperandOperations)
{
  math_Vector aVec1(1, 3);
  aVec1(1) = 1.0;
  aVec1(2) = 2.0;
  aVec1(3) = 3.0;

  math_Vector aVec2(1, 3);
  aVec2(1) = 4.0;
  aVec2(2) = 5.0;
  aVec2(3) = 6.0;

  math_Vector aResult(1, 3);

  aResult.Add(aVec1, aVec2);
  EXPECT_EQ(aResult(1), 5.0);
  EXPECT_EQ(aResult(2), 7.0);
  EXPECT_EQ(aResult(3), 9.0);

  aResult.Subtract(aVec1, aVec2);
  EXPECT_EQ(aResult(1), -3.0);
  EXPECT_EQ(aResult(2), -3.0);
  EXPECT_EQ(aResult(3), -3.0);

  aResult.Multiply(2.5, aVec1);
  EXPECT_EQ(aResult(1), 2.5);
  EXPECT_EQ(aResult(2), 5.0);
  EXPECT_EQ(aResult(3), 7.5);
}

TEST(MathVectorTest, OppositeOperation)
{
  math_Vector aVec(1, 3);
  aVec(1) = 1.0;
  aVec(2) = -2.0;
  aVec(3) = 3.0;

  math_Vector anOpposite = aVec.Opposite();
  EXPECT_EQ(anOpposite(1), -1.0);
  EXPECT_EQ(anOpposite(2), 2.0);
  EXPECT_EQ(anOpposite(3), -3.0);

  math_Vector anOpposite2 = -aVec;
  checkVectorsEqual(anOpposite, anOpposite2);
}

TEST(MathVectorTest, AssignmentOperations)
{
  math_Vector aVec1(1, 3);
  aVec1(1) = 1.0;
  aVec1(2) = 2.0;
  aVec1(3) = 3.0;

  math_Vector aVec2(1, 3);
  aVec2.Init(0.0);

  aVec2.Initialized(aVec1);
  checkVectorsEqual(aVec1, aVec2);

  math_Vector aVec3(1, 3);
  aVec3 = aVec1;
  checkVectorsEqual(aVec1, aVec3);
}

TEST(MathVectorTest, FriendOperators)
{
  math_Vector aVec(1, 3);
  aVec(1) = 2.0;
  aVec(2) = 4.0;
  aVec(3) = 6.0;

  math_Vector aResult1 = 3.0 * aVec;
  EXPECT_EQ(aResult1(1), 6.0);
  EXPECT_EQ(aResult1(2), 12.0);
  EXPECT_EQ(aResult1(3), 18.0);

  math_Vector aResult2 = aVec * 2.5;
  EXPECT_EQ(aResult2(1), 5.0);
  EXPECT_EQ(aResult2(2), 10.0);
  EXPECT_EQ(aResult2(3), 15.0);

  math_Vector aResult3 = aVec / 2.0;
  EXPECT_EQ(aResult3(1), 1.0);
  EXPECT_EQ(aResult3(2), 2.0);
  EXPECT_EQ(aResult3(3), 3.0);
}

TEST(MathVectorTest, EdgeCases)
{

  math_Vector aSingleVec(5, 5, 42.0);
  EXPECT_EQ(aSingleVec.Length(), 1);
  EXPECT_EQ(aSingleVec(5), 42.0);
  EXPECT_EQ(aSingleVec.Max(), 5);
  EXPECT_EQ(aSingleVec.Min(), 5);

  math_Vector aNegVec(-2, 1);
  aNegVec(-2) = 10.0;
  aNegVec(-1) = 20.0;
  aNegVec(0)  = 30.0;
  aNegVec(1)  = 40.0;

  EXPECT_EQ(aNegVec.Length(), 4);
  EXPECT_EQ(aNegVec.Lower(), -2);
  EXPECT_EQ(aNegVec.Upper(), 1);
  EXPECT_EQ(aNegVec.Max(), 1);
  EXPECT_EQ(aNegVec.Min(), -2);
}

TEST(MathVectorTest, MoveSemantics)
{

  int         aLen = 100;
  math_Vector aVec1(1, aLen);
  for (int i = 1; i <= aLen; ++i)
  {
    aVec1(i) = static_cast<double>(i);
  }

  math_Vector aVec2(std::move(aVec1));

  EXPECT_EQ(aVec2.Length(), aLen);
  EXPECT_EQ(aVec2(1), 1.0);
  EXPECT_EQ(aVec2(aLen), static_cast<double>(aLen));

  EXPECT_EQ(aVec1.Length(), 0);

  int         aSmallLen = 10;
  math_Vector aSmallVec1(1, aSmallLen);
  for (int i = 1; i <= aSmallLen; ++i)
  {
    aSmallVec1(i) = static_cast<double>(i);
  }

  math_Vector aSmallVec2(std::move(aSmallVec1));

  EXPECT_EQ(aSmallVec2.Length(), aSmallLen);
  EXPECT_EQ(aSmallVec2(1), 1.0);

  EXPECT_EQ(aSmallVec1.Length(), aSmallLen);
  EXPECT_EQ(aSmallVec1(1), 1.0);

  math_Vector aVecAssign1(1, aLen);
  for (int i = 1; i <= aLen; ++i)
  {
    aVecAssign1(i) = static_cast<double>(i);
  }

  math_Vector aVecAssign2(1, aLen);
  aVecAssign2.Init(0.0);

  aVecAssign2 = std::move(aVecAssign1);

  EXPECT_EQ(aVecAssign2.Length(), aLen);
  EXPECT_EQ(aVecAssign2(1), 1.0);

  EXPECT_EQ(aVecAssign1.Length(), 0);
}

TEST(MathVectorTest, Resize_StackToStack_SameSize)
{

  math_Vector aVec(1, 10);
  for (int i = 1; i <= 10; ++i)
  {
    aVec(i) = static_cast<double>(i);
  }

  aVec.Resize(10);

  EXPECT_EQ(aVec.Length(), 10);
  EXPECT_EQ(aVec.Lower(), 1);
  EXPECT_EQ(aVec.Upper(), 10);
  for (int i = 1; i <= 10; ++i)
  {
    EXPECT_DOUBLE_EQ(aVec(i), static_cast<double>(i));
  }
}

TEST(MathVectorTest, Resize_StackToStack_Grow)
{

  math_Vector aVec(1, 5);
  for (int i = 1; i <= 5; ++i)
  {
    aVec(i) = static_cast<double>(i * 10);
  }

  aVec.Resize(20);

  EXPECT_EQ(aVec.Length(), 20);
  EXPECT_EQ(aVec.Lower(), 1);
  EXPECT_EQ(aVec.Upper(), 20);

  for (int i = 1; i <= 5; ++i)
  {
    EXPECT_DOUBLE_EQ(aVec(i), static_cast<double>(i * 10));
  }
}

TEST(MathVectorTest, Resize_StackToStack_Shrink)
{

  math_Vector aVec(1, 20);
  for (int i = 1; i <= 20; ++i)
  {
    aVec(i) = static_cast<double>(i);
  }

  aVec.Resize(10);

  EXPECT_EQ(aVec.Length(), 10);
  EXPECT_EQ(aVec.Lower(), 1);
  EXPECT_EQ(aVec.Upper(), 10);

  for (int i = 1; i <= 10; ++i)
  {
    EXPECT_DOUBLE_EQ(aVec(i), static_cast<double>(i));
  }
}

TEST(MathVectorTest, Resize_StackToHeap)
{

  math_Vector aVec(1, 20);
  for (int i = 1; i <= 20; ++i)
  {
    aVec(i) = static_cast<double>(i);
  }

  aVec.Resize(50);

  EXPECT_EQ(aVec.Length(), 50);
  EXPECT_EQ(aVec.Lower(), 1);
  EXPECT_EQ(aVec.Upper(), 50);

  for (int i = 1; i <= 20; ++i)
  {
    EXPECT_DOUBLE_EQ(aVec(i), static_cast<double>(i));
  }
}

TEST(MathVectorTest, Resize_HeapToStack)
{

  math_Vector aVec(1, 50);
  for (int i = 1; i <= 50; ++i)
  {
    aVec(i) = static_cast<double>(i);
  }

  aVec.Resize(20);

  EXPECT_EQ(aVec.Length(), 20);
  EXPECT_EQ(aVec.Lower(), 1);
  EXPECT_EQ(aVec.Upper(), 20);

  for (int i = 1; i <= 20; ++i)
  {
    EXPECT_DOUBLE_EQ(aVec(i), static_cast<double>(i));
  }
}

TEST(MathVectorTest, Resize_HeapToHeap)
{

  math_Vector aVec(1, 50);
  for (int i = 1; i <= 50; ++i)
  {
    aVec(i) = static_cast<double>(i);
  }

  aVec.Resize(100);

  EXPECT_EQ(aVec.Length(), 100);
  EXPECT_EQ(aVec.Lower(), 1);
  EXPECT_EQ(aVec.Upper(), 100);

  for (int i = 1; i <= 50; ++i)
  {
    EXPECT_DOUBLE_EQ(aVec(i), static_cast<double>(i));
  }
}

TEST(MathVectorTest, Resize_NegativeLowerBound)
{

  math_Vector aVec(-5, 5);
  for (int i = -5; i <= 5; ++i)
  {
    aVec(i) = static_cast<double>(i);
  }

  aVec.Resize(8);

  EXPECT_EQ(aVec.Length(), 8);
  EXPECT_EQ(aVec.Lower(), -5);
  EXPECT_EQ(aVec.Upper(), 2);

  for (int i = -5; i <= 2; ++i)
  {
    EXPECT_DOUBLE_EQ(aVec(i), static_cast<double>(i));
  }
}
