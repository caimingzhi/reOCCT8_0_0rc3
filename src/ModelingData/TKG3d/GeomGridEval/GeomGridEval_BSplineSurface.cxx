

#include <GeomGridEval_BSplineSurface.hpp>

#include <algorithm>
#include <BSplCLib.hpp>
#include <BSplSLib.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

namespace
{

  constexpr int THE_CACHE_THRESHOLD = 4;

  template <typename BuildCacheFunc, typename CacheEvalFunc, typename DirectEvalFunc>
  void iterateSortedUVPoints(const NCollection_Array1<GeomGridEval::UVPointWithSpan>& theUVPoints,
                             BuildCacheFunc&&                                         theBuildCache,
                             CacheEvalFunc&&                                          theCacheEval,
                             DirectEvalFunc&&                                         theDirectEval)
  {
    const int aNbPoints = theUVPoints.Size();
    if (aNbPoints == 0)
    {
      return;
    }

    int i = 0;
    while (i < aNbPoints)
    {
      const GeomGridEval::UVPointWithSpan& aFirstPt = theUVPoints.Value(i);
      const int                            aUSpan   = aFirstPt.USpanIdx;
      const int                            aVSpan   = aFirstPt.VSpanIdx;

      int aGroupEnd = i + 1;
      while (aGroupEnd < aNbPoints)
      {
        const GeomGridEval::UVPointWithSpan& aPt = theUVPoints.Value(aGroupEnd);
        if (aPt.USpanIdx != aUSpan || aPt.VSpanIdx != aVSpan)
        {
          break;
        }
        ++aGroupEnd;
      }
      const int aGroupSize = aGroupEnd - i;

      if (aGroupSize >= THE_CACHE_THRESHOLD)
      {

        theBuildCache(aFirstPt.U, aFirstPt.V);
        for (int j = i; j < aGroupEnd; ++j)
        {
          theCacheEval(theUVPoints.Value(j));
        }
      }
      else
      {

        for (int j = i; j < aGroupEnd; ++j)
        {
          theDirectEval(theUVPoints.Value(j));
        }
      }

      i = aGroupEnd;
    }
  }

  int locateSpan(double&                           theParam,
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
    theParam = aNewParam;
    return aSpanIndex;
  }

  void computeSpansAndSort(NCollection_Array1<GeomGridEval::UVPointWithSpan>& theUVPoints,
                           const NCollection_Array1<double>&                  theUFlatKnots,
                           const NCollection_Array1<double>&                  theVFlatKnots,
                           int                                                theUDegree,
                           int                                                theVDegree,
                           bool                                               theIsUPeriodic,
                           bool                                               theIsVPeriodic)
  {
    if (theUVPoints.IsEmpty())
    {
      return;
    }

    const int aNbPoints = theUVPoints.Size();

    for (int i = 0; i < aNbPoints; ++i)
    {
      GeomGridEval::UVPointWithSpan& aPt = theUVPoints.ChangeValue(i);

      double aUParam   = aPt.U;
      int    aUSpanIdx = locateSpan(aUParam, theUDegree, theIsUPeriodic, theUFlatKnots);
      aPt.U            = aUParam;
      aPt.USpanIdx     = aUSpanIdx;

      const double aUSpanStart   = theUFlatKnots.Value(aUSpanIdx);
      const double aUSpanHalfLen = 0.5 * (theUFlatKnots.Value(aUSpanIdx + 1) - aUSpanStart);
      const double aUSpanMid     = aUSpanStart + aUSpanHalfLen;
      aPt.LocalU                 = (aPt.U - aUSpanMid) / aUSpanHalfLen;

      double aVParam   = aPt.V;
      int    aVSpanIdx = locateSpan(aVParam, theVDegree, theIsVPeriodic, theVFlatKnots);
      aPt.V            = aVParam;
      aPt.VSpanIdx     = aVSpanIdx;

      const double aVSpanStart   = theVFlatKnots.Value(aVSpanIdx);
      const double aVSpanHalfLen = 0.5 * (theVFlatKnots.Value(aVSpanIdx + 1) - aVSpanStart);
      const double aVSpanMid     = aVSpanStart + aVSpanHalfLen;
      aPt.LocalV                 = (aPt.V - aVSpanMid) / aVSpanHalfLen;
    }

    std::sort(theUVPoints.begin(),
              theUVPoints.end(),
              [](const GeomGridEval::UVPointWithSpan& a, const GeomGridEval::UVPointWithSpan& b)
              {
                if (a.USpanIdx != b.USpanIdx)
                  return a.USpanIdx < b.USpanIdx;
                if (a.VSpanIdx != b.VSpanIdx)
                  return a.VSpanIdx < b.VSpanIdx;
                return a.U < b.U;
              });
  }

