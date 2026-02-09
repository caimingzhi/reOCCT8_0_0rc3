#pragma once

#include <BSplSLib_Cache.hpp>
#include <Geom_BSplineSurface.hpp>
#include <GeomGridEval.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_BSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_BSplineSurface(const occ::handle<Geom_BSplineSurface>& theSurface)
      : myGeom(theSurface)
  {
  }

  GeomGridEval_BSplineSurface(const GeomGridEval_BSplineSurface&)            = delete;
  GeomGridEval_BSplineSurface& operator=(const GeomGridEval_BSplineSurface&) = delete;
  GeomGridEval_BSplineSurface(GeomGridEval_BSplineSurface&&)                 = delete;
  GeomGridEval_BSplineSurface& operator=(GeomGridEval_BSplineSurface&&)      = delete;

  const occ::handle<Geom_BSplineSurface>& Geometry() const { return myGeom; }

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
  NCollection_Array1<GeomGridEval::SurfD1> EvaluatePointsD1(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;
  NCollection_Array1<GeomGridEval::SurfD2> EvaluatePointsD2(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;
  NCollection_Array1<GeomGridEval::SurfD3> EvaluatePointsD3(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;
  NCollection_Array1<gp_Vec> EvaluatePointsDN(const NCollection_Array1<double>& theUParams,
                                              const NCollection_Array1<double>& theVParams,
                                              int                               theNU,
                                              int                               theNV) const;

private:
  occ::handle<Geom_BSplineSurface> myGeom;
};
