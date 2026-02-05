#pragma once

#include <XmlLDrivers_DocumentRetrievalDriver.hpp>
#include <XmlMDF_ADriverTable.hpp>

// Retrieval driver of a TObj XML document
//

class XmlTObjDrivers_DocumentRetrievalDriver : public XmlLDrivers_DocumentRetrievalDriver
{
public:
  // ---------- PUBLIC METHODS ----------

  Standard_EXPORT XmlTObjDrivers_DocumentRetrievalDriver();
  // Constructor

  Standard_EXPORT occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(XmlTObjDrivers_DocumentRetrievalDriver,
                          XmlLDrivers_DocumentRetrievalDriver)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp

#ifdef _MSC_VER
  #pragma once
#endif
