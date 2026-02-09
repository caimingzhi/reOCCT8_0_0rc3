#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathLin_Gauss.hpp>
#include <MathLin_SVD.hpp>
#include <MathLin_Householder.hpp>
#include <MathUtils_Core.hpp>

#include <cmath>

namespace MathLin
{
  using namespace MathUtils;

  enum class LeastSquaresMethod
  {
    NormalEquations,
    QR,
    SVD
  };

  struct LeastSquaresResult
  {
    Status                     Status = Status::NotConverged;
    std::optional<math_Vector> Solution;
    std::optional<double>      Residual;
    std::optional<double>      ResidualSq;
    int                        Rank = 0;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  inline LeastSquaresResult LeastSquares(const math_Matrix& theA,
                                         const math_Vector& theB,
                                         LeastSquaresMethod theMethod    = LeastSquaresMethod::QR,
                                         double             theTolerance = 1.0e-15)
  {
    LeastSquaresResult aResult;

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();
    const int aM        = aRowUpper - aRowLower + 1;
    const int aN        = aColUpper - aColLower + 1;

    if (theB.Length() != aM)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    LinearResult aLinResult;

    switch (theMethod)
    {
      case LeastSquaresMethod::NormalEquations:
      {

        math_Matrix aAtA(aColLower, aColUpper, aColLower, aColUpper, 0.0);
        math_Vector aAtb(aColLower, aColUpper, 0.0);

        for (int i = aColLower; i <= aColUpper; ++i)
        {
          for (int j = aColLower; j <= aColUpper; ++j)
          {
            double aSum = 0.0;
            for (int k = aRowLower; k <= aRowUpper; ++k)
            {
              aSum += theA(k, i) * theA(k, j);
            }
            aAtA(i, j) = aSum;
          }
        }

        for (int i = aColLower; i <= aColUpper; ++i)
        {
          double aSum = 0.0;
          for (int k = aRowLower; k <= aRowUpper; ++k)
          {
            aSum += theA(k, i) * theB(theB.Lower() + k - aRowLower);
          }
          aAtb(i) = aSum;
        }

        aLinResult   = Solve(aAtA, aAtb, theTolerance);
        aResult.Rank = (aLinResult.IsDone()) ? aN : 0;
      }
      break;

      case LeastSquaresMethod::QR:
      {
        aLinResult = SolveQR(theA, theB, theTolerance);
        if (aLinResult.IsDone())
        {

          aResult.Rank = aN;
        }
      }
      break;

      case LeastSquaresMethod::SVD:
      {
        aLinResult = SolveSVD(theA, theB, theTolerance);
        if (aLinResult.IsDone())
        {

          SVDResult aSVD = SVD(theA, theTolerance);
          aResult.Rank   = aSVD.IsDone() ? aSVD.Rank : 0;
        }
      }
      break;
    }

    if (!aLinResult.IsDone())
    {
      aResult.Status = aLinResult.Status;
      return aResult;
    }

    aResult.Solution = aLinResult.Solution;

    const math_Vector& aX          = *aResult.Solution;
    double             aResidualSq = 0.0;

    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      double aAxi = 0.0;
      for (int j = aColLower; j <= aColUpper; ++j)
      {
        aAxi += theA(i, j) * aX(j);
      }
      double aRi = aAxi - theB(theB.Lower() + i - aRowLower);
      aResidualSq += aRi * aRi;
    }

    aResult.ResidualSq = aResidualSq;
    aResult.Residual   = std::sqrt(aResidualSq);
    aResult.Status     = Status::OK;
    return aResult;
  }

