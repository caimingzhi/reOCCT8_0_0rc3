

#include <Vrml_Scale.hpp>

Vrml_Scale::Vrml_Scale()
{
  gp_Vec tmpV(1, 1, 1);
  myScaleFactor = tmpV;
}

Vrml_Scale::Vrml_Scale(const gp_Vec& aScaleFactor)
{
  myScaleFactor = aScaleFactor;
}

void Vrml_Scale::SetScaleFactor(const gp_Vec& aScaleFactor)
{
  myScaleFactor = aScaleFactor;
}

gp_Vec Vrml_Scale::ScaleFactor() const
{
  return myScaleFactor;
}

Standard_OStream& Vrml_Scale::Print(Standard_OStream& anOStream) const
{
  anOStream << "Scale {\n";

  if (std::abs(myScaleFactor.X() - 1) > 0.0001 || std::abs(myScaleFactor.Y() - 1) > 0.0001
      || std::abs(myScaleFactor.Z() - 1) > 0.0001)
  {
    anOStream << "    scaleFactor\t";
    anOStream << myScaleFactor.X() << " " << myScaleFactor.Y() << " " << myScaleFactor.Z() << "\n";
  }

  anOStream << "}\n";
  return anOStream;
}
