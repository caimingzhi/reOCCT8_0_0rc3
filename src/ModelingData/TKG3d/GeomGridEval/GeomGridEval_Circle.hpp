#pragma once

#include <Geom_Circle.hpp>
#include <GeomGridEval.hpp>
#include <NCollection_Array1.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_Circle
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_Circle(const occ::handle<Geom_Circle>& theCircle)
      : myGeom(theCircle)
  {
  }

  GeomGridEval_Circle(const GeomGridEval_Circle&)            = delete;
  GeomGridEval_Circle& operator=(const GeomGridEval_Circle&) = delete;
  GeomGridEval_Circle(GeomGridEval_Circle&&)                 = delete;
  GeomGridEval_Circle& operator=(GeomGridEval_Circle&&)      = delete;

  const occ::handle<Geom_Circle>& Geometry() const { return myGeom; }

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
  occ::handle<Geom_Circle> myGeom;
};
