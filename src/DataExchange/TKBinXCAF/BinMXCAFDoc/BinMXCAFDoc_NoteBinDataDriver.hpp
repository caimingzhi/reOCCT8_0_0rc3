#pragma once


#include <BinMXCAFDoc_NoteDriver.hpp>

class BinMXCAFDoc_NoteBinDataDriver : public BinMXCAFDoc_NoteDriver
{
public:
  Standard_EXPORT BinMXCAFDoc_NoteBinDataDriver(const occ::handle<Message_Messenger>& theMsgDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const BinObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             BinObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&                        theSource,
    BinObjMgt_Persistent&                                    theTarget,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const override;

  DEFINE_STANDARD_RTTIEXT(BinMXCAFDoc_NoteBinDataDriver, BinMXCAFDoc_NoteDriver)
};

