

#include <GeomGridEval_Torus.hpp>

#include <gp_Torus.hpp>

#include <cmath>

GeomGridEval_Torus::Data GeomGridEval_Torus::extractData() const
{
  const gp_Torus& aTorus  = myGeom->Torus();
  const gp_Pnt&   aCenter = aTorus.Location();
  const gp_Dir&   aXDir   = aTorus.Position().XDirection();
  const gp_Dir&   aYDir   = aTorus.Position().YDirection();
  const gp_Dir&   aZDir   = aTorus.Position().Direction();

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
          aTorus.MajorRadius(),
          aTorus.MinorRadius()};
}

GeomGridEval_Torus::UContext GeomGridEval_Torus::computeUContext(const Data& theData, double theU)
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

gp_Pnt GeomGridEval_Torus::computeD0(const Data& theData, const UContext& theUCtx, double theV)
{
  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const double K = theData.MajorRadius + theData.MinorRadius * cosV;

  return gp_Pnt(theData.CX + K * theUCtx.dirUX + theData.MinorRadius * sinV * theData.ZX,
                theData.CY + K * theUCtx.dirUY + theData.MinorRadius * sinV * theData.ZY,
                theData.CZ + K * theUCtx.dirUZ + theData.MinorRadius * sinV * theData.ZZ);
}

GeomGridEval::SurfD1 GeomGridEval_Torus::computeD1(const Data&     theData,
                                                   const UContext& theUCtx,
                                                   double          theV)
{
  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const double K = theData.MajorRadius + theData.MinorRadius * cosV;

  const double dU1 = K * theUCtx.dDirUX;
  const double dU2 = K * theUCtx.dDirUY;
  const double dU3 = K * theUCtx.dDirUZ;

  const double dV1 =
    -theData.MinorRadius * sinV * theUCtx.dirUX + theData.MinorRadius * cosV * theData.ZX;
  const double dV2 =
    -theData.MinorRadius * sinV * theUCtx.dirUY + theData.MinorRadius * cosV * theData.ZY;
  const double dV3 =
    -theData.MinorRadius * sinV * theUCtx.dirUZ + theData.MinorRadius * cosV * theData.ZZ;

  return {gp_Pnt(theData.CX + K * theUCtx.dirUX + theData.MinorRadius * sinV * theData.ZX,
                 theData.CY + K * theUCtx.dirUY + theData.MinorRadius * sinV * theData.ZY,
                 theData.CZ + K * theUCtx.dirUZ + theData.MinorRadius * sinV * theData.ZZ),
          gp_Vec(dU1, dU2, dU3),
          gp_Vec(dV1, dV2, dV3)};
}

GeomGridEval::SurfD2 GeomGridEval_Torus::computeD2(const Data&     theData,
                                                   const UContext& theUCtx,
                                                   double          theV)
{
  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const double K = theData.MajorRadius + theData.MinorRadius * cosV;

  const double dU1 = K * theUCtx.dDirUX;
  const double dU2 = K * theUCtx.dDirUY;
  const double dU3 = K * theUCtx.dDirUZ;

  const double dV1 =
    -theData.MinorRadius * sinV * theUCtx.dirUX + theData.MinorRadius * cosV * theData.ZX;
  const double dV2 =
    -theData.MinorRadius * sinV * theUCtx.dirUY + theData.MinorRadius * cosV * theData.ZY;
  const double dV3 =
    -theData.MinorRadius * sinV * theUCtx.dirUZ + theData.MinorRadius * cosV * theData.ZZ;

  const double d2U1 = -K * theUCtx.dirUX;
  const double d2U2 = -K * theUCtx.dirUY;
  const double d2U3 = -K * theUCtx.dirUZ;

  const double d2V1 =
    -theData.MinorRadius * cosV * theUCtx.dirUX - theData.MinorRadius * sinV * theData.ZX;
  const double d2V2 =
    -theData.MinorRadius * cosV * theUCtx.dirUY - theData.MinorRadius * sinV * theData.ZY;
  const double d2V3 =
    -theData.MinorRadius * cosV * theUCtx.dirUZ - theData.MinorRadius * sinV * theData.ZZ;

  const double d2UV1 = -theData.MinorRadius * sinV * theUCtx.dDirUX;
  const double d2UV2 = -theData.MinorRadius * sinV * theUCtx.dDirUY;
  const double d2UV3 = -theData.MinorRadius * sinV * theUCtx.dDirUZ;

  return {gp_Pnt(theData.CX + K * theUCtx.dirUX + theData.MinorRadius * sinV * theData.ZX,
                 theData.CY + K * theUCtx.dirUY + theData.MinorRadius * sinV * theData.ZY,
                 theData.CZ + K * theUCtx.dirUZ + theData.MinorRadius * sinV * theData.ZZ),
          gp_Vec(dU1, dU2, dU3),
          gp_Vec(dV1, dV2, dV3),
          gp_Vec(d2U1, d2U2, d2U3),
          gp_Vec(d2V1, d2V2, d2V3),
          gp_Vec(d2UV1, d2UV2, d2UV3)};
}

