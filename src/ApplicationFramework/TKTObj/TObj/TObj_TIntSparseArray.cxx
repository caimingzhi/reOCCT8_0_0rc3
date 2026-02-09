#include <TObj_TIntSparseArray.hpp>
#include <Standard_GUID.hpp>
#include <Standard_ImmutableObject.hpp>
#include <TDF_Data.hpp>
#include <TDF_DeltaOnModification.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_TIntSparseArray, TDF_Attribute)

TObj_TIntSparseArray::TObj_TIntSparseArray()
    : myVector(100),
      myOldMap(100),
      myDoBackup(true)
{
}

const Standard_GUID& TObj_TIntSparseArray::GetID()
{
  static Standard_GUID GInterfaceID("7016dc0c-b118-4433-8ef3-aecdccc79198");
  return GInterfaceID;
}

const Standard_GUID& TObj_TIntSparseArray::ID() const
{
  return GetID();
}

occ::handle<TObj_TIntSparseArray> TObj_TIntSparseArray::Set(const TDF_Label& theLabel)
{
  occ::handle<TObj_TIntSparseArray> aTData;
  if (!theLabel.FindAttribute(GetID(), aTData))
  {
    aTData = new TObj_TIntSparseArray;
    theLabel.AddAttribute(aTData);
  }
  return aTData;
}

void TObj_TIntSparseArray::SetValue(const size_t theId, const int theValue)
{

  if (!Label().Data()->IsModificationAllowed())
    throw Standard_ImmutableObject("Attribute TObj_TIntSparseArray is changed outside transaction");

  if (theId < 1 || theValue < 1)
    throw Standard_OutOfRange("TObj_TIntSparseArray::SetValue");

  int  anOld = AbsentValue;
  bool isOld = myVector.HasValue(theId);
  if (isOld)
  {
    int& aData = myVector(theId);
    if (aData == theValue)

      return;
    anOld = aData;

    aData = theValue;
  }
  else
  {

    myVector.SetValue(theId, theValue);
  }

  TDF_Label aLabel = Label();
  if (!aLabel.IsNull())
  {
    occ::handle<TDF_Data> aData               = aLabel.Data();
    int                   aCurrentTransaction = aData->Transaction();
    int                   aMyTransaction      = Transaction();

    if (myDoBackup && aMyTransaction < aCurrentTransaction)
      backupValue(theId, anOld, theValue);
  }
}

void TObj_TIntSparseArray::UnsetValue(const size_t theId)
{

  if (!Label().Data()->IsModificationAllowed())
    throw Standard_ImmutableObject("Attribute TObj_TIntSparseArray is changed outside transaction");

  if (theId < 1)
    throw Standard_OutOfRange("TObj_TIntSparseArray::UnsetValue");

  int  anOld = AbsentValue;
  bool isOld = myVector.HasValue(theId);
  if (isOld)
  {
    anOld = myVector(theId);

    myVector.UnsetValue(theId);
  }
  else

    return;

  TDF_Label aLabel = Label();
  if (!aLabel.IsNull())
  {
    occ::handle<TDF_Data> aData               = aLabel.Data();
    int                   aCurrentTransaction = aData->Transaction();
    int                   aMyTransaction      = Transaction();

    if (myDoBackup && aMyTransaction < aCurrentTransaction)
      backupValue(theId, anOld, AbsentValue);
  }
}

void TObj_TIntSparseArray::Clear()
{

  TDF_Label aLabel = Label();
  if (!aLabel.IsNull())
  {
    occ::handle<TDF_Data> aData               = aLabel.Data();
    int                   aCurrentTransaction = aData->Transaction();
    int                   aMyTransaction      = Transaction();

    if (myDoBackup && aMyTransaction < aCurrentTransaction)
    {
      NCollection_SparseArray<int>::Iterator anIt(myVector);
      for (; anIt.More(); anIt.Next())
      {
        size_t anId = anIt.Key();
        int    aVal = anIt.Value();
        backupValue(anId, aVal, AbsentValue);
      }
    }
  }
  myVector.Clear();
}

void TObj_TIntSparseArray::backupValue(const size_t theId,
                                       const int    theCurrValue,
                                       const int    theNewValue)
{

  if (!myOldMap.IsBound(theId))
    myOldMap.Bind(theId, theCurrValue);
  else
  {

    int aUData = myOldMap.Value(theId);
    if (aUData == theNewValue)
      myOldMap.UnBind(theId);
  }
}

occ::handle<TDF_Attribute> TObj_TIntSparseArray::NewEmpty() const
{
  return new TObj_TIntSparseArray;
}

occ::handle<TDF_Attribute> TObj_TIntSparseArray::BackupCopy() const
{
  occ::handle<TObj_TIntSparseArray> aCopy = occ::down_cast<TObj_TIntSparseArray>(NewEmpty());

  if (!myOldMap.IsEmpty())
    aCopy->myOldMap.Exchange((NCollection_SparseArray<int>&)myOldMap);

  return aCopy;
}

void TObj_TIntSparseArray::Restore(const occ::handle<TDF_Attribute>& theDelta)
{
  occ::handle<TObj_TIntSparseArray> aDelta = occ::down_cast<TObj_TIntSparseArray>(theDelta);
  if (aDelta.IsNull())
    return;

  if (!aDelta->myOldMap.IsEmpty())
  {
    NCollection_SparseArray<int>::Iterator anIt(aDelta->myOldMap);
    for (; anIt.More(); anIt.Next())
    {
      size_t anId  = anIt.Key();
      int    anOld = anIt.Value();
      if (anOld == AbsentValue)
        UnsetValue(anId);
      else
        SetValue(anId, anOld);
    }
  }
}

void TObj_TIntSparseArray::Paste(const occ::handle<TDF_Attribute>& theInto,
                                 const occ::handle<TDF_RelocationTable>&) const
{
  occ::handle<TObj_TIntSparseArray> aInto = occ::down_cast<TObj_TIntSparseArray>(theInto);
  if (aInto.IsNull())
    return;

  aInto->myVector.Assign(myVector);
}

void TObj_TIntSparseArray::BeforeCommitTransaction()
{
  if (!myOldMap.IsEmpty())
  {
    Backup();
    ClearDelta();
  }
}

void TObj_TIntSparseArray::DeltaOnModification(const occ::handle<TDF_DeltaOnModification>& theDelta)
{

  Restore(theDelta->Attribute());
}

bool TObj_TIntSparseArray::AfterUndo(const occ::handle<TDF_AttributeDelta>&, const bool)
{

  ClearDelta();
  return true;
}
