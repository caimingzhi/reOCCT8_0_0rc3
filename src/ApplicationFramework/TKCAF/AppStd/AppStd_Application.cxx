#include <AppStd_Application.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AppStd_Application, TDocStd_Application)

const char* AppStd_Application::ResourcesName()
{
  const char* aRes = "Standard";
  return aRes;
}

void AppStd_Application::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDocStd_Application)
}
