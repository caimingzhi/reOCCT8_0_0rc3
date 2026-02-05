#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <LProp_CurAndInf.hpp>
class Geom2d_Curve;

//! An algorithm for computing local properties of a curve.
//! These properties include:
//! - the maximum and minimum curvatures
//! - the inflection points.
//! A CurAndInf2d object provides the framework for:
//! - defining the curve to be analyzed
//! - implementing the computation algorithms
//! - consulting the results.
class Geom2dLProp_CurAndInf2d : public LProp_CurAndInf
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initializes the framework.
  //! Note: The curve on which the local properties are
  //! computed is defined using one of the following
  //! functions: Perform, PerformCurExt or PerformInf.
  Standard_EXPORT Geom2dLProp_CurAndInf2d();

  //! For the curve C, Computes both the
  //! inflection points and the maximum and minimum curvatures.
  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& C);

  //! For the curve C, Computes the locals extremas of curvature.
  Standard_EXPORT void PerformCurExt(const occ::handle<Geom2d_Curve>& C);

  //! For the curve C, Computes the inflections.
  //! After computation, the following functions can be used:
  //! - IsDone to check if the computation was successful
  //! - NbPoints to obtain the number of computed particular points
  //! - Parameter to obtain the parameter on the curve for
  //! each particular point
  //! - Type to check if the point is an inflection point or an
  //! extremum of curvature of the curve C.
  //! Warning
  //! These functions can be used to analyze a series of
  //! curves, however it is necessary to clear the table of
  //! results between each computation.
  Standard_EXPORT void PerformInf(const occ::handle<Geom2d_Curve>& C);

  //! True if the solutions are found.
  Standard_EXPORT bool IsDone() const;

private:
  bool isDone;
};
