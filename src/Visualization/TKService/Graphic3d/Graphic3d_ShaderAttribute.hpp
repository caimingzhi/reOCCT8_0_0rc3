#pragma once

#include <Standard_Transient.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <TCollection_AsciiString.hpp>

class Graphic3d_ShaderAttribute : public Standard_Transient
{
public:
  Standard_EXPORT Graphic3d_ShaderAttribute(const TCollection_AsciiString& theName,
                                            const int                      theLocation);

  Standard_EXPORT ~Graphic3d_ShaderAttribute() override;

  const TCollection_AsciiString& Name() const { return myName; }

  int Location() const { return myLocation; }

protected:
  TCollection_AsciiString myName;
  int                     myLocation;

public:
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ShaderAttribute, Standard_Transient)
};
