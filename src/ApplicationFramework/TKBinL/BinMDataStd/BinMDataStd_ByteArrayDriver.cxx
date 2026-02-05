#include <BinMDataStd.hpp>
#include <BinMDataStd_ByteArrayDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_ByteArray.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_FormatVersion.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_ByteArrayDriver, BinMDF_ADriver)

//=================================================================================================

BinMDataStd_ByteArrayDriver::BinMDataStd_ByteArrayDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_ByteArray)->Name())
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMDataStd_ByteArrayDriver::NewEmpty() const
{
  return new TDataStd_ByteArray();
}

//=======================================================================
// function : Paste
// purpose  : persistent -> transient (retrieve)
//=======================================================================
bool BinMDataStd_ByteArrayDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                        const occ::handle<TDF_Attribute>& theTarget,
                                        BinObjMgt_RRelocationTable&       theRelocTable) const
{
  int aFirstInd, aLastInd;
  if (!(theSource >> aFirstInd >> aLastInd))
    return false;
  if (aLastInd < aFirstInd)
    return false;

  NCollection_Array1<uint8_t> aTargetArray(aFirstInd, aLastInd);
  theSource.GetByteArray(&aTargetArray(aFirstInd), aTargetArray.Length());

  const occ::handle<TDataStd_ByteArray>     anAtt = occ::down_cast<TDataStd_ByteArray>(theTarget);
  occ::handle<NCollection_HArray1<uint8_t>> bytes =
    new NCollection_HArray1<uint8_t>(aFirstInd, aLastInd);
  for (int i = aFirstInd; i <= aLastInd; i++)
  {
    bytes->SetValue(i, aTargetArray.Value(i));
  }
  anAtt->ChangeArray(bytes);

  bool aDelta(false);
  if (theRelocTable.GetHeaderData()->StorageVersion().IntegerValue()
      >= TDocStd_FormatVersion_VERSION_3)
  {
    uint8_t aDeltaValue;
    if (!(theSource >> aDeltaValue))
      return false;
    else
      aDelta = (aDeltaValue != 0);
  }
  anAtt->SetDelta(aDelta);

  BinMDataStd::SetAttributeID(theSource,
                              anAtt,
                              theRelocTable.GetHeaderData()->StorageVersion().IntegerValue());
  return true;
}

//=======================================================================
// function : Paste
// purpose  : transient -> persistent (store)
//=======================================================================
void BinMDataStd_ByteArrayDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataStd_ByteArray> anAtt     = occ::down_cast<TDataStd_ByteArray>(theSource);
  const int                       aFirstInd = anAtt->Lower();
  const int                       aLastInd  = anAtt->Upper();
  if (aLastInd < aFirstInd)
    return;
  theTarget << aFirstInd << aLastInd;

  const occ::handle<NCollection_HArray1<uint8_t>>& bytes = anAtt->InternalArray();
  int                         lower = bytes->Lower(), i = lower, upper = bytes->Upper();
  NCollection_Array1<uint8_t> aSourceArray(lower, upper);
  for (; i <= upper; i++)
  {
    aSourceArray.SetValue(i, bytes->Value(i));
  }
  uint8_t* aPtr = (uint8_t*)&aSourceArray(lower);
  theTarget.PutByteArray(aPtr, bytes->Length());
  theTarget << (uint8_t)(anAtt->GetDelta() ? 1 : 0);

  // process user defined guid
  if (anAtt->ID() != TDataStd_ByteArray::GetID())
    theTarget << anAtt->ID();
}
