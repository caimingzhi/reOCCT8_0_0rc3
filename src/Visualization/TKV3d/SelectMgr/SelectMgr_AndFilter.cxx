

#include <SelectMgr_AndFilter.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Filter.hpp>
#include <NCollection_List.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_AndFilter, SelectMgr_CompositionFilter)

SelectMgr_AndFilter::SelectMgr_AndFilter() = default;

bool SelectMgr_AndFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const
{
  NCollection_List<occ::handle<SelectMgr_Filter>>::Iterator it(myFilters);
  for (; it.More(); it.Next())
    if (!it.Value()->IsOk(anobj))
      return false;
  return true;
}
