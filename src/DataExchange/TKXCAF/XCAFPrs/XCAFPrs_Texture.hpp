#pragma once

#include <Graphic3d_Texture2D.hpp>
#include <Graphic3d_TextureUnit.hpp>
#include <Image_Texture.hpp>

class XCAFPrs_Texture : public Graphic3d_Texture2D
{
  DEFINE_STANDARD_RTTIEXT(XCAFPrs_Texture, Graphic3d_Texture2D)
public:
  Standard_EXPORT XCAFPrs_Texture(const occ::handle<Image_Texture>& theImageSource,
                                  const Graphic3d_TextureUnit       theUnit);

  Standard_EXPORT occ::handle<Image_CompressedPixMap> GetCompressedImage(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  Standard_EXPORT occ::handle<Image_PixMap> GetImage(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  const occ::handle<Image_Texture>& GetImageSource() const { return myImageSource; }

protected:
  occ::handle<Image_Texture> myImageSource;
};
