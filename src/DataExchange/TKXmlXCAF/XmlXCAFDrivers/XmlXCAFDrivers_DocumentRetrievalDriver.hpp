#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XmlDrivers_DocumentRetrievalDriver.hpp>
class XmlMDF_ADriverTable;
class Message_Messenger;

//! retrieval driver of a XS document
class XmlXCAFDrivers_DocumentRetrievalDriver : public XmlDrivers_DocumentRetrievalDriver
{

public:
  Standard_EXPORT XmlXCAFDrivers_DocumentRetrievalDriver();

  Standard_EXPORT occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

  DEFINE_STANDARD_RTTIEXT(XmlXCAFDrivers_DocumentRetrievalDriver,
                          XmlDrivers_DocumentRetrievalDriver)
};

