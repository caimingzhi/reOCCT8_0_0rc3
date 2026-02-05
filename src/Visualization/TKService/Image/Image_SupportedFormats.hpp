#pragma once

#include <Image_CompressedFormat.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Type.hpp>

//! Structure holding information about supported texture formats.
class Image_SupportedFormats : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Image_SupportedFormats, Standard_Transient)
public:
  //! Empty constructor.
  Standard_EXPORT Image_SupportedFormats();

  //! Return TRUE if image format is supported.
  bool IsSupported(Image_Format theFormat) const { return myFormats.Value(theFormat); }

  //! Set if image format is supported or not.
  void Add(Image_Format theFormat) { myFormats.SetValue(theFormat, true); }

  //! Return TRUE if there are compressed image formats supported.
  bool HasCompressed() const { return myHasCompressed; }

  //! Return TRUE if compressed image format is supported.
  bool IsSupported(Image_CompressedFormat theFormat) const { return myFormats.Value(theFormat); }

  //! Set if compressed image format is supported or not.
  void Add(Image_CompressedFormat theFormat)
  {
    myFormats.SetValue(theFormat, true);
    myHasCompressed = true;
  }

  //! Reset flags.
  void Clear()
  {
    myFormats.Init(false);
    myHasCompressed = false;
  }

protected:
  NCollection_Array1<bool> myFormats; //!< list of supported formats
  // clang-format off
  bool   myHasCompressed; //!< flag indicating that some compressed image formats are supported
  // clang-format on
};
