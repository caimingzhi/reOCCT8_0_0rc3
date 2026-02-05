#pragma once

#include <Standard.hpp>

#include <BinLDrivers_DocumentRetrievalDriver.hpp>
#include <Standard_IStream.hpp>
#include <Storage_Position.hpp>
#include <Standard_Integer.hpp>
class BinMDF_ADriverTable;
class Message_Messenger;
class BinLDrivers_DocumentSection;

class BinDrivers_DocumentRetrievalDriver : public BinLDrivers_DocumentRetrievalDriver
{

public:
  //! Constructor
  Standard_EXPORT BinDrivers_DocumentRetrievalDriver();

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

  Standard_EXPORT void ReadShapeSection(
    BinLDrivers_DocumentSection& theSection,
    Standard_IStream&            theIS,
    const bool                   isMess   = false,
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT void CheckShapeSection(const Storage_Position& thePos,
                                         Standard_IStream&       theIS) override;

  //! Clears the NamedShape driver
  Standard_EXPORT void Clear() override;

  //! Enables reading in the quick part access mode.
  Standard_EXPORT void EnableQuickPartReading(
    const occ::handle<Message_Messenger>& theMessageDriver,
    bool                                  theValue) override;

  DEFINE_STANDARD_RTTIEXT(BinDrivers_DocumentRetrievalDriver, BinLDrivers_DocumentRetrievalDriver)
};
