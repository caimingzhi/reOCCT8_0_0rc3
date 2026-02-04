#pragma once


#include <Graphic3d_CubeMap.hpp>
#include <NCollection_Array1.hpp>
#include <OSD_Path.hpp>

//! Class to manage cubemap located in six different images.
class Graphic3d_CubeMapSeparate : public Graphic3d_CubeMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_CubeMapSeparate, Graphic3d_CubeMap)
public:
  //! Initializes cubemap to be loaded from file.
  //! @thePaths - array of paths to separate image files (has to have size equal 6).
  Standard_EXPORT Graphic3d_CubeMapSeparate(
    const NCollection_Array1<TCollection_AsciiString>& thePaths);

  //! Initializes cubemap to be set directly from PixMaps.
  //! @theImages - array if PixMaps (has to have size equal 6).
  Standard_EXPORT Graphic3d_CubeMapSeparate(
    const NCollection_Array1<occ::handle<Image_PixMap>>& theImages);

  //! Returns current cubemap side as compressed PixMap.
  Standard_EXPORT occ::handle<Image_CompressedPixMap> CompressedValue(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  //! Returns current side of cubemap as PixMap.
  //! Returns null handle if current side or whole cubemap is invalid.
  //! All origin images have to have the same sizes, format and quad shapes to form valid cubemap.
  Standard_EXPORT occ::handle<Image_PixMap> Value(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  //! Returns NULL.
  occ::handle<Image_PixMap> GetImage(const occ::handle<Image_SupportedFormats>&) override
  {
    return occ::handle<Image_PixMap>();
  }

  //! Checks if a texture class is valid or not.
  //! Returns true if the construction of the class is correct.
  Standard_EXPORT bool IsDone() const override;

  //! Empty destructor.
  ~Graphic3d_CubeMapSeparate() override = default;

protected:
  OSD_Path                  myPaths[6];  //!< array of paths to cubemap images
  occ::handle<Image_PixMap> myImages[6]; //!< array of cubemap images

  size_t       mySize;   //!< size of each side of cubemap
  Image_Format myFormat; //!< format each side of cubemap

private:
  //! Nulifies whole images array.
  void resetImages();
};

