#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

enum StdSelect_TypeOfEdge
{
  StdSelect_AnyEdge,
  StdSelect_Line,
  StdSelect_Circle
};

#include <SelectMgr_Filter.hpp>
#include <TopAbs_ShapeEnum.hpp>
class SelectMgr_EntityOwner;

class StdSelect_EdgeFilter : public SelectMgr_Filter
{

public:
  Standard_EXPORT StdSelect_EdgeFilter(const StdSelect_TypeOfEdge Edge);

  Standard_EXPORT void SetType(const StdSelect_TypeOfEdge aNewType);

  Standard_EXPORT StdSelect_TypeOfEdge Type() const;

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aStandardMode) const override;

  DEFINE_STANDARD_RTTIEXT(StdSelect_EdgeFilter, SelectMgr_Filter)

private:
  StdSelect_TypeOfEdge mytype;
};
