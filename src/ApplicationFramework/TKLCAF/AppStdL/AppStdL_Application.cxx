#include <AppStdL_Application.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AppStdL_Application, TDocStd_Application)

//=================================================================================================

const char* AppStdL_Application::ResourcesName()
{
  const char* aRes = "StandardLite";
  return aRes;
}

//=================================================================================================

void AppStdL_Application::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDocStd_Application)
}
