#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
class Geom_Curve;

//! These global functions compute the degree of
//! continuity of a 3D curve built by concatenation of two
//! other curves (or portions of curves) at their junction point.
class GeomLProp
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the regularity at the junction between C1 and
  //! C2. The booleans r1 and r2 are true if the curves must
  //! be taken reversed. The point u1 on C1 and the point
  //! u2 on C2 must be confused.
  //! tl and ta are the linear and angular tolerance used two
  //! compare the derivative.
  Standard_EXPORT static GeomAbs_Shape Continuity(const occ::handle<Geom_Curve>& C1,
                                                  const occ::handle<Geom_Curve>& C2,
                                                  const double                   u1,
                                                  const double                   u2,
                                                  const bool                     r1,
                                                  const bool                     r2,
                                                  const double                   tl,
                                                  const double                   ta);

  //! The same as preceding but using the standard
  //! tolerances from package Precision.
  Standard_EXPORT static GeomAbs_Shape Continuity(const occ::handle<Geom_Curve>& C1,
                                                  const occ::handle<Geom_Curve>& C2,
                                                  const double                   u1,
                                                  const double                   u2,
                                                  const bool                     r1,
                                                  const bool                     r2);
};
