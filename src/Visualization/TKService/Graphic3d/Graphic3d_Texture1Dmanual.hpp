#pragma once

#include <Graphic3d_Texture1D.hpp>
#include <Graphic3d_NameOfTexture1D.hpp>

class Graphic3d_Texture1Dmanual : public Graphic3d_Texture1D
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture1Dmanual, Graphic3d_Texture1D)
public:
  Standard_EXPORT Graphic3d_Texture1Dmanual(const TCollection_AsciiString& theFileName);

  Standard_EXPORT Graphic3d_Texture1Dmanual(const Graphic3d_NameOfTexture1D theNOT);

  Standard_EXPORT Graphic3d_Texture1Dmanual(const occ::handle<Image_PixMap>& thePixMap);
};