  [[nodiscard]] NCollection_Array1<GeomGridEval::UVPointWithSpan> prepareGridPoints(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams,
    const NCollection_Array1<double>& theUFlatKnots,
    const NCollection_Array1<double>& theVFlatKnots,
    int                               theUDegree,
    int                               theVDegree,
    bool                              theIsUPeriodic,
    bool                              theIsVPeriodic)
  {
    const int aNbU      = theUParams.Size();
    const int aNbV      = theVParams.Size();
    const int aNbPoints = aNbU * aNbV;
    const int aULower   = theUParams.Lower();
    const int aVLower   = theVParams.Lower();

    NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints(0, aNbPoints - 1);

    int aIdx = 0;
    for (int i = 0; i < aNbU; ++i)
    {
      const double aU = theUParams.Value(aULower + i);
      for (int j = 0; j < aNbV; ++j)
      {
        const double aV      = theVParams.Value(aVLower + j);
        const int    aOutIdx = i * aNbV + j;
        aUVPoints.SetValue(aIdx++, GeomGridEval::UVPointWithSpan{aU, aV, 0.0, 0.0, 0, 0, aOutIdx});
      }
    }

    computeSpansAndSort(aUVPoints,
                        theUFlatKnots,
                        theVFlatKnots,
                        theUDegree,
                        theVDegree,
                        theIsUPeriodic,
                        theIsVPeriodic);
    return aUVPoints;
  }

  [[nodiscard]] NCollection_Array1<GeomGridEval::UVPointWithSpan> preparePairPoints(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs,
    const NCollection_Array1<double>&   theUFlatKnots,
    const NCollection_Array1<double>&   theVFlatKnots,
    int                                 theUDegree,
    int                                 theVDegree,
    bool                                theIsUPeriodic,
    bool                                theIsVPeriodic)
  {
    const int aNbPairs = theUVPairs.IsEmpty() ? 0 : theUVPairs.Size();
    if (aNbPairs == 0)
    {
      return NCollection_Array1<GeomGridEval::UVPointWithSpan>();
    }

    NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints(0, aNbPairs - 1);

    const int aLower = theUVPairs.Lower();
    for (int i = 0; i < aNbPairs; ++i)
    {
      const gp_Pnt2d& aUV = theUVPairs.Value(aLower + i);
      aUVPoints.SetValue(i, GeomGridEval::UVPointWithSpan{aUV.X(), aUV.Y(), 0.0, 0.0, 0, 0, i});
    }

    computeSpansAndSort(aUVPoints,
                        theUFlatKnots,
                        theVFlatKnots,
                        theUDegree,
                        theVDegree,
                        theIsUPeriodic,
                        theIsVPeriodic);
    return aUVPoints;
  }

} // namespace

