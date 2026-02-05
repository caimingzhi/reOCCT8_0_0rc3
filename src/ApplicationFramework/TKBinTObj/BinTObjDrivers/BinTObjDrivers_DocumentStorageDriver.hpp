#pragma once

#include <BinLDrivers_DocumentStorageDriver.hpp>
#include <BinMDF_ADriverTable.hpp>

//  Block of comments describing class BinTObjDrivers_DocumentStorageDriver
//

class BinTObjDrivers_DocumentStorageDriver : public BinLDrivers_DocumentStorageDriver
{
public:
  // ---------- PUBLIC METHODS ----------

  Standard_EXPORT BinTObjDrivers_DocumentStorageDriver();
  // Constructor

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(BinTObjDrivers_DocumentStorageDriver, BinLDrivers_DocumentStorageDriver)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp

#ifdef _MSC_VER
  #pragma once
#endif
