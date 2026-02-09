

#include <Vrml_Instancing.hpp>

Vrml_Instancing::Vrml_Instancing(const TCollection_AsciiString& aString)
{
  TCollection_AsciiString tmpAS = aString;
  tmpAS.ChangeAll(' ', '_', true);
  myName = tmpAS;
}

Standard_OStream& Vrml_Instancing::DEF(Standard_OStream& anOStream) const
{
  anOStream << "DEF " << myName << "\n";
  return anOStream;
}

Standard_OStream& Vrml_Instancing::USE(Standard_OStream& anOStream) const
{
  anOStream << "USE " << myName << "\n";
  return anOStream;
}