NCollection_Array2<gp_Pnt> GeomGridEval_BSplineSurface::EvaluateGrid(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();

  const int  aUDegree    = myGeom->UDegree();
  const int  aVDegree    = myGeom->VDegree();
  const bool isUPeriodic = myGeom->IsUPeriodic();
  const bool isVPeriodic = myGeom->IsVPeriodic();
  const bool isURational = myGeom->IsURational();
  const bool isVRational = myGeom->IsVRational();

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = prepareGridPoints(theUParams,
                                                                                  theVParams,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  if (aUVPoints.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  const int                  aNbPoints = aNbU * aNbV;
  NCollection_Array1<gp_Pnt> aLinearResult(1, aNbPoints);

  occ::handle<BSplSLib_Cache> aCache = new BSplSLib_Cache(aUDegree,
                                                          isUPeriodic,
                                                          aUFlatKnots,
                                                          aVDegree,
                                                          isVPeriodic,
                                                          aVFlatKnots,
                                                          aWeights);

  iterateSortedUVPoints(
    aUVPoints,
    [&](double theU, double theV)
    { aCache->BuildCache(theU, theV, aUFlatKnots, aVFlatKnots, aPoles, aWeights); },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPnt;
      aCache->D0Local(thePt.LocalU, thePt.LocalV, aPnt);
      aLinearResult.SetValue(thePt.OutputIdx + 1, aPnt);
    },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPnt;
      BSplSLib::D0(thePt.U,
                   thePt.V,
                   thePt.USpanIdx,
                   thePt.VSpanIdx,
                   aPoles,
                   aWeights,
                   aUFlatKnots,
                   aVFlatKnots,
                   nullptr,
                   nullptr,
                   aUDegree,
                   aVDegree,
                   isURational,
                   isVRational,
                   isUPeriodic,
                   isVPeriodic,
                   aPnt);
      aLinearResult.SetValue(thePt.OutputIdx + 1, aPnt);
    });

  NCollection_Array2<gp_Pnt> aGrid(1, aNbU, 1, aNbV);
  for (int i = 0; i < aNbU; ++i)
  {
    for (int j = 0; j < aNbV; ++j)
    {
      const int aLinIdx = i * aNbV + j;
      aGrid.SetValue(i + 1, j + 1, aLinearResult.Value(aLinIdx + 1));
    }
  }
  return aGrid;
}

NCollection_Array1<gp_Pnt> GeomGridEval_BSplineSurface::EvaluatePoints(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();

  const int  aUDegree    = myGeom->UDegree();
  const int  aVDegree    = myGeom->VDegree();
  const bool isUPeriodic = myGeom->IsUPeriodic();
  const bool isVPeriodic = myGeom->IsVPeriodic();
  const bool isURational = myGeom->IsURational();
  const bool isVRational = myGeom->IsVRational();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = preparePairPoints(theUVPairs,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  const int aNbPoints = aUVPoints.Size();
  if (aNbPoints == 0)
  {
    return NCollection_Array1<gp_Pnt>();
  }

  NCollection_Array1<gp_Pnt> aPoints(1, aNbPoints);

  occ::handle<BSplSLib_Cache> aCache = new BSplSLib_Cache(aUDegree,
                                                          isUPeriodic,
                                                          aUFlatKnots,
                                                          aVDegree,
                                                          isVPeriodic,
                                                          aVFlatKnots,
                                                          aWeights);

  iterateSortedUVPoints(
    aUVPoints,
    [&](double theU, double theV)
    { aCache->BuildCache(theU, theV, aUFlatKnots, aVFlatKnots, aPoles, aWeights); },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPnt;
      aCache->D0Local(thePt.LocalU, thePt.LocalV, aPnt);
      aPoints.SetValue(thePt.OutputIdx + 1, aPnt);
    },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPnt;
      BSplSLib::D0(thePt.U,
                   thePt.V,
                   thePt.USpanIdx,
                   thePt.VSpanIdx,
                   aPoles,
                   aWeights,
                   aUFlatKnots,
                   aVFlatKnots,
                   nullptr,
                   nullptr,
                   aUDegree,
                   aVDegree,
                   isURational,
                   isVRational,
                   isUPeriodic,
                   isVPeriodic,
                   aPnt);
      aPoints.SetValue(thePt.OutputIdx + 1, aPnt);
    });

  return aPoints;
}

