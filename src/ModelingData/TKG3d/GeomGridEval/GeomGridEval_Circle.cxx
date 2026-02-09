

#include <GeomGridEval_Circle.hpp>

#include <gp_Circ.hpp>

#include <cmath>

NCollection_Array1<gp_Pnt> GeomGridEval_Circle::EvaluateGrid(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<gp_Pnt>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Pnt> aResult(1, aNb);

  const gp_Circ& aCirc   = myGeom->Circ();
  const gp_Pnt&  aCenter = aCirc.Location();
  const gp_Dir&  aXDir   = aCirc.Position().XDirection();
  const gp_Dir&  aYDir   = aCirc.Position().YDirection();
  const double   aRadius = aCirc.Radius();

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
                     gp_Pnt(aCX + aRadius * (cosU * aXX + sinU * aYX),
                            aCY + aRadius * (cosU * aXY + sinU * aYY),
                            aCZ + aRadius * (cosU * aXZ + sinU * aYZ)));
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD1> GeomGridEval_Circle::EvaluateGridD1(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD1>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD1> aResult(1, aNb);

  const gp_Circ& aCirc   = myGeom->Circ();
  const gp_Pnt&  aCenter = aCirc.Location();
  const gp_Dir&  aXDir   = aCirc.Position().XDirection();
  const gp_Dir&  aYDir   = aCirc.Position().YDirection();
  const double   aRadius = aCirc.Radius();

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
                        + 1) = {gp_Pnt(aCX + aRadius * (cosU * aXX + sinU * aYX),
                                       aCY + aRadius * (cosU * aXY + sinU * aYY),
                                       aCZ + aRadius * (cosU * aXZ + sinU * aYZ)),
                                gp_Vec(aRadius * (-sinU * aXX + cosU * aYX),
                                       aRadius * (-sinU * aXY + cosU * aYY),
                                       aRadius * (-sinU * aXZ + cosU * aYZ))};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD2> GeomGridEval_Circle::EvaluateGridD2(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD2>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD2> aResult(1, aNb);

  const gp_Circ& aCirc   = myGeom->Circ();
  const gp_Pnt&  aCenter = aCirc.Location();
  const gp_Dir&  aXDir   = aCirc.Position().XDirection();
  const gp_Dir&  aYDir   = aCirc.Position().YDirection();
  const double   aRadius = aCirc.Radius();

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
                        + 1) = {gp_Pnt(aCX + aRadius * (cosU * aXX + sinU * aYX),
                                       aCY + aRadius * (cosU * aXY + sinU * aYY),
                                       aCZ + aRadius * (cosU * aXZ + sinU * aYZ)),
                                gp_Vec(aRadius * (-sinU * aXX + cosU * aYX),
                                       aRadius * (-sinU * aXY + cosU * aYY),
                                       aRadius * (-sinU * aXZ + cosU * aYZ)),
                                gp_Vec(aRadius * (-cosU * aXX - sinU * aYX),
                                       aRadius * (-cosU * aXY - sinU * aYY),
                                       aRadius * (-cosU * aXZ - sinU * aYZ))};
  }
  return aResult;
}

NCollection_Array1<GeomGridEval::CurveD3> GeomGridEval_Circle::EvaluateGridD3(
  const NCollection_Array1<double>& theParams) const
{
  if (myGeom.IsNull() || theParams.IsEmpty())
  {
    return NCollection_Array1<GeomGridEval::CurveD3>();
  }

  const int                                 aNb = theParams.Size();
  NCollection_Array1<GeomGridEval::CurveD3> aResult(1, aNb);

  const gp_Circ& aCirc   = myGeom->Circ();
  const gp_Pnt&  aCenter = aCirc.Location();
  const gp_Dir&  aXDir   = aCirc.Position().XDirection();
  const gp_Dir&  aYDir   = aCirc.Position().YDirection();
  const double   aRadius = aCirc.Radius();

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
                        + 1) = {gp_Pnt(aCX + aRadius * (cosU * aXX + sinU * aYX),
                                       aCY + aRadius * (cosU * aXY + sinU * aYY),
                                       aCZ + aRadius * (cosU * aXZ + sinU * aYZ)),
                                gp_Vec(aRadius * (-sinU * aXX + cosU * aYX),
                                       aRadius * (-sinU * aXY + cosU * aYY),
                                       aRadius * (-sinU * aXZ + cosU * aYZ)),
                                gp_Vec(aRadius * (-cosU * aXX - sinU * aYX),
                                       aRadius * (-cosU * aXY - sinU * aYY),
                                       aRadius * (-cosU * aXZ - sinU * aYZ)),
                                gp_Vec(aRadius * (sinU * aXX - cosU * aYX),
                                       aRadius * (sinU * aXY - cosU * aYY),
                                       aRadius * (sinU * aXZ - cosU * aYZ))};
  }
  return aResult;
}

NCollection_Array1<gp_Vec> GeomGridEval_Circle::EvaluateGridDN(
  const NCollection_Array1<double>& theParams,
  int                               theN) const
{
  if (myGeom.IsNull() || theParams.IsEmpty() || theN < 1)
  {
    return NCollection_Array1<gp_Vec>();
  }

  const int                  aNb = theParams.Size();
  NCollection_Array1<gp_Vec> aResult(1, aNb);

  const gp_Circ& aCirc   = myGeom->Circ();
  const gp_Dir&  aXDir   = aCirc.Position().XDirection();
  const gp_Dir&  aYDir   = aCirc.Position().YDirection();
  const double   aRadius = aCirc.Radius();

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

    double aCoeffX, aCoeffY;
    switch (aPhase)
    {
      case 0:
        aCoeffX = -sinU;
        aCoeffY = cosU;
        break;
      case 1:
        aCoeffX = -cosU;
        aCoeffY = -sinU;
        break;
      case 2:
        aCoeffX = sinU;
        aCoeffY = -cosU;
        break;
      default:
        aCoeffX = cosU;
        aCoeffY = sinU;
        break;
    }

    aResult.SetValue(i - theParams.Lower() + 1,
                     gp_Vec(aRadius * (aCoeffX * aXX + aCoeffY * aYX),
                            aRadius * (aCoeffX * aXY + aCoeffY * aYY),
                            aRadius * (aCoeffX * aXZ + aCoeffY * aYZ)));
  }
  return aResult;
}
