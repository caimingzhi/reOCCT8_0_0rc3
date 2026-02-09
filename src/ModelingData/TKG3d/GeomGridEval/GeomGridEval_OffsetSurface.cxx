

#include <GeomGridEval_OffsetSurface.hpp>

#include <GeomAdaptor_Surface.hpp>
#include <Geom_OffsetSurfaceUtils.hpp>
#include <GeomGridEval_Surface.hpp>

NCollection_Array2<gp_Pnt> GeomGridEval_OffsetSurface::EvaluateGrid(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myBasis.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {

      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluateGrid(theUParams, theVParams);
    }
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array2<gp_Pnt> aResult(1, aNbU, 1, aNbV);

  GeomGridEval_Surface aBasisEval;
  aBasisEval.Initialize(myBasis);
  NCollection_Array2<GeomGridEval::SurfD1> aBasisD1 =
    aBasisEval.EvaluateGridD1(theUParams, theVParams);

  if (aBasisD1.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  GeomAdaptor_Surface aBasisAdaptor(myBasis);

  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i - 1);
    for (int j = 1; j <= aNbV; ++j)
    {
      const double                aV     = theVParams.Value(theVParams.Lower() + j - 1);
      const GeomGridEval::SurfD1& aBasis = aBasisD1.Value(i, j);
      gp_Pnt                      aP     = aBasis.Point;
      Geom_OffsetSurfaceUtils::EvaluateD0(aU,
                                          aV,
                                          &aBasisAdaptor,
                                          myOffset,
                                          anOscQuery,
                                          aP,
                                          aBasis.D1U,
                                          aBasis.D1V);
      aResult.SetValue(i, j, aP);
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD1> GeomGridEval_OffsetSurface::EvaluateGridD1(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myBasis.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {
      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluateGridD1(theUParams, theVParams);
    }
  }

  const int                                aNbU = theUParams.Size();
  const int                                aNbV = theVParams.Size();
  NCollection_Array2<GeomGridEval::SurfD1> aResult(1, aNbU, 1, aNbV);

  GeomGridEval_Surface aBasisEval;
  aBasisEval.Initialize(myBasis);
  NCollection_Array2<GeomGridEval::SurfD2> aBasisD2 =
    aBasisEval.EvaluateGridD2(theUParams, theVParams);

  if (aBasisD2.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  GeomAdaptor_Surface       aBasisAdaptor(myBasis);
  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i - 1);
    for (int j = 1; j <= aNbV; ++j)
    {
      const double                aV     = theVParams.Value(theVParams.Lower() + j - 1);
      const GeomGridEval::SurfD2& aBasis = aBasisD2.Value(i, j);
      gp_Pnt                      aP     = aBasis.Point;
      gp_Vec                      aD1U   = aBasis.D1U;
      gp_Vec                      aD1V   = aBasis.D1V;
      Geom_OffsetSurfaceUtils::EvaluateD1(aU,
                                          aV,
                                          &aBasisAdaptor,
                                          myOffset,
                                          anOscQuery,
                                          aP,
                                          aD1U,
                                          aD1V,
                                          aBasis.D2U,
                                          aBasis.D2V,
                                          aBasis.D2UV);
      aResult.ChangeValue(i, j) = {aP, aD1U, aD1V};
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD2> GeomGridEval_OffsetSurface::EvaluateGridD2(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myBasis.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {
      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluateGridD2(theUParams, theVParams);
    }
  }

  const int                                aNbU = theUParams.Size();
  const int                                aNbV = theVParams.Size();
  NCollection_Array2<GeomGridEval::SurfD2> aResult(1, aNbU, 1, aNbV);

  GeomGridEval_Surface aBasisEval;
  aBasisEval.Initialize(myBasis);
  NCollection_Array2<GeomGridEval::SurfD3> aBasisD3 =
    aBasisEval.EvaluateGridD3(theUParams, theVParams);

  if (aBasisD3.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  GeomAdaptor_Surface       aBasisAdaptor(myBasis);
  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i - 1);
    for (int j = 1; j <= aNbV; ++j)
    {
      const double                aV     = theVParams.Value(theVParams.Lower() + j - 1);
      const GeomGridEval::SurfD3& aBasis = aBasisD3.Value(i, j);
      gp_Pnt                      aP     = aBasis.Point;
      gp_Vec                      aD1U   = aBasis.D1U;
      gp_Vec                      aD1V   = aBasis.D1V;
      gp_Vec                      aD2U   = aBasis.D2U;
      gp_Vec                      aD2V   = aBasis.D2V;
      gp_Vec                      aD2UV  = aBasis.D2UV;
      Geom_OffsetSurfaceUtils::EvaluateD2(aU,
                                          aV,
                                          &aBasisAdaptor,
                                          myOffset,
                                          anOscQuery,
                                          aP,
                                          aD1U,
                                          aD1V,
                                          aD2U,
                                          aD2V,
                                          aD2UV,
                                          aBasis.D3U,
                                          aBasis.D3V,
                                          aBasis.D3UUV,
                                          aBasis.D3UVV);
      aResult.ChangeValue(i, j) = {aP, aD1U, aD1V, aD2U, aD2V, aD2UV};
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD3> GeomGridEval_OffsetSurface::EvaluateGridD3(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myBasis.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD3>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {
      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluateGridD3(theUParams, theVParams);
    }
  }

  const int                                aNbU = theUParams.Size();
  const int                                aNbV = theVParams.Size();
  NCollection_Array2<GeomGridEval::SurfD3> aResult(1, aNbU, 1, aNbV);

  GeomAdaptor_Surface       aBasisAdaptor(myBasis);
  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i - 1);
    for (int j = 1; j <= aNbV; ++j)
    {
      const double aV = theVParams.Value(theVParams.Lower() + j - 1);
      gp_Pnt       aP;
      gp_Vec       aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      Geom_OffsetSurfaceUtils::EvaluateD3(aU,
                                          aV,
                                          &aBasisAdaptor,
                                          myOffset,
                                          anOscQuery,
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

NCollection_Array2<gp_Vec> GeomGridEval_OffsetSurface::EvaluateGridDN(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams,
  int                               theNU,
  int                               theNV) const
{
  if (myBasis.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty() || theNU < 0 || theNV < 0
      || (theNU + theNV) < 1)
  {
    return NCollection_Array2<gp_Vec>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {
      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluateGridDN(theUParams, theVParams, theNU, theNV);
    }
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array2<gp_Vec> aResult(1, aNbU, 1, aNbV);

  GeomGridEval_Surface aBasisEval;
  aBasisEval.Initialize(myBasis);
  NCollection_Array2<GeomGridEval::SurfD1> aBasisD1 =
    aBasisEval.EvaluateGridD1(theUParams, theVParams);

  if (aBasisD1.IsEmpty())
  {
    return NCollection_Array2<gp_Vec>();
  }

  GeomAdaptor_Surface       aBasisAdaptor(myBasis);
  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbU; ++i)
  {
    const double aU = theUParams.Value(theUParams.Lower() + i - 1);
    for (int j = 1; j <= aNbV; ++j)
    {
      const double                aV     = theVParams.Value(theVParams.Lower() + j - 1);
      const GeomGridEval::SurfD1& aBasis = aBasisD1.Value(i, j);
      gp_Vec                      aDN;
      Geom_OffsetSurfaceUtils::EvaluateDN(aU,
                                          aV,
                                          theNU,
                                          theNV,
                                          &aBasisAdaptor,
                                          myOffset,
                                          anOscQuery,
                                          aDN,
                                          aBasis.D1U,
                                          aBasis.D1V);
      aResult.SetValue(i, j, aDN);
    }
  }

  return aResult;
}

NCollection_Array1<gp_Pnt> GeomGridEval_OffsetSurface::EvaluatePoints(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myBasis.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {
      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluatePoints(theUVPairs);
    }
  }

  const int aNbPts = theUVPairs.Size();

  NCollection_Array1<gp_Pnt> aResult(1, aNbPts);

  GeomGridEval_Surface aBasisEval;
  aBasisEval.Initialize(myBasis);
  NCollection_Array1<GeomGridEval::SurfD1> aBasisD1 = aBasisEval.EvaluatePointsD1(theUVPairs);

  if (aBasisD1.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  GeomAdaptor_Surface       aBasisAdaptor(myBasis);
  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbPts; ++i)
  {
    const gp_Pnt2d&             aUV    = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    const GeomGridEval::SurfD1& aBasis = aBasisD1.Value(i);
    gp_Pnt                      aP     = aBasis.Point;
    Geom_OffsetSurfaceUtils::EvaluateD0(aUV.X(),
                                        aUV.Y(),
                                        &aBasisAdaptor,
                                        myOffset,
                                        anOscQuery,
                                        aP,
                                        aBasis.D1U,
                                        aBasis.D1V);
    aResult.SetValue(i, aP);
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD1> GeomGridEval_OffsetSurface::EvaluatePointsD1(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myBasis.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {
      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluatePointsD1(theUVPairs);
    }
  }

  const int                                aNbPts = theUVPairs.Size();
  NCollection_Array1<GeomGridEval::SurfD1> aResult(1, aNbPts);

  GeomGridEval_Surface aBasisEval;
  aBasisEval.Initialize(myBasis);
  NCollection_Array1<GeomGridEval::SurfD2> aBasisD2 = aBasisEval.EvaluatePointsD2(theUVPairs);

  if (aBasisD2.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  GeomAdaptor_Surface       aBasisAdaptor(myBasis);
  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbPts; ++i)
  {
    const gp_Pnt2d&             aUV    = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    const GeomGridEval::SurfD2& aBasis = aBasisD2.Value(i);
    gp_Pnt                      aP     = aBasis.Point;
    gp_Vec                      aD1U   = aBasis.D1U;
    gp_Vec                      aD1V   = aBasis.D1V;
    Geom_OffsetSurfaceUtils::EvaluateD1(aUV.X(),
                                        aUV.Y(),
                                        &aBasisAdaptor,
                                        myOffset,
                                        anOscQuery,
                                        aP,
                                        aD1U,
                                        aD1V,
                                        aBasis.D2U,
                                        aBasis.D2V,
                                        aBasis.D2UV);
    aResult.ChangeValue(i) = {aP, aD1U, aD1V};
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD2> GeomGridEval_OffsetSurface::EvaluatePointsD2(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myBasis.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {
      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluatePointsD2(theUVPairs);
    }
  }

  const int                                aNbPts = theUVPairs.Size();
  NCollection_Array1<GeomGridEval::SurfD2> aResult(1, aNbPts);

  GeomGridEval_Surface aBasisEval;
  aBasisEval.Initialize(myBasis);
  NCollection_Array1<GeomGridEval::SurfD3> aBasisD3 = aBasisEval.EvaluatePointsD3(theUVPairs);

  if (aBasisD3.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  GeomAdaptor_Surface       aBasisAdaptor(myBasis);
  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbPts; ++i)
  {
    const gp_Pnt2d&             aUV    = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    const GeomGridEval::SurfD3& aBasis = aBasisD3.Value(i);
    gp_Pnt                      aP     = aBasis.Point;
    gp_Vec                      aD1U   = aBasis.D1U;
    gp_Vec                      aD1V   = aBasis.D1V;
    gp_Vec                      aD2U   = aBasis.D2U;
    gp_Vec                      aD2V   = aBasis.D2V;
    gp_Vec                      aD2UV  = aBasis.D2UV;
    Geom_OffsetSurfaceUtils::EvaluateD2(aUV.X(),
                                        aUV.Y(),
                                        &aBasisAdaptor,
                                        myOffset,
                                        anOscQuery,
                                        aP,
                                        aD1U,
                                        aD1V,
                                        aD2U,
                                        aD2V,
                                        aD2UV,
                                        aBasis.D3U,
                                        aBasis.D3V,
                                        aBasis.D3UUV,
                                        aBasis.D3UVV);
    aResult.ChangeValue(i) = {aP, aD1U, aD1V, aD2U, aD2V, aD2UV};
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD3> GeomGridEval_OffsetSurface::EvaluatePointsD3(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myBasis.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {
      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluatePointsD3(theUVPairs);
    }
  }

  const int                                aNbPts = theUVPairs.Size();
  NCollection_Array1<GeomGridEval::SurfD3> aResult(1, aNbPts);

  GeomAdaptor_Surface       aBasisAdaptor(myBasis);
  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbPts; ++i)
  {
    const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    gp_Pnt          aP;
    gp_Vec          aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
    Geom_OffsetSurfaceUtils::EvaluateD3(aUV.X(),
                                        aUV.Y(),
                                        &aBasisAdaptor,
                                        myOffset,
                                        anOscQuery,
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
    aResult.ChangeValue(i) = {aP, aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV};
  }

  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_OffsetSurface::EvaluatePointsDN(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs,
  int                                 theNU,
  int                                 theNV) const
{
  if (myBasis.IsNull() || theUVPairs.IsEmpty() || theNU < 0 || theNV < 0 || (theNU + theNV) < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  if (!myGeom.IsNull())
  {
    occ::handle<Geom_Surface> anEquivSurf = myGeom->Surface();
    if (!anEquivSurf.IsNull() && anEquivSurf.get() != myGeom.get())
    {
      GeomGridEval_Surface anEquivEval;
      anEquivEval.Initialize(anEquivSurf);
      return anEquivEval.EvaluatePointsDN(theUVPairs, theNU, theNV);
    }
  }

  const int aNbPts = theUVPairs.Size();

  NCollection_Array1<gp_Vec> aResult(1, aNbPts);

  GeomGridEval_Surface aBasisEval;
  aBasisEval.Initialize(myBasis);
  NCollection_Array1<GeomGridEval::SurfD1> aBasisD1 = aBasisEval.EvaluatePointsD1(theUVPairs);

  if (aBasisD1.IsEmpty())
  {
    return NCollection_Array1<gp_Vec>();
  }

  GeomAdaptor_Surface       aBasisAdaptor(myBasis);
  const Geom_OffsetSurface* anOscQuery = myGeom.get();

  for (int i = 1; i <= aNbPts; ++i)
  {
    const gp_Pnt2d&             aUV    = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    const GeomGridEval::SurfD1& aBasis = aBasisD1.Value(i);
    gp_Vec                      aDN;
    Geom_OffsetSurfaceUtils::EvaluateDN(aUV.X(),
                                        aUV.Y(),
                                        theNU,
                                        theNV,
                                        &aBasisAdaptor,
                                        myOffset,
                                        anOscQuery,
                                        aDN,
                                        aBasis.D1U,
                                        aBasis.D1V);
    aResult.SetValue(i, aDN);
  }

  return aResult;
}
