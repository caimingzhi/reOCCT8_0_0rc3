#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <cmath>

namespace MathLin
{
  using namespace MathUtils;

  struct CroutResult
  {
    Status                     Status = Status::NotConverged;
    std::optional<math_Matrix> L;
    std::optional<math_Vector> D;
    std::optional<math_Matrix> Inverse;
    std::optional<double>      Determinant;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  inline CroutResult Crout(const math_Matrix& theA, double theMinPivot = 1.0e-20)
  {
    CroutResult aResult;

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();
    const int aN        = aRowUpper - aRowLower + 1;

    if (aN != aColUpper - aColLower + 1)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    math_Matrix aL(1, aN, 1, aN, 0.0);
    math_Vector aDiag(1, aN);

    double aDet = 1.0;

    for (int i = 1; i <= aN; ++i)
    {

      for (int j = 1; j <= i - 1; ++j)
      {
        double aScale = 0.0;
        for (int k = 1; k <= j - 1; ++k)
        {
          aScale += aL(i, k) * aL(j, k) * aDiag(k);
        }
        aL(i, j) = (theA(i + aRowLower - 1, j + aColLower - 1) - aScale) / aDiag(j);
      }

      double aScale = 0.0;
      for (int k = 1; k <= i - 1; ++k)
      {
        aScale += aL(i, k) * aL(i, k) * aDiag(k);
      }
      aDiag(i) = theA(i + aRowLower - 1, i + aColLower - 1) - aScale;
      aDet *= aDiag(i);

      if (std::abs(aDiag(i)) <= theMinPivot)
      {
        aResult.Status = Status::Singular;
        return aResult;
      }

      aL(i, i) = 1.0;
    }

    aL(1, 1) = 1.0 / aL(1, 1);
    for (int i = 2; i <= aN; ++i)
    {
      for (int k = 1; k <= i - 1; ++k)
      {
        double aScale = 0.0;
        for (int j = k; j <= i - 1; ++j)
        {
          aScale += aL(i, j) * aL(j, k);
        }
        aL(i, k) = -aScale / aL(i, i);
      }
      aL(i, i) = 1.0 / aL(i, i);
    }

    math_Matrix aInv(1, aN, 1, aN, 0.0);
    for (int j = 1; j <= aN; ++j)
    {
      double aScale = aL(j, j) * aL(j, j) / aDiag(j);
      for (int k = j + 1; k <= aN; ++k)
      {
        aScale += aL(k, j) * aL(k, j) / aDiag(k);
      }
      aInv(j, j) = aScale;

      for (int i = j + 1; i <= aN; ++i)
      {
        aScale = aL(i, j) * aL(i, i) / aDiag(i);
        for (int k = i + 1; k <= aN; ++k)
        {
          aScale += aL(k, j) * aL(k, i) / aDiag(k);
        }
        aInv(i, j) = aScale;
      }
    }

    aResult.L = math_Matrix(aRowLower, aRowUpper, aColLower, aColUpper, 0.0);
    for (int i = 1; i <= aN; ++i)
    {
      for (int j = 1; j <= i; ++j)
      {
        (*aResult.L)(i + aRowLower - 1, j + aColLower - 1) = aL(i, j);
      }
    }

    aResult.D = math_Vector(aRowLower, aRowUpper);
    for (int i = 1; i <= aN; ++i)
    {
      (*aResult.D)(i + aRowLower - 1) = aDiag(i);
    }

    aResult.Inverse = math_Matrix(aRowLower, aRowUpper, aColLower, aColUpper, 0.0);
    for (int i = 1; i <= aN; ++i)
    {
      for (int j = 1; j <= i; ++j)
      {
        (*aResult.Inverse)(i + aRowLower - 1, j + aColLower - 1) = aInv(i, j);
      }

      for (int j = i + 1; j <= aN; ++j)
      {
        (*aResult.Inverse)(i + aRowLower - 1, j + aColLower - 1) = aInv(j, i);
      }
    }

    aResult.Determinant = aDet;
    aResult.Status      = Status::OK;
    return aResult;
  }

  inline LinearResult SolveCrout(const math_Matrix& theA,
                                 const math_Vector& theB,
                                 double             theMinPivot = 1.0e-20)
  {
    LinearResult aResult;

    CroutResult aCrout = Crout(theA, theMinPivot);
    if (!aCrout.IsDone())
    {
      aResult.Status = aCrout.Status;
      return aResult;
    }

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aN        = aRowUpper - aRowLower + 1;

    if (theB.Length() != aN)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    const math_Matrix& aInv    = *aCrout.Inverse;
    const int          aBLower = theB.Lower();

    aResult.Solution = math_Vector(aRowLower, aRowUpper, 0.0);
    for (int i = 1; i <= aN; ++i)
    {
      double aSum = aInv(i + aRowLower - 1, 1 + aRowLower - 1) * theB(1 + aBLower - 1);
      for (int j = 2; j <= i; ++j)
      {
        aSum += aInv(i + aRowLower - 1, j + aRowLower - 1) * theB(j + aBLower - 1);
      }
      for (int j = i + 1; j <= aN; ++j)
      {
        aSum += aInv(j + aRowLower - 1, i + aRowLower - 1) * theB(j + aBLower - 1);
      }
      (*aResult.Solution)(i + aRowLower - 1) = aSum;
    }

    aResult.Determinant = aCrout.Determinant;
    aResult.Status      = Status::OK;
    return aResult;
  }

  inline InverseResult InvertCrout(const math_Matrix& theA, double theMinPivot = 1.0e-20)
  {
    InverseResult aResult;

    CroutResult aCrout = Crout(theA, theMinPivot);
    if (!aCrout.IsDone())
    {
      aResult.Status = aCrout.Status;
      return aResult;
    }

    aResult.Status      = Status::OK;
    aResult.Inverse     = aCrout.Inverse;
    aResult.Determinant = aCrout.Determinant;
    return aResult;
  }

} // namespace MathLin
