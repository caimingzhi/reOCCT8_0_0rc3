

#include <math_EigenValuesSearcher.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array1.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Failure.hpp>
#include <Precision.hpp>

#include <cmath>
#include <algorithm>

namespace
{

  void createTridiagonalMatrix(const NCollection_Array1<double>& theDiagonal,
                               const NCollection_Array1<double>& theSubdiagonal,
                               math_Matrix&                      theMatrix)
  {
    const int aN = theDiagonal.Length();
    theMatrix.Init(0.0);

    for (int i = 1; i <= aN; i++)
      theMatrix(i, i) = theDiagonal(i);

    for (int i = 2; i <= aN; i++)
    {
      theMatrix(i, i - 1) = theSubdiagonal(i);
      theMatrix(i - 1, i) = theSubdiagonal(i);
    }
  }

  bool verifyEigenPair(const math_Matrix& theMatrix,
                       const double       theEigenValue,
                       const math_Vector& theEigenVector,
                       const double       theTolerance = 1e-12)
  {
    const int   aN = theMatrix.RowNumber();
    math_Vector aResult(1, aN);

    for (int i = 1; i <= aN; i++)
    {
      double aSum = 0.0;
      for (int j = 1; j <= aN; j++)
        aSum += theMatrix(i, j) * theEigenVector(j);
      aResult(i) = aSum;
    }

    for (int i = 1; i <= aN; i++)
    {
      const double aExpected = theEigenValue * theEigenVector(i);
      if (std::abs(aResult(i) - aExpected) > theTolerance)
        return false;
    }

    return true;
  }

  bool areOrthogonal(const math_Vector& theVec1,
                     const math_Vector& theVec2,
                     const double       theTolerance = 1e-12)
  {
    double aDotProduct = 0.0;
    for (int i = 1; i <= theVec1.Length(); i++)
      aDotProduct += theVec1(i) * theVec2(i);

    return std::abs(aDotProduct) < theTolerance;
  }

  double vectorNorm(const math_Vector& theVector)
  {
    double aNorm = 0.0;
    for (int i = 1; i <= theVector.Length(); i++)
      aNorm += theVector(i) * theVector(i);
    return std::sqrt(aNorm);
  }
} // namespace

TEST(math_EigenValuesSearcherTest, ConstructorDimensionMismatch)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 2);

  aDiagonal.SetValue(1, 1.0);
  aDiagonal.SetValue(2, 2.0);
  aDiagonal.SetValue(3, 3.0);

  aSubdiagonal.SetValue(1, 0.5);
  aSubdiagonal.SetValue(2, 1.5);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_FALSE(searcher.IsDone());
}

TEST(math_EigenValuesSearcherTest, OneByOneMatrix)
{
  NCollection_Array1<double> aDiagonal(1, 1);
  NCollection_Array1<double> aSubdiagonal(1, 1);

  aDiagonal.SetValue(1, 5.0);
  aSubdiagonal.SetValue(1, 0.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());
  EXPECT_EQ(searcher.Dimension(), 1);
  EXPECT_NEAR(searcher.EigenValue(1), 5.0, Precision::Confusion());

  math_Vector eigenvec = searcher.EigenVector(1);
  EXPECT_EQ(eigenvec.Length(), 1);
  EXPECT_NEAR(eigenvec(1), 1.0, Precision::Confusion());
}

