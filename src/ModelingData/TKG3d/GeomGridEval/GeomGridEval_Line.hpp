#pragma once

#include <Geom_Line.hpp>
#include <GeomGridEval.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_Line
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_Line(const occ::handle<Geom_Line>& theLine)
      : myGeom(theLine)
  {
  }

  GeomGridEval_Line(const GeomGridEval_Line&)            = delete;
  GeomGridEval_Line& operator=(const GeomGridEval_Line&) = delete;
  GeomGridEval_Line(GeomGridEval_Line&&)                 = delete;
  GeomGridEval_Line& operator=(GeomGridEval_Line&&)      = delete;

  const occ::handle<Geom_Line>& Geometry() const { return myGeom; }

  NCollection_Array1<gp_Pnt> EvaluateGrid(const NCollection_Array1<double>& theParams) const
  {
    if (myGeom.IsNull() || theParams.IsEmpty())
    {
      return NCollection_Array1<gp_Pnt>();
    }

    NCollection_Array1<gp_Pnt> aResult(1, theParams.Size());

    const gp_Lin& aLin = myGeom->Lin();
    const gp_Pnt& aLoc = aLin.Location();
    const gp_Dir& aDir = aLin.Direction();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aDirX = aDir.X();
    const double aDirY = aDir.Y();
    const double aDirZ = aDir.Z();

    for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
    {
      const double t = theParams.Value(i);
      aResult.SetValue(i - theParams.Lower() + 1,
                       gp_Pnt(aLocX + t * aDirX, aLocY + t * aDirY, aLocZ + t * aDirZ));
    }
    return aResult;
  }

  NCollection_Array1<GeomGridEval::CurveD1> EvaluateGridD1(
    const NCollection_Array1<double>& theParams) const
  {
    if (myGeom.IsNull() || theParams.IsEmpty())
    {
      return NCollection_Array1<GeomGridEval::CurveD1>();
    }

    NCollection_Array1<GeomGridEval::CurveD1> aResult(1, theParams.Size());

    const gp_Lin& aLin = myGeom->Lin();
    const gp_Pnt& aLoc = aLin.Location();
    const gp_Dir& aDir = aLin.Direction();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aDirX = aDir.X();
    const double aDirY = aDir.Y();
    const double aDirZ = aDir.Z();

    const gp_Vec aD1(aDirX, aDirY, aDirZ);

    for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
    {
      const double t           = theParams.Value(i);
      aResult.ChangeValue(i - theParams.Lower()
                          + 1) = {gp_Pnt(aLocX + t * aDirX, aLocY + t * aDirY, aLocZ + t * aDirZ),
                                  aD1};
    }
    return aResult;
  }

  NCollection_Array1<GeomGridEval::CurveD2> EvaluateGridD2(
    const NCollection_Array1<double>& theParams) const
  {
    if (myGeom.IsNull() || theParams.IsEmpty())
    {
      return NCollection_Array1<GeomGridEval::CurveD2>();
    }

    NCollection_Array1<GeomGridEval::CurveD2> aResult(1, theParams.Size());

    const gp_Lin& aLin = myGeom->Lin();
    const gp_Pnt& aLoc = aLin.Location();
    const gp_Dir& aDir = aLin.Direction();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aDirX = aDir.X();
    const double aDirY = aDir.Y();
    const double aDirZ = aDir.Z();

    const gp_Vec aD1(aDirX, aDirY, aDirZ);
    const gp_Vec aD2(0, 0, 0);

    for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
    {
      const double t = theParams.Value(i);
      aResult.ChangeValue(
        i - theParams.Lower()
        + 1) = {gp_Pnt(aLocX + t * aDirX, aLocY + t * aDirY, aLocZ + t * aDirZ), aD1, aD2};
    }
    return aResult;
  }

  NCollection_Array1<GeomGridEval::CurveD3> EvaluateGridD3(
    const NCollection_Array1<double>& theParams) const
  {
    if (myGeom.IsNull() || theParams.IsEmpty())
    {
      return NCollection_Array1<GeomGridEval::CurveD3>();
    }

    NCollection_Array1<GeomGridEval::CurveD3> aResult(1, theParams.Size());

    const gp_Lin& aLin = myGeom->Lin();
    const gp_Pnt& aLoc = aLin.Location();
    const gp_Dir& aDir = aLin.Direction();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aDirX = aDir.X();
    const double aDirY = aDir.Y();
    const double aDirZ = aDir.Z();

    const gp_Vec aD1(aDirX, aDirY, aDirZ);
    const gp_Vec aZero(0, 0, 0);

    for (int i = theParams.Lower(); i <= theParams.Upper(); ++i)
    {
      const double t = theParams.Value(i);
      aResult.ChangeValue(
        i - theParams.Lower()
        + 1) = {gp_Pnt(aLocX + t * aDirX, aLocY + t * aDirY, aLocZ + t * aDirZ), aD1, aZero, aZero};
    }
    return aResult;
  }

  NCollection_Array1<gp_Vec> EvaluateGridDN(const NCollection_Array1<double>& theParams,
                                            int                               theN) const
  {
    if (myGeom.IsNull() || theParams.IsEmpty() || theN < 1)
    {
      return NCollection_Array1<gp_Vec>();
    }

    NCollection_Array1<gp_Vec> aResult(1, theParams.Size());

    if (theN == 1)
    {

      const gp_Dir aDir = myGeom->Lin().Direction();
      const gp_Vec aD1(aDir.X(), aDir.Y(), aDir.Z());
      for (int i = 1; i <= theParams.Size(); ++i)
      {
        aResult.SetValue(i, aD1);
      }
    }
    else
    {

      const gp_Vec aZero(0, 0, 0);
      for (int i = 1; i <= theParams.Size(); ++i)
      {
        aResult.SetValue(i, aZero);
      }
    }
    return aResult;
  }

private:
  occ::handle<Geom_Line> myGeom;
};
