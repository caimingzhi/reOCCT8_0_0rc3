#pragma once

#include <Graphic3d_Aspects.hpp>

//! Creates and updates an attribute group for marker type primitives.
//! This group contains the type of marker, its color, and its scale factor.
class Graphic3d_AspectMarker3d : public Graphic3d_Aspects
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_AspectMarker3d, Graphic3d_Aspects)
public:
  //! Creates a context table for marker primitives
  //! defined with the following default values:
  //!
  //! Marker type : TOM_X
  //! Color       : YELLOW
  //! Scale factor: 1.0
  Standard_EXPORT Graphic3d_AspectMarker3d();

  Standard_EXPORT Graphic3d_AspectMarker3d(const Aspect_TypeOfMarker theType,
                                           const Quantity_Color&     theColor,
                                           const double              theScale);

  //! Creates a context table for marker primitives
  //! defined with the specified values.
  Standard_EXPORT Graphic3d_AspectMarker3d(
    const Quantity_Color&                            theColor,
    const int                                        theWidth,
    const int                                        theHeight,
    const occ::handle<NCollection_HArray1<uint8_t>>& theTextureBitmap);

  //! Creates a context table for marker primitives
  //! defined with the specified values.
  Standard_EXPORT Graphic3d_AspectMarker3d(const occ::handle<Image_PixMap>& theTextureImage);

  //! Return scale factor.
  float Scale() const { return myMarkerScale; }

  //! Modifies the scale factor.
  //! Marker type Aspect_TOM_POINT is not affected by the marker size scale factor.
  //! It is always the smallest displayable dot.
  //! Warning: Raises Standard_OutOfRange if the scale is a negative value.
  void SetScale(const float theScale) { SetMarkerScale(theScale); }

  //! Assign scale factor.
  void SetScale(const double theScale) { SetScale((float)theScale); }

  //! Return marker type.
  Aspect_TypeOfMarker Type() const { return myMarkerType; }

  //! Modifies the type of marker.
  void SetType(const Aspect_TypeOfMarker theType) { myMarkerType = theType; }

  //! Returns marker's texture size.
  Standard_EXPORT void GetTextureSize(int& theWidth, int& theHeight) const;

  //! Returns marker's image texture.
  //! Could be null handle if marker aspect has been initialized as default type of marker.
  const occ::handle<Graphic3d_MarkerImage>& GetMarkerImage() const { return myMarkerImage; }

  Standard_EXPORT void SetBitMap(const int                                        theWidth,
                                 const int                                        theHeight,
                                 const occ::handle<NCollection_HArray1<uint8_t>>& theTexture);
};
