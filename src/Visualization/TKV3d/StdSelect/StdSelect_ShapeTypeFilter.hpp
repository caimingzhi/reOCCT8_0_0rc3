#pragma once

#include <TopAbs_ShapeEnum.hpp>
#include <SelectMgr_Filter.hpp>

class SelectMgr_EntityOwner;

class StdSelect_ShapeTypeFilter : public SelectMgr_Filter
{
  DEFINE_STANDARD_RTTIEXT(StdSelect_ShapeTypeFilter, SelectMgr_Filter)
public:
  Standard_EXPORT StdSelect_ShapeTypeFilter(const TopAbs_ShapeEnum aType);

  TopAbs_ShapeEnum Type() const { return myType; }

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aStandardMode) const override;

private:
  TopAbs_ShapeEnum myType;
};
