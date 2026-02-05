#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class Geom2d_Transformation;
class gp_Pnt2d;

//! This class implements an elementary construction algorithm for
//! a rotation in 2D space. The result is a Geom2d_Transformation transformation.
//! A MakeRotation object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GCE2d_MakeRotation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a rotation through angle Angle about the center Point.
  Standard_EXPORT GCE2d_MakeRotation(const gp_Pnt2d& Point, const double Angle);

  //! Returns the constructed transformation.
  Standard_EXPORT const occ::handle<Geom2d_Transformation>& Value() const;

  operator const occ::handle<Geom2d_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom2d_Transformation> TheRotation;
};
