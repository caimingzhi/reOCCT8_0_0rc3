#pragma once


#include <BinMDF_ADriver.hpp>

//! Binary persistence driver for XCAFDoc_VisMaterialTool attribute.
class BinMXCAFDoc_VisMaterialToolDriver : public BinMDF_ADriver
{
  DEFINE_STANDARD_RTTIEXT(BinMXCAFDoc_VisMaterialToolDriver, BinMDF_ADriver)
public:
  //! Main constructor.
  Standard_EXPORT BinMXCAFDoc_VisMaterialToolDriver(
    const occ::handle<Message_Messenger>& theMsgDriver);

  //! Create new instance of XCAFDoc_VisMaterialTool.
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! Paste attribute from persistence into document.
  Standard_EXPORT bool Paste(const BinObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             BinObjMgt_RRelocationTable&       theRelocTable) const override;

  //! Paste attribute from document into persistence.
  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&                        theSource,
    BinObjMgt_Persistent&                                    theTarget,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const override;
};

