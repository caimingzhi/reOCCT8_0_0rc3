#pragma once

#include <Image_CompressedPixMap.hpp>
#include <NCollection_Buffer.hpp>

class Image_SupportedFormats;

class Image_DDSParser
{
public:
  Standard_EXPORT static occ::handle<Image_CompressedPixMap> Load(
    const occ::handle<Image_SupportedFormats>& theSupported,
    const TCollection_AsciiString&             theFile,
    const int                                  theFaceIndex,
    const int64_t                              theFileOffset = 0);

  Standard_EXPORT static occ::handle<Image_CompressedPixMap> Load(
    const occ::handle<Image_SupportedFormats>& theSupported,
    const occ::handle<NCollection_Buffer>&     theBuffer,
    const int                                  theFaceIndex);

private:
  struct DDSPixelFormat;
  struct DDSFileHeader;

private:
  static occ::handle<Image_CompressedPixMap> parseHeader(const DDSFileHeader& theHeader);
};