NCollection_Array2<GeomGridEval::SurfD1> GeomGridEval_BSplineSurface::EvaluateGridD1(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array1<GeomGridEval::SurfD1> aLinearResult = EvaluatePointsD1(theUParams, theVParams);
  if (aLinearResult.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  NCollection_Array2<GeomGridEval::SurfD1> aGrid(1, aNbU, 1, aNbV);
  for (int i = 0; i < aNbU; ++i)
  {
    for (int j = 0; j < aNbV; ++j)
    {
      const int aLinIdx = i * aNbV + j;
      aGrid.SetValue(i + 1, j + 1, aLinearResult.Value(aLinIdx + 1));
    }
  }
  return aGrid;
}

NCollection_Array1<GeomGridEval::SurfD1> GeomGridEval_BSplineSurface::EvaluatePointsD1(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();

  const int  aUDegree    = myGeom->UDegree();
  const int  aVDegree    = myGeom->VDegree();
  const bool isUPeriodic = myGeom->IsUPeriodic();
  const bool isVPeriodic = myGeom->IsVPeriodic();
  const bool isURational = myGeom->IsURational();
  const bool isVRational = myGeom->IsVRational();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = preparePairPoints(theUVPairs,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  const int aNbPoints = aUVPoints.Size();
  if (aNbPoints == 0)
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  NCollection_Array1<GeomGridEval::SurfD1> aResults(1, aNbPoints);

  occ::handle<BSplSLib_Cache> aCache = new BSplSLib_Cache(aUDegree,
                                                          isUPeriodic,
                                                          aUFlatKnots,
                                                          aVDegree,
                                                          isVPeriodic,
                                                          aVFlatKnots,
                                                          aWeights);

  iterateSortedUVPoints(
    aUVPoints,
    [&](double theU, double theV)
    { aCache->BuildCache(theU, theV, aUFlatKnots, aVFlatKnots, aPoles, aWeights); },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V;
      aCache->D1Local(thePt.LocalU, thePt.LocalV, aPoint, aD1U, aD1V);
      aResults.SetValue(thePt.OutputIdx + 1, GeomGridEval::SurfD1{aPoint, aD1U, aD1V});
    },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V;
      BSplSLib::D1(thePt.U,
                   thePt.V,
                   thePt.USpanIdx,
                   thePt.VSpanIdx,
                   aPoles,
                   aWeights,
                   aUFlatKnots,
                   aVFlatKnots,
                   nullptr,
                   nullptr,
                   aUDegree,
                   aVDegree,
                   isURational,
                   isVRational,
                   isUPeriodic,
                   isVPeriodic,
                   aPoint,
                   aD1U,
                   aD1V);
      aResults.SetValue(thePt.OutputIdx + 1, GeomGridEval::SurfD1{aPoint, aD1U, aD1V});
    });

  return aResults;
}

