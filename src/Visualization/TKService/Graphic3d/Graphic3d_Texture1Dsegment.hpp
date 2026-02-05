#pragma once

#include <Standard.hpp>

#include <Graphic3d_Texture1D.hpp>
#include <Graphic3d_NameOfTexture1D.hpp>
class TCollection_AsciiString;

//! This class provides the implementation
//! of a 1D texture applicable along a segment.
//! You might use the SetSegment() method
//! to set the way the texture is "stretched" on facets.
class Graphic3d_Texture1Dsegment : public Graphic3d_Texture1D
{

public:
  //! Creates a texture from a file
  Standard_EXPORT Graphic3d_Texture1Dsegment(const TCollection_AsciiString& theFileName);

  //! Creates a texture from a predefined texture name set.
  Standard_EXPORT Graphic3d_Texture1Dsegment(const Graphic3d_NameOfTexture1D theNOT);

  //! Creates a texture from the pixmap.
  Standard_EXPORT Graphic3d_Texture1Dsegment(const occ::handle<Image_PixMap>& thePixMap);

  //! Sets the texture application bounds. Defines the way
  //! the texture is stretched across facets.
  //! Default values are <0.0, 0.0, 0.0> , <0.0, 0.0, 1.0>
  Standard_EXPORT void SetSegment(const float theX1,
                                  const float theY1,
                                  const float theZ1,
                                  const float theX2,
                                  const float theY2,
                                  const float theZ2);

  //! Returns the values of the current segment X1, Y1, Z1 , X2, Y2, Z2.
  Standard_EXPORT void Segment(float& theX1,
                               float& theY1,
                               float& theZ1,
                               float& theX2,
                               float& theY2,
                               float& theZ2) const;

  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture1Dsegment, Graphic3d_Texture1D)

private:
  float myX1;
  float myY1;
  float myZ1;
  float myX2;
  float myY2;
  float myZ2;
};
