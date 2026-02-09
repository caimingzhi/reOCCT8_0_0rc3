#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_OStream.hpp>

class Vrml_Instancing
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Instancing(const TCollection_AsciiString& aString);

  Standard_EXPORT Standard_OStream& DEF(Standard_OStream& anOStream) const;

  Standard_EXPORT Standard_OStream& USE(Standard_OStream& anOStream) const;

private:
  TCollection_AsciiString myName;
};
