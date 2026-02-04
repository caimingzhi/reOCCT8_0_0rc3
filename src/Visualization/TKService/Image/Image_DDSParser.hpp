#pragma once


#include <Image_CompressedPixMap.hpp>
#include <NCollection_Buffer.hpp>

class Image_SupportedFormats;

//! Auxiliary tool for parsing DDS file structure (without decoding).
class Image_DDSParser
{
public:
  //! Load the face from DDS file.
  //! @param[in] theSupported  list of supported image formats
  //! @param[in] theFile       file path
  //! @param[in] theFaceIndex  face index, within [0, Image_CompressedPixMap::NbFaces()) range;
  //!                          use -1 to skip reading the face data
  //! @param[in] theFileOffset  offset to the DDS data
  //! @return loaded face or NULL if file cannot be read or not valid DDS file
  Standard_EXPORT static occ::handle<Image_CompressedPixMap> Load(
    const occ::handle<Image_SupportedFormats>& theSupported,
    const TCollection_AsciiString&             theFile,
    const int                                  theFaceIndex,
    const int64_t                              theFileOffset = 0);

  //! Load the face from DDS file.
  //! @param[in] theSupported  list of supported image formats
  //! @param[in] theBuffer     pre-loaded file data, should be at least of 128 bytes long defining
  //! DDS header.
  //! @param[in] theFaceIndex  face index, within [0, Image_CompressedPixMap::NbFaces()) range;
  //!                          use -1 to skip reading the face data
  //! @return loaded face or NULL if file cannot be read or not valid DDS file
  Standard_EXPORT static occ::handle<Image_CompressedPixMap> Load(
    const occ::handle<Image_SupportedFormats>& theSupported,
    const occ::handle<NCollection_Buffer>&     theBuffer,
    const int                                  theFaceIndex);

private:
  struct DDSPixelFormat;
  struct DDSFileHeader;

private:
  //! Parse DDS header.
  static occ::handle<Image_CompressedPixMap> parseHeader(const DDSFileHeader& theHeader);
};

