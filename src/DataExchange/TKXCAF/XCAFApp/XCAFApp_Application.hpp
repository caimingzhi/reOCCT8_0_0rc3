#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDocStd_Application.hpp>
#include <Standard_CString.hpp>

//! Implements an Application for the DECAF documents
class XCAFApp_Application : public TDocStd_Application
{

public:
  //! methods from TDocStd_Application
  //! ================================
  Standard_EXPORT const char* ResourcesName() override;

  //! Set XCAFDoc_DocumentTool attribute
  Standard_EXPORT void InitDocument(const occ::handle<CDM_Document>& aDoc) const override;

  //! Initializes (for the first time) and returns the
  //! static object (XCAFApp_Application)
  //! This is the only valid method to get XCAFApp_Application
  //! object, and it should be called at least once before
  //! any actions with documents in order to init application
  Standard_EXPORT static occ::handle<XCAFApp_Application> GetApplication();

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(XCAFApp_Application, TDocStd_Application)

protected:
  Standard_EXPORT XCAFApp_Application();
};

