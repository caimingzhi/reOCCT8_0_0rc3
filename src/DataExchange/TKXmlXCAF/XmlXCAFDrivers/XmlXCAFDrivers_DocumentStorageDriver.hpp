#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XmlDrivers_DocumentStorageDriver.hpp>
class TCollection_ExtendedString;
class XmlMDF_ADriverTable;
class Message_Messenger;

//! storage driver of a XS document
class XmlXCAFDrivers_DocumentStorageDriver : public XmlDrivers_DocumentStorageDriver
{

public:
  Standard_EXPORT XmlXCAFDrivers_DocumentStorageDriver(
    const TCollection_ExtendedString& theCopyright);

  Standard_EXPORT occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

  DEFINE_STANDARD_RTTIEXT(XmlXCAFDrivers_DocumentStorageDriver, XmlDrivers_DocumentStorageDriver)
};
