#pragma once

#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <math_Vector.hpp>

#include <cmath>

namespace MathUtils
{

  inline bool IsXConverged(double theXOld, double theXNew, double theTolerance)
  {
    const double aDiff  = std::abs(theXNew - theXOld);
    const double aScale = std::max(1.0, std::abs(theXNew));
    return aDiff < theTolerance * aScale;
  }

  inline bool IsFConverged(double theFValue, double theTolerance)
  {
    return std::abs(theFValue) < theTolerance;
  }

  inline bool IsConverged(double theXOld, double theXNew, double theFValue, const Config& theConfig)
  {
    return IsXConverged(theXOld, theXNew, theConfig.XTolerance)
           || IsFConverged(theFValue, theConfig.FTolerance);
  }

  inline bool IsMinConverged(double        theXOld,
                             double        theXNew,
                             double        theFOld,
                             double        theFNew,
                             const Config& theConfig)
  {

    if (IsXConverged(theXOld, theXNew, theConfig.XTolerance))
    {
      return true;
    }

    const double aFDiff  = std::abs(theFNew - theFOld);
    const double aFScale = std::max(1.0, std::abs(theFNew));
    return aFDiff < theConfig.FTolerance * aFScale;
  }

  inline bool IsVectorConverged(const math_Vector& theOld,
                                const math_Vector& theNew,
                                double             theTolerance)
  {
    double aMaxDiff  = 0.0;
    double aMaxScale = 1.0;
    for (int i = theOld.Lower(); i <= theOld.Upper(); ++i)
    {
      aMaxDiff  = std::max(aMaxDiff, std::abs(theNew(i) - theOld(i)));
      aMaxScale = std::max(aMaxScale, std::abs(theNew(i)));
    }
    return aMaxDiff < theTolerance * aMaxScale;
  }

  inline bool IsGradientConverged(const math_Vector& theGradient, double theTolerance)
  {
    double aNormSq = 0.0;
    for (int i = theGradient.Lower(); i <= theGradient.Upper(); ++i)
    {
      aNormSq += Sqr(theGradient(i));
    }
    return std::sqrt(aNormSq) < theTolerance;
  }

  inline double InfinityNorm(const math_Vector& theVector)
  {
    double aMax = 0.0;
    for (int i = theVector.Lower(); i <= theVector.Upper(); ++i)
    {
      aMax = std::max(aMax, std::abs(theVector(i)));
    }
    return aMax;
  }

  inline double EuclideanNorm(const math_Vector& theVector)
  {
    double aSumSq = 0.0;
    for (int i = theVector.Lower(); i <= theVector.Upper(); ++i)
    {
      aSumSq += Sqr(theVector(i));
    }
    return std::sqrt(aSumSq);
  }

} // namespace MathUtils
