

#include <GeomGridEval_BezierSurface.hpp>

#include <BSplCLib.hpp>
#include <BSplSLib.hpp>
#include <GeomGridEval_Curve.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>

namespace
{

  constexpr int THE_ISOLINE_THRESHOLD = 8;

  occ::handle<BSplSLib_Cache> buildBezierCache(const occ::handle<Geom_BezierSurface>& theGeom)
  {
    const int aUDegree = theGeom->UDegree();
    const int aVDegree = theGeom->VDegree();

    NCollection_Array1<double> aUFlatKnots(BSplCLib::FlatBezierKnots(aUDegree),
                                           1,
                                           2 * (aUDegree + 1));
    NCollection_Array1<double> aVFlatKnots(BSplCLib::FlatBezierKnots(aVDegree),
                                           1,
                                           2 * (aVDegree + 1));

    const NCollection_Array2<gp_Pnt>& aPoles   = theGeom->Poles();
    const NCollection_Array2<double>* aWeights = theGeom->Weights();

    occ::handle<BSplSLib_Cache> aCache =
      new BSplSLib_Cache(aUDegree, false, aUFlatKnots, aVDegree, false, aVFlatKnots, aWeights);

    aCache->BuildCache(0.5, 0.5, aUFlatKnots, aVFlatKnots, aPoles, aWeights);

    return aCache;
  }
} // namespace

