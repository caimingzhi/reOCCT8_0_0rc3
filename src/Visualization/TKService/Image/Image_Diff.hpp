#pragma once

#include <Image_PixMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <TColStd_HPackedMapOfInteger.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Vector.hpp>

class Image_Diff : public Standard_Transient
{

public:
  Standard_EXPORT Image_Diff();

  Standard_EXPORT ~Image_Diff() override;

  Standard_EXPORT bool Init(const occ::handle<Image_PixMap>& theImageRef,
                            const occ::handle<Image_PixMap>& theImageNew,
                            const bool                       theToBlackWhite = false);

  Standard_EXPORT bool Init(const TCollection_AsciiString& theImgPathRef,
                            const TCollection_AsciiString& theImgPathNew,
                            const bool                     theToBlackWhite = false);

  void SetColorTolerance(const double theTolerance) { myColorTolerance = theTolerance; }

  double ColorTolerance() const { return myColorTolerance; }

  void SetBorderFilterOn(const bool theToIgnore) { myIsBorderFilterOn = theToIgnore; }

  bool IsBorderFilterOn() const { return myIsBorderFilterOn; }

  Standard_EXPORT int Compare();

  Standard_EXPORT bool SaveDiffImage(Image_PixMap& theDiffImage) const;

  Standard_EXPORT bool SaveDiffImage(const TCollection_AsciiString& theDiffPath) const;

protected:
  Standard_EXPORT int ignoreBorderEffect();

  Standard_EXPORT void releaseGroupsOfDiffPixels();

protected:
  static int PackXY(uint16_t theX, uint16_t theY)
  {
    return int((unsigned int)theY | ((unsigned int)theX << 16));
  }

  static uint16_t UnpackX(int theXY)
  {
    return (uint16_t)(((unsigned int)theXY & 0xffff0000) >> 16);
  }

  static uint16_t UnpackY(int theXY) { return (uint16_t)((unsigned int)theXY & 0xffff); }

protected:
  occ::handle<Image_PixMap> myImageRef;
  occ::handle<Image_PixMap> myImageNew;

  double myColorTolerance;

  bool myIsBorderFilterOn;

  NCollection_Vector<int>                                    myDiffPixels;
  TColStd_PackedMapOfInteger                                 myLinearGroups;
  NCollection_List<occ::handle<TColStd_HPackedMapOfInteger>> myGroupsOfDiffPixels;

public:
  DEFINE_STANDARD_RTTIEXT(Image_Diff, Standard_Transient)
};
