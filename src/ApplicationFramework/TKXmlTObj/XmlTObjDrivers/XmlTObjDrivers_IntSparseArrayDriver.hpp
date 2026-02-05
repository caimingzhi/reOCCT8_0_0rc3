#pragma once

#include <XmlMDF_ADriver.hpp>

class XmlTObjDrivers_IntSparseArrayDriver : public XmlMDF_ADriver
{

public:
  Standard_EXPORT XmlTObjDrivers_IntSparseArrayDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);
  // constructor

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;
  // Creates a new attribute

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             XmlObjMgt_RRelocationTable&       theRelocTable) const override;
  // Translate the contents of <theSource> and put it
  // into <theTarget>

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& theSource,
                             XmlObjMgt_Persistent&             theTarget,
                             XmlObjMgt_SRelocationTable&       theRelocTable) const override;
  // Translate the contents of <aSource> and put it
  // into <aTarget>

public:
  // CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(XmlTObjDrivers_IntSparseArrayDriver, XmlMDF_ADriver)
};

// Define handle class

#ifdef _MSC_VER
  #pragma once
#endif
