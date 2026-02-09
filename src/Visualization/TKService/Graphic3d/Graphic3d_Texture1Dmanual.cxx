#include <Graphic3d_Texture1Dmanual.hpp>

#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_Texture1Dmanual, Graphic3d_Texture1D)

Graphic3d_Texture1Dmanual::Graphic3d_Texture1Dmanual(const TCollection_AsciiString& theFileName)
    : Graphic3d_Texture1D(theFileName, Graphic3d_TypeOfTexture_1D)
{
}

Graphic3d_Texture1Dmanual::Graphic3d_Texture1Dmanual(const Graphic3d_NameOfTexture1D theNOT)
    : Graphic3d_Texture1D(theNOT, Graphic3d_TypeOfTexture_1D)
{
}

Graphic3d_Texture1Dmanual::Graphic3d_Texture1Dmanual(const occ::handle<Image_PixMap>& thePixMap)
    : Graphic3d_Texture1D(thePixMap, Graphic3d_TypeOfTexture_1D)
{
}