TEST(math_EigenValuesSearcherTest, TwoByTwoMatrix)
{
  NCollection_Array1<double> aDiagonal(1, 2);
  NCollection_Array1<double> aSubdiagonal(1, 2);

  aDiagonal.SetValue(1, 2.0);
  aDiagonal.SetValue(2, 3.0);
  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());
  EXPECT_EQ(searcher.Dimension(), 2);

  std::vector<double> eigenvals = {searcher.EigenValue(1), searcher.EigenValue(2)};
  std::sort(eigenvals.begin(), eigenvals.end());

  const double lambda1 = 2.5 - 0.5 * std::sqrt(5.0);
  const double lambda2 = 2.5 + 0.5 * std::sqrt(5.0);

  EXPECT_NEAR(eigenvals[0], lambda1, 1e-10);
  EXPECT_NEAR(eigenvals[1], lambda2, 1e-10);

  math_Matrix originalMatrix(1, 2, 1, 2);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 2; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-10));
    EXPECT_NEAR(vectorNorm(eigenvec), 1.0, 1e-10);
  }

  const math_Vector vec1 = searcher.EigenVector(1);
  const math_Vector vec2 = searcher.EigenVector(2);
  EXPECT_TRUE(areOrthogonal(vec1, vec2, 1e-10));
}

TEST(math_EigenValuesSearcherTest, ThreeByThreeMatrix)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  aDiagonal.SetValue(1, 4.0);
  aDiagonal.SetValue(2, 4.0);
  aDiagonal.SetValue(3, 4.0);
  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1.0);
  aSubdiagonal.SetValue(3, 1.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());
  EXPECT_EQ(searcher.Dimension(), 3);

  math_Matrix originalMatrix(1, 3, 1, 3);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 3; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-10));
    EXPECT_NEAR(vectorNorm(eigenvec), 1.0, 1e-10);
  }

  for (int i = 1; i <= 3; i++)
  {
    for (int j = i + 1; j <= 3; j++)
    {
      const math_Vector vec_i = searcher.EigenVector(i);
      const math_Vector vec_j = searcher.EigenVector(j);
      EXPECT_TRUE(areOrthogonal(vec_i, vec_j, 1e-10));
    }
  }
}

TEST(math_EigenValuesSearcherTest, DiagonalMatrix)
{
  NCollection_Array1<double> aDiagonal(1, 4);
  NCollection_Array1<double> aSubdiagonal(1, 4);

  aDiagonal.SetValue(1, 1.0);
  aDiagonal.SetValue(2, 2.0);
  aDiagonal.SetValue(3, 3.0);
  aDiagonal.SetValue(4, 4.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 0.0);
  aSubdiagonal.SetValue(3, 0.0);
  aSubdiagonal.SetValue(4, 0.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());
  EXPECT_EQ(searcher.Dimension(), 4);

  std::vector<double> eigenvals;
  for (int i = 1; i <= 4; i++)
    eigenvals.push_back(searcher.EigenValue(i));

  std::sort(eigenvals.begin(), eigenvals.end());

  EXPECT_NEAR(eigenvals[0], 1.0, Precision::Confusion());
  EXPECT_NEAR(eigenvals[1], 2.0, Precision::Confusion());
  EXPECT_NEAR(eigenvals[2], 3.0, Precision::Confusion());
  EXPECT_NEAR(eigenvals[3], 4.0, Precision::Confusion());
}

TEST(math_EigenValuesSearcherTest, IdentityMatrix)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  aDiagonal.SetValue(1, 1.0);
  aDiagonal.SetValue(2, 1.0);
  aDiagonal.SetValue(3, 1.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 0.0);
  aSubdiagonal.SetValue(3, 0.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());
  EXPECT_EQ(searcher.Dimension(), 3);

  for (int i = 1; i <= 3; i++)
  {
    EXPECT_NEAR(searcher.EigenValue(i), 1.0, Precision::Confusion());
  }
}

TEST(math_EigenValuesSearcherTest, NegativeEigenvalues)
{
  NCollection_Array1<double> aDiagonal(1, 2);
  NCollection_Array1<double> aSubdiagonal(1, 2);

  aDiagonal.SetValue(1, -1.0);
  aDiagonal.SetValue(2, -1.0);
  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 2.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  std::vector<double> eigenvals = {searcher.EigenValue(1), searcher.EigenValue(2)};
  std::sort(eigenvals.begin(), eigenvals.end());

  EXPECT_NEAR(eigenvals[0], -3.0, 1e-10);
  EXPECT_NEAR(eigenvals[1], 1.0, 1e-10);

  math_Matrix originalMatrix(1, 2, 1, 2);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 2; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);
    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-10));
  }
}

