#pragma once

#include <Graphic3d_CubeMapOrder.hpp>
#include <Graphic3d_TextureMap.hpp>

//! Base class for cubemaps.
//! It is iterator over cubemap sides.
class Graphic3d_CubeMap : public Graphic3d_TextureMap
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_CubeMap, Graphic3d_TextureMap)
public:
  //! Constructor defining loading cubemap from file.
  Standard_EXPORT Graphic3d_CubeMap(const TCollection_AsciiString& theFileName,
                                    bool                           theToGenerateMipmaps = false);

  //! Constructor defining direct cubemap initialization from PixMap.
  Standard_EXPORT Graphic3d_CubeMap(
    const occ::handle<Image_PixMap>& thePixmap            = occ::handle<Image_PixMap>(),
    bool                             theToGenerateMipmaps = false);

  //! Returns whether the iterator has reached the end (true if it hasn't).
  bool More() const { return !myEndIsReached; }

  //! Returns current cubemap side (iterator state).
  Graphic3d_CubeMapSide CurrentSide() const { return myCurrentSide; }

  //! Moves iterator to the next cubemap side.
  //! Uses OpenGL cubemap sides order +X -> -X -> +Y -> -Y -> +Z -> -Z.
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

  //! Sets Z axis inversion (vertical flipping).
  void SetZInversion(bool theZIsInverted) { myZIsInverted = theZIsInverted; }

  //! Returns whether Z axis is inverted.
  bool ZIsInverted() const { return myZIsInverted; }

  //! Returns whether mipmaps of cubemap will be generated or not.
  bool HasMipmaps() const { return myHasMipmaps; }

  //! Sets whether to generate mipmaps of cubemap or not.
  void SetMipmapsGeneration(bool theToGenerateMipmaps) { myHasMipmaps = theToGenerateMipmaps; }

  //! Returns current cubemap side as compressed PixMap.
  //! Returns null handle if current side is invalid or if image is not in supported compressed
  //! format.
  virtual occ::handle<Image_CompressedPixMap> CompressedValue(
    const occ::handle<Image_SupportedFormats>& theSupported) = 0;

  //! Returns PixMap containing current side of cubemap.
  //! Returns null handle if current side is invalid.
  virtual occ::handle<Image_PixMap> Value(
    const occ::handle<Image_SupportedFormats>& theSupported) = 0;

  //! Sets iterator state to +X cubemap side.
  Graphic3d_CubeMap& Reset()
  {
    myCurrentSide  = Graphic3d_CMS_POS_X;
    myEndIsReached = false;
    return *this;
  }

  //! Empty destructor.
  Standard_EXPORT ~Graphic3d_CubeMap() override;

protected:
  Graphic3d_CubeMapSide myCurrentSide; //!< Iterator state
  // clang-format off
  bool      myEndIsReached; //!< Indicates whether end of iteration has been reached or hasn't
  bool      myZIsInverted;  //!< Indicates whether Z axis is inverted that allows to synchronize vertical flip of cubemap
  // clang-format on
};
