#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class Geom_Transformation;
class gp_Lin;
class gp_Ax1;
class gp_Pnt;
class gp_Dir;

//! This class implements elementary construction algorithms for a
//! rotation in 3D space. The result is a
//! Geom_Transformation transformation.
//! A MakeRotation object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GC_MakeRotation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a rotation through angle Angle about the axis defined by the line Line.
  Standard_EXPORT GC_MakeRotation(const gp_Lin& Line, const double Angle);

  //! Constructs a rotation through angle Angle about the axis defined by the axis Axis.
  Standard_EXPORT GC_MakeRotation(const gp_Ax1& Axis, const double Angle);

  //! Constructs a rotation through angle Angle about the axis
  //! defined by the point Point and the unit vector Direc.
  Standard_EXPORT GC_MakeRotation(const gp_Pnt& Point, const gp_Dir& Direc, const double Angle);

  //! Returns the constructed transformation.
  Standard_EXPORT const occ::handle<Geom_Transformation>& Value() const;

  operator const occ::handle<Geom_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom_Transformation> TheRotation;
};

