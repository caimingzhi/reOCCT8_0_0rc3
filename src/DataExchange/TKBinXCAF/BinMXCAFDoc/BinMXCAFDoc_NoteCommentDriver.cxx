#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <BinMXCAFDoc_NoteCommentDriver.hpp>
#include <XCAFDoc_NoteComment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_NoteCommentDriver, BinMXCAFDoc_NoteDriver)

//=================================================================================================

BinMXCAFDoc_NoteCommentDriver::BinMXCAFDoc_NoteCommentDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMXCAFDoc_NoteDriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_NoteComment)->Name())
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMXCAFDoc_NoteCommentDriver::NewEmpty() const
{
  return new XCAFDoc_NoteComment();
}

//=================================================================================================

bool BinMXCAFDoc_NoteCommentDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                          const occ::handle<TDF_Attribute>& theTarget,
                                          BinObjMgt_RRelocationTable&       theRelocTable) const
{
  if (!BinMXCAFDoc_NoteDriver::Paste(theSource, theTarget, theRelocTable))
    return false;

  occ::handle<XCAFDoc_NoteComment> aNote = occ::down_cast<XCAFDoc_NoteComment>(theTarget);
  if (aNote.IsNull())
    return false;

  TCollection_ExtendedString aComment;
  if (!(theSource >> aComment))
    return false;

  aNote->Set(aComment);

  return true;
}

//=================================================================================================

void BinMXCAFDoc_NoteCommentDriver::Paste(
  const occ::handle<TDF_Attribute>&                        theSource,
  BinObjMgt_Persistent&                                    theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const
{
  BinMXCAFDoc_NoteDriver::Paste(theSource, theTarget, theRelocTable);

  occ::handle<XCAFDoc_NoteComment> aNote = occ::down_cast<XCAFDoc_NoteComment>(theSource);
  if (!aNote.IsNull())
    theTarget << aNote->Comment();
}

//=================================================================================================

BinMXCAFDoc_NoteCommentDriver::BinMXCAFDoc_NoteCommentDriver(
  const occ::handle<Message_Messenger>& theMsgDriver,
  const char*                           theName)
    : BinMXCAFDoc_NoteDriver(theMsgDriver, theName)
{
}
