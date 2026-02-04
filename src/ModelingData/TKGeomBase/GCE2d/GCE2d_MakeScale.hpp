#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class Geom2d_Transformation;
class gp_Pnt2d;

//! This class implements an elementary construction algorithm for
//! a scaling transformation in 2D space. The result is a
//! Geom2d_Transformation transformation.
//! A MakeScale object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GCE2d_MakeScale
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a scaling transformation with
  //! -   Point as the center of the transformation, and
  //! -   Scale as the scale factor.
  Standard_EXPORT GCE2d_MakeScale(const gp_Pnt2d& Point, const double Scale);

  //! Returns the constructed transformation.
  Standard_EXPORT const occ::handle<Geom2d_Transformation>& Value() const;

  operator const occ::handle<Geom2d_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom2d_Transformation> TheScale;
};

