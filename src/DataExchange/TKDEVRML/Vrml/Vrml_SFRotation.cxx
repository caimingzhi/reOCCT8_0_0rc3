

#include <Vrml_SFRotation.hpp>

Vrml_SFRotation::Vrml_SFRotation() = default;

Vrml_SFRotation::Vrml_SFRotation(const double aRotationX,
                                 const double aRotationY,
                                 const double aRotationZ,
                                 const double anAngle)
{
  myRotationX = aRotationX;
  myRotationY = aRotationY;
  myRotationZ = aRotationZ;
  myAngle     = anAngle;
}

void Vrml_SFRotation::SetRotationX(const double aRotationX)
{
  myRotationX = aRotationX;
}

double Vrml_SFRotation::RotationX() const
{
  return myRotationX;
}

void Vrml_SFRotation::SetRotationY(const double aRotationY)
{
  myRotationY = aRotationY;
}

double Vrml_SFRotation::RotationY() const
{
  return myRotationY;
}

void Vrml_SFRotation::SetRotationZ(const double aRotationZ)
{
  myRotationZ = aRotationZ;
}

double Vrml_SFRotation::RotationZ() const
{
  return myRotationZ;
}

void Vrml_SFRotation::SetAngle(const double anAngle)
{
  myAngle = anAngle;
}

double Vrml_SFRotation::Angle() const
{
  return myAngle;
}
