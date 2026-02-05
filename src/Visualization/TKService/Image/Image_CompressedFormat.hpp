#pragma once

#include <Image_Format.hpp>

//! List of compressed pixel formats natively supported by various graphics hardware (e.g. for
//! efficient decoding on-the-fly). It is defined as extension of Image_Format.
enum Image_CompressedFormat
{
  Image_CompressedFormat_UNKNOWN       = Image_Format_UNKNOWN,
  Image_CompressedFormat_RGB_S3TC_DXT1 = Image_Format_NB,
  Image_CompressedFormat_RGBA_S3TC_DXT1,
  Image_CompressedFormat_RGBA_S3TC_DXT3,
  Image_CompressedFormat_RGBA_S3TC_DXT5
};

enum
{
  Image_CompressedFormat_NB = Image_CompressedFormat_RGBA_S3TC_DXT5 + 1
};
