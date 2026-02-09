

#include <Standard_CLocaleSentry.hpp>
#include <Standard_CString.hpp>
#include <Standard_Type.hpp>
#include <cstring>
#include <cstdarg>

#ifdef __APPLE__

  #define SAVE_TL()
#elif defined(_MSC_VER)

  #define SAVE_TL()
  #define strtod_l(thePtr, theNextPtr, theLocale) _strtod_l(thePtr, theNextPtr, theLocale)
  #define vprintf_l(theLocale, theFormat, theArgPtr) _vprintf_l(theFormat, theLocale, theArgPtr)
  #define vsprintf_l(theBuffer, theLocale, theFormat, theArgPtr)                                   \
    _vsprintf_l(theBuffer, theFormat, theLocale, theArgPtr)
  #define vfprintf_l(theFile, theLocale, theFormat, theArgPtr)                                     \
    _vfprintf_l(theFile, theFormat, theLocale, theArgPtr)
#else

  #define SAVE_TL() Standard_CLocaleSentry aLocaleSentry;
  #ifndef OCCT_CLOCALE_POSIX2008

    #if !defined(__ANDROID__) && !defined(__QNX__) && !defined(__MINGW32__)
      #error System does not support xlocale. Import/export could be broken if C locale did not specified by application.
    #endif
    #define strtod_l(thePtr, theNextPtr, theLocale) strtod(thePtr, theNextPtr)
  #endif
  #define vprintf_l(theLocale, theFormat, theArgPtr) vprintf(theFormat, theArgPtr)
  #define vsprintf_l(theBuffer, theLocale, theFormat, theArgPtr)                                   \
    vsprintf(theBuffer, theFormat, theArgPtr)
  #define vfprintf_l(theFile, theLocale, theFormat, theArgPtr)                                     \
    vfprintf(theFile, theFormat, theArgPtr)
#endif

double Atof(const char* theStr)
{
  return Strtod(theStr, nullptr);
}

int Printf(const char* theFormat, ...)
{
  SAVE_TL();
  va_list argp;
  va_start(argp, theFormat);
  int result = vprintf_l(Standard_CLocaleSentry::GetCLocale(), theFormat, argp);
  va_end(argp);
  return result;
}

int Fprintf(FILE* theFile, const char* theFormat, ...)
{
  SAVE_TL();
  va_list argp;
  va_start(argp, theFormat);
  int result = vfprintf_l(theFile, Standard_CLocaleSentry::GetCLocale(), theFormat, argp);
  va_end(argp);
  return result;
}

int Sprintf(char* theBuffer, const char* theFormat, ...)
{
  SAVE_TL();
  va_list argp;
  va_start(argp, theFormat);
  int result = vsprintf_l(theBuffer, Standard_CLocaleSentry::GetCLocale(), theFormat, argp);
  va_end(argp);
  return result;
}

int Vsprintf(char* theBuffer, const char* theFormat, va_list theArgList)
{
  SAVE_TL();
  return vsprintf_l(theBuffer, Standard_CLocaleSentry::GetCLocale(), theFormat, theArgList);
}