NCollection_Array2<GeomGridEval::SurfD2> GeomGridEval_BSplineSurface::EvaluateGridD2(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array1<GeomGridEval::SurfD2> aLinearResult = EvaluatePointsD2(theUParams, theVParams);
  if (aLinearResult.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  NCollection_Array2<GeomGridEval::SurfD2> aGrid(1, aNbU, 1, aNbV);
  for (int i = 0; i < aNbU; ++i)
  {
    for (int j = 0; j < aNbV; ++j)
    {
      const int aLinIdx = i * aNbV + j;
      aGrid.SetValue(i + 1, j + 1, aLinearResult.Value(aLinIdx + 1));
    }
  }
  return aGrid;
}

NCollection_Array1<GeomGridEval::SurfD2> GeomGridEval_BSplineSurface::EvaluatePointsD2(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();

  const int  aUDegree    = myGeom->UDegree();
  const int  aVDegree    = myGeom->VDegree();
  const bool isUPeriodic = myGeom->IsUPeriodic();
  const bool isVPeriodic = myGeom->IsVPeriodic();
  const bool isURational = myGeom->IsURational();
  const bool isVRational = myGeom->IsVRational();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = preparePairPoints(theUVPairs,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  const int aNbPoints = aUVPoints.Size();
  if (aNbPoints == 0)
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  NCollection_Array1<GeomGridEval::SurfD2> aResults(1, aNbPoints);

  occ::handle<BSplSLib_Cache> aCache = new BSplSLib_Cache(aUDegree,
                                                          isUPeriodic,
                                                          aUFlatKnots,
                                                          aVDegree,
                                                          isVPeriodic,
                                                          aVFlatKnots,
                                                          aWeights);

  iterateSortedUVPoints(
    aUVPoints,
    [&](double theU, double theV)
    { aCache->BuildCache(theU, theV, aUFlatKnots, aVFlatKnots, aPoles, aWeights); },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      aCache->D2Local(thePt.LocalU, thePt.LocalV, aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV);
      aResults.SetValue(thePt.OutputIdx + 1,
                        GeomGridEval::SurfD2{aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV});
    },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      BSplSLib::D2(thePt.U,
                   thePt.V,
                   thePt.USpanIdx,
                   thePt.VSpanIdx,
                   aPoles,
                   aWeights,
                   aUFlatKnots,
                   aVFlatKnots,
                   nullptr,
                   nullptr,
                   aUDegree,
                   aVDegree,
                   isURational,
                   isVRational,
                   isUPeriodic,
                   isVPeriodic,
                   aPoint,
                   aD1U,
                   aD1V,
                   aD2U,
                   aD2V,
                   aD2UV);
      aResults.SetValue(thePt.OutputIdx + 1,
                        GeomGridEval::SurfD2{aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV});
    });

  return aResults;
}

NCollection_Array2<GeomGridEval::SurfD3> GeomGridEval_BSplineSurface::EvaluateGridD3(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD3>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array1<GeomGridEval::SurfD3> aLinearResult = EvaluatePointsD3(theUParams, theVParams);
  if (aLinearResult.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD3>();
  }

  NCollection_Array2<GeomGridEval::SurfD3> aGrid(1, aNbU, 1, aNbV);
  for (int i = 0; i < aNbU; ++i)
  {
    for (int j = 0; j < aNbV; ++j)
    {
      const int aLinIdx = i * aNbV + j;
      aGrid.SetValue(i + 1, j + 1, aLinearResult.Value(aLinIdx + 1));
    }
  }
  return aGrid;
}

NCollection_Array1<GeomGridEval::SurfD3> GeomGridEval_BSplineSurface::EvaluatePointsD3(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();
  const int                         aUDegree    = myGeom->UDegree();
  const int                         aVDegree    = myGeom->VDegree();
  const bool                        isURational = myGeom->IsURational();
  const bool                        isVRational = myGeom->IsVRational();
  const bool                        isUPeriodic = myGeom->IsUPeriodic();
  const bool                        isVPeriodic = myGeom->IsVPeriodic();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = preparePairPoints(theUVPairs,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  const int aNbPoints = aUVPoints.Size();
  if (aNbPoints == 0)
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  NCollection_Array1<GeomGridEval::SurfD3> aResults(1, aNbPoints);

  for (int i = 0; i < aNbPoints; ++i)
  {
    const GeomGridEval::UVPointWithSpan& aPt = aUVPoints.Value(i);

    gp_Pnt aPoint;
    gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;

    BSplSLib::D3(aPt.U,
                 aPt.V,
                 aPt.USpanIdx,
                 aPt.VSpanIdx,
                 aPoles,
                 aWeights,
                 aUFlatKnots,
                 aVFlatKnots,
                 nullptr,
                 nullptr,
                 aUDegree,
                 aVDegree,
                 isURational,
                 isVRational,
                 isUPeriodic,
                 isVPeriodic,
                 aPoint,
                 aD1U,
                 aD1V,
                 aD2U,
                 aD2V,
                 aD2UV,
                 aD3U,
                 aD3V,
                 aD3UUV,
                 aD3UVV);

    aResults.SetValue(
      aPt.OutputIdx + 1,
      GeomGridEval::SurfD3{aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV});
  }

  return aResults;
}

NCollection_Array2<gp_Vec> GeomGridEval_BSplineSurface::EvaluateGridDN(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams,
  int                               theNU,
  int                               theNV) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<gp_Vec>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array1<gp_Vec> aLinearResult = EvaluatePointsDN(theUParams, theVParams, theNU, theNV);
  if (aLinearResult.IsEmpty())
  {
    return NCollection_Array2<gp_Vec>();
  }

  NCollection_Array2<gp_Vec> aGrid(1, aNbU, 1, aNbV);
  for (int i = 0; i < aNbU; ++i)
  {
    for (int j = 0; j < aNbV; ++j)
    {
      const int aLinIdx = i * aNbV + j;
      aGrid.SetValue(i + 1, j + 1, aLinearResult.Value(aLinIdx + 1));
    }
  }
  return aGrid;
}

