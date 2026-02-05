#include <BinTObjDrivers_IntSparseArrayDriver.hpp>
#include <Message_Messenger.hpp>
#include <TDF_Attribute.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <TObj_TIntSparseArray.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinTObjDrivers_IntSparseArrayDriver, BinMDF_ADriver)

//=================================================================================================

BinTObjDrivers_IntSparseArrayDriver::BinTObjDrivers_IntSparseArrayDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : BinMDF_ADriver(theMessageDriver, nullptr)
{
}

//=======================================================================
// function : NewEmpty
// purpose  : Creates a new attribute
//=======================================================================

occ::handle<TDF_Attribute> BinTObjDrivers_IntSparseArrayDriver::NewEmpty() const
{
  return new TObj_TIntSparseArray;
}

//=======================================================================
// function : Paste
// purpose  : Retrieve. Translate the contents of <theSource> and put it
//           into <theTarget>.
//=======================================================================

bool BinTObjDrivers_IntSparseArrayDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                                const occ::handle<TDF_Attribute>& theTarget,
                                                BinObjMgt_RRelocationTable&) const
{
  occ::handle<TObj_TIntSparseArray> aTarget = occ::down_cast<TObj_TIntSparseArray>(theTarget);

  // get pairs (ID, value) while ID != 0
  int anId;
  if (!(theSource >> anId) || anId < 0)
    return false;
  while (anId)
  {
    int aValue;
    if (!(theSource >> aValue) || aValue <= 0)
      return false;

    // store the value in the target array
    aTarget->SetDoBackup(false);
    aTarget->SetValue(anId, aValue);
    aTarget->SetDoBackup(true);

    // get next ID
    if (!(theSource >> anId) || anId < 0)
      return false;
  }
  return true;
}

//=======================================================================
// function : Paste
// purpose  : Store. Translate the contents of <theSource> and put it
//           into <theTarget>
//=======================================================================

void BinTObjDrivers_IntSparseArrayDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TObj_TIntSparseArray> aSource = occ::down_cast<TObj_TIntSparseArray>(theSource);

  // put only non-null values as pairs (ID, value)
  // terminate the list by ID=0
  TObj_TIntSparseArray::Iterator anIt = aSource->GetIterator();
  for (; anIt.More(); anIt.Next())
  {
    int aValue = anIt.Value();
    if (aValue == 0)
      continue;

    // store ID and value
    theTarget << (int)anIt.Index() << aValue;
  }
  // zero indicates end of the entities
  theTarget << (int)0;
}