TEST(math_EigenValuesSearcherTest, FiveByFiveMatrix)
{
  NCollection_Array1<double> aDiagonal(1, 5);
  NCollection_Array1<double> aSubdiagonal(1, 5);

  for (int i = 1; i <= 5; i++)
    aDiagonal.SetValue(i, 2.0);

  aSubdiagonal.SetValue(1, 0.0);
  for (int i = 2; i <= 5; i++)
    aSubdiagonal.SetValue(i, -1.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());
  EXPECT_EQ(searcher.Dimension(), 5);

  math_Matrix originalMatrix(1, 5, 1, 5);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 5; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-9));
    EXPECT_NEAR(vectorNorm(eigenvec), 1.0, 1e-9);
  }

  for (int i = 1; i <= 5; i++)
  {
    const double eigenval = searcher.EigenValue(i);
    EXPECT_GE(eigenval, 0.0);
    EXPECT_LE(eigenval, 4.0);
  }
}

TEST(math_EigenValuesSearcherTest, SmallSubdiagonalElements)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  aDiagonal.SetValue(1, 1.0);
  aDiagonal.SetValue(2, 2.0);
  aDiagonal.SetValue(3, 3.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1e-14);
  aSubdiagonal.SetValue(3, 1e-14);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  std::vector<double> eigenvals;
  for (int i = 1; i <= 3; i++)
    eigenvals.push_back(searcher.EigenValue(i));

  std::sort(eigenvals.begin(), eigenvals.end());

  EXPECT_NEAR(eigenvals[0], 1.0, 1e-10);
  EXPECT_NEAR(eigenvals[1], 2.0, 1e-10);
  EXPECT_NEAR(eigenvals[2], 3.0, 1e-10);
}

TEST(math_EigenValuesSearcherTest, ZeroDiagonalElements)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  aDiagonal.SetValue(1, 0.0);
  aDiagonal.SetValue(2, 0.0);
  aDiagonal.SetValue(3, 0.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1.0);
  aSubdiagonal.SetValue(3, 1.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());
  EXPECT_EQ(searcher.Dimension(), 3);

  std::vector<double> eigenvals;
  for (int i = 1; i <= 3; i++)
    eigenvals.push_back(searcher.EigenValue(i));

  std::sort(eigenvals.begin(), eigenvals.end());

  EXPECT_NEAR(eigenvals[0], -std::sqrt(2.0), 1e-10);
  EXPECT_NEAR(eigenvals[1], 0.0, 1e-10);
  EXPECT_NEAR(eigenvals[2], std::sqrt(2.0), 1e-10);
}

TEST(math_EigenValuesSearcherTest, LargeDiagonalElements)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  aDiagonal.SetValue(1, 1e6);
  aDiagonal.SetValue(2, 2e6);
  aDiagonal.SetValue(3, 3e6);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1e3);
  aSubdiagonal.SetValue(3, 2e3);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 3, 1, 3);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 3; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-6));
    EXPECT_NEAR(vectorNorm(eigenvec), 1.0, 1e-10);
  }
}

TEST(math_EigenValuesSearcherTest, AlternatingPattern)
{
  NCollection_Array1<double> aDiagonal(1, 4);
  NCollection_Array1<double> aSubdiagonal(1, 4);

  aDiagonal.SetValue(1, 1.0);
  aDiagonal.SetValue(2, -1.0);
  aDiagonal.SetValue(3, 1.0);
  aDiagonal.SetValue(4, -1.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 0.5);
  aSubdiagonal.SetValue(3, -0.5);
  aSubdiagonal.SetValue(4, 0.5);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 4, 1, 4);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 4; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-10));
  }
}

