#include <BinDrivers.hpp>
#include <BinDrivers_DocumentRetrievalDriver.hpp>
#include <BinLDrivers_DocumentSection.hpp>
#include <BinMDataStd.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <BinMNaming_NamedShapeDriver.hpp>
#include <Message_Messenger.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_IStream.hpp>
#include <Standard_Type.hpp>
#include <Standard_NotImplemented.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TNaming_NamedShape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinDrivers_DocumentRetrievalDriver, BinLDrivers_DocumentRetrievalDriver)

BinDrivers_DocumentRetrievalDriver::BinDrivers_DocumentRetrievalDriver() = default;

occ::handle<BinMDF_ADriverTable> BinDrivers_DocumentRetrievalDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMessageDriver)
{
  return BinDrivers::AttributeDrivers(theMessageDriver);
}

void BinDrivers_DocumentRetrievalDriver::ReadShapeSection(BinLDrivers_DocumentSection&,
                                                          Standard_IStream& theIS,
                                                          const bool,
                                                          const Message_ProgressRange& theRange)

{

  occ::handle<BinMDF_ADriver> aDriver;
  if (myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver))
  {
    try
    {
      OCC_CATCH_SIGNALS
      occ::handle<BinMNaming_NamedShapeDriver> aNamedShapeDriver =
        occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
      aNamedShapeDriver->ReadShapeSection(theIS, theRange);
    }
    catch (Standard_Failure const& anException)
    {
      const TCollection_ExtendedString aMethStr("BinDrivers_DocumentRetrievalDriver: ");
      myMsgDriver->Send(aMethStr + "error of Shape Section " + anException.what(), Message_Fail);
    }
  }
}

void BinDrivers_DocumentRetrievalDriver::CheckShapeSection(const Storage_Position&,
                                                           Standard_IStream&)
{
}

void BinDrivers_DocumentRetrievalDriver::Clear()
{

  occ::handle<BinMDF_ADriver> aDriver;
  if (myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver))
  {
    occ::handle<BinMNaming_NamedShapeDriver> aNamedShapeDriver =
      occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
    aNamedShapeDriver->Clear();
  }
  BinLDrivers_DocumentRetrievalDriver::Clear();
}

void BinDrivers_DocumentRetrievalDriver::EnableQuickPartReading(
  const occ::handle<Message_Messenger>& theMessageDriver,
  bool                                  theValue)
{
  if (myDrivers.IsNull())
    myDrivers = AttributeDrivers(theMessageDriver);
  if (myDrivers.IsNull())
    return;

  occ::handle<BinMDF_ADriver> aDriver;
  myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver);
  occ::handle<BinMNaming_NamedShapeDriver> aShapesDriver =
    occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
  if (aShapesDriver.IsNull())
    throw Standard_NotImplemented("Internal Error - TNaming_NamedShape is not found!");

  aShapesDriver->EnableQuickPart(theValue);
}
