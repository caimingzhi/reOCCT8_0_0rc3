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

#ifdef __cplusplus

  #include <Standard_TypeDef.hpp>

inline bool IsEqual(const char* theOne, const char* theTwo)
{
  return strcmp(theOne, theTwo) == 0;
}

#endif

#ifdef __cplusplus
extern "C"
{
#endif

  Standard_EXPORT double Atof(const char* theStr);

  Standard_EXPORT double Strtod(const char* theStr, char** theNextPtr);

  Standard_EXPORT int Printf(const char* theFormat, ...)
#ifdef __GNUC__
    __attribute__((format(printf, 1, 2)))
#endif
    ;

  Standard_EXPORT int Fprintf(FILE* theFile, const char* theFormat, ...)
#ifdef __GNUC__
    __attribute__((format(printf, 2, 3)))
#endif
    ;

  Standard_EXPORT int Sprintf(char* theBuffer, const char* theFormat, ...)
#ifdef __GNUC__
    __attribute__((format(printf, 2, 3)))
#endif
    ;

  Standard_EXPORT int Vsprintf(char* theBuffer, const char* theFormat, va_list theArgList)
#ifdef __GNUC__
    __attribute__((format(printf, 2, 0)))
#endif
    ;

#ifdef __cplusplus
}
#endif
