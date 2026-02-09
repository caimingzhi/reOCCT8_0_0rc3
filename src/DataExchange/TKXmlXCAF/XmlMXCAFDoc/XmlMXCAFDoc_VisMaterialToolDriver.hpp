#pragma once

#include <XmlMDF_ADriver.hpp>

class XmlMXCAFDoc_VisMaterialToolDriver : public XmlMDF_ADriver
{
  DEFINE_STANDARD_RTTIEXT(XmlMXCAFDoc_VisMaterialToolDriver, XmlMDF_ADriver)
public:
  Standard_EXPORT XmlMXCAFDoc_VisMaterialToolDriver(
    const occ::handle<Message_Messenger>& theMsgDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             XmlObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& theSource,
                             XmlObjMgt_Persistent&             theTarget,
                             XmlObjMgt_SRelocationTable&       theRelocTable) const override;
};
