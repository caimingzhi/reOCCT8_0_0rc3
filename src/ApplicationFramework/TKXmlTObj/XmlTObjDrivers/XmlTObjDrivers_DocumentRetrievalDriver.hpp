#pragma once

#include <XmlLDrivers_DocumentRetrievalDriver.hpp>
#include <XmlMDF_ADriverTable.hpp>

class XmlTObjDrivers_DocumentRetrievalDriver : public XmlLDrivers_DocumentRetrievalDriver
{
public:
  Standard_EXPORT XmlTObjDrivers_DocumentRetrievalDriver();

  Standard_EXPORT occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

public:
  DEFINE_STANDARD_RTTIEXT(XmlTObjDrivers_DocumentRetrievalDriver,
                          XmlLDrivers_DocumentRetrievalDriver)
};

#ifdef _MSC_VER
  #pragma once
#endif
