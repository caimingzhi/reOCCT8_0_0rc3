

#include <GeomGridEval_BezierCurve.hpp>

#include <BSplCLib.hpp>
#include <BSplCLib_Cache.hpp>
#include <gp_Pnt.hpp>

namespace
{

  occ::handle<BSplCLib_Cache> CreateBezierCache(const occ::handle<Geom_BezierCurve>& theCurve)
  {
    const int                  aDegree = theCurve->Degree();
    NCollection_Array1<double> aFlatKnots(BSplCLib::FlatBezierKnots(aDegree), 1, 2 * (aDegree + 1));

    occ::handle<BSplCLib_Cache> aCache = new BSplCLib_Cache(aDegree,
                                                            theCurve->IsPeriodic(),
                                                            aFlatKnots,
                                                            theCurve->Poles(),
                                                            theCurve->Weights());
    aCache->BuildCache(0.5, aFlatKnots, theCurve->Poles(), theCurve->Weights());
    return aCache;
  }
} // namespace

NCollection_Array1<gp_Pnt> GeomGridEval_BezierCurve::EvaluateGrid(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Pnt> aResult(1, aNb);

  occ::handle<BSplCLib_Cache> aCache = CreateBezierCache(myGeom);

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    gp_Pnt aP;
    aCache->D0(theParams.Value(i), aP);
    aResult.SetValue(i - theParams.Lower() + 1, aP);
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD1> GeomGridEval_BezierCurve::EvaluateGridD1(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD1> aResult(1, aNb);

  occ::handle<BSplCLib_Cache> aCache = CreateBezierCache(myGeom);

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    gp_Pnt aP;
    gp_Vec aD1;
    aCache->D1(theParams.Value(i), aP, aD1);
    aResult.ChangeValue(i - theParams.Lower() + 1) = {aP, aD1};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD2> GeomGridEval_BezierCurve::EvaluateGridD2(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD2> aResult(1, aNb);

  occ::handle<BSplCLib_Cache> aCache = CreateBezierCache(myGeom);

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    gp_Pnt aP;
    gp_Vec aD1, aD2;
    aCache->D2(theParams.Value(i), aP, aD1, aD2);
    aResult.ChangeValue(i - theParams.Lower() + 1) = {aP, aD1, aD2};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD3> GeomGridEval_BezierCurve::EvaluateGridD3(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD3> aResult(1, aNb);

  occ::handle<BSplCLib_Cache> aCache = CreateBezierCache(myGeom);

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    gp_Pnt aP;
    gp_Vec aD1, aD2, aD3;
    aCache->D3(theParams.Value(i), aP, aD1, aD2, aD3);
    aResult.ChangeValue(i - theParams.Lower() + 1) = {aP, aD1, aD2, aD3};
  }
  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_BezierCurve::EvaluateGridDN(
  const NCollection_Array1<double>& theParams,
  int                               theN) const
{
  if (myGeom.IsNull() || theParams.IsEmpty() || theN < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Vec> aResult(1, aNb);

  const int aDegree = myGeom->Degree();
  if (theN > aDegree)
  {
    const gp_Vec aZeroVec(0.0, 0.0, 0.0);
    for (int i = 1; i <= aNb; ++i)
    {
      aResult.SetValue(i, aZeroVec);
    }
    return aResult;
  }

  const NCollection_Array1<gp_Pnt>& aPoles   = myGeom->Poles();
  const NCollection_Array1<double>* aWeights = myGeom->Weights();

  NCollection_Array1<double> aFlatKnots(BSplCLib::FlatBezierKnots(aDegree), 1, 2 * (aDegree + 1));

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    gp_Vec aDN;
    BSplCLib::DN(theParams.Value(i),
                 theN,
                 0,
                 aDegree,
                 false,
                 aPoles,
                 aWeights,
                 aFlatKnots,
                 nullptr,
                 aDN);
    aResult.SetValue(i - theParams.Lower() + 1, aDN);
  }
  return aResult;
}
