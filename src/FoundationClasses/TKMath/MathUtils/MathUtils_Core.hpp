#pragma once

#include <math_Vector.hpp>

#include <cmath>
#include <algorithm>
#include <limits>

namespace MathUtils
{

  inline constexpr double THE_EPSILON = std::numeric_limits<double>::epsilon();

  inline constexpr double THE_ZERO_TOL = 1.0e-15;

  inline constexpr double THE_PI = 3.14159265358979323846;

  inline constexpr double THE_2PI = 6.28318530717958647692;

  inline constexpr double THE_GOLDEN_RATIO = 1.618033988749895;

  inline constexpr double THE_GOLDEN_SECTION = 0.381966011250105;

  inline constexpr double Clamp(double theValue, double theLower, double theUpper)
  {
    return (theValue < theLower) ? theLower : ((theValue > theUpper) ? theUpper : theValue);
  }

  inline bool IsZero(double theValue, double theTolerance = THE_ZERO_TOL)
  {
    return std::abs(theValue) < theTolerance;
  }

  inline bool IsEqual(double theA, double theB, double theTolerance = THE_ZERO_TOL)
  {
    const double aDiff  = std::abs(theA - theB);
    const double aScale = std::max({1.0, std::abs(theA), std::abs(theB)});
    return aDiff < theTolerance * aScale;
  }

  inline double SafeDiv(double theNumerator, double theDenominator, double theDefault = 0.0)
  {
    return IsZero(theDenominator) ? theDefault : theNumerator / theDenominator;
  }

  inline int Sign(double theValue)
  {
    if (theValue > THE_ZERO_TOL)
      return 1;
    if (theValue < -THE_ZERO_TOL)
      return -1;
    return 0;
  }

  inline double SignTransfer(double theA, double theB)
  {
    return (theB >= 0.0) ? std::abs(theA) : -std::abs(theA);
  }

  inline constexpr double Sqr(double theValue)
  {
    return theValue * theValue;
  }

  inline constexpr double Cube(double theValue)
  {
    return theValue * theValue * theValue;
  }

  inline double CubeRoot(double theValue)
  {
    return (theValue >= 0.0) ? std::cbrt(theValue) : -std::cbrt(-theValue);
  }

  inline bool IsFinite(double theValue)
  {
    return std::isfinite(theValue);
  }

  inline double ComputeScaleFactor(const double* theCoeffs, int theCount)
  {
    double aMaxAbs = 0.0;
    for (int i = 0; i < theCount; ++i)
    {
      aMaxAbs = std::max(aMaxAbs, std::abs(theCoeffs[i]));
    }

    if (aMaxAbs < THE_ZERO_TOL || aMaxAbs > 1.0e15)
    {

      int anExp = 0;
      std::frexp(aMaxAbs, &anExp);
      return std::ldexp(1.0, -anExp + 1);
    }

    return 1.0;
  }

  inline double DotProduct(const math_Vector& theA, const math_Vector& theB)
  {
    double    aSum   = 0.0;
    const int aLower = theA.Lower();
    const int aUpper = theA.Upper();
    for (int i = aLower; i <= aUpper; ++i)
    {
      aSum += theA(i) * theB(i);
    }
    return aSum;
  }

  inline double VectorNorm(const math_Vector& theVec)
  {
    double aSum = 0.0;
    for (int i = theVec.Lower(); i <= theVec.Upper(); ++i)
    {
      aSum += theVec(i) * theVec(i);
    }
    return std::sqrt(aSum);
  }

  inline double VectorInfNorm(const math_Vector& theVec)
  {
    double aMax = 0.0;
    for (int i = theVec.Lower(); i <= theVec.Upper(); ++i)
    {
      aMax = std::max(aMax, std::abs(theVec(i)));
    }
    return aMax;
  }

} // namespace MathUtils
