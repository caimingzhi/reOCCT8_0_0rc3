#pragma once

#include <BinMDF_ADriver.hpp>
#include <Standard_Boolean.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>

class BinMXCAFDoc_VisMaterialDriver : public BinMDF_ADriver
{
  DEFINE_STANDARD_RTTIEXT(BinMXCAFDoc_VisMaterialDriver, BinMDF_ADriver)

  enum
  {
    MaterialVersionMajor_1 = 1,
    MaterialVersionMinor_0 = 0,
    MaterialVersionMinor_1 = 1,

    MaterialVersionMajor = MaterialVersionMajor_1,
    MaterialVersionMinor = MaterialVersionMinor_1
  };

public:
  Standard_EXPORT BinMXCAFDoc_VisMaterialDriver(const occ::handle<Message_Messenger>& theMsgDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const BinObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             BinObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&                        theSource,
    BinObjMgt_Persistent&                                    theTarget,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const override;
};
