

#include <Vrml_Rotation.hpp>
#include <Vrml_SFRotation.hpp>

Vrml_Rotation::Vrml_Rotation()
{
  Vrml_SFRotation tmpR(0, 0, 1, 0);
  myRotation = tmpR;
}

Vrml_Rotation::Vrml_Rotation(const Vrml_SFRotation& aRotation)
{
  myRotation = aRotation;
}

void Vrml_Rotation::SetRotation(const Vrml_SFRotation& aRotation)
{
  myRotation = aRotation;
}

Vrml_SFRotation Vrml_Rotation::Rotation() const
{
  return myRotation;
}

Standard_OStream& Vrml_Rotation::Print(Standard_OStream& anOStream) const
{
  anOStream << "Rotation {\n";

  if (std::abs(myRotation.RotationX() - 0) > 0.0001 || std::abs(myRotation.RotationY() - 0) > 0.0001
      || std::abs(myRotation.RotationZ() - 1) > 0.0001 || std::abs(myRotation.Angle() - 0) > 0.0001)
  {
    anOStream << "    rotation\t";
    anOStream << myRotation.RotationX() << " " << myRotation.RotationY() << " ";
    anOStream << myRotation.RotationZ() << " " << myRotation.Angle() << "\n";
  }

  anOStream << "}\n";
  return anOStream;
}
