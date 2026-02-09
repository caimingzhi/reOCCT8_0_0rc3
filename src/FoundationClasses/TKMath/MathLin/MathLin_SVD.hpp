#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <math_Recipes.hpp>
#include <MathUtils_Core.hpp>

#include <cmath>
#include <algorithm>

namespace MathLin
{
  using namespace MathUtils;

  struct SVDResult
  {
    Status                     Status = Status::NotConverged;
    std::optional<math_Matrix> U;
    std::optional<math_Vector> SingularValues;
    std::optional<math_Matrix> V;
    int                        Rank = 0;

    bool IsDone() const { return Status == Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  inline SVDResult SVD(const math_Matrix& theA, double theTolerance = 1.0e-15)
  {
    SVDResult aResult;

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();
    const int aM        = aRowUpper - aRowLower + 1;
    const int aN        = aColUpper - aColLower + 1;

    const int aURows = std::max(aM, aN);

    math_Matrix aU(1, aURows, 1, aN, 0.0);
    math_Vector aW(1, aN);
    math_Matrix aV(1, aN, 1, aN);

    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      for (int j = aColLower; j <= aColUpper; ++j)
      {
        aU(i - aRowLower + 1, j - aColLower + 1) = theA(i, j);
      }
    }

    if (SVD_Decompose(aU, aW, aV) != 0)
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    double aMaxSV = 0.0;
    for (int i = 1; i <= aN; ++i)
    {
      aMaxSV = std::max(aMaxSV, aW(i));
    }

    double aThreshold = theTolerance * aMaxSV;
    aResult.Rank      = 0;
    for (int i = 1; i <= aN; ++i)
    {
      if (aW(i) > aThreshold)
      {
        ++aResult.Rank;
      }
    }

    aResult.U = math_Matrix(aRowLower, aRowLower + aM - 1, aColLower, aColLower + aN - 1);
    for (int i = 1; i <= aM; ++i)
    {
      for (int j = 1; j <= aN; ++j)
      {
        (*aResult.U)(aRowLower + i - 1, aColLower + j - 1) = aU(i, j);
      }
    }

    aResult.SingularValues = math_Vector(aColLower, aColLower + aN - 1);
    for (int i = 1; i <= aN; ++i)
    {
      (*aResult.SingularValues)(aColLower + i - 1) = aW(i);
    }

    aResult.V = math_Matrix(aColLower, aColLower + aN - 1, aColLower, aColLower + aN - 1);
    for (int i = 1; i <= aN; ++i)
    {
      for (int j = 1; j <= aN; ++j)
      {
        (*aResult.V)(aColLower + i - 1, aColLower + j - 1) = aV(i, j);
      }
    }

    aResult.Status = Status::OK;
    return aResult;
  }

  inline LinearResult SolveSVD(const math_Matrix& theA,
                               const math_Vector& theB,
                               double             theTolerance = 1.0e-6)
  {
    LinearResult aResult;

    SVDResult aSVD = SVD(theA, theTolerance);
    if (!aSVD.IsDone())
    {
      aResult.Status = aSVD.Status;
      return aResult;
    }

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

    const int aBLower = theB.Lower();

    const math_Matrix& aU = *aSVD.U;
    const math_Vector& aW = *aSVD.SingularValues;
    const math_Matrix& aV = *aSVD.V;

    double aMaxSV = 0.0;
    for (int i = aColLower; i <= aColUpper; ++i)
    {
      aMaxSV = std::max(aMaxSV, aW(i));
    }
    double aWMin = theTolerance * aMaxSV;

    math_Vector aTmp(aColLower, aColUpper, 0.0);
    for (int j = aColLower; j <= aColUpper; ++j)
    {
      double aSum = 0.0;
      for (int i = aRowLower; i <= aRowUpper; ++i)
      {

        aSum += aU(i, j) * theB(aBLower + (i - aRowLower));
      }

      if (aW(j) > aWMin)
      {
        aTmp(j) = aSum / aW(j);
      }
    }

    aResult.Solution = math_Vector(aColLower, aColUpper, 0.0);
    for (int i = aColLower; i <= aColUpper; ++i)
    {
      double aSum = 0.0;
      for (int j = aColLower; j <= aColUpper; ++j)
      {
        aSum += aV(i, j) * aTmp(j);
      }
      (*aResult.Solution)(i) = aSum;
    }

    aResult.Status = Status::OK;
    return aResult;
  }

  inline InverseResult PseudoInverse(const math_Matrix& theA, double theTolerance = 1.0e-6)
  {
    InverseResult aResult;

    SVDResult aSVD = SVD(theA, theTolerance);
    if (!aSVD.IsDone())
    {
      aResult.Status = aSVD.Status;
      return aResult;
    }

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();

    const math_Matrix& aU = *aSVD.U;
    const math_Vector& aW = *aSVD.SingularValues;
    const math_Matrix& aV = *aSVD.V;

    double aMaxSV = 0.0;
    for (int i = aColLower; i <= aColUpper; ++i)
    {
      aMaxSV = std::max(aMaxSV, aW(i));
    }
    double aWMin = theTolerance * aMaxSV;

    aResult.Inverse = math_Matrix(aColLower, aColUpper, aRowLower, aRowUpper, 0.0);

    for (int i = aColLower; i <= aColUpper; ++i)
    {
      for (int j = aRowLower; j <= aRowUpper; ++j)
      {
        double aSum = 0.0;
        for (int k = aColLower; k <= aColUpper; ++k)
        {
          if (aW(k) > aWMin)
          {
            aSum += aV(i, k) * aU(j, k) / aW(k);
          }
        }
        (*aResult.Inverse)(i, j) = aSum;
      }
    }

    aResult.Status = Status::OK;
    return aResult;
  }

  inline double ConditionNumber(const math_Matrix& theA)
  {
    SVDResult aSVD = SVD(theA);
    if (!aSVD.IsDone())
    {
      return std::numeric_limits<double>::infinity();
    }

    const math_Vector& aW     = *aSVD.SingularValues;
    const int          aLower = aW.Lower();
    const int          aUpper = aW.Upper();

    double aMaxSV = 0.0;
    double aMinSV = std::numeric_limits<double>::max();

    for (int i = aLower; i <= aUpper; ++i)
    {
      if (aW(i) > 0.0)
      {
        aMaxSV = std::max(aMaxSV, aW(i));
        aMinSV = std::min(aMinSV, aW(i));
      }
    }

    if (aMinSV <= 0.0 || aMaxSV <= 0.0)
    {
      return std::numeric_limits<double>::infinity();
    }

    return aMaxSV / aMinSV;
  }

  inline int NumericalRank(const math_Matrix& theA, double theTolerance = 1.0e-15)
  {
    SVDResult aSVD = SVD(theA, theTolerance);
    return aSVD.IsDone() ? aSVD.Rank : 0;
  }

} // namespace MathLin
