

#include <Graphic3d_CubeMapSeparate.hpp>

#include <Image_AlienPixMap.hpp>
#include <Image_DDSParser.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <OSD_File.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_CubeMapSeparate, Graphic3d_CubeMap)

Graphic3d_CubeMapSeparate::Graphic3d_CubeMapSeparate(
  const NCollection_Array1<TCollection_AsciiString>& thePaths)
{
  if (thePaths.Size() == 6)
  {
    for (unsigned int i = 0; i < 6; ++i)
    {
      myPaths[i] = thePaths[i];
    }
  }
  else
  {
    throw Standard_Failure("Invalid number of paths to load Graphic3d_CubeMapSeparate");
  }
}

Graphic3d_CubeMapSeparate::Graphic3d_CubeMapSeparate(
  const NCollection_Array1<occ::handle<Image_PixMap>>& theImages)
{
  if (theImages.Size() == 6)
  {
    if (theImages[0].IsNull())
    {
      return;
    }

    if (theImages[0]->SizeX() != theImages[0]->SizeY())
    {
      return;
    }

    myImages[0] = theImages[0];
    myIsTopDown = myImages[0]->IsTopDown();

    for (unsigned int i = 1; i < 6; ++i)
    {
      if (!theImages[i].IsNull())
      {
        if (theImages[i]->SizeX() == myImages[0]->SizeX()
            && theImages[i]->SizeY() == myImages[0]->SizeY()
            && theImages[i]->Format() == myImages[0]->Format()
            && theImages[i]->IsTopDown() == myImages[0]->IsTopDown())
        {
          myImages[i] = theImages[i];
          continue;
        }
      }
      resetImages();
      return;
    }
  }
  else
  {
    throw Standard_Failure("Invalid number of images in Graphic3d_CubeMapSeparate initialization");
  }
}

occ::handle<Image_CompressedPixMap> Graphic3d_CubeMapSeparate::CompressedValue(
  const occ::handle<Image_SupportedFormats>& theSupported)
{
  if (!myImages[0].IsNull())
  {
    return occ::handle<Image_CompressedPixMap>();
  }

  const Graphic3d_CubeMapOrder anOrder = Graphic3d_CubeMapOrder::Default();
  TCollection_AsciiString      aFilePath;
  myPaths[anOrder[myCurrentSide]].SystemName(aFilePath);
  if (aFilePath.IsEmpty())
  {
    return occ::handle<Image_CompressedPixMap>();
  }

  occ::handle<Image_CompressedPixMap> anImage = Image_DDSParser::Load(theSupported, aFilePath, 0);
  if (anImage.IsNull() || anImage->SizeX() != anImage->SizeY())
  {
    return occ::handle<Image_CompressedPixMap>();
  }

  if (myCurrentSide == 0)
  {
    mySize      = anImage->SizeX();
    myFormat    = anImage->BaseFormat();
    myIsTopDown = anImage->IsTopDown();
    return anImage;
  }

  if (anImage->BaseFormat() == myFormat && anImage->SizeX() == (int)mySize)
  {
    return anImage;
  }

  Message::SendWarning(TCollection_AsciiString() + "'" + aFilePath
                       + "' inconsistent image format or dimension in Graphic3d_CubeMapSeparate");
  return occ::handle<Image_CompressedPixMap>();
}

occ::handle<Image_PixMap> Graphic3d_CubeMapSeparate::Value(
  const occ::handle<Image_SupportedFormats>& theSupported)
{
  Graphic3d_CubeMapOrder anOrder = Graphic3d_CubeMapOrder::Default();
  if (!myIsTopDown)
  {
    anOrder.Swap(Graphic3d_CMS_POS_Y, Graphic3d_CMS_NEG_Y);
  }

  if (!myImages[anOrder[myCurrentSide]].IsNull())
  {
    return myImages[anOrder[myCurrentSide]];
  }
  else
  {
    TCollection_AsciiString aFilePath;
    myPaths[anOrder[myCurrentSide]].SystemName(aFilePath);
    if (!aFilePath.IsEmpty())
    {
      occ::handle<Image_AlienPixMap> anImage = new Image_AlienPixMap;
      if (anImage->Load(aFilePath))
      {
        convertToCompatible(theSupported, anImage);
        if (anImage->SizeX() == anImage->SizeY())
        {
          if (myCurrentSide == 0)
          {
            mySize      = anImage->SizeX();
            myFormat    = anImage->Format();
            myIsTopDown = anImage->IsTopDown();
            return anImage;
          }
          else
          {
            if (anImage->Format() == myFormat && anImage->SizeX() == mySize
                && anImage->IsTopDown() == myIsTopDown)
            {
              return anImage;
            }
            else
            {
              Message::SendWarning(
                TCollection_AsciiString() + "'" + aFilePath
                + "' inconsistent image format or dimension in Graphic3d_CubeMapSeparate");
            }
          }
        }
      }
      else
      {
        Message::SendWarning(TCollection_AsciiString() + "Unable to load '" + aFilePath
                             + "' image of Graphic3d_CubeMapSeparate");
      }
    }
    else
    {
      Message::SendWarning(TCollection_AsciiString() + "[" + myCurrentSide
                           + "] path of Graphic3d_CubeMapSeparate is invalid");
    }
  }

  return occ::handle<Image_PixMap>();
}

bool Graphic3d_CubeMapSeparate::IsDone() const
{
  if (!myImages[0].IsNull())
  {
    return true;
  }

  for (unsigned int i = 0; i < 6; ++i)
  {
    OSD_File aCubeMapFile(myPaths[i]);
    if (!aCubeMapFile.Exists())
    {
      return false;
    }
  }

  return true;
}

void Graphic3d_CubeMapSeparate::resetImages()
{
  for (unsigned int i = 0; i < 6; ++i)
  {
    myImages[i].Nullify();
  }
}
