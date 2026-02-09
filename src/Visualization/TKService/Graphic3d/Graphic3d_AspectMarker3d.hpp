#pragma once

#include <Graphic3d_Aspects.hpp>

class Graphic3d_AspectMarker3d : public Graphic3d_Aspects
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_AspectMarker3d, Graphic3d_Aspects)
public:
  Standard_EXPORT Graphic3d_AspectMarker3d();

  Standard_EXPORT Graphic3d_AspectMarker3d(const Aspect_TypeOfMarker theType,
                                           const Quantity_Color&     theColor,
                                           const double              theScale);

  Standard_EXPORT Graphic3d_AspectMarker3d(
    const Quantity_Color&                            theColor,
    const int                                        theWidth,
    const int                                        theHeight,
    const occ::handle<NCollection_HArray1<uint8_t>>& theTextureBitmap);

  Standard_EXPORT Graphic3d_AspectMarker3d(const occ::handle<Image_PixMap>& theTextureImage);

  float Scale() const { return myMarkerScale; }

  void SetScale(const float theScale) { SetMarkerScale(theScale); }

  void SetScale(const double theScale) { SetScale((float)theScale); }

  Aspect_TypeOfMarker Type() const { return myMarkerType; }

  void SetType(const Aspect_TypeOfMarker theType) { myMarkerType = theType; }

  Standard_EXPORT void GetTextureSize(int& theWidth, int& theHeight) const;

  const occ::handle<Graphic3d_MarkerImage>& GetMarkerImage() const { return myMarkerImage; }

  Standard_EXPORT void SetBitMap(const int                                        theWidth,
                                 const int                                        theHeight,
                                 const occ::handle<NCollection_HArray1<uint8_t>>& theTexture);
};