TEST(math_EigenValuesSearcherTest, RepeatedEigenvalues)
{
  NCollection_Array1<double> aDiagonal(1, 4);
  NCollection_Array1<double> aSubdiagonal(1, 4);

  aDiagonal.SetValue(1, 2.0);
  aDiagonal.SetValue(2, 2.0);
  aDiagonal.SetValue(3, 2.0);
  aDiagonal.SetValue(4, 2.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 0.0);
  aSubdiagonal.SetValue(3, 0.0);
  aSubdiagonal.SetValue(4, 0.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  for (int i = 1; i <= 4; i++)
  {
    EXPECT_NEAR(searcher.EigenValue(i), 2.0, Precision::Confusion());
  }
}

TEST(math_EigenValuesSearcherTest, VerySmallElements)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  aDiagonal.SetValue(1, 1e-10);
  aDiagonal.SetValue(2, 2e-10);
  aDiagonal.SetValue(3, 3e-10);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1e-11);
  aSubdiagonal.SetValue(3, 2e-11);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 3, 1, 3);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 3; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-18));
    EXPECT_NEAR(vectorNorm(eigenvec), 1.0, 1e-12);
  }
}

TEST(math_EigenValuesSearcherTest, AntisymmetricSubdiagonal)
{
  NCollection_Array1<double> aDiagonal(1, 5);
  NCollection_Array1<double> aSubdiagonal(1, 5);

  for (int i = 1; i <= 5; i++)
    aDiagonal.SetValue(i, static_cast<double>(i));

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1.0);
  aSubdiagonal.SetValue(3, -2.0);
  aSubdiagonal.SetValue(4, 1.0);
  aSubdiagonal.SetValue(5, -2.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 5, 1, 5);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 5; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-9));
  }

  for (int i = 1; i <= 5; i++)
  {
    for (int j = i + 1; j <= 5; j++)
    {
      const math_Vector vec_i = searcher.EigenVector(i);
      const math_Vector vec_j = searcher.EigenVector(j);
      EXPECT_TRUE(areOrthogonal(vec_i, vec_j, 1e-9));
    }
  }
}

TEST(math_EigenValuesSearcherTest, WilkinsonMatrix)
{
  const int                  n = 5;
  NCollection_Array1<double> aDiagonal(1, n);
  NCollection_Array1<double> aSubdiagonal(1, n);

  const int m = (n - 1) / 2;
  for (int i = 1; i <= n; i++)
  {
    aDiagonal.SetValue(i, static_cast<double>(std::abs(i - 1 - m)));
  }

  aSubdiagonal.SetValue(1, 0.0);
  for (int i = 2; i <= n; i++)
    aSubdiagonal.SetValue(i, 1.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, n, 1, n);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= n; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-9));
    EXPECT_NEAR(vectorNorm(eigenvec), 1.0, 1e-9);
  }
}

TEST(math_EigenValuesSearcherTest, MixedSignDiagonal)
{
  NCollection_Array1<double> aDiagonal(1, 4);
  NCollection_Array1<double> aSubdiagonal(1, 4);

  aDiagonal.SetValue(1, -2.0);
  aDiagonal.SetValue(2, 1.0);
  aDiagonal.SetValue(3, -1.0);
  aDiagonal.SetValue(4, 3.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1.5);
  aSubdiagonal.SetValue(3, 0.8);
  aSubdiagonal.SetValue(4, -0.6);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 4, 1, 4);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  std::vector<double> eigenvals;
  for (int i = 1; i <= 4; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    eigenvals.push_back(eigenval);
    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-9));
  }

  double eigenSum = 0.0, diagSum = 0.0;
  for (int i = 1; i <= 4; i++)
  {
    eigenSum += eigenvals[i - 1];
    diagSum += aDiagonal(i);
  }
  EXPECT_NEAR(eigenSum, diagSum, 1e-9);
}

