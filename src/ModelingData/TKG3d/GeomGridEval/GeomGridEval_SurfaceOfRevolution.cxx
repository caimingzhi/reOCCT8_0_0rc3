

#include <GeomGridEval_SurfaceOfRevolution.hpp>

#include <Geom_RevolutionUtils.hpp>

GeomGridEval_SurfaceOfRevolution::GeomGridEval_SurfaceOfRevolution(
  const occ::handle<Geom_SurfaceOfRevolution>& theRevolution)
    : myGeom(theRevolution)
{
  if (!myGeom.IsNull())
  {
    myBasisCurve    = myGeom->BasisCurve();
    myAxis          = myGeom->Axis();
    myAxisLocation  = myAxis.Location();
    myAxisDirection = myAxis.Direction();
  }
}

NCollection_Array2<gp_Pnt> GeomGridEval_SurfaceOfRevolution::EvaluateGrid(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myBasisCurve.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  GeomGridEval_Curve aCurveEval;
  aCurveEval.Initialize(myBasisCurve);

  NCollection_Array1<gp_Pnt> aCurvePoints = aCurveEval.EvaluateGrid(theVParams);
  if (aCurvePoints.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  NCollection_Array2<gp_Pnt> aResult(1, aNbU, 1, aNbV);

  for (int i = 1; i <= aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i - 1);

    for (int j = 1; j <= aNbV; ++j)
    {
      gp_Pnt aP;
      Geom_RevolutionUtils::CalculateD0(aCurvePoints.Value(j), aU, myAxis, aP);
      aResult.SetValue(i, j, aP);
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD1> GeomGridEval_SurfaceOfRevolution::EvaluateGridD1(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myBasisCurve.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  GeomGridEval_Curve aCurveEval;
  aCurveEval.Initialize(myBasisCurve);

  NCollection_Array1<GeomGridEval::CurveD1> aCurveD1 = aCurveEval.EvaluateGridD1(theVParams);
  if (aCurveD1.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  NCollection_Array2<GeomGridEval::SurfD1> aResult(1, aNbU, 1, aNbV);

  for (int i = 1; i <= aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i - 1);

    for (int j = 1; j <= aNbV; ++j)
    {
      const GeomGridEval::CurveD1& aCurveData = aCurveD1.Value(j);

      gp_Pnt aP;
      gp_Vec aD1U, aD1V;
      Geom_RevolutionUtils::CalculateD1(aCurveData.Point,
                                        aCurveData.D1,
                                        aU,
                                        myAxis,
                                        aP,
                                        aD1U,
                                        aD1V);
      aResult.ChangeValue(i, j) = {aP, aD1U, aD1V};
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD2> GeomGridEval_SurfaceOfRevolution::EvaluateGridD2(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myBasisCurve.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  GeomGridEval_Curve aCurveEval;
  aCurveEval.Initialize(myBasisCurve);

  NCollection_Array1<GeomGridEval::CurveD2> aCurveD2 = aCurveEval.EvaluateGridD2(theVParams);
  if (aCurveD2.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  NCollection_Array2<GeomGridEval::SurfD2> aResult(1, aNbU, 1, aNbV);

  for (int i = 1; i <= aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i - 1);

    for (int j = 1; j <= aNbV; ++j)
    {
      const GeomGridEval::CurveD2& aCurveData = aCurveD2.Value(j);

      gp_Pnt aP;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      Geom_RevolutionUtils::CalculateD2(aCurveData.Point,
                                        aCurveData.D1,
                                        aCurveData.D2,
                                        aU,
                                        myAxis,
                                        aP,
                                        aD1U,
                                        aD1V,
                                        aD2U,
                                        aD2V,
                                        aD2UV);
      aResult.ChangeValue(i, j) = {aP, aD1U, aD1V, aD2U, aD2V, aD2UV};
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD3> GeomGridEval_SurfaceOfRevolution::EvaluateGridD3(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myBasisCurve.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD3>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  GeomGridEval_Curve aCurveEval;
  aCurveEval.Initialize(myBasisCurve);

  NCollection_Array1<GeomGridEval::CurveD3> aCurveD3 = aCurveEval.EvaluateGridD3(theVParams);
  if (aCurveD3.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD3>();
  }

  NCollection_Array2<GeomGridEval::SurfD3> aResult(1, aNbU, 1, aNbV);

  for (int i = 1; i <= aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i - 1);

    for (int j = 1; j <= aNbV; ++j)
    {
      const GeomGridEval::CurveD3& aCurveData = aCurveD3.Value(j);

      gp_Pnt aP;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      Geom_RevolutionUtils::CalculateD3(aCurveData.Point,
                                        aCurveData.D1,
                                        aCurveData.D2,
                                        aCurveData.D3,
                                        aU,
                                        myAxis,
                                        aP,
                                        aD1U,
                                        aD1V,
                                        aD2U,
                                        aD2V,
                                        aD2UV,
                                        aD3U,
                                        aD3V,
                                        aD3UUV,
                                        aD3UVV);
      aResult.ChangeValue(i, j) = {aP, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV};
    }
  }

  return aResult;
}

NCollection_Array2<gp_Vec> GeomGridEval_SurfaceOfRevolution::EvaluateGridDN(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams,
  int                               theNU,
  int                               theNV) const
{
  if (myBasisCurve.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty() || theNU < 0
      || theNV < 0 || (theNU + theNV) < 1)
  {
    return NCollection_Array2<gp_Vec>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array2<gp_Vec> aResult(1, aNbU, 1, aNbV);

  GeomGridEval_Curve aCurveEval;
  aCurveEval.Initialize(myBasisCurve);

  if (theNU == 0)
  {

    NCollection_Array1<gp_Vec> aCurveDN = aCurveEval.EvaluateGridDN(theVParams, theNV);

    for (int i = 1; i <= aNbU; ++i)
    {
      const double aU = theUParams.Value(theUParams.Lower() + i - 1);

      for (int j = 1; j <= aNbV; ++j)
      {
        gp_Vec aDN = Geom_RevolutionUtils::CalculateDN(aCurveDN.Value(j), aU, myAxis, theNU, theNV);
        aResult.SetValue(i, j, aDN);
      }
    }
  }
  else
  {

    NCollection_Array1<gp_Vec> aCurveDV;
    NCollection_Array1<gp_Pnt> aCurvePts;

    if (theNV == 0)
    {
      aCurvePts = aCurveEval.EvaluateGrid(theVParams);
    }
    else
    {
      aCurveDV = aCurveEval.EvaluateGridDN(theVParams, theNV);
    }

    for (int i = 1; i <= aNbU; ++i)
    {
      const double aU = theUParams.Value(theUParams.Lower() + i - 1);

      for (int j = 1; j <= aNbV; ++j)
      {
        gp_Vec aCurvePtOrDN;
        if (theNV == 0)
        {

          aCurvePtOrDN = gp_Vec(aCurvePts.Value(j).XYZ() - myAxisLocation.XYZ());
        }
        else
        {
          aCurvePtOrDN = aCurveDV.Value(j);
        }

        gp_Vec aDN = Geom_RevolutionUtils::CalculateDN(aCurvePtOrDN, aU, myAxis, theNU, theNV);
        aResult.SetValue(i, j, aDN);
      }
    }
  }

  return aResult;
}

NCollection_Array1<gp_Pnt> GeomGridEval_SurfaceOfRevolution::EvaluatePoints(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  return GeomGridEval::EvaluatePointsHelper(theUVPairs,
                                            [this](double theU, double theV) -> gp_Pnt
                                            { return myGeom->Value(theU, theV); });
}

NCollection_Array1<GeomGridEval::SurfD1> GeomGridEval_SurfaceOfRevolution::EvaluatePointsD1(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  return GeomGridEval::EvaluatePointsD1Helper(theUVPairs,
                                              [this](double theU, double theV)
                                              {
                                                gp_Pnt aP;
                                                gp_Vec aD1U, aD1V;
                                                myGeom->D1(theU, theV, aP, aD1U, aD1V);
                                                return GeomGridEval::SurfD1{aP, aD1U, aD1V};
                                              });
}

NCollection_Array1<GeomGridEval::SurfD2> GeomGridEval_SurfaceOfRevolution::EvaluatePointsD2(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  return GeomGridEval::EvaluatePointsD2Helper(
    theUVPairs,
    [this](double theU, double theV)
    {
      gp_Pnt aP;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      myGeom->D2(theU, theV, aP, aD1U, aD1V, aD2U, aD2V, aD2UV);
      return GeomGridEval::SurfD2{aP, aD1U, aD1V, aD2U, aD2V, aD2UV};
    });
}

NCollection_Array1<GeomGridEval::SurfD3> GeomGridEval_SurfaceOfRevolution::EvaluatePointsD3(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  return GeomGridEval::EvaluatePointsD3Helper(
    theUVPairs,
    [this](double theU, double theV)
    {
      gp_Pnt aP;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      myGeom->D3(theU, theV, aP, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV);
      return GeomGridEval::SurfD3{aP, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV};
    });
}

NCollection_Array1<gp_Vec> GeomGridEval_SurfaceOfRevolution::EvaluatePointsDN(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs,
  int                                 theNU,
  int                                 theNV) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty() || theNU < 0 || theNV < 0 || (theNU + theNV) < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  return GeomGridEval::EvaluatePointsDNHelper(
    theUVPairs,
    [this, theNU, theNV](double theU, double theV) -> gp_Vec
    { return myGeom->DN(theU, theV, theNU, theNV); });
}
