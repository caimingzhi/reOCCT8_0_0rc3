#include <Image_Diff.hpp>

#include <Image_AlienPixMap.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hpp>

#include <cstdlib>

IMPLEMENT_STANDARD_RTTIEXT(Image_Diff, Standard_Transient)

namespace
{

  static const size_t Image_Diff_NbOfNeighborPixels = 8;

  static const int Image_Diff_NEIGHBOR_PIXELS[Image_Diff_NbOfNeighborPixels][2] =
    {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

  static bool isBlackPixel(const Image_PixMap& theData, size_t theY, size_t theX)
  {
    switch (theData.Format())
    {
      case Image_Format_Gray:
      case Image_Format_Alpha:
      {
        return theData.Value<unsigned char>(theY, theX) == 0;
      }
      case Image_Format_RGB:
      case Image_Format_BGR:
      case Image_Format_RGB32:
      case Image_Format_BGR32:
      case Image_Format_RGBA:
      case Image_Format_BGRA:
      {
        const uint8_t* aColor = theData.RawValue(theY, theX);
        return aColor[0] == 0 && aColor[1] == 0 && aColor[2] == 0;
      }
      default:
      {
        const Quantity_ColorRGBA       aPixelRgba = theData.PixelColor((int)theY, (int)theX);
        const NCollection_Vec4<float>& aPixel     = aPixelRgba;
        return aPixel.r() == 0.0f && aPixel.g() == 0.0f && aPixel.b() == 0.0f;
      }
    }
  }

} // namespace

Image_Diff::Image_Diff()
    : myColorTolerance(0.0),
      myIsBorderFilterOn(false)
{
}

Image_Diff::~Image_Diff()
{
  releaseGroupsOfDiffPixels();
}

bool Image_Diff::Init(const occ::handle<Image_PixMap>& theImageRef,
                      const occ::handle<Image_PixMap>& theImageNew,
                      const bool                       theToBlackWhite)
{
  myImageRef.Nullify();
  myImageNew.Nullify();
  myDiffPixels.Clear();
  releaseGroupsOfDiffPixels();
  if (theImageRef.IsNull() || theImageNew.IsNull() || theImageRef->IsEmpty()
      || theImageNew->IsEmpty() || theImageRef->SizeX() != theImageNew->SizeX()
      || theImageRef->SizeY() != theImageNew->SizeY()
      || theImageRef->Format() != theImageNew->Format())
  {
    Message::SendFail("Error: Images have different format or dimensions");
    return false;
  }
  else if (theImageRef->SizeX() >= 0xFFFF || theImageRef->SizeY() >= 0xFFFF)
  {
    Message::SendFail("Error: Images are too large");
    return false;
  }

  myImageRef = theImageRef;
  myImageNew = theImageNew;
  if (theToBlackWhite)
  {
    Image_PixMap::ToBlackWhite(*myImageRef);
    Image_PixMap::ToBlackWhite(*myImageNew);
  }
  return true;
}

bool Image_Diff::Init(const TCollection_AsciiString& theImgPathRef,
                      const TCollection_AsciiString& theImgPathNew,
                      const bool                     theToBlackWhite)
{
  occ::handle<Image_AlienPixMap> anImgRef = new Image_AlienPixMap();
  occ::handle<Image_AlienPixMap> anImgNew = new Image_AlienPixMap();
  if (!anImgRef->Load(theImgPathRef) || !anImgNew->Load(theImgPathNew))
  {
    Message::SendFail("Error: Failed to load image(s) file(s)");
    return false;
  }
  return Init(anImgRef, anImgNew, theToBlackWhite);
}

int Image_Diff::Compare()
{

  int aNbDiffColors = 0;
  myDiffPixels.Clear();

  if (myImageRef.IsNull() || myImageNew.IsNull())
  {
    return -1;
  }

  if (myImageNew->SizeBytes() == myImageRef->SizeBytes()
      && memcmp(myImageNew->Data(), myImageRef->Data(), myImageRef->SizeBytes()) == 0)
  {
    return 0;
  }

  switch (myImageRef->Format())
  {
    case Image_Format_Gray:
    case Image_Format_Alpha:
    {

      const int aDiffThreshold = int(255.0 * myColorTolerance);
      for (size_t aRow = 0; aRow < myImageRef->SizeY(); ++aRow)
      {
        for (size_t aCol = 0; aCol < myImageRef->SizeX(); ++aCol)
        {
          const int aDiff = int(myImageNew->Value<unsigned char>(aRow, aCol))
                            - int(myImageRef->Value<unsigned char>(aRow, aCol));
          if (std::abs(aDiff) > aDiffThreshold)
          {
            myDiffPixels.Append(PackXY((uint16_t)aCol, (uint16_t)aRow));
            ++aNbDiffColors;
          }
        }
      }
      break;
    }
    case Image_Format_RGB:
    case Image_Format_BGR:
    case Image_Format_RGB32:
    case Image_Format_BGR32:
    case Image_Format_RGBA:
    case Image_Format_BGRA:
    {

      const int aDiffThreshold = int(255.0 * myColorTolerance);

      for (size_t aRow = 0; aRow < myImageRef->SizeY(); ++aRow)
      {
        for (size_t aCol = 0; aCol < myImageRef->SizeX(); ++aCol)
        {

          const uint8_t* aColorRef = myImageRef->RawValue(aRow, aCol);
          const uint8_t* aColorNew = myImageNew->RawValue(aRow, aCol);
          const int      aDiff     = NCollection_Vec3<int>(int(aColorRef[0]) - int(aColorNew[0]),
                                                  int(aColorRef[1]) - int(aColorNew[1]),
                                                  int(aColorRef[2]) - int(aColorNew[2]))
                              .cwiseAbs()
                              .maxComp();
          if (aDiff > aDiffThreshold)
          {
            myDiffPixels.Append(PackXY((uint16_t)aCol, (uint16_t)aRow));
            ++aNbDiffColors;
          }
        }
      }
      break;
    }
    default:
    {

      const float aDiffThreshold = float(myColorTolerance);
      for (size_t aRow = 0; aRow < myImageRef->SizeY(); ++aRow)
      {
        for (size_t aCol = 0; aCol < myImageRef->SizeX(); ++aCol)
        {

          const Quantity_ColorRGBA       aPixel1Rgba = myImageRef->PixelColor(int(aCol), int(aRow));
          const Quantity_ColorRGBA       aPixel2Rgba = myImageNew->PixelColor(int(aCol), int(aRow));
          const NCollection_Vec3<float>& aPixel1     = aPixel1Rgba.GetRGB();
          const NCollection_Vec3<float>& aPixel2     = aPixel2Rgba.GetRGB();
          const float                    aDiff       = (aPixel2 - aPixel1).cwiseAbs().maxComp();
          if (aDiff > aDiffThreshold)
          {
            myDiffPixels.Append(PackXY((uint16_t)aCol, (uint16_t)aRow));
            ++aNbDiffColors;
          }
        }
      }
      break;
    }
  }

  if (myIsBorderFilterOn && !myDiffPixels.IsEmpty())
  {
    aNbDiffColors = ignoreBorderEffect();
  }

  return aNbDiffColors;
}

bool Image_Diff::SaveDiffImage(Image_PixMap& theDiffImage) const
{
  if (myImageRef.IsNull() || myImageNew.IsNull())
  {
    return false;
  }

  if (theDiffImage.IsEmpty() || theDiffImage.SizeX() != myImageRef->SizeX()
      || theDiffImage.SizeY() != myImageRef->SizeY())
  {
    if (!theDiffImage.InitTrash(Image_Format_Gray, myImageRef->SizeX(), myImageRef->SizeY()))
    {
      return false;
    }
  }

  const Quantity_ColorRGBA aWhiteRgba(1.0f, 1.0f, 1.0f, 1.0f);

  memset(theDiffImage.ChangeData(), 0, theDiffImage.SizeBytes());
  if (myGroupsOfDiffPixels.IsEmpty())
  {
    if (myIsBorderFilterOn)
    {
      return true;
    }

    switch (theDiffImage.Format())
    {
      case Image_Format_Gray:
      case Image_Format_Alpha:
      {
        for (NCollection_Vector<int>::Iterator aPixelIter(myDiffPixels); aPixelIter.More();
             aPixelIter.Next())
        {
          theDiffImage.ChangeValue<unsigned char>(UnpackY(aPixelIter.Value()),
                                                  UnpackX(aPixelIter.Value())) = 255;
        }
        break;
      }
      case Image_Format_RGB:
      case Image_Format_BGR:
      case Image_Format_RGB32:
      case Image_Format_BGR32:
      case Image_Format_RGBA:
      case Image_Format_BGRA:
      {
        for (NCollection_Vector<int>::Iterator aPixelIter(myDiffPixels); aPixelIter.More();
             aPixelIter.Next())
        {
          memset(
            theDiffImage.ChangeRawValue(UnpackY(aPixelIter.Value()), UnpackX(aPixelIter.Value())),
            255,
            3);
        }
        break;
      }
      default:
      {
        for (NCollection_Vector<int>::Iterator aPixelIter(myDiffPixels); aPixelIter.More();
             aPixelIter.Next())
        {
          theDiffImage.SetPixelColor(UnpackX(aPixelIter.Value()),
                                     UnpackY(aPixelIter.Value()),
                                     aWhiteRgba);
        }
        break;
      }
    }
    return true;
  }

  int aGroupId = 1;
  for (NCollection_List<occ::handle<TColStd_HPackedMapOfInteger>>::Iterator aGrIter(
         myGroupsOfDiffPixels);
       aGrIter.More();
       aGrIter.Next(), ++aGroupId)
  {
    if (myLinearGroups.Contains(aGroupId))
    {
      continue;
    }

    const occ::handle<TColStd_HPackedMapOfInteger>& aGroup = aGrIter.Value();
    switch (theDiffImage.Format())
    {
      case Image_Format_Gray:
      case Image_Format_Alpha:
      {
        for (TColStd_MapIteratorOfPackedMapOfInteger aPixelIter(aGroup->Map()); aPixelIter.More();
             aPixelIter.Next())
        {
          int aDiffPixel(aPixelIter.Key());
          theDiffImage.ChangeValue<unsigned char>(UnpackY(aDiffPixel), UnpackX(aDiffPixel)) = 255;
        }
        break;
      }
      case Image_Format_RGB:
      case Image_Format_BGR:
      case Image_Format_RGB32:
      case Image_Format_BGR32:
      case Image_Format_RGBA:
      case Image_Format_BGRA:
      {
        for (TColStd_MapIteratorOfPackedMapOfInteger aPixelIter(aGroup->Map()); aPixelIter.More();
             aPixelIter.Next())
        {
          int aDiffPixel(aPixelIter.Key());
          memset(theDiffImage.ChangeValue<uint8_t*>(UnpackY(aDiffPixel), UnpackX(aDiffPixel)),
                 255,
                 3);
        }
        break;
      }
      default:
      {
        for (TColStd_MapIteratorOfPackedMapOfInteger aPixelIter(aGroup->Map()); aPixelIter.More();
             aPixelIter.Next())
        {
          int aDiffPixel(aPixelIter.Key());
          theDiffImage.SetPixelColor(UnpackX(aDiffPixel), UnpackY(aDiffPixel), aWhiteRgba);
        }
        break;
      }
    }
  }

  return true;
}

bool Image_Diff::SaveDiffImage(const TCollection_AsciiString& theDiffPath) const
{
  if (myImageRef.IsNull() || myImageNew.IsNull() || theDiffPath.IsEmpty())
  {
    return false;
  }

  Image_AlienPixMap aDiff;
  if (!aDiff.InitTrash(Image_Format_Gray, myImageRef->SizeX(), myImageRef->SizeY())
      || !SaveDiffImage(aDiff))
  {
    return false;
  }

  return aDiff.Save(theDiffPath);
}

int Image_Diff::ignoreBorderEffect()
{
  if (myImageRef.IsNull() || myImageNew.IsNull())
  {
    return 0;
  }

  releaseGroupsOfDiffPixels();

  const int aLen1 = !myDiffPixels.IsEmpty() ? (myDiffPixels.Length() - 1) : 0;
  for (int aPixelId1 = 0; aPixelId1 < aLen1; ++aPixelId1)
  {
    int aValue1 = myDiffPixels.Value(aPixelId1);

    for (int aPixelId2 = aPixelId1 + 1; aPixelId2 < myDiffPixels.Length(); ++aPixelId2)
    {
      int aValue2 = myDiffPixels.Value(aPixelId2);
      if (std::abs(int(UnpackX(aValue1)) - int(UnpackX(aValue2))) <= 1
          && std::abs(int(UnpackY(aValue1)) - int(UnpackY(aValue2))) <= 1)
      {

        if (myGroupsOfDiffPixels.IsEmpty())
        {
          occ::handle<TColStd_HPackedMapOfInteger> aGroup = new TColStd_HPackedMapOfInteger();
          aGroup->ChangeMap().Add(aValue1);
          aGroup->ChangeMap().Add(aValue2);
          myGroupsOfDiffPixels.Append(aGroup);
        }
        else
        {

          bool isFound = false;
          for (NCollection_List<occ::handle<TColStd_HPackedMapOfInteger>>::Iterator aGrIter(
                 myGroupsOfDiffPixels);
               aGrIter.More();
               aGrIter.Next())
          {
            const occ::handle<TColStd_HPackedMapOfInteger>& aGroup = aGrIter.ChangeValue();
            if (aGroup->Map().Contains(aValue1))
            {
              aGroup->ChangeMap().Add(aValue2);
              isFound = true;
              break;
            }
          }

          if (!isFound)
          {

            occ::handle<TColStd_HPackedMapOfInteger> aGroup = new TColStd_HPackedMapOfInteger();
            aGroup->ChangeMap().Add(aValue1);
            aGroup->ChangeMap().Add(aValue2);
            myGroupsOfDiffPixels.Append(aGroup);
          }
        }
      }
    }
  }

  int aGroupId = 1;
  for (NCollection_List<occ::handle<TColStd_HPackedMapOfInteger>>::Iterator aGrIter(
         myGroupsOfDiffPixels);
       aGrIter.More();
       aGrIter.Next(), ++aGroupId)
  {
    int                                             aNeighboursNb = 0;
    bool                                            isLine        = true;
    const occ::handle<TColStd_HPackedMapOfInteger>& aGroup        = aGrIter.Value();
    if (aGroup->Map().IsEmpty())
    {
      continue;
    }

    int aDiffPixel = 0;
    for (TColStd_MapIteratorOfPackedMapOfInteger aPixelIter(aGroup->Map()); aPixelIter.More();
         aPixelIter.Next())
    {
      aDiffPixel    = aPixelIter.Key();
      aNeighboursNb = 0;

      for (size_t aNgbrIter = 0; aNgbrIter < Image_Diff_NbOfNeighborPixels; ++aNgbrIter)
      {
        int anX = UnpackX(aDiffPixel) + Image_Diff_NEIGHBOR_PIXELS[aNgbrIter][0];
        int anY = UnpackY(aDiffPixel) + Image_Diff_NEIGHBOR_PIXELS[aNgbrIter][1];
        if (size_t(anX) < myImageRef->SizeX() && size_t(anY) < myImageRef->SizeY()
            && aGroup->Map().Contains(PackXY((uint16_t)anX, (uint16_t)anY)))
        {
          ++aNeighboursNb;
        }
      }

      if (aNeighboursNb > 2)
      {
        isLine = false;
        break;
      }
    }

    if (isLine)
    {

      aNeighboursNb = 0;
      for (size_t aNgbrIter = 0; aNgbrIter < Image_Diff_NbOfNeighborPixels; ++aNgbrIter)
      {
        int anX = UnpackX(aDiffPixel) + Image_Diff_NEIGHBOR_PIXELS[aNgbrIter][0];
        int anY = UnpackY(aDiffPixel) + Image_Diff_NEIGHBOR_PIXELS[aNgbrIter][1];
        if (size_t(anX) < myImageRef->SizeX() && size_t(anY) < myImageRef->SizeY()
            && !isBlackPixel(*myImageRef, size_t(anY), size_t(anX)))
        {
          ++aNeighboursNb;
        }
      }

      if (aNeighboursNb > 1)
      {
        myLinearGroups.Add(aGroupId);
      }
    }
  }

  int aNbDiffColors = 0;
  aGroupId          = 1;
  for (NCollection_List<occ::handle<TColStd_HPackedMapOfInteger>>::Iterator aGrIter(
         myGroupsOfDiffPixels);
       aGrIter.More();
       aGrIter.Next(), ++aGroupId)
  {
    if (!myLinearGroups.Contains(aGroupId))
    {
      ++aNbDiffColors;
    }
  }

  return aNbDiffColors;
}

void Image_Diff::releaseGroupsOfDiffPixels()
{
  myGroupsOfDiffPixels.Clear();
  myLinearGroups.Clear();
}