TEST(math_EigenValuesSearcherTest, LargerMatrix)
{
  const int                  n = 8;
  NCollection_Array1<double> aDiagonal(1, n);
  NCollection_Array1<double> aSubdiagonal(1, n);

  for (int i = 1; i <= n; i++)
  {
    aDiagonal.SetValue(i, static_cast<double>(i * i));
  }

  aSubdiagonal.SetValue(1, 0.0);
  for (int i = 2; i <= n; i++)
  {
    double val = static_cast<double>(i % 3 == 0 ? -1.0 : 1.0);
    aSubdiagonal.SetValue(i, val * std::sqrt(static_cast<double>(i)));
  }

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, n, 1, n);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= n; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-8));
    EXPECT_NEAR(vectorNorm(eigenvec), 1.0, 1e-8);
  }

  for (int i = 1; i <= n; i++)
  {
    for (int j = i + 1; j <= n; j++)
    {
      const math_Vector vec_i = searcher.EigenVector(i);
      const math_Vector vec_j = searcher.EigenVector(j);
      EXPECT_TRUE(areOrthogonal(vec_i, vec_j, 1e-8));
    }
  }
}

TEST(math_EigenValuesSearcherTest, RationalNumberPattern)
{
  NCollection_Array1<double> aDiagonal(1, 4);
  NCollection_Array1<double> aSubdiagonal(1, 4);

  aDiagonal.SetValue(1, 1.0 / 3.0);
  aDiagonal.SetValue(2, 2.0 / 3.0);
  aDiagonal.SetValue(3, 1.0);
  aDiagonal.SetValue(4, 4.0 / 3.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1.0 / 6.0);
  aSubdiagonal.SetValue(3, 1.0 / 4.0);
  aSubdiagonal.SetValue(4, 1.0 / 5.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 4, 1, 4);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 4; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-12));
    EXPECT_NEAR(vectorNorm(eigenvec), 1.0, 1e-12);
  }
}

TEST(math_EigenValuesSearcherTest, NearDegenerateEigenvalues)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  aDiagonal.SetValue(1, 1.0);
  aDiagonal.SetValue(2, 1.0 + 1e-8);
  aDiagonal.SetValue(3, 1.0 + 2e-8);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1e-10);
  aSubdiagonal.SetValue(3, 1e-10);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  std::vector<double> eigenvals;
  for (int i = 1; i <= 3; i++)
    eigenvals.push_back(searcher.EigenValue(i));

  std::sort(eigenvals.begin(), eigenvals.end());

  EXPECT_NEAR(eigenvals[0], 1.0, 1e-7);
  EXPECT_NEAR(eigenvals[1], 1.0 + 1e-8, 1e-7);
  EXPECT_NEAR(eigenvals[2], 1.0 + 2e-8, 1e-7);

  math_Matrix originalMatrix(1, 3, 1, 3);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 3; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-9));
  }
}

TEST(math_EigenValuesSearcherTest, DeflationConditionPrecision)
{
  NCollection_Array1<double> aDiagonal(1, 4);
  NCollection_Array1<double> aSubdiagonal(1, 4);

  aDiagonal.SetValue(1, 1e6);
  aDiagonal.SetValue(2, 2e6);
  aDiagonal.SetValue(3, 3e6);
  aDiagonal.SetValue(4, 4e6);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1e-15);
  aSubdiagonal.SetValue(3, 2e-15);
  aSubdiagonal.SetValue(4, 3e-15);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 4, 1, 4);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 4; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-9));
  }

  std::vector<double> eigenvals;
  for (int i = 1; i <= 4; i++)
    eigenvals.push_back(searcher.EigenValue(i));

  std::sort(eigenvals.begin(), eigenvals.end());

  EXPECT_NEAR(eigenvals[0], 1e6, 1e3);
  EXPECT_NEAR(eigenvals[1], 2e6, 1e3);
  EXPECT_NEAR(eigenvals[2], 3e6, 1e3);
  EXPECT_NEAR(eigenvals[3], 4e6, 1e3);
}