GeomGridEval::SurfD3 GeomGridEval_Torus::computeD3(const Data&     theData,
                                                   const UContext& theUCtx,
                                                   double          theV)
{
  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const double R1 = theData.MinorRadius * cosV;
  const double R2 = theData.MinorRadius * sinV;

  const double K = theData.MajorRadius + R1;

  const double A3 = R2 * theUCtx.cosU;
  const double A4 = R2 * theUCtx.sinU;

  const double A5 = R1 * theUCtx.cosU;
  const double A6 = R1 * theUCtx.sinU;

  const double Som1X = K * theUCtx.dirUX;
  const double Som1Y = K * theUCtx.dirUY;
  const double Som1Z = K * theUCtx.dirUZ;

  const double Som3X = A3 * theData.XX + A4 * theData.YX;
  const double Som3Y = A3 * theData.XY + A4 * theData.YY;
  const double Som3Z = A3 * theData.XZ + A4 * theData.YZ;

  const double dU1 = K * theUCtx.dDirUX;
  const double dU2 = K * theUCtx.dDirUY;
  const double dU3 = K * theUCtx.dDirUZ;

  const double dV1 = -Som3X + R1 * theData.ZX;
  const double dV2 = -Som3Y + R1 * theData.ZY;
  const double dV3 = -Som3Z + R1 * theData.ZZ;

  const double d2U1 = -Som1X;
  const double d2U2 = -Som1Y;
  const double d2U3 = -Som1Z;

  const double d2V1 = -A5 * theData.XX - A6 * theData.YX - R2 * theData.ZX;
  const double d2V2 = -A5 * theData.XY - A6 * theData.YY - R2 * theData.ZY;
  const double d2V3 = -A5 * theData.XZ - A6 * theData.YZ - R2 * theData.ZZ;

  const double d2UV1 = A4 * theData.XX - A3 * theData.YX;
  const double d2UV2 = A4 * theData.XY - A3 * theData.YY;
  const double d2UV3 = A4 * theData.XZ - A3 * theData.YZ;

  const double d3U1 = -dU1;
  const double d3U2 = -dU2;
  const double d3U3 = -dU3;

  const double d3V1 = Som3X - R1 * theData.ZX;
  const double d3V2 = Som3Y - R1 * theData.ZY;
  const double d3V3 = Som3Z - R1 * theData.ZZ;

  const double d3UUV1 = Som3X;
  const double d3UUV2 = Som3Y;
  const double d3UUV3 = Som3Z;

  const double d3UVV1 = A6 * theData.XX - A5 * theData.YX;
  const double d3UVV2 = A6 * theData.XY - A5 * theData.YY;
  const double d3UVV3 = A6 * theData.XZ - A5 * theData.YZ;

  return {gp_Pnt(theData.CX + Som1X + R2 * theData.ZX,
                 theData.CY + Som1Y + R2 * theData.ZY,
                 theData.CZ + Som1Z + R2 * theData.ZZ),
          gp_Vec(dU1, dU2, dU3),
          gp_Vec(dV1, dV2, dV3),
          gp_Vec(d2U1, d2U2, d2U3),
          gp_Vec(d2V1, d2V2, d2V3),
          gp_Vec(d2UV1, d2UV2, d2UV3),
          gp_Vec(d3U1, d3U2, d3U3),
          gp_Vec(d3V1, d3V2, d3V3),
          gp_Vec(d3UUV1, d3UUV2, d3UUV3),
          gp_Vec(d3UVV1, d3UVV2, d3UVV3)};
}

