#include <Graphic3d_Texture1D.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_Texture1D, Graphic3d_TextureMap)

static const char* NameOfTexture1d_to_FileName[] = {"1d_elevation.rgb"};

Graphic3d_Texture1D::Graphic3d_Texture1D(const TCollection_AsciiString& theFileName,
                                         const Graphic3d_TypeOfTexture  theType)
    : Graphic3d_TextureMap(theFileName, theType),
      myName(Graphic3d_NOT_1D_UNKNOWN)
{
}

Graphic3d_Texture1D::Graphic3d_Texture1D(const Graphic3d_NameOfTexture1D theNOT,
                                         const Graphic3d_TypeOfTexture   theType)
    : Graphic3d_TextureMap(NameOfTexture1d_to_FileName[theNOT], theType),
      myName(theNOT)
{
  myPath.SetTrek(Graphic3d_TextureRoot::TexturesFolder());
  myTexId = TCollection_AsciiString("Graphic3d_Texture1D_") + NameOfTexture1d_to_FileName[theNOT];
}

Graphic3d_Texture1D::Graphic3d_Texture1D(const occ::handle<Image_PixMap>& thePixMap,
                                         const Graphic3d_TypeOfTexture    theType)
    : Graphic3d_TextureMap(thePixMap, theType),
      myName(Graphic3d_NOT_1D_UNKNOWN)
{
}

Graphic3d_NameOfTexture1D Graphic3d_Texture1D::Name() const
{
  return myName;
}

int Graphic3d_Texture1D::NumberOfTextures()
{
  return sizeof(NameOfTexture1d_to_FileName) / sizeof(char*);
}

TCollection_AsciiString Graphic3d_Texture1D::TextureName(const int theRank)
{
  if (theRank < 1 || theRank > NumberOfTextures())
  {
    throw Standard_OutOfRange("BAD index of texture");
  }

  TCollection_AsciiString aFileName(NameOfTexture1d_to_FileName[theRank - 1]);
  int                     i = aFileName.SearchFromEnd(".");
  return aFileName.SubString(4, i - 1);
}
