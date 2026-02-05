#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class Geom_Transformation;
class gp_Pnt;

//! This class implements an elementary construction algorithm for
//! a scaling transformation in 3D space. The result is a
//! Geom_Transformation transformation (a scaling transformation with
//! the center point <Point> and the scaling value <Scale>).
//! A MakeScale object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GC_MakeScale
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a scaling transformation with
  //! -   Point as the center of the transformation, and
  //! -   Scale as the scale factor.
  Standard_EXPORT GC_MakeScale(const gp_Pnt& Point, const double Scale);

  //! Returns the constructed transformation.
  Standard_EXPORT const occ::handle<Geom_Transformation>& Value() const;

  operator const occ::handle<Geom_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom_Transformation> TheScale;
};