gp_Vec GeomGridEval_Torus::computeDN(const Data&     theData,
                                     const UContext& theUCtx,
                                     double          theV,
                                     int             theNU,
                                     int             theNV)
{

  const double cosV = std::cos(theV);
  const double sinV = std::sin(theV);

  const int aPhaseU = theNU % 4;

  const int aPhaseV = theNV % 4;

  double dirDnX, dirDnY, dirDnZ;
  switch (aPhaseU)
  {
    case 0:
      dirDnX = theUCtx.dirUX;
      dirDnY = theUCtx.dirUY;
      dirDnZ = theUCtx.dirUZ;
      break;
    case 1:
      dirDnX = theUCtx.dDirUX;
      dirDnY = theUCtx.dDirUY;
      dirDnZ = theUCtx.dDirUZ;
      break;
    case 2:
      dirDnX = -theUCtx.dirUX;
      dirDnY = -theUCtx.dirUY;
      dirDnZ = -theUCtx.dirUZ;
      break;
    case 3:
    default:
      dirDnX = -theUCtx.dDirUX;
      dirDnY = -theUCtx.dDirUY;
      dirDnZ = -theUCtx.dDirUZ;
      break;
  }

  double dCosV;
  switch (aPhaseV)
  {
    case 0:
      dCosV = cosV;
      break;
    case 1:
      dCosV = -sinV;
      break;
    case 2:
      dCosV = -cosV;
      break;
    case 3:
    default:
      dCosV = sinV;
      break;
  }

  double dSinV;
  switch (aPhaseV)
  {
    case 0:
      dSinV = sinV;
      break;
    case 1:
      dSinV = cosV;
      break;
    case 2:
      dSinV = -sinV;
      break;
    case 3:
    default:
      dSinV = -cosV;
      break;
  }

  double resX, resY, resZ;

  if (theNV == 0)
  {

    const double K = theData.MajorRadius + theData.MinorRadius * cosV;
    resX           = K * dirDnX;
    resY           = K * dirDnY;
    resZ           = K * dirDnZ;
  }
  else if (theNU == 0)
  {

    const double dK = theData.MinorRadius * dCosV;
    resX            = dK * dirDnX + theData.MinorRadius * dSinV * theData.ZX;
    resY            = dK * dirDnY + theData.MinorRadius * dSinV * theData.ZY;
    resZ            = dK * dirDnZ + theData.MinorRadius * dSinV * theData.ZZ;
  }
  else
  {

    const double coeff = theData.MinorRadius * dCosV;
    resX               = coeff * dirDnX;
    resY               = coeff * dirDnY;
    resZ               = coeff * dirDnZ;
  }

  return gp_Vec(resX, resY, resZ);
}

NCollection_Array2<gp_Pnt> GeomGridEval_Torus::EvaluateGrid(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<gp_Pnt>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array2<gp_Pnt> aResult(1, aNbU, 1, aNbV);
  const Data                 aData = extractData();

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   u     = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, u);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double v = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeD0(aData, aUCtx, v));
    }
  }
  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD1> GeomGridEval_Torus::EvaluateGridD1(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD1>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array2<GeomGridEval::SurfD1> aResult(1, aNbU, 1, aNbV);
  const Data                               aData = extractData();

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   u     = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, u);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double v = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeD1(aData, aUCtx, v));
    }
  }
  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD2> GeomGridEval_Torus::EvaluateGridD2(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD2>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array2<GeomGridEval::SurfD2> aResult(1, aNbU, 1, aNbV);
  const Data                               aData = extractData();

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   u     = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, u);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double v = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeD2(aData, aUCtx, v));
    }
  }
  return aResult;
}

