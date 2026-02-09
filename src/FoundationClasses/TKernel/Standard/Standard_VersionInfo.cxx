

#include <Standard_VersionInfo.hpp>

#include <Standard_Version.hxx>

const char* OCCT_DevelopmentVersion()
{
#ifdef OCC_VERSION_DEVELOPMENT
  return OCC_VERSION_DEVELOPMENT;
#else
  return "";
#endif
}

double OCCT_Version_Double()
{
  return OCC_VERSION;
}

const char* OCCT_Version_String()
{
  return OCC_VERSION_STRING;
}

const char* OCCT_Version_String_Complete()
{
  return OCC_VERSION_COMPLETE;
}

const char* OCCT_Version_String_Extended()
{
  return OCC_VERSION_STRING_EXT;
}
