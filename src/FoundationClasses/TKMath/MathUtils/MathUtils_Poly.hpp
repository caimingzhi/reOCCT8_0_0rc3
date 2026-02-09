#pragma once

#include <MathUtils_Core.hpp>

#include <cmath>
#include <array>

namespace MathUtils
{

  inline double EvalPoly(const double* theCoeffs, int theDegree, double theX)
  {
    double aResult = theCoeffs[theDegree];
    for (int i = theDegree - 1; i >= 0; --i)
    {
      aResult = aResult * theX + theCoeffs[i];
    }
    return aResult;
  }

  inline void EvalPolyDeriv(const double* theCoeffs,
                            int           theDegree,
                            double        theX,
                            double&       theValue,
                            double&       theDeriv)
  {
    theValue = theCoeffs[theDegree];
    theDeriv = 0.0;
    for (int i = theDegree - 1; i >= 0; --i)
    {
      theDeriv = theDeriv * theX + theValue;
      theValue = theValue * theX + theCoeffs[i];
    }
  }

  inline double EvalPolyDesc(const double* theCoeffs, int theDegree, double theX)
  {
    double aResult = theCoeffs[0];
    for (int i = 1; i <= theDegree; ++i)
    {
      aResult = aResult * theX + theCoeffs[i];
    }
    return aResult;
  }

  inline double RefinePolyRoot(const double* theCoeffs,
                               int           theDegree,
                               double        theRoot,
                               int           theMaxIter = 5)
  {
    double aX = theRoot;
    for (int i = 0; i < theMaxIter; ++i)
    {
      double aF  = 0.0;
      double aDf = 0.0;
      EvalPolyDeriv(theCoeffs, theDegree, aX, aF, aDf);

      if (IsZero(aDf))
      {
        break;
      }

      const double aDx = aF / aDf;
      aX -= aDx;

      if (std::abs(aDx) < THE_EPSILON * std::max(1.0, std::abs(aX)))
      {
        break;
      }
    }
    return aX;
  }

  inline double RefinePolyRootDesc(const double* theCoeffs,
                                   int           theDegree,
                                   double        theRoot,
                                   int           theMaxIter = 5)
  {

    std::array<double, 5> aAsc;
    for (int i = 0; i <= theDegree; ++i)
    {
      aAsc[i] = theCoeffs[theDegree - i];
    }
    return RefinePolyRoot(aAsc.data(), theDegree, theRoot, theMaxIter);
  }

  inline void SortRoots(double* theRoots, size_t theCount)
  {
    for (size_t i = 1; i < theCount; ++i)
    {
      const double aKey = theRoots[i];
      size_t       j    = i;
      while (j > 0 && theRoots[j - 1] > aKey)
      {
        theRoots[j] = theRoots[j - 1];
        --j;
      }
      theRoots[j] = aKey;
    }
  }

  inline size_t RemoveDuplicateRoots(double* theRoots,
                                     size_t  theCount,
                                     double  theTolerance = 1.0e-10)
  {
    if (theCount <= 1)
    {
      return theCount;
    }

    size_t aNewCount = 1;
    for (size_t i = 1; i < theCount; ++i)
    {
      if (std::abs(theRoots[i] - theRoots[aNewCount - 1]) > theTolerance)
      {
        theRoots[aNewCount] = theRoots[i];
        ++aNewCount;
      }
    }
    return aNewCount;
  }

  inline void DepressCubic(double  theB,
                           double  theC,
                           double  theD,
                           double& theP,
                           double& theQ,
                           double& theShift)
  {
    theShift         = theB / 3.0;
    const double aB2 = theB * theB;
    theP             = theC - aB2 / 3.0;
    theQ             = theD - theB * theC / 3.0 + 2.0 * aB2 * theB / 27.0;
  }

  inline void DepressQuartic(double  theB,
                             double  theC,
                             double  theD,
                             double  theE,
                             double& theP,
                             double& theQ,
                             double& theR,
                             double& theShift)
  {
    theShift         = theB / 4.0;
    const double aB2 = theB * theB;
    const double aB3 = aB2 * theB;
    const double aB4 = aB2 * aB2;

    theP = theC - 3.0 * aB2 / 8.0;
    theQ = theD - theB * theC / 2.0 + aB3 / 8.0;
    theR = theE - theB * theD / 4.0 + aB2 * theC / 16.0 - 3.0 * aB4 / 256.0;
  }

} // namespace MathUtils
