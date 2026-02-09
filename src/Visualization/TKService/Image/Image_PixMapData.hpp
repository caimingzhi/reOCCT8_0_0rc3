#pragma once

#include <Standard.hpp>

struct Image_ColorRGB
{

  typedef uint8_t ComponentType_t;

  static int Length() { return 3; }

public:
  uint8_t r() const { return v[0]; }

  uint8_t g() const { return v[1]; }

  uint8_t b() const { return v[2]; }

  uint8_t& r() { return v[0]; }

  uint8_t& g() { return v[1]; }

  uint8_t& b() { return v[2]; }

public:
  uint8_t v[3];
};

struct Image_ColorRGB32
{

  typedef uint8_t ComponentType_t;

  static int Length() { return 3; }

  uint8_t r() const { return v[0]; }

  uint8_t g() const { return v[1]; }

  uint8_t b() const { return v[2]; }

  uint8_t a_() const { return v[3]; }

  uint8_t& r() { return v[0]; }

  uint8_t& g() { return v[1]; }

  uint8_t& b() { return v[2]; }

  uint8_t& a_() { return v[3]; }

public:
  uint8_t v[4];
};

struct Image_ColorRGBA
{

  typedef uint8_t ComponentType_t;

  static int Length() { return 4; }

  uint8_t r() const { return v[0]; }

  uint8_t g() const { return v[1]; }

  uint8_t b() const { return v[2]; }

  uint8_t a() const { return v[3]; }

  uint8_t& r() { return v[0]; }

  uint8_t& g() { return v[1]; }

  uint8_t& b() { return v[2]; }

  uint8_t& a() { return v[3]; }

public:
  uint8_t v[4];
};

struct Image_ColorBGR
{

  typedef uint8_t ComponentType_t;

  static int Length() { return 3; }

  uint8_t r() const { return v[2]; }

  uint8_t g() const { return v[1]; }

  uint8_t b() const { return v[0]; }

  uint8_t& r() { return v[2]; }

  uint8_t& g() { return v[1]; }

  uint8_t& b() { return v[0]; }

public:
  uint8_t v[3];
};

struct Image_ColorBGR32
{

  typedef uint8_t ComponentType_t;

  static int Length() { return 3; }

  uint8_t r() const { return v[2]; }

  uint8_t g() const { return v[1]; }

  uint8_t b() const { return v[0]; }

  uint8_t a_() const { return v[3]; }

  uint8_t& r() { return v[2]; }

  uint8_t& g() { return v[1]; }

  uint8_t& b() { return v[0]; }

  uint8_t& a_() { return v[3]; }

public:
  uint8_t v[4];
};

struct Image_ColorBGRA
{

  typedef uint8_t ComponentType_t;

  static int Length() { return 4; }

  uint8_t r() const { return v[2]; }

  uint8_t g() const { return v[1]; }

  uint8_t b() const { return v[0]; }

  uint8_t a() const { return v[3]; }

  uint8_t& r() { return v[2]; }

  uint8_t& g() { return v[1]; }

  uint8_t& b() { return v[0]; }

  uint8_t& a() { return v[3]; }

public:
  uint8_t v[4];
};

struct Image_ColorRGF
{

  typedef float ComponentType_t;

  static int Length() { return 2; }

  float r() const { return v[0]; }

  float g() const { return v[1]; }

  float& r() { return v[0]; }

  float& g() { return v[1]; }

public:
  float v[2];
};

struct Image_ColorRGBF
{

  typedef float ComponentType_t;

  static int Length() { return 3; }

  float r() const { return v[0]; }

  float g() const { return v[1]; }

  float b() const { return v[2]; }

  float& r() { return v[0]; }

  float& g() { return v[1]; }

  float& b() { return v[2]; }

public:
  float v[3];
};

struct Image_ColorBGRF
{

  typedef float ComponentType_t;

  static int Length() { return 3; }

  float r() const { return v[2]; }

  float g() const { return v[1]; }

  float b() const { return v[0]; }

  float& r() { return v[2]; }

  float& g() { return v[1]; }

  float& b() { return v[0]; }

public:
  float v[3];
};

struct Image_ColorRGBAF
{

  typedef float ComponentType_t;

  static int Length() { return 4; }

  float r() const { return v[0]; }

  float g() const { return v[1]; }

  float b() const { return v[2]; }

  float a() const { return v[3]; }

  float& r() { return v[0]; }

  float& g() { return v[1]; }

  float& b() { return v[2]; }

  float& a() { return v[3]; }

public:
  float v[4];
};

struct Image_ColorBGRAF
{

  typedef float ComponentType_t;

  static int Length() { return 4; }

  float r() const { return v[2]; }

  float g() const { return v[1]; }

  float b() const { return v[0]; }

  float a() const { return v[3]; }

  float& r() { return v[2]; }

  float& g() { return v[1]; }

  float& b() { return v[0]; }

  float& a() { return v[3]; }

public:
  float v[4];
};

#include <NCollection_Buffer.hpp>
#include <NCollection_Vec3.hpp>

