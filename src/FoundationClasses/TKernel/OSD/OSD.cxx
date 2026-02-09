

#include <OSD.hpp>

#include <Standard_CString.hpp>

bool OSD::RealToCString(const double aReal, Standard_PCharacter& aString)
{
  char *p, *q;

  if (Sprintf(aString, "%.17e", aReal) <= 0)
    return false;

  p = strchr(aString, 'e');
  if (p)
  {
    if (!strcmp(p, "e+00"))
      *p = 0;
    for (q = p - 1; *q == '0'; q--)
      ;
    if (q != p - 1)
    {
      if (*q != '.')
        q++;
      while (*p)
        *q++ = *p++;
      *q = 0;
    }
  }
  return true;
}

bool OSD::CStringToReal(const char* aString, double& aReal)
{
  char* endptr;
  aReal = Strtod(aString, &endptr);
  return *endptr == 0;
}

#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

void OSD::SecSleep(const int theSeconds)
{
#ifdef _WIN32
  Sleep(theSeconds * 1000);
#else
  usleep(theSeconds * 1000 * 1000);
#endif
}

void OSD::MilliSecSleep(const int theMilliseconds)
{
#ifdef _WIN32
  Sleep(theMilliseconds);
#else
  usleep(theMilliseconds * 1000);
#endif
}
