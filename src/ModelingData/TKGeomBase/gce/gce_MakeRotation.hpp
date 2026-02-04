#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf.hpp>
class gp_Lin;
class gp_Ax1;
class gp_Pnt;
class gp_Dir;

//! This class implements elementary construction algorithms for a
//! rotation in 3D space. The result is a gp_Trsf transformation.
//! A MakeRotation object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class gce_MakeRotation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a rotation through angle Angle about the axis defined by the line Line.
  Standard_EXPORT gce_MakeRotation(const gp_Lin& Line, const double Angle);

  //! Constructs a rotation through angle Angle about the axis defined by the axis Axis.
  Standard_EXPORT gce_MakeRotation(const gp_Ax1& Axis, const double Angle);

  //! Constructs a rotation through angle Angle about the axis defined by:
  //! the point Point and the unit vector Direc.
  Standard_EXPORT gce_MakeRotation(const gp_Pnt& Point, const gp_Dir& Direc, const double Angle);

  //! Returns the constructed transformation.
  Standard_EXPORT const gp_Trsf& Value() const;

  Standard_EXPORT const gp_Trsf& Operator() const;
  Standard_EXPORT                operator gp_Trsf() const;

private:
  gp_Trsf TheRotation;
};

