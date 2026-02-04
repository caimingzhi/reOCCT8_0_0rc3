#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Revolution.hpp>
class gp_Pnt;
class gp_Ax2;
class TopoDS_Face;

//! Implements the sphere primitive
class BRepPrim_Sphere : public BRepPrim_Revolution
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a Sphere at origin with Radius. The axes
  //! of the sphere are the reference axes. An error is
  //! raised if the radius is < Resolution.
  Standard_EXPORT BRepPrim_Sphere(const double Radius);

  //! Creates a Sphere with Center and Radius.
  //! Axes are the reference axes.
  //! This is the STEP constructor.
  Standard_EXPORT BRepPrim_Sphere(const gp_Pnt& Center, const double Radius);

  //! Creates a sphere with given axes system.
  Standard_EXPORT BRepPrim_Sphere(const gp_Ax2& Axes, const double Radius);

  //! The surface normal should be directed towards the
  //! outside.
  Standard_EXPORT TopoDS_Face MakeEmptyLateralFace() const override;

private:
  Standard_EXPORT void SetMeridian();

  double myRadius;
};

