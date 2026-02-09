#pragma once

#include <BSplCLib_Cache.hpp>
#include <Geom_BezierCurve.hpp>
#include <GeomGridEval.hpp>
#include <NCollection_Array1.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_BezierCurve
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_BezierCurve(const occ::handle<Geom_BezierCurve>& theBezier)
      : myGeom(theBezier)
  {
  }

  GeomGridEval_BezierCurve(const GeomGridEval_BezierCurve&)            = delete;
  GeomGridEval_BezierCurve& operator=(const GeomGridEval_BezierCurve&) = delete;
  GeomGridEval_BezierCurve(GeomGridEval_BezierCurve&&)                 = delete;
  GeomGridEval_BezierCurve& operator=(GeomGridEval_BezierCurve&&)      = delete;

  const occ::handle<Geom_BezierCurve>& Geometry() const { return myGeom; }

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
  occ::handle<Geom_BezierCurve> myGeom;
};
