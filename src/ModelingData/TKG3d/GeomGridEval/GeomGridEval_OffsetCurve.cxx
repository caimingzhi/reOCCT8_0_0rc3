

#include <GeomGridEval_OffsetCurve.hpp>

#include <Geom_OffsetCurveUtils.hpp>
#include <GeomGridEval_Curve.hpp>

NCollection_Array1<gp_Pnt> GeomGridEval_OffsetCurve::EvaluateGrid(
  const NCollection_Array1<double>& theParams) const
{
  if (myBasis.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  GeomGridEval_Curve aBasisEval;
  aBasisEval.Initialize(myBasis);

  NCollection_Array1<GeomGridEval::CurveD1> aBasisD1 = aBasisEval.EvaluateGridD1(theParams);
  if (aBasisD1.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const int                  aNbParams = theParams.Size();
  NCollection_Array1<gp_Pnt> aResult(1, aNbParams);

  const gp_XYZ aDirXYZ = myDirection.XYZ();

  for (int i = 1; i <= aNbParams; ++i)
  {
    const GeomGridEval::CurveD1& aBasis = aBasisD1.Value(i);
    gp_Pnt                       aP     = aBasis.Point;

    Geom_OffsetCurveUtils::CalculateD0(aP, aBasis.D1, aDirXYZ, myOffset);
    aResult.SetValue(i, aP);
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD1> GeomGridEval_OffsetCurve::EvaluateGridD1(
  const NCollection_Array1<double>& theParams) const
{
  if (myBasis.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }

  GeomGridEval_Curve aBasisEval;
  aBasisEval.Initialize(myBasis);

  NCollection_Array1<GeomGridEval::CurveD2> aBasisD2 = aBasisEval.EvaluateGridD2(theParams);
  if (aBasisD2.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }

  const int                                 aNbParams = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD1> aResult(1, aNbParams);

  const gp_XYZ aDirXYZ = myDirection.XYZ();

  for (int i = 1; i <= aNbParams; ++i)
  {
    const GeomGridEval::CurveD2& aBasis = aBasisD2.Value(i);
    gp_Pnt                       aP     = aBasis.Point;
    gp_Vec                       aD1    = aBasis.D1;

    Geom_OffsetCurveUtils::CalculateD1(aP, aD1, aBasis.D2, aDirXYZ, myOffset);
    aResult.ChangeValue(i) = {aP, aD1};
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD2> GeomGridEval_OffsetCurve::EvaluateGridD2(
  const NCollection_Array1<double>& theParams) const
{
  if (myBasis.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }

  GeomGridEval_Curve aBasisEval;
  aBasisEval.Initialize(myBasis);

  NCollection_Array1<GeomGridEval::CurveD3> aBasisD3 = aBasisEval.EvaluateGridD3(theParams);
  if (aBasisD3.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }

  const int                                 aNbParams = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD2> aResult(1, aNbParams);

  const gp_XYZ aDirXYZ = myDirection.XYZ();

  for (int i = 1; i <= aNbParams; ++i)
  {
    const GeomGridEval::CurveD3& aBasis = aBasisD3.Value(i);
    gp_Pnt                       aP     = aBasis.Point;
    gp_Vec                       aD1    = aBasis.D1;
    gp_Vec                       aD2    = aBasis.D2;
    gp_Vec                       aD3    = aBasis.D3;

    bool isDirectionChange = false;
    if (aD1.SquareMagnitude() <= gp::Resolution())
    {
      gp_Vec aDummyD4;
      isDirectionChange =
        Geom_OffsetCurveUtils::AdjustDerivative(*myBasis,
                                                3,
                                                theParams.Value(theParams.Lower() + i - 1),
                                                aD1,
                                                aD2,
                                                aD3,
                                                aDummyD4);
    }

    Geom_OffsetCurveUtils::CalculateD2(aP, aD1, aD2, aD3, aDirXYZ, myOffset, isDirectionChange);
    aResult.ChangeValue(i) = {aP, aD1, aD2};
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD3> GeomGridEval_OffsetCurve::EvaluateGridD3(
  const NCollection_Array1<double>& theParams) const
{
  if (myBasis.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }

  GeomGridEval_Curve aBasisEval;
  aBasisEval.Initialize(myBasis);

  NCollection_Array1<GeomGridEval::CurveD3> aBasisD3 = aBasisEval.EvaluateGridD3(theParams);
  if (aBasisD3.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }

  const int                                 aNbParams = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD3> aResult(1, aNbParams);

  const gp_XYZ aDirXYZ = myDirection.XYZ();

  for (int i = 1; i <= aNbParams; ++i)
  {
    const double aParam = theParams.Value(theParams.Lower() + i - 1);

    const GeomGridEval::CurveD3& aBasis = aBasisD3.Value(i);
    gp_Pnt                       aP     = aBasis.Point;
    gp_Vec                       aD1    = aBasis.D1;
    gp_Vec                       aD2    = aBasis.D2;
    gp_Vec                       aD3    = aBasis.D3;
    gp_Vec                       aD4    = myBasis->DN(aParam, 4);

    bool isDirectionChange = false;
    if (aD1.SquareMagnitude() <= gp::Resolution())
    {
      isDirectionChange =
        Geom_OffsetCurveUtils::AdjustDerivative(*myBasis, 4, aParam, aD1, aD2, aD3, aD4);
    }

    Geom_OffsetCurveUtils::CalculateD3(aP,
                                       aD1,
                                       aD2,
                                       aD3,
                                       aD4,
                                       aDirXYZ,
                                       myOffset,
                                       isDirectionChange);
    aResult.ChangeValue(i) = {aP, aD1, aD2, aD3};
  }

  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_OffsetCurve::EvaluateGridDN(
  const NCollection_Array1<double>& theParams,
  int                               theN) const
{
  if (myBasis.IsNull() || theParams.IsEmpty() || theN < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const int aNbParams = theParams.Size();

  if (theN == 1)
  {
    NCollection_Array1<GeomGridEval::CurveD1> aD1Grid = EvaluateGridD1(theParams);
    NCollection_Array1<gp_Vec>                aResult(1, aNbParams);
    for (int i = 1; i <= aNbParams; ++i)
    {
      aResult.SetValue(i, aD1Grid.Value(i).D1);
    }
    return aResult;
  }
  else if (theN == 2)
  {
    NCollection_Array1<GeomGridEval::CurveD2> aD2Grid = EvaluateGridD2(theParams);
    NCollection_Array1<gp_Vec>                aResult(1, aNbParams);
    for (int i = 1; i <= aNbParams; ++i)
    {
      aResult.SetValue(i, aD2Grid.Value(i).D2);
    }
    return aResult;
  }
  else if (theN == 3)
  {
    NCollection_Array1<GeomGridEval::CurveD3> aD3Grid = EvaluateGridD3(theParams);
    NCollection_Array1<gp_Vec>                aResult(1, aNbParams);
    for (int i = 1; i <= aNbParams; ++i)
    {
      aResult.SetValue(i, aD3Grid.Value(i).D3);
    }
    return aResult;
  }
  else
  {

    GeomGridEval_Curve aBasisEval;
    aBasisEval.Initialize(myBasis);
    return aBasisEval.EvaluateGridDN(theParams, theN);
  }
}
