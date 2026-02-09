

#include <Graphic3d_CubeMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_CubeMap, Graphic3d_TextureMap)

Graphic3d_CubeMap::Graphic3d_CubeMap(const TCollection_AsciiString& theFileName,
                                     bool                           theToGenerateMipmaps)
    : Graphic3d_TextureMap(theFileName, Graphic3d_TypeOfTexture_CUBEMAP),
      myCurrentSide(Graphic3d_CMS_POS_X),
      myEndIsReached(false),
      myZIsInverted(false)
{
  myHasMipmaps = theToGenerateMipmaps;
}

Graphic3d_CubeMap::Graphic3d_CubeMap(const occ::handle<Image_PixMap>& thePixmap,
                                     bool                             theToGenerateMipmaps)
    : Graphic3d_TextureMap(thePixmap, Graphic3d_TypeOfTexture_CUBEMAP),
      myCurrentSide(Graphic3d_CMS_POS_X),
      myEndIsReached(false),
      myZIsInverted(false)
{
  myHasMipmaps = theToGenerateMipmaps;
}

Graphic3d_CubeMap::~Graphic3d_CubeMap() = default;