  inline LeastSquaresResult WeightedLeastSquares(
    const math_Matrix& theA,
    const math_Vector& theB,
    const math_Vector& theW,
    LeastSquaresMethod theMethod    = LeastSquaresMethod::QR,
    double             theTolerance = 1.0e-15)
  {
    LeastSquaresResult aResult;

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();
    const int aM        = aRowUpper - aRowLower + 1;

    if (theB.Length() != aM || theW.Length() != aM)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    for (int i = theW.Lower(); i <= theW.Upper(); ++i)
    {
      if (theW(i) <= 0.0)
      {
        aResult.Status = Status::InvalidInput;
        return aResult;
      }
    }

    math_Matrix aWA(aRowLower, aRowUpper, aColLower, aColUpper);
    math_Vector aWB(theB.Lower(), theB.Upper());

    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      double aSqrtW = std::sqrt(theW(theW.Lower() + i - aRowLower));
      for (int j = aColLower; j <= aColUpper; ++j)
      {
        aWA(i, j) = aSqrtW * theA(i, j);
      }
      aWB(theB.Lower() + i - aRowLower) = aSqrtW * theB(theB.Lower() + i - aRowLower);
    }

    return LeastSquares(aWA, aWB, theMethod, theTolerance);
  }

  inline LeastSquaresResult RegularizedLeastSquares(const math_Matrix& theA,
                                                    const math_Vector& theB,
                                                    double             theLambda,
                                                    double             theTolerance = 1.0e-15)
  {
    LeastSquaresResult aResult;

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();
    const int aM        = aRowUpper - aRowLower + 1;
    const int aN        = aColUpper - aColLower + 1;

    if (theB.Length() != aM)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    if (theLambda < 0.0)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    math_Matrix aAtA(aColLower, aColUpper, aColLower, aColUpper, 0.0);
    math_Vector aAtb(aColLower, aColUpper, 0.0);

    for (int i = aColLower; i <= aColUpper; ++i)
    {
      for (int j = aColLower; j <= aColUpper; ++j)
      {
        double aSum = 0.0;
        for (int k = aRowLower; k <= aRowUpper; ++k)
        {
          aSum += theA(k, i) * theA(k, j);
        }
        aAtA(i, j) = aSum;
      }

      aAtA(i, i) += theLambda;
    }

    for (int i = aColLower; i <= aColUpper; ++i)
    {
      double aSum = 0.0;
      for (int k = aRowLower; k <= aRowUpper; ++k)
      {
        aSum += theA(k, i) * theB(theB.Lower() + k - aRowLower);
      }
      aAtb(i) = aSum;
    }

    LinearResult aLinResult = Solve(aAtA, aAtb, theTolerance);
    if (!aLinResult.IsDone())
    {
      aResult.Status = aLinResult.Status;
      return aResult;
    }

    aResult.Solution = aLinResult.Solution;
    aResult.Rank     = aN;

    const math_Vector& aX          = *aResult.Solution;
    double             aResidualSq = 0.0;

    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      double aAxi = 0.0;
      for (int j = aColLower; j <= aColUpper; ++j)
      {
        aAxi += theA(i, j) * aX(j);
      }
      double aRi = aAxi - theB(theB.Lower() + i - aRowLower);
      aResidualSq += aRi * aRi;
    }

    aResult.ResidualSq = aResidualSq;
    aResult.Residual   = std::sqrt(aResidualSq);
    aResult.Status     = Status::OK;
    return aResult;
  }

  inline double OptimalRegularization(const math_Matrix& theA,
                                      const math_Vector& theB,
                                      double             theLambdaMin = 1.0e-10,
                                      double             theLambdaMax = 1.0e2,
                                      int                theNbPoints  = 20)
  {
    double aBestLambda = theLambdaMin;
    double aBestScore  = std::numeric_limits<double>::max();

    const double aLogMin  = std::log10(theLambdaMin);
    const double aLogMax  = std::log10(theLambdaMax);
    const double aLogStep = (aLogMax - aLogMin) / (theNbPoints - 1);

    for (int k = 0; k < theNbPoints; ++k)
    {
      double aLambda = std::pow(10.0, aLogMin + k * aLogStep);

      auto aResult = RegularizedLeastSquares(theA, theB, aLambda);
      if (aResult.IsDone() && aResult.ResidualSq)
      {
        double aScore = *aResult.ResidualSq;
        if (aScore < aBestScore)
        {
          aBestScore  = aScore;
          aBestLambda = aLambda;
        }
      }
    }

    return aBestLambda;
  }

} // namespace MathLin