TEST(math_EigenValuesSearcherTest, ExactZeroSubdiagonal)
{
  NCollection_Array1<double> aDiagonal(1, 5);
  NCollection_Array1<double> aSubdiagonal(1, 5);

  aDiagonal.SetValue(1, 1.0);
  aDiagonal.SetValue(2, 4.0);
  aDiagonal.SetValue(3, 9.0);
  aDiagonal.SetValue(4, 16.0);
  aDiagonal.SetValue(5, 25.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1.0);
  aSubdiagonal.SetValue(3, 0.0);
  aSubdiagonal.SetValue(4, 2.0);
  aSubdiagonal.SetValue(5, 0.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 5, 1, 5);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 5; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-12));
  }
}

TEST(math_EigenValuesSearcherTest, ConvergenceBehavior)
{
  NCollection_Array1<double> aDiagonal(1, 6);
  NCollection_Array1<double> aSubdiagonal(1, 6);

  for (int i = 1; i <= 6; i++)
    aDiagonal.SetValue(i, static_cast<double>(i) * 0.1);

  aSubdiagonal.SetValue(1, 0.0);
  for (int i = 2; i <= 6; i++)
    aSubdiagonal.SetValue(i, 0.99);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 6, 1, 6);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 6; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-9));
  }
}

TEST(math_EigenValuesSearcherTest, NumericalStability)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  aDiagonal.SetValue(1, 1e-100);
  aDiagonal.SetValue(2, 1e100);
  aDiagonal.SetValue(3, 1e-50);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1e-75);
  aSubdiagonal.SetValue(3, 1e75);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  for (int i = 1; i <= 3; i++)
  {
    const double eigenval = searcher.EigenValue(i);
    EXPECT_TRUE(std::isfinite(eigenval));
    EXPECT_FALSE(std::isnan(eigenval));

    const math_Vector eigenvec = searcher.EigenVector(i);
    for (int j = 1; j <= 3; j++)
    {
      EXPECT_TRUE(std::isfinite(eigenvec(j)));
      EXPECT_FALSE(std::isnan(eigenvec(j)));
    }
  }
}

TEST(math_EigenValuesSearcherTest, WilkinsonShiftAccuracy)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  aDiagonal.SetValue(1, 1.0);
  aDiagonal.SetValue(2, 2.0);
  aDiagonal.SetValue(3, 1.0000001);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1.0);
  aSubdiagonal.SetValue(3, 0.0000001);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 3, 1, 3);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 3; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-10));
  }
}

TEST(math_EigenValuesSearcherTest, ZeroRadiusHandling)
{
  NCollection_Array1<double> aDiagonal(1, 4);
  NCollection_Array1<double> aSubdiagonal(1, 4);

  aDiagonal.SetValue(1, 0.0);
  aDiagonal.SetValue(2, 0.0);
  aDiagonal.SetValue(3, 1.0);
  aDiagonal.SetValue(4, 1.0);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, 1e-16);
  aSubdiagonal.SetValue(3, 1e-16);
  aSubdiagonal.SetValue(4, 0.0);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 4, 1, 4);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 4; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-12));
  }
}

TEST(math_EigenValuesSearcherTest, PathologicalEqualElements)
{
  NCollection_Array1<double> aDiagonal(1, 5);
  NCollection_Array1<double> aSubdiagonal(1, 5);

  const double value = 42.0;
  for (int i = 1; i <= 5; i++)
    aDiagonal.SetValue(i, value);

  aSubdiagonal.SetValue(1, 0.0);
  for (int i = 2; i <= 5; i++)
    aSubdiagonal.SetValue(i, value);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 5, 1, 5);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 5; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-9));
  }
}

