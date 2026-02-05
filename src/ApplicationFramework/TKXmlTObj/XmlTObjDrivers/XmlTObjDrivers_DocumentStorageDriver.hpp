#pragma once

#include <XmlLDrivers_DocumentStorageDriver.hpp>
#include <XmlMDF_ADriverTable.hpp>

//  Block of comments describing class XmlTObjDrivers_DocumentStorageDriver
//

class XmlTObjDrivers_DocumentStorageDriver : public XmlLDrivers_DocumentStorageDriver
{
public:
  // ---------- PUBLIC METHODS ----------

  Standard_EXPORT XmlTObjDrivers_DocumentStorageDriver(
    const TCollection_ExtendedString& theCopyright);
  // Constructor

  Standard_EXPORT occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(XmlTObjDrivers_DocumentStorageDriver, XmlLDrivers_DocumentStorageDriver)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp

#ifdef _MSC_VER
  #pragma once
#endif
