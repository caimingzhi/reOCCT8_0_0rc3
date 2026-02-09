#pragma once

#include <Geom_Hyperbola.hpp>
#include <GeomGridEval.hpp>
#include <NCollection_Array1.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_Hyperbola
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_Hyperbola(const occ::handle<Geom_Hyperbola>& theHyperbola)
      : myGeom(theHyperbola)
  {
  }

  GeomGridEval_Hyperbola(const GeomGridEval_Hyperbola&)            = delete;
  GeomGridEval_Hyperbola& operator=(const GeomGridEval_Hyperbola&) = delete;
  GeomGridEval_Hyperbola(GeomGridEval_Hyperbola&&)                 = delete;
  GeomGridEval_Hyperbola& operator=(GeomGridEval_Hyperbola&&)      = delete;

  const occ::handle<Geom_Hyperbola>& Geometry() const { return myGeom; }

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
  occ::handle<Geom_Hyperbola> myGeom;
};
