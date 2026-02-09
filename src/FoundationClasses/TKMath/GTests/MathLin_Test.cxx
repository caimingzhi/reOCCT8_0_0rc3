

#include <gtest/gtest.h>

#include <MathLin_SVD.hpp>
#include <MathLin_Householder.hpp>
#include <MathLin_Jacobi.hpp>
#include <MathLin_LeastSquares.hpp>
#include <MathLin_Gauss.hpp>
#include <math_SVD.hpp>
#include <math_Householder.hpp>
#include <math_Jacobi.hpp>
#include <math_GaussLeastSquare.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-10;

  math_Matrix CreateIdentity(int theN)
  {
    math_Matrix aMat(1, theN, 1, theN, 0.0);
    for (int i = 1; i <= theN; ++i)
    {
      aMat(i, i) = 1.0;
    }
    return aMat;
  }

  math_Matrix CreateSPD(int theN)
  {
    math_Matrix aMat(1, theN, 1, theN, 0.0);
    for (int i = 1; i <= theN; ++i)
    {
      for (int j = 1; j <= theN; ++j)
      {
        aMat(i, j) = 1.0 / (i + j - 1);
      }
      aMat(i, i) += static_cast<double>(theN);
    }
    return aMat;
  }

  math_Matrix CreateRandom(int theM, int theN, int theSeed = 42)
  {
    math_Matrix aMat(1, theM, 1, theN);
    srand(static_cast<unsigned int>(theSeed));
    for (int i = 1; i <= theM; ++i)
    {
      for (int j = 1; j <= theN; ++j)
      {
        aMat(i, j) = static_cast<double>(rand()) / RAND_MAX * 2.0 - 1.0;
      }
    }
    return aMat;
  }

  double VectorNorm(const math_Vector& theVec)
  {
    double aNorm = 0.0;
    for (int i = theVec.Lower(); i <= theVec.Upper(); ++i)
    {
      aNorm += theVec(i) * theVec(i);
    }
    return std::sqrt(aNorm);
  }

  math_Matrix MatMul(const math_Matrix& theA, const math_Matrix& theB)
  {
    const int   aM = theA.RowNumber();
    const int   aN = theB.ColNumber();
    const int   aK = theA.ColNumber();
    math_Matrix aResult(1, aM, 1, aN, 0.0);
    for (int i = 1; i <= aM; ++i)
    {
      for (int j = 1; j <= aN; ++j)
      {
        for (int k = 1; k <= aK; ++k)
        {
          aResult(i, j) += theA(i, k) * theB(k, j);
        }
      }
    }
    return aResult;
  }

  math_Matrix Transpose(const math_Matrix& theMat)
  {
    const int   aM = theMat.RowNumber();
    const int   aN = theMat.ColNumber();
    math_Matrix aResult(1, aN, 1, aM);
    for (int i = 1; i <= aM; ++i)
    {
      for (int j = 1; j <= aN; ++j)
      {
        aResult(j, i) = theMat(i, j);
      }
    }
    return aResult;
  }

} // namespace

TEST(MathLin_SVD_Test, BasicDecomposition_2x2)
{
  math_Matrix aMat(1, 2, 1, 2);
  aMat(1, 1) = 3.0;
  aMat(1, 2) = 2.0;
  aMat(2, 1) = 2.0;
  aMat(2, 2) = 3.0;

  auto aResult = MathLin::SVD(aMat);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.Rank, 2);

  const math_Matrix& aU = *aResult.U;
  const math_Vector& aS = *aResult.SingularValues;
  const math_Matrix& aV = *aResult.V;

  math_Matrix aSigma(1, 2, 1, 2, 0.0);
  aSigma(1, 1) = aS(1);
  aSigma(2, 2) = aS(2);

  math_Matrix aUSigma        = MatMul(aU, aSigma);
  math_Matrix aVt            = Transpose(aV);
  math_Matrix aReconstructed = MatMul(aUSigma, aVt);

  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      EXPECT_NEAR(aReconstructed(i, j), aMat(i, j), THE_TOLERANCE);
    }
  }
}

