#pragma once


#include <Standard.hpp>

#include <XmlMDF_ADriver.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>

//! Attribute Driver.
class XmlMXCAFDoc_VisMaterialDriver : public XmlMDF_ADriver
{
  DEFINE_STANDARD_RTTIEXT(XmlMXCAFDoc_VisMaterialDriver, XmlMDF_ADriver)
public:
  //! Main constructor.
  Standard_EXPORT XmlMXCAFDoc_VisMaterialDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  //! Create new instance of XCAFDoc_VisMaterial.
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

