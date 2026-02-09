#pragma once

#include <Standard_Macro.hpp>

#include <locale.h>

#if defined(__APPLE__)
  #include <xlocale.h>
#endif

#ifndef OCCT_CLOCALE_POSIX2008

  #if defined(__APPLE__)
    #define OCCT_CLOCALE_POSIX2008
  #endif

  #if defined(_GNU_SOURCE) && !defined(__ANDROID__)
    #define OCCT_CLOCALE_POSIX2008
  #endif
#endif

#if !defined(__ANDROID__)

class Standard_CLocaleSentry
{
public:
  Standard_EXPORT Standard_CLocaleSentry();

  Standard_EXPORT ~Standard_CLocaleSentry();

public:
  #ifdef OCCT_CLOCALE_POSIX2008
  typedef locale_t clocale_t;
  #elif defined(_MSC_VER)
  typedef _locale_t clocale_t;
  #else
  typedef void* clocale_t;
  #endif

  static Standard_EXPORT clocale_t GetCLocale();

private:
  void* myPrevLocale;
  #ifdef _MSC_VER
  int myPrevTLocaleState;
  #endif

private:
  Standard_CLocaleSentry(const Standard_CLocaleSentry&)            = delete;
  Standard_CLocaleSentry& operator=(const Standard_CLocaleSentry&) = delete;
};

#else

class Standard_CLocaleSentry
{
public:
  Standard_CLocaleSentry() {}

  typedef void* clocale_t;

  static clocale_t GetCLocale() { return 0; }
};

#endif
