#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomGridEval.hpp>
#include <NCollection_Array1.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <functional>

class GeomGridEval_OtherCurve
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_OtherCurve(const Adaptor3d_Curve& theCurve)
      : myCurve(theCurve)
  {
  }

  GeomGridEval_OtherCurve(const GeomGridEval_OtherCurve&)            = delete;
  GeomGridEval_OtherCurve& operator=(const GeomGridEval_OtherCurve&) = delete;
  GeomGridEval_OtherCurve(GeomGridEval_OtherCurve&&)                 = delete;
  GeomGridEval_OtherCurve& operator=(GeomGridEval_OtherCurve&&)      = delete;

  const Adaptor3d_Curve& Curve() const { return myCurve.get(); }

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
  std::reference_wrapper<const Adaptor3d_Curve> myCurve;
};
