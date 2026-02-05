#include <TObj_Partition.hpp>

#include <TObj_Model.hpp>
#include <TObj_TNameContainer.hpp>

#include <TDataStd_Name.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_Partition, TObj_Object)
IMPLEMENT_TOBJOCAF_PERSISTENCE(TObj_Partition)

//=================================================================================================

TObj_Partition::TObj_Partition(const TDF_Label& theLabel, const bool theSetName)
    : TObj_Object(theLabel, theSetName)
{
}

//=================================================================================================

occ::handle<TObj_Partition> TObj_Partition::Create(const TDF_Label& theLabel, const bool theSetName)
{
  occ::handle<TObj_Partition> aPartition = new TObj_Partition(theLabel, theSetName);
  aPartition->SetLastIndex(0);
  return aPartition;
}

//=================================================================================================

TDF_Label TObj_Partition::NewLabel() const
{
  TDF_Label     aLabel;
  TDF_TagSource aTag;
  aLabel = TDF_TagSource::NewChild(GetChildLabel());
  return aLabel;
}

//=================================================================================================

void TObj_Partition::SetNamePrefix(const occ::handle<TCollection_HExtendedString>& thePrefix)
{
  myPrefix = thePrefix;
}

//=================================================================================================

occ::handle<TCollection_HExtendedString> TObj_Partition::GetNewName(const bool theIsToChangeCount)
{
  if (myPrefix.IsNull())
    return nullptr;

  int                                      aRank    = GetLastIndex() + 1;
  int                                      saveRank = aRank;
  occ::handle<TCollection_HExtendedString> aName;
  do
  {
    aName = new TCollection_HExtendedString(myPrefix->String() + aRank++);
  } while (GetModel()->IsRegisteredName(aName, GetDictionary()));

  // the last index is increased taking into account only names that are
  // actually set; the name requested by the current operation can be
  // dropped later and this will not cause index to be increased
  if (theIsToChangeCount && --aRank > saveRank)
    SetLastIndex(aRank);
  return aName;
}

//=================================================================================================

occ::handle<TObj_Partition> TObj_Partition::GetPartition(const occ::handle<TObj_Object>& theObject)
{
  occ::handle<TObj_Partition> aPartition;
  if (!theObject.IsNull())
  {
    TDF_Label aLabel = theObject->GetLabel().Father();

    // find partition which contains the object
    while (aPartition.IsNull() && !aLabel.IsNull())
    {
      occ::handle<TObj_Object> anObject;
      if (TObj_Object::GetObj(aLabel, anObject, true))
        aPartition = occ::down_cast<TObj_Partition>(anObject);

      if (aPartition.IsNull())
        aLabel = aLabel.Father();
    }
  }
  return aPartition;
}

//=================================================================================================

int TObj_Partition::GetLastIndex() const
{
  return getInteger(DataTag_LastIndex);
}

//=================================================================================================

void TObj_Partition::SetLastIndex(const int theIndex)
{
  setInteger(theIndex, DataTag_LastIndex);
}

//=================================================================================================

bool TObj_Partition::copyData(const occ::handle<TObj_Object>& theTargetObject)
{
  bool                        IsDone;
  occ::handle<TObj_Partition> aTargetPartition = occ::down_cast<TObj_Partition>(theTargetObject);
  IsDone                                       = !aTargetPartition.IsNull();
  if (IsDone)
  {
    IsDone = TObj_Object::copyData(theTargetObject);
    if (IsDone)
    {
      aTargetPartition->myPrefix = myPrefix;
    }
  }
  return IsDone;
}

//=======================================================================
// function : SetName
// purpose  : do not register a name in the dictionary
//=======================================================================

bool TObj_Partition::SetName(const occ::handle<TCollection_HExtendedString>& theName) const
{
  occ::handle<TCollection_HExtendedString> anOldName = GetName();
  if (!anOldName.IsNull() && theName->String().IsEqual(anOldName->String()))
    return true;

  TDataStd_Name::Set(GetLabel(), theName->String());
  return true;
}

//=======================================================================
// function : AfterRetrieval
// purpose  : do not register a name in the dictionary
//=======================================================================

void TObj_Partition::AfterRetrieval() {}
