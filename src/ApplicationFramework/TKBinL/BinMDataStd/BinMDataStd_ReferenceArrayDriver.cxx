#include <BinMDataStd_ReferenceArrayDriver.hpp>
#include <BinMDataStd.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_ReferenceArray.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_ReferenceArrayDriver, BinMDF_ADriver)

BinMDataStd_ReferenceArrayDriver::BinMDataStd_ReferenceArrayDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_ReferenceArray)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataStd_ReferenceArrayDriver::NewEmpty() const
{
  return new TDataStd_ReferenceArray();
}

bool BinMDataStd_ReferenceArrayDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                             const occ::handle<TDF_Attribute>& theTarget,
                                             BinObjMgt_RRelocationTable&       theRelocTable) const
{
  int aFirstInd, aLastInd;
  if (!(theSource >> aFirstInd >> aLastInd))
    return false;
  const int aLength = aLastInd - aFirstInd + 1;
  if (aLength <= 0)
    return false;

  const occ::handle<TDataStd_ReferenceArray> anAtt =
    occ::down_cast<TDataStd_ReferenceArray>(theTarget);
  anAtt->Init(aFirstInd, aLastInd);
  for (int i = aFirstInd; i <= aLastInd; i++)
  {
    TCollection_AsciiString entry;
    if (!(theSource >> entry))
      return false;
    TDF_Label L;
    TDF_Tool::Label(anAtt->Label().Data(), entry, L, true);
    if (!L.IsNull())
      anAtt->SetValue(i, L);
  }

  BinMDataStd::SetAttributeID(theSource,
                              anAtt,
                              theRelocTable.GetHeaderData()->StorageVersion().IntegerValue());
  return true;
}

void BinMDataStd_ReferenceArrayDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataStd_ReferenceArray> anAtt = occ::down_cast<TDataStd_ReferenceArray>(theSource);
  int aFirstInd = anAtt->Lower(), aLastInd = anAtt->Upper(), i = aFirstInd;
  if (aFirstInd > aLastInd)
    return;
  theTarget << aFirstInd << aLastInd;
  for (; i <= aLastInd; i++)
  {
    TDF_Label L = anAtt->Value(i);
    if (!L.IsNull())
    {
      TCollection_AsciiString entry;
      TDF_Tool::Entry(L, entry);
      theTarget << entry;
    }
  }

  if (anAtt->ID() != TDataStd_ReferenceArray::GetID())
    theTarget << anAtt->ID();
}