NCollection_Array2<GeomGridEval::SurfD3> GeomGridEval_Torus::EvaluateGridD3(
  const NCollection_Array1<double>& theUParams,
  const NCollection_Array1<double>& theVParams) const
{
  if (myGeom.IsNull() || theUParams.IsEmpty() || theVParams.IsEmpty())
  {
    return NCollection_Array2<GeomGridEval::SurfD3>();
  }

  const int aNbU = theUParams.Size();
  const int aNbV = theVParams.Size();

  NCollection_Array2<GeomGridEval::SurfD3> aResult(1, aNbU, 1, aNbV);
  const Data                               aData = extractData();

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   u     = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, u);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double v = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeD3(aData, aUCtx, v));
    }
  }
  return aResult;
}

NCollection_Array2<gp_Vec> GeomGridEval_Torus::EvaluateGridDN(
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
  const Data                 aData = extractData();

  for (int iU = 1; iU <= aNbU; ++iU)
  {
    const double   u     = theUParams.Value(theUParams.Lower() + iU - 1);
    const UContext aUCtx = computeUContext(aData, u);

    for (int iV = 1; iV <= aNbV; ++iV)
    {
      const double v = theVParams.Value(theVParams.Lower() + iV - 1);
      aResult.SetValue(iU, iV, computeDN(aData, aUCtx, v, theNU, theNV));
    }
  }
  return aResult;
}

NCollection_Array1<gp_Pnt> GeomGridEval_Torus::EvaluatePoints(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const int                  aNbPts = theUVPairs.Size();
  NCollection_Array1<gp_Pnt> aResult(1, aNbPts);
  const Data                 aData = extractData();

  for (int iPt = 1; iPt <= aNbPts; ++iPt)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + iPt - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(iPt, computeD0(aData, aUCtx, aUV.Y()));
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD1> GeomGridEval_Torus::EvaluatePointsD1(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD1>();
  }

  const int                                aNbPts = theUVPairs.Size();
  NCollection_Array1<GeomGridEval::SurfD1> aResult(1, aNbPts);
  const Data                               aData = extractData();

  for (int iPt = 1; iPt <= aNbPts; ++iPt)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + iPt - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(iPt, computeD1(aData, aUCtx, aUV.Y()));
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD2> GeomGridEval_Torus::EvaluatePointsD2(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD2>();
  }

  const int                                aNbPts = theUVPairs.Size();
  NCollection_Array1<GeomGridEval::SurfD2> aResult(1, aNbPts);
  const Data                               aData = extractData();

  for (int iPt = 1; iPt <= aNbPts; ++iPt)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + iPt - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(iPt, computeD2(aData, aUCtx, aUV.Y()));
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::SurfD3> GeomGridEval_Torus::EvaluatePointsD3(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::SurfD3>();
  }

  const int                                aNbPts = theUVPairs.Size();
  NCollection_Array1<GeomGridEval::SurfD3> aResult(1, aNbPts);
  const Data                               aData = extractData();

  for (int iPt = 1; iPt <= aNbPts; ++iPt)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + iPt - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(iPt, computeD3(aData, aUCtx, aUV.Y()));
  }
  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_Torus::EvaluatePointsDN(
  const NCollection_Array1<gp_Pnt2d>& theUVPairs,
  int                                 theNU,
  int                                 theNV) const
{
  if (myGeom.IsNull() || theUVPairs.IsEmpty() || theNU < 0 || theNV < 0 || (theNU + theNV) < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const int                  aNbPts = theUVPairs.Size();
  NCollection_Array1<gp_Vec> aResult(1, aNbPts);
  const Data                 aData = extractData();

  for (int iPt = 1; iPt <= aNbPts; ++iPt)
  {
    const gp_Pnt2d& aUV   = theUVPairs.Value(theUVPairs.Lower() + iPt - 1);
    const UContext  aUCtx = computeUContext(aData, aUV.X());
    aResult.SetValue(iPt, computeDN(aData, aUCtx, aUV.Y(), theNU, theNV));
  }
  return aResult;
}
