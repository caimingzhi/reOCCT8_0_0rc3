#pragma once


#include <SelectMgr_Filter.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_ShapeEnum.hpp>

//! A framework to define a compound filter composed of
//! two or more simple filters.
class SelectMgr_CompositionFilter : public SelectMgr_Filter
{

public:
  //! Adds the filter afilter to a filter object created by a
  //! filter class inheriting this framework.
  Standard_EXPORT void Add(const occ::handle<SelectMgr_Filter>& afilter);

  //! Removes the filter aFilter from this framework.
  Standard_EXPORT void Remove(const occ::handle<SelectMgr_Filter>& aFilter);

  //! Returns true if this framework is empty.
  Standard_EXPORT bool IsEmpty() const;

  //! Returns true if the filter aFilter is in this framework.
  Standard_EXPORT bool IsIn(const occ::handle<SelectMgr_Filter>& aFilter) const;

  //! Returns the list of stored filters from this framework.
  const NCollection_List<occ::handle<SelectMgr_Filter>>& StoredFilters() const { return myFilters; }

  //! Clears the filters used in this framework.
  Standard_EXPORT void Clear();

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aStandardMode) const override;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_CompositionFilter, SelectMgr_Filter)

protected:
  NCollection_List<occ::handle<SelectMgr_Filter>> myFilters;
};

