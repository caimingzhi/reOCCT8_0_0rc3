#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>

#include <cmath>
#include <algorithm>

namespace MathLin
{
  using namespace MathUtils;

  struct QRResult
  {
    Status                     Status = Status::NotConverged;
    std::optional<math_Matrix> Q;
    std::optional<math_Matrix> R;
    int                        Rank = 0;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  inline QRResult QR(const math_Matrix& theA, double theTolerance = 1.0e-20)
  {
    QRResult aResult;

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();
    const int aM        = aRowUpper - aRowLower + 1;
    const int aN        = aColUpper - aColLower + 1;

    if (aM < aN)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    math_Matrix aR(aRowLower, aRowUpper, aColLower, aColUpper);
    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      for (int j = aColLower; j <= aColUpper; ++j)
      {
        aR(i, j) = theA(i, j);
      }
    }

    math_Matrix aQ(aRowLower, aRowUpper, aRowLower, aRowUpper, 0.0);
    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      aQ(i, i) = 1.0;
    }

    math_Vector aV(aRowLower, aRowUpper);

    aResult.Rank = 0;

    for (int j = aColLower; j <= aColUpper; ++j)
    {
      const int aJOffset = j - aColLower;

      double aNorm = 0.0;
      for (int i = aRowLower + aJOffset; i <= aRowUpper; ++i)
      {
        aNorm += MathUtils::Sqr(aR(i, j));
      }
      aNorm = std::sqrt(aNorm);

      if (aNorm < theTolerance)
      {

        continue;
      }

      ++aResult.Rank;

      double aAlpha = aR(aRowLower + aJOffset, j);
      double aBeta  = (aAlpha >= 0.0) ? -aNorm : aNorm;

      for (int i = aRowLower; i < aRowLower + aJOffset; ++i)
      {
        aV(i) = 0.0;
      }
      aV(aRowLower + aJOffset) = aAlpha - aBeta;
      for (int i = aRowLower + aJOffset + 1; i <= aRowUpper; ++i)
      {
        aV(i) = aR(i, j);
      }

      double aVNormSq = 0.0;
      for (int i = aRowLower + aJOffset; i <= aRowUpper; ++i)
      {
        aVNormSq += MathUtils::Sqr(aV(i));
      }

      if (aVNormSq < MathUtils::THE_ZERO_TOL)
      {
        continue;
      }

      double aTau = 2.0 / aVNormSq;

      for (int k = j; k <= aColUpper; ++k)
      {

        double aVdotRk = 0.0;
        for (int i = aRowLower + aJOffset; i <= aRowUpper; ++i)
        {
          aVdotRk += aV(i) * aR(i, k);
        }

        for (int i = aRowLower + aJOffset; i <= aRowUpper; ++i)
        {
          aR(i, k) -= aTau * aVdotRk * aV(i);
        }
      }

      for (int k = aRowLower; k <= aRowUpper; ++k)
      {

        double aQkV = 0.0;
        for (int i = aRowLower + aJOffset; i <= aRowUpper; ++i)
        {
          aQkV += aQ(k, i) * aV(i);
        }

        for (int i = aRowLower + aJOffset; i <= aRowUpper; ++i)
        {
          aQ(k, i) -= aTau * aQkV * aV(i);
        }
      }
    }

    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      for (int j = aColLower; j < aColLower + (i - aRowLower) && j <= aColUpper; ++j)
      {
        aR(i, j) = 0.0;
      }
    }

    aResult.Q      = aQ;
    aResult.R      = aR;
    aResult.Status = Status::OK;
    return aResult;
  }

  inline LinearResult SolveQR(const math_Matrix& theA,
                              const math_Vector& theB,
                              double             theTolerance = 1.0e-20)
  {
    LinearResult aResult;

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();
    const int aM        = aRowUpper - aRowLower + 1;

    if (theB.Length() != aM)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    QRResult aQR = QR(theA, theTolerance);
    if (!aQR.IsDone())
    {
      aResult.Status = aQR.Status;
      return aResult;
    }

    const math_Matrix& aQ = *aQR.Q;
    const math_Matrix& aR = *aQR.R;

    math_Vector aC(aRowLower, aRowUpper, 0.0);
    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      double aSum = 0.0;
      for (int k = aRowLower; k <= aRowUpper; ++k)
      {
        aSum += aQ(k, i) * theB(theB.Lower() + k - aRowLower);
      }
      aC(i) = aSum;
    }

    aResult.Solution = math_Vector(aColLower, aColUpper, 0.0);

    for (int i = aColUpper; i >= aColLower; --i)
    {
      const int aIOffset = i - aColLower;
      double    aDiag    = aR(aRowLower + aIOffset, i);

      if (std::abs(aDiag) < theTolerance)
      {
        aResult.Status = Status::Singular;
        return aResult;
      }

      double aSum = aC(aRowLower + aIOffset);
      for (int k = i + 1; k <= aColUpper; ++k)
      {
        aSum -= aR(aRowLower + aIOffset, k) * (*aResult.Solution)(k);
      }
      (*aResult.Solution)(i) = aSum / aDiag;
    }

    aResult.Status = Status::OK;
    return aResult;
  }

  inline LinearResult SolveQRMultiple(const math_Matrix& theA,
                                      const math_Matrix& theB,
                                      double             theTolerance = 1.0e-20)
  {
    LinearResult aResult;

    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();

    if (theB.RowNumber() != theA.RowNumber())
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    QRResult aQR = QR(theA, theTolerance);
    if (!aQR.IsDone())
    {
      aResult.Status = aQR.Status;
      return aResult;
    }

    math_Vector aFirstSol(aColLower, aColUpper);
    bool        aFirstDone = false;

    for (int j = theB.LowerCol(); j <= theB.UpperCol(); ++j)
    {

      math_Vector aBj(theB.LowerRow(), theB.UpperRow());
      for (int i = theB.LowerRow(); i <= theB.UpperRow(); ++i)
      {
        aBj(i) = theB(i, j);
      }

      LinearResult aColResult = SolveQR(theA, aBj, theTolerance);
      if (!aColResult.IsDone())
      {
        aResult.Status = aColResult.Status;
        return aResult;
      }

      if (!aFirstDone)
      {
        aFirstSol  = *aColResult.Solution;
        aFirstDone = true;
      }
    }

    aResult.Solution = aFirstSol;
    aResult.Status   = Status::OK;
    return aResult;
  }

} // namespace MathLin
