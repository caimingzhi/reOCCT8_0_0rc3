#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Cone.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
class gp_Ax2;

//! Describes functions to build cones or portions of cones.
//! A MakeCone object provides a framework for:
//! -   defining the construction of a cone,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class BRepPrimAPI_MakeCone : public BRepPrimAPI_MakeOneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  //! Make a cone.
  //! @param[in] R1  cone bottom radius, may be null (z = 0)
  //! @param[in] R2  cone top radius, may be null (z = H)
  //! @param[in] H   cone height
  Standard_EXPORT BRepPrimAPI_MakeCone(const double R1, const double R2, const double H);

  //! Make a cone.
  //! @param[in] R1     cone bottom radius, may be null (z = 0)
  //! @param[in] R2     cone top radius, may be null (z = H)
  //! @param[in] H      cone height
  //! @param[in] angle  angle to create a part cone
  Standard_EXPORT BRepPrimAPI_MakeCone(const double R1,
                                       const double R2,
                                       const double H,
                                       const double angle);

  //! Make a cone.
  //! @param[in] axes  coordinate system for the construction of the cone
  //! @param[in] R1    cone bottom radius, may be null (z = 0)
  //! @param[in] R2    cone top radius, may be null (z = H)
  //! @param[in] H     cone height
  Standard_EXPORT BRepPrimAPI_MakeCone(const gp_Ax2& Axes,
                                       const double  R1,
                                       const double  R2,
                                       const double  H);

  //! Make a cone of height H radius R1 in the plane z =
  //! 0, R2 in the plane Z = H. R1 and R2 may be null.
  //! Take a section of <angle>
  //! Constructs a cone, or a portion of a cone, of height H,
  //! and radius R1 in the plane z = 0 and R2 in the plane
  //! z = H. The result is a sharp cone if R1 or R2 is equal to 0.
  //! The cone is constructed about the "Z Axis" of either:
  //! -   the global coordinate system, or
  //! -   the local coordinate system Axes.
  //! It is limited in these coordinate systems as follows:
  //! -   in the v parametric direction (the Z coordinate), by
  //! the two parameter values 0 and H,
  //! -   and in the u parametric direction (defined by the
  //! angle of rotation around the Z axis), in the case of a
  //! portion of a cone, by the two parameter values 0 and
  //! angle. Angle is given in radians.
  //! The resulting shape is composed of:
  //! -   a lateral conical face
  //! -   two planar faces in the planes z = 0 and z = H,
  //! or only one planar face in one of these two planes if a
  //! radius value is null (in the case of a complete cone,
  //! these faces are circles), and
  //! -   and in the case of a portion of a cone, two planar
  //! faces to close the shape. (either two parallelograms or
  //! two triangles, in the planes u = 0 and u = angle).
  //! Exceptions
  //! Standard_DomainError if:
  //! -   H is less than or equal to Precision::Confusion(), or
  //! -   the half-angle at the apex of the cone, defined by
  //! R1, R2 and H, is less than Precision::Confusion()/H, or greater than
  //! (Pi/2)-Precision::Confusion()/H.f
  Standard_EXPORT BRepPrimAPI_MakeCone(const gp_Ax2& Axes,
                                       const double  R1,
                                       const double  R2,
                                       const double  H,
                                       const double  angle);

  //! Returns the algorithm.
  Standard_EXPORT void* OneAxis() override;

  //! Returns the algorithm.
  Standard_EXPORT BRepPrim_Cone& Cone();

private:
  BRepPrim_Cone myCone;
};
