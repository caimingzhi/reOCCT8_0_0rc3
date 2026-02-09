#pragma once

#include <Image_CompressedFormat.hpp>
#include <Image_PixMapData.hpp>
#include <Standard_Transient.hpp>
#include <Quantity_ColorRGBA.hpp>

class Image_PixMap : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Image_PixMap, Standard_Transient)
public:
  static inline bool IsBigEndianHost()
  {
    union
    {
      int  myInt;
      char myChar[sizeof(int)];
    } aUnion;

    aUnion.myInt = 1;
    return !aUnion.myChar[0];
  }

  Standard_EXPORT static size_t SizePixelBytes(const Image_Format thePixelFormat);

  Standard_EXPORT static bool SwapRgbaBgra(Image_PixMap& theImage);

  Standard_EXPORT static void ToBlackWhite(Image_PixMap& theImage);

  Standard_EXPORT static bool FlipY(Image_PixMap& theImage);

  Standard_EXPORT static const occ::handle<NCollection_BaseAllocator>& DefaultAllocator();

  Standard_EXPORT static const char* ImageFormatToString(Image_Format theFormat);

  Standard_EXPORT static const char* ImageFormatToString(Image_CompressedFormat theFormat);

  Standard_EXPORT static Quantity_ColorRGBA ColorFromRawPixel(const uint8_t*     theRawValue,
                                                              const Image_Format theFormat,
                                                              const bool theToLinearize = false);

  Standard_EXPORT static void ColorToRawPixel(uint8_t*                  theRawValue,
                                              const Image_Format        theFormat,
                                              const Quantity_ColorRGBA& theColor,
                                              const bool                theToDeLinearize = false);

public:
  Image_Format Format() const { return myImgFormat; }

  Standard_EXPORT void SetFormat(const Image_Format thePixelFormat);

  size_t Width() const { return myData.SizeX; }

  size_t Height() const { return myData.SizeY; }

  size_t Depth() const { return myData.SizeZ; }

  size_t SizeX() const { return myData.SizeX; }

  size_t SizeY() const { return myData.SizeY; }

  size_t SizeZ() const { return myData.SizeZ; }

  NCollection_Vec3<size_t> SizeXYZ() const
  {
    return NCollection_Vec3<size_t>(myData.SizeX, myData.SizeY, myData.SizeZ);
  }

  double Ratio() const { return (SizeY() > 0) ? (double(SizeX()) / double(SizeY())) : 1.0; }

  bool IsEmpty() const { return myData.IsEmpty(); }

  Standard_EXPORT Image_PixMap();

  Standard_EXPORT ~Image_PixMap() override;

  Quantity_ColorRGBA PixelColor(int theX, int theY, bool theToLinearize = false) const
  {
    if (IsEmpty() || theX < 0 || (size_t)theX >= SizeX() || theY < 0 || (size_t)theY >= SizeY())
    {
      return Quantity_ColorRGBA(0.0f, 0.0f, 0.0f, 0.0f);
    }

    const uint8_t* aRawPixel = RawValueXY(theX, theY);
    return ColorFromRawPixel(aRawPixel, myImgFormat, theToLinearize);
  }

  void SetPixelColor(const int             theX,
                     const int             theY,
                     const Quantity_Color& theColor,
                     const bool            theToDeLinearize = false)
  {
    SetPixelColor(theX, theY, Quantity_ColorRGBA(theColor, 1.0f), theToDeLinearize);
  }

  void SetPixelColor(const int                 theX,
                     const int                 theY,
                     const Quantity_ColorRGBA& theColor,
                     const bool                theToDeLinearize = false)
  {
    if (IsEmpty() || theX < 0 || size_t(theX) >= SizeX() || theY < 0 || size_t(theY) >= SizeY())
    {
      return;
    }

    uint8_t* aRawPixel = ChangeRawValueXY(theX, theY);
    ColorToRawPixel(aRawPixel, myImgFormat, theColor, theToDeLinearize);
  }

  Standard_EXPORT virtual bool InitWrapper(Image_Format thePixelFormat,
                                           uint8_t*     theDataPtr,
                                           const size_t theSizeX,
                                           const size_t theSizeY,
                                           const size_t theSizeRowBytes = 0);

  Standard_EXPORT virtual bool InitTrash(Image_Format thePixelFormat,
                                         const size_t theSizeX,
                                         const size_t theSizeY,
                                         const size_t theSizeRowBytes = 0);

  Standard_EXPORT virtual bool InitCopy(const Image_PixMap& theCopy);

  bool InitZero(Image_Format  thePixelFormat,
                const size_t  theSizeX,
                const size_t  theSizeY,
                const size_t  theSizeRowBytes = 0,
                const uint8_t theValue        = 0)
  {
    return InitZero3D(thePixelFormat,
                      NCollection_Vec3<size_t>(theSizeX, theSizeY, 1),
                      theSizeRowBytes,
                      theValue);
  }

  Standard_EXPORT virtual void Clear();

public:
  Standard_EXPORT virtual bool InitWrapper3D(Image_Format                    thePixelFormat,
                                             uint8_t*                        theDataPtr,
                                             const NCollection_Vec3<size_t>& theSizeXYZ,
                                             const size_t                    theSizeRowBytes = 0);

  Standard_EXPORT virtual bool InitTrash3D(Image_Format                    thePixelFormat,
                                           const NCollection_Vec3<size_t>& theSizeXYZ,
                                           const size_t                    theSizeRowBytes = 0);

  Standard_EXPORT bool InitZero3D(Image_Format                    thePixelFormat,
                                  const NCollection_Vec3<size_t>& theSizeXYZ,
                                  const size_t                    theSizeRowBytes = 0,
                                  const uint8_t                   theValue        = 0);

