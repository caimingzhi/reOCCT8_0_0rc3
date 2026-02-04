#pragma once


#include <Graphic3d_CubeMap.hpp>
#include <NCollection_Array1.hpp>
#include <OSD_Path.hpp>

//! Class is intended to process cubemap packed into single image plane.
class Graphic3d_CubeMapPacked : public Graphic3d_CubeMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_CubeMapPacked, Graphic3d_CubeMap)
public:
  //! Initialization to load cubemap from file.
  //! @theFileName - path to the cubemap image
  //! @theOrder - array containing six different indexes of cubemap sides which maps tile grid to
  //! cubemap sides
  Standard_EXPORT Graphic3d_CubeMapPacked(
    const TCollection_AsciiString&         theFileName,
    const Graphic3d_ValidatedCubeMapOrder& theOrder = Graphic3d_CubeMapOrder::Default());

  //! Initialization to set cubemap directly by PixMap.
  //! @thePixMap - origin PixMap
  //! @theOrder - array containing six different indexes of cubemap sides which maps tile grid to
  //! cubemap sides
  Standard_EXPORT Graphic3d_CubeMapPacked(
    const occ::handle<Image_PixMap>&       theImage,
    const Graphic3d_ValidatedCubeMapOrder& theOrder = Graphic3d_CubeMapOrder::Default());

  //! Returns current cubemap side as compressed PixMap.
  Standard_EXPORT occ::handle<Image_CompressedPixMap> CompressedValue(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  //! Returns current cubemap side as PixMap.
  //! Resulting PixMap is memory wrapper over original image.
  //! Returns null handle if current side or whole cubemap is invalid.
  //! Origin image has to contain six quad tiles having one sizes without any gaps to be valid.
  Standard_EXPORT occ::handle<Image_PixMap> Value(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  //! Empty destructor.
  ~Graphic3d_CubeMapPacked() override = default;

private:
  //! Checks whether given tiles order is valid.
  static bool checkOrder(const NCollection_Array1<unsigned int>& theOrder);

  //! Checks whether given pixmap is valid to contain six tiles.
  static bool checkImage(const occ::handle<Image_PixMap>& theImage, unsigned int& theTileNumberX);

  //! Tries to load image from file and checks it after that.
  //! Does nothing in case of fail.
  void tryLoadImage(const occ::handle<Image_SupportedFormats>& theSupported,
                    const TCollection_AsciiString&             theFilePath);

protected:
  Graphic3d_CubeMapOrder myOrder;       //!< order mapping tile grit to cubemap sides
  unsigned int           myTileNumberX; //!< width of tile grid
};

