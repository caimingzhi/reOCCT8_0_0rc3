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

class Resource_Unicode
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void ConvertSJISToUnicode(const char*                 fromstr,
                                                   TCollection_ExtendedString& tostr);

  Standard_EXPORT static void ConvertEUCToUnicode(const char*                 fromstr,
                                                  TCollection_ExtendedString& tostr);

  Standard_EXPORT static void ConvertGBToUnicode(const char*                 fromstr,
                                                 TCollection_ExtendedString& tostr);

  Standard_EXPORT static bool ConvertGBKToUnicode(const char*                 fromstr,
                                                  TCollection_ExtendedString& tostr);

  Standard_EXPORT static bool ConvertBig5ToUnicode(const char*                 fromstr,
                                                   TCollection_ExtendedString& tostr);

  Standard_EXPORT static bool ConvertUnicodeToSJIS(const TCollection_ExtendedString& fromstr,
                                                   Standard_PCharacter&              tostr,
                                                   const int                         maxsize);

  Standard_EXPORT static bool ConvertUnicodeToEUC(const TCollection_ExtendedString& fromstr,
                                                  Standard_PCharacter&              tostr,
                                                  const int                         maxsize);

  Standard_EXPORT static bool ConvertUnicodeToGB(const TCollection_ExtendedString& fromstr,
                                                 Standard_PCharacter&              tostr,
                                                 const int                         maxsize);

  Standard_EXPORT static bool ConvertUnicodeToANSI(const TCollection_ExtendedString& fromstr,
                                                   Standard_PCharacter&              tostr,
                                                   const int                         maxsize);

  Standard_EXPORT static void SetFormat(const Resource_FormatType typecode);

  Standard_EXPORT static Resource_FormatType GetFormat();

  Standard_EXPORT static void ReadFormat();

  static void ConvertFormatToUnicode(const char* theFromStr, TCollection_ExtendedString& theToStr)
  {
    return ConvertFormatToUnicode(Resource_Unicode::GetFormat(), theFromStr, theToStr);
  }

  Standard_EXPORT static void ConvertFormatToUnicode(const Resource_FormatType   theFormat,
                                                     const char*                 theFromStr,
                                                     TCollection_ExtendedString& theToStr);

  Standard_EXPORT static bool ConvertUnicodeToFormat(const Resource_FormatType         theFormat,
                                                     const TCollection_ExtendedString& theFromStr,
                                                     Standard_PCharacter&              theToStr,
                                                     const int                         theMaxSize);

  static bool ConvertUnicodeToFormat(const TCollection_ExtendedString& theFromStr,
                                     Standard_PCharacter&              theToStr,
                                     const int                         theMaxSize)
  {
    return ConvertUnicodeToFormat(Resource_Unicode::GetFormat(), theFromStr, theToStr, theMaxSize);
  }
};