public:
  bool IsTopDown() const { return myData.TopToDown == 1; }

  void SetTopDown(const bool theIsTopDown) { myData.SetTopDown(theIsTopDown); }

  size_t TopDownInc() const { return myData.TopToDown; }

  const uint8_t* Data() const { return myData.Data(); }

  uint8_t* ChangeData() { return myData.ChangeData(); }

  const uint8_t* Row(size_t theRow) const { return myData.Row(theRow); }

  uint8_t* ChangeRow(size_t theRow) { return myData.ChangeRow(theRow); }

  const uint8_t* Slice(size_t theSlice) const { return myData.Slice(theSlice); }

  uint8_t* ChangeSlice(size_t theSlice) { return myData.ChangeSlice(theSlice); }

  const uint8_t* SliceRow(size_t theSlice, size_t theRow) const
  {
    return myData.SliceRow(theSlice, theRow);
  }

  uint8_t* ChangeSliceRow(size_t theSlice, size_t theRow)
  {
    return myData.ChangeSliceRow(theSlice, theRow);
  }

  size_t SizePixelBytes() const { return myData.SizeBPP; }

  size_t SizeRowBytes() const { return myData.SizeRowBytes; }

  size_t RowExtraBytes() const { return SizeRowBytes() - SizeX() * SizePixelBytes(); }

  size_t MaxRowAligmentBytes() const { return myData.MaxRowAligmentBytes(); }

  size_t SizeSliceBytes() const { return myData.SizeSliceBytes; }

  size_t SizeBytes() const { return myData.Size(); }

public:
  template <typename ColorType_t>
  const ColorType_t& Value(size_t theRow, size_t theCol) const
  {
    return *reinterpret_cast<const ColorType_t*>(myData.Value(theRow, theCol));
  }

  template <typename ColorType_t>
  ColorType_t& ChangeValue(size_t theRow, size_t theCol)
  {
    return *reinterpret_cast<ColorType_t*>(myData.ChangeValue(theRow, theCol));
  }

  const uint8_t* RawValue(size_t theRow, size_t theCol) const
  {
    return myData.Value(theRow, theCol);
  }

  uint8_t* ChangeRawValue(size_t theRow, size_t theCol)
  {
    return myData.ChangeValue(theRow, theCol);
  }

  template <typename ColorType_t>
  const ColorType_t& ValueXY(size_t theX, size_t theY) const
  {
    return *reinterpret_cast<const ColorType_t*>(myData.ValueXY(theX, theY));
  }

  template <typename ColorType_t>
  ColorType_t& ChangeValueXY(size_t theX, size_t theY)
  {
    return *reinterpret_cast<ColorType_t*>(myData.ChangeValueXY(theX, theY));
  }

  const uint8_t* RawValueXY(size_t theX, size_t theY) const { return myData.ValueXY(theX, theY); }

  uint8_t* ChangeRawValueXY(size_t theX, size_t theY) { return myData.ChangeValueXY(theX, theY); }

public:
  template <typename ColorType_t>
  const ColorType_t& ValueXYZ(size_t theX, size_t theY, size_t theZ) const
  {
    return *reinterpret_cast<const ColorType_t*>(myData.ValueXYZ(theX, theY, theZ));
  }

  template <typename ColorType_t>
  ColorType_t& ChangeValueXYZ(size_t theX, size_t theY, size_t theZ)
  {
    return *reinterpret_cast<ColorType_t*>(myData.ChangeValueXYZ(theX, theY, theZ));
  }

  const uint8_t* RawValueXYZ(size_t theX, size_t theY, size_t theZ) const
  {
    return myData.ValueXYZ(theX, theY, theZ);
  }

  uint8_t* ChangeRawValueXYZ(size_t theX, size_t theY, size_t theZ)
  {
    return myData.ChangeValueXYZ(theX, theY, theZ);
  }

public:
  static float ConvertFromHalfFloat(const uint16_t theHalf)
  {
    union FloatUint32
    {
      float    Float32;
      uint32_t UInt32;
    };

    const uint32_t e = (theHalf & 0x7C00) >> 10;
    const uint32_t m = (theHalf & 0x03FF) << 13;
    FloatUint32    mf, aRes;
    mf.Float32 = (float)m;

    const uint32_t v = mf.UInt32 >> 23;
    aRes.UInt32      = (theHalf & 0x8000) << 16 | (e != 0) * ((e + 112) << 23 | m)
                  | ((e == 0) & (m != 0)) * ((v - 37) << 23 | ((m << (150 - v)) & 0x007FE000));

    return aRes.Float32;
  }

  static uint16_t ConvertToHalfFloat(const float theFloat)
  {
    union FloatUint32
    {
      float    Float32;
      uint32_t UInt32;
    };

    FloatUint32 anInput;
    anInput.Float32 = theFloat;

    const uint32_t b = anInput.UInt32 + 0x00001000;
    const uint32_t e = (b & 0x7F800000) >> 23;
    const uint32_t m = b & 0x007FFFFF;
    return (uint16_t)((b & 0x80000000) >> 16 | (e > 112) * ((((e - 112) << 10) & 0x7C00) | m >> 13)
                      | ((e < 113) & (e > 101)) * ((((0x007FF000 + m) >> (125 - e)) + 1) >> 1)
                      | (e > 143) * 0x7FFF);
  }

protected:
  Image_PixMapData myData;
  Image_Format     myImgFormat;

private:
  Image_PixMap(const Image_PixMap&)            = delete;
  Image_PixMap& operator=(const Image_PixMap&) = delete;
};
