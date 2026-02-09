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
  MathUtils::ScalarResult Secant(Function&                theFunc,
                                 double                   theX0,
                                 double                   theX1,
                                 const MathUtils::Config& theConfig = MathUtils::Config())
  {
    MathUtils::ScalarResult aResult;

    double aX0 = theX0;
    double aX1 = theX1;
    double aF0 = 0.0;
    double aF1 = 0.0;

    if (!theFunc.Value(aX0, aF0))
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }
    if (!theFunc.Value(aX1, aF1))
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      if (MathUtils::IsFConverged(aF1, theConfig.FTolerance))
      {
        aResult.Status = MathUtils::Status::OK;
        aResult.Root   = aX1;
        aResult.Value  = aF1;
        return aResult;
      }

      const double aDenom = aF1 - aF0;
      if (MathUtils::IsZero(aDenom))
      {
        aResult.Status = MathUtils::Status::NumericalError;
        aResult.Root   = aX1;
        aResult.Value  = aF1;
        return aResult;
      }

      const double aXNew = aX1 - aF1 * (aX1 - aX0) / aDenom;

      if (MathUtils::IsXConverged(aX1, aXNew, theConfig.XTolerance))
      {
        double aFNew = 0.0;
        theFunc.Value(aXNew, aFNew);
        aResult.Status = MathUtils::Status::OK;
        aResult.Root   = aXNew;
        aResult.Value  = aFNew;
        return aResult;
      }

      aX0 = aX1;
      aF0 = aF1;
      aX1 = aXNew;

      if (!theFunc.Value(aX1, aF1))
      {
        aResult.Status = MathUtils::Status::NumericalError;
        aResult.Root   = aX1;
        return aResult;
      }
    }

    aResult.Status = MathUtils::Status::MaxIterations;
    aResult.Root   = aX1;
    aResult.Value  = aF1;
    return aResult;
  }

  template <typename Function>
  MathUtils::ScalarResult SecantAuto(Function&                theFunc,
                                     double                   theX0,
                                     const MathUtils::Config& theConfig = MathUtils::Config())
  {

    const double aDelta = (std::abs(theX0) > 1.0) ? 0.01 * theX0 : 0.01;
    return Secant(theFunc, theX0, theX0 + aDelta, theConfig);
  }

} // namespace MathRoot
