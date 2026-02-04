#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Cylinder.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
class gp_Ax2;

//! Describes functions to build cylinders or portions of cylinders.
//! A MakeCylinder object provides a framework for:
//! -   defining the construction of a cylinder,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class BRepPrimAPI_MakeCylinder : public BRepPrimAPI_MakeOneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  //! Make a cylinder.
  //! @param[in] R  cylinder radius
  //! @param[in] H  cylinder height
  Standard_EXPORT BRepPrimAPI_MakeCylinder(const double R, const double H);

  //! Make a cylinder (part cylinder).
  //! @param[in] R      cylinder radius
  //! @param[in] H      cylinder height
  //! @param[in] Angle  defines the missing portion of the cylinder
  Standard_EXPORT BRepPrimAPI_MakeCylinder(const double R, const double H, const double Angle);

  //! Make a cylinder of radius R and length H.
  //! @param[in] Axes  coordinate system for the construction of the cylinder
  //! @param[in] R     cylinder radius
  //! @param[in] H     cylinder height
  Standard_EXPORT BRepPrimAPI_MakeCylinder(const gp_Ax2& Axes, const double R, const double H);

  //! Make a cylinder of radius R and length H with
  //! angle H.
  //! Constructs
  //! -   a cylinder of radius R and height H, or
  //! -   a portion of cylinder of radius R and height H, and of
  //! the angle Angle defining the missing portion of the cylinder.
  //! The cylinder is constructed about the "Z Axis" of either:
  //! -   the global coordinate system, or
  //! -   the local coordinate system Axes.
  //! It is limited in this coordinate system as follows:
  //! -   in the v parametric direction (the Z axis), by the two
  //! parameter values 0 and H,
  //! -   and in the u parametric direction (the rotation angle
  //! around the Z Axis), in the case of a portion of a
  //! cylinder, by the two parameter values 0 and Angle.
  //! Angle is given in radians.
  //! The resulting shape is composed of:
  //! -   a lateral cylindrical face,
  //! -   two planar faces in the planes z = 0 and z = H
  //! (in the case of a complete cylinder, these faces are circles), and
  //! -   in case of a portion of a cylinder, two additional
  //! planar faces to close the shape.(two rectangles in the
  //! planes u = 0 and u = Angle).
  //! Exceptions Standard_DomainError if:
  //! -   R is less than or equal to Precision::Confusion(), or
  //! -   H is less than or equal to Precision::Confusion().
  Standard_EXPORT BRepPrimAPI_MakeCylinder(const gp_Ax2& Axes,
                                           const double  R,
                                           const double  H,
                                           const double  Angle);

  //! Returns the algorithm.
  Standard_EXPORT void* OneAxis() override;

  //! Returns the algorithm.
  Standard_EXPORT BRepPrim_Cylinder& Cylinder();

private:
  BRepPrim_Cylinder myCylinder;
};

