#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Law_BSpline;

//! For a B-spline curve the discontinuities are localised at the
//! knot values and between two knots values the B-spline is
//! infinitely continuously differentiable.
//! At a knot of range index the continuity is equal to:
//! Degree - Mult (Index) where Degree is the degree of the
//! basis B-spline functions and Mult the multiplicity of the knot
//! of range Index.
//! If for your computation you need to have B-spline curves with a
//! minima of continuity it can be interesting to know between which
//! knot values, a B-spline curve arc, has a continuity of given order.
//! This algorithm computes the indexes of the knots where you should
//! split the curve, to obtain arcs with a constant continuity given
//! at the construction time. The splitting values are in the range
//! [FirstUKnotValue, LastUKnotValue] (See class B-spline curve from
//! package Geom).
//! If you just want to compute the local derivatives on the curve you
//! don't need to create the B-spline curve arcs, you can use the
//! functions LocalD1, LocalD2, LocalD3, LocalDN of the class
//! BSplineCurve.
class Law_BSplineKnotSplitting
{
public:
  DEFINE_STANDARD_ALLOC

  //! Locates the knot values which correspond to the segmentation of
  //! the curve into arcs with a continuity equal to ContinuityRange.
  //!
  //! Raised if ContinuityRange is not greater or equal zero.
  Standard_EXPORT Law_BSplineKnotSplitting(const occ::handle<Law_BSpline>& BasisLaw,
                                           const int                       ContinuityRange);

  //! Returns the number of knots corresponding to the splitting.
  Standard_EXPORT int NbSplits() const;

  //! Returns the indexes of the BSpline curve knots corresponding to
  //! the splitting.
  //!
  //! Raised if the length of SplitValues is not equal to NbSPlit.
  Standard_EXPORT void Splitting(NCollection_Array1<int>& SplitValues) const;

  //! Returns the index of the knot corresponding to the splitting
  //! of range Index.
  //!
  //! Raised if Index < 1 or Index > NbSplits
  Standard_EXPORT int SplitValue(const int Index) const;

private:
  occ::handle<NCollection_HArray1<int>> splitIndexes;
};

