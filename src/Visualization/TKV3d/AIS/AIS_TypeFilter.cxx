#include <AIS_InteractiveObject.hpp>
#include <AIS_TypeFilter.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_TypeFilter, SelectMgr_Filter)

AIS_TypeFilter::AIS_TypeFilter(const AIS_KindOfInteractive TheKind)
    : myKind(TheKind)
{
}

bool AIS_TypeFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& anObj) const
{
  occ::handle<AIS_InteractiveObject> anObject =
    occ::down_cast<AIS_InteractiveObject>(anObj->Selectable());
  return !anObject.IsNull() && anObject->Type() == myKind;
}
