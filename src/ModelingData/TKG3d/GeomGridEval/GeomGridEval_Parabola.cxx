

#include <GeomGridEval_Parabola.hpp>

#include <gp_Parab.hpp>

#include <cmath>

NCollection_Array1<gp_Pnt> GeomGridEval_Parabola::EvaluateGrid(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Pnt> aResult(1, aNb);

  const gp_Parab& aParab  = myGeom->Parab();
  const gp_Pnt&   aCenter = aParab.Location();
  const gp_Dir    aXDir   = aParab.XAxis().Direction();
  const gp_Dir    aYDir   = aParab.YAxis().Direction();
  const double    aFocal  = aParab.Focal();

  const double aCX = aCenter.X();
  const double aCY = aCenter.Y();
  const double aCZ = aCenter.Z();
  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  const double aCoeff = 1.0 / (4.0 * aFocal);

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u = theParams.Value(i);

    const double u2Term = u * u * aCoeff;

    aResult.SetValue(i - theParams.Lower() + 1,
                     gp_Pnt(aCX + u2Term * aXX + u * aYX,
                            aCY + u2Term * aXY + u * aYY,
                            aCZ + u2Term * aXZ + u * aYZ));
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD1> GeomGridEval_Parabola::EvaluateGridD1(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD1> aResult(1, aNb);

  const gp_Parab& aParab  = myGeom->Parab();
  const gp_Pnt&   aCenter = aParab.Location();
  const gp_Dir    aXDir   = aParab.XAxis().Direction();
  const gp_Dir    aYDir   = aParab.YAxis().Direction();
  const double    aFocal  = aParab.Focal();

  const double aCX = aCenter.X();
  const double aCY = aCenter.Y();
  const double aCZ = aCenter.Z();
  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  const double aCoeff  = 1.0 / (4.0 * aFocal);
  const double aCoeff2 = 1.0 / (2.0 * aFocal);

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u = theParams.Value(i);

    const double u2Term = u * u * aCoeff;
    const double d1Term = u * aCoeff2;

    aResult.ChangeValue(i - theParams.Lower()
                        + 1) = {gp_Pnt(aCX + u2Term * aXX + u * aYX,
                                       aCY + u2Term * aXY + u * aYY,
                                       aCZ + u2Term * aXZ + u * aYZ),
                                gp_Vec(d1Term * aXX + aYX, d1Term * aXY + aYY, d1Term * aXZ + aYZ)};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD2> GeomGridEval_Parabola::EvaluateGridD2(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD2> aResult(1, aNb);

  const gp_Parab& aParab  = myGeom->Parab();
  const gp_Pnt&   aCenter = aParab.Location();
  const gp_Dir    aXDir   = aParab.XAxis().Direction();
  const gp_Dir    aYDir   = aParab.YAxis().Direction();
  const double    aFocal  = aParab.Focal();

  const double aCX = aCenter.X();
  const double aCY = aCenter.Y();
  const double aCZ = aCenter.Z();
  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  const double aCoeff  = 1.0 / (4.0 * aFocal);
  const double aCoeff2 = 1.0 / (2.0 * aFocal);
  const double aCoeff3 = aCoeff2;

  const gp_Vec aD2(aCoeff3 * aXX, aCoeff3 * aXY, aCoeff3 * aXZ);

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u = theParams.Value(i);

    const double u2Term = u * u * aCoeff;
    const double d1Term = u * aCoeff2;

    aResult.ChangeValue(i - theParams.Lower()
                        + 1) = {gp_Pnt(aCX + u2Term * aXX + u * aYX,
                                       aCY + u2Term * aXY + u * aYY,
                                       aCZ + u2Term * aXZ + u * aYZ),
                                gp_Vec(d1Term * aXX + aYX, d1Term * aXY + aYY, d1Term * aXZ + aYZ),
                                aD2};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD3> GeomGridEval_Parabola::EvaluateGridD3(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD3> aResult(1, aNb);

  const gp_Parab& aParab  = myGeom->Parab();
  const gp_Pnt&   aCenter = aParab.Location();
  const gp_Dir    aXDir   = aParab.XAxis().Direction();
  const gp_Dir    aYDir   = aParab.YAxis().Direction();
  const double    aFocal  = aParab.Focal();

  const double aCX = aCenter.X();
  const double aCY = aCenter.Y();
  const double aCZ = aCenter.Z();
  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  const double aCoeff  = 1.0 / (4.0 * aFocal);
  const double aCoeff2 = 1.0 / (2.0 * aFocal);
  const double aCoeff3 = aCoeff2;

  const gp_Vec aD2(aCoeff3 * aXX, aCoeff3 * aXY, aCoeff3 * aXZ);
  const gp_Vec aD3(0.0, 0.0, 0.0);

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u = theParams.Value(i);

    const double u2Term = u * u * aCoeff;
    const double d1Term = u * aCoeff2;

    aResult.ChangeValue(i - theParams.Lower()
                        + 1) = {gp_Pnt(aCX + u2Term * aXX + u * aYX,
                                       aCY + u2Term * aXY + u * aYY,
                                       aCZ + u2Term * aXZ + u * aYZ),
                                gp_Vec(d1Term * aXX + aYX, d1Term * aXY + aYY, d1Term * aXZ + aYZ),
                                aD2,
                                aD3};
  }
  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_Parabola::EvaluateGridDN(
  const NCollection_Array1<double>& theParams,
  int                               theN) const
{
  if (myGeom.IsNull() || theParams.IsEmpty() || theN < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Vec> aResult(1, aNb);

  const gp_Parab& aParab = myGeom->Parab();
  const gp_Dir&   aXDir  = aParab.XAxis().Direction();
  const gp_Dir&   aYDir  = aParab.YAxis().Direction();
  const double    aFocal = aParab.Focal();

  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  const double aCoeff2 = 1.0 / (2.0 * aFocal);

  if (theN == 1)
  {

    for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
    {
      const double u      = theParams.Value(i);
      const double d1Term = u * aCoeff2;
      aResult.SetValue(i - theParams.Lower() + 1,
                       gp_Vec(d1Term * aXX + aYX, d1Term * aXY + aYY, d1Term * aXZ + aYZ));
    }
  }
  else if (theN == 2)
  {

    const gp_Vec aD2(aCoeff2 * aXX, aCoeff2 * aXY, aCoeff2 * aXZ);
    for (int i = 1; i <= aNb; ++i)
    {
      aResult.SetValue(i, aD2);
    }
  }
  else
  {

    const gp_Vec aZero(0.0, 0.0, 0.0);
    for (int i = 1; i <= aNb; ++i)
    {
      aResult.SetValue(i, aZero);
    }
  }
  return aResult;
}
