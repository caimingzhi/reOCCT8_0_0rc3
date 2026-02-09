#include <BinMDF_ADriverTable.hpp>
#include <BinXCAFDrivers.hpp>
#include <BinXCAFDrivers_DocumentStorageDriver.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinXCAFDrivers_DocumentStorageDriver, BinDrivers_DocumentStorageDriver)

BinXCAFDrivers_DocumentStorageDriver::BinXCAFDrivers_DocumentStorageDriver() = default;

occ::handle<BinMDF_ADriverTable> BinXCAFDrivers_DocumentStorageDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMsgDriver)
{
  return BinXCAFDrivers::AttributeDrivers(theMsgDriver);
}
