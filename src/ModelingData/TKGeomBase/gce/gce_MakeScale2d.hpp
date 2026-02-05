#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf2d.hpp>
class gp_Pnt2d;

//! This class implements an elementary construction algorithm for
//! a scaling transformation in 2D space. The result is a gp_Trsf2d transformation.
//! A MakeScale2d object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class gce_MakeScale2d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a scaling transformation with:
  //! -   Point as the center of the transformation, and
  //! -   Scale as the scale factor.
  Standard_EXPORT gce_MakeScale2d(const gp_Pnt2d& Point, const double Scale);

  //! Returns the constructed transformation.
  Standard_EXPORT const gp_Trsf2d& Value() const;

  Standard_EXPORT const gp_Trsf2d& Operator() const;
  Standard_EXPORT                  operator gp_Trsf2d() const;

private:
  gp_Trsf2d TheScale2d;
};
