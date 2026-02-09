#pragma once

#include <Standard.hpp>

#include <Graphic3d_Texture1D.hpp>
#include <Graphic3d_NameOfTexture1D.hpp>
class TCollection_AsciiString;

class Graphic3d_Texture1Dsegment : public Graphic3d_Texture1D
{

public:
  Standard_EXPORT Graphic3d_Texture1Dsegment(const TCollection_AsciiString& theFileName);

  Standard_EXPORT Graphic3d_Texture1Dsegment(const Graphic3d_NameOfTexture1D theNOT);

  Standard_EXPORT Graphic3d_Texture1Dsegment(const occ::handle<Image_PixMap>& thePixMap);

  Standard_EXPORT void SetSegment(const float theX1,
                                  const float theY1,
                                  const float theZ1,
                                  const float theX2,
                                  const float theY2,
                                  const float theZ2);

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
