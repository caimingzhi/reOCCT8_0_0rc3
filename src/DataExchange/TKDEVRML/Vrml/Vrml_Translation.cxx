

#include <Vrml_Translation.hpp>

Vrml_Translation::Vrml_Translation()
{
  gp_Vec tmpV(0, 0, 0);
  myTranslation = tmpV;
}

Vrml_Translation::Vrml_Translation(const gp_Vec& aTranslation)
{
  myTranslation = aTranslation;
}

void Vrml_Translation::SetTranslation(const gp_Vec& aTranslation)
{
  myTranslation = aTranslation;
}

gp_Vec Vrml_Translation::Translation() const
{
  return myTranslation;
}

Standard_OStream& Vrml_Translation::Print(Standard_OStream& anOStream) const
{
  anOStream << "Translation {\n";

  if (std::abs(myTranslation.X() - 0) > 0.0001 || std::abs(myTranslation.Y() - 0) > 0.0001
      || std::abs(myTranslation.Z() - 0) > 0.0001)
  {
    anOStream << "    translation\t";
    anOStream << myTranslation.X() << " " << myTranslation.Y() << " " << myTranslation.Z() << "\n";
  }

  anOStream << "}\n";
  return anOStream;
}
