#pragma once

#include <BSplCLib.hpp>

#include <algorithm>
#include <cmath>

struct BSplCLib_CacheParams
{
  const int    Degree;
  const bool   IsPeriodic;
  const double FirstParameter;
  const double LastParameter;

  const int SpanIndexMin;
  const int SpanIndexMax;

  double SpanStart;
  double SpanLength;
  int    SpanIndex;

  BSplCLib_CacheParams(int                               theDegree,
                       bool                              thePeriodic,
                       const NCollection_Array1<double>& theFlatKnots)
      : Degree(theDegree),
        IsPeriodic(thePeriodic),
        FirstParameter(theFlatKnots.Value(theFlatKnots.Lower() + theDegree)),
        LastParameter(theFlatKnots.Value(theFlatKnots.Upper() - theDegree)),
        SpanIndexMin(theFlatKnots.Lower() + theDegree),
        SpanIndexMax(theFlatKnots.Upper() - theDegree - 1),
        SpanStart(0.0),
        SpanLength(0.0),
        SpanIndex(0)
  {
  }

  double PeriodicNormalization(double theParameter) const noexcept
  {
    if (IsPeriodic)
    {
      const double aPeriod = LastParameter - FirstParameter;
      if (theParameter < FirstParameter)
      {
        const double aScale = std::trunc((FirstParameter - theParameter) / aPeriod);
        return theParameter + aPeriod * (aScale + 1.0);
      }
      if (theParameter > LastParameter)
      {
        const double aScale = std::trunc((theParameter - LastParameter) / aPeriod);
        return theParameter - aPeriod * (aScale + 1.0);
      }
    }
    return theParameter;
  }

  bool IsCacheValid(double theParameter) const noexcept
  {
    const double aNewParam = PeriodicNormalization(theParameter);
    const double aDelta    = aNewParam - SpanStart;
    if ((aDelta < 0.0 && SpanIndex != SpanIndexMin)
        || (aDelta >= SpanLength && SpanIndex != SpanIndexMax))
    {
      return false;
    }

    if (SpanIndex == SpanIndexMax)
      return true;

    const double anEps        = Epsilon((std::min)(std::fabs(LastParameter), std::fabs(aNewParam)));
    const double aDeltaToNext = std::fabs(aDelta - SpanLength);
    return aDeltaToNext > anEps;
  }

  void LocateParameter(double& theParameter, const NCollection_Array1<double>& theFlatKnots)
  {
    SpanIndex = 0;
    BSplCLib::LocateParameter(Degree,
                              theFlatKnots,
                              BSplCLib::NoMults(),
                              theParameter,
                              IsPeriodic,
                              SpanIndex,
                              theParameter);
    SpanStart  = theFlatKnots.Value(SpanIndex);
    SpanLength = theFlatKnots.Value(SpanIndex + 1) - SpanStart;
  }

  BSplCLib_CacheParams(const BSplCLib_CacheParams&)            = delete;
  BSplCLib_CacheParams& operator=(const BSplCLib_CacheParams&) = delete;
};
