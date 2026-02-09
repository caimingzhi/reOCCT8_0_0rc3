

#include <GeomGridEval_Hyperbola.hpp>

#include <gp_Hypr.hpp>

#include <cmath>

NCollection_Array1<gp_Pnt> GeomGridEval_Hyperbola::EvaluateGrid(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Pnt> aResult(1, aNb);

  const gp_Hypr& aHypr   = myGeom->Hypr();
  const gp_Pnt&  aCenter = aHypr.Location();
  const gp_Dir   aXDir   = aHypr.XAxis().Direction();
  const gp_Dir   aYDir   = aHypr.YAxis().Direction();
  const double   aMajR   = aHypr.MajorRadius();
  const double   aMinR   = aHypr.MinorRadius();

  const double aCX = aCenter.X();
  const double aCY = aCenter.Y();
  const double aCZ = aCenter.Z();
  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u     = theParams.Value(i);
    const double coshU = std::cosh(u);
    const double sinhU = std::sinh(u);

    aResult.SetValue(i - theParams.Lower() + 1,
                     gp_Pnt(aCX + aMajR * coshU * aXX + aMinR * sinhU * aYX,
                            aCY + aMajR * coshU * aXY + aMinR * sinhU * aYY,
                            aCZ + aMajR * coshU * aXZ + aMinR * sinhU * aYZ));
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD1> GeomGridEval_Hyperbola::EvaluateGridD1(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD1> aResult(1, aNb);

  const gp_Hypr& aHypr   = myGeom->Hypr();
  const gp_Pnt&  aCenter = aHypr.Location();
  const gp_Dir   aXDir   = aHypr.XAxis().Direction();
  const gp_Dir   aYDir   = aHypr.YAxis().Direction();
  const double   aMajR   = aHypr.MajorRadius();
  const double   aMinR   = aHypr.MinorRadius();

  const double aCX = aCenter.X();
  const double aCY = aCenter.Y();
  const double aCZ = aCenter.Z();
  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u     = theParams.Value(i);
    const double coshU = std::cosh(u);
    const double sinhU = std::sinh(u);

    aResult.ChangeValue(i - theParams.Lower()
                        + 1) = {gp_Pnt(aCX + aMajR * coshU * aXX + aMinR * sinhU * aYX,
                                       aCY + aMajR * coshU * aXY + aMinR * sinhU * aYY,
                                       aCZ + aMajR * coshU * aXZ + aMinR * sinhU * aYZ),
                                gp_Vec(aMajR * sinhU * aXX + aMinR * coshU * aYX,
                                       aMajR * sinhU * aXY + aMinR * coshU * aYY,
                                       aMajR * sinhU * aXZ + aMinR * coshU * aYZ)};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD2> GeomGridEval_Hyperbola::EvaluateGridD2(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD2> aResult(1, aNb);

  const gp_Hypr& aHypr   = myGeom->Hypr();
  const gp_Pnt&  aCenter = aHypr.Location();
  const gp_Dir   aXDir   = aHypr.XAxis().Direction();
  const gp_Dir   aYDir   = aHypr.YAxis().Direction();
  const double   aMajR   = aHypr.MajorRadius();
  const double   aMinR   = aHypr.MinorRadius();

  const double aCX = aCenter.X();
  const double aCY = aCenter.Y();
  const double aCZ = aCenter.Z();
  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u     = theParams.Value(i);
    const double coshU = std::cosh(u);
    const double sinhU = std::sinh(u);

    aResult.ChangeValue(i - theParams.Lower()
                        + 1) = {gp_Pnt(aCX + aMajR * coshU * aXX + aMinR * sinhU * aYX,
                                       aCY + aMajR * coshU * aXY + aMinR * sinhU * aYY,
                                       aCZ + aMajR * coshU * aXZ + aMinR * sinhU * aYZ),
                                gp_Vec(aMajR * sinhU * aXX + aMinR * coshU * aYX,
                                       aMajR * sinhU * aXY + aMinR * coshU * aYY,
                                       aMajR * sinhU * aXZ + aMinR * coshU * aYZ),
                                gp_Vec(aMajR * coshU * aXX + aMinR * sinhU * aYX,
                                       aMajR * coshU * aXY + aMinR * sinhU * aYY,
                                       aMajR * coshU * aXZ + aMinR * sinhU * aYZ)};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD3> GeomGridEval_Hyperbola::EvaluateGridD3(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD3> aResult(1, aNb);

  const gp_Hypr& aHypr   = myGeom->Hypr();
  const gp_Pnt&  aCenter = aHypr.Location();
  const gp_Dir   aXDir   = aHypr.XAxis().Direction();
  const gp_Dir   aYDir   = aHypr.YAxis().Direction();
  const double   aMajR   = aHypr.MajorRadius();
  const double   aMinR   = aHypr.MinorRadius();

  const double aCX = aCenter.X();
  const double aCY = aCenter.Y();
  const double aCZ = aCenter.Z();
  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u     = theParams.Value(i);
    const double coshU = std::cosh(u);
    const double sinhU = std::sinh(u);

    aResult.ChangeValue(i - theParams.Lower()
                        + 1) = {gp_Pnt(aCX + aMajR * coshU * aXX + aMinR * sinhU * aYX,
                                       aCY + aMajR * coshU * aXY + aMinR * sinhU * aYY,
                                       aCZ + aMajR * coshU * aXZ + aMinR * sinhU * aYZ),
                                gp_Vec(aMajR * sinhU * aXX + aMinR * coshU * aYX,
                                       aMajR * sinhU * aXY + aMinR * coshU * aYY,
                                       aMajR * sinhU * aXZ + aMinR * coshU * aYZ),
                                gp_Vec(aMajR * coshU * aXX + aMinR * sinhU * aYX,
                                       aMajR * coshU * aXY + aMinR * sinhU * aYY,
                                       aMajR * coshU * aXZ + aMinR * sinhU * aYZ),
                                gp_Vec(aMajR * sinhU * aXX + aMinR * coshU * aYX,
                                       aMajR * sinhU * aXY + aMinR * coshU * aYY,
                                       aMajR * sinhU * aXZ + aMinR * coshU * aYZ)};
  }
  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_Hyperbola::EvaluateGridDN(
  const NCollection_Array1<double>& theParams,
  int                               theN) const
{
  if (myGeom.IsNull() || theParams.IsEmpty() || theN < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Vec> aResult(1, aNb);

  const gp_Hypr& aHypr = myGeom->Hypr();
  const gp_Dir   aXDir = aHypr.XAxis().Direction();
  const gp_Dir   aYDir = aHypr.YAxis().Direction();
  const double   aMajR = aHypr.MajorRadius();
  const double   aMinR = aHypr.MinorRadius();

  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  const bool isOdd = (theN % 2) == 1;

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u     = theParams.Value(i);
    const double coshU = std::cosh(u);
    const double sinhU = std::sinh(u);

    if (isOdd)
    {

      aResult.SetValue(i - theParams.Lower() + 1,
                       gp_Vec(aMajR * sinhU * aXX + aMinR * coshU * aYX,
                              aMajR * sinhU * aXY + aMinR * coshU * aYY,
                              aMajR * sinhU * aXZ + aMinR * coshU * aYZ));
    }
    else
    {

      aResult.SetValue(i - theParams.Lower() + 1,
                       gp_Vec(aMajR * coshU * aXX + aMinR * sinhU * aYX,
                              aMajR * coshU * aXY + aMinR * sinhU * aYY,
                              aMajR * coshU * aXZ + aMinR * sinhU * aYZ));
    }
  }
  return aResult;
}
