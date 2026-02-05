#include <XmlTObjDrivers_DocumentRetrievalDriver.hpp>
#include <XmlLDrivers.hpp>
#include <XmlTObjDrivers.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlTObjDrivers_DocumentRetrievalDriver,
                           XmlLDrivers_DocumentRetrievalDriver)

//=================================================================================================

XmlTObjDrivers_DocumentRetrievalDriver::XmlTObjDrivers_DocumentRetrievalDriver() = default;

//=================================================================================================

occ::handle<XmlMDF_ADriverTable> XmlTObjDrivers_DocumentRetrievalDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMsgDrv)
{
  // Standard drivers
  occ::handle<XmlMDF_ADriverTable> aTable = XmlLDrivers::AttributeDrivers(theMsgDrv);

  // Native drivers
  XmlTObjDrivers::AddDrivers(aTable, theMsgDrv);

  return aTable;
}
