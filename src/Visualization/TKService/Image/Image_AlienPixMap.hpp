#pragma once

#include <Image_PixMap.hpp>

class TCollection_AsciiString;
struct IWICPalette;
struct FIBITMAP;

class Image_AlienPixMap : public Image_PixMap
{
  DEFINE_STANDARD_RTTIEXT(Image_AlienPixMap, Image_PixMap)
public:
  Standard_EXPORT static bool IsTopDownDefault();

public:
  Standard_EXPORT Image_AlienPixMap();

  Standard_EXPORT ~Image_AlienPixMap() override;

  bool Load(const TCollection_AsciiString& theFileName) { return Load(nullptr, 0, theFileName); }

  Standard_EXPORT bool Load(std::istream& theStream, const TCollection_AsciiString& theFileName);

  Standard_EXPORT bool Load(const uint8_t*                 theData,
                            const size_t                   theLength,
                            const TCollection_AsciiString& theFileName);

  bool Save(const TCollection_AsciiString& theFileName) { return Save(nullptr, 0, theFileName); }

  Standard_EXPORT bool Save(std::ostream& theStream, const TCollection_AsciiString& theExtension);

  Standard_EXPORT bool Save(uint8_t*                       theBuffer,
                            const size_t                   theLength,
                            const TCollection_AsciiString& theFileName);

  Standard_EXPORT bool InitTrash(Image_Format thePixelFormat,
                                 const size_t theSizeX,
                                 const size_t theSizeY,
                                 const size_t theSizeRowBytes = 0) override;

  Standard_EXPORT bool InitCopy(const Image_PixMap& theCopy) override;

  Standard_EXPORT void Clear() override;

  Standard_EXPORT bool AdjustGamma(const double theGammaCorr);

#if !defined(HAVE_FREEIMAGE) && defined(_WIN32)

  IWICPalette* GetPalette() const { return myPalette; }
#endif

private:
  Image_AlienPixMap(const Image_AlienPixMap&)            = delete;
  Image_AlienPixMap& operator=(const Image_AlienPixMap&) = delete;

  Standard_EXPORT bool InitWrapper(Image_Format thePixelFormat,
                                   uint8_t*     theDataPtr,
                                   const size_t theSizeX,
                                   const size_t theSizeY,
                                   const size_t theSizeRowBytes) override;

  Standard_EXPORT bool savePPM(const TCollection_AsciiString& theFileName) const;

  FIBITMAP* getImageToDump(const int theFormat);

private:
  FIBITMAP*                     myLibImage;
  [[maybe_unused]] IWICPalette* myPalette;
};
