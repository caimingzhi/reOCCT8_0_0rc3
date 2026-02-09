#include <BinMDataStd_ExtStringListDriver.hpp>
#include <BinMDataStd.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_Array1.hpp>
#include <TDataStd_ExtStringList.hpp>
#include <NCollection_List.hpp>
#include <TDF_Attribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_ExtStringListDriver, BinMDF_ADriver)

BinMDataStd_ExtStringListDriver::BinMDataStd_ExtStringListDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_ExtStringList)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataStd_ExtStringListDriver::NewEmpty() const
{
  return new TDataStd_ExtStringList();
}

bool BinMDataStd_ExtStringListDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                            const occ::handle<TDF_Attribute>& theTarget,
                                            BinObjMgt_RRelocationTable&       theRelocTable) const
{
  int aFirstInd, aLastInd;
  if (!(theSource >> aFirstInd >> aLastInd))
    return false;

  const occ::handle<TDataStd_ExtStringList> anAtt =
    occ::down_cast<TDataStd_ExtStringList>(theTarget);
  if (aLastInd > 0)
  {
    const int aLength = aLastInd - aFirstInd + 1;
    if (aLength <= 0)
      return false;
    for (int i = aFirstInd; i <= aLastInd; i++)
    {
      TCollection_ExtendedString aStr;
      if (!(theSource >> aStr))
      {
        return false;
      }
      anAtt->Append(aStr);
    }
  }

  BinMDataStd::SetAttributeID(theSource,
                              anAtt,
                              theRelocTable.GetHeaderData()->StorageVersion().IntegerValue());
  return true;
}

void BinMDataStd_ExtStringListDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  const occ::handle<TDataStd_ExtStringList> anAtt =
    occ::down_cast<TDataStd_ExtStringList>(theSource);
  const int aFirstInd = (anAtt->Extent() > 0) ? 1 : 0;
  const int aLastInd(anAtt->Extent());
  theTarget << aFirstInd << aLastInd;
  NCollection_List<TCollection_ExtendedString>::Iterator itr(anAtt->List());
  for (; itr.More(); itr.Next())
  {
    theTarget << itr.Value();
  }

  if (anAtt->ID() != TDataStd_ExtStringList::GetID())
    theTarget << anAtt->ID();
}
