#pragma once

#include <Standard.hpp>
#include <Standard_OStream.hpp>
#include <BinLDrivers_DocumentStorageDriver.hpp>

class BinMDF_ADriverTable;
class Message_Messenger;
class BinLDrivers_DocumentSection;

class BinDrivers_DocumentStorageDriver : public BinLDrivers_DocumentStorageDriver
{

public:
  Standard_EXPORT BinDrivers_DocumentStorageDriver();

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

  Standard_EXPORT void WriteShapeSection(
    BinLDrivers_DocumentSection& theDocSection,
    Standard_OStream&            theOS,
    const TDocStd_FormatVersion  theDocVer,
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT bool IsWithTriangles() const;

  Standard_EXPORT bool IsWithNormals() const;

  Standard_EXPORT void SetWithTriangles(const occ::handle<Message_Messenger>& theMessageDriver,
                                        const bool                            theWithTriangulation);

  Standard_EXPORT void SetWithNormals(const occ::handle<Message_Messenger>& theMessageDriver,
                                      const bool                            theWithTriangulation);

  Standard_EXPORT void EnableQuickPartWriting(
    const occ::handle<Message_Messenger>& theMessageDriver,
    const bool                            theValue) override;

  Standard_EXPORT void Clear() override;

  DEFINE_STANDARD_RTTIEXT(BinDrivers_DocumentStorageDriver, BinLDrivers_DocumentStorageDriver)
};
