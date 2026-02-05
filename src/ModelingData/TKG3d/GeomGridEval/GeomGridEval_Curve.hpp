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

//! @brief Unified grid evaluator for any 3D curve.
//!
//! Uses std::variant for compile-time type safety and zero heap allocation
//! for the evaluator itself. Automatically detects curve type from
//! Adaptor3d_Curve and dispatches to the appropriate specialized evaluator.
//!
//! Supported curve types with optimized evaluation:
//! - Line: Direct analytical formula
//! - Circle: Trigonometric formula
//! - Ellipse: Analytical formula
//! - Hyperbola: Analytical formula
//! - Parabola: Analytical formula
//! - BezierCurve: Optimized batch evaluation via BSplCLib
//! - BSplineCurve: Optimized batch evaluation via BSplCLib_GridEvaluator
//! - Other: Fallback using Adaptor3d_Curve::D0
//!
//! Usage:
//! @code
//!   GeomGridEval_Curve anEval;
//!   anEval.Initialize(myAdaptorCurve);
//!   // OR
//!   anEval.Initialize(myGeomCurve);
//!   NCollection_Array1<gp_Pnt> aGrid = anEval.EvaluateGrid(myParams);
//! @endcode
class GeomGridEval_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  //! Variant type holding all possible curve evaluators.
  using EvaluatorVariant = std::variant<std::monostate,            // Uninitialized state
                                        GeomGridEval_Line,         // Line curve
                                        GeomGridEval_Circle,       // Circle curve
                                        GeomGridEval_Ellipse,      // Ellipse curve
                                        GeomGridEval_Hyperbola,    // Hyperbola curve
                                        GeomGridEval_Parabola,     // Parabola curve
                                        GeomGridEval_BezierCurve,  // Bezier curve
                                        GeomGridEval_BSplineCurve, // B-spline curve
                                        GeomGridEval_OffsetCurve,  // Offset curve
                                        GeomGridEval_OtherCurve>;  // Fallback for other types

  //! Default constructor - uninitialized state.
  GeomGridEval_Curve()
      : myEvaluator(std::monostate{}),
        myCurveType(GeomAbs_OtherCurve)
  {
  }

  //! Non-copyable and non-movable.
  GeomGridEval_Curve(const GeomGridEval_Curve&)            = delete;
  GeomGridEval_Curve& operator=(const GeomGridEval_Curve&) = delete;
  GeomGridEval_Curve(GeomGridEval_Curve&&)                 = delete;
  GeomGridEval_Curve& operator=(GeomGridEval_Curve&&)      = delete;

  //! Initialize from adaptor reference (auto-detects curve type).
  //! For GeomAdaptor_Curve, extracts underlying Geom_Curve for optimized evaluation.
  //! For other adaptors, stores reference for fallback evaluation.
  //! @note The curve adaptor reference must remain valid during the lifetime
  //!       of this evaluator when using fallback evaluation.
  //! @param theCurve curve adaptor reference to evaluate
  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theCurve);

  //! Initialize from geometry handle (auto-detects curve type).
  //! @param theCurve geometry to evaluate
  Standard_EXPORT void Initialize(const occ::handle<Geom_Curve>& theCurve);

  //! Returns true if properly initialized.
  Standard_EXPORT bool IsInitialized() const;

  //! Evaluate grid points at all parameters.
  //! @param theParams array of parameter values
  //! @return array of 3D points (1-based indexing)
  Standard_EXPORT NCollection_Array1<gp_Pnt> EvaluateGrid(
    const NCollection_Array1<double>& theParams) const;

  //! Evaluate grid points with first derivative.
  //! @param theParams array of parameter values
  //! @return array of CurveD1 (1-based indexing)
  Standard_EXPORT NCollection_Array1<GeomGridEval::CurveD1> EvaluateGridD1(
    const NCollection_Array1<double>& theParams) const;

  //! Evaluate grid points with first and second derivatives.
  //! @param theParams array of parameter values
  //! @return array of CurveD2 (1-based indexing)
  Standard_EXPORT NCollection_Array1<GeomGridEval::CurveD2> EvaluateGridD2(
    const NCollection_Array1<double>& theParams) const;

  //! Evaluate grid points with first, second, and third derivatives.
  //! @param theParams array of parameter values
  //! @return array of CurveD3 (1-based indexing)
  Standard_EXPORT NCollection_Array1<GeomGridEval::CurveD3> EvaluateGridD3(
    const NCollection_Array1<double>& theParams) const;

  //! Evaluate Nth derivative at all grid points.
  //! @param theParams array of parameter values
  //! @param theN derivative order (N >= 1)
  //! @return array of derivative vectors (1-based indexing)
  Standard_EXPORT NCollection_Array1<gp_Vec> EvaluateGridDN(
    const NCollection_Array1<double>& theParams,
    int                               theN) const;

  //! Returns the detected curve type.
  GeomAbs_CurveType GetType() const { return myCurveType; }

private:
  EvaluatorVariant  myEvaluator;
  GeomAbs_CurveType myCurveType;
};
