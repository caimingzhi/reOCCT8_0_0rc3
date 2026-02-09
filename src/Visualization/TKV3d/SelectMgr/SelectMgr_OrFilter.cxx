

#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_OrFilter.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_OrFilter, SelectMgr_CompositionFilter)

SelectMgr_OrFilter::SelectMgr_OrFilter() = default;

bool SelectMgr_OrFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& theObj) const
{
  if (myFilters.IsEmpty())
  {
    return true;
  }

  for (NCollection_List<occ::handle<SelectMgr_Filter>>::Iterator aFilterIter(myFilters);
       aFilterIter.More();
       aFilterIter.Next())
  {
    if (aFilterIter.Value()->IsOk(theObj))
    {
      return true;
    }
  }

  return false;
}
