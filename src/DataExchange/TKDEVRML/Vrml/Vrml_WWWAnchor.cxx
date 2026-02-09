

#include <Vrml_WWWAnchor.hpp>

Vrml_WWWAnchor::Vrml_WWWAnchor(const TCollection_AsciiString& aName,
                               const TCollection_AsciiString& aDescription,
                               const Vrml_WWWAnchorMap        aMap)
{
  myName        = aName;
  myDescription = aDescription;
  myMap         = aMap;
}

void Vrml_WWWAnchor::SetName(const TCollection_AsciiString& aName)
{
  myName = aName;
}

TCollection_AsciiString Vrml_WWWAnchor::Name() const
{
  return myName;
}

void Vrml_WWWAnchor::SetDescription(const TCollection_AsciiString& aDescription)
{
  myDescription = aDescription;
}

TCollection_AsciiString Vrml_WWWAnchor::Description() const
{
  return myDescription;
}

void Vrml_WWWAnchor::SetMap(const Vrml_WWWAnchorMap aMap)
{
  myMap = aMap;
}

Vrml_WWWAnchorMap Vrml_WWWAnchor::Map() const
{
  return myMap;
}

Standard_OStream& Vrml_WWWAnchor::Print(Standard_OStream& anOStream) const
{
  anOStream << "WWWAnchor {\n";

  if (!(myName.IsEqual("")))
  {
    anOStream << "    name\t";
    anOStream << '"' << myName << '"' << "\n";
  }

  if (!(myDescription.IsEqual("")))
  {
    anOStream << "    description\t";
    anOStream << '"' << myDescription << '"' << "\n";
  }

  switch (myMap)
  {
    case Vrml_MAP_NONE:
      break;
    case Vrml_POINT:
      anOStream << "    map\t\tPOINT\n";
      break;
  }

  anOStream << "}\n";
  return anOStream;
}
