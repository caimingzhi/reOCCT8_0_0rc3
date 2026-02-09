

#include <GeomGridEval_Cylinder.hpp>

#include <gp_Cylinder.hpp>

#include <cmath>

GeomGridEval_Cylinder::Data GeomGridEval_Cylinder::extractData() const
{
  const gp_Cylinder& aCyl    = myGeom->Cylinder();
  const gp_Pnt&      aCenter = aCyl.Location();
  const gp_Dir&      aXDir   = aCyl.Position().XDirection();
  const gp_Dir&      aYDir   = aCyl.Position().YDirection();
  const gp_Dir&      aZDir   = aCyl.Position().Direction();

  return {aCenter.X(),
          aCenter.Y(),
          aCenter.Z(),
          aXDir.X(),
          aXDir.Y(),
          aXDir.Z(),
          aYDir.X(),
          aYDir.Y(),
          aYDir.Z(),
          aZDir.X(),
          aZDir.Y(),
          aZDir.Z(),
          aCyl.Radius()};
}

GeomGridEval_Cylinder::UContext GeomGridEval_Cylinder::computeUContext(const Data& theData,
                                                                       double      theU)
{
  const double cosU = std::cos(theU);
  const double sinU = std::sin(theU);

  return {cosU,
          sinU,
          cosU * theData.XX + sinU * theData.YX,
          cosU * theData.XY + sinU * theData.YY,
          cosU * theData.XZ + sinU * theData.YZ,
          -sinU * theData.XX + cosU * theData.YX,
          -sinU * theData.XY + cosU * theData.YY,
          -sinU * theData.XZ + cosU * theData.YZ};
}

gp_Pnt GeomGridEval_Cylinder::computeD0(const Data& theData, const UContext& theUCtx, double theV)
{

  return gp_Pnt(theData.CX + theData.Radius * theUCtx.dirUX + theV * theData.ZX,
                theData.CY + theData.Radius * theUCtx.dirUY + theV * theData.ZY,
                theData.CZ + theData.Radius * theUCtx.dirUZ + theV * theData.ZZ);
}

GeomGridEval::SurfD1 GeomGridEval_Cylinder::computeD1(const Data&     theData,
                                                      const UContext& theUCtx,
                                                      double          theV)
{

  return {gp_Pnt(theData.CX + theData.Radius * theUCtx.dirUX + theV * theData.ZX,
                 theData.CY + theData.Radius * theUCtx.dirUY + theV * theData.ZY,
                 theData.CZ + theData.Radius * theUCtx.dirUZ + theV * theData.ZZ),
          gp_Vec(theData.Radius * theUCtx.dDirUX,
                 theData.Radius * theUCtx.dDirUY,
                 theData.Radius * theUCtx.dDirUZ),
          gp_Vec(theData.ZX, theData.ZY, theData.ZZ)};
}

GeomGridEval::SurfD2 GeomGridEval_Cylinder::computeD2(const Data&     theData,
                                                      const UContext& theUCtx,
                                                      double          theV)
{

  const gp_Vec aZero(0.0, 0.0, 0.0);

  return {gp_Pnt(theData.CX + theData.Radius * theUCtx.dirUX + theV * theData.ZX,
                 theData.CY + theData.Radius * theUCtx.dirUY + theV * theData.ZY,
                 theData.CZ + theData.Radius * theUCtx.dirUZ + theV * theData.ZZ),
          gp_Vec(theData.Radius * theUCtx.dDirUX,
                 theData.Radius * theUCtx.dDirUY,
                 theData.Radius * theUCtx.dDirUZ),
          gp_Vec(theData.ZX, theData.ZY, theData.ZZ),
          gp_Vec(-theData.Radius * theUCtx.dirUX,
                 -theData.Radius * theUCtx.dirUY,
                 -theData.Radius * theUCtx.dirUZ),
          aZero,
          aZero};
}

GeomGridEval::SurfD3 GeomGridEval_Cylinder::computeD3(const Data&     theData,
                                                      const UContext& theUCtx,
                                                      double          theV)
{

  const gp_Vec aZero(0.0, 0.0, 0.0);

  return {gp_Pnt(theData.CX + theData.Radius * theUCtx.dirUX + theV * theData.ZX,
                 theData.CY + theData.Radius * theUCtx.dirUY + theV * theData.ZY,
                 theData.CZ + theData.Radius * theUCtx.dirUZ + theV * theData.ZZ),
          gp_Vec(theData.Radius * theUCtx.dDirUX,
                 theData.Radius * theUCtx.dDirUY,
                 theData.Radius * theUCtx.dDirUZ),
          gp_Vec(theData.ZX, theData.ZY, theData.ZZ),
          gp_Vec(-theData.Radius * theUCtx.dirUX,
                 -theData.Radius * theUCtx.dirUY,
                 -theData.Radius * theUCtx.dirUZ),
          aZero,
          aZero,
          gp_Vec(-theData.Radius * theUCtx.dDirUX,
                 -theData.Radius * theUCtx.dDirUY,
                 -theData.Radius * theUCtx.dDirUZ),
          aZero,
          aZero,
          aZero};
}

