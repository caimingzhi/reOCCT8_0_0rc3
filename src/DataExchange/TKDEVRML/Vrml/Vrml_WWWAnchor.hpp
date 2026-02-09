#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>

enum Vrml_WWWAnchorMap
{
  Vrml_MAP_NONE,
  Vrml_POINT
};

#include <Standard_OStream.hpp>

class Vrml_WWWAnchor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_WWWAnchor(const TCollection_AsciiString& aName        = "",
                                 const TCollection_AsciiString& aDescription = "",
                                 const Vrml_WWWAnchorMap        aMap         = Vrml_MAP_NONE);

  Standard_EXPORT void SetName(const TCollection_AsciiString& aName);

  Standard_EXPORT TCollection_AsciiString Name() const;

  Standard_EXPORT void SetDescription(const TCollection_AsciiString& aDescription);

  Standard_EXPORT TCollection_AsciiString Description() const;

  Standard_EXPORT void SetMap(const Vrml_WWWAnchorMap aMap);

  Standard_EXPORT Vrml_WWWAnchorMap Map() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  TCollection_AsciiString myName;
  TCollection_AsciiString myDescription;
  Vrml_WWWAnchorMap       myMap;
};
