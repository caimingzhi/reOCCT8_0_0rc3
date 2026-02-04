#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_PCharacter.hpp>
#include <Standard_Integer.hpp>
#include <Resource_FormatType.hpp>
class TCollection_ExtendedString;

//! This class provides functions used to convert a non-ASCII C string
//! given in ANSI, EUC, GB or SJIS format, to a
//! Unicode string of extended characters, and vice versa.
class Resource_Unicode
{
public:
  DEFINE_STANDARD_ALLOC

  //! Converts non-ASCII CString <fromstr> in SJIS format
  //! to Unicode ExtendedString <tostr>.
  Standard_EXPORT static void ConvertSJISToUnicode(const char*                 fromstr,
                                                   TCollection_ExtendedString& tostr);

  //! Converts non-ASCII CString <fromstr> in EUC format
  //! to Unicode ExtendedString <tostr>.
  Standard_EXPORT static void ConvertEUCToUnicode(const char*                 fromstr,
                                                  TCollection_ExtendedString& tostr);

  //! Converts non-ASCII CString <fromstr> in GB format
  //! to Unicode ExtendedString <tostr>.
  Standard_EXPORT static void ConvertGBToUnicode(const char*                 fromstr,
                                                 TCollection_ExtendedString& tostr);

  //! Converts non-ASCII CString <fromstr> in GBK format
  //! to Unicode ExtendedString <tostr>.
  Standard_EXPORT static bool ConvertGBKToUnicode(const char*                 fromstr,
                                                  TCollection_ExtendedString& tostr);

  //! Converts non-ASCII CString <fromstr> in Big5 format
  //! to Unicode ExtendedString <tostr>.
  Standard_EXPORT static bool ConvertBig5ToUnicode(const char*                 fromstr,
                                                   TCollection_ExtendedString& tostr);

  //! Converts Unicode ExtendedString <fromstr> to non-ASCII
  //! CString <tostr> in SJIS format, limited to <maxsize>
  //! characters. To translate the whole <fromstr>, use more
  //! than twice the length of <fromstr>. Returns true if
  //! <maxsize> has not been reached before end of conversion.
  Standard_EXPORT static bool ConvertUnicodeToSJIS(const TCollection_ExtendedString& fromstr,
                                                   Standard_PCharacter&              tostr,
                                                   const int                         maxsize);

  //! Converts Unicode ExtendedString <fromstr> to non-ASCII
  //! CString <tostr> in EUC format, limited to <maxsize>
  //! characters. To translate the whole <fromstr>, use more
  //! than twice the length of <fromstr>. Returns true if
  //! <maxsize> has not been reached before end of conversion.
  Standard_EXPORT static bool ConvertUnicodeToEUC(const TCollection_ExtendedString& fromstr,
                                                  Standard_PCharacter&              tostr,
                                                  const int                         maxsize);

  //! Converts Unicode ExtendedString <fromstr> to non-ASCII
  //! CString <tostr> in GB format, limited to <maxsize>
  //! characters. To translate the whole <fromstr>, use more
  //! than twice the length of <fromstr>. Returns true if
  //! <maxsize> has not been reached before end of conversion.
  Standard_EXPORT static bool ConvertUnicodeToGB(const TCollection_ExtendedString& fromstr,
                                                 Standard_PCharacter&              tostr,
                                                 const int                         maxsize);

  //! Converts Unicode ExtendedString <fromstr> to non-ASCII
  //! CString <tostr> in ANSI format, limited to <maxsize>
  //! characters. To translate the whole <fromstr>, use more
  //! than twice the length of <fromstr>. Returns true if
  //! <maxsize> has not been reached before end of conversion.
  Standard_EXPORT static bool ConvertUnicodeToANSI(const TCollection_ExtendedString& fromstr,
                                                   Standard_PCharacter&              tostr,
                                                   const int                         maxsize);

  //! Defines the current conversion format as typecode.
  //! This conversion format will then be used by the
  //! functions ConvertFormatToUnicode and
  //! ConvertUnicodeToFormat to convert the strings.
  Standard_EXPORT static void SetFormat(const Resource_FormatType typecode);

  //! Returns the current conversion format (either
  //! ANSI, EUC, GB or SJIS).
  //! The current converting format must be defined in
  //! advance with the SetFormat function.
  Standard_EXPORT static Resource_FormatType GetFormat();

  //! Reads converting format from resource "FormatType"
  //! in Resource Manager "CharSet"
  Standard_EXPORT static void ReadFormat();

  //! Converts the non-ASCII C string (as specified by GetFormat()) to the Unicode string of
  //! extended characters.
  static void ConvertFormatToUnicode(const char* theFromStr, TCollection_ExtendedString& theToStr)
  {
    return ConvertFormatToUnicode(Resource_Unicode::GetFormat(), theFromStr, theToStr);
  }

  //! Converts the non-ASCII C string in specified format to the Unicode string of extended
  //! characters.
  //! @param[in] theFormat   source encoding
  //! @param[in] theFromStr  text to convert
  //! @param[out] theToStr   destination string
  Standard_EXPORT static void ConvertFormatToUnicode(const Resource_FormatType   theFormat,
                                                     const char*                 theFromStr,
                                                     TCollection_ExtendedString& theToStr);

  //! Converts the Unicode string of extended characters to the non-ASCII string according to
  //! specified format. You need more than twice the length of the source string to complete the
  //! conversion. The function returns true if conversion is complete, i.e. the maximum number of
  //! characters is not reached before the end of conversion.
  //! @param[in] theFormat   destination encoding
  //! @param[in] theFromStr  text to convert
  //! @param[out] theToStr   destination buffer
  //! @param[in] theMaxSize  destination buffer length
  Standard_EXPORT static bool ConvertUnicodeToFormat(const Resource_FormatType         theFormat,
                                                     const TCollection_ExtendedString& theFromStr,
                                                     Standard_PCharacter&              theToStr,
                                                     const int                         theMaxSize);

  //! Converts the Unicode string of extended characters to the non-ASCII string according to the
  //! format returned by the function GetFormat.
  //! @param[in] theFromStr  text to convert
  //! @param[out] theToStr   destination buffer
  //! @param[in] theMaxSize  destination buffer length
  static bool ConvertUnicodeToFormat(const TCollection_ExtendedString& theFromStr,
                                     Standard_PCharacter&              theToStr,
                                     const int                         theMaxSize)
  {
    return ConvertUnicodeToFormat(Resource_Unicode::GetFormat(), theFromStr, theToStr, theMaxSize);
  }
};