NCollection_Array1<gp_Vec> GeomGridEval_BSplineSurface::EvaluatePointsDN(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs,
  int                                 theNU,
  int                                 theNV) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty() || theNU < 0 || theNV < 0 || (theNU + theNV) < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array1<gp_Vec>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();
  const int                         aUDegree    = myGeom->UDegree();
  const int                         aVDegree    = myGeom->VDegree();
  const bool                        isURational = myGeom->IsURational();
  const bool                        isVRational = myGeom->IsVRational();
  const bool                        isUPeriodic = myGeom->IsUPeriodic();
  const bool                        isVPeriodic = myGeom->IsVPeriodic();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = preparePairPoints(theUVPairs,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  const int aNbPoints = aUVPoints.Size();
  if (aNbPoints == 0)
  {
    return NCollection_Array1<gp_Vec>();
  }

  NCollection_Array1<gp_Vec> aResults(1, aNbPoints);

  if (theNU > aUDegree || theNV > aVDegree)
  {
    const gp_Vec aZeroVec(0.0, 0.0, 0.0);
    for (int i = 1; i <= aNbPoints; ++i)
    {
      aResults.SetValue(i, aZeroVec);
    }
    return aResults;
  }

  for (int i = 0; i < aNbPoints; ++i)
  {
    const GeomGridEval::UVPointWithSpan& aPt = aUVPoints.Value(i);

    gp_Vec aDN;
    BSplSLib::DN(aPt.U,
                 aPt.V,
                 theNU,
                 theNV,
                 aPt.USpanIdx,
                 aPt.VSpanIdx,
                 aPoles,
                 aWeights,
                 aUFlatKnots,
                 aVFlatKnots,
                 nullptr,
                 nullptr,
                 aUDegree,
                 aVDegree,
                 isURational,
                 isVRational,
                 isUPeriodic,
                 isVPeriodic,
                 aDN);

    aResults.SetValue(aPt.OutputIdx + 1, aDN);
  }

  return aResults;
}

NCollection_Array1<GeomGridEval::SurfD1> GeomGridEval_BSplineSurface::EvaluatePointsD1(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();

  const int  aUDegree    = myGeom->UDegree();
  const int  aVDegree    = myGeom->VDegree();
  const bool isUPeriodic = myGeom->IsUPeriodic();
  const bool isVPeriodic = myGeom->IsVPeriodic();
  const bool isURational = myGeom->IsURational();
  const bool isVRational = myGeom->IsVRational();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = prepareGridPoints(theUParams,
                                                                                  theVParams,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  const int aNbPoints = aUVPoints.Size();
  if (aNbPoints == 0)
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  NCollection_Array1<GeomGridEval::SurfD1> aResults(1, aNbPoints);

  occ::handle<BSplSLib_Cache> aCache = new BSplSLib_Cache(aUDegree,
                                                          isUPeriodic,
                                                          aUFlatKnots,
                                                          aVDegree,
                                                          isVPeriodic,
                                                          aVFlatKnots,
                                                          aWeights);

  iterateSortedUVPoints(
    aUVPoints,
    [&](double theU, double theV)
    { aCache->BuildCache(theU, theV, aUFlatKnots, aVFlatKnots, aPoles, aWeights); },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V;
      aCache->D1Local(thePt.LocalU, thePt.LocalV, aPoint, aD1U, aD1V);
      aResults.SetValue(thePt.OutputIdx + 1, GeomGridEval::SurfD1{aPoint, aD1U, aD1V});
    },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V;
      BSplSLib::D1(thePt.U,
                   thePt.V,
                   thePt.USpanIdx,
                   thePt.VSpanIdx,
                   aPoles,
                   aWeights,
                   aUFlatKnots,
                   aVFlatKnots,
                   nullptr,
                   nullptr,
                   aUDegree,
                   aVDegree,
                   isURational,
                   isVRational,
                   isUPeriodic,
                   isVPeriodic,
                   aPoint,
                   aD1U,
                   aD1V);
      aResults.SetValue(thePt.OutputIdx + 1, GeomGridEval::SurfD1{aPoint, aD1U, aD1V});
    });

  return aResults;
}

