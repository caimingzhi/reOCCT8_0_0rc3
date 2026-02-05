#include <BinMDataStd.hpp>
#include <BinMDataStd_IntPackedMapDriver.hpp>
#include <BinMDF_ADriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <TDataStd_IntPackedMap.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_FormatVersion.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_IntPackedMapDriver, BinMDF_ADriver)

//=================================================================================================

BinMDataStd_IntPackedMapDriver::BinMDataStd_IntPackedMapDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : BinMDF_ADriver(theMessageDriver, STANDARD_TYPE(TDataStd_IntPackedMap)->Name())
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMDataStd_IntPackedMapDriver::NewEmpty() const
{
  return new TDataStd_IntPackedMap;
}

//=======================================================================
// function : Paste
// purpose  : persistent -> transient (retrieve)
//=======================================================================

bool BinMDataStd_IntPackedMapDriver::Paste(const BinObjMgt_Persistent&       Source,
                                           const occ::handle<TDF_Attribute>& Target,
                                           BinObjMgt_RRelocationTable&       RelocTable) const
{
  occ::handle<TDataStd_IntPackedMap> aTagAtt = occ::down_cast<TDataStd_IntPackedMap>(Target);
  if (aTagAtt.IsNull())
  {
    myMessageDriver->Send("IntPackedMapDriver:: The target attribute is Null.", Message_Fail);
    return false;
  }

  int aSize = 0;
  if (!(Source >> aSize))
  {
    myMessageDriver->Send("Cannot retrieve size for IntPackedMap attribute.", Message_Fail);
    return false;
  }
  if (aSize)
  {
    occ::handle<TColStd_HPackedMapOfInteger> aHMap = new TColStd_HPackedMapOfInteger();
    int                                      aKey;
    for (int i = 0; i < aSize; i++)
    {
      bool ok = Source >> aKey;
      if (!ok)
      {
        myMessageDriver->Send("Cannot retrieve integer member for IntPackedMap attribute.",
                              Message_Fail);
        return false;
      }
      if (!aHMap->ChangeMap().Add(aKey))
        return false;
    }
    aTagAtt->ChangeMap(aHMap);
  }

  bool aDelta(false);
  if (RelocTable.GetHeaderData()->StorageVersion().IntegerValue()
      >= TDocStd_FormatVersion_VERSION_3)
  {
    uint8_t aDeltaValue;
    if (!(Source >> aDeltaValue))
      return false;
    else
      aDelta = (aDeltaValue != 0);
  }
  aTagAtt->SetDelta(aDelta);
  return true;
}

//=======================================================================
// function : Paste
// purpose  : transient -> persistent (store)
//=======================================================================

void BinMDataStd_IntPackedMapDriver::Paste(
  const occ::handle<TDF_Attribute>& Source,
  BinObjMgt_Persistent&             Target,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>& /*RelocTable*/) const
{
  occ::handle<TDataStd_IntPackedMap> anAtt = occ::down_cast<TDataStd_IntPackedMap>(Source);
  if (anAtt.IsNull())
  {
    myMessageDriver->Send("IntPackedMapDriver:: The source attribute is Null.", Message_Fail);
    return;
  }
  int aSize = (anAtt->IsEmpty()) ? 0 : anAtt->Extent();
  Target << aSize;
  if (aSize)
  {
    TColStd_MapIteratorOfPackedMapOfInteger anIt(anAtt->GetMap());
    for (; anIt.More(); anIt.Next())
      Target << anIt.Key();
  }
  Target << (uint8_t)(anAtt->GetDelta() ? 1 : 0);
}
