

#include <Image_SupportedFormats.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Image_SupportedFormats, Standard_Transient)

Image_SupportedFormats::Image_SupportedFormats()
    : myFormats(Image_Format_UNKNOWN, Image_CompressedFormat_NB - 1),
      myHasCompressed(false)
{
  myFormats.Init(false);
}
