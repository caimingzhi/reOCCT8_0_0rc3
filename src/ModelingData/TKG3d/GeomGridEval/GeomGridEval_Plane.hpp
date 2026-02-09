#pragma once

#include <Geom_Plane.hpp>
#include <GeomGridEval.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_Plane
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_Plane(const occ::handle<Geom_Plane>& thePlane)
      : myGeom(thePlane)
  {
  }

  GeomGridEval_Plane(const GeomGridEval_Plane&)            = delete;
  GeomGridEval_Plane& operator=(const GeomGridEval_Plane&) = delete;
  GeomGridEval_Plane(GeomGridEval_Plane&&)                 = delete;
  GeomGridEval_Plane& operator=(GeomGridEval_Plane&&)      = delete;

  const occ::handle<Geom_Plane>& Geometry() const { return myGeom; }

  NCollection_Array2<gp_Pnt> EvaluateGrid(const NCollection_Array1<double>& theUParams,
                                          const NCollection_Array1<double>& theVParams) const
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (myGeom.IsNull() || aNbU == 0 || aNbV == 0)
    {
      return NCollection_Array2<gp_Pnt>();
    }

    NCollection_Array2<gp_Pnt> aResult(1, aNbU, 1, aNbV);

    const gp_Pln& aPln  = myGeom->Pln();
    const gp_Pnt& aLoc  = aPln.Location();
    const gp_Dir& aXDir = aPln.Position().XDirection();
    const gp_Dir& aYDir = aPln.Position().YDirection();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aXX   = aXDir.X();
    const double aXY   = aXDir.Y();
    const double aXZ   = aXDir.Z();
    const double aYX   = aYDir.X();
    const double aYY   = aYDir.Y();
    const double aYZ   = aYDir.Z();

    for (int iU = 1; iU <= aNbU; ++iU)
    {
      const double u  = theUParams.Value(theUParams.Lower() + iU - 1);
      const double uX = aLocX + u * aXX;
      const double uY = aLocY + u * aXY;
      const double uZ = aLocZ + u * aXZ;

      for (int iV = 1; iV <= aNbV; ++iV)
      {
        const double v = theVParams.Value(theVParams.Lower() + iV - 1);
        aResult.SetValue(iU, iV, gp_Pnt(uX + v * aYX, uY + v * aYY, uZ + v * aYZ));
      }
    }
    return aResult;
  }

  NCollection_Array2<GeomGridEval::SurfD1> EvaluateGridD1(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (myGeom.IsNull() || aNbU == 0 || aNbV == 0)
    {
      return NCollection_Array2<GeomGridEval::SurfD1>();
    }

    NCollection_Array2<GeomGridEval::SurfD1> aResult(1, aNbU, 1, aNbV);

    const gp_Pln& aPln  = myGeom->Pln();
    const gp_Pnt& aLoc  = aPln.Location();
    const gp_Dir& aXDir = aPln.Position().XDirection();
    const gp_Dir& aYDir = aPln.Position().YDirection();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aXX   = aXDir.X();
    const double aXY   = aXDir.Y();
    const double aXZ   = aXDir.Z();
    const double aYX   = aYDir.X();
    const double aYY   = aYDir.Y();
    const double aYZ   = aYDir.Z();

    const gp_Vec aD1U(aXX, aXY, aXZ);
    const gp_Vec aD1V(aYX, aYY, aYZ);

    for (int iU = 1; iU <= aNbU; ++iU)
    {
      const double u  = theUParams.Value(theUParams.Lower() + iU - 1);
      const double uX = aLocX + u * aXX;
      const double uY = aLocY + u * aXY;
      const double uZ = aLocZ + u * aXZ;

      for (int iV = 1; iV <= aNbV; ++iV)
      {
        const double v          = theVParams.Value(theVParams.Lower() + iV - 1);
        aResult.ChangeValue(iU,
                            iV) = {gp_Pnt(uX + v * aYX, uY + v * aYY, uZ + v * aYZ), aD1U, aD1V};
      }
    }
    return aResult;
  }

  NCollection_Array2<GeomGridEval::SurfD2> EvaluateGridD2(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (myGeom.IsNull() || aNbU == 0 || aNbV == 0)
    {
      return NCollection_Array2<GeomGridEval::SurfD2>();
    }

    NCollection_Array2<GeomGridEval::SurfD2> aResult(1, aNbU, 1, aNbV);

    const gp_Pln& aPln  = myGeom->Pln();
    const gp_Pnt& aLoc  = aPln.Location();
    const gp_Dir& aXDir = aPln.Position().XDirection();
    const gp_Dir& aYDir = aPln.Position().YDirection();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aXX   = aXDir.X();
    const double aXY   = aXDir.Y();
    const double aXZ   = aXDir.Z();
    const double aYX   = aYDir.X();
    const double aYY   = aYDir.Y();
    const double aYZ   = aYDir.Z();

    const gp_Vec aD1U(aXX, aXY, aXZ);
    const gp_Vec aD1V(aYX, aYY, aYZ);
    const gp_Vec aZero(0, 0, 0);

    for (int iU = 1; iU <= aNbU; ++iU)
    {
      const double u  = theUParams.Value(theUParams.Lower() + iU - 1);
      const double uX = aLocX + u * aXX;
      const double uY = aLocY + u * aXY;
      const double uZ = aLocZ + u * aXZ;

      for (int iV = 1; iV <= aNbV; ++iV)
      {
        const double v = theVParams.Value(theVParams.Lower() + iV - 1);
        aResult.ChangeValue(
          iU,
          iV) = {gp_Pnt(uX + v * aYX, uY + v * aYY, uZ + v * aYZ), aD1U, aD1V, aZero, aZero, aZero};
      }
    }
    return aResult;
  }

  NCollection_Array2<GeomGridEval::SurfD3> EvaluateGridD3(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (myGeom.IsNull() || aNbU == 0 || aNbV == 0)
    {
      return NCollection_Array2<GeomGridEval::SurfD3>();
    }

    NCollection_Array2<GeomGridEval::SurfD3> aResult(1, aNbU, 1, aNbV);

    const gp_Pln& aPln  = myGeom->Pln();
    const gp_Pnt& aLoc  = aPln.Location();
    const gp_Dir& aXDir = aPln.Position().XDirection();
    const gp_Dir& aYDir = aPln.Position().YDirection();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aXX   = aXDir.X();
    const double aXY   = aXDir.Y();
    const double aXZ   = aXDir.Z();
    const double aYX   = aYDir.X();
    const double aYY   = aYDir.Y();
    const double aYZ   = aYDir.Z();

    const gp_Vec aD1U(aXX, aXY, aXZ);
    const gp_Vec aD1V(aYX, aYY, aYZ);
    const gp_Vec aZero(0, 0, 0);

    for (int iU = 1; iU <= aNbU; ++iU)
    {
      const double u  = theUParams.Value(theUParams.Lower() + iU - 1);
      const double uX = aLocX + u * aXX;
      const double uY = aLocY + u * aXY;
      const double uZ = aLocZ + u * aXZ;

      for (int iV = 1; iV <= aNbV; ++iV)
      {
        const double v              = theVParams.Value(theVParams.Lower() + iV - 1);
        aResult.ChangeValue(iU, iV) = {gp_Pnt(uX + v * aYX, uY + v * aYY, uZ + v * aYZ),
                                       aD1U,
                                       aD1V,
                                       aZero,
                                       aZero,
                                       aZero,
                                       aZero,
                                       aZero,
                                       aZero,
                                       aZero};
      }
    }
    return aResult;
  }

  NCollection_Array2<gp_Vec> EvaluateGridDN(const NCollection_Array1<double>& theUParams,
                                            const NCollection_Array1<double>& theVParams,
                                            int                               theNU,
                                            int                               theNV) const
  {
    const int aNbU = theUParams.Size();
    const int aNbV = theVParams.Size();
    if (myGeom.IsNull() || aNbU == 0 || aNbV == 0 || theNU < 0 || theNV < 0 || (theNU + theNV) < 1)
    {
      return NCollection_Array2<gp_Vec>();
    }

    NCollection_Array2<gp_Vec> aResult(1, aNbU, 1, aNbV);

    gp_Vec aDerivative(0, 0, 0);

    if (theNU == 1 && theNV == 0)
    {

      const gp_Dir aXDir = myGeom->Pln().Position().XDirection();
      aDerivative        = gp_Vec(aXDir.X(), aXDir.Y(), aXDir.Z());
    }
    else if (theNU == 0 && theNV == 1)
    {

      const gp_Dir aYDir = myGeom->Pln().Position().YDirection();
      aDerivative        = gp_Vec(aYDir.X(), aYDir.Y(), aYDir.Z());
    }

    for (int iU = 1; iU <= aNbU; ++iU)
    {
      for (int iV = 1; iV <= aNbV; ++iV)
      {
        aResult.SetValue(iU, iV, aDerivative);
      }
    }
    return aResult;
  }

  NCollection_Array1<gp_Pnt> EvaluatePoints(const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
  {
    if (myGeom.IsNull() || theUVPairs.IsEmpty())
    {
      return NCollection_Array1<gp_Pnt>();
    }

    const int                  aNbPoints = theUVPairs.Size();
    NCollection_Array1<gp_Pnt> aResult(1, aNbPoints);

    const gp_Pln& aPln  = myGeom->Pln();
    const gp_Pnt& aLoc  = aPln.Location();
    const gp_Dir& aXDir = aPln.Position().XDirection();
    const gp_Dir& aYDir = aPln.Position().YDirection();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aXX   = aXDir.X();
    const double aXY   = aXDir.Y();
    const double aXZ   = aXDir.Z();
    const double aYX   = aYDir.X();
    const double aYY   = aYDir.Y();
    const double aYZ   = aYDir.Z();

    for (int i = 1; i <= aNbPoints; ++i)
    {
      const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i - 1);
      const double    u   = aUV.X();
      const double    v   = aUV.Y();
      aResult.SetValue(
        i,
        gp_Pnt(aLocX + u * aXX + v * aYX, aLocY + u * aXY + v * aYY, aLocZ + u * aXZ + v * aYZ));
    }
    return aResult;
  }

  NCollection_Array1<GeomGridEval::SurfD1> EvaluatePointsD1(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
  {
    if (myGeom.IsNull() || theUVPairs.IsEmpty())
    {
      return NCollection_Array1<GeomGridEval::SurfD1>();
    }

    const int                                aNbPoints = theUVPairs.Size();
    NCollection_Array1<GeomGridEval::SurfD1> aResult(1, aNbPoints);

    const gp_Pln& aPln  = myGeom->Pln();
    const gp_Pnt& aLoc  = aPln.Location();
    const gp_Dir& aXDir = aPln.Position().XDirection();
    const gp_Dir& aYDir = aPln.Position().YDirection();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aXX   = aXDir.X();
    const double aXY   = aXDir.Y();
    const double aXZ   = aXDir.Z();
    const double aYX   = aYDir.X();
    const double aYY   = aYDir.Y();
    const double aYZ   = aYDir.Z();

    const gp_Vec aD1U(aXX, aXY, aXZ);
    const gp_Vec aD1V(aYX, aYY, aYZ);

    for (int i = 1; i <= aNbPoints; ++i)
    {
      const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i - 1);
      const double    u   = aUV.X();
      const double    v   = aUV.Y();
      aResult.SetValue(
        i,
        {gp_Pnt(aLocX + u * aXX + v * aYX, aLocY + u * aXY + v * aYY, aLocZ + u * aXZ + v * aYZ),
         aD1U,
         aD1V});
    }
    return aResult;
  }

  NCollection_Array1<GeomGridEval::SurfD2> EvaluatePointsD2(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
  {
    if (myGeom.IsNull() || theUVPairs.IsEmpty())
    {
      return NCollection_Array1<GeomGridEval::SurfD2>();
    }

    const int                                aNbPoints = theUVPairs.Size();
    NCollection_Array1<GeomGridEval::SurfD2> aResult(1, aNbPoints);

    const gp_Pln& aPln  = myGeom->Pln();
    const gp_Pnt& aLoc  = aPln.Location();
    const gp_Dir& aXDir = aPln.Position().XDirection();
    const gp_Dir& aYDir = aPln.Position().YDirection();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aXX   = aXDir.X();
    const double aXY   = aXDir.Y();
    const double aXZ   = aXDir.Z();
    const double aYX   = aYDir.X();
    const double aYY   = aYDir.Y();
    const double aYZ   = aYDir.Z();

    const gp_Vec aD1U(aXX, aXY, aXZ);
    const gp_Vec aD1V(aYX, aYY, aYZ);
    const gp_Vec aZero(0, 0, 0);

    for (int i = 1; i <= aNbPoints; ++i)
    {
      const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i - 1);
      const double    u   = aUV.X();
      const double    v   = aUV.Y();
      aResult.SetValue(
        i,
        {gp_Pnt(aLocX + u * aXX + v * aYX, aLocY + u * aXY + v * aYY, aLocZ + u * aXZ + v * aYZ),
         aD1U,
         aD1V,
         aZero,
         aZero,
         aZero});
    }
    return aResult;
  }

  NCollection_Array1<GeomGridEval::SurfD3> EvaluatePointsD3(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const
  {
    if (myGeom.IsNull() || theUVPairs.IsEmpty())
    {
      return NCollection_Array1<GeomGridEval::SurfD3>();
    }

    const int                                aNbPoints = theUVPairs.Size();
    NCollection_Array1<GeomGridEval::SurfD3> aResult(1, aNbPoints);

    const gp_Pln& aPln  = myGeom->Pln();
    const gp_Pnt& aLoc  = aPln.Location();
    const gp_Dir& aXDir = aPln.Position().XDirection();
    const gp_Dir& aYDir = aPln.Position().YDirection();

    const double aLocX = aLoc.X();
    const double aLocY = aLoc.Y();
    const double aLocZ = aLoc.Z();
    const double aXX   = aXDir.X();
    const double aXY   = aXDir.Y();
    const double aXZ   = aXDir.Z();
    const double aYX   = aYDir.X();
    const double aYY   = aYDir.Y();
    const double aYZ   = aYDir.Z();

    const gp_Vec aD1U(aXX, aXY, aXZ);
    const gp_Vec aD1V(aYX, aYY, aYZ);
    const gp_Vec aZero(0, 0, 0);

    for (int i = 1; i <= aNbPoints; ++i)
    {
      const gp_Pnt2d& aUV = theUVPairs.Value(theUVPairs.Lower() + i - 1);
      const double    u   = aUV.X();
      const double    v   = aUV.Y();
      aResult.SetValue(
        i,
        {gp_Pnt(aLocX + u * aXX + v * aYX, aLocY + u * aXY + v * aYY, aLocZ + u * aXZ + v * aYZ),
         aD1U,
         aD1V,
         aZero,
         aZero,
         aZero,
         aZero,
         aZero,
         aZero,
         aZero});
    }
    return aResult;
  }

  NCollection_Array1<gp_Vec> EvaluatePointsDN(const NCollection_Array1<gp_Pnt2d>& theUVPairs,
                                              int                                 theNU,
                                              int                                 theNV) const
  {
    if (myGeom.IsNull() || theUVPairs.IsEmpty() || theNU < 0 || theNV < 0 || (theNU + theNV) < 1)
    {
      return NCollection_Array1<gp_Vec>();
    }

    const int                  aNbPoints = theUVPairs.Size();
    NCollection_Array1<gp_Vec> aResult(1, aNbPoints);

    gp_Vec aDerivative(0, 0, 0);

    if (theNU == 1 && theNV == 0)
    {
      const gp_Dir aXDir = myGeom->Pln().Position().XDirection();
      aDerivative        = gp_Vec(aXDir.X(), aXDir.Y(), aXDir.Z());
    }
    else if (theNU == 0 && theNV == 1)
    {
      const gp_Dir aYDir = myGeom->Pln().Position().YDirection();
      aDerivative        = gp_Vec(aYDir.X(), aYDir.Y(), aYDir.Z());
    }

    for (int i = 1; i <= aNbPoints; ++i)
    {
      aResult.SetValue(i, aDerivative);
    }
    return aResult;
  }

private:
  occ::handle<Geom_Plane> myGeom;
};
