#include <BinDrivers_DocumentStorageDriver.hpp>

#include <BinDrivers.hpp>
#include <BinLDrivers_DocumentSection.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <BinMNaming_NamedShapeDriver.hpp>
#include <Message_Messenger.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>
#include <TNaming_NamedShape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinDrivers_DocumentStorageDriver, BinLDrivers_DocumentStorageDriver)

//=================================================================================================

BinDrivers_DocumentStorageDriver::BinDrivers_DocumentStorageDriver() = default;

//=================================================================================================

occ::handle<BinMDF_ADriverTable> BinDrivers_DocumentStorageDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMessageDriver)
{
  return BinDrivers::AttributeDrivers(theMessageDriver);
}

//=================================================================================================

bool BinDrivers_DocumentStorageDriver::IsWithTriangles() const
{
  if (myDrivers.IsNull())
  {
    return false;
  }

  occ::handle<BinMDF_ADriver> aDriver;
  myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver);
  occ::handle<BinMNaming_NamedShapeDriver> aShapesDriver =
    occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
  return !aShapesDriver.IsNull() && aShapesDriver->IsWithTriangles();
}

//=================================================================================================

void BinDrivers_DocumentStorageDriver::SetWithTriangles(
  const occ::handle<Message_Messenger>& theMessageDriver,
  const bool                            theWithTriangulation)
{
  if (myDrivers.IsNull())
  {
    myDrivers = AttributeDrivers(theMessageDriver);
  }
  if (myDrivers.IsNull())
  {
    return;
  }

  occ::handle<BinMDF_ADriver> aDriver;
  myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver);
  occ::handle<BinMNaming_NamedShapeDriver> aShapesDriver =
    occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
  if (aShapesDriver.IsNull())
  {
    throw Standard_NotImplemented("Internal Error - TNaming_NamedShape is not found!");
  }

  aShapesDriver->SetWithTriangles(theWithTriangulation);
}

void BinDrivers_DocumentStorageDriver::EnableQuickPartWriting(
  const occ::handle<Message_Messenger>& theMessageDriver,
  const bool                            theValue)
{
  if (myDrivers.IsNull())
  {
    myDrivers = AttributeDrivers(theMessageDriver);
  }
  if (myDrivers.IsNull())
  {
    return;
  }

  occ::handle<BinMDF_ADriver> aDriver;
  myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver);
  occ::handle<BinMNaming_NamedShapeDriver> aShapesDriver =
    occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
  if (aShapesDriver.IsNull())
  {
    throw Standard_NotImplemented("Internal Error - TNaming_NamedShape is not found!");
  }

  aShapesDriver->EnableQuickPart(theValue);
}

//=================================================================================================

void BinDrivers_DocumentStorageDriver::Clear()
{
  // Clear NamedShape driver
  occ::handle<BinMDF_ADriver> aDriver;
  if (myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver))
  {
    occ::handle<BinMNaming_NamedShapeDriver> aNamedShapeDriver =
      occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
    aNamedShapeDriver->Clear();
  }
  BinLDrivers_DocumentStorageDriver::Clear();
}

//=================================================================================================

bool BinDrivers_DocumentStorageDriver::IsWithNormals() const
{
  if (myDrivers.IsNull())
  {
    return false;
  }

  occ::handle<BinMDF_ADriver> aDriver;
  myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver);
  occ::handle<BinMNaming_NamedShapeDriver> aShapesDriver =
    occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
  return !aShapesDriver.IsNull() && aShapesDriver->IsWithNormals();
}

//=================================================================================================

void BinDrivers_DocumentStorageDriver::SetWithNormals(
  const occ::handle<Message_Messenger>& theMessageDriver,
  const bool                            theWithNormals)
{
  if (myDrivers.IsNull())
  {
    myDrivers = AttributeDrivers(theMessageDriver);
  }
  if (myDrivers.IsNull())
  {
    return;
  }

  occ::handle<BinMDF_ADriver> aDriver;
  myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver);
  occ::handle<BinMNaming_NamedShapeDriver> aShapesDriver =
    occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
  if (aShapesDriver.IsNull())
  {
    throw Standard_NotImplemented("Internal Error - TNaming_NamedShape is not found!");
  }

  aShapesDriver->SetWithNormals(theWithNormals);
}

//=======================================================================
// function : WriteShapeSection
// purpose  : Implements WriteShapeSection
//=======================================================================
void BinDrivers_DocumentStorageDriver::WriteShapeSection(BinLDrivers_DocumentSection& theSection,
                                                         Standard_OStream&            theOS,
                                                         const TDocStd_FormatVersion  theDocVer,
                                                         const Message_ProgressRange& theRange)
{
  const size_t aShapesSectionOffset = (size_t)theOS.tellp();

  occ::handle<BinMDF_ADriver> aDriver;
  if (myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver))
  {
    try
    {
      OCC_CATCH_SIGNALS
      occ::handle<BinMNaming_NamedShapeDriver> aNamedShapeDriver =
        occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
      aNamedShapeDriver->WriteShapeSection(theOS, theDocVer, theRange);
    }
    catch (Standard_Failure const& anException)
    {
      TCollection_ExtendedString anErrorStr("BinDrivers_DocumentStorageDriver, Shape Section :");
      myMsgDriver->Send(anErrorStr + anException.what(), Message_Fail);
    }
  }

  // Write the section info in the TOC.
  theSection.Write(theOS, aShapesSectionOffset, theDocVer);
}
