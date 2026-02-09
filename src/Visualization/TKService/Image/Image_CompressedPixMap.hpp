#pragma once

#include <Image_Format.hpp>
#include <Image_CompressedFormat.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Buffer.hpp>
#include <Standard_Type.hpp>

class Image_CompressedPixMap : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Image_CompressedPixMap, Standard_Transient)
public:
  Image_Format BaseFormat() const { return myBaseFormat; }

  void SetBaseFormat(Image_Format theFormat) { myBaseFormat = theFormat; }

  Image_CompressedFormat CompressedFormat() const { return myFormat; }

  void SetCompressedFormat(Image_CompressedFormat theFormat) { myFormat = theFormat; }

  const occ::handle<NCollection_Buffer>& FaceData() const { return myFaceData; }

  void SetFaceData(const occ::handle<NCollection_Buffer>& theBuffer) { myFaceData = theBuffer; }

  const NCollection_Array1<int>& MipMaps() const { return myMipMaps; }

  NCollection_Array1<int>& ChangeMipMaps() { return myMipMaps; }

  bool IsCompleteMipMapSet() const { return myIsCompleteMips; }

  void SetCompleteMipMapSet(bool theIsComplete) { myIsCompleteMips = theIsComplete; }

  size_t FaceBytes() const { return myFaceBytes; }

  void SetFaceBytes(size_t theSize) { myFaceBytes = theSize; }

  int SizeX() const { return mySizeX; }

  int SizeY() const { return mySizeY; }

  void SetSize(int theSizeX, int theSizeY)
  {
    mySizeX = theSizeX;
    mySizeY = theSizeY;
  }

  bool IsTopDown() const { return true; }

  int NbFaces() const { return myNbFaces; }

  void SetNbFaces(int theSize) { myNbFaces = theSize; }

public:
  Image_CompressedPixMap()
      : myFaceBytes(0),
        myNbFaces(0),
        mySizeX(0),
        mySizeY(0),
        myBaseFormat(Image_Format_UNKNOWN),
        myFormat(Image_CompressedFormat_UNKNOWN),
        myIsCompleteMips(false)
  {
  }

protected:
  NCollection_Array1<int>         myMipMaps;
  occ::handle<NCollection_Buffer> myFaceData;
  size_t                          myFaceBytes;
  int                             myNbFaces;
  int                             mySizeX;
  int                             mySizeY;
  Image_Format                    myBaseFormat;
  Image_CompressedFormat          myFormat;

  bool myIsCompleteMips;
};
