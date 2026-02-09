

#include <Vrml_TransformSeparator.hpp>

Vrml_TransformSeparator::Vrml_TransformSeparator()
{
  myFlagPrint = false;
}

Standard_OStream& Vrml_TransformSeparator::Print(Standard_OStream& anOStream)
{
  if (myFlagPrint == 0)
  {
    anOStream << "TransformSeparator {\n";
    myFlagPrint = true;
  }
  else
  {
    anOStream << "}\n";
    myFlagPrint = false;
  }
  return anOStream;
}
