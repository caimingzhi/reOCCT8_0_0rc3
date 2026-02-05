#pragma once

#include <Standard_Transient.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <TCollection_AsciiString.hpp>

//! Describes custom vertex shader attribute.
class Graphic3d_ShaderAttribute : public Standard_Transient
{
public:
  //! Creates new attribute.
  Standard_EXPORT Graphic3d_ShaderAttribute(const TCollection_AsciiString& theName,
                                            const int                      theLocation);

  //! Destructor.
  Standard_EXPORT ~Graphic3d_ShaderAttribute() override;

  //! Returns name of shader variable.
  const TCollection_AsciiString& Name() const { return myName; }

  //! Returns attribute location to be bound on GLSL program linkage stage.
  int Location() const { return myLocation; }

protected:
  TCollection_AsciiString myName;     //!< attribute name
  int                     myLocation; //!< attribute location

public:
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ShaderAttribute, Standard_Transient)
};
