#include <BinTObjDrivers_DocumentRetrievalDriver.hpp>
#include <BinLDrivers.hpp>
#include <BinTObjDrivers.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinTObjDrivers_DocumentRetrievalDriver,
                           BinLDrivers_DocumentRetrievalDriver)

BinTObjDrivers_DocumentRetrievalDriver::BinTObjDrivers_DocumentRetrievalDriver()

  = default;

occ::handle<BinMDF_ADriverTable> BinTObjDrivers_DocumentRetrievalDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMsgDrv)
{

  occ::handle<BinMDF_ADriverTable> aTable = BinLDrivers::AttributeDrivers(theMsgDrv);

  BinTObjDrivers::AddDrivers(aTable, theMsgDrv);

  return aTable;
}