TEST(MathLin_SVD_Test, SingularValues)
{
  math_Matrix aMat(1, 3, 1, 3);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 2.0;
  aMat(1, 3) = 3.0;
  aMat(2, 1) = 4.0;
  aMat(2, 2) = 5.0;
  aMat(2, 3) = 6.0;
  aMat(3, 1) = 7.0;
  aMat(3, 2) = 8.0;
  aMat(3, 3) = 9.0;

  auto aResult = MathLin::SVD(aMat);

  ASSERT_TRUE(aResult.IsDone());

  const math_Vector& aS = *aResult.SingularValues;
  for (int i = aS.Lower(); i < aS.Upper(); ++i)
  {
    EXPECT_GE(aS(i), 0.0);
    EXPECT_GE(aS(i), aS(i + 1));
  }

  EXPECT_LE(aResult.Rank, 2);
}

TEST(MathLin_SVD_Test, SolveSystem)
{
  math_Matrix aMat(1, 2, 1, 2);
  aMat(1, 1) = 3.0;
  aMat(1, 2) = 1.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 2.0;

  math_Vector aB(1, 2);
  aB(1) = 9.0;
  aB(2) = 8.0;

  auto aResult = MathLin::SolveSVD(aMat, aB);

  ASSERT_TRUE(aResult.IsDone());

  const math_Vector& aX      = *aResult.Solution;
  double             aCheck1 = aMat(1, 1) * aX(1) + aMat(1, 2) * aX(2);
  double             aCheck2 = aMat(2, 1) * aX(1) + aMat(2, 2) * aX(2);

  EXPECT_NEAR(aCheck1, aB(1), THE_TOLERANCE);
  EXPECT_NEAR(aCheck2, aB(2), THE_TOLERANCE);
}

TEST(MathLin_SVD_Test, PseudoInverse)
{
  math_Matrix aMat(1, 2, 1, 2);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 2.0;
  aMat(2, 1) = 3.0;
  aMat(2, 2) = 4.0;

  auto aPinv = MathLin::PseudoInverse(aMat);

  ASSERT_TRUE(aPinv.IsDone());

  math_Matrix aTemp  = MatMul(aMat, *aPinv.Inverse);
  math_Matrix aCheck = MatMul(aTemp, aMat);

  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      EXPECT_NEAR(aCheck(i, j), aMat(i, j), THE_TOLERANCE);
    }
  }
}

TEST(MathLin_SVD_Test, ConditionNumber)
{

  math_Matrix aI     = CreateIdentity(3);
  double      aCondI = MathLin::ConditionNumber(aI);
  EXPECT_NEAR(aCondI, 1.0, THE_TOLERANCE);

  math_Matrix aHilbert(1, 3, 1, 3);
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      aHilbert(i, j) = 1.0 / (i + j - 1);
    }
  }
  double aCondH = MathLin::ConditionNumber(aHilbert);
  EXPECT_GT(aCondH, 100.0);
}

TEST(MathLin_Householder_Test, BasicQR_2x2)
{
  math_Matrix aMat(1, 2, 1, 2);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 2.0;
  aMat(2, 1) = 3.0;
  aMat(2, 2) = 4.0;

  auto aResult = MathLin::QR(aMat);

  ASSERT_TRUE(aResult.IsDone());

  const math_Matrix& aQ = *aResult.Q;
  const math_Matrix& aR = *aResult.R;

  math_Matrix aQQt = MatMul(aQ, Transpose(aQ));
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      double aExpected = (i == j) ? 1.0 : 0.0;
      EXPECT_NEAR(aQQt(i, j), aExpected, THE_TOLERANCE);
    }
  }

  EXPECT_NEAR(aR(2, 1), 0.0, THE_TOLERANCE);

  math_Matrix aQR = MatMul(aQ, aR);
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      EXPECT_NEAR(aQR(i, j), aMat(i, j), THE_TOLERANCE);
    }
  }
}

