#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Real.hpp>
class BRepAdaptor_Curve;

//! These global functions compute the degree of
//! continuity of a curve built by concatenation of two
//! edges at their junction point.
class BRepLProp
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the regularity at the junction between C1 and
  //! C2. The point u1 on C1 and the point u2 on C2 must be
  //! confused. tl and ta are the linear and angular
  //! tolerance used two compare the derivative.
  Standard_EXPORT static GeomAbs_Shape Continuity(const BRepAdaptor_Curve& C1,
                                                  const BRepAdaptor_Curve& C2,
                                                  const double             u1,
                                                  const double             u2,
                                                  const double             tl,
                                                  const double             ta);

  //! The same as preceding but using the standard tolerances from package Precision.
  Standard_EXPORT static GeomAbs_Shape Continuity(const BRepAdaptor_Curve& C1,
                                                  const BRepAdaptor_Curve& C2,
                                                  const double             u1,
                                                  const double             u2);
};
