#include <BinMDataStd.hpp>
#include <BinMDataStd_ExtStringArrayDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_ExtStringArray.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_FormatVersion.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_ExtStringArrayDriver, BinMDF_ADriver)

BinMDataStd_ExtStringArrayDriver::BinMDataStd_ExtStringArrayDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_ExtStringArray)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataStd_ExtStringArrayDriver::NewEmpty() const
{
  return new TDataStd_ExtStringArray();
}

bool BinMDataStd_ExtStringArrayDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                             const occ::handle<TDF_Attribute>& theTarget,
                                             BinObjMgt_RRelocationTable&       theRelocTable) const
{
  int aFirstInd, aLastInd;
  if (!(theSource >> aFirstInd >> aLastInd))
    return false;
  const int aLength = aLastInd - aFirstInd + 1;
  if (aLength <= 0)
    return false;

  occ::handle<TDataStd_ExtStringArray> anAtt = occ::down_cast<TDataStd_ExtStringArray>(theTarget);
  anAtt->Init(aFirstInd, aLastInd);
  NCollection_Array1<TCollection_ExtendedString>& aTargetArray = anAtt->Array()->ChangeArray1();
  bool                                            ok           = true;
  for (int i = aFirstInd; i <= aLastInd; i++)
  {
    TCollection_ExtendedString aStr;
    if (!(theSource >> aStr))
    {
      ok = false;
      break;
    }
    aTargetArray.SetValue(i, aStr);
  }

  if (ok)
  {
    bool aDelta(false);
    if (theRelocTable.GetHeaderData()->StorageVersion().IntegerValue()
        >= TDocStd_FormatVersion_VERSION_3)
    {
      uint8_t aDeltaValue;
      if (!(theSource >> aDeltaValue))
      {
        return false;
      }
      else
        aDelta = (aDeltaValue != 0);
    }
    anAtt->SetDelta(aDelta);
  }

  BinMDataStd::SetAttributeID(theSource,
                              anAtt,
                              theRelocTable.GetHeaderData()->StorageVersion().IntegerValue());
  return ok;
}

void BinMDataStd_ExtStringArrayDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  const occ::handle<TDataStd_ExtStringArray> anAtt =
    occ::down_cast<TDataStd_ExtStringArray>(theSource);
  const NCollection_Array1<TCollection_ExtendedString>& aSourceArray = anAtt->Array()->Array1();
  const int                                             aFirstInd    = aSourceArray.Lower();
  const int                                             aLastInd     = aSourceArray.Upper();
  theTarget << aFirstInd << aLastInd;
  for (int i = aFirstInd; i <= aLastInd; i++)
    theTarget << anAtt->Value(i);

  theTarget << (uint8_t)(anAtt->GetDelta() ? 1 : 0);

  if (anAtt->ID() != TDataStd_ExtStringArray::GetID())
    theTarget << anAtt->ID();
}
