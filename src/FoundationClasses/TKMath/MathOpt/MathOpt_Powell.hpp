#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <MathUtils_LineSearch.hpp>

#include <cmath>

namespace MathOpt
{
  using namespace MathUtils;

  template <typename Function>
  VectorResult Powell(Function&          theFunc,
                      const math_Vector& theStartingPoint,
                      const Config&      theConfig = Config())
  {
    VectorResult aResult;

    const int aLower = theStartingPoint.Lower();
    const int aUpper = theStartingPoint.Upper();
    const int aN     = aUpper - aLower + 1;

    math_Vector aX(aLower, aUpper);
    aX = theStartingPoint;

    double aFx = 0.0;
    if (!theFunc.Value(aX, aFx))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    math_Matrix aDirections(1, aN, 1, aN, 0.0);
    for (int i = 1; i <= aN; ++i)
    {
      aDirections(i, i) = 1.0;
    }

    math_Vector aDir(aLower, aUpper);
    math_Vector aXOld(aLower, aUpper);
    math_Vector aPt(aLower, aUpper);
    math_Vector aPtt(aLower, aUpper);
    math_Vector aXit(aLower, aUpper);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      const double aFp = aFx;
      aXOld            = aX;

      double aDel  = 0.0;
      int    aIBig = 0;

      for (int i = 1; i <= aN; ++i)
      {

        for (int j = aLower; j <= aUpper; ++j)
        {
          aDir(j) = aDirections(i, j - aLower + 1);
        }

        const double aFpPrev = aFx;

        MathUtils::LineSearchResult aLineResult =
          MathUtils::ExactLineSearch(theFunc, aX, aDir, 10.0, theConfig.XTolerance);

        if (aLineResult.IsValid)
        {

          for (int j = aLower; j <= aUpper; ++j)
          {
            aX(j) += aLineResult.Alpha * aDir(j);
          }
          aFx = aLineResult.FNew;

          const double aDecrease = aFpPrev - aFx;
          if (aDecrease > aDel)
          {
            aDel  = aDecrease;
            aIBig = i;
          }
        }
      }

      if (2.0 * std::abs(aFp - aFx)
          <= theConfig.FTolerance * (std::abs(aFp) + std::abs(aFx) + MathUtils::THE_ZERO_TOL))
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        return aResult;
      }

      for (int j = aLower; j <= aUpper; ++j)
      {
        aPtt(j) = 2.0 * aX(j) - aXOld(j);
        aXit(j) = aX(j) - aXOld(j);
      }

      double aFptt = 0.0;
      if (!theFunc.Value(aPtt, aFptt))
      {

        continue;
      }

      if (aFptt < aFp)
      {
        const double aT = 2.0 * (aFp - 2.0 * aFx + aFptt) * MathUtils::Sqr(aFp - aFx - aDel)
                          - aDel * MathUtils::Sqr(aFp - aFptt);

        if (aT < 0.0)
        {

          MathUtils::LineSearchResult aLineResult =
            MathUtils::ExactLineSearch(theFunc, aX, aXit, 10.0, theConfig.XTolerance);

          if (aLineResult.IsValid)
          {

            for (int j = aLower; j <= aUpper; ++j)
            {
              aX(j) += aLineResult.Alpha * aXit(j);
            }
            aFx = aLineResult.FNew;

            if (aIBig > 0)
            {
              for (int j = 1; j <= aN; ++j)
              {
                aDirections(aIBig, j) = aDirections(aN, j);
                aDirections(aN, j)    = aXit(aLower + j - 1);
              }
            }
          }
        }
      }

      double aMaxDiff = 0.0;
      for (int j = aLower; j <= aUpper; ++j)
      {
        aMaxDiff = std::max(aMaxDiff, std::abs(aX(j) - aXOld(j)));
      }
      if (aMaxDiff < theConfig.XTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        return aResult;
      }
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aX;
    aResult.Value    = aFx;
    return aResult;
  }

  template <typename Function>
  VectorResult PowellWithDirections(Function&          theFunc,
                                    const math_Vector& theStartingPoint,
                                    const math_Matrix& theInitialDirections,
                                    const Config&      theConfig = Config())
  {
    VectorResult aResult;

    const int aLower = theStartingPoint.Lower();
    const int aUpper = theStartingPoint.Upper();
    const int aN     = aUpper - aLower + 1;

    if (theInitialDirections.RowNumber() != aN || theInitialDirections.ColNumber() != aN)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    math_Vector aX(aLower, aUpper);
    aX = theStartingPoint;

    double aFx = 0.0;
    if (!theFunc.Value(aX, aFx))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    math_Matrix aDirections(1, aN, 1, aN);
    aDirections = theInitialDirections;

    math_Vector aDir(aLower, aUpper);
    math_Vector aXOld(aLower, aUpper);
    math_Vector aPtt(aLower, aUpper);
    math_Vector aXit(aLower, aUpper);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      const double aFp = aFx;
      aXOld            = aX;

      double aDel  = 0.0;
      int    aIBig = 0;

      for (int i = 1; i <= aN; ++i)
      {
        for (int j = aLower; j <= aUpper; ++j)
        {
          aDir(j) = aDirections(i, j - aLower + 1);
        }

        const double aFpPrev = aFx;

        MathUtils::LineSearchResult aLineResult =
          MathUtils::ExactLineSearch(theFunc, aX, aDir, 10.0, theConfig.XTolerance);

        if (aLineResult.IsValid)
        {
          for (int j = aLower; j <= aUpper; ++j)
          {
            aX(j) += aLineResult.Alpha * aDir(j);
          }
          aFx = aLineResult.FNew;

          const double aDecrease = aFpPrev - aFx;
          if (aDecrease > aDel)
          {
            aDel  = aDecrease;
            aIBig = i;
          }
        }
      }

      if (2.0 * std::abs(aFp - aFx)
          <= theConfig.FTolerance * (std::abs(aFp) + std::abs(aFx) + MathUtils::THE_ZERO_TOL))
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        return aResult;
      }

      for (int j = aLower; j <= aUpper; ++j)
      {
        aPtt(j) = 2.0 * aX(j) - aXOld(j);
        aXit(j) = aX(j) - aXOld(j);
      }

      double aFptt = 0.0;
      if (!theFunc.Value(aPtt, aFptt))
      {
        continue;
      }

      if (aFptt < aFp)
      {
        const double aT = 2.0 * (aFp - 2.0 * aFx + aFptt) * MathUtils::Sqr(aFp - aFx - aDel)
                          - aDel * MathUtils::Sqr(aFp - aFptt);

        if (aT < 0.0)
        {
          MathUtils::LineSearchResult aLineResult =
            MathUtils::ExactLineSearch(theFunc, aX, aXit, 10.0, theConfig.XTolerance);

          if (aLineResult.IsValid)
          {
            for (int j = aLower; j <= aUpper; ++j)
            {
              aX(j) += aLineResult.Alpha * aXit(j);
            }
            aFx = aLineResult.FNew;

            if (aIBig > 0)
            {
              for (int j = 1; j <= aN; ++j)
              {
                aDirections(aIBig, j) = aDirections(aN, j);
                aDirections(aN, j)    = aXit(aLower + j - 1);
              }
            }
          }
        }
      }

      double aMaxDiff = 0.0;
      for (int j = aLower; j <= aUpper; ++j)
      {
        aMaxDiff = std::max(aMaxDiff, std::abs(aX(j) - aXOld(j)));
      }
      if (aMaxDiff < theConfig.XTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        return aResult;
      }
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aX;
    aResult.Value    = aFx;
    return aResult;
  }

} // namespace MathOpt
