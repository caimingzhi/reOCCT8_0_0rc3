#include <BinMDataStd.hpp>
#include <BinMDataStd_RealArrayDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_RealArray.hpp>
#include <TDF_Attribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_RealArrayDriver, BinMDF_ADriver)

BinMDataStd_RealArrayDriver::BinMDataStd_RealArrayDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_RealArray)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataStd_RealArrayDriver::NewEmpty() const
{
  return new TDataStd_RealArray();
}

bool BinMDataStd_RealArrayDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                        const occ::handle<TDF_Attribute>& theTarget,
                                        BinObjMgt_RRelocationTable&       theRelocTable) const
{
  int aFirstInd, aLastInd;
  if (!(theSource >> aFirstInd >> aLastInd))
    return false;
  const int aLength = aLastInd - aFirstInd + 1;
  if (aLength <= 0)
    return false;

  const occ::handle<TDataStd_RealArray> anAtt = occ::down_cast<TDataStd_RealArray>(theTarget);
  anAtt->Init(aFirstInd, aLastInd);
  NCollection_Array1<double>& aTargetArray = anAtt->Array()->ChangeArray1();
  if (!theSource.GetRealArray(&aTargetArray(aFirstInd), aLength))
    return false;

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

void BinMDataStd_RealArrayDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataStd_RealArray>   anAtt        = occ::down_cast<TDataStd_RealArray>(theSource);
  const NCollection_Array1<double>& aSourceArray = anAtt->Array()->Array1();
  const int                         aFirstInd    = aSourceArray.Lower();
  const int                         aLastInd     = aSourceArray.Upper();
  const int                         aLength      = aLastInd - aFirstInd + 1;
  theTarget << aFirstInd << aLastInd;
  double* aPtr = (double*)&aSourceArray(aFirstInd);
  theTarget.PutRealArray(aPtr, aLength);
  theTarget << (uint8_t)(anAtt->GetDelta() ? 1 : 0);

  if (anAtt->ID() != TDataStd_RealArray::GetID())
    theTarget << anAtt->ID();
}