NCollection_Array1<GeomGridEval::SurfD2> GeomGridEval_BSplineSurface::EvaluatePointsD2(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();

  const int  aUDegree    = myGeom->UDegree();
  const int  aVDegree    = myGeom->VDegree();
  const bool isUPeriodic = myGeom->IsUPeriodic();
  const bool isVPeriodic = myGeom->IsVPeriodic();
  const bool isURational = myGeom->IsURational();
  const bool isVRational = myGeom->IsVRational();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = prepareGridPoints(theUParams,
                                                                                  theVParams,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  const int aNbPoints = aUVPoints.Size();
  if (aNbPoints == 0)
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  NCollection_Array1<GeomGridEval::SurfD2> aResults(1, aNbPoints);

  occ::handle<BSplSLib_Cache> aCache = new BSplSLib_Cache(aUDegree,
                                                          isUPeriodic,
                                                          aUFlatKnots,
                                                          aVDegree,
                                                          isVPeriodic,
                                                          aVFlatKnots,
                                                          aWeights);

  iterateSortedUVPoints(
    aUVPoints,
    [&](double theU, double theV)
    { aCache->BuildCache(theU, theV, aUFlatKnots, aVFlatKnots, aPoles, aWeights); },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      aCache->D2Local(thePt.LocalU, thePt.LocalV, aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV);
      aResults.SetValue(thePt.OutputIdx + 1,
                        GeomGridEval::SurfD2{aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV});
    },
    [&](const GeomGridEval::UVPointWithSpan& thePt)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      BSplSLib::D2(thePt.U,
                   thePt.V,
                   thePt.USpanIdx,
                   thePt.VSpanIdx,
                   aPoles,
                   aWeights,
                   aUFlatKnots,
                   aVFlatKnots,
                   nullptr,
                   nullptr,
                   aUDegree,
                   aVDegree,
                   isURational,
                   isVRational,
                   isUPeriodic,
                   isVPeriodic,
                   aPoint,
                   aD1U,
                   aD1V,
                   aD2U,
                   aD2V,
                   aD2UV);
      aResults.SetValue(thePt.OutputIdx + 1,
                        GeomGridEval::SurfD2{aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV});
    });

  return aResults;
}

