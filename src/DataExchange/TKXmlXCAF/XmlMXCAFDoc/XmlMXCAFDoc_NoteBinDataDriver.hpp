#pragma once

#include <XmlMXCAFDoc_NoteDriver.hpp>

class XmlMXCAFDoc_NoteBinDataDriver : public XmlMXCAFDoc_NoteDriver
{
public:
  Standard_EXPORT XmlMXCAFDoc_NoteBinDataDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             XmlObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& theSource,
                             XmlObjMgt_Persistent&             theTarget,
                             XmlObjMgt_SRelocationTable&       theRelocTable) const override;

  DEFINE_STANDARD_RTTIEXT(XmlMXCAFDoc_NoteBinDataDriver, XmlMXCAFDoc_NoteDriver)
};
