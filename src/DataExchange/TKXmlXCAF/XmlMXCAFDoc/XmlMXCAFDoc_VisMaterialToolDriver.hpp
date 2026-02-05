#pragma once

#include <XmlMDF_ADriver.hpp>

//! XML persistence driver for XCAFDoc_VisMaterialTool.
class XmlMXCAFDoc_VisMaterialToolDriver : public XmlMDF_ADriver
{
  DEFINE_STANDARD_RTTIEXT(XmlMXCAFDoc_VisMaterialToolDriver, XmlMDF_ADriver)
public:
  //! Main constructor.
  Standard_EXPORT XmlMXCAFDoc_VisMaterialToolDriver(
    const occ::handle<Message_Messenger>& theMsgDriver);

  //! Create new instance of XCAFDoc_VisMaterialTool.
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! Paste attribute from persistence into document.
  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             XmlObjMgt_RRelocationTable&       theRelocTable) const override;

  //! Paste attribute from document into persistence.
  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& theSource,
                             XmlObjMgt_Persistent&             theTarget,
                             XmlObjMgt_SRelocationTable&       theRelocTable) const override;
};
