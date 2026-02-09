#pragma once

#include <Graphic3d_CubeMap.hpp>
#include <NCollection_Array1.hpp>
#include <OSD_Path.hpp>

class Graphic3d_CubeMapPacked : public Graphic3d_CubeMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_CubeMapPacked, Graphic3d_CubeMap)
public:
  Standard_EXPORT Graphic3d_CubeMapPacked(
    const TCollection_AsciiString&         theFileName,
    const Graphic3d_ValidatedCubeMapOrder& theOrder = Graphic3d_CubeMapOrder::Default());

  Standard_EXPORT Graphic3d_CubeMapPacked(
    const occ::handle<Image_PixMap>&       theImage,
    const Graphic3d_ValidatedCubeMapOrder& theOrder = Graphic3d_CubeMapOrder::Default());

  Standard_EXPORT occ::handle<Image_CompressedPixMap> CompressedValue(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  Standard_EXPORT occ::handle<Image_PixMap> Value(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  ~Graphic3d_CubeMapPacked() override = default;

private:
  static bool checkOrder(const NCollection_Array1<unsigned int>& theOrder);

  static bool checkImage(const occ::handle<Image_PixMap>& theImage, unsigned int& theTileNumberX);

  void tryLoadImage(const occ::handle<Image_SupportedFormats>& theSupported,
                    const TCollection_AsciiString&             theFilePath);

protected:
  Graphic3d_CubeMapOrder myOrder;
  unsigned int           myTileNumberX;
};
