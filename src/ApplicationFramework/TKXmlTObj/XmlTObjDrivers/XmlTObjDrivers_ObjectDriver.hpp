#pragma once

#include <XmlMDF_ADriver.hpp>

class XmlTObjDrivers_ObjectDriver : public XmlMDF_ADriver
{

public:
  Standard_EXPORT XmlTObjDrivers_ObjectDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);
  // constructor

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;
  // Creates a new attribute

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       Source,
                             const occ::handle<TDF_Attribute>& Target,
                             XmlObjMgt_RRelocationTable&       RelocTable) const override;
  // Translate the contents of <aSource> and put it
  // into <aTarget>, using the relocation table
  // <aRelocTable> to keep the sharings.
  // an TObj_Object is restored by TObj_Persistence basing on class name
  // stored in Source

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& Source,
                             XmlObjMgt_Persistent&             Target,
                             XmlObjMgt_SRelocationTable&       RelocTable) const override;
  // Translate the contents of <aSource> and put it
  // into <aTarget>, using the relocation table
  // <aRelocTable> to keep the sharings.
  // anObject is stored as a Name of class derived from TObj_Object

public:
  // CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(XmlTObjDrivers_ObjectDriver, XmlMDF_ADriver)
};

// Define handle class

#ifdef _MSC_VER
  #pragma once
#endif
