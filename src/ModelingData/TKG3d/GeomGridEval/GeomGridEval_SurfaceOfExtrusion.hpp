#pragma once

#include <GeomGridEval.hpp>
#include <GeomGridEval_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

//! @brief Optimized batch evaluator for linear extrusion surface grid points.
//!
//! Evaluates the extrusion surface formula:
//! S(u, v) = C(u) + v * Direction
//!
//! Where:
//! - C(u) is the basis curve
//! - v is the extrusion parameter
//! - Direction is the extrusion direction (unit vector)
//!
//! Optimization: Uses GeomGridEval_Curve for batch evaluation of the basis curve,
//! then applies the linear shift v*Direction for each grid point.
//! This is more efficient than point-by-point evaluation.
//!
//! Usage:
//! @code
//!   GeomGridEval_SurfaceOfExtrusion anEvaluator(myExtrusionSurface);
//!   NCollection_Array2<gp_Pnt> aGrid = anEvaluator.EvaluateGrid(myUParams, myVParams);
//! @endcode
class GeomGridEval_SurfaceOfExtrusion
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor with geometry.
  //! @param theExtrusion the extrusion surface geometry to evaluate
  Standard_EXPORT GeomGridEval_SurfaceOfExtrusion(
    const occ::handle<Geom_SurfaceOfLinearExtrusion>& theExtrusion);

  //! Non-copyable and non-movable.
  GeomGridEval_SurfaceOfExtrusion(const GeomGridEval_SurfaceOfExtrusion&)            = delete;
  GeomGridEval_SurfaceOfExtrusion& operator=(const GeomGridEval_SurfaceOfExtrusion&) = delete;
  GeomGridEval_SurfaceOfExtrusion(GeomGridEval_SurfaceOfExtrusion&&)                 = delete;
  GeomGridEval_SurfaceOfExtrusion& operator=(GeomGridEval_SurfaceOfExtrusion&&)      = delete;

  //! Returns the geometry handle.
  const occ::handle<Geom_SurfaceOfLinearExtrusion>& Geometry() const { return myGeom; }

  //! Evaluate all grid points.
  //! @param[in] theUParams array of U parameter values (curve parameter)
  //! @param[in] theVParams array of V parameter values (extrusion distance)
  //! @return 2D array of evaluated points (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array2<gp_Pnt> EvaluateGrid(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  //! Evaluate all grid points with first partial derivatives.
  //! @param[in] theUParams array of U parameter values (curve parameter)
  //! @param[in] theVParams array of V parameter values (extrusion distance)
  //! @return 2D array of SurfD1 (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD1> EvaluateGridD1(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  //! Evaluate all grid points with first and second partial derivatives.
  //! @param[in] theUParams array of U parameter values (curve parameter)
  //! @param[in] theVParams array of V parameter values (extrusion distance)
  //! @return 2D array of SurfD2 (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD2> EvaluateGridD2(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  //! Evaluate all grid points with derivatives up to third order.
  //! @param[in] theUParams array of U parameter values (curve parameter)
  //! @param[in] theVParams array of V parameter values (extrusion distance)
  //! @return 2D array of SurfD3 (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD3> EvaluateGridD3(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  //! Evaluate partial derivative d^(NU+NV)S/(dU^NU dV^NV) at all grid points.
  //! @param[in] theUParams array of U parameter values (curve parameter)
  //! @param[in] theVParams array of V parameter values (extrusion distance)
  //! @param[in] theNU derivative order in U direction
  //! @param[in] theNV derivative order in V direction
  //! @return 2D array of derivative vectors (1-based indexing)
  Standard_EXPORT NCollection_Array2<gp_Vec> EvaluateGridDN(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams,
    int                               theNU,
    int                               theNV) const;

  //! Evaluate points at arbitrary UV pairs.
  //! @param[in] theUVPairs array of UV coordinate pairs (U=X(), V=Y())
  //! @return array of evaluated points (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array1<gp_Pnt> EvaluatePoints(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  //! Evaluate points with first partial derivatives at arbitrary UV pairs.
  //! @param[in] theUVPairs array of UV coordinate pairs (U=X(), V=Y())
  //! @return array of SurfD1 (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD1> EvaluatePointsD1(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  //! Evaluate points with first and second partial derivatives at arbitrary UV pairs.
  //! @param[in] theUVPairs array of UV coordinate pairs (U=X(), V=Y())
  //! @return array of SurfD2 (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD2> EvaluatePointsD2(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  //! Evaluate points with derivatives up to third order at arbitrary UV pairs.
  //! @param[in] theUVPairs array of UV coordinate pairs (U=X(), V=Y())
  //! @return array of SurfD3 (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD3> EvaluatePointsD3(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  //! Evaluate partial derivative at arbitrary UV pairs.
  //! @param[in] theUVPairs array of UV coordinate pairs (U=X(), V=Y())
  //! @param[in] theNU derivative order in U direction
  //! @param[in] theNV derivative order in V direction
  //! @return array of derivative vectors (1-based indexing)
  Standard_EXPORT NCollection_Array1<gp_Vec> EvaluatePointsDN(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs,
    int                                 theNU,
    int                                 theNV) const;

private:
  occ::handle<Geom_SurfaceOfLinearExtrusion> myGeom;
  occ::handle<Geom_Curve>                    myBasisCurve;
  gp_Dir                                     myDirection;
};
