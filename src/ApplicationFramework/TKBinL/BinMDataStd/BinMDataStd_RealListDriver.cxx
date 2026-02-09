#include <BinMDataStd_RealListDriver.hpp>
#include <BinMDataStd.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <TDataStd_RealList.hpp>
#include <TDF_Attribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_RealListDriver, BinMDF_ADriver)

BinMDataStd_RealListDriver::BinMDataStd_RealListDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_RealList)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataStd_RealListDriver::NewEmpty() const
{
  return new TDataStd_RealList();
}

bool BinMDataStd_RealListDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       BinObjMgt_RRelocationTable&       theRelocTable) const
{
  int aIndex, aFirstInd, aLastInd;
  if (!(theSource >> aFirstInd >> aLastInd))
    return false;

  const occ::handle<TDataStd_RealList> anAtt = occ::down_cast<TDataStd_RealList>(theTarget);
  if (aLastInd > 0)
  {
    const int aLength = aLastInd - aFirstInd + 1;
    if (aLength > 0)
    {
      NCollection_Array1<double> aTargetArray(aFirstInd, aLastInd);
      theSource.GetRealArray(&aTargetArray(aFirstInd), aLength);
      for (aIndex = aFirstInd; aIndex <= aLastInd; aIndex++)
        anAtt->Append(aTargetArray.Value(aIndex));
    }
  }

  BinMDataStd::SetAttributeID(theSource,
                              anAtt,
                              theRelocTable.GetHeaderData()->StorageVersion().IntegerValue());
  return true;
}

void BinMDataStd_RealListDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  const occ::handle<TDataStd_RealList> anAtt     = occ::down_cast<TDataStd_RealList>(theSource);
  const int                            aFirstInd = (anAtt->Extent() > 0) ? 1 : 0;
  const int                            aLastInd(anAtt->Extent());
  const int                            aLength = aLastInd - aFirstInd + 1;
  if (aLength <= 0)
    return;
  theTarget << aFirstInd << aLastInd;
  if (aLastInd == 0)
    return;
  NCollection_Array1<double> aSourceArray(aFirstInd, aLastInd);
  if (aLastInd >= 1)
  {
    NCollection_List<double>::Iterator itr(anAtt->List());
    for (int i = 1; itr.More(); itr.Next(), i++)
    {
      aSourceArray.SetValue(i, itr.Value());
    }
    double* aPtr = (double*)&aSourceArray(aFirstInd);
    theTarget.PutRealArray(aPtr, aLength);
  }

  if (anAtt->ID() != TDataStd_RealList::GetID())
    theTarget << anAtt->ID();
}
