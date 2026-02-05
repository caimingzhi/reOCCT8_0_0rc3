#pragma once

#include <Standard.hpp>

#include <TDocStd_Application.hpp>

//! Legacy class defining resources name for lite OCAF documents
class AppStdL_Application : public TDocStd_Application
{
public:
  //! returns the file name which contains application
  //! resources
  Standard_EXPORT const char* ResourcesName() override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(AppStdL_Application, TDocStd_Application)
};
