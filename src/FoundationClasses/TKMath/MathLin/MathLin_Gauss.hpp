#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>
#include <math_IntegerVector.hpp>

#include <cmath>

namespace MathLin
{
  using namespace MathUtils;

  struct LUResult
  {
    Status                            Status = Status::NotConverged;
    std::optional<math_Matrix>        LU;
    std::optional<math_IntegerVector> Pivot;
    std::optional<double>             Determinant;
    int                               Sign = 1;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  inline LUResult LU(const math_Matrix& theA, double theMinPivot = 1.0e-20)
  {
    LUResult aResult;

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();
    const int aRowCount = aRowUpper - aRowLower + 1;
    const int aColCount = aColUpper - aColLower + 1;

    if (aRowCount != aColCount)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    aResult.LU    = theA;
    aResult.Pivot = math_IntegerVector(aRowLower, aRowUpper);
    aResult.Sign  = 1;

    math_Matrix&        aLU    = *aResult.LU;
    math_IntegerVector& aPivot = *aResult.Pivot;

    math_Vector aScale(aRowLower, aRowUpper);
    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      double aMax = 0.0;
      for (int j = aColLower; j <= aColUpper; ++j)
      {
        const double aAbs = std::abs(aLU(i, j));
        if (aAbs > aMax)
        {
          aMax = aAbs;
        }
      }
      if (aMax < theMinPivot)
      {
        aResult.Status = Status::NumericalError;
        return aResult;
      }
      aScale(i) = 1.0 / aMax;
    }

    for (int k = aRowLower; k <= aRowUpper; ++k)
    {

      double aMaxScaled = 0.0;
      int    aPivotRow  = k;

      for (int i = k; i <= aRowUpper; ++i)
      {
        const double aScaled = aScale(i) * std::abs(aLU(i, k));
        if (aScaled > aMaxScaled)
        {
          aMaxScaled = aScaled;
          aPivotRow  = i;
        }
      }

      if (aPivotRow != k)
      {
        for (int j = aColLower; j <= aColUpper; ++j)
        {
          std::swap(aLU(aPivotRow, j), aLU(k, j));
        }
        aResult.Sign = -aResult.Sign;
        std::swap(aScale(aPivotRow), aScale(k));
      }
      aPivot(k) = aPivotRow;

      if (std::abs(aLU(k, k)) < theMinPivot)
      {
        aResult.Status = Status::NumericalError;
        return aResult;
      }

      for (int i = k + 1; i <= aRowUpper; ++i)
      {
        aLU(i, k) /= aLU(k, k);
        const double aFactor = aLU(i, k);
        for (int j = k + 1; j <= aColUpper; ++j)
        {
          aLU(i, j) -= aFactor * aLU(k, j);
        }
      }
    }

    aResult.Determinant = static_cast<double>(aResult.Sign);
    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      *aResult.Determinant *= aLU(i, i);
    }

