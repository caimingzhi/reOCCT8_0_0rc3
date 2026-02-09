#pragma once

#include <BinLDrivers_DocumentStorageDriver.hpp>
#include <BinMDF_ADriverTable.hpp>

class BinTObjDrivers_DocumentStorageDriver : public BinLDrivers_DocumentStorageDriver
{
public:
  Standard_EXPORT BinTObjDrivers_DocumentStorageDriver();

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

public:
  DEFINE_STANDARD_RTTIEXT(BinTObjDrivers_DocumentStorageDriver, BinLDrivers_DocumentStorageDriver)
};

#ifdef _MSC_VER
  #pragma once
#endif
