#pragma once

#include <BinMDF_ADriver.hpp>

class BinTObjDrivers_XYZDriver : public BinMDF_ADriver
{

public:
  Standard_EXPORT BinTObjDrivers_XYZDriver(const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const BinObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             BinObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&                        theSource,
    BinObjMgt_Persistent&                                    theTarget,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const override;

public:
  DEFINE_STANDARD_RTTIEXT(BinTObjDrivers_XYZDriver, BinMDF_ADriver)
};

#ifdef _MSC_VER
  #pragma once
#endif
