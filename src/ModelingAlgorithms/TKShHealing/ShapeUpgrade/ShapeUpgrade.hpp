#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Geom_BoundedCurve.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Geom2d_BoundedCurve.hpp>
class Geom_BSplineCurve;
class Geom2d_BSplineCurve;

//! This package provides tools for splitting and converting shapes by some criteria.
//! It provides modifications of the kind when one topological
//! object can be converted or split in to several ones.
//! In particular this package contains high level API classes which perform:
//! converting geometry of shapes up to given continuity,
//! splitting revolutions by U to segments less than given value,
//! converting to beziers, splitting closed faces.
class ShapeUpgrade
{
public:
  DEFINE_STANDARD_ALLOC

  //! Unifies same domain faces and edges of specified shape
  Standard_EXPORT static bool C0BSplineToSequenceOfC1BSplineCurve(
    const occ::handle<Geom_BSplineCurve>&                               BS,
    occ::handle<NCollection_HSequence<occ::handle<Geom_BoundedCurve>>>& seqBS);

  //! Converts C0 B-Spline curve into sequence of C1 B-Spline curves.
  //! This method splits B-Spline at the knots with multiplicities equal to degree,
  //! i.e. unlike method GeomConvert::C0BSplineToArrayOfC1BSplineCurve
  //! this one does not use any tolerance and therefore does not change the geometry of B-Spline.
  //! Returns True if C0 B-Spline was successfully split,
  //! else returns False (if BS is C1 B-Spline).
  Standard_EXPORT static bool C0BSplineToSequenceOfC1BSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>&                               BS,
    occ::handle<NCollection_HSequence<occ::handle<Geom2d_BoundedCurve>>>& seqBS);
};
