#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_ExtendedString.hpp>
#include <XmlDrivers.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMXCAFDoc.hpp>
#include <XmlXCAFDrivers_DocumentStorageDriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlXCAFDrivers_DocumentStorageDriver, XmlDrivers_DocumentStorageDriver)

XmlXCAFDrivers_DocumentStorageDriver::XmlXCAFDrivers_DocumentStorageDriver(
  const TCollection_ExtendedString& theCopyright)
    : XmlDrivers_DocumentStorageDriver(theCopyright)
{
  AddNamespace("xcaf", "http://www.opencascade.org/OCAF/XML/XCAF");
}

occ::handle<XmlMDF_ADriverTable> XmlXCAFDrivers_DocumentStorageDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMsgDrv)
{

  occ::handle<XmlMDF_ADriverTable> aTable = XmlDrivers::AttributeDrivers(theMsgDrv);

  XmlMXCAFDoc::AddDrivers(aTable, theMsgDrv);

  return aTable;
}
