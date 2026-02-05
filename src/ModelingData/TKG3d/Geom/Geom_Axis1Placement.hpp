#pragma once

#include <Standard.hpp>

#include <Geom_AxisPlacement.hpp>
class gp_Ax1;
class gp_Pnt;
class gp_Dir;
class gp_Trsf;
class Geom_Geometry;

//! Describes an axis in 3D space.
//! An axis is defined by:
//! - its origin, also termed the "Location point" of the axis,
//! - its unit vector, termed the "Direction" of the axis.
//! Note: Geom_Axis1Placement axes provide the
//! same kind of "geometric" services as gp_Ax1 axes
//! but have more complex data structures. The
//! geometric objects provided by the Geom package
//! use gp_Ax1 objects to include axes in their data
//! structures, or to define an axis of symmetry or axis of rotation.
//! Geom_Axis1Placement axes are used in a context
//! where they can be shared by several objects
//! contained inside a common data structure.
class Geom_Axis1Placement : public Geom_AxisPlacement
{

public:
  //! Returns a transient copy of A1.
  Standard_EXPORT Geom_Axis1Placement(const gp_Ax1& A1);

  //! P is the origin of the axis placement and V is the direction
  //! of the axis placement.
  Standard_EXPORT Geom_Axis1Placement(const gp_Pnt& P, const gp_Dir& V);

  //! Returns a non transient copy of <me>.
  Standard_EXPORT const gp_Ax1& Ax1() const;

  //! Reverses the direction of the axis placement.
  Standard_EXPORT void Reverse();

  //! Returns a copy of <me> reversed.
  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Axis1Placement> Reversed() const;

  //! Assigns V to the unit vector of this axis.
  Standard_EXPORT void SetDirection(const gp_Dir& V) override;

  //! Applies the transformation T to this axis.
  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  //! Creates a new object, which is a copy of this axis.
  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom_Axis1Placement, Geom_AxisPlacement)
};
