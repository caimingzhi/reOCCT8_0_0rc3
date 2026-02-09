#include <Graphic3d_TextureEnv.hpp>
#include <Graphic3d_TextureParams.hpp>
#include <Graphic3d_TypeOfTexture.hpp>
#include <Graphic3d_TypeOfTextureMode.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_TextureEnv, Graphic3d_TextureRoot)

static const char* NameOfTextureEnv_to_FileName[] = {"env_clouds.rgb",
                                                     "env_cv.rgb",
                                                     "env_medit.rgb",
                                                     "env_pearl.rgb",
                                                     "env_sky1.rgb",
                                                     "env_sky2.rgb",
                                                     "env_lines.rgb",
                                                     "env_road.rgb"};

Graphic3d_TextureEnv::Graphic3d_TextureEnv(const TCollection_AsciiString& theFileName)
    : Graphic3d_TextureRoot(theFileName, Graphic3d_TypeOfTexture_2D),
      myName(Graphic3d_NOT_ENV_UNKNOWN)
{
  myHasMipmaps = true;
  myParams->SetFilter(Graphic3d_TOTF_TRILINEAR);
  myParams->SetGenMode(Graphic3d_TOTM_SPHERE,
                       NCollection_Vec4<float>(1.0f, 0.0f, 0.0f, 0.0f),
                       NCollection_Vec4<float>(0.0f, 1.0f, 0.0f, 0.0f));
}

Graphic3d_TextureEnv::Graphic3d_TextureEnv(const Graphic3d_NameOfTextureEnv theNOT)
    : Graphic3d_TextureRoot(NameOfTextureEnv_to_FileName[theNOT], Graphic3d_TypeOfTexture_2D),
      myName(theNOT)
{
  myHasMipmaps = true;
  myPath.SetTrek(Graphic3d_TextureRoot::TexturesFolder());
  myTexId = TCollection_AsciiString("Graphic3d_TextureEnv_") + NameOfTextureEnv_to_FileName[theNOT];

  myParams->SetFilter(Graphic3d_TOTF_TRILINEAR);
  myParams->SetGenMode(Graphic3d_TOTM_SPHERE,
                       NCollection_Vec4<float>(1.0f, 0.0f, 0.0f, 0.0f),
                       NCollection_Vec4<float>(0.0f, 1.0f, 0.0f, 0.0f));
}

Graphic3d_TextureEnv::Graphic3d_TextureEnv(const occ::handle<Image_PixMap>& thePixMap)
    : Graphic3d_TextureRoot(thePixMap, Graphic3d_TypeOfTexture_2D),
      myName(Graphic3d_NOT_ENV_UNKNOWN)
{
  myHasMipmaps = true;
  myParams->SetFilter(Graphic3d_TOTF_TRILINEAR);
  myParams->SetGenMode(Graphic3d_TOTM_SPHERE,
                       NCollection_Vec4<float>(1.0f, 0.0f, 0.0f, 0.0f),
                       NCollection_Vec4<float>(0.0f, 1.0f, 0.0f, 0.0f));
}

Graphic3d_NameOfTextureEnv Graphic3d_TextureEnv::Name() const
{
  return myName;
}

int Graphic3d_TextureEnv::NumberOfTextures()
{
  return sizeof(NameOfTextureEnv_to_FileName) / sizeof(char*);
}

TCollection_AsciiString Graphic3d_TextureEnv::TextureName(const int theRank)
{
  if (theRank < 1 || theRank > NumberOfTextures())
  {
    throw Standard_OutOfRange("BAD index of texture");
  }

  TCollection_AsciiString aFileName(NameOfTextureEnv_to_FileName[theRank - 1]);
  int                     i = aFileName.SearchFromEnd(".");
  return aFileName.SubString(5, i - 1);
}
