#pragma once

#include <Graphic3d_CubeMap.hpp>
#include <NCollection_Array1.hpp>
#include <OSD_Path.hpp>

class Graphic3d_CubeMapSeparate : public Graphic3d_CubeMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_CubeMapSeparate, Graphic3d_CubeMap)
public:
  Standard_EXPORT Graphic3d_CubeMapSeparate(
    const NCollection_Array1<TCollection_AsciiString>& thePaths);

  Standard_EXPORT Graphic3d_CubeMapSeparate(
    const NCollection_Array1<occ::handle<Image_PixMap>>& theImages);

  Standard_EXPORT occ::handle<Image_CompressedPixMap> CompressedValue(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  Standard_EXPORT occ::handle<Image_PixMap> Value(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  occ::handle<Image_PixMap> GetImage(const occ::handle<Image_SupportedFormats>&) override
  {
    return occ::handle<Image_PixMap>();
  }

  Standard_EXPORT bool IsDone() const override;

  ~Graphic3d_CubeMapSeparate() override = default;

protected:
  OSD_Path                  myPaths[6];
  occ::handle<Image_PixMap> myImages[6];

  size_t       mySize;
  Image_Format myFormat;

private:
  void resetImages();
};
