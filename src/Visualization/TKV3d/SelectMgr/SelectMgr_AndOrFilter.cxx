

#include <SelectMgr_AndOrFilter.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Filter.hpp>
#include <NCollection_List.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_AndOrFilter, SelectMgr_CompositionFilter)

SelectMgr_AndOrFilter::SelectMgr_AndOrFilter(const SelectMgr_FilterType theFilterType)
    : myFilterType(theFilterType)
{
}

void SelectMgr_AndOrFilter::SetDisabledObjects(
  const occ::handle<NCollection_Shared<NCollection_Map<const Standard_Transient*>>>& theObjects)
{
  myDisabledObjects = theObjects;
}

bool SelectMgr_AndOrFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& theObj) const
{
  const SelectMgr_SelectableObject* aSelectable = theObj->Selectable().operator->();
  if (!myDisabledObjects.IsNull() && myDisabledObjects->Contains(aSelectable))
  {
    return false;
  }

  for (NCollection_List<occ::handle<SelectMgr_Filter>>::Iterator anIter(myFilters); anIter.More();
       anIter.Next())
  {
    bool isOK = anIter.Value()->IsOk(theObj);
    if (isOK && myFilterType == SelectMgr_FilterType_OR)
    {
      return true;
    }
    else if (!isOK && myFilterType == SelectMgr_FilterType_AND)
    {
      return false;
    }
  }

  return myFilterType != SelectMgr_FilterType_OR || myFilters.IsEmpty();
}
