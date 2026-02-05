#pragma once

#include <Standard.hpp>

#include <BinMDF_ADriver.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
class Message_Messenger;
class TDF_Attribute;
class BinObjMgt_Persistent;

//! Position Attribute Driver.
class BinMDataXtd_PositionDriver : public BinMDF_ADriver
{

public:
  Standard_EXPORT BinMDataXtd_PositionDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const BinObjMgt_Persistent&       Source,
                             const occ::handle<TDF_Attribute>& Target,
                             BinObjMgt_RRelocationTable&       RelocTable) const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&                        Source,
    BinObjMgt_Persistent&                                    Target,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& RelocTable) const override;

  DEFINE_STANDARD_RTTIEXT(BinMDataXtd_PositionDriver, BinMDF_ADriver)
};
