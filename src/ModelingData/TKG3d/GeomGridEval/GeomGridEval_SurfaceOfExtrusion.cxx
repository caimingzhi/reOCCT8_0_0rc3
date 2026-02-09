

#include <GeomGridEval_SurfaceOfExtrusion.hpp>

#include <Geom_ExtrusionUtils.hpp>

GeomGridEval_SurfaceOfExtrusion::GeomGridEval_SurfaceOfExtrusion(
  const occ::handle<Geom_SurfaceOfLinearExtrusion>& theExtrusion)
    : myGeom(theExtrusion)
{
  if (!myGeom.IsNull())
  {
    myBasisCurve = myGeom->BasisCurve();
    myDirection  = myGeom->Direction();
  }
}

NCollection_Array2<gp_Pnt> GeomGridEval_SurfaceOfExtrusion::EvaluateGrid(
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

  NCollection_Array1<gp_Pnt> aCurvePoints = aCurveEval.EvaluateGrid(theUParams);
  if (aCurvePoints.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  const gp_XYZ               aDirXYZ = myDirection.XYZ();
  NCollection_Array2<gp_Pnt> aResult(1, aNbU, 1, aNbV);

  for (int i = 1; i <= aNbU; ++i)
  {
    const gp_Pnt& aCurvePt = aCurvePoints.Value(i);
    for (int j = 1; j <= aNbV; ++j)
    {
      const double aV = theVParams.Value(theVParams.Lower() + j - 1);
      gp_Pnt       aP;
      Geom_ExtrusionUtils::CalculateD0(aCurvePt, aV, aDirXYZ, aP);
      aResult.SetValue(i, j, aP);
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD1> GeomGridEval_SurfaceOfExtrusion::EvaluateGridD1(
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

  NCollection_Array1<GeomGridEval::CurveD1> aCurveD1 = aCurveEval.EvaluateGridD1(theUParams);
  if (aCurveD1.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  const gp_XYZ                             aDirXYZ = myDirection.XYZ();
  NCollection_Array2<GeomGridEval::SurfD1> aResult(1, aNbU, 1, aNbV);

  for (int i = 1; i <= aNbU; ++i)
  {
    const GeomGridEval::CurveD1& aCurveData = aCurveD1.Value(i);

    for (int j = 1; j <= aNbV; ++j)
    {
      const double aV = theVParams.Value(theVParams.Lower() + j - 1);
      gp_Pnt       aP;
      gp_Vec       aD1U, aD1V;
      Geom_ExtrusionUtils::CalculateD1(aCurveData.Point,
                                       aCurveData.D1,
                                       aV,
                                       aDirXYZ,
                                       aP,
                                       aD1U,
                                       aD1V);
      aResult.ChangeValue(i, j) = {aP, aD1U, aD1V};
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD2> GeomGridEval_SurfaceOfExtrusion::EvaluateGridD2(
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

  NCollection_Array1<GeomGridEval::CurveD2> aCurveD2 = aCurveEval.EvaluateGridD2(theUParams);
  if (aCurveD2.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  const gp_XYZ                             aDirXYZ = myDirection.XYZ();
  NCollection_Array2<GeomGridEval::SurfD2> aResult(1, aNbU, 1, aNbV);

  for (int i = 1; i <= aNbU; ++i)
  {
    const GeomGridEval::CurveD2& aCurveData = aCurveD2.Value(i);

    for (int j = 1; j <= aNbV; ++j)
    {
      const double aV = theVParams.Value(theVParams.Lower() + j - 1);
      gp_Pnt       aP;
      gp_Vec       aD1U, aD1V, aD2U, aD2V, aD2UV;
      Geom_ExtrusionUtils::CalculateD2(aCurveData.Point,
                                       aCurveData.D1,
                                       aCurveData.D2,
                                       aV,
                                       aDirXYZ,
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

NCollection_Array2<GeomGridEval::SurfD3> GeomGridEval_SurfaceOfExtrusion::EvaluateGridD3(
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

  NCollection_Array1<GeomGridEval::CurveD3> aCurveD3 = aCurveEval.EvaluateGridD3(theUParams);
  if (aCurveD3.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD3>();
  }

  const gp_XYZ                             aDirXYZ = myDirection.XYZ();
  NCollection_Array2<GeomGridEval::SurfD3> aResult(1, aNbU, 1, aNbV);

  for (int i = 1; i <= aNbU; ++i)
  {
    const GeomGridEval::CurveD3& aCurveData = aCurveD3.Value(i);

    for (int j = 1; j <= aNbV; ++j)
    {
      const double aV = theVParams.Value(theVParams.Lower() + j - 1);
      gp_Pnt       aP;
      gp_Vec       aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      Geom_ExtrusionUtils::CalculateD3(aCurveData.Point,
                                       aCurveData.D1,
                                       aCurveData.D2,
                                       aCurveData.D3,
                                       aV,
                                       aDirXYZ,
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

NCollection_Array2<gp_Vec> GeomGridEval_SurfaceOfExtrusion::EvaluateGridDN(
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

  const gp_XYZ aDirXYZ = myDirection.XYZ();

  if (theNV == 0)
  {

    GeomGridEval_Curve aCurveEval;
    aCurveEval.Initialize(myBasisCurve);

    NCollection_Array1<gp_Vec> aCurveDN = aCurveEval.EvaluateGridDN(theUParams, theNU);

    for (int i = 1; i <= aNbU; ++i)
    {
      const gp_Vec aDN = Geom_ExtrusionUtils::CalculateDN(aCurveDN.Value(i), aDirXYZ, theNU, theNV);
      for (int j = 1; j <= aNbV; ++j)
      {
        aResult.SetValue(i, j, aDN);
      }
    }
  }
  else
  {

    const gp_Vec aDN = Geom_ExtrusionUtils::CalculateDN(gp_Vec(), aDirXYZ, theNU, theNV);
    for (int i = 1; i <= aNbU; ++i)
    {
      for (int j = 1; j <= aNbV; ++j)
      {
        aResult.SetValue(i, j, aDN);
      }
    }
  }

  return aResult;
}

NCollection_Array1<gp_Pnt> GeomGridEval_SurfaceOfExtrusion::EvaluatePoints(
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

NCollection_Array1<GeomGridEval::SurfD1> GeomGridEval_SurfaceOfExtrusion::EvaluatePointsD1(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  return GeomGridEval::EvaluatePointsD1Helper(
    theUVPairs,
    [this](double theU, double theV) -> GeomGridEval::SurfD1
    {
      gp_Pnt aP;
      gp_Vec aD1U, aD1V;
      myGeom->D1(theU, theV, aP, aD1U, aD1V);
      return {aP, aD1U, aD1V};
    });
}

NCollection_Array1<GeomGridEval::SurfD2> GeomGridEval_SurfaceOfExtrusion::EvaluatePointsD2(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  return GeomGridEval::EvaluatePointsD2Helper(
    theUVPairs,
    [this](double theU, double theV) -> GeomGridEval::SurfD2
    {
      gp_Pnt aP;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      myGeom->D2(theU, theV, aP, aD1U, aD1V, aD2U, aD2V, aD2UV);
      return {aP, aD1U, aD1V, aD2U, aD2V, aD2UV};
    });
}

NCollection_Array1<GeomGridEval::SurfD3> GeomGridEval_SurfaceOfExtrusion::EvaluatePointsD3(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  return GeomGridEval::EvaluatePointsD3Helper(
    theUVPairs,
    [this](double theU, double theV) -> GeomGridEval::SurfD3
    {
      gp_Pnt aP;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      myGeom->D3(theU, theV, aP, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV);
      return {aP, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV};
    });
}

NCollection_Array1<gp_Vec> GeomGridEval_SurfaceOfExtrusion::EvaluatePointsDN(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs,
  int                                 theNU,
  int                                 theNV) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty() || theNU < 0 || theNV < 0 || (theNU + theNV) < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  return GeomGridEval::EvaluatePointsDNHelper(theUVPairs,
                                              [this, theNU, theNV](double theU, double theV)
                                              { return myGeom->DN(theU, theV, theNU, theNV); });
}
