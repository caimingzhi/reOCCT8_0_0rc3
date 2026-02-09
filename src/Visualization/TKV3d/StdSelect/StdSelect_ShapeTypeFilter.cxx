#include <Standard_Type.hpp>
#include <StdSelect_BRepOwner.hpp>
#include <StdSelect_ShapeTypeFilter.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StdSelect_ShapeTypeFilter, SelectMgr_Filter)

StdSelect_ShapeTypeFilter::StdSelect_ShapeTypeFilter(const TopAbs_ShapeEnum aType)
    : myType(aType)
{
}

bool StdSelect_ShapeTypeFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& EO) const
{
  occ::handle<StdSelect_BRepOwner> BRO = occ::down_cast<StdSelect_BRepOwner>(EO);
  if (BRO.IsNull() || !BRO->HasShape())
    return false;
  const TopoDS_Shape& anobj = BRO->Shape();
  return anobj.ShapeType() == myType;
}

bool StdSelect_ShapeTypeFilter::ActsOn(const TopAbs_ShapeEnum aStandardMode) const
{
  return aStandardMode == myType;
}