TEST(MathLin_Householder_Test, SolveSystem)
{
  math_Matrix aMat(1, 2, 1, 2);
  aMat(1, 1) = 3.0;
  aMat(1, 2) = 1.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 2.0;

  math_Vector aB(1, 2);
  aB(1) = 9.0;
  aB(2) = 8.0;

  auto aResult = MathLin::SolveQR(aMat, aB);

  ASSERT_TRUE(aResult.IsDone());

  const math_Vector& aX      = *aResult.Solution;
  double             aCheck1 = aMat(1, 1) * aX(1) + aMat(1, 2) * aX(2);
  double             aCheck2 = aMat(2, 1) * aX(1) + aMat(2, 2) * aX(2);

  EXPECT_NEAR(aCheck1, aB(1), THE_TOLERANCE);
  EXPECT_NEAR(aCheck2, aB(2), THE_TOLERANCE);
}

TEST(MathLin_Householder_Test, Overdetermined)
{

  math_Matrix aMat(1, 3, 1, 2);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 1.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 2.0;
  aMat(3, 1) = 1.0;
  aMat(3, 2) = 3.0;

  math_Vector aB(1, 3);
  aB(1) = 1.0;
  aB(2) = 2.0;
  aB(3) = 3.0;

  auto aResult = MathLin::SolveQR(aMat, aB);

  ASSERT_TRUE(aResult.IsDone());

  EXPECT_EQ((*aResult.Solution).Length(), 2);
}

TEST(MathLin_Jacobi_Test, Eigenvalues_Diagonal)
{
  math_Matrix aMat(1, 3, 1, 3, 0.0);
  aMat(1, 1) = 3.0;
  aMat(2, 2) = 1.0;
  aMat(3, 3) = 2.0;

  auto aResult = MathLin::Jacobi(aMat, true);

  ASSERT_TRUE(aResult.IsDone());

  const math_Vector& aEigenVals = *aResult.EigenValues;

  EXPECT_NEAR(aEigenVals(1), 3.0, THE_TOLERANCE);
  EXPECT_NEAR(aEigenVals(2), 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aEigenVals(3), 1.0, THE_TOLERANCE);
}

TEST(MathLin_Jacobi_Test, Eigenvalues_Symmetric)
{
  math_Matrix aMat(1, 2, 1, 2);
  aMat(1, 1) = 3.0;
  aMat(1, 2) = 1.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 3.0;

  auto aResult = MathLin::Jacobi(aMat, true);

  ASSERT_TRUE(aResult.IsDone());

  const math_Vector& aEigenVals = *aResult.EigenValues;

  EXPECT_NEAR(aEigenVals(1), 4.0, THE_TOLERANCE);
  EXPECT_NEAR(aEigenVals(2), 2.0, THE_TOLERANCE);
}

TEST(MathLin_Jacobi_Test, EigenvectorsOrthogonal)
{
  math_Matrix aMat = CreateSPD(3);

  auto aResult = MathLin::Jacobi(aMat, false);

  ASSERT_TRUE(aResult.IsDone());

  const math_Matrix& aV = *aResult.EigenVectors;

  math_Matrix aVtV = MatMul(Transpose(aV), aV);
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      double aExpected = (i == j) ? 1.0 : 0.0;
      EXPECT_NEAR(aVtV(i, j), aExpected, 1.0e-8);
    }
  }
}

TEST(MathLin_Jacobi_Test, SpectralDecomposition)
{
  math_Matrix aMat = CreateSPD(3);

  auto aResult = MathLin::SpectralDecomposition(aMat);

  ASSERT_TRUE(aResult.IsDone());

  const math_Vector& aD = *aResult.EigenValues;
  const math_Matrix& aV = *aResult.EigenVectors;

  math_Matrix aDiag(1, 3, 1, 3, 0.0);
  for (int i = 1; i <= 3; ++i)
  {
    aDiag(i, i) = aD(i);
  }

  math_Matrix aVD            = MatMul(aV, aDiag);
  math_Matrix aReconstructed = MatMul(aVD, Transpose(aV));

  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      EXPECT_NEAR(aReconstructed(i, j), aMat(i, j), 1.0e-8);
    }
  }
}

TEST(MathLin_Jacobi_Test, MatrixSqrt)
{
  math_Matrix aMat = CreateSPD(2);

  auto aSqrt = MathLin::MatrixSqrt(aMat);

  ASSERT_TRUE(aSqrt.has_value());

  math_Matrix aCheck = MatMul(*aSqrt, *aSqrt);

  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      EXPECT_NEAR(aCheck(i, j), aMat(i, j), 1.0e-8);
    }
  }
}

