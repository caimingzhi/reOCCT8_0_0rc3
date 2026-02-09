#pragma once

#include <BSplCLib_Cache.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomGridEval.hpp>
#include <NCollection_Array1.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_BSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_BSplineCurve(const occ::handle<Geom_BSplineCurve>& theCurve)
      : myGeom(theCurve)
  {
  }

  GeomGridEval_BSplineCurve(const GeomGridEval_BSplineCurve&)            = delete;
  GeomGridEval_BSplineCurve& operator=(const GeomGridEval_BSplineCurve&) = delete;
  GeomGridEval_BSplineCurve(GeomGridEval_BSplineCurve&&)                 = delete;
  GeomGridEval_BSplineCurve& operator=(GeomGridEval_BSplineCurve&&)      = delete;

  const occ::handle<Geom_BSplineCurve>& Geometry() const { return myGeom; }

  Standard_EXPORT NCollection_Array1<gp_Pnt> EvaluateGrid(
    const NCollection_Array1<double>& theParams) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::CurveD1> EvaluateGridD1(
    const NCollection_Array1<double>& theParams) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::CurveD2> EvaluateGridD2(
    const NCollection_Array1<double>& theParams) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::CurveD3> EvaluateGridD3(
    const NCollection_Array1<double>& theParams) const;

  Standard_EXPORT NCollection_Array1<gp_Vec> EvaluateGridDN(
    const NCollection_Array1<double>& theParams,
    int                               theN) const;

private:
  occ::handle<Geom_BSplineCurve> myGeom;
};
