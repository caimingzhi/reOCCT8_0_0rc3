#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <XmlDrivers.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMXCAFDoc.hpp>
#include <XmlXCAFDrivers_DocumentRetrievalDriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlXCAFDrivers_DocumentRetrievalDriver,
                           XmlDrivers_DocumentRetrievalDriver)

XmlXCAFDrivers_DocumentRetrievalDriver::XmlXCAFDrivers_DocumentRetrievalDriver() = default;

occ::handle<XmlMDF_ADriverTable> XmlXCAFDrivers_DocumentRetrievalDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMsgDrv)
{

  occ::handle<XmlMDF_ADriverTable> aTable = XmlDrivers::AttributeDrivers(theMsgDrv);

  XmlMXCAFDoc::AddDrivers(aTable, theMsgDrv);

  return aTable;
}
