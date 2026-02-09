#include <BinTObjDrivers_IntSparseArrayDriver.hpp>
#include <Message_Messenger.hpp>
#include <TDF_Attribute.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <TObj_TIntSparseArray.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinTObjDrivers_IntSparseArrayDriver, BinMDF_ADriver)

BinTObjDrivers_IntSparseArrayDriver::BinTObjDrivers_IntSparseArrayDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : BinMDF_ADriver(theMessageDriver, nullptr)
{
}

occ::handle<TDF_Attribute> BinTObjDrivers_IntSparseArrayDriver::NewEmpty() const
{
  return new TObj_TIntSparseArray;
}

bool BinTObjDrivers_IntSparseArrayDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                                const occ::handle<TDF_Attribute>& theTarget,
                                                BinObjMgt_RRelocationTable&) const
{
  occ::handle<TObj_TIntSparseArray> aTarget = occ::down_cast<TObj_TIntSparseArray>(theTarget);

  int anId;
  if (!(theSource >> anId) || anId < 0)
    return false;
  while (anId)
  {
    int aValue;
    if (!(theSource >> aValue) || aValue <= 0)
      return false;

    aTarget->SetDoBackup(false);
    aTarget->SetValue(anId, aValue);
    aTarget->SetDoBackup(true);

    if (!(theSource >> anId) || anId < 0)
      return false;
  }
  return true;
}

void BinTObjDrivers_IntSparseArrayDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TObj_TIntSparseArray> aSource = occ::down_cast<TObj_TIntSparseArray>(theSource);

  TObj_TIntSparseArray::Iterator anIt = aSource->GetIterator();
  for (; anIt.More(); anIt.Next())
  {
    int aValue = anIt.Value();
    if (aValue == 0)
      continue;

    theTarget << (int)anIt.Index() << aValue;
  }

  theTarget << (int)0;
}
