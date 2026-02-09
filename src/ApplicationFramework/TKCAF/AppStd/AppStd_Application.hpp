#pragma once

#include <Standard.hpp>

#include <TDocStd_Application.hpp>

class AppStd_Application : public TDocStd_Application
{
public:
  Standard_EXPORT const char* ResourcesName() override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(AppStd_Application, TDocStd_Application)
};
