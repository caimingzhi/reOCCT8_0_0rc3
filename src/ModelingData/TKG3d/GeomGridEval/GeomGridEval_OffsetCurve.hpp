#pragma once

#include <Geom_Curve.hpp>
#include <Geom_OffsetCurve.hpp>
#include <GeomGridEval.hpp>
#include <NCollection_Array1.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_OffsetCurve
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_OffsetCurve(const occ::handle<Geom_OffsetCurve>& theOffset)
      : myGeom(theOffset),
        myOffset(0.0)
  {
    if (!myGeom.IsNull())
    {
      myOffset    = myGeom->Offset();
      myBasis     = myGeom->BasisCurve();
      myDirection = myGeom->Direction();
    }
  }

  GeomGridEval_OffsetCurve(const GeomGridEval_OffsetCurve&)            = delete;
  GeomGridEval_OffsetCurve& operator=(const GeomGridEval_OffsetCurve&) = delete;
  GeomGridEval_OffsetCurve(GeomGridEval_OffsetCurve&&)                 = delete;
  GeomGridEval_OffsetCurve& operator=(GeomGridEval_OffsetCurve&&)      = delete;

  const occ::handle<Geom_OffsetCurve>& Geometry() const { return myGeom; }

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
  occ::handle<Geom_OffsetCurve> myGeom;
  occ::handle<Geom_Curve>       myBasis;
  double                        myOffset;
  gp_Dir                        myDirection;
};
