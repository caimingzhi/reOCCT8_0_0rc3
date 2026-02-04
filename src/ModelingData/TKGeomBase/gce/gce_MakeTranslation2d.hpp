#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf2d.hpp>
class gp_Vec2d;
class gp_Pnt2d;

//! This class implements elementary construction algorithms for a
//! translation in 2D space. The result is a gp_Trsf2d transformation.
//! A MakeTranslation2d object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class gce_MakeTranslation2d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a translation along the vector Vect.
  Standard_EXPORT gce_MakeTranslation2d(const gp_Vec2d& Vect);

  //! Constructs a translation along the vector
  //! (Point1,Point2) defined from the point Point1 to the point Point2.
  Standard_EXPORT gce_MakeTranslation2d(const gp_Pnt2d& Point1, const gp_Pnt2d& Point2);

  //! Returns the constructed transformation.
  Standard_EXPORT const gp_Trsf2d& Value() const;

  Standard_EXPORT const gp_Trsf2d& Operator() const;
  Standard_EXPORT                  operator gp_Trsf2d() const;

private:
  gp_Trsf2d TheTranslation2d;
};

