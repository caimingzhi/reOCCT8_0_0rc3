#include <BinMDF_ADriverTable.hpp>
#include <BinXCAFDrivers.hpp>
#include <BinXCAFDrivers_DocumentRetrievalDriver.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinXCAFDrivers_DocumentRetrievalDriver,
                           BinDrivers_DocumentRetrievalDriver)

//=================================================================================================

BinXCAFDrivers_DocumentRetrievalDriver::BinXCAFDrivers_DocumentRetrievalDriver() = default;

//=================================================================================================

occ::handle<BinMDF_ADriverTable> BinXCAFDrivers_DocumentRetrievalDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMsgDriver)
{
  return BinXCAFDrivers::AttributeDrivers(theMsgDriver);
}
