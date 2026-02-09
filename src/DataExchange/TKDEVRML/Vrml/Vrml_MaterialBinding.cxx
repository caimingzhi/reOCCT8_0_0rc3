

#include <Vrml_MaterialBinding.hpp>

Vrml_MaterialBinding::Vrml_MaterialBinding(const Vrml_MaterialBindingAndNormalBinding aValue)
{
  myValue = aValue;
}

Vrml_MaterialBinding::Vrml_MaterialBinding()
{
  myValue = Vrml_DEFAULT;
}

void Vrml_MaterialBinding::SetValue(const Vrml_MaterialBindingAndNormalBinding aValue)
{
  myValue = aValue;
}

Vrml_MaterialBindingAndNormalBinding Vrml_MaterialBinding::Value() const
{
  return myValue;
}

Standard_OStream& Vrml_MaterialBinding::Print(Standard_OStream& anOStream) const
{
  anOStream << "MaterialBinding {\n";
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