TEST(MathLin_LeastSquares_Test, SquareSystem)
{
  math_Matrix aMat(1, 2, 1, 2);
  aMat(1, 1) = 3.0;
  aMat(1, 2) = 1.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 2.0;

  math_Vector aB(1, 2);
  aB(1) = 9.0;
  aB(2) = 8.0;

  auto aResult = MathLin::LeastSquares(aMat, aB, MathLin::LeastSquaresMethod::QR);

  ASSERT_TRUE(aResult.IsDone());

  EXPECT_LT(*aResult.Residual, THE_TOLERANCE);
}

TEST(MathLin_LeastSquares_Test, Overdetermined)
{

  math_Matrix aMat(1, 4, 1, 2);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 1.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 2.0;
  aMat(3, 1) = 1.0;
  aMat(3, 2) = 3.0;
  aMat(4, 1) = 1.0;
  aMat(4, 2) = 4.0;

  math_Vector aB(1, 4);
  aB(1) = 2.0;
  aB(2) = 3.0;
  aB(3) = 4.0;
  aB(4) = 5.0;

  auto aResult = MathLin::LeastSquares(aMat, aB, MathLin::LeastSquaresMethod::QR);

  ASSERT_TRUE(aResult.IsDone());

  const math_Vector& aX = *aResult.Solution;

  EXPECT_NEAR(aX(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aX(2), 1.0, THE_TOLERANCE);

  EXPECT_LT(*aResult.Residual, THE_TOLERANCE);
}

TEST(MathLin_LeastSquares_Test, MethodComparison)
{
  math_Matrix aMat = CreateRandom(5, 3);
  math_Vector aB(1, 5);
  for (int i = 1; i <= 5; ++i)
  {
    aB(i) = static_cast<double>(i);
  }

  auto aResultNE  = MathLin::LeastSquares(aMat, aB, MathLin::LeastSquaresMethod::NormalEquations);
  auto aResultQR  = MathLin::LeastSquares(aMat, aB, MathLin::LeastSquaresMethod::QR);
  auto aResultSVD = MathLin::LeastSquares(aMat, aB, MathLin::LeastSquaresMethod::SVD);

  ASSERT_TRUE(aResultNE.IsDone());
  ASSERT_TRUE(aResultQR.IsDone());
  ASSERT_TRUE(aResultSVD.IsDone());

  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR((*aResultNE.Solution)(i), (*aResultQR.Solution)(i), 1.0e-6);
    EXPECT_NEAR((*aResultQR.Solution)(i), (*aResultSVD.Solution)(i), 1.0e-6);
  }
}

TEST(MathLin_LeastSquares_Test, WeightedLeastSquares)
{
  math_Matrix aMat(1, 3, 1, 2);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 1.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 2.0;
  aMat(3, 1) = 1.0;
  aMat(3, 2) = 3.0;

  math_Vector aB(1, 3);
  aB(1) = 2.0;
  aB(2) = 3.0;
  aB(3) = 4.5;

  math_Vector aW1(1, 3, 1.0);
  auto        aResult1 = MathLin::WeightedLeastSquares(aMat, aB, aW1);

  math_Vector aW2(1, 3);
  aW2(1)        = 10.0;
  aW2(2)        = 10.0;
  aW2(3)        = 0.1;
  auto aResult2 = MathLin::WeightedLeastSquares(aMat, aB, aW2);

  ASSERT_TRUE(aResult1.IsDone());
  ASSERT_TRUE(aResult2.IsDone());

  EXPECT_NE((*aResult1.Solution)(1), (*aResult2.Solution)(1));
}

TEST(MathLin_LeastSquares_Test, RegularizedLeastSquares)
{

  math_Matrix aMat(1, 3, 1, 3);
  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      aMat(i, j) = 1.0 / (i + j - 1);
    }
  }

  math_Vector aB(1, 3);
  aB(1) = 1.0;
  aB(2) = 0.5;
  aB(3) = 0.333;

  auto aResultNoReg = MathLin::LeastSquares(aMat, aB);
  auto aResultReg   = MathLin::RegularizedLeastSquares(aMat, aB, 0.01);

  ASSERT_TRUE(aResultNoReg.IsDone());
  ASSERT_TRUE(aResultReg.IsDone());

  double aNormNoReg = VectorNorm(*aResultNoReg.Solution);
  double aNormReg   = VectorNorm(*aResultReg.Solution);
  EXPECT_LT(aNormReg, aNormNoReg);
}

