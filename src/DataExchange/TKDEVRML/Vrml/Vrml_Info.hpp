#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_OStream.hpp>

class Vrml_Info
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Info(const TCollection_AsciiString& aString = "<Undefined info>");

  Standard_EXPORT void SetString(const TCollection_AsciiString& aString);

  Standard_EXPORT TCollection_AsciiString String() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  TCollection_AsciiString myString;
};
