

#include <Graphic3d_Texture3D.hpp>

#include <Graphic3d_TextureParams.hpp>
#include <Image_AlienPixMap.hpp>
#include <Message.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_Texture3D, Graphic3d_TextureMap)

Graphic3d_Texture3D::Graphic3d_Texture3D(const TCollection_AsciiString& theFileName)
    : Graphic3d_TextureMap(theFileName, Graphic3d_TypeOfTexture_3D)
{
  myParams->SetFilter(Graphic3d_TOTF_TRILINEAR);
}

Graphic3d_Texture3D::Graphic3d_Texture3D(const occ::handle<Image_PixMap>& thePixMap)
    : Graphic3d_TextureMap(thePixMap, Graphic3d_TypeOfTexture_3D)
{
  myParams->SetFilter(Graphic3d_TOTF_TRILINEAR);
}

Graphic3d_Texture3D::Graphic3d_Texture3D(
  const NCollection_Array1<TCollection_AsciiString>& theFiles)
    : Graphic3d_TextureMap("", Graphic3d_TypeOfTexture_3D)
{
  myParams->SetFilter(Graphic3d_TOTF_TRILINEAR);
  myPaths.Resize(theFiles.Lower(), theFiles.Upper(), false);
  myPaths.Assign(theFiles);
}

Graphic3d_Texture3D::~Graphic3d_Texture3D() = default;

void Graphic3d_Texture3D::SetImage(const occ::handle<Image_PixMap>& thePixMap)
{
  myPixMap = thePixMap;
  myPath   = OSD_Path();

  NCollection_Array1<TCollection_AsciiString> anArr;
  myPaths.Move(anArr);
}

occ::handle<Image_PixMap> Graphic3d_Texture3D::GetImage(
  const occ::handle<Image_SupportedFormats>& theSupported)
{
  if (myPaths.IsEmpty() || !myPixMap.IsNull())
  {
    return base_type::GetImage(theSupported);
  }

  occ::handle<Image_PixMap> anImage3D;
  const int                 aNbSlices = myPaths.Length();
  for (int aSlice = 0; aSlice < aNbSlices; ++aSlice)
  {
    const TCollection_AsciiString& aSlicePath = myPaths[myPaths.Lower() + aSlice];
    occ::handle<Image_AlienPixMap> anImage    = new Image_AlienPixMap();
    if (!anImage->Load(aSlicePath))
    {
      Message::SendFail() << "Graphic3d_Texture3D::GetImage() failed to load slice " << aSlice
                          << " from '" << aSlicePath << "'";
      return occ::handle<Image_PixMap>();
    }

    convertToCompatible(theSupported, anImage);
    if (anImage3D.IsNull())
    {
      myIsTopDown = anImage->IsTopDown();
      anImage3D   = new Image_PixMap();
      anImage3D->SetTopDown(myIsTopDown);
      if (!anImage3D->InitTrash3D(
            anImage->Format(),
            NCollection_Vec3<size_t>(anImage->SizeX(), anImage->SizeY(), aNbSlices),
            anImage->SizeRowBytes()))
      {
        Message::SendFail() << "Graphic3d_Texture3D::GetImage() failed to allocate 3D image "
                            << (int)anImage->SizeX() << "x" << (int)anImage->SizeY() << "x"
                            << aNbSlices;
        return occ::handle<Image_PixMap>();
      }
    }
    if (anImage->Format() != anImage3D->Format() || anImage->SizeX() != anImage3D->SizeX()
        || anImage->SizeY() != anImage3D->SizeY()
        || anImage->SizeRowBytes() != anImage3D->SizeRowBytes())
    {
      Message::SendFail() << "Graphic3d_Texture3D::GetImage() slice " << aSlice << " from '"
                          << aSlicePath << "' have different dimensions";
      return occ::handle<Image_PixMap>();
    }

    memcpy(anImage3D->ChangeSlice(aSlice), anImage->Data(), anImage->SizeBytes());
  }

  return anImage3D;
}
