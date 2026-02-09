#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <XCAFDoc_NoteComment.hpp>
#include <XmlMXCAFDoc_NoteCommentDriver.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMXCAFDoc_NoteCommentDriver, XmlMXCAFDoc_NoteDriver)
IMPLEMENT_DOMSTRING(Comment, "comment")

XmlMXCAFDoc_NoteCommentDriver::XmlMXCAFDoc_NoteCommentDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMXCAFDoc_NoteDriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_NoteComment)->Name())
{
}

occ::handle<TDF_Attribute> XmlMXCAFDoc_NoteCommentDriver::NewEmpty() const
{
  return new XCAFDoc_NoteComment();
}

bool XmlMXCAFDoc_NoteCommentDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                          const occ::handle<TDF_Attribute>& theTarget,
                                          XmlObjMgt_RRelocationTable&       theRelocTable) const
{
  XmlMXCAFDoc_NoteDriver::Paste(theSource, theTarget, theRelocTable);

  const XmlObjMgt_Element& anElement = theSource;

  XmlObjMgt_DOMString aComment = anElement.getAttribute(::Comment());
  if (aComment == nullptr)
    return false;

  occ::handle<XCAFDoc_NoteComment> aNote = occ::down_cast<XCAFDoc_NoteComment>(theTarget);
  if (aNote.IsNull())
    return false;

  aNote->Set(aComment.GetString());

  return true;
}

void XmlMXCAFDoc_NoteCommentDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                          XmlObjMgt_Persistent&             theTarget,
                                          XmlObjMgt_SRelocationTable&       theRelocTable) const
{
  XmlMXCAFDoc_NoteDriver::Paste(theSource, theTarget, theRelocTable);

  occ::handle<XCAFDoc_NoteComment> aNote = occ::down_cast<XCAFDoc_NoteComment>(theSource);

  XmlObjMgt_DOMString aComment(TCollection_AsciiString(aNote->TimeStamp()).ToCString());

  theTarget.Element().setAttribute(::Comment(), aComment);
}

XmlMXCAFDoc_NoteCommentDriver::XmlMXCAFDoc_NoteCommentDriver(
  const occ::handle<Message_Messenger>& theMsgDriver,
  const char*                           theName)
    : XmlMXCAFDoc_NoteDriver(theMsgDriver, theName)
{
}