NCollection_Array2<gp_Pnt> GeomGridEval_BezierSurface::EvaluateGrid(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  const bool isVIso = (aNbV == 1 && aNbU >= THE_ISOLINE_THRESHOLD);

  if (isVIso)
  {
    try
    {
      OCC_CATCH_SIGNALS

      occ::handle<Geom_Curve> aCurve = myGeom->VIso(theVParams.Value(theVParams.Lower()));

      if (!aCurve.IsNull())
      {

        GeomGridEval_Curve aCurveEval;
        aCurveEval.Initialize(aCurve);

        NCollection_Array1<gp_Pnt> aCurveResult = aCurveEval.EvaluateGrid(theUParams);

        NCollection_Array2<gp_Pnt> aResult(1, aNbU, 1, 1);
        for (int k = 1; k <= aNbU; ++k)
        {
          aResult(k, 1) = aCurveResult(k);
        }
        return aResult;
      }
    }
    catch (const Standard_Failure&)
    {
    }
  }

  occ::handle<BSplSLib_Cache> aCache = buildBezierCache(myGeom);

  NCollection_Array2<gp_Pnt> aResult(1, aNbU, 1, aNbV);

  for (int i = 0; i < aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i);
    for (int j = 0; j < aNbV; ++j)
    {
      gp_Pnt aPoint;
      aCache->D0(aU, theVParams.Value(theVParams.Lower() + j), aPoint);
      aResult.SetValue(i + 1, j + 1, aPoint);
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD1> GeomGridEval_BezierSurface::EvaluateGridD1(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  occ::handle<BSplSLib_Cache> aCache = buildBezierCache(myGeom);

  const int                                aNbU = theUParams.Size();
  const int                                aNbV = theVParams.Size();
  NCollection_Array2<GeomGridEval::SurfD1> aResult(1, aNbU, 1, aNbV);

  for (int i = 0; i < aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i);
    for (int j = 0; j < aNbV; ++j)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V;
      aCache->D1(aU, theVParams.Value(theVParams.Lower() + j), aPoint, aD1U, aD1V);
      aResult.ChangeValue(i + 1, j + 1) = {aPoint, aD1U, aD1V};
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD2> GeomGridEval_BezierSurface::EvaluateGridD2(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  occ::handle<BSplSLib_Cache> aCache = buildBezierCache(myGeom);

  const int                                aNbU = theUParams.Size();
  const int                                aNbV = theVParams.Size();
  NCollection_Array2<GeomGridEval::SurfD2> aResult(1, aNbU, 1, aNbV);

  for (int i = 0; i < aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i);
    for (int j = 0; j < aNbV; ++j)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      aCache
        ->D2(aU, theVParams.Value(theVParams.Lower() + j), aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV);
      aResult.ChangeValue(i + 1, j + 1) = {aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV};
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD3> GeomGridEval_BezierSurface::EvaluateGridD3(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD3>();
  }

  const int                                aNbU = theUParams.Size();
  const int                                aNbV = theVParams.Size();
  NCollection_Array2<GeomGridEval::SurfD3> aResult(1, aNbU, 1, aNbV);

  const int aUDegree = myGeom->UDegree();
  const int aVDegree = myGeom->VDegree();

  NCollection_Array1<double> aUFlatKnots(BSplCLib::FlatBezierKnots(aUDegree),
                                         1,
                                         2 * (aUDegree + 1));
  NCollection_Array1<double> aVFlatKnots(BSplCLib::FlatBezierKnots(aVDegree),
                                         1,
                                         2 * (aVDegree + 1));

  const NCollection_Array2<gp_Pnt>& aPoles     = myGeom->Poles();
  const NCollection_Array2<double>* aWeights   = myGeom->Weights();
  const bool                        isRational = (aWeights != nullptr);

  for (int i = 0; i < aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i);
    for (int j = 0; j < aNbV; ++j)
    {
      gp_Pnt aPoint;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;

      BSplSLib::D3(aU,
                   theVParams.Value(theVParams.Lower() + j),
                   0,
                   0,
                   aPoles,
                   aWeights,
                   aUFlatKnots,
                   aVFlatKnots,
                   nullptr,
                   nullptr,
                   aUDegree,
                   aVDegree,
                   isRational,
                   isRational,
                   false,
                   false,
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

      aResult.ChangeValue(
        i + 1,
        j + 1) = {aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV};
    }
  }

  return aResult;
}

NCollection_Array2<gp_Vec> GeomGridEval_BezierSurface::EvaluateGridDN(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams,
  int                               theNU,
  int                               theNV) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty() || theNU < 0 || theNV < 0
      || (theNU + theNV) < 1)
  {
    return NCollection_Array2<gp_Vec>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array2<gp_Vec> aResult(1, aNbU, 1, aNbV);

  const int aUDegree = myGeom->UDegree();
  const int aVDegree = myGeom->VDegree();

  if (theNU > aUDegree || theNV > aVDegree)
  {

    const gp_Vec aZeroVec(0.0, 0.0, 0.0);
    for (int i = 1; i <= aNbU; ++i)
    {
      for (int j = 1; j <= aNbV; ++j)
      {
        aResult.SetValue(i, j, aZeroVec);
      }
    }
    return aResult;
  }

  const NCollection_Array2<gp_Pnt>& aPoles     = myGeom->Poles();
  const NCollection_Array2<double>* aWeights   = myGeom->Weights();
  const bool                        isRational = (aWeights != nullptr);

  NCollection_Array1<double> aUFlatKnots(BSplCLib::FlatBezierKnots(aUDegree),
                                         1,
                                         2 * (aUDegree + 1));
  NCollection_Array1<double> aVFlatKnots(BSplCLib::FlatBezierKnots(aVDegree),
                                         1,
                                         2 * (aVDegree + 1));

  for (int i = 0; i < aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i);
    for (int j = 0; j < aNbV; ++j)
    {
      gp_Vec aDN;
      BSplSLib::DN(aU,
                   theVParams.Value(theVParams.Lower() + j),
                   theNU,
                   theNV,
                   0,
                   0,
                   aPoles,
                   aWeights,
                   aUFlatKnots,
                   aVFlatKnots,
                   nullptr,
                   nullptr,
                   aUDegree,
                   aVDegree,
                   isRational,
                   isRational,
                   false,
                   false,
                   aDN);
      aResult.SetValue(i + 1, j + 1, aDN);
    }
  }

  return aResult;
}

NCollection_Array1<gp_Pnt> GeomGridEval_BezierSurface::EvaluatePoints(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  occ::handle<BSplSLib_Cache> aCache = buildBezierCache(myGeom);

  const int                  aNbPts = theUVPairs.Size();
  NCollection_Array1<gp_Pnt> aResult(1, aNbPts);

  for (int i = 0; i < aNbPts; ++i)
  {
    const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i);
    gp_Pnt          aPoint;
    aCache->D0(aUV.X(), aUV.Y(), aPoint);
    aResult.SetValue(i + 1, aPoint);
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD1> GeomGridEval_BezierSurface::EvaluatePointsD1(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  occ::handle<BSplSLib_Cache> aCache = buildBezierCache(myGeom);

  const int                                aNbPts = theUVPairs.Size();
  NCollection_Array1<GeomGridEval::SurfD1> aResult(1, aNbPts);

  for (int i = 0; i < aNbPts; ++i)
  {
    const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i);
    gp_Pnt          aPoint;
    gp_Vec          aD1U, aD1V;
    aCache->D1(aUV.X(), aUV.Y(), aPoint, aD1U, aD1V);
    aResult.ChangeValue(i + 1) = {aPoint, aD1U, aD1V};
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD2> GeomGridEval_BezierSurface::EvaluatePointsD2(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  occ::handle<BSplSLib_Cache> aCache = buildBezierCache(myGeom);

  const int                                aNbPts = theUVPairs.Size();
  NCollection_Array1<GeomGridEval::SurfD2> aResult(1, aNbPts);

  for (int i = 0; i < aNbPts; ++i)
  {
    const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i);
    gp_Pnt          aPoint;
    gp_Vec          aD1U, aD1V, aD2U, aD2V, aD2UV;
    aCache->D2(aUV.X(), aUV.Y(), aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV);
    aResult.ChangeValue(i + 1) = {aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV};
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD3> GeomGridEval_BezierSurface::EvaluatePointsD3(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  const int                                aNbPts = theUVPairs.Size();
  NCollection_Array1<GeomGridEval::SurfD3> aResult(1, aNbPts);

  const int aUDegree = myGeom->UDegree();
  const int aVDegree = myGeom->VDegree();

  NCollection_Array1<double> aUFlatKnots(BSplCLib::FlatBezierKnots(aUDegree),
                                         1,
                                         2 * (aUDegree + 1));
  NCollection_Array1<double> aVFlatKnots(BSplCLib::FlatBezierKnots(aVDegree),
                                         1,
                                         2 * (aVDegree + 1));

  const NCollection_Array2<gp_Pnt>& aPoles     = myGeom->Poles();
  const NCollection_Array2<double>* aWeights   = myGeom->Weights();
  const bool                        isRational = (aWeights != nullptr);

  for (int i = 0; i < aNbPts; ++i)
  {
    const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i);
    gp_Pnt          aPoint;
    gp_Vec          aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;

    BSplSLib::D3(aUV.X(),
                 aUV.Y(),
                 0,
                 0,
                 aPoles,
                 aWeights,
                 aUFlatKnots,
                 aVFlatKnots,
                 nullptr,
                 nullptr,
                 aUDegree,
                 aVDegree,
                 isRational,
                 isRational,
                 false,
                 false,
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

    aResult.ChangeValue(i
                        + 1) = {aPoint, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV};
  }

  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_BezierSurface::EvaluatePointsDN(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs,
  int                                 theNU,
  int                                 theNV) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty() || theNU < 0 || theNV < 0 || (theNU + theNV) < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const int aNbPts = theUVPairs.Size();

  NCollection_Array1<gp_Vec> aResult(1, aNbPts);

  const int aUDegree = myGeom->UDegree();
  const int aVDegree = myGeom->VDegree();

  if (theNU > aUDegree || theNV > aVDegree)
  {

    const gp_Vec aZeroVec(0.0, 0.0, 0.0);
    for (int i = 1; i <= aNbPts; ++i)
    {
      aResult.SetValue(i, aZeroVec);
    }
    return aResult;
  }

  const NCollection_Array2<gp_Pnt>& aPoles     = myGeom->Poles();
  const NCollection_Array2<double>* aWeights   = myGeom->Weights();
  const bool                        isRational = (aWeights != nullptr);

  NCollection_Array1<double> aUFlatKnots(BSplCLib::FlatBezierKnots(aUDegree),
                                         1,
                                         2 * (aUDegree + 1));
  NCollection_Array1<double> aVFlatKnots(BSplCLib::FlatBezierKnots(aVDegree),
                                         1,
                                         2 * (aVDegree + 1));

  for (int i = 0; i < aNbPts; ++i)
  {
    const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i);
    gp_Vec          aDN;
    BSplSLib::DN(aUV.X(),
                 aUV.Y(),
                 theNU,
                 theNV,
                 0,
                 0,
                 aPoles,
                 aWeights,
                 aUFlatKnots,
                 aVFlatKnots,
                 nullptr,
                 nullptr,
                 aUDegree,
                 aVDegree,
                 isRational,
                 isRational,
                 false,
                 false,
                 aDN);
    aResult.SetValue(i + 1, aDN);
  }

  return aResult;
}
