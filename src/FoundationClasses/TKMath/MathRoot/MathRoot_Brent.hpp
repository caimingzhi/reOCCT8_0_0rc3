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
  MathUtils::ScalarResult Brent(Function&                theFunc,
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

    if (std::abs(aFa) < std::abs(aFb))
    {
      std::swap(aA, aB);
      std::swap(aFa, aFb);
    }

    double aC  = aA;
    double aFc = aFa;
    double aD  = aB - aA;
    double aE  = aD;

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      if (std::abs(aFb) < theConfig.FTolerance)
      {
        aResult.Status = MathUtils::Status::OK;
        aResult.Root   = aB;
        aResult.Value  = aFb;
        return aResult;
      }

      if (std::abs(aB - aA) < theConfig.XTolerance * std::max(1.0, std::abs(aB)))
      {
        aResult.Status = MathUtils::Status::OK;
        aResult.Root   = aB;
        aResult.Value  = aFb;
        return aResult;
      }

      double aS = 0.0;

      if (std::abs(aFa - aFc) > MathUtils::THE_ZERO_TOL
          && std::abs(aFb - aFc) > MathUtils::THE_ZERO_TOL)
      {

        aS = aA * aFb * aFc / ((aFa - aFb) * (aFa - aFc))
             + aB * aFa * aFc / ((aFb - aFa) * (aFb - aFc))
             + aC * aFa * aFb / ((aFc - aFa) * (aFc - aFb));
      }
      else
      {

        aS = aB - aFb * (aB - aA) / (aFb - aFa);
      }

      const double aTol = 2.0 * MathUtils::THE_EPSILON * std::abs(aB) + 0.5 * theConfig.XTolerance;
      const double aM   = 0.5 * (aC - aB);

      bool aUseInterp = false;

      const double aBound1 = (3.0 * aA + aB) / 4.0;
      if ((aS > std::min(aBound1, aB) && aS < std::max(aBound1, aB)))
      {

        if (std::abs(aS - aB) < std::abs(aE) / 2.0)
        {
          aUseInterp = true;
        }
      }

      if (!aUseInterp)
      {

        aS = aB + aM;
        aE = aM;
        aD = aM;
      }
      else
      {
        aE = aD;
        aD = aS - aB;
      }

      aA  = aB;
      aFa = aFb;

      if (std::abs(aD) > aTol)
      {
        aB = aS;
      }
      else
      {
        aB += (aM > 0.0) ? aTol : -aTol;
      }

      if (!theFunc.Value(aB, aFb))
      {
        aResult.Status = MathUtils::Status::NumericalError;
        aResult.Root   = aB;
        return aResult;
      }

      if (aFb * aFc > 0.0)
      {
        aC  = aA;
        aFc = aFa;
        aD  = aB - aA;
        aE  = aD;
      }
      else if (std::abs(aFc) < std::abs(aFb))
      {

        aA  = aB;
        aFa = aFb;
        std::swap(aB, aC);
        std::swap(aFb, aFc);
      }
    }

    aResult.Status = MathUtils::Status::MaxIterations;
    aResult.Root   = aB;
    aResult.Value  = aFb;
    return aResult;
  }

} // namespace MathRoot
