#pragma once

#include <XmlLDrivers_DocumentStorageDriver.hpp>
#include <XmlMDF_ADriverTable.hpp>

class XmlTObjDrivers_DocumentStorageDriver : public XmlLDrivers_DocumentStorageDriver
{
public:
  Standard_EXPORT XmlTObjDrivers_DocumentStorageDriver(
    const TCollection_ExtendedString& theCopyright);

  Standard_EXPORT occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

public:
  DEFINE_STANDARD_RTTIEXT(XmlTObjDrivers_DocumentStorageDriver, XmlLDrivers_DocumentStorageDriver)
};

#ifdef _MSC_VER
  #pragma once
#endif
