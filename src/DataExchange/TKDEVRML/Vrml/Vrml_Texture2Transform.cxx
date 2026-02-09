

#include <Vrml_Texture2Transform.hpp>

Vrml_Texture2Transform::Vrml_Texture2Transform()
{
  gp_Vec2d tmpVec(0, 0);
  myTranslation = tmpVec;
  myCenter      = tmpVec;

  myRotation = 0;

  tmpVec.SetCoord(1, 1);
  myScaleFactor = tmpVec;
}

Vrml_Texture2Transform::Vrml_Texture2Transform(const gp_Vec2d& aTranslation,
                                               const double    aRotation,
                                               const gp_Vec2d& aScaleFactor,
                                               const gp_Vec2d& aCenter)
{
  myTranslation = aTranslation;
  myRotation    = aRotation;
  myScaleFactor = aScaleFactor;
  myCenter      = aCenter;
}

void Vrml_Texture2Transform::SetTranslation(const gp_Vec2d& aTranslation)
{
  myTranslation = aTranslation;
}

gp_Vec2d Vrml_Texture2Transform::Translation() const
{
  return myTranslation;
}

void Vrml_Texture2Transform::SetRotation(const double aRotation)
{
  myRotation = aRotation;
}

double Vrml_Texture2Transform::Rotation() const
{
  return myRotation;
}

void Vrml_Texture2Transform::SetScaleFactor(const gp_Vec2d& aScaleFactor)
{
  myScaleFactor = aScaleFactor;
}

gp_Vec2d Vrml_Texture2Transform::ScaleFactor() const
{
  return myScaleFactor;
}

void Vrml_Texture2Transform::SetCenter(const gp_Vec2d& aCenter)
{
  myCenter = aCenter;
}

gp_Vec2d Vrml_Texture2Transform::Center() const
{
  return myCenter;
}

Standard_OStream& Vrml_Texture2Transform::Print(Standard_OStream& anOStream) const
{
  anOStream << "Texture2Transform {\n";

  if (std::abs(myTranslation.X() - 0) > 0.0001 || std::abs(myTranslation.Y() - 0) > 0.0001)
  {
    anOStream << "    translation\t";
    anOStream << myTranslation.X() << " " << myTranslation.Y() << "\n";
  }

  if (std::abs(myRotation - 0) > 0.0001)
  {
    anOStream << "    rotation\t";
    anOStream << myRotation << "\n";
  }

  if (std::abs(myScaleFactor.X() - 0) > 0.0001 || std::abs(myScaleFactor.Y() - 0) > 0.0001)
  {
    anOStream << "    scaleFactor\t";
    anOStream << myScaleFactor.X() << " " << myScaleFactor.Y() << "\n";
  }

  if (std::abs(myCenter.X() - 0) > 0.0001 || std::abs(myCenter.Y() - 0) > 0.0001)
  {
    anOStream << "    center\t";
    anOStream << myCenter.X() << " " << myCenter.Y() << "\n";
  }

  anOStream << "}\n";
  return anOStream;
}
