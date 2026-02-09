#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BinDrivers_DocumentStorageDriver.hpp>
class BinMDF_ADriverTable;
class Message_Messenger;

class BinXCAFDrivers_DocumentStorageDriver : public BinDrivers_DocumentStorageDriver
{

public:
  Standard_EXPORT BinXCAFDrivers_DocumentStorageDriver();

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

  DEFINE_STANDARD_RTTIEXT(BinXCAFDrivers_DocumentStorageDriver, BinDrivers_DocumentStorageDriver)
};
