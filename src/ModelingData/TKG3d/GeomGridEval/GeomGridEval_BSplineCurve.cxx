

#include <GeomGridEval_BSplineCurve.hpp>

#include <BSplCLib.hpp>
#include <BSplCLib_Cache.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

namespace
{

  constexpr int THE_CACHE_THRESHOLD = 4;

  struct ParamWithSpan
  {
    double Param;
    double LocalParam;
    int    SpanIndex;
    int    OrigIdx;
  };

  struct SpanRange
  {
    int    SpanIndex;
    int    StartIdx;
    int    EndIdx;
    double SpanMid;
  };

  struct PreparedParams
  {
    NCollection_Array1<ParamWithSpan> Params;
    NCollection_Array1<SpanRange>     Ranges;
  };

  int locateSpan(double                            theParam,
                 int                               theDegree,
                 bool                              theIsPeriodic,
                 const NCollection_Array1<double>& theFlatKnots)
  {
    int    aSpanIndex = 0;
    double aNewParam  = theParam;
    BSplCLib::LocateParameter(theDegree,
                              theFlatKnots,
                              BSplCLib::NoMults(),
                              theParam,
                              theIsPeriodic,
                              aSpanIndex,
                              aNewParam);
    return aSpanIndex;
  }

  int locateSpanWithHint(double                            theParam,
                         int                               theHint,
                         int                               theDegree,
                         bool                              theIsPeriodic,
                         const NCollection_Array1<double>& theFlatKnots)
  {
    const int aLower = theFlatKnots.Lower() + theDegree;
    const int aUpper = theFlatKnots.Upper() - theDegree - 1;

    if (theHint >= aLower && theHint <= aUpper)
    {
      const double aSpanStart = theFlatKnots.Value(theHint);
      const double aSpanEnd   = theFlatKnots.Value(theHint + 1);

      if (theParam >= aSpanStart && theParam < aSpanEnd)
      {
        return theHint;
      }

      if (theHint < aUpper && theParam >= aSpanEnd)
      {
        const double aNextEnd = theFlatKnots.Value(theHint + 2);
        if (theParam < aNextEnd)
        {
          return theHint + 1;
        }
      }
    }

    return locateSpan(theParam, theDegree, theIsPeriodic, theFlatKnots);
  }

  [[nodiscard]] PreparedParams prepareParams(const NCollection_Array1<double>& theParams,
                                             int                               theDegree,
                                             bool                              theIsPeriodic,
                                             const NCollection_Array1<double>& theFlatKnots)
  {
    PreparedParams aResult;
    const int      aNbParams = theParams.Size();
    aResult.Params.Resize(0, aNbParams - 1, false);

    int aPrevSpan = theFlatKnots.Lower() + theDegree;

    for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
    {
      const double aParam = theParams.Value(i);
      const int    aSpanIdx =
        locateSpanWithHint(aParam, aPrevSpan, theDegree, theIsPeriodic, theFlatKnots);
      aPrevSpan = aSpanIdx;

      const double aSpanStart  = theFlatKnots.Value(aSpanIdx);
      const double aSpanLength = theFlatKnots.Value(aSpanIdx + 1) - aSpanStart;
      const double aLocalParam = (aSpanLength > 0.0) ? (aParam - aSpanStart) / aSpanLength : 0.0;

      const int aIdx = i - theParams.Lower();
      aResult.Params.SetValue(aIdx, ParamWithSpan{aParam, aLocalParam, aSpanIdx, aIdx});
    }

    int aNbSpans     = 1;
    int aCurrentSpan = aResult.Params.Value(0).SpanIndex;
    for (int i = 1; i < aNbParams; ++i)
    {
      if (aResult.Params.Value(i).SpanIndex != aCurrentSpan)
      {
        ++aNbSpans;
        aCurrentSpan = aResult.Params.Value(i).SpanIndex;
      }
    }

    aResult.Ranges.Resize(0, aNbSpans - 1, false);

    aCurrentSpan    = aResult.Params.Value(0).SpanIndex;
    int aRangeStart = 0;
    int aRangeIdx   = 0;

    for (int i = 1; i < aNbParams; ++i)
    {
      const int aSpan = aResult.Params.Value(i).SpanIndex;
      if (aSpan != aCurrentSpan)
      {
        const double aSpanStart  = theFlatKnots.Value(aCurrentSpan);
        const double aSpanLength = theFlatKnots.Value(aCurrentSpan + 1) - aSpanStart;
        const double aSpanMid    = aSpanStart + aSpanLength * 0.5;

        aResult.Ranges.SetValue(aRangeIdx, SpanRange{aCurrentSpan, aRangeStart, i, aSpanMid});
        ++aRangeIdx;
        aCurrentSpan = aSpan;
        aRangeStart  = i;
      }
    }

    const double aSpanStart  = theFlatKnots.Value(aCurrentSpan);
    const double aSpanLength = theFlatKnots.Value(aCurrentSpan + 1) - aSpanStart;
    const double aSpanMid    = aSpanStart + aSpanLength * 0.5;

    aResult.Ranges.SetValue(aRangeIdx, SpanRange{aCurrentSpan, aRangeStart, aNbParams, aSpanMid});

    return aResult;
  }

