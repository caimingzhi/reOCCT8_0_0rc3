#pragma once

#include <SelectMgr_Filter.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_ShapeEnum.hpp>

class SelectMgr_CompositionFilter : public SelectMgr_Filter
{

public:
  Standard_EXPORT void Add(const occ::handle<SelectMgr_Filter>& afilter);

  Standard_EXPORT void Remove(const occ::handle<SelectMgr_Filter>& aFilter);

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT bool IsIn(const occ::handle<SelectMgr_Filter>& aFilter) const;

  const NCollection_List<occ::handle<SelectMgr_Filter>>& StoredFilters() const { return myFilters; }

  Standard_EXPORT void Clear();

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aStandardMode) const override;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_CompositionFilter, SelectMgr_Filter)

protected:
  NCollection_List<occ::handle<SelectMgr_Filter>> myFilters;
};
