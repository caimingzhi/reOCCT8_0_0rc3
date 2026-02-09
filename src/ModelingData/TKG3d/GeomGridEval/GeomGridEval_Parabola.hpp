#pragma once

#include <Geom_Parabola.hpp>
#include <GeomGridEval.hpp>
#include <NCollection_Array1.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_Parabola
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_Parabola(const occ::handle<Geom_Parabola>& theParabola)
      : myGeom(theParabola)
  {
  }

  GeomGridEval_Parabola(const GeomGridEval_Parabola&)            = delete;
  GeomGridEval_Parabola& operator=(const GeomGridEval_Parabola&) = delete;
  GeomGridEval_Parabola(GeomGridEval_Parabola&&)                 = delete;
  GeomGridEval_Parabola& operator=(GeomGridEval_Parabola&&)      = delete;

  const occ::handle<Geom_Parabola>& Geometry() const { return myGeom; }

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
  occ::handle<Geom_Parabola> myGeom;
};