NCollection_Array1<GeomGridEval::SurfD3> GeomGridEval_BSplineSurface::EvaluatePointsD3(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();
  const int                         aUDegree    = myGeom->UDegree();
  const int                         aVDegree    = myGeom->VDegree();
  const bool                        isURational = myGeom->IsURational();
  const bool                        isVRational = myGeom->IsVRational();
  const bool                        isUPeriodic = myGeom->IsUPeriodic();
  const bool                        isVPeriodic = myGeom->IsVPeriodic();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = prepareGridPoints(theUParams,
                                                                                  theVParams,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  const int aNbPoints = aUVPoints.Size();
  if (aNbPoints == 0)
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  NCollection_Array1<GeomGridEval::SurfD3> aResults(1, aNbPoints);

  for (int i = 0; i < aNbPoints; ++i)
  {
    const GeomGridEval::UVPointWithSpan& aPt = aUVPoints.Value(i);

    gp_Pnt aPoint;
    gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;

    BSplSLib::D3(aPt.U,
                 aPt.V,
                 aPt.USpanIdx,
                 aPt.VSpanIdx,
                 aPoles,
                 aWeights,
                 aUFlatKnots,
                 aVFlatKnots,
                 nullptr,
                 nullptr,
                 aUDegree,
                 aVDegree,
                 isURational,
                 isVRational,
                 isUPeriodic,
                 isVPeriodic,
                 aPoint,
                 aD1U,
                 aD1V,
                 aD2U,
                 aD2V,
                 aD2UV,
                 aD3U,
                 aD3V,
                 aD3UUV,
                 aD3UVV);

    aResults.SetValue(
      aPt.OutputIdx + 1,
      GeomGridEval::SurfD3{aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV});
  }

  return aResults;
}

NCollection_Array1<gp_Vec> GeomGridEval_BSplineSurface::EvaluatePointsDN(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams,
  int                               theNU,
  int                               theNV) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty() || theNU < 0 || theNV < 0
      || (theNU + theNV) < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const occ::handle<NCollection_HArray1<double>>& aUFlatKnotsHandle = myGeom->HArrayUFlatKnots();
  const occ::handle<NCollection_HArray1<double>>& aVFlatKnotsHandle = myGeom->HArrayVFlatKnots();
  const occ::handle<NCollection_HArray2<gp_Pnt>>& aPolesHandle      = myGeom->HArrayPoles();

  if (aUFlatKnotsHandle.IsNull() || aVFlatKnotsHandle.IsNull() || aPolesHandle.IsNull())
  {
    return NCollection_Array1<gp_Vec>();
  }

  const NCollection_Array1<double>& aUFlatKnots = aUFlatKnotsHandle->Array1();
  const NCollection_Array1<double>& aVFlatKnots = aVFlatKnotsHandle->Array1();
  const NCollection_Array2<gp_Pnt>& aPoles      = aPolesHandle->Array2();
  const NCollection_Array2<double>* aWeights    = myGeom->Weights();
  const int                         aUDegree    = myGeom->UDegree();
  const int                         aVDegree    = myGeom->VDegree();
  const bool                        isURational = myGeom->IsURational();
  const bool                        isVRational = myGeom->IsVRational();
  const bool                        isUPeriodic = myGeom->IsUPeriodic();
  const bool                        isVPeriodic = myGeom->IsVPeriodic();

  NCollection_Array1<GeomGridEval::UVPointWithSpan> aUVPoints = prepareGridPoints(theUParams,
                                                                                  theVParams,
                                                                                  aUFlatKnots,
                                                                                  aVFlatKnots,
                                                                                  aUDegree,
                                                                                  aVDegree,
                                                                                  isUPeriodic,
                                                                                  isVPeriodic);

  const int aNbPoints = aUVPoints.Size();
  if (aNbPoints == 0)
  {
    return NCollection_Array1<gp_Vec>();
  }

  NCollection_Array1<gp_Vec> aResults(1, aNbPoints);

  if (theNU > aUDegree || theNV > aVDegree)
  {
    const gp_Vec aZeroVec(0.0, 0.0, 0.0);
    for (int i = 1; i <= aNbPoints; ++i)
    {
      aResults.SetValue(i, aZeroVec);
    }
    return aResults;
  }

  for (int i = 0; i < aNbPoints; ++i)
  {
    const GeomGridEval::UVPointWithSpan& aPt = aUVPoints.Value(i);

    gp_Vec aDN;
    BSplSLib::DN(aPt.U,
                 aPt.V,
                 theNU,
                 theNV,
                 aPt.USpanIdx,
                 aPt.VSpanIdx,
                 aPoles,
                 aWeights,
                 aUFlatKnots,
                 aVFlatKnots,
                 nullptr,
                 nullptr,
                 aUDegree,
                 aVDegree,
                 isURational,
                 isVRational,
                 isUPeriodic,
                 isVPeriodic,
                 aDN);

    aResults.SetValue(aPt.OutputIdx + 1, aDN);
  }

  return aResults;
}
