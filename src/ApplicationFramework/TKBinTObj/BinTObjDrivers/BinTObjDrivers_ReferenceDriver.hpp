#pragma once


#include <BinMDF_ADriver.hpp>

class BinTObjDrivers_ReferenceDriver : public BinMDF_ADriver
{

public:
  Standard_EXPORT BinTObjDrivers_ReferenceDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);
  // constructor

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;
  // Creates a new attribute

  Standard_EXPORT bool Paste(const BinObjMgt_Persistent&       Source,
                             const occ::handle<TDF_Attribute>& Target,
                             BinObjMgt_RRelocationTable&       RelocTable) const override;
  // Translate the contents of <aSource> and put it
  // into <aTarget>, using the relocation table
  // <aRelocTable> to keep the sharings.

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&                        Source,
    BinObjMgt_Persistent&                                    Target,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& RelocTable) const override;
  // Translate the contents of <aSource> and put it
  // into <aTarget>, using the relocation table
  // <aRelocTable> to keep the sharings.
  // Store master and referred labels as entry, the other model referred
  // as entry in model-container
  // The reference pointing nowhere is not stored

public:
  // CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(BinTObjDrivers_ReferenceDriver, BinMDF_ADriver)
};

// Define handle class

#ifdef _MSC_VER
#pragma once
#endif
