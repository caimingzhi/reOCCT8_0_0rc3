#pragma once

#include <Image_CompressedFormat.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Type.hpp>

class Image_SupportedFormats : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Image_SupportedFormats, Standard_Transient)
public:
  Standard_EXPORT Image_SupportedFormats();

  bool IsSupported(Image_Format theFormat) const { return myFormats.Value(theFormat); }

  void Add(Image_Format theFormat) { myFormats.SetValue(theFormat, true); }

  bool HasCompressed() const { return myHasCompressed; }

  bool IsSupported(Image_CompressedFormat theFormat) const { return myFormats.Value(theFormat); }

  void Add(Image_CompressedFormat theFormat)
  {
    myFormats.SetValue(theFormat, true);
    myHasCompressed = true;
  }

  void Clear()
  {
    myFormats.Init(false);
    myHasCompressed = false;
  }

protected:
  NCollection_Array1<bool> myFormats;

  bool myHasCompressed;
};
