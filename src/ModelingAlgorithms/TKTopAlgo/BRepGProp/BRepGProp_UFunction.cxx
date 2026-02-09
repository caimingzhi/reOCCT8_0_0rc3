#include <BRepGProp_UFunction.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>

BRepGProp_UFunction::BRepGProp_UFunction(const BRepGProp_Face& theSurface,
                                         const gp_Pnt&         theVertex,
                                         const bool            IsByPoint,
                                         const double*         theCoeffs)
    : mySurface(theSurface),
      myVertex(theVertex),
      myCoeffs(theCoeffs),
      myVParam(0.),
      myValueType(GProp_Unknown),
      myIsByPoint(IsByPoint)
{
}

bool BRepGProp_UFunction::Value(const double X, double& F)
{

  if (myValueType == GProp_Mass)
  {
    gp_XYZ aPMP0;
    double aTmpPar1;
    double aTmpPar2;

    F = VolumeValue(X, aPMP0, aTmpPar1, aTmpPar2);

    return true;
  }

  if (myValueType == GProp_CenterMassX || myValueType == GProp_CenterMassY
      || myValueType == GProp_CenterMassZ)
    return CenterMassValue(X, F);

  if (myValueType == GProp_InertiaXX || myValueType == GProp_InertiaYY
      || myValueType == GProp_InertiaZZ || myValueType == GProp_InertiaXY
      || myValueType == GProp_InertiaXZ || myValueType == GProp_InertiaYZ)
    return InertiaValue(X, F);

  return false;
}

double BRepGProp_UFunction::VolumeValue(const double X,
                                        gp_XYZ&      thePMP0,
                                        double&      theS,
                                        double&      theD1)
{
  gp_Pnt aPnt;
  gp_Vec aNorm;

  mySurface.Normal(X, myVParam, aPnt, aNorm);

  thePMP0 = aPnt.XYZ().Subtracted(myVertex.XYZ());

  if (myIsByPoint)
    return thePMP0.Dot(aNorm.XYZ());

  const double* aCoeff = myCoeffs;

  theS  = aNorm.X() * aCoeff[0] + aNorm.Y() * aCoeff[1] + aNorm.Z() * aCoeff[2];
  theD1 = thePMP0.X() * aCoeff[0] + thePMP0.Y() * aCoeff[1] + thePMP0.Z() * aCoeff[2] - aCoeff[3];

  return theS * theD1;
}

bool BRepGProp_UFunction::CenterMassValue(const double X, double& F)
{
  gp_XYZ aPmP0;
  double aS;
  double aD1;

  F = VolumeValue(X, aPmP0, aS, aD1);

  if (myIsByPoint)
  {
    switch (myValueType)
    {
      case GProp_CenterMassX:
        F *= aPmP0.X();
        break;
      case GProp_CenterMassY:
        F *= aPmP0.Y();
        break;
      case GProp_CenterMassZ:
        F *= aPmP0.Z();
        break;
      default:
        return false;
    }

    return true;
  }

  const double* aCoeff = myCoeffs;

  switch (myValueType)
  {
    case GProp_CenterMassX:
      F *= (aPmP0.X() - 0.5 * aCoeff[0] * aD1);
      break;
    case GProp_CenterMassY:
      F *= (aPmP0.Y() - 0.5 * aCoeff[1] * aD1);
      break;
    case GProp_CenterMassZ:
      F *= (aPmP0.Z() - 0.5 * aCoeff[2] * aD1);
      break;
    default:
      return false;
  }

  return true;
}

bool BRepGProp_UFunction::InertiaValue(const double X, double& F)
{
  gp_XYZ        aPmP0;
  double        aS;
  double        aD1;
  double        aParam1;
  double        aParam2;
  const double* aCoeffs = myCoeffs;

  F = VolumeValue(X, aPmP0, aS, aD1);

  if (myIsByPoint)
  {
    switch (myValueType)
    {
      case GProp_InertiaXX:
      case GProp_InertiaYZ:
        aParam1 = aPmP0.Y() - aCoeffs[1];
        aParam2 = aPmP0.Z() - aCoeffs[2];
        break;
      case GProp_InertiaYY:
      case GProp_InertiaXZ:
        aParam1 = aPmP0.X() - aCoeffs[0];
        aParam2 = aPmP0.Z() - aCoeffs[2];
        break;
      case GProp_InertiaZZ:
      case GProp_InertiaXY:
        aParam1 = aPmP0.X() - aCoeffs[0];
        aParam2 = aPmP0.Y() - aCoeffs[1];
        break;
      default:
        return false;
    }

    if (myValueType == GProp_InertiaXX || myValueType == GProp_InertiaYY
        || myValueType == GProp_InertiaZZ)
      F *= aParam1 * aParam1 + aParam2 * aParam2;
    else
      F *= -aParam1 * aParam2;

    return true;
  }

  double aD2 = aD1 * aD1;
  double aD3 = aD1 * aD2 / 3.;
  double aPPar1;
  double aPPar2;
  double aCoeff1;
  double aCoeff2;

  if (myValueType == GProp_InertiaXX || myValueType == GProp_InertiaYY
      || myValueType == GProp_InertiaZZ)
  {

    if (myValueType == GProp_InertiaXX)
    {
      aPPar1  = aPmP0.Y();
      aPPar2  = aPmP0.Z();
      aCoeff1 = aCoeffs[1];
      aCoeff2 = aCoeffs[2];
    }
    else if (myValueType == GProp_InertiaYY)
    {
      aPPar1  = aPmP0.X();
      aPPar2  = aPmP0.Z();
      aCoeff1 = aCoeffs[0];
      aCoeff2 = aCoeffs[2];
    }
    else
    {
      aPPar1  = aPmP0.X();
      aPPar2  = aPmP0.Y();
      aCoeff1 = aCoeffs[0];
      aCoeff2 = aCoeffs[1];
    }

    aPPar1 -= aCoeff1 * aD1;
    aPPar2 -= aCoeff2 * aD1;
    aParam1 = aPPar1 * aPPar1 * aD1 + aPPar1 * aCoeff1 * aD2 + aCoeff1 * aCoeff1 * aD3;
    aParam2 = aPPar2 * aPPar2 * aD1 + aPPar2 * aCoeff2 * aD2 + aCoeff2 * aCoeff2 * aD3;

    F = (aParam1 + aParam2) * aS;

    return true;
  }

  if (myValueType == GProp_InertiaXY || myValueType == GProp_InertiaYZ
      || myValueType == GProp_InertiaXZ)
  {

    if (myValueType == GProp_InertiaXY)
    {
      aPPar1  = aPmP0.X();
      aPPar2  = aPmP0.Y();
      aCoeff1 = aCoeffs[0];
      aCoeff2 = aCoeffs[1];
    }
    else if (myValueType == GProp_InertiaYZ)
    {
      aPPar1  = aPmP0.Y();
      aPPar2  = aPmP0.Z();
      aCoeff1 = aCoeffs[1];
      aCoeff2 = aCoeffs[2];
    }
    else
    {
      aPPar1  = aPmP0.X();
      aPPar2  = aPmP0.Z();
      aCoeff1 = aCoeffs[0];
      aCoeff2 = aCoeffs[2];
    }

    aD2 *= 0.5;
    aPPar1 -= aCoeff1 * aD1;
    aPPar2 -= aCoeff2 * aD1;
    aParam1 =
      aPPar1 * aPPar2 * aD1 + (aPPar1 * aCoeff2 + aPPar2 * aCoeff1) * aD2 + aCoeff1 * aCoeff2 * aD3;

    F = -aParam1 * aS;

    return true;
  }

  return false;
}
