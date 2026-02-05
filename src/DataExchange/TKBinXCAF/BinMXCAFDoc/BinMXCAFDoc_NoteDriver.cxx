#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <BinMXCAFDoc_NoteDriver.hpp>
#include <XCAFDoc_Note.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_NoteDriver, BinMDF_ADriver)

//=================================================================================================

BinMXCAFDoc_NoteDriver::BinMXCAFDoc_NoteDriver(const occ::handle<Message_Messenger>& theMsgDriver,
                                               const char*                           theName)
    : BinMDF_ADriver(theMsgDriver, theName)
{
}

//=================================================================================================

bool BinMXCAFDoc_NoteDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                   const occ::handle<TDF_Attribute>& theTarget,
                                   BinObjMgt_RRelocationTable& /*theRelocTable*/) const
{
  occ::handle<XCAFDoc_Note> aNote = occ::down_cast<XCAFDoc_Note>(theTarget);
  if (aNote.IsNull())
    return false;

  TCollection_ExtendedString aUserName, aTimeStamp;
  if (!(theSource >> aUserName >> aTimeStamp))
    return false;

  aNote->Set(aUserName, aTimeStamp);

  return true;
}

//=================================================================================================

void BinMXCAFDoc_NoteDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>& /*theRelocTable*/) const
{
  occ::handle<XCAFDoc_Note> aNote = occ::down_cast<XCAFDoc_Note>(theSource);
  if (!aNote.IsNull())
    theTarget << aNote->UserName() << aNote->TimeStamp();
}
