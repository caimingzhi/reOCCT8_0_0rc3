#pragma once


#include <Standard.hpp>

#include <Graphic3d_NameOfTexture1D.hpp>
#include <Graphic3d_TextureMap.hpp>
#include <Graphic3d_TypeOfTexture.hpp>
#include <Image_PixMap.hpp>
#include <Standard_Integer.hpp>
class TCollection_AsciiString;

//! This is an abstract class for managing 1D textures.
class Graphic3d_Texture1D : public Graphic3d_TextureMap
{

public:
  //! Returns the name of the predefined textures or NOT_1D_UNKNOWN
  //! when the name is given as a filename.
  Standard_EXPORT Graphic3d_NameOfTexture1D Name() const;

  //! Returns the number of predefined textures.
  Standard_EXPORT static int NumberOfTextures();

  //! Returns the name of the predefined texture of rank <aRank>
  Standard_EXPORT static TCollection_AsciiString TextureName(const int aRank);

  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture1D, Graphic3d_TextureMap)

protected:
  Standard_EXPORT Graphic3d_Texture1D(const TCollection_AsciiString& theFileName,
                                      const Graphic3d_TypeOfTexture  theType);

  Standard_EXPORT Graphic3d_Texture1D(const Graphic3d_NameOfTexture1D theName,
                                      const Graphic3d_TypeOfTexture   theType);

  Standard_EXPORT Graphic3d_Texture1D(const occ::handle<Image_PixMap>& thePixMap,
                                      const Graphic3d_TypeOfTexture    theType);

private:
  Graphic3d_NameOfTexture1D myName;
};

