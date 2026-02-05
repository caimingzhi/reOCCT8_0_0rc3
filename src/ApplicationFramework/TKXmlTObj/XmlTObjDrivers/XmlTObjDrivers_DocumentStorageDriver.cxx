#include <XmlTObjDrivers_DocumentStorageDriver.hpp>
#include <XmlLDrivers.hpp>
#include <XmlTObjDrivers.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlTObjDrivers_DocumentStorageDriver, XmlLDrivers_DocumentStorageDriver)

//=================================================================================================

XmlTObjDrivers_DocumentStorageDriver::XmlTObjDrivers_DocumentStorageDriver(
  const TCollection_ExtendedString& theCopyright)
    : XmlLDrivers_DocumentStorageDriver(theCopyright)
{
}

//=================================================================================================

occ::handle<XmlMDF_ADriverTable> XmlTObjDrivers_DocumentStorageDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMsgDrv)
{
  // Standard drivers
  occ::handle<XmlMDF_ADriverTable> aTable = XmlLDrivers::AttributeDrivers(theMsgDrv);

  // Native drivers
  XmlTObjDrivers::AddDrivers(aTable, theMsgDrv);

  return aTable;
}
