#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Torus.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
class gp_Ax2;

//! Describes functions to build tori or portions of tori.
//! A MakeTorus object provides a framework for:
//! -   defining the construction of a torus,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class BRepPrimAPI_MakeTorus : public BRepPrimAPI_MakeOneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  //! Make a torus.
  //! @param[in] R1  distance from the center of the pipe to the center of the torus
  //! @param[in] R2  radius of the pipe
  Standard_EXPORT BRepPrimAPI_MakeTorus(const double R1, const double R2);

  //! Make a section of a torus.
  //! @param[in] R1     distance from the center of the pipe to the center of the torus
  //! @param[in] R2     radius of the pipe
  //! @param[in] angle  angle to create a torus pipe segment
  Standard_EXPORT BRepPrimAPI_MakeTorus(const double R1, const double R2, const double angle);

  //! Make  a torus with angles on the small circle.
  //! @param[in] R1      distance from the center of the pipe to the center of the torus
  //! @param[in] R2      radius of the pipe
  //! @param[in] angle1  first  angle to create a torus ring segment
  //! @param[in] angle2  second angle to create a torus ring segment
  Standard_EXPORT BRepPrimAPI_MakeTorus(const double R1,
                                        const double R2,
                                        const double angle1,
                                        const double angle2);

  //! Make  a torus with angles on the small circle.
  //! @param[in] R1      distance from the center of the pipe to the center of the torus
  //! @param[in] R2      radius of the pipe
  //! @param[in] angle1  first  angle to create a torus ring segment
  //! @param[in] angle2  second angle to create a torus ring segment
  //! @param[in] angle   angle to create a torus pipe segment
  Standard_EXPORT BRepPrimAPI_MakeTorus(const double R1,
                                        const double R2,
                                        const double angle1,
                                        const double angle2,
                                        const double angle);

  //! Make a torus.
  //! @param[in] Axes  coordinate system for the construction of the sphere
  //! @param[in] R1    distance from the center of the pipe to the center of the torus
  //! @param[in] R2    radius of the pipe
  Standard_EXPORT BRepPrimAPI_MakeTorus(const gp_Ax2& Axes, const double R1, const double R2);

  //! Make a section of a torus.
  //! @param[in] Axes   coordinate system for the construction of the sphere
  //! @param[in] R1     distance from the center of the pipe to the center of the torus
  //! @param[in] R2     radius of the pipe
  //! @param[in] angle  angle to create a torus pipe segment
  Standard_EXPORT BRepPrimAPI_MakeTorus(const gp_Ax2& Axes,
                                        const double  R1,
                                        const double  R2,
                                        const double  angle);

  //! Make a torus.
  //! @param[in] Axes    coordinate system for the construction of the sphere
  //! @param[in] R1      distance from the center of the pipe to the center of the torus
  //! @param[in] R2      radius of the pipe
  //! @param[in] angle1  first  angle to create a torus ring segment
  //! @param[in] angle2  second angle to create a torus ring segment
  Standard_EXPORT BRepPrimAPI_MakeTorus(const gp_Ax2& Axes,
                                        const double  R1,
                                        const double  R2,
                                        const double  angle1,
                                        const double  angle2);

  //! Make a section of a torus of radii R1 R2.
  //! For all algorithms The resulting shape is composed of
  //! -      a lateral toroidal face,
  //! -      two conical faces (defined by the equation v = angle1 and
  //! v = angle2) if the sphere is truncated in the v parametric
  //! direction (they may be cylindrical faces in some
  //! particular conditions), and in case of a portion
  //! of torus, two planar faces to close the shape.(in the planes
  //! u = 0 and u = angle).
  //! Notes:
  //! -      The u parameter corresponds to a rotation angle around the Z axis.
  //! -      The circle whose radius is equal to the minor radius,
  //! located in the plane defined by the X axis and the Z axis,
  //! centered on the X axis, on its positive side, and positioned
  //! at a distance from the origin equal to the major radius, is
  //! the reference circle of the torus. The rotation around an
  //! axis parallel to the Y axis and passing through the center
  //! of the reference circle gives the v parameter on the
  //! reference circle. The X axis gives the origin of the v
  //! parameter. Near 0, as v increases, the Z coordinate increases
  //! (following the standard trigonometric convention: Z = r*sin(v)).
  Standard_EXPORT BRepPrimAPI_MakeTorus(const gp_Ax2& Axes,
                                        const double  R1,
                                        const double  R2,
                                        const double  angle1,
                                        const double  angle2,
                                        const double  angle);

  //! Returns the algorithm.
  Standard_EXPORT void* OneAxis() override;

  //! Returns the algorithm.
  Standard_EXPORT BRepPrim_Torus& Torus();

private:
  BRepPrim_Torus myTorus;
};
