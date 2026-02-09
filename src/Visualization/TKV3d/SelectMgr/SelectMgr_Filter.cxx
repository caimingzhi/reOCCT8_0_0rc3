#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Filter.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_Filter, Standard_Transient)

bool SelectMgr_Filter::ActsOn(const TopAbs_ShapeEnum) const
{
  return false;
}
