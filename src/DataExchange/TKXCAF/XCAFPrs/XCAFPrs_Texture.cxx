

#include <XCAFPrs_Texture.hpp>

#include <Graphic3d_TextureParams.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XCAFPrs_Texture, Graphic3d_Texture2D)

XCAFPrs_Texture::XCAFPrs_Texture(const occ::handle<Image_Texture>& theImageSource,
                                 const Graphic3d_TextureUnit       theUnit)
    : Graphic3d_Texture2D(""),
      myImageSource(theImageSource)
{
  if (!myImageSource.IsNull() && !myImageSource->TextureId().IsEmpty())
  {
    myTexId = myImageSource->TextureId();
  }
  myParams->SetTextureUnit(theUnit);
  myIsColorMap =
    theUnit == Graphic3d_TextureUnit_BaseColor || theUnit == Graphic3d_TextureUnit_Emissive;
}

occ::handle<Image_CompressedPixMap> XCAFPrs_Texture::GetCompressedImage(
  const occ::handle<Image_SupportedFormats>& theSupported)
{
  return !myImageSource.IsNull() ? myImageSource->ReadCompressedImage(theSupported)
                                 : occ::handle<Image_CompressedPixMap>();
}

occ::handle<Image_PixMap> XCAFPrs_Texture::GetImage(
  const occ::handle<Image_SupportedFormats>& theSupported)
{
  occ::handle<Image_PixMap> anImage;
  if (!myImageSource.IsNull())
  {
    anImage = myImageSource->ReadImage(theSupported);
    convertToCompatible(theSupported, anImage);
  }
  return anImage;
}
