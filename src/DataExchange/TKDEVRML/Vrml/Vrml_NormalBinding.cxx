

#include <Vrml_NormalBinding.hpp>

Vrml_NormalBinding::Vrml_NormalBinding(const Vrml_MaterialBindingAndNormalBinding aValue)
{
  myValue = aValue;
}

Vrml_NormalBinding::Vrml_NormalBinding()
{
  myValue = Vrml_DEFAULT;
}

void Vrml_NormalBinding::SetValue(const Vrml_MaterialBindingAndNormalBinding aValue)
{
  myValue = aValue;
}

Vrml_MaterialBindingAndNormalBinding Vrml_NormalBinding::Value() const
{
  return myValue;
}

Standard_OStream& Vrml_NormalBinding::Print(Standard_OStream& anOStream) const
{
  anOStream << "NormalBinding {\n";
  switch (myValue)
  {
    case Vrml_DEFAULT:
      break;
    case Vrml_OVERALL:
      anOStream << "    value\tOVERALL\n";
      break;
    case Vrml_PER_PART:
      anOStream << "    value\tPER_PART\n";
      break;
    case Vrml_PER_PART_INDEXED:
      anOStream << "    value\tPER_PART_INDEXED\n";
      break;
    case Vrml_PER_FACE:
      anOStream << "    value\tPER_FACE\n";
      break;
    case Vrml_PER_FACE_INDEXED:
      anOStream << "    value\tPER_FACE_INDEXED\n";
      break;
    case Vrml_PER_VERTEX:
      anOStream << "    value\tPER_VERTEX\n";
      break;
    case Vrml_PER_VERTEX_INDEXED:
      anOStream << "    value\tPER_VERTEX_INDEXED\n";
      break;
  }
  anOStream << "}\n";
  return anOStream;
}
