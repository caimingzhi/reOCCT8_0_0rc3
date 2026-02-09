#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <MathUtils_Convergence.hpp>

#include <cmath>

namespace MathRoot
{
  using namespace MathUtils;

  template <typename Function>
  MathUtils::ScalarResult Newton(Function&                theFunc,
                                 double                   theGuess,
                                 const MathUtils::Config& theConfig = MathUtils::Config())
  {
    MathUtils::ScalarResult aResult;
    double                  aX   = theGuess;
    double                  aFx  = 0.0;
    double                  aDfx = 0.0;

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      const double anXOld = aX;

      if (!theFunc.Values(aX, aFx, aDfx))
      {
        aResult.Status       = MathUtils::Status::NumericalError;
        aResult.Root         = aX;
        aResult.NbIterations = anIter;
        return aResult;
      }

      if (MathUtils::IsZero(aDfx))
      {

        if (!MathUtils::IsFConverged(aFx, theConfig.FTolerance))
        {
          aResult.Status       = MathUtils::Status::NumericalError;
          aResult.Root         = aX;
          aResult.Value        = aFx;
          aResult.Derivative   = aDfx;
          aResult.NbIterations = anIter;
          return aResult;
        }
      }
      else
      {

        aX -= aFx / aDfx;
      }

      aResult.NbIterations = anIter + 1;

      if (MathUtils::IsConverged(anXOld, aX, aFx, theConfig))
      {
        aResult.Status     = MathUtils::Status::OK;
        aResult.Root       = aX;
        aResult.Value      = aFx;
        aResult.Derivative = aDfx;
        return aResult;
      }
    }

    aResult.Status     = MathUtils::Status::MaxIterations;
    aResult.Root       = aX;
    aResult.Value      = aFx;
    aResult.Derivative = aDfx;
    return aResult;
  }

  template <typename Function>
  MathUtils::ScalarResult NewtonBounded(Function&                theFunc,
                                        double                   theGuess,
                                        double                   theLower,
                                        double                   theUpper,
                                        const MathUtils::Config& theConfig = MathUtils::Config())
  {
    MathUtils::ScalarResult aResult;

    double aX   = MathUtils::Clamp(theGuess, theLower, theUpper);
    double aXLo = theLower;
    double aXHi = theUpper;

    double aFx    = 0.0;
    double aDfx   = 0.0;
    double aFLo   = 0.0;
    double aFHi   = 0.0;
    double aDummy = 0.0;

    if (!theFunc.Values(aXLo, aFLo, aDummy))
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }
    if (!theFunc.Values(aXHi, aFHi, aDummy))
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }

    const bool aBracketed = (aFLo * aFHi < 0.0);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      const double anXOld = aX;

      if (!theFunc.Values(aX, aFx, aDfx))
      {
        aResult.Status       = MathUtils::Status::NumericalError;
        aResult.Root         = aX;
        aResult.NbIterations = anIter;
        return aResult;
      }

      aResult.NbIterations = anIter + 1;

      if (MathUtils::IsFConverged(aFx, theConfig.FTolerance))
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

      if (aXNew < aXLo || aXNew > aXHi)
      {

        if (aBracketed)
        {
          aXNew = 0.5 * (aXLo + aXHi);
        }
        else
        {

          aXNew = MathUtils::Clamp(aXNew, aXLo, aXHi);
        }
      }

      aX = aXNew;

      if (aBracketed)
      {
        if (aFx * aFLo < 0.0)
        {
          aXHi = anXOld;
          aFHi = aFx;
        }
        else
        {
          aXLo = anXOld;
          aFLo = aFx;
        }
      }

      if (MathUtils::IsXConverged(anXOld, aX, theConfig.XTolerance))
      {

        theFunc.Values(aX, aFx, aDfx);
        aResult.Status     = MathUtils::Status::OK;
        aResult.Root       = aX;
        aResult.Value      = aFx;
        aResult.Derivative = aDfx;
        return aResult;
      }
    }

    aResult.Status     = MathUtils::Status::MaxIterations;
    aResult.Root       = aX;
    aResult.Value      = aFx;
    aResult.Derivative = aDfx;
    return aResult;
  }

} // namespace MathRoot
