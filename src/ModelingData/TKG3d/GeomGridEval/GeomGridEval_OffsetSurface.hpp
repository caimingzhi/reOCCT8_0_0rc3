#pragma once

#include <Geom_OffsetSurface.hpp>
#include <Geom_Surface.hpp>
#include <GeomGridEval.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_OffsetSurface
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_OffsetSurface(const occ::handle<Geom_OffsetSurface>& theOffset)
      : myGeom(theOffset),
        myOffset(0.0)
  {
    if (!myGeom.IsNull())
    {
      myOffset = myGeom->Offset();
      myBasis  = myGeom->BasisSurface();
    }
  }

  GeomGridEval_OffsetSurface(const GeomGridEval_OffsetSurface&)            = delete;
  GeomGridEval_OffsetSurface& operator=(const GeomGridEval_OffsetSurface&) = delete;
  GeomGridEval_OffsetSurface(GeomGridEval_OffsetSurface&&)                 = delete;
  GeomGridEval_OffsetSurface& operator=(GeomGridEval_OffsetSurface&&)      = delete;

  const occ::handle<Geom_OffsetSurface>& Geometry() const { return myGeom; }

  Standard_EXPORT NCollection_Array2<gp_Pnt> EvaluateGrid(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD1> EvaluateGridD1(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD2> EvaluateGridD2(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD3> EvaluateGridD3(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<gp_Vec> EvaluateGridDN(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams,
    int                               theNU,
    int                               theNV) const;

  Standard_EXPORT NCollection_Array1<gp_Pnt> EvaluatePoints(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD1> EvaluatePointsD1(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD2> EvaluatePointsD2(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD3> EvaluatePointsD3(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<gp_Vec> EvaluatePointsDN(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs,
    int                                 theNU,
    int                                 theNV) const;

private:
  occ::handle<Geom_OffsetSurface> myGeom;
  occ::handle<Geom_Surface>       myBasis;
  double                          myOffset;
};