TEST(math_EigenValuesSearcherTest, IncreasingSubdiagonal)
{
  NCollection_Array1<double> aDiagonal(1, 6);
  NCollection_Array1<double> aSubdiagonal(1, 6);

  for (int i = 1; i <= 6; i++)
    aDiagonal.SetValue(i, 1.0);

  aSubdiagonal.SetValue(1, 0.0);
  for (int i = 2; i <= 6; i++)
    aSubdiagonal.SetValue(i, static_cast<double>(i - 1) * 0.1);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);

  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 6, 1, 6);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 6; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-10));
    EXPECT_NEAR(vectorNorm(eigenvec), 1.0, 1e-10);
  }

  for (int i = 1; i <= 6; i++)
  {
    for (int j = i + 1; j <= 6; j++)
    {
      const math_Vector vec_i = searcher.EigenVector(i);
      const math_Vector vec_j = searcher.EigenVector(j);
      EXPECT_TRUE(areOrthogonal(vec_i, vec_j, 1e-10));
    }
  }
}

TEST(math_EigenValuesSearcherTest, DeflationConditionSemantics)
{
  NCollection_Array1<double> aDiagonal(1, 3);
  NCollection_Array1<double> aSubdiagonal(1, 3);

  const double largeDiag1       = 1e8;
  const double largeDiag2       = 2e8;
  const double machEpsilonLevel = largeDiag1 * std::numeric_limits<double>::epsilon();

  aDiagonal.SetValue(1, largeDiag1);
  aDiagonal.SetValue(2, largeDiag2);
  aDiagonal.SetValue(3, 3e8);

  aSubdiagonal.SetValue(1, 0.0);
  aSubdiagonal.SetValue(2, machEpsilonLevel);
  aSubdiagonal.SetValue(3, machEpsilonLevel * 0.5);

  const double diagSum       = std::abs(largeDiag1) + std::abs(largeDiag2);
  const double testCondition = machEpsilonLevel + diagSum;

  EXPECT_EQ(testCondition, diagSum)
    << "Deflation condition should hold for machine-epsilon level elements";

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);
  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 3, 1, 3);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 3; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-6));
  }
}

TEST(math_EigenValuesSearcherTest, DeflationBoundaryCondition)
{
  NCollection_Array1<double> aDiagonal(1, 4);
  NCollection_Array1<double> aSubdiagonal(1, 4);

  aDiagonal.SetValue(1, 1.0);
  aDiagonal.SetValue(2, 1000.0);
  aDiagonal.SetValue(3, 1e-6);
  aDiagonal.SetValue(4, 1e6);

  aSubdiagonal.SetValue(1, 0.0);

  const double eps = std::numeric_limits<double>::epsilon();

  const double sum1 = std::abs(aDiagonal(1)) + std::abs(aDiagonal(2));
  aSubdiagonal.SetValue(2, sum1 * eps * 0.1);

  const double sum2 = std::abs(aDiagonal(2)) + std::abs(aDiagonal(3));
  aSubdiagonal.SetValue(3, sum2 * eps * 0.1);

  const double sum3 = std::abs(aDiagonal(3)) + std::abs(aDiagonal(4));
  aSubdiagonal.SetValue(4, sum3 * eps * 0.1);

  math_EigenValuesSearcher searcher(aDiagonal, aSubdiagonal);
  EXPECT_TRUE(searcher.IsDone());

  math_Matrix originalMatrix(1, 4, 1, 4);
  createTridiagonalMatrix(aDiagonal, aSubdiagonal, originalMatrix);

  for (int i = 1; i <= 4; i++)
  {
    const double      eigenval = searcher.EigenValue(i);
    const math_Vector eigenvec = searcher.EigenVector(i);

    EXPECT_TRUE(verifyEigenPair(originalMatrix, eigenval, eigenvec, 1e-9));
    EXPECT_TRUE(std::isfinite(eigenval));
    EXPECT_FALSE(std::isnan(eigenval));
  }
}
