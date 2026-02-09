

#include <AIS_Selection.hpp>

#include <AIS_InteractiveObject.hpp>
#include <AIS_SelectionScheme.hpp>
#include <SelectMgr_Filter.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_Selection, Standard_Transient)

namespace
{
  constexpr int THE_MaxSizeOfResult = 100000;
}

AIS_Selection::AIS_Selection()
{

  myResultMap.ReSize(THE_MaxSizeOfResult);
}

void AIS_Selection::Clear()
{
  for (NCollection_List<occ::handle<SelectMgr_EntityOwner>>::Iterator aSelIter(Objects());
       aSelIter.More();
       aSelIter.Next())
  {
    const occ::handle<SelectMgr_EntityOwner> anObject = aSelIter.Value();
    anObject->SetSelected(false);
  }
  myresult.Clear();
  myResultMap.Clear();
  myIterator = NCollection_List<occ::handle<SelectMgr_EntityOwner>>::Iterator();
}

AIS_SelectStatus AIS_Selection::Select(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                       const occ::handle<SelectMgr_Filter>&      theFilter,
                                       const AIS_SelectionScheme                 theSelScheme,
                                       const bool                                theIsDetected)
{
  if (theOwner.IsNull() || !theOwner->HasSelectable())
  {
    return AIS_SS_NotDone;
  }

  const bool isDetected = theIsDetected && (theFilter.IsNull() || theFilter->IsOk(theOwner));

  const bool wasSelected = theOwner->IsSelected();
  const bool toSelect    = theOwner->Select(theSelScheme, isDetected);

  if (!wasSelected || !myResultMap.IsBound(theOwner))
  {
    if (!toSelect)
      return AIS_SS_NotDone;

    NCollection_List<occ::handle<SelectMgr_EntityOwner>>::Iterator aListIter;
    myresult.Append(theOwner, aListIter);
    myResultMap.Bind(theOwner, aListIter);
    theOwner->SetSelected(true);
    return AIS_SS_Added;
  }

  NCollection_List<occ::handle<SelectMgr_EntityOwner>>::Iterator aListIter =
    myResultMap.Find(theOwner);
  if (myIterator == aListIter)
  {
    if (myIterator.More())
    {
      myIterator.Next();
    }
    else
    {
      myIterator = NCollection_List<occ::handle<SelectMgr_EntityOwner>>::Iterator();
    }
  }

  if (theOwner->IsForcedHilight())
  {
    return AIS_SS_Added;
  }

  myresult.Remove(aListIter);
  myResultMap.UnBind(theOwner);
  theOwner->SetSelected(false);

  if (aListIter.More())
  {
    const occ::handle<SelectMgr_EntityOwner>& aNextObject = aListIter.Value();
    if (myResultMap.IsBound(aNextObject))
    {
      myResultMap(aNextObject) = aListIter;
    }
    else
    {
      myResultMap.Bind(aNextObject, aListIter);
    }
  }
  return AIS_SS_Removed;
}

AIS_SelectStatus AIS_Selection::AddSelect(const occ::handle<SelectMgr_EntityOwner>& theObject)
{
  if (theObject.IsNull() || !theObject->HasSelectable() || myResultMap.IsBound(theObject))
  {
    return AIS_SS_NotDone;
  }

  NCollection_List<occ::handle<SelectMgr_EntityOwner>>::Iterator aListIter;
  myresult.Append(theObject, aListIter);
  myResultMap.Bind(theObject, aListIter);
  theObject->SetSelected(true);
  return AIS_SS_Added;
}

void AIS_Selection::SelectOwners(
  const NCollection_Array1<occ::handle<SelectMgr_EntityOwner>>& thePickedOwners,
  const AIS_SelectionScheme                                     theSelScheme,
  const bool                                                    theToAllowSelOverlap,
  const occ::handle<SelectMgr_Filter>&                          theFilter)
{
  (void)theToAllowSelOverlap;

  if (theSelScheme == AIS_SelectionScheme_ReplaceExtra && thePickedOwners.Size() == myresult.Size())
  {

    bool isTheSame = true;
    for (NCollection_Array1<occ::handle<SelectMgr_EntityOwner>>::Iterator aPickedIter(
           thePickedOwners);
         aPickedIter.More();
         aPickedIter.Next())
    {
      if (!myResultMap.IsBound(aPickedIter.Value()))
      {
        isTheSame = false;
        break;
      }
    }
    if (isTheSame)
    {
      Clear();
      return;
    }
  }

  if (theSelScheme == AIS_SelectionScheme_Replace
      || theSelScheme == AIS_SelectionScheme_ReplaceExtra
      || theSelScheme == AIS_SelectionScheme_Clear)
  {
    Clear();
  }

  for (NCollection_Array1<occ::handle<SelectMgr_EntityOwner>>::Iterator aPickedIter(
         thePickedOwners);
       aPickedIter.More();
       aPickedIter.Next())
  {
    const occ::handle<SelectMgr_EntityOwner>& anOwner = aPickedIter.Value();
    Select(anOwner, theFilter, theSelScheme, true);
  }
}

AIS_SelectStatus AIS_Selection::appendOwner(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                            const occ::handle<SelectMgr_Filter>&      theFilter)
{
  if (theOwner.IsNull() || !theOwner->HasSelectable() || !theFilter->IsOk(theOwner))
  {
    return AIS_SS_NotDone;
  }

  return AddSelect(theOwner);
}
