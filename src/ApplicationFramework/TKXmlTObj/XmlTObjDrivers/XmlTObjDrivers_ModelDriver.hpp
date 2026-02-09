#pragma once

#include <XmlMDF_ADriver.hpp>

class XmlTObjDrivers_ModelDriver : public XmlMDF_ADriver
{

public:
  Standard_EXPORT XmlTObjDrivers_ModelDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       Source,
                             const occ::handle<TDF_Attribute>& Target,
                             XmlObjMgt_RRelocationTable&       RelocTable) const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& Source,
                             XmlObjMgt_Persistent&             Target,
                             XmlObjMgt_SRelocationTable&       RelocTable) const override;

public:
  DEFINE_STANDARD_RTTIEXT(XmlTObjDrivers_ModelDriver, XmlMDF_ADriver)
};

#ifdef _MSC_VER
  #pragma once
#endif
