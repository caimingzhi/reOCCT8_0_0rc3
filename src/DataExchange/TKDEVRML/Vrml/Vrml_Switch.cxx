

#include <Vrml_Switch.hpp>

Vrml_Switch::Vrml_Switch(const int aWhichChild)
{
  myWhichChild = aWhichChild;
}

void Vrml_Switch::SetWhichChild(const int aWhichChild)
{
  myWhichChild = aWhichChild;
}

int Vrml_Switch::WhichChild() const
{
  return myWhichChild;
}

Standard_OStream& Vrml_Switch::Print(Standard_OStream& anOStream) const
{
  anOStream << "Switch {\n";
  if (myWhichChild != -1)
  {
    anOStream << "    whichChild\t";
    anOStream << myWhichChild << "\n";
  }
  anOStream << "}\n";
  return anOStream;
}
