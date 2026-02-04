#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_Transformation;
class gp_Vec2d;
class gp_Pnt2d;

//! This class implements elementary construction algorithms for a
//! translation in 2D space. The result is a
//! Geom2d_Transformation transformation.
//! A MakeTranslation object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GCE2d_MakeTranslation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a translation along the vector Vect.
  Standard_EXPORT GCE2d_MakeTranslation(const gp_Vec2d& Vect);

  //! Constructs a translation along the vector
  //! (Point1,Point2) defined from the point Point1 to the point Point2.
  Standard_EXPORT GCE2d_MakeTranslation(const gp_Pnt2d& Point1, const gp_Pnt2d& Point2);

  //! Returns the constructed transformation.
  Standard_EXPORT const occ::handle<Geom2d_Transformation>& Value() const;

  operator const occ::handle<Geom2d_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom2d_Transformation> TheTranslation;
};

