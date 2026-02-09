#pragma once

#include <Graphic3d_CubeMapOrder.hpp>
#include <Graphic3d_TextureMap.hpp>

class Graphic3d_CubeMap : public Graphic3d_TextureMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_CubeMap, Graphic3d_TextureMap)
public:
  Standard_EXPORT Graphic3d_CubeMap(const TCollection_AsciiString& theFileName,
                                    bool                           theToGenerateMipmaps = false);

  Standard_EXPORT Graphic3d_CubeMap(
    const occ::handle<Image_PixMap>& thePixmap            = occ::handle<Image_PixMap>(),
    bool                             theToGenerateMipmaps = false);

  bool More() const { return !myEndIsReached; }

  Graphic3d_CubeMapSide CurrentSide() const { return myCurrentSide; }

  void Next()
  {
    if (!myEndIsReached && myCurrentSide == Graphic3d_CMS_NEG_Z)
    {
      myEndIsReached = true;
    }
    else
    {
      myCurrentSide = Graphic3d_CubeMapSide(myCurrentSide + 1);
    }
  }

  void SetZInversion(bool theZIsInverted) { myZIsInverted = theZIsInverted; }

  bool ZIsInverted() const { return myZIsInverted; }

  bool HasMipmaps() const { return myHasMipmaps; }

  void SetMipmapsGeneration(bool theToGenerateMipmaps) { myHasMipmaps = theToGenerateMipmaps; }

  virtual occ::handle<Image_CompressedPixMap> CompressedValue(
    const occ::handle<Image_SupportedFormats>& theSupported) = 0;

  virtual occ::handle<Image_PixMap> Value(
    const occ::handle<Image_SupportedFormats>& theSupported) = 0;

  Graphic3d_CubeMap& Reset()
  {
    myCurrentSide  = Graphic3d_CMS_POS_X;
    myEndIsReached = false;
    return *this;
  }

  Standard_EXPORT ~Graphic3d_CubeMap() override;

protected:
  Graphic3d_CubeMapSide myCurrentSide;

  bool myEndIsReached;
  bool myZIsInverted;
};
