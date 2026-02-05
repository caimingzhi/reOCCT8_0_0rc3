#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>

//! defines SFRotation type of VRML field types.
//! The 4 values represent an axis of rotation followed by amount of
//! right-handed rotation about the that axis, in radians.
class Vrml_SFRotation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_SFRotation();

  Standard_EXPORT Vrml_SFRotation(const double aRotationX,
                                  const double aRotationY,
                                  const double aRotationZ,
                                  const double anAngle);

  Standard_EXPORT void SetRotationX(const double aRotationX);

  Standard_EXPORT double RotationX() const;

  Standard_EXPORT void SetRotationY(const double aRotationY);

  Standard_EXPORT double RotationY() const;

  Standard_EXPORT void SetRotationZ(const double aRotationZ);

  Standard_EXPORT double RotationZ() const;

  Standard_EXPORT void SetAngle(const double anAngle);

  Standard_EXPORT double Angle() const;

private:
  double myRotationX;
  double myRotationY;
  double myRotationZ;
  double myAngle;
};
