#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_CurveType.hpp>
#include <Geom_Curve.hpp>
#include <GeomGridEval_BSplineCurve.hpp>
#include <GeomGridEval_BezierCurve.hpp>
#include <GeomGridEval_Circle.hpp>
#include <GeomGridEval_Ellipse.hpp>
#include <GeomGridEval_Hyperbola.hpp>
#include <GeomGridEval_Line.hpp>
#include <GeomGridEval_OffsetCurve.hpp>
#include <GeomGridEval_OtherCurve.hpp>
#include <GeomGridEval_Parabola.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <variant>

class GeomGridEval_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  using EvaluatorVariant = std::variant<std::monostate,
                                        GeomGridEval_Line,
                                        GeomGridEval_Circle,
                                        GeomGridEval_Ellipse,
                                        GeomGridEval_Hyperbola,
                                        GeomGridEval_Parabola,
                                        GeomGridEval_BezierCurve,
                                        GeomGridEval_BSplineCurve,
                                        GeomGridEval_OffsetCurve,
                                        GeomGridEval_OtherCurve>;

  GeomGridEval_Curve()
      : myEvaluator(std::monostate{}),
        myCurveType(GeomAbs_OtherCurve)
  {
  }

  GeomGridEval_Curve(const GeomGridEval_Curve&)            = delete;
  GeomGridEval_Curve& operator=(const GeomGridEval_Curve&) = delete;
  GeomGridEval_Curve(GeomGridEval_Curve&&)                 = delete;
  GeomGridEval_Curve& operator=(GeomGridEval_Curve&&)      = delete;

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theCurve);

  Standard_EXPORT void Initialize(const occ::handle<Geom_Curve>& theCurve);

  Standard_EXPORT bool IsInitialized() const;

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

  GeomAbs_CurveType GetType() const { return myCurveType; }

private:
  EvaluatorVariant  myEvaluator;
  GeomAbs_CurveType myCurveType;
};
