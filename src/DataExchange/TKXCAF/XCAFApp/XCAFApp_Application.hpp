#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDocStd_Application.hpp>
#include <Standard_CString.hpp>

class XCAFApp_Application : public TDocStd_Application
{

public:
  Standard_EXPORT const char* ResourcesName() override;

  Standard_EXPORT void InitDocument(const occ::handle<CDM_Document>& aDoc) const override;

  Standard_EXPORT static occ::handle<XCAFApp_Application> GetApplication();

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(XCAFApp_Application, TDocStd_Application)

protected:
  Standard_EXPORT XCAFApp_Application();
};
