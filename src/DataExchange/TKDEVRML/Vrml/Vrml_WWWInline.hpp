#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TCollection_AsciiString.hpp>
#include <gp_Vec.hpp>
#include <Standard_OStream.hpp>

class Vrml_WWWInline
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_WWWInline();

  Standard_EXPORT Vrml_WWWInline(const TCollection_AsciiString& aName,
                                 const gp_Vec&                  aBboxSize,
                                 const gp_Vec&                  aBboxCenter);

  Standard_EXPORT void SetName(const TCollection_AsciiString& aName);

  Standard_EXPORT TCollection_AsciiString Name() const;

  Standard_EXPORT void SetBboxSize(const gp_Vec& aBboxSize);

  Standard_EXPORT gp_Vec BboxSize() const;

  Standard_EXPORT void SetBboxCenter(const gp_Vec& aBboxCenter);

  Standard_EXPORT gp_Vec BboxCenter() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  TCollection_AsciiString myName;
  gp_Vec                  myBboxSize;
  gp_Vec                  myBboxCenter;
};