  template <typename BuildCacheFunc, typename CacheEvalFunc, typename DirectEvalFunc>
  void iterateSpanBlocks(const NCollection_Array1<SpanRange>&     theSpanRanges,
                         const NCollection_Array1<ParamWithSpan>& theParams,
                         BuildCacheFunc&&                         theBuildCache,
                         CacheEvalFunc&&                          theCacheEval,
                         DirectEvalFunc&&                         theDirectEval)
  {
    const int aNbRanges = theSpanRanges.Size();
    for (int iRange = 0; iRange < aNbRanges; ++iRange)
    {
      const auto& aRange    = theSpanRanges.Value(iRange);
      const int   aNbInSpan = aRange.EndIdx - aRange.StartIdx;

      if (aNbInSpan >= THE_CACHE_THRESHOLD)
      {

        theBuildCache(theParams.Value(aRange.StartIdx).Param);

        for (int i = aRange.StartIdx; i < aRange.EndIdx; ++i)
        {
          const auto& aP = theParams.Value(i);
          theCacheEval(aP.OrigIdx, aP.LocalParam);
        }
      }
      else
      {

        const int aSpanIdx = aRange.SpanIndex;
        for (int i = aRange.StartIdx; i < aRange.EndIdx; ++i)
        {
          const auto& aP = theParams.Value(i);
          theDirectEval(aP.OrigIdx, aP.Param, aSpanIdx);
        }
      }
    }
  }

} // namespace

NCollection_Array1<gp_Pnt> GeomGridEval_BSplineCurve::EvaluateGrid(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const occ::handle<NCollection_HArray1<double>>& aFlatKnotsHandle = myGeom->HArrayFlatKnots();
  if (aFlatKnotsHandle.IsNull())
  {
    return NCollection_Array1<gp_Pnt>();
  }
  const NCollection_Array1<double>& aFlatKnots = aFlatKnotsHandle->Array1();

  const occ::handle<NCollection_HArray1<gp_Pnt>>& aPolesHandle = myGeom->HArrayPoles();
  if (aPolesHandle.IsNull())
  {
    return NCollection_Array1<gp_Pnt>();
  }
  const NCollection_Array1<gp_Pnt>& aPoles = aPolesHandle->Array1();

  const occ::handle<NCollection_HArray1<double>>& aWeightsHandle = myGeom->HArrayWeights();
  const bool                                      isRational     = myGeom->IsRational();
  if (isRational && aWeightsHandle.IsNull())
  {
    return NCollection_Array1<gp_Pnt>();
  }
  const NCollection_Array1<double>* aWeights = isRational ? &aWeightsHandle->Array1() : nullptr;

  const int  aDegree    = myGeom->Degree();
  const bool isPeriodic = myGeom->IsPeriodic();

  PreparedParams aPrepared = prepareParams(theParams, aDegree, isPeriodic, aFlatKnots);

  const int                  aNbParams = theParams.Size();
  NCollection_Array1<gp_Pnt> aPoints(1, aNbParams);

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, isPeriodic, aFlatKnots, aPoles, aWeights);

  iterateSpanBlocks(
    aPrepared.Ranges,
    aPrepared.Params,
    [&](double theParam) { aCache->BuildCache(theParam, aFlatKnots, aPoles, aWeights); },

    [&](int theIdx, double theLocalParam)
    { aCache->D0Local(theLocalParam, aPoints.ChangeValue(theIdx + 1)); },

    [&](int theIdx, double theParam, int theSpanIdx)
    {
      gp_Pnt aPoint;
      BSplCLib::D0(theParam,
                   theSpanIdx,
                   aDegree,
                   isPeriodic,
                   aPoles,
                   aWeights,
                   aFlatKnots,
                   nullptr,
                   aPoint);
      aPoints.ChangeValue(theIdx + 1) = aPoint;
    });

  return aPoints;
}

