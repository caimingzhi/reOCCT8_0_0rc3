#pragma once

#include <Graphic3d_TextureMap.hpp>
#include <NCollection_Array1.hpp>

class Graphic3d_Texture3D : public Graphic3d_TextureMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture3D, Graphic3d_TextureMap)
public:
  Standard_EXPORT Graphic3d_Texture3D(const TCollection_AsciiString& theFileName);

  Standard_EXPORT Graphic3d_Texture3D(const occ::handle<Image_PixMap>& thePixMap);

  Standard_EXPORT Graphic3d_Texture3D(const NCollection_Array1<TCollection_AsciiString>& theFiles);

  Standard_EXPORT ~Graphic3d_Texture3D() override;

  Standard_EXPORT void SetImage(const occ::handle<Image_PixMap>& thePixMap);

  Standard_EXPORT occ::handle<Image_PixMap> GetImage(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

protected:
  NCollection_Array1<TCollection_AsciiString> myPaths;
};