TEST(MathLin_Test, CompareWithOldAPI_SVD)
{
  math_Matrix aMat(1, 3, 1, 3);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 2.0;
  aMat(1, 3) = 3.0;
  aMat(2, 1) = 4.0;
  aMat(2, 2) = 5.0;
  aMat(2, 3) = 6.0;
  aMat(3, 1) = 7.0;
  aMat(3, 2) = 8.0;
  aMat(3, 3) = 10.0;

  math_Vector aB(1, 3);
  aB(1) = 1.0;
  aB(2) = 2.0;
  aB(3) = 3.0;

  math_SVD    anOldSVD(aMat);
  math_Vector anOldSol(1, 3);
  anOldSVD.Solve(aB, anOldSol);

  auto aNewResult = MathLin::SolveSVD(aMat, aB);

  ASSERT_TRUE(anOldSVD.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR(anOldSol(i), (*aNewResult.Solution)(i), 1.0e-8);
  }
}

TEST(MathLin_Test, CompareWithOldAPI_Householder)
{
  math_Matrix aMat(1, 3, 1, 2);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 1.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 2.0;
  aMat(3, 1) = 1.0;
  aMat(3, 2) = 3.0;

  math_Vector aB(1, 3);
  aB(1) = 2.0;
  aB(2) = 3.0;
  aB(3) = 4.0;

  math_Matrix aBMat(1, 3, 1, 1);
  aBMat(1, 1) = aB(1);
  aBMat(2, 1) = aB(2);
  aBMat(3, 1) = aB(3);
  math_Householder anOldHH(aMat, aBMat);

  auto aNewResult = MathLin::SolveQR(aMat, aB);

  ASSERT_TRUE(anOldHH.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  math_Vector anOldSol(1, 2);
  anOldHH.Value(anOldSol, 1);

  for (int i = 1; i <= 2; ++i)
  {
    EXPECT_NEAR(anOldSol(i), (*aNewResult.Solution)(i), 1.0e-8);
  }
}

TEST(MathLin_Test, CompareWithOldAPI_Jacobi)
{
  math_Matrix aMat(1, 3, 1, 3);
  aMat(1, 1) = 3.0;
  aMat(1, 2) = 1.0;
  aMat(1, 3) = 0.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 3.0;
  aMat(2, 3) = 1.0;
  aMat(3, 1) = 0.0;
  aMat(3, 2) = 1.0;
  aMat(3, 3) = 3.0;

  math_Jacobi anOldJacobi(aMat);

  auto aNewResult = MathLin::Jacobi(aMat, true);

  ASSERT_TRUE(anOldJacobi.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  const math_Vector& aNewEig = *aNewResult.EigenValues;
  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR(anOldJacobi.Value(i), aNewEig(i), 1.0e-8);
  }
}

TEST(MathLin_Test, CompareWithOldAPI_GaussLeastSquare)
{
  math_Matrix aMat(1, 4, 1, 2);
  aMat(1, 1) = 1.0;
  aMat(1, 2) = 1.0;
  aMat(2, 1) = 1.0;
  aMat(2, 2) = 2.0;
  aMat(3, 1) = 1.0;
  aMat(3, 2) = 3.0;
  aMat(4, 1) = 1.0;
  aMat(4, 2) = 4.0;

  math_Vector aB(1, 4);
  aB(1) = 2.0;
  aB(2) = 3.0;
  aB(3) = 4.0;
  aB(4) = 5.0;

  math_GaussLeastSquare anOldLS(aMat);
  math_Vector           anOldSol(1, 2);
  anOldLS.Solve(aB, anOldSol);

  auto aNewResult = MathLin::LeastSquares(aMat, aB);

  ASSERT_TRUE(anOldLS.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  for (int i = 1; i <= 2; ++i)
  {
    EXPECT_NEAR(anOldSol(i), (*aNewResult.Solution)(i), 1.0e-8);
  }
}
