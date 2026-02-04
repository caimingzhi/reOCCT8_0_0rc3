#pragma once


#include <XmlMXCAFDoc_NoteDriver.hpp>

//! Attribute Driver.
class XmlMXCAFDoc_NoteCommentDriver : public XmlMXCAFDoc_NoteDriver
{
public:
  Standard_EXPORT XmlMXCAFDoc_NoteCommentDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             XmlObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& theSource,
                             XmlObjMgt_Persistent&             theTarget,
                             XmlObjMgt_SRelocationTable&       theRelocTable) const override;

  DEFINE_STANDARD_RTTIEXT(XmlMXCAFDoc_NoteCommentDriver, XmlMXCAFDoc_NoteDriver)

protected:
  XmlMXCAFDoc_NoteCommentDriver(const occ::handle<Message_Messenger>& theMsgDriver,
                                const char*                           theName);
};

