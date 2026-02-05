#pragma once

#include <Graphic3d_Texture1D.hpp>
#include <Graphic3d_NameOfTexture1D.hpp>

//! This class provides the implementation of a manual 1D texture.
//! you MUST provide texture coordinates on your facets if you want to see your texture.
class Graphic3d_Texture1Dmanual : public Graphic3d_Texture1D
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture1Dmanual, Graphic3d_Texture1D)
public:
  //! Creates a texture from the file FileName.
  Standard_EXPORT Graphic3d_Texture1Dmanual(const TCollection_AsciiString& theFileName);

  //! Create a texture from a predefined texture name set.
  Standard_EXPORT Graphic3d_Texture1Dmanual(const Graphic3d_NameOfTexture1D theNOT);

  //! Creates a texture from the pixmap.
  Standard_EXPORT Graphic3d_Texture1Dmanual(const occ::handle<Image_PixMap>& thePixMap);
};
