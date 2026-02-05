#pragma once

#include <Geom_OffsetSurface.hpp>
#include <Geom_Surface.hpp>
#include <GeomGridEval.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

//! @brief Batch evaluator for offset surface grid points.
//!
//! Evaluates the offset surface formula:
//! P(u,v) = S(u,v) + Offset * Normal(u,v)
//!
//! Uses GeomGridEval_Surface for batch evaluation of the basis surface,
//! then applies offset transformation.
//!
//! Usage:
//! @code
//!   GeomGridEval_OffsetSurface anEvaluator(myGeomOffset);
//!   NCollection_Array2<gp_Pnt> aGrid = anEvaluator.EvaluateGrid(myUParams, myVParams);
//! @endcode
class GeomGridEval_OffsetSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor with geometry.
  //! @param theOffset the offset surface geometry to evaluate
  GeomGridEval_OffsetSurface(const occ::handle<Geom_OffsetSurface>& theOffset)
      : myGeom(theOffset),
        myOffset(0.0)
  {
    if (!myGeom.IsNull())
    {
      myOffset = myGeom->Offset();
      myBasis  = myGeom->BasisSurface();
    }
  }

  //! Non-copyable and non-movable.
  GeomGridEval_OffsetSurface(const GeomGridEval_OffsetSurface&)            = delete;
  GeomGridEval_OffsetSurface& operator=(const GeomGridEval_OffsetSurface&) = delete;
  GeomGridEval_OffsetSurface(GeomGridEval_OffsetSurface&&)                 = delete;
  GeomGridEval_OffsetSurface& operator=(GeomGridEval_OffsetSurface&&)      = delete;

  //! Returns the geometry handle.
  const occ::handle<Geom_OffsetSurface>& Geometry() const { return myGeom; }

  //! Evaluate all grid points.
  //! @param[in] theUParams array of U parameter values
  //! @param[in] theVParams array of V parameter values
  //! @return 2D array of evaluated points (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array2<gp_Pnt> EvaluateGrid(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  //! Evaluate all grid points with first partial derivatives.
  //! @param[in] theUParams array of U parameter values
  //! @param[in] theVParams array of V parameter values
  //! @return 2D array of SurfD1 (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD1> EvaluateGridD1(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  //! Evaluate all grid points with first and second partial derivatives.
  //! @param[in] theUParams array of U parameter values
  //! @param[in] theVParams array of V parameter values
  //! @return 2D array of SurfD2 (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD2> EvaluateGridD2(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  //! Evaluate all grid points with derivatives up to third order.
  //! Uses GeomAdaptor_Surface::D3 for evaluation.
  //! @param[in] theUParams array of U parameter values
  //! @param[in] theVParams array of V parameter values
  //! @return 2D array of SurfD3 (1-based indexing),
  //!         or empty array if geometry is null or no parameters set
  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD3> EvaluateGridD3(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  //! Evaluate partial derivative d^(NU+NV)S/(dU^NU dV^NV) at all grid points.
  //! Uses geometry DN method.
  //! @param[in] theUParams array of U parameter values
  //! @param[in] theVParams array of V parameter values
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
  occ::handle<Geom_OffsetSurface> myGeom;
  occ::handle<Geom_Surface>       myBasis;
  double                          myOffset;
};
