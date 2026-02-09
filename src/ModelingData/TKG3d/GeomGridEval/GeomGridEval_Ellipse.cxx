

#include <GeomGridEval_Ellipse.hpp>

#include <gp_Elips.hpp>

#include <cmath>

NCollection_Array1<gp_Pnt> GeomGridEval_Ellipse::EvaluateGrid(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Pnt> aResult(1, aNb);

  const gp_Elips& anElips = myGeom->Elips();
  const gp_Pnt&   aCenter = anElips.Location();
  const gp_Dir    aXDir   = anElips.XAxis().Direction();
  const gp_Dir    aYDir   = anElips.YAxis().Direction();
  const double    aMajR   = anElips.MajorRadius();
  const double    aMinR   = anElips.MinorRadius();

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
    const double u    = theParams.Value(i);
    const double cosU = std::cos(u);
    const double sinU = std::sin(u);

    aResult.SetValue(i - theParams.Lower() + 1,
                     gp_Pnt(aCX + aMajR * cosU * aXX + aMinR * sinU * aYX,
                            aCY + aMajR * cosU * aXY + aMinR * sinU * aYY,
                            aCZ + aMajR * cosU * aXZ + aMinR * sinU * aYZ));
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD1> GeomGridEval_Ellipse::EvaluateGridD1(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD1> aResult(1, aNb);

  const gp_Elips& anElips = myGeom->Elips();
  const gp_Pnt&   aCenter = anElips.Location();
  const gp_Dir    aXDir   = anElips.XAxis().Direction();
  const gp_Dir    aYDir   = anElips.YAxis().Direction();
  const double    aMajR   = anElips.MajorRadius();
  const double    aMinR   = anElips.MinorRadius();

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
    const double u    = theParams.Value(i);
    const double cosU = std::cos(u);
    const double sinU = std::sin(u);

    aResult.ChangeValue(i - theParams.Lower()
                        + 1) = {gp_Pnt(aCX + aMajR * cosU * aXX + aMinR * sinU * aYX,
                                       aCY + aMajR * cosU * aXY + aMinR * sinU * aYY,
                                       aCZ + aMajR * cosU * aXZ + aMinR * sinU * aYZ),
                                gp_Vec(-aMajR * sinU * aXX + aMinR * cosU * aYX,
                                       -aMajR * sinU * aXY + aMinR * cosU * aYY,
                                       -aMajR * sinU * aXZ + aMinR * cosU * aYZ)};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD2> GeomGridEval_Ellipse::EvaluateGridD2(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD2> aResult(1, aNb);

  const gp_Elips& anElips = myGeom->Elips();
  const gp_Pnt&   aCenter = anElips.Location();
  const gp_Dir    aXDir   = anElips.XAxis().Direction();
  const gp_Dir    aYDir   = anElips.YAxis().Direction();
  const double    aMajR   = anElips.MajorRadius();
  const double    aMinR   = anElips.MinorRadius();

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
    const double u    = theParams.Value(i);
    const double cosU = std::cos(u);
    const double sinU = std::sin(u);

    aResult.ChangeValue(i - theParams.Lower()
                        + 1) = {gp_Pnt(aCX + aMajR * cosU * aXX + aMinR * sinU * aYX,
                                       aCY + aMajR * cosU * aXY + aMinR * sinU * aYY,
                                       aCZ + aMajR * cosU * aXZ + aMinR * sinU * aYZ),
                                gp_Vec(-aMajR * sinU * aXX + aMinR * cosU * aYX,
                                       -aMajR * sinU * aXY + aMinR * cosU * aYY,
                                       -aMajR * sinU * aXZ + aMinR * cosU * aYZ),
                                gp_Vec(-aMajR * cosU * aXX - aMinR * sinU * aYX,
                                       -aMajR * cosU * aXY - aMinR * sinU * aYY,
                                       -aMajR * cosU * aXZ - aMinR * sinU * aYZ)};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD3> GeomGridEval_Ellipse::EvaluateGridD3(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD3> aResult(1, aNb);

  const gp_Elips& anElips = myGeom->Elips();
  const gp_Pnt&   aCenter = anElips.Location();
  const gp_Dir    aXDir   = anElips.XAxis().Direction();
  const gp_Dir    aYDir   = anElips.YAxis().Direction();
  const double    aMajR   = anElips.MajorRadius();
  const double    aMinR   = anElips.MinorRadius();

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
    const double u    = theParams.Value(i);
    const double cosU = std::cos(u);
    const double sinU = std::sin(u);

    aResult.ChangeValue(i - theParams.Lower()
                        + 1) = {gp_Pnt(aCX + aMajR * cosU * aXX + aMinR * sinU * aYX,
                                       aCY + aMajR * cosU * aXY + aMinR * sinU * aYY,
                                       aCZ + aMajR * cosU * aXZ + aMinR * sinU * aYZ),
                                gp_Vec(-aMajR * sinU * aXX + aMinR * cosU * aYX,
                                       -aMajR * sinU * aXY + aMinR * cosU * aYY,
                                       -aMajR * sinU * aXZ + aMinR * cosU * aYZ),
                                gp_Vec(-aMajR * cosU * aXX - aMinR * sinU * aYX,
                                       -aMajR * cosU * aXY - aMinR * sinU * aYY,
                                       -aMajR * cosU * aXZ - aMinR * sinU * aYZ),
                                gp_Vec(aMajR * sinU * aXX - aMinR * cosU * aYX,
                                       aMajR * sinU * aXY - aMinR * cosU * aYY,
                                       aMajR * sinU * aXZ - aMinR * cosU * aYZ)};
  }
  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_Ellipse::EvaluateGridDN(
  const NCollection_Array1<double>& theParams,
  int                               theN) const
{
  if (myGeom.IsNull() || theParams.IsEmpty() || theN < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Vec> aResult(1, aNb);

  const gp_Elips& anElips = myGeom->Elips();
  const gp_Dir    aXDir   = anElips.XAxis().Direction();
  const gp_Dir    aYDir   = anElips.YAxis().Direction();
  const double    aMajR   = anElips.MajorRadius();
  const double    aMinR   = anElips.MinorRadius();

  const double aXX = aXDir.X();
  const double aXY = aXDir.Y();
  const double aXZ = aXDir.Z();
  const double aYX = aYDir.X();
  const double aYY = aYDir.Y();
  const double aYZ = aYDir.Z();

  const int aPhase = (theN - 1) % 4;

  for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
  {
    const double u    = theParams.Value(i);
    const double cosU = std::cos(u);
    const double sinU = std::sin(u);

    double aCoeffMajR, aCoeffMinR;
    switch (aPhase)
    {
      case 0:
        aCoeffMajR = -sinU;
        aCoeffMinR = cosU;
        break;
      case 1:
        aCoeffMajR = -cosU;
        aCoeffMinR = -sinU;
        break;
      case 2:
        aCoeffMajR = sinU;
        aCoeffMinR = -cosU;
        break;
      default:
        aCoeffMajR = cosU;
        aCoeffMinR = sinU;
        break;
    }

    aResult.SetValue(i - theParams.Lower() + 1,
                     gp_Vec(aMajR * aCoeffMajR * aXX + aMinR * aCoeffMinR * aYX,
                            aMajR * aCoeffMajR * aXY + aMinR * aCoeffMinR * aYY,
                            aMajR * aCoeffMajR * aXZ + aMinR * aCoeffMinR * aYZ));
  }
  return aResult;
}
