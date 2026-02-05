#include <Graphic3d_ShaderAttribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_ShaderAttribute, Standard_Transient)

//=================================================================================================

Graphic3d_ShaderAttribute::Graphic3d_ShaderAttribute(const TCollection_AsciiString& theName,
                                                     const int                      theLocation)
    : myName(theName),
      myLocation(theLocation)
{
}

//=================================================================================================

Graphic3d_ShaderAttribute::~Graphic3d_ShaderAttribute() = default;
