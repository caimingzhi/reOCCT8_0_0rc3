

#include <Vrml_Group.hpp>

Vrml_Group::Vrml_Group()
{
  myFlagPrint = false;
}

Standard_OStream& Vrml_Group::Print(Standard_OStream& anOStream)
{
  if (myFlagPrint == 0)
  {
    anOStream << "Group {\n";
    myFlagPrint = true;
  }
  else
  {
    anOStream << "}\n";
    myFlagPrint = false;
  }
  return anOStream;
}
