#pragma once

#include <cstddef>
#include <ctime>

#include <stdint.h>

#if (defined(_MSC_VER) && (_MSC_VER < 1800))

  #define PRIx64 "I64x"
  #define PRIX64 "I64X"
  #define PRId64 "I64d"
  #define PRIu64 "I64u"
  #define SCNd64 "I64d"
  #define SCNu64 "I64u"
  #ifdef _WIN64
    #define PRIxPTR "I64x"
    #define PRIXPTR "I64X"
    #define PRIdPTR "I64d"
    #define PRIuPTR "I64u"
    #define SCNdPTR "I64d"
    #define SCNuPTR "I64u"
  #else
    #define PRIxPTR "Ix"
    #define PRIXPTR "IX"
    #define PRIdPTR "d"
    #define PRIuPTR "u"
    #define SCNdPTR "d"
    #define SCNuPTR "u"
  #endif
#else

  #ifndef __STDC_FORMAT_MACROS
    #define __STDC_FORMAT_MACROS
  #endif
  #include <inttypes.h>
#endif

#include <Standard_Macro.hpp>

Standard_DEPRECATED("Standard_False is deprecated, use false directly")
inline constexpr bool Standard_False = false;

Standard_DEPRECATED("Standard_True is deprecated, use true directly")
inline constexpr bool Standard_True = true;

Standard_DEPRECATED("Standard_Integer is deprecated, use int directly")
typedef int Standard_Integer;

Standard_DEPRECATED("Standard_UInteger is deprecated, use unsigned int directly")
typedef unsigned int Standard_UInteger;

Standard_DEPRECATED("Standard_Real is deprecated, use double directly")
typedef double Standard_Real;

Standard_DEPRECATED("Standard_Boolean is deprecated, use bool directly")
typedef bool Standard_Boolean;

Standard_DEPRECATED("Standard_ShortReal is deprecated, use float directly")
typedef float Standard_ShortReal;

Standard_DEPRECATED("Standard_Character is deprecated, use char directly")
typedef char Standard_Character;

Standard_DEPRECATED("Standard_Byte is deprecated, use uint8_t directly")
typedef uint8_t Standard_Byte;

Standard_DEPRECATED("Standard_Address is deprecated, use void* directly")
typedef void* Standard_Address;

Standard_DEPRECATED("Standard_Size is deprecated, use size_t directly")
typedef size_t Standard_Size;

Standard_DEPRECATED("Standard_Time is deprecated, use std::time_t directly")
typedef std::time_t Standard_Time;

Standard_DEPRECATED("Standard_Utf8Char is deprecated, use char directly")
typedef char Standard_Utf8Char;

Standard_DEPRECATED("Standard_Utf8UChar is deprecated, use unsigned char directly")
typedef unsigned char Standard_Utf8UChar;

Standard_DEPRECATED("Standard_ExtCharacter is deprecated, use char16_t directly")
typedef char16_t Standard_ExtCharacter;

Standard_DEPRECATED("Standard_Utf16Char is deprecated, use char16_t directly")
typedef char16_t Standard_Utf16Char;

Standard_DEPRECATED("Standard_Utf32Char is deprecated, use char32_t directly")
typedef char32_t Standard_Utf32Char;

Standard_DEPRECATED("Standard_WideChar is deprecated, use wchar_t directly")
typedef wchar_t Standard_WideChar;

Standard_DEPRECATED("Standard_CString is deprecated, use const char* directly")
typedef const char* Standard_CString;

Standard_DEPRECATED("Standard_ExtString is deprecated, use const char16_t* directly")
typedef const char16_t* Standard_ExtString;
