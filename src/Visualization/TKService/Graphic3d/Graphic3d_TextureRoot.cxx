#include <Graphic3d_TextureRoot.hpp>

#include <Graphic3d_GraphicDriver.hpp>
#include <Graphic3d_TextureParams.hpp>
#include <Image_AlienPixMap.hpp>
#include <Image_DDSParser.hpp>
#include <Image_SupportedFormats.hpp>
#include <OSD_Directory.hpp>
#include <OSD_Environment.hpp>
#include <OSD_File.hpp>
#include <OSD_OpenFile.hpp>

#include <atomic>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_TextureRoot, Standard_Transient)

namespace
{
  static std::atomic<int> THE_TEXTURE_COUNTER(0);
}

//=================================================================================================

TCollection_AsciiString Graphic3d_TextureRoot::TexturesFolder()
{
  static bool                    IsDefined = false;
  static TCollection_AsciiString VarName;
  if (!IsDefined)
  {
    IsDefined = true;
    OSD_Environment aTexDirEnv("CSF_MDTVTexturesDirectory");
    VarName = aTexDirEnv.Value();
    if (VarName.IsEmpty())
    {
      OSD_Environment aCasRootEnv("CASROOT");
      VarName = aCasRootEnv.Value();
      if (!VarName.IsEmpty())
      {
        VarName += "/src/Textures";
      }
    }

    if (VarName.IsEmpty())
    {
#ifdef OCCT_DEBUG
      std::cerr
        << "Both environment variables CSF_MDTVTexturesDirectory and CASROOT are undefined!\n"
        << "At least one should be defined to use standard Textures.\n";
#endif
      throw Standard_Failure("CSF_MDTVTexturesDirectory and CASROOT are undefined");
    }

    const OSD_Path                aDirPath(VarName);
    OSD_Directory                 aDir(aDirPath);
    const TCollection_AsciiString aTexture = VarName + "/2d_MatraDatavision.rgb";
    OSD_File                      aTextureFile(aTexture);
    if (!aDir.Exists() || !aTextureFile.Exists())
    {
#ifdef OCCT_DEBUG
      std::cerr << " CSF_MDTVTexturesDirectory or CASROOT not correctly set\n";
      std::cerr << " not all files are found in : " << VarName.ToCString() << std::endl;
#endif
      throw Standard_Failure("CSF_MDTVTexturesDirectory or CASROOT not correctly set");
    }
  }
  return VarName;
}

//=================================================================================================

Graphic3d_TextureRoot::Graphic3d_TextureRoot(const TCollection_AsciiString& theFileName,
                                             const Graphic3d_TypeOfTexture  theType)
    : myParams(new Graphic3d_TextureParams()),
      myPath(theFileName),
      myRevision(0),
      myType(theType == Graphic3d_TOT_2D_MIPMAP ? Graphic3d_TypeOfTexture_2D : theType),
      myIsColorMap(true),
      myIsTopDown(true),
      myHasMipmaps(theType == Graphic3d_TOT_2D_MIPMAP)
{
  generateId();
}

//=================================================================================================

Graphic3d_TextureRoot::Graphic3d_TextureRoot(const occ::handle<Image_PixMap>& thePixMap,
                                             const Graphic3d_TypeOfTexture    theType)
    : myParams(new Graphic3d_TextureParams()),
      myPixMap(thePixMap),
      myRevision(0),
      myType(theType == Graphic3d_TOT_2D_MIPMAP ? Graphic3d_TypeOfTexture_2D : theType),
      myIsColorMap(true),
      myIsTopDown(true),
      myHasMipmaps(theType == Graphic3d_TOT_2D_MIPMAP)
{
  generateId();
}

//=================================================================================================

Graphic3d_TextureRoot::~Graphic3d_TextureRoot() = default;

//=================================================================================================

void Graphic3d_TextureRoot::generateId()
{
  myTexId = TCollection_AsciiString("Graphic3d_TextureRoot_")
            + TCollection_AsciiString(++THE_TEXTURE_COUNTER);
}

//=================================================================================================

occ::handle<Image_CompressedPixMap> Graphic3d_TextureRoot::GetCompressedImage(
  const occ::handle<Image_SupportedFormats>& theSupported)
{
  if (!myPixMap.IsNull())
  {
    return occ::handle<Image_CompressedPixMap>();
  }

  // Case 2: texture source is specified as path
  TCollection_AsciiString aFilePath;
  myPath.SystemName(aFilePath);
  if (aFilePath.IsEmpty())
  {
    return occ::handle<Image_CompressedPixMap>();
  }

  TCollection_AsciiString aFilePathLower = aFilePath;
  aFilePathLower.LowerCase();
  if (!aFilePathLower.EndsWith(".dds"))
  {
    // do not waste time on file system access in case of wrong file extension
    return occ::handle<Image_CompressedPixMap>();
  }

  if (occ::handle<Image_CompressedPixMap> anImage =
        Image_DDSParser::Load(theSupported, aFilePath, 0))
  {
    myIsTopDown = anImage->IsTopDown();
    return anImage;
  }
  return occ::handle<Image_CompressedPixMap>();
}

//=================================================================================================

occ::handle<Image_PixMap> Graphic3d_TextureRoot::GetImage(
  const occ::handle<Image_SupportedFormats>& theSupported)
{
  if (occ::handle<Image_PixMap> anOldImage = GetImage())
  {
    myIsTopDown = anOldImage->IsTopDown();
    return anOldImage; // compatibility with old API
  }

  // Case 1: texture source is specified as pixmap
  if (!myPixMap.IsNull())
  {
    myIsTopDown = myPixMap->IsTopDown();
    return myPixMap;
  }

  // Case 2: texture source is specified as path
  TCollection_AsciiString aFilePath;
  myPath.SystemName(aFilePath);
  if (aFilePath.IsEmpty())
  {
    return occ::handle<Image_PixMap>();
  }

  occ::handle<Image_AlienPixMap> anImage = new Image_AlienPixMap();
  if (anImage->Load(aFilePath))
  {
    myIsTopDown = anImage->IsTopDown();
    convertToCompatible(theSupported, anImage);
    return anImage;
  }

  return occ::handle<Image_PixMap>();
}

//=================================================================================================

void Graphic3d_TextureRoot::convertToCompatible(
  const occ::handle<Image_SupportedFormats>& theSupported,
  const occ::handle<Image_PixMap>&           theImage)
{
  if (theImage.IsNull() || theSupported.IsNull() || theSupported->IsSupported(theImage->Format()))
  {
    return;
  }

  switch (theImage->Format())
  {
    // BGR formats are unsupported in OpenGL ES, only RGB
    case Image_Format_BGR:
      Image_PixMap::SwapRgbaBgra(*theImage);
      theImage->SetFormat(Image_Format_RGB);
      break;
    case Image_Format_BGRA:
    case Image_Format_BGR32:
      Image_PixMap::SwapRgbaBgra(*theImage);
      theImage->SetFormat(theImage->Format() == Image_Format_BGR32 ? Image_Format_RGB32
                                                                   : Image_Format_RGBA);
      break;
    default:
      break;
  }
}

//=================================================================================================

bool Graphic3d_TextureRoot::IsDone() const
{
  // Case 1: texture source is specified as pixmap
  if (!myPixMap.IsNull())
  {
    return !myPixMap->IsEmpty();
  }

  // Case 2: texture source is specified as path
  OSD_File aTextureFile(myPath);
  return aTextureFile.Exists();
}
