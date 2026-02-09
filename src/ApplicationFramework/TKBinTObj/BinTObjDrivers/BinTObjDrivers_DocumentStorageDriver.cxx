#include <BinTObjDrivers_DocumentStorageDriver.hpp>
#include <BinLDrivers.hpp>
#include <BinTObjDrivers.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinTObjDrivers_DocumentStorageDriver, BinLDrivers_DocumentStorageDriver)

BinTObjDrivers_DocumentStorageDriver::BinTObjDrivers_DocumentStorageDriver()

  = default;

occ::handle<BinMDF_ADriverTable> BinTObjDrivers_DocumentStorageDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMsgDrv)
{

  occ::handle<BinMDF_ADriverTable> aTable = BinLDrivers::AttributeDrivers(theMsgDrv);

  BinTObjDrivers::AddDrivers(aTable, theMsgDrv);

  return aTable;
}