gp_Vec GeomGridEval_Cylinder::computeDN(const Data&     theData,
                                        const UContext& theUCtx,
                                        double,
                                        int theNU,
                                        int theNV)
{

  if (theNV > 1)
  {
    return gp_Vec(0.0, 0.0, 0.0);
  }

  if (theNV == 1)
  {
    if (theNU == 0)
    {
      return gp_Vec(theData.ZX, theData.ZY, theData.ZZ);
    }
    return gp_Vec(0.0, 0.0, 0.0);
  }

  const int aPhase = theNU % 4;

  double dirX, dirY, dirZ;
  switch (aPhase)
  {
    case 0:
      dirX = theUCtx.dirUX;
      dirY = theUCtx.dirUY;
      dirZ = theUCtx.dirUZ;
      break;
    case 1:
      dirX = theUCtx.dDirUX;
      dirY = theUCtx.dDirUY;
      dirZ = theUCtx.dDirUZ;
      break;
    case 2:
      dirX = -theUCtx.dirUX;
      dirY = -theUCtx.dirUY;
      dirZ = -theUCtx.dirUZ;
      break;
    case 3:
      dirX = -theUCtx.dDirUX;
      dirY = -theUCtx.dDirUY;
      dirZ = -theUCtx.dDirUZ;
      break;
    default:
      dirX = 0.0;
      dirY = 0.0;
      dirZ = 0.0;
      break;
  }

  return gp_Vec(theData.Radius * dirX, theData.Radius * dirY, theData.Radius * dirZ);
}

NCollection_Array2<gp_Pnt> GeomGridEval_Cylinder::EvaluateGrid(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  const Data aData = extractData();
  const int  aNbU  = theUParams.Length();
  const int  aNbV  = theVParams.Length();

  NCollection_Array2<gp_Pnt> aResult(1, aNbU, 1, aNbV);

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   aU    = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, aU);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double aV = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeD0(aData, aUCtx, aV));
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD1> GeomGridEval_Cylinder::EvaluateGridD1(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  const Data aData = extractData();
  const int  aNbU  = theUParams.Length();
  const int  aNbV  = theVParams.Length();

  NCollection_Array2<GeomGridEval::SurfD1> aResult(1, aNbU, 1, aNbV);

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   aU    = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, aU);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double aV = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeD1(aData, aUCtx, aV));
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD2> GeomGridEval_Cylinder::EvaluateGridD2(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  const Data aData = extractData();
  const int  aNbU  = theUParams.Length();
  const int  aNbV  = theVParams.Length();

  NCollection_Array2<GeomGridEval::SurfD2> aResult(1, aNbU, 1, aNbV);

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   aU    = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, aU);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double aV = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeD2(aData, aUCtx, aV));
    }
  }

  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD3> GeomGridEval_Cylinder::EvaluateGridD3(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD3>();
  }

  const Data aData = extractData();
  const int  aNbU  = theUParams.Length();
  const int  aNbV  = theVParams.Length();

  NCollection_Array2<GeomGridEval::SurfD3> aResult(1, aNbU, 1, aNbV);

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   aU    = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, aU);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double aV = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeD3(aData, aUCtx, aV));
    }
  }

  return aResult;
}

NCollection_Array2<gp_Vec> GeomGridEval_Cylinder::EvaluateGridDN(
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

  const Data aData = extractData();
  const int  aNbU  = theUParams.Length();
  const int  aNbV  = theVParams.Length();

  NCollection_Array2<gp_Vec> aResult(1, aNbU, 1, aNbV);

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   aU    = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, aU);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double aV = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeDN(aData, aUCtx, aV, theNU, theNV));
    }
  }

  return aResult;
}

NCollection_Array1<gp_Pnt> GeomGridEval_Cylinder::EvaluatePoints(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const Data                 aData = extractData();
  const int                  aNb   = theUVPairs.Length();
  NCollection_Array1<gp_Pnt> aResult(1, aNb);

  for (int i = 1; i <= aNb; ++i)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(i, computeD0(aData, aUCtx, aUV.Y()));
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD1> GeomGridEval_Cylinder::EvaluatePointsD1(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  const Data                               aData = extractData();
  const int                                aNb   = theUVPairs.Length();
  NCollection_Array1<GeomGridEval::SurfD1> aResult(1, aNb);

  for (int i = 1; i <= aNb; ++i)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(i, computeD1(aData, aUCtx, aUV.Y()));
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD2> GeomGridEval_Cylinder::EvaluatePointsD2(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  const Data                               aData = extractData();
  const int                                aNb   = theUVPairs.Length();
  NCollection_Array1<GeomGridEval::SurfD2> aResult(1, aNb);

  for (int i = 1; i <= aNb; ++i)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(i, computeD2(aData, aUCtx, aUV.Y()));
  }

  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD3> GeomGridEval_Cylinder::EvaluatePointsD3(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  const Data                               aData = extractData();
  const int                                aNb   = theUVPairs.Length();
  NCollection_Array1<GeomGridEval::SurfD3> aResult(1, aNb);

  for (int i = 1; i <= aNb; ++i)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(i, computeD3(aData, aUCtx, aUV.Y()));
  }

  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_Cylinder::EvaluatePointsDN(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs,
  int                                 theNU,
  int                                 theNV) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty() || theNU < 0 || theNV < 0 || (theNU + theNV) < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const Data                 aData = extractData();
  const int                  aNb   = theUVPairs.Length();
  NCollection_Array1<gp_Vec> aResult(1, aNb);

  for (int i = 1; i <= aNb; ++i)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + i - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(i, computeDN(aData, aUCtx, aUV.Y(), theNU, theNV));
  }

  return aResult;
}