NCollection_Array1<GeomGridEval::CurveD1> GeomGridEval_BSplineCurve::EvaluateGridD1(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }

  const occ::handle<NCollection_HArray1<double>>& aFlatKnotsHandle = myGeom->HArrayFlatKnots();
  if (aFlatKnotsHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }
  const NCollection_Array1<double>& aFlatKnots = aFlatKnotsHandle->Array1();

  const occ::handle<NCollection_HArray1<gp_Pnt>>& aPolesHandle = myGeom->HArrayPoles();
  if (aPolesHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }
  const NCollection_Array1<gp_Pnt>& aPoles = aPolesHandle->Array1();

  const occ::handle<NCollection_HArray1<double>>& aWeightsHandle = myGeom->HArrayWeights();
  const bool                                      isRational     = myGeom->IsRational();
  if (isRational && aWeightsHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }
  const NCollection_Array1<double>* aWeights = isRational ? &aWeightsHandle->Array1() : nullptr;

  const int  aDegree    = myGeom->Degree();
  const bool isPeriodic = myGeom->IsPeriodic();

  PreparedParams aPrepared = prepareParams(theParams, aDegree, isPeriodic, aFlatKnots);

  const int                                 aNbParams = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD1> aResults(1, aNbParams);

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, isPeriodic, aFlatKnots, aPoles, aWeights);

  iterateSpanBlocks(
    aPrepared.Ranges,
    aPrepared.Params,
    [&](double theParam) { aCache->BuildCache(theParam, aFlatKnots, aPoles, aWeights); },
    [&](int theIdx, double theLocalParam)
    {
      gp_Pnt aPoint;
      gp_Vec aD1;
      aCache->D1Local(theLocalParam, aPoint, aD1);
      aResults.ChangeValue(theIdx + 1) = {aPoint, aD1};
    },
    [&](int theIdx, double theParam, int theSpanIdx)
    {
      gp_Pnt aPoint;
      gp_Vec aD1;
      BSplCLib::D1(theParam,
                   theSpanIdx,
                   aDegree,
                   isPeriodic,
                   aPoles,
                   aWeights,
                   aFlatKnots,
                   nullptr,
                   aPoint,
                   aD1);
      aResults.ChangeValue(theIdx + 1) = {aPoint, aD1};
    });

  return aResults;
}

NCollection_Array1<GeomGridEval::CurveD2> GeomGridEval_BSplineCurve::EvaluateGridD2(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }

  const occ::handle<NCollection_HArray1<double>>& aFlatKnotsHandle = myGeom->HArrayFlatKnots();
  if (aFlatKnotsHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }
  const NCollection_Array1<double>& aFlatKnots = aFlatKnotsHandle->Array1();

  const occ::handle<NCollection_HArray1<gp_Pnt>>& aPolesHandle = myGeom->HArrayPoles();
  if (aPolesHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }
  const NCollection_Array1<gp_Pnt>& aPoles = aPolesHandle->Array1();

  const occ::handle<NCollection_HArray1<double>>& aWeightsHandle = myGeom->HArrayWeights();
  const bool                                      isRational     = myGeom->IsRational();
  if (isRational && aWeightsHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }
  const NCollection_Array1<double>* aWeights = isRational ? &aWeightsHandle->Array1() : nullptr;

  const int  aDegree    = myGeom->Degree();
  const bool isPeriodic = myGeom->IsPeriodic();

  PreparedParams aPrepared = prepareParams(theParams, aDegree, isPeriodic, aFlatKnots);

  const int                                 aNbParams = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD2> aResults(1, aNbParams);

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, isPeriodic, aFlatKnots, aPoles, aWeights);

  iterateSpanBlocks(
    aPrepared.Ranges,
    aPrepared.Params,
    [&](double theParam) { aCache->BuildCache(theParam, aFlatKnots, aPoles, aWeights); },
    [&](int theIdx, double theLocalParam)
    {
      gp_Pnt aPoint;
      gp_Vec aD1, aD2;
      aCache->D2Local(theLocalParam, aPoint, aD1, aD2);
      aResults.ChangeValue(theIdx + 1) = {aPoint, aD1, aD2};
    },
    [&](int theIdx, double theParam, int theSpanIdx)
    {
      gp_Pnt aPoint;
      gp_Vec aD1, aD2;
      BSplCLib::D2(theParam,
                   theSpanIdx,
                   aDegree,
                   isPeriodic,
                   aPoles,
                   aWeights,
                   aFlatKnots,
                   nullptr,
                   aPoint,
                   aD1,
                   aD2);
      aResults.ChangeValue(theIdx + 1) = {aPoint, aD1, aD2};
    });

  return aResults;
}

