#pragma once

#include <TopAbs_ShapeEnum.hpp>
#include <SelectMgr_Filter.hpp>

class SelectMgr_EntityOwner;

//! A filter framework which allows you to define a filter for a specific shape type.
class StdSelect_ShapeTypeFilter : public SelectMgr_Filter
{
  DEFINE_STANDARD_RTTIEXT(StdSelect_ShapeTypeFilter, SelectMgr_Filter)
public:
  //! Constructs a filter object defined by the shape type aType.
  Standard_EXPORT StdSelect_ShapeTypeFilter(const TopAbs_ShapeEnum aType);

  //! Returns the type of shape selected by the filter.
  TopAbs_ShapeEnum Type() const { return myType; }

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aStandardMode) const override;

private:
  TopAbs_ShapeEnum myType;
};
