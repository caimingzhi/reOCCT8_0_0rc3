#include <SelectMgr_Selection.hpp>

#include <SelectMgr_EntityOwner.hpp>
#include <Standard_NullObject.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_Selection, Standard_Transient)

SelectMgr_Selection::SelectMgr_Selection(const int theModeIdx)
    : myMode(theModeIdx),
      mySelectionState(SelectMgr_SOS_Unknown),
      myBVHUpdateStatus(SelectMgr_TBU_None),
      mySensFactor(2),
      myIsCustomSens(false)
{
}

SelectMgr_Selection::~SelectMgr_Selection()
{
  Destroy();
}

void SelectMgr_Selection::Destroy()
{
  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator anEntityIter(
         myEntities);
       anEntityIter.More();
       anEntityIter.Next())
  {
    occ::handle<SelectMgr_SensitiveEntity>& anEntity = anEntityIter.ChangeValue();
    anEntity->BaseSensitive()->Set(nullptr);
  }
  mySensFactor = 2;
}

void SelectMgr_Selection::Add(const occ::handle<Select3D_SensitiveEntity>& theSensitive)
{

  Standard_NullObject_Raise_if(theSensitive.IsNull(),
                               "Null sensitive entity is added to the selection");
  if (theSensitive.IsNull())
  {

    return;
  }

  occ::handle<SelectMgr_SensitiveEntity> anEntity = new SelectMgr_SensitiveEntity(theSensitive);
  myEntities.Append(anEntity);
  if (mySelectionState == SelectMgr_SOS_Activated && !anEntity->IsActiveForSelection())
  {
    anEntity->SetActiveForSelection();
  }

  if (myIsCustomSens)
  {
    anEntity->BaseSensitive()->SetSensitivityFactor(mySensFactor);
  }
  else
  {
    mySensFactor = std::max(mySensFactor, anEntity->BaseSensitive()->SensitivityFactor());
  }
}

void SelectMgr_Selection::Clear()
{
  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator anEntityIter(
         myEntities);
       anEntityIter.More();
       anEntityIter.Next())
  {
    occ::handle<SelectMgr_SensitiveEntity>& anEntity = anEntityIter.ChangeValue();
    anEntity->Clear();
  }

  myEntities.Clear();
}

void SelectMgr_Selection::SetSensitivity(const int theNewSens)
{
  mySensFactor   = theNewSens;
  myIsCustomSens = true;
  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator anEntityIter(
         myEntities);
       anEntityIter.More();
       anEntityIter.Next())
  {
    occ::handle<SelectMgr_SensitiveEntity>& anEntity = anEntityIter.ChangeValue();
    anEntity->BaseSensitive()->SetSensitivityFactor(theNewSens);
  }
}

void SelectMgr_Selection::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  NCollection_Map<occ::handle<SelectMgr_EntityOwner>> anOwners;
  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator anIterator(myEntities);
       anIterator.More();
       anIterator.Next())
  {
    const occ::handle<SelectMgr_SensitiveEntity>& anEntity = anIterator.Value();
    if (anEntity.IsNull() || anEntity->BaseSensitive().IsNull())
    {
      continue;
    }
    const occ::handle<SelectMgr_EntityOwner>& anOwner = anEntity->BaseSensitive()->OwnerId();
    if (anOwners.Add(anOwner))
    {
      OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, anOwner.get())
    }
  }

  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator anIterator(myEntities);
       anIterator.More();
       anIterator.Next())
  {
    const occ::handle<SelectMgr_SensitiveEntity>& anEntity = anIterator.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, anEntity.get())
  }

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myMode)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySelectionState)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySensFactor)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myUpdateStatus)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myBVHUpdateStatus)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsCustomSens)
}