NCollection_Array1<GeomGridEval::CurveD3> GeomGridEval_BSplineCurve::EvaluateGridD3(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }

  const occ::handle<NCollection_HArray1<double>>& aFlatKnotsHandle = myGeom->HArrayFlatKnots();
  if (aFlatKnotsHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }
  const NCollection_Array1<double>& aFlatKnots = aFlatKnotsHandle->Array1();

  const occ::handle<NCollection_HArray1<gp_Pnt>>& aPolesHandle = myGeom->HArrayPoles();
  if (aPolesHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }
  const NCollection_Array1<gp_Pnt>& aPoles = aPolesHandle->Array1();

  const occ::handle<NCollection_HArray1<double>>& aWeightsHandle = myGeom->HArrayWeights();
  const bool                                      isRational     = myGeom->IsRational();
  if (isRational && aWeightsHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }
  const NCollection_Array1<double>* aWeights = isRational ? &aWeightsHandle->Array1() : nullptr;

  const int  aDegree    = myGeom->Degree();
  const bool isPeriodic = myGeom->IsPeriodic();

  PreparedParams aPrepared = prepareParams(theParams, aDegree, isPeriodic, aFlatKnots);

  const int                                 aNbParams = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD3> aResults(1, aNbParams);

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, isPeriodic, aFlatKnots, aPoles, aWeights);

  iterateSpanBlocks(
    aPrepared.Ranges,
    aPrepared.Params,
    [&](double theParam) { aCache->BuildCache(theParam, aFlatKnots, aPoles, aWeights); },
    [&](int theIdx, double theLocalParam)
    {
      gp_Pnt aPoint;
      gp_Vec aD1, aD2, aD3;
      aCache->D3Local(theLocalParam, aPoint, aD1, aD2, aD3);
      aResults.ChangeValue(theIdx + 1) = {aPoint, aD1, aD2, aD3};
    },
    [&](int theIdx, double theParam, int theSpanIdx)
    {
      gp_Pnt aPoint;
      gp_Vec aD1, aD2, aD3;
      BSplCLib::D3(theParam,
                   theSpanIdx,
                   aDegree,
                   isPeriodic,
                   aPoles,
                   aWeights,
                   aFlatKnots,
                   nullptr,
                   aPoint,
                   aD1,
                   aD2,
                   aD3);
      aResults.ChangeValue(theIdx + 1) = {aPoint, aD1, aD2, aD3};
    });

  return aResults;
}

NCollection_Array1<gp_Vec> GeomGridEval_BSplineCurve::EvaluateGridDN(
  const NCollection_Array1<double>& theParams,
  int                               theN) const
{
  if (myGeom.IsNull() || theParams.IsEmpty() || theN < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const int                  aNbParams = theParams.Size();
  NCollection_Array1<gp_Vec> aResult(1, aNbParams);

  const int aDegree = myGeom->Degree();
  if (theN > aDegree)
  {
    const gp_Vec aZeroVec(0.0, 0.0, 0.0);
    for (int i = 1; i <= aNbParams; ++i)
    {
      aResult.SetValue(i, aZeroVec);
    }
    return aResult;
  }

  const occ::handle<NCollection_HArray1<double>>& aFlatKnotsHandle = myGeom->HArrayFlatKnots();
  if (aFlatKnotsHandle.IsNull())
  {
    return NCollection_Array1<gp_Vec>();
  }
  const NCollection_Array1<double>& aFlatKnots = aFlatKnotsHandle->Array1();

  const occ::handle<NCollection_HArray1<gp_Pnt>>& aPolesHandle = myGeom->HArrayPoles();
  if (aPolesHandle.IsNull())
  {
    return NCollection_Array1<gp_Vec>();
  }
  const NCollection_Array1<gp_Pnt>& aPoles = aPolesHandle->Array1();

  const occ::handle<NCollection_HArray1<double>>& aWeightsHandle = myGeom->HArrayWeights();
  const bool                                      isRational     = myGeom->IsRational();
  const NCollection_Array1<double>*               aWeights =
    (isRational && !aWeightsHandle.IsNull()) ? &aWeightsHandle->Array1() : nullptr;

  const NCollection_Array1<double>& aKnots     = myGeom->Knots();
  const NCollection_Array1<int>&    aMults     = myGeom->Multiplicities();
  const bool                        isPeriodic = myGeom->IsPeriodic();

  PreparedParams aPrepared = prepareParams(theParams, aDegree, isPeriodic, aFlatKnots);

  const int aNbRanges = aPrepared.Ranges.Size();
  for (int iRange = 0; iRange < aNbRanges; ++iRange)
  {
    const SpanRange& aRange   = aPrepared.Ranges.Value(iRange);
    const int        aSpanIdx = aRange.SpanIndex;

    for (int i = aRange.StartIdx; i < aRange.EndIdx; ++i)
    {
      const ParamWithSpan& aP = aPrepared.Params.Value(i);
      gp_Vec               aDN;
      BSplCLib::DN(aP.Param,
                   theN,
                   aSpanIdx,
                   aDegree,
                   isPeriodic,
                   aPoles,
                   aWeights,
                   aKnots,
                   &aMults,
                   aDN);
      aResult.SetValue(aP.OrigIdx + 1, aDN);
    }
  }
  return aResult;
}
