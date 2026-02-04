#pragma once


#include <Standard_Macro.hpp>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#if defined(_MSC_VER)
  #if !defined(strcasecmp)
    #define strcasecmp _stricmp
  #endif
  #if !defined(strncasecmp)
    #define strncasecmp _strnicmp
  #endif
#endif

// C++ only definitions
#ifdef __cplusplus

  #include <Standard_TypeDef.hpp>

//! Returns Standard_True if two strings are equal
inline bool IsEqual(const char* theOne, const char* theTwo)
{
  return strcmp(theOne, theTwo) == 0;
}

#endif /* __cplusplus */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  //! Equivalent of standard C function atof() that always uses C locale
  Standard_EXPORT double Atof(const char* theStr);

  //! Optimized equivalent of standard C function strtod() that always uses C locale
  Standard_EXPORT double Strtod(const char* theStr, char** theNextPtr);

  //! Equivalent of standard C function printf() that always uses C locale
  Standard_EXPORT int Printf(const char* theFormat, ...)
#ifdef __GNUC__
    __attribute__((format(printf, 1, 2)))
#endif
    ;

  //! Equivalent of standard C function fprintf() that always uses C locale
  Standard_EXPORT int Fprintf(FILE* theFile, const char* theFormat, ...)
#ifdef __GNUC__
    __attribute__((format(printf, 2, 3)))
#endif
    ;

  //! Equivalent of standard C function sprintf() that always uses C locale
  Standard_EXPORT int Sprintf(char* theBuffer, const char* theFormat, ...)
#ifdef __GNUC__
    __attribute__((format(printf, 2, 3)))
#endif
    ;

  //! Equivalent of standard C function vsprintf() that always uses C locale.
  //! Note that this function does not check buffer bounds and should be used with precaution
  //! measures (only with format fitting into the buffer of known size).
  //! @param[in][out] theBuffer    string buffer to fill
  //! @param[in] theFormat   format to apply
  //! @param[in] theArgList  argument list for specified format
  //! @return the total number of characters written, or a negative number on error
  Standard_EXPORT int Vsprintf(char* theBuffer, const char* theFormat, va_list theArgList)
#ifdef __GNUC__
    __attribute__((format(printf, 2, 0)))
#endif
    ;

#ifdef __cplusplus
}
#endif /* __cplusplus */

