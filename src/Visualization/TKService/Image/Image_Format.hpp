#pragma once

enum Image_Format
{
  Image_Format_UNKNOWN = 0,
  Image_Format_Gray    = 1,
  Image_Format_Alpha,
  Image_Format_RGB,
  Image_Format_BGR,
  Image_Format_RGB32,

  Image_Format_BGR32,
  Image_Format_RGBA,
  Image_Format_BGRA,
  Image_Format_GrayF,
  Image_Format_AlphaF,
  Image_Format_RGF,
  Image_Format_RGBF,
  Image_Format_BGRF,
  Image_Format_RGBAF,
  Image_Format_BGRAF,
  Image_Format_GrayF_half,
  Image_Format_RGF_half,
  Image_Format_RGBAF_half,
  Image_Format_Gray16,
};

enum
{
  Image_Format_NB = Image_Format_Gray16 + 1
};