    aResult.Status = Status::OK;
    return aResult;
  }

  inline LinearResult Solve(const math_Matrix& theA,
                            const math_Vector& theB,
                            double             theMinPivot = 1.0e-20)
  {
    LinearResult aResult;

    LUResult aLURes = LU(theA, theMinPivot);
    if (!aLURes.IsDone())
    {
      aResult.Status = aLURes.Status;
      return aResult;
    }

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();

    if (theB.Lower() != aRowLower || theB.Upper() != aRowUpper)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    const math_Matrix&        aLU    = *aLURes.LU;
    const math_IntegerVector& aPivot = *aLURes.Pivot;

    math_Vector aX = theB;

    int aFirstNonZero = 0;
    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      const int aPivotIdx = aPivot(i);
      double    aSum      = aX(aPivotIdx);
      aX(aPivotIdx)       = aX(i);

      if (aFirstNonZero != 0)
      {
        for (int j = aFirstNonZero; j < i; ++j)
        {
          aSum -= aLU(i, j) * aX(j);
        }
      }
      else if (!MathUtils::IsZero(aSum))
      {
        aFirstNonZero = i;
      }
      aX(i) = aSum;
    }

    for (int i = aRowUpper; i >= aRowLower; --i)
    {
      double aSum = aX(i);
      for (int j = i + 1; j <= aRowUpper; ++j)
      {
        aSum -= aLU(i, j) * aX(j);
      }
      aX(i) = aSum / aLU(i, i);
    }

    aResult.Status      = Status::OK;
    aResult.Solution    = aX;
    aResult.Determinant = aLURes.Determinant;
    return aResult;
  }

  inline LinearResult SolveMultiple(const math_Matrix& theA,
                                    const math_Matrix& theB,
                                    double             theMinPivot = 1.0e-20)
  {
    LinearResult aResult;

    LUResult aLURes = LU(theA, theMinPivot);
    if (!aLURes.IsDone())
    {
      aResult.Status = aLURes.Status;
      return aResult;
    }

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();

    if (theB.LowerRow() != aRowLower || theB.UpperRow() != aRowUpper)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    const math_Matrix&        aLU    = *aLURes.LU;
    const math_IntegerVector& aPivot = *aLURes.Pivot;

    math_Matrix aX(theB.LowerRow(), theB.UpperRow(), theB.LowerCol(), theB.UpperCol());

    for (int col = theB.LowerCol(); col <= theB.UpperCol(); ++col)
    {

      math_Vector aWork(aRowLower, aRowUpper);
      for (int i = aRowLower; i <= aRowUpper; ++i)
      {
        aWork(i) = theB(i, col);
      }

      int aFirstNonZero = 0;
      for (int i = aRowLower; i <= aRowUpper; ++i)
      {
        const int aPivotIdx = aPivot(i);
        double    aSum      = aWork(aPivotIdx);
        aWork(aPivotIdx)    = aWork(i);

        if (aFirstNonZero != 0)
        {
          for (int j = aFirstNonZero; j < i; ++j)
          {
            aSum -= aLU(i, j) * aWork(j);
          }
        }
        else if (!MathUtils::IsZero(aSum))
        {
          aFirstNonZero = i;
        }
        aWork(i) = aSum;
      }

      for (int i = aRowUpper; i >= aRowLower; --i)
      {
        double aSum = aWork(i);
        for (int j = i + 1; j <= aRowUpper; ++j)
        {
          aSum -= aLU(i, j) * aWork(j);
        }
        aWork(i) = aSum / aLU(i, i);
      }

      for (int i = aRowLower; i <= aRowUpper; ++i)
      {
        aX(i, col) = aWork(i);
      }
    }

    aResult.Status      = Status::OK;
    aResult.Determinant = aLURes.Determinant;

    math_Vector aSol(aRowLower, aRowUpper);
    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      aSol(i) = aX(i, theB.LowerCol());
    }
    aResult.Solution = aSol;
    return aResult;
  }

  inline LinearResult Determinant(const math_Matrix& theA, double theMinPivot = 1.0e-20)
  {
    LinearResult aResult;

    LUResult aLURes = LU(theA, theMinPivot);
    if (!aLURes.IsDone())
    {
      aResult.Status      = aLURes.Status;
      aResult.Determinant = 0.0;
      return aResult;
    }

    aResult.Status      = Status::OK;
    aResult.Determinant = aLURes.Determinant;
    return aResult;
  }

  inline InverseResult Invert(const math_Matrix& theA, double theMinPivot = 1.0e-20)
  {
    InverseResult aResult;

    LUResult aLURes = LU(theA, theMinPivot);
    if (!aLURes.IsDone())
    {
      aResult.Status = aLURes.Status;
      return aResult;
    }

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();

    const math_Matrix&        aLU    = *aLURes.LU;
    const math_IntegerVector& aPivot = *aLURes.Pivot;

    math_Matrix aInv(aRowLower, aRowUpper, aColLower, aColUpper, 0.0);
    math_Vector aCol(aRowLower, aRowUpper);

    for (int col = aColLower; col <= aColUpper; ++col)
    {

      for (int i = aRowLower; i <= aRowUpper; ++i)
      {
        aCol(i) = 0.0;
      }
      aCol(col - aColLower + aRowLower) = 1.0;

      int aFirstNonZero = 0;
      for (int i = aRowLower; i <= aRowUpper; ++i)
      {
        const int aPivotIdx = aPivot(i);
        double    aSum      = aCol(aPivotIdx);
        aCol(aPivotIdx)     = aCol(i);

        if (aFirstNonZero != 0)
        {
          for (int j = aFirstNonZero; j < i; ++j)
          {
            aSum -= aLU(i, j) * aCol(j);
          }
        }
        else if (!MathUtils::IsZero(aSum))
        {
          aFirstNonZero = i;
        }
        aCol(i) = aSum;
      }

      for (int i = aRowUpper; i >= aRowLower; --i)
      {
        double aSum = aCol(i);
        for (int j = i + 1; j <= aRowUpper; ++j)
        {
          aSum -= aLU(i, j) * aCol(j);
        }
        aCol(i) = aSum / aLU(i, i);
      }

      for (int i = aRowLower; i <= aRowUpper; ++i)
      {
        aInv(i, col) = aCol(i);
      }
    }

    aResult.Status      = Status::OK;
    aResult.Inverse     = aInv;
    aResult.Determinant = aLURes.Determinant;
    return aResult;
  }

} // namespace MathLin
