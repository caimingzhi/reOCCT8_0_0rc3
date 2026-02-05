#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TNaming_NamedShape.hpp>
#include <XmlDrivers.hpp>
#include <XmlDrivers_DocumentRetrievalDriver.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMNaming_NamedShapeDriver.hpp>
#include <XmlObjMgt_Element.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlDrivers_DocumentRetrievalDriver, XmlLDrivers_DocumentRetrievalDriver)

//=================================================================================================

XmlDrivers_DocumentRetrievalDriver::XmlDrivers_DocumentRetrievalDriver() = default;

//=================================================================================================

occ::handle<XmlMDF_ADriverTable> XmlDrivers_DocumentRetrievalDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMessageDriver)
{
  return XmlDrivers::AttributeDrivers(theMessageDriver);
}

//=======================================================================
// function : ReadShapeSection
// purpose  : Implementation of ReadShapeSection
//=======================================================================
occ::handle<XmlMDF_ADriver> XmlDrivers_DocumentRetrievalDriver::ReadShapeSection(
  const XmlObjMgt_Element&              theElement,
  const occ::handle<Message_Messenger>& theMsgDriver,
  const Message_ProgressRange&          theRange)
{
  if (myDrivers.IsNull())
    myDrivers = AttributeDrivers(theMsgDriver);
  occ::handle<XmlMDF_ADriver> aDriver;
  if (myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver))
  {
    occ::handle<XmlMNaming_NamedShapeDriver> aNamedShapeDriver =
      occ::down_cast<XmlMNaming_NamedShapeDriver>(aDriver);
    aNamedShapeDriver->ReadShapeSection(theElement, theRange);
  }
  return aDriver;
}

//=======================================================================
// function : ShapeSetCleaning
// purpose  : definition of ShapeSetCleaning
//=======================================================================
void XmlDrivers_DocumentRetrievalDriver::ShapeSetCleaning(
  const occ::handle<XmlMDF_ADriver>& theDriver)
{
  occ::handle<XmlMNaming_NamedShapeDriver> aNamedShapeDriver =
    occ::down_cast<XmlMNaming_NamedShapeDriver>(theDriver);
  if (!aNamedShapeDriver.IsNull())
    aNamedShapeDriver->Clear();
}
