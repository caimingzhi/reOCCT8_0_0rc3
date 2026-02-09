#pragma once

#include <XmlMDF_ADriver.hpp>

class XmlTObjDrivers_IntSparseArrayDriver : public XmlMDF_ADriver
{

public:
  Standard_EXPORT XmlTObjDrivers_IntSparseArrayDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             XmlObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& theSource,
                             XmlObjMgt_Persistent&             theTarget,
                             XmlObjMgt_SRelocationTable&       theRelocTable) const override;

public:
  DEFINE_STANDARD_RTTIEXT(XmlTObjDrivers_IntSparseArrayDriver, XmlMDF_ADriver)
};

#ifdef _MSC_VER
  #pragma once
#endif
