#pragma once

#include <BinMDF_ADriver.hpp>

class BinTObjDrivers_ObjectDriver : public BinMDF_ADriver
{

public:
  Standard_EXPORT BinTObjDrivers_ObjectDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const BinObjMgt_Persistent&       Source,
                             const occ::handle<TDF_Attribute>& Target,
                             BinObjMgt_RRelocationTable&       RelocTable) const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&                        Source,
    BinObjMgt_Persistent&                                    Target,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& RelocTable) const override;

public:
  DEFINE_STANDARD_RTTIEXT(BinTObjDrivers_ObjectDriver, BinMDF_ADriver)
};

#ifdef _MSC_VER
  #pragma once
#endif
