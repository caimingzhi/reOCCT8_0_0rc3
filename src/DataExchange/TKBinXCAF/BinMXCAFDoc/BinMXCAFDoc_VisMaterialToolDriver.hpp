#pragma once

#include <BinMDF_ADriver.hpp>

class BinMXCAFDoc_VisMaterialToolDriver : public BinMDF_ADriver
{
  DEFINE_STANDARD_RTTIEXT(BinMXCAFDoc_VisMaterialToolDriver, BinMDF_ADriver)
public:
  Standard_EXPORT BinMXCAFDoc_VisMaterialToolDriver(
    const occ::handle<Message_Messenger>& theMsgDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const BinObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             BinObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&                        theSource,
    BinObjMgt_Persistent&                                    theTarget,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const override;
};
