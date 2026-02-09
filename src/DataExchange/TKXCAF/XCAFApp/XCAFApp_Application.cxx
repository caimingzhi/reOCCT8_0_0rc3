#include <Resource_Manager.hpp>
#include <Standard_Dump.hpp>
#include <TDF_Label.hpp>
#include <TPrsStd_DriverTable.hpp>
#include <XCAFApp_Application.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFPrs_Driver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XCAFApp_Application, TDocStd_Application)

occ::handle<XCAFApp_Application> XCAFApp_Application::GetApplication()
{
  static occ::handle<XCAFApp_Application> locApp;
  if (locApp.IsNull())
    locApp = new XCAFApp_Application;
  return locApp;
}

XCAFApp_Application::XCAFApp_Application()
{

  occ::handle<TPrsStd_DriverTable> table = TPrsStd_DriverTable::Get();
  table->AddDriver(XCAFPrs_Driver::GetID(), new XCAFPrs_Driver);
}

const char* XCAFApp_Application::ResourcesName()
{
  return static_cast<const char*>("XCAF");
}

void XCAFApp_Application::InitDocument(const occ::handle<CDM_Document>& aDoc) const
{
  XCAFDoc_DocumentTool::Set(occ::down_cast<TDocStd_Document>(aDoc)->Main());
}

void XCAFApp_Application::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDocStd_Application)
}
