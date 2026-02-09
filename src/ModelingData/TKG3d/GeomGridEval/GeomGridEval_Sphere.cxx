

#include <GeomGridEval_Sphere.hpp>

#include <gp_Sphere.hpp>

#include <cmath>

GeomGridEval_Sphere::Data GeomGridEval_Sphere::extractData() const
{
  const gp_Sphere& aSph    = myGeom->Sphere();
  const gp_Pnt&    aCenter = aSph.Location();
  const gp_Dir&    aXDir   = aSph.Position().XDirection();
  const gp_Dir&    aYDir   = aSph.Position().YDirection();
  const gp_Dir&    aZDir   = aSph.Position().Direction();

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
          aSph.Radius()};
}

GeomGridEval_Sphere::UContext GeomGridEval_Sphere::computeUContext(const Data& theData, double theU)
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

gp_Pnt GeomGridEval_Sphere::computeD0(const Data& theData, const UContext& theUCtx, double theV)
{
  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const double RcosV = theData.Radius * cosV;
  const double RsinV = theData.Radius * sinV;

  return gp_Pnt(theData.CX + RcosV * theUCtx.dirUX + RsinV * theData.ZX,
                theData.CY + RcosV * theUCtx.dirUY + RsinV * theData.ZY,
                theData.CZ + RcosV * theUCtx.dirUZ + RsinV * theData.ZZ);
}

GeomGridEval::SurfD1 GeomGridEval_Sphere::computeD1(const Data&     theData,
                                                    const UContext& theUCtx,
                                                    double          theV)
{
  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const double RcosV = theData.Radius * cosV;
  const double RsinV = theData.Radius * sinV;

  return {gp_Pnt(theData.CX + RcosV * theUCtx.dirUX + RsinV * theData.ZX,
                 theData.CY + RcosV * theUCtx.dirUY + RsinV * theData.ZY,
                 theData.CZ + RcosV * theUCtx.dirUZ + RsinV * theData.ZZ),
          gp_Vec(RcosV * theUCtx.dDirUX, RcosV * theUCtx.dDirUY, RcosV * theUCtx.dDirUZ),
          gp_Vec(-RsinV * theUCtx.dirUX + RcosV * theData.ZX,
                 -RsinV * theUCtx.dirUY + RcosV * theData.ZY,
                 -RsinV * theUCtx.dirUZ + RcosV * theData.ZZ)};
}

GeomGridEval::SurfD2 GeomGridEval_Sphere::computeD2(const Data&     theData,
                                                    const UContext& theUCtx,
                                                    double          theV)
{
  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const double RcosV = theData.Radius * cosV;
  const double RsinV = theData.Radius * sinV;

  return {gp_Pnt(theData.CX + RcosV * theUCtx.dirUX + RsinV * theData.ZX,
                 theData.CY + RcosV * theUCtx.dirUY + RsinV * theData.ZY,
                 theData.CZ + RcosV * theUCtx.dirUZ + RsinV * theData.ZZ),
          gp_Vec(RcosV * theUCtx.dDirUX, RcosV * theUCtx.dDirUY, RcosV * theUCtx.dDirUZ),
          gp_Vec(-RsinV * theUCtx.dirUX + RcosV * theData.ZX,
                 -RsinV * theUCtx.dirUY + RcosV * theData.ZY,
                 -RsinV * theUCtx.dirUZ + RcosV * theData.ZZ),
          gp_Vec(-RcosV * theUCtx.dirUX, -RcosV * theUCtx.dirUY, -RcosV * theUCtx.dirUZ),
          gp_Vec(-RcosV * theUCtx.dirUX - RsinV * theData.ZX,
                 -RcosV * theUCtx.dirUY - RsinV * theData.ZY,
                 -RcosV * theUCtx.dirUZ - RsinV * theData.ZZ),
          gp_Vec(-RsinV * theUCtx.dDirUX, -RsinV * theUCtx.dDirUY, -RsinV * theUCtx.dDirUZ)};
}

