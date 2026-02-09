#include <BinMDataStd_ReferenceListDriver.hpp>
#include <BinMDataStd.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_ReferenceList.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_ReferenceListDriver, BinMDF_ADriver)

BinMDataStd_ReferenceListDriver::BinMDataStd_ReferenceListDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_ReferenceList)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataStd_ReferenceListDriver::NewEmpty() const
{
  return new TDataStd_ReferenceList();
}

bool BinMDataStd_ReferenceListDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                            const occ::handle<TDF_Attribute>& theTarget,
                                            BinObjMgt_RRelocationTable&       theRelocTable) const
{
  int aFirstInd, aLastInd;
  if (!(theSource >> aFirstInd >> aLastInd))
    return false;

  const occ::handle<TDataStd_ReferenceList> anAtt =
    occ::down_cast<TDataStd_ReferenceList>(theTarget);
  if (aLastInd > 0)
  {

    const int aLength = aLastInd - aFirstInd + 1;
    if (aLength <= 0)
      return false;
    for (int i = aFirstInd; i <= aLastInd; i++)
    {
      TCollection_AsciiString entry;
      if (!(theSource >> entry))
        return false;
      TDF_Label L;
      TDF_Tool::Label(anAtt->Label().Data(), entry, L, true);
      if (!L.IsNull())
        anAtt->Append(L);
    }
  }

  BinMDataStd::SetAttributeID(theSource,
                              anAtt,
                              theRelocTable.GetHeaderData()->StorageVersion().IntegerValue());
  return true;
}

void BinMDataStd_ReferenceListDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  const occ::handle<TDataStd_ReferenceList> anAtt =
    occ::down_cast<TDataStd_ReferenceList>(theSource);
  if (anAtt.IsNull())
    return;
  const int aFirstInd = (anAtt->Extent() > 0) ? 1 : 0;
  const int aLastInd(anAtt->Extent());
  theTarget << aFirstInd << aLastInd;
  if (aLastInd == 0)
    return;
  NCollection_List<TDF_Label>::Iterator itr(anAtt->List());
  for (int i = aFirstInd; itr.More(); itr.Next(), i++)
  {
    TDF_Label L = itr.Value();
    if (!L.IsNull())
    {
      TCollection_AsciiString entry;
      TDF_Tool::Entry(L, entry);
      theTarget << entry;
    }
  }

  if (anAtt->ID() != TDataStd_ReferenceList::GetID())
    theTarget << anAtt->ID();
}
