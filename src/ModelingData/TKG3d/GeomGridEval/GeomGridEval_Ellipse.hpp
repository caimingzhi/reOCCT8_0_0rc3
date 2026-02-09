#pragma once

#include <Geom_Ellipse.hpp>
#include <GeomGridEval.hpp>
#include <NCollection_Array1.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_Ellipse
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_Ellipse(const occ::handle<Geom_Ellipse>& theEllipse)
      : myGeom(theEllipse)
  {
  }

  GeomGridEval_Ellipse(const GeomGridEval_Ellipse&)            = delete;
  GeomGridEval_Ellipse& operator=(const GeomGridEval_Ellipse&) = delete;
  GeomGridEval_Ellipse(GeomGridEval_Ellipse&&)                 = delete;
  GeomGridEval_Ellipse& operator=(GeomGridEval_Ellipse&&)      = delete;

  const occ::handle<Geom_Ellipse>& Geometry() const { return myGeom; }

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
  occ::handle<Geom_Ellipse> myGeom;
};