GeomGridEval::SurfD3 GeomGridEval_Sphere::computeD3(const Data&     theData,
                                                    const UContext& theUCtx,
                                                    double          theV)
{
  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const double RcosV = theData.Radius * cosV;
  const double RsinV = theData.Radius * sinV;

  return {gp_Pnt(theData.CX + RcosV * theUCtx.dirUX + RsinV * theData.ZX,
                 theData.CY + RcosV * theUCtx.dirUY + RsinV * theData.ZY,
                 theData.CZ + RcosV * theUCtx.dirUZ + RsinV * theData.ZZ),
          gp_Vec(RcosV * theUCtx.dDirUX, RcosV * theUCtx.dDirUY, RcosV * theUCtx.dDirUZ),
          gp_Vec(-RsinV * theUCtx.dirUX + RcosV * theData.ZX,
                 -RsinV * theUCtx.dirUY + RcosV * theData.ZY,
                 -RsinV * theUCtx.dirUZ + RcosV * theData.ZZ),
          gp_Vec(-RcosV * theUCtx.dirUX, -RcosV * theUCtx.dirUY, -RcosV * theUCtx.dirUZ),
          gp_Vec(-RcosV * theUCtx.dirUX - RsinV * theData.ZX,
                 -RcosV * theUCtx.dirUY - RsinV * theData.ZY,
                 -RcosV * theUCtx.dirUZ - RsinV * theData.ZZ),
          gp_Vec(-RsinV * theUCtx.dDirUX, -RsinV * theUCtx.dDirUY, -RsinV * theUCtx.dDirUZ),
          gp_Vec(-RcosV * theUCtx.dDirUX, -RcosV * theUCtx.dDirUY, -RcosV * theUCtx.dDirUZ),
          gp_Vec(RsinV * theUCtx.dirUX - RcosV * theData.ZX,
                 RsinV * theUCtx.dirUY - RcosV * theData.ZY,
                 RsinV * theUCtx.dirUZ - RcosV * theData.ZZ),
          gp_Vec(RsinV * theUCtx.dirUX, RsinV * theUCtx.dirUY, RsinV * theUCtx.dirUZ),
          gp_Vec(-RcosV * theUCtx.dDirUX, -RcosV * theUCtx.dDirUY, -RcosV * theUCtx.dDirUZ)};
}

gp_Vec GeomGridEval_Sphere::computeDN(const Data&     theData,
                                      const UContext& theUCtx,
                                      double          theV,
                                      int             theNU,
                                      int             theNV)
{
  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const int aPhaseU = theNU % 4;
  const int aPhaseV = theNV % 4;

  double dirX, dirY, dirZ;
  switch (aPhaseU)
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

  double aCoeffVXY, aCoeffVZ;
  switch (aPhaseV)
  {
    case 0:
      aCoeffVXY = cosV;
      aCoeffVZ  = sinV;
      break;
    case 1:
      aCoeffVXY = -sinV;
      aCoeffVZ  = cosV;
      break;
    case 2:
      aCoeffVXY = -cosV;
      aCoeffVZ  = -sinV;
      break;
    case 3:
      aCoeffVXY = sinV;
      aCoeffVZ  = -cosV;
      break;
    default:
      aCoeffVXY = 0.0;
      aCoeffVZ  = 0.0;
      break;
  }

  double aZTermX = 0.0, aZTermY = 0.0, aZTermZ = 0.0;
  if (theNU == 0)
  {
    aZTermX = aCoeffVZ * theData.ZX;
    aZTermY = aCoeffVZ * theData.ZY;
    aZTermZ = aCoeffVZ * theData.ZZ;
  }

  return gp_Vec(theData.Radius * (aCoeffVXY * dirX + aZTermX),
                theData.Radius * (aCoeffVXY * dirY + aZTermY),
                theData.Radius * (aCoeffVXY * dirZ + aZTermZ));
}

NCollection_Array2<gp_Pnt> GeomGridEval_Sphere::EvaluateGrid(
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

NCollection_Array2<GeomGridEval::SurfD1> GeomGridEval_Sphere::EvaluateGridD1(
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

NCollection_Array2<GeomGridEval::SurfD2> GeomGridEval_Sphere::EvaluateGridD2(
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

NCollection_Array2<GeomGridEval::SurfD3> GeomGridEval_Sphere::EvaluateGridD3(
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

NCollection_Array2<gp_Vec> GeomGridEval_Sphere::EvaluateGridDN(
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

NCollection_Array1<gp_Pnt> GeomGridEval_Sphere::EvaluatePoints(
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

NCollection_Array1<GeomGridEval::SurfD1> GeomGridEval_Sphere::EvaluatePointsD1(
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

NCollection_Array1<GeomGridEval::SurfD2> GeomGridEval_Sphere::EvaluatePointsD2(
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

NCollection_Array1<GeomGridEval::SurfD3> GeomGridEval_Sphere::EvaluatePointsD3(
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

NCollection_Array1<gp_Vec> GeomGridEval_Sphere::EvaluatePointsDN(
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
