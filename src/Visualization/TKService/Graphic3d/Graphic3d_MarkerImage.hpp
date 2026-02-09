#pragma once

#include <Aspect_TypeOfMarker.hpp>
#include <NCollection_Vec4.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_AsciiString.hpp>

class Image_PixMap;

class Graphic3d_MarkerImage : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_MarkerImage, Standard_Transient)
public:
  Standard_EXPORT static occ::handle<Graphic3d_MarkerImage> StandardMarker(
    const Aspect_TypeOfMarker      theMarkerType,
    const float                    theScale,
    const NCollection_Vec4<float>& theColor);

public:
  Standard_EXPORT Graphic3d_MarkerImage(
    const occ::handle<Image_PixMap>& theImage,
    const occ::handle<Image_PixMap>& theImageAlpha = occ::handle<Image_PixMap>());

  Standard_EXPORT Graphic3d_MarkerImage(const occ::handle<NCollection_HArray1<uint8_t>>& theBitMap,
                                        const int                                        theWidth,
                                        const int                                        theHeight);

  Standard_EXPORT const occ::handle<Image_PixMap>& GetImage();

  Standard_EXPORT const occ::handle<Image_PixMap>& GetImageAlpha();

  Standard_EXPORT const TCollection_AsciiString& GetImageId() const;

  Standard_EXPORT const TCollection_AsciiString& GetImageAlphaId() const;

  Standard_EXPORT void GetTextureSize(int& theWidth, int& theHeight) const;

  Standard_EXPORT bool IsColoredImage() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<uint8_t>> GetBitMapArray(
    const double theAlphaValue = 0.5,
    const bool   theIsTopDown  = false) const;

protected:
  Standard_EXPORT Graphic3d_MarkerImage(
    const TCollection_AsciiString&   theId,
    const TCollection_AsciiString&   theAlphaId,
    const occ::handle<Image_PixMap>& theImage,
    const occ::handle<Image_PixMap>& theImageAlpha = occ::handle<Image_PixMap>());

private:
  TCollection_AsciiString myImageId;
  TCollection_AsciiString myImageAlphaId;

  occ::handle<NCollection_HArray1<uint8_t>> myBitMap;
  occ::handle<Image_PixMap>                 myImage;
  occ::handle<Image_PixMap>                 myImageAlpha;
  int                                       myMargin;

  int myWidth;
  int myHeight;
};