class Image_PixMapData : public NCollection_Buffer
{
public:
  Image_PixMapData()
      : NCollection_Buffer(occ::handle<NCollection_BaseAllocator>()),
        myTopRowPtr(nullptr),
        SizeBPP(0),
        SizeX(0),
        SizeY(0),
        SizeZ(0),
        SizeRowBytes(0),
        SizeSliceBytes(0),
        TopToDown(size_t(-1))
  {
  }

  bool Init(const occ::handle<NCollection_BaseAllocator>& theAlloc,
            const size_t                                  theSizeBPP,
            const size_t                                  theSizeX,
            const size_t                                  theSizeY,
            const size_t                                  theSizeRowBytes,
            uint8_t*                                      theDataPtr)
  {
    return Init(theAlloc,
                theSizeBPP,
                NCollection_Vec3<size_t>(theSizeX, theSizeY, 1),
                theSizeRowBytes,
                theDataPtr);
  }

  bool Init(const occ::handle<NCollection_BaseAllocator>& theAlloc,
            const size_t                                  theSizeBPP,
            const NCollection_Vec3<size_t>&               theSizeXYZ,
            const size_t                                  theSizeRowBytes,
            uint8_t*                                      theDataPtr)
  {
    SetAllocator(theAlloc);

    myData         = theDataPtr;
    myTopRowPtr    = nullptr;
    SizeBPP        = theSizeBPP;
    SizeX          = theSizeXYZ.x();
    SizeY          = theSizeXYZ.y();
    SizeZ          = theSizeXYZ.z();
    SizeRowBytes   = theSizeRowBytes != 0 ? theSizeRowBytes : (SizeX * theSizeBPP);
    SizeSliceBytes = SizeRowBytes * SizeY;
    mySize         = SizeSliceBytes * SizeZ;
    if (myData == nullptr)
    {
      Allocate(mySize);
    }
    SetTopDown(TopToDown == 1);
    return !IsEmpty();
  }

  void ZeroData()
  {
    if (myData != nullptr)
    {
      memset(myData, 0, mySize);
    }
  }

  const uint8_t* Row(const size_t theRow) const
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theRow * TopToDown);
  }

  uint8_t* ChangeRow(const size_t theRow)
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theRow * TopToDown);
  }

  const uint8_t* Value(const size_t theRow, const size_t theCol) const
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theRow * TopToDown) + SizeBPP * theCol;
  }

  uint8_t* ChangeValue(size_t theRow, size_t theCol)
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theRow * TopToDown) + SizeBPP * theCol;
  }

  const uint8_t* ValueXY(size_t theX, size_t theY) const
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theY * TopToDown) + SizeBPP * theX;
  }

  uint8_t* ChangeValueXY(size_t theX, size_t theY)
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theY * TopToDown) + SizeBPP * theX;
  }

public:
  const uint8_t* Slice(size_t theSlice) const
  {
    return myData + ptrdiff_t(SizeSliceBytes * theSlice);
  }

  uint8_t* ChangeSlice(size_t theSlice) { return myData + ptrdiff_t(SizeSliceBytes * theSlice); }

  const uint8_t* SliceRow(size_t theSlice, size_t theRow) const
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theRow * TopToDown)
           + ptrdiff_t(SizeSliceBytes * theSlice);
  }

  uint8_t* ChangeSliceRow(size_t theSlice, size_t theRow)
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theRow * TopToDown)
           + ptrdiff_t(SizeSliceBytes * theSlice);
  }

  const uint8_t* ValueXYZ(size_t theX, size_t theY, size_t theZ) const
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theY * TopToDown) + SizeBPP * theX
           + ptrdiff_t(SizeSliceBytes * theZ);
  }

  uint8_t* ChangeValueXYZ(size_t theX, size_t theY, size_t theZ)
  {
    return myTopRowPtr + ptrdiff_t(SizeRowBytes * theY * TopToDown) + SizeBPP * theX
           + ptrdiff_t(SizeSliceBytes * theZ);
  }

  size_t MaxRowAligmentBytes() const
  {
    size_t anAlignment = 2;
    for (; anAlignment <= 16; anAlignment <<= 1)
    {
      if ((SizeRowBytes % anAlignment) != 0 || (size_t(myData) % anAlignment) != 0)
      {
        return (anAlignment >> 1);
      }
    }
    return anAlignment;
  }

  void SetTopDown(const bool theIsTopDown)
  {
    TopToDown = (theIsTopDown ? 1 : size_t(-1));
    myTopRowPtr =
      ((TopToDown == 1 || myData == nullptr) ? myData : (myData + SizeRowBytes * (SizeY - 1)));
  }

protected:
  uint8_t* myTopRowPtr;

public:
  size_t SizeBPP;
  size_t SizeX;
  size_t SizeY;
  size_t SizeZ;
  size_t SizeRowBytes;
  size_t SizeSliceBytes;
  size_t TopToDown;

public:
  DEFINE_STANDARD_RTTIEXT(Image_PixMapData, NCollection_Buffer)
};
