#include <SelectMgr_CompositionFilter.hpp>
#include <SelectMgr_Filter.hpp>
#include <NCollection_List.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_CompositionFilter, SelectMgr_Filter)

void SelectMgr_CompositionFilter::Add(const occ::handle<SelectMgr_Filter>& afilter)
{
  myFilters.Append(afilter);
}

void SelectMgr_CompositionFilter::Remove(const occ::handle<SelectMgr_Filter>& afilter)
{
  NCollection_List<occ::handle<SelectMgr_Filter>>::Iterator It(myFilters);
  for (; It.More(); It.Next())
  {
    if (afilter == It.Value())
    {
      myFilters.Remove(It);
      return;
    }
  }
}

bool SelectMgr_CompositionFilter::IsEmpty() const
{
  return myFilters.IsEmpty();
}

bool SelectMgr_CompositionFilter::IsIn(const occ::handle<SelectMgr_Filter>& afilter) const
{
  NCollection_List<occ::handle<SelectMgr_Filter>>::Iterator It(myFilters);
  for (; It.More(); It.Next())
    if (afilter == It.Value())
      return true;
  return false;
}

void SelectMgr_CompositionFilter::Clear()
{
  myFilters.Clear();
}

bool SelectMgr_CompositionFilter::ActsOn(const TopAbs_ShapeEnum aStandardMode) const
{
  NCollection_List<occ::handle<SelectMgr_Filter>>::Iterator It(myFilters);
  for (; It.More(); It.Next())
  {
    if (It.Value()->ActsOn(aStandardMode))
      return true;
  }

  return false;
}
