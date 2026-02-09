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

  inline EigenResult Jacobi(const math_Matrix& theA, bool theSortDescending = true)
  {
    EigenResult aResult;

    const int aRowLower = theA.LowerRow();
    const int aRowUpper = theA.UpperRow();
    const int aColLower = theA.LowerCol();
    const int aColUpper = theA.UpperCol();
    const int aN        = aRowUpper - aRowLower + 1;

    if (aColUpper - aColLower + 1 != aN)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    math_Matrix aWorkA(1, aN, 1, aN);
    math_Vector aEigenVals(1, aN);
    math_Matrix aEigenVecs(1, aN, 1, aN);

    for (int i = aRowLower; i <= aRowUpper; ++i)
    {
      for (int j = aColLower; j <= aColUpper; ++j)
      {
        aWorkA(i - aRowLower + 1, j - aColLower + 1) = theA(i, j);
      }
    }

    int aNbRotations = 0;
    if (::Jacobi(aWorkA, aEigenVals, aEigenVecs, aNbRotations) != 0)
    {
      aResult.Status = Status::NotConverged;
      return aResult;
    }

    aResult.NbIterations = static_cast<size_t>(aNbRotations);

    if (theSortDescending && aN > 1)
    {

      for (int i = 1; i < aN; ++i)
      {
        int    aMaxIdx = i;
        double aMaxVal = aEigenVals(i);

        for (int j = i + 1; j <= aN; ++j)
        {
          if (aEigenVals(j) > aMaxVal)
          {
            aMaxVal = aEigenVals(j);
            aMaxIdx = j;
          }
        }

        if (aMaxIdx != i)
        {

          std::swap(aEigenVals(i), aEigenVals(aMaxIdx));

          for (int k = 1; k <= aN; ++k)
          {
            std::swap(aEigenVecs(k, i), aEigenVecs(k, aMaxIdx));
          }
        }
      }
    }

    aResult.EigenValues = math_Vector(aRowLower, aRowUpper);
    for (int i = 1; i <= aN; ++i)
    {
      (*aResult.EigenValues)(aRowLower + i - 1) = aEigenVals(i);
    }

    aResult.EigenVectors = math_Matrix(aRowLower, aRowUpper, aColLower, aColUpper);
    for (int i = 1; i <= aN; ++i)
    {
      for (int j = 1; j <= aN; ++j)
      {
        (*aResult.EigenVectors)(aRowLower + i - 1, aColLower + j - 1) = aEigenVecs(i, j);
      }
    }

    aResult.Status = Status::OK;
    return aResult;
  }

  inline EigenResult EigenValues(const math_Matrix& theA, bool theSortDescending = true)
  {

    return Jacobi(theA, theSortDescending);
  }

  inline EigenResult SpectralDecomposition(const math_Matrix& theA)
  {
    return Jacobi(theA, false);
  }

  inline std::optional<math_Matrix> MatrixPower(const math_Matrix& theA, double thePower)
  {
    EigenResult aEigen = Jacobi(theA, false);
    if (!aEigen.IsDone())
    {
      return std::nullopt;
    }

    const math_Vector& aD = *aEigen.EigenValues;
    const math_Matrix& aV = *aEigen.EigenVectors;

    const int aLower = aD.Lower();
    const int aUpper = aD.Upper();

    math_Vector aDp(aLower, aUpper);
    for (int i = aLower; i <= aUpper; ++i)
    {
      if (aD(i) < 0.0 && thePower != std::floor(thePower))
      {

        return std::nullopt;
      }
      aDp(i) = (aD(i) >= 0.0) ? std::pow(aD(i), thePower) : std::pow(-aD(i), thePower);
      if (aD(i) < 0.0 && static_cast<int>(thePower) % 2 != 0)
      {
        aDp(i) = -aDp(i);
      }
    }

    math_Matrix aResult(aLower, aUpper, aLower, aUpper, 0.0);
    for (int i = aLower; i <= aUpper; ++i)
    {
      for (int j = aLower; j <= aUpper; ++j)
      {
        double aSum = 0.0;
        for (int k = aLower; k <= aUpper; ++k)
        {
          aSum += aV(i, k) * aDp(k) * aV(j, k);
        }
        aResult(i, j) = aSum;
      }
    }

    return aResult;
  }

  inline std::optional<math_Matrix> MatrixSqrt(const math_Matrix& theA)
  {
    return MatrixPower(theA, 0.5);
  }

  inline std::optional<math_Matrix> MatrixInvSqrt(const math_Matrix& theA)
  {
    return MatrixPower(theA, -0.5);
  }

} // namespace MathLin
