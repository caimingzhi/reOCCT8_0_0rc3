#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>

#include <cmath>
#include <utility>

namespace MathRoot
{
  using namespace MathUtils;

  template <typename Function>
  MathUtils::ScalarResult Bisection(Function&                theFunc,
                                    double                   theLower,
                                    double                   theUpper,
                                    const MathUtils::Config& theConfig = MathUtils::Config())
  {
    MathUtils::ScalarResult aResult;

    double aA  = theLower;
    double aB  = theUpper;
    double aFa = 0.0;
    double aFb = 0.0;

    if (!theFunc.Value(aA, aFa))
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }
    if (!theFunc.Value(aB, aFb))
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }

    if (aFa * aFb > 0.0)
    {
      aResult.Status = MathUtils::Status::InvalidInput;
      return aResult;
    }

    if (aA > aB)
    {
      std::swap(aA, aB);
      std::swap(aFa, aFb);
    }

    bool aIsNegAtA = (aFa < 0.0);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {

      const double aM  = 0.5 * (aA + aB);
      double       aFm = 0.0;

      if (!theFunc.Value(aM, aFm))
      {
        aResult.Status       = MathUtils::Status::NumericalError;
        aResult.Root         = aM;
        aResult.NbIterations = anIter + 1;
        return aResult;
      }

      aResult.NbIterations = anIter + 1;

      if (std::abs(aFm) < theConfig.FTolerance)
      {
        aResult.Status = MathUtils::Status::OK;
        aResult.Root   = aM;
        aResult.Value  = aFm;
        return aResult;
      }

      if ((aB - aA) < theConfig.XTolerance * std::max(1.0, std::abs(aM)))
      {
        aResult.Status = MathUtils::Status::OK;
        aResult.Root   = aM;
        aResult.Value  = aFm;
        return aResult;
      }

      const bool aIsNegAtM = (aFm < 0.0);
      if (aIsNegAtM == aIsNegAtA)
      {

        aA  = aM;
        aFa = aFm;
      }
      else
      {

        aB  = aM;
        aFb = aFm;
      }
    }

    aResult.Status = MathUtils::Status::MaxIterations;
    aResult.Root   = 0.5 * (aA + aB);
    aResult.Value  = 0.0;
    theFunc.Value(*aResult.Root, *aResult.Value);
    return aResult;
  }

  template <typename Function>
  MathUtils::ScalarResult BisectionNewton(Function&                theFunc,
                                          double                   theLower,
                                          double                   theUpper,
                                          const MathUtils::Config& theConfig = MathUtils::Config())
  {
    MathUtils::ScalarResult aResult;

    double aA     = theLower;
    double aB     = theUpper;
    double aFa    = 0.0;
    double aFb    = 0.0;
    double aDummy = 0.0;

    if (!theFunc.Values(aA, aFa, aDummy))
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }
    if (!theFunc.Values(aB, aFb, aDummy))
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }

    if (aFa * aFb > 0.0)
    {
      aResult.Status = MathUtils::Status::InvalidInput;
      return aResult;
    }

    if (aA > aB)
    {
      std::swap(aA, aB);
      std::swap(aFa, aFb);
    }

    bool aIsNegAtA = (aFa < 0.0);

    double aX   = 0.5 * (aA + aB);
    double aFx  = 0.0;
    double aDfx = 0.0;

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      if (!theFunc.Values(aX, aFx, aDfx))
      {
        aResult.Status       = MathUtils::Status::NumericalError;
        aResult.Root         = aX;
        aResult.NbIterations = anIter + 1;
        return aResult;
      }

      aResult.NbIterations = anIter + 1;

      if (std::abs(aFx) < theConfig.FTolerance)
      {
        aResult.Status     = MathUtils::Status::OK;
        aResult.Root       = aX;
        aResult.Value      = aFx;
        aResult.Derivative = aDfx;
        return aResult;
      }

      if ((aB - aA) < theConfig.XTolerance * std::max(1.0, std::abs(aX)))
      {
        aResult.Status     = MathUtils::Status::OK;
        aResult.Root       = aX;
        aResult.Value      = aFx;
        aResult.Derivative = aDfx;
        return aResult;
      }

      double aXNew = aX;
      if (!MathUtils::IsZero(aDfx))
      {
        aXNew = aX - aFx / aDfx;
      }

      if (aXNew <= aA || aXNew >= aB)
      {

        aXNew = 0.5 * (aA + aB);
      }

      const bool aIsNegAtX = (aFx < 0.0);
      if (aIsNegAtX == aIsNegAtA)
      {

        aA = aX;
      }
      else
      {

        aB = aX;
      }

      aX = aXNew;
    }

    aResult.Status     = MathUtils::Status::MaxIterations;
    aResult.Root       = aX;
    aResult.Value      = 0.0;
    aResult.Derivative = 0.0;
    theFunc.Values(*aResult.Root, *aResult.Value, *aResult.Derivative);
    return aResult;
  }

} // namespace MathRoot
