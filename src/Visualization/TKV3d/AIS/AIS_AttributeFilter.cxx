#include <AIS_AttributeFilter.hpp>
#include <AIS_InteractiveObject.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_AttributeFilter, SelectMgr_Filter)

AIS_AttributeFilter::AIS_AttributeFilter()
    : hasC(false),
      hasW(false)
{
}

AIS_AttributeFilter::AIS_AttributeFilter(const Quantity_NameOfColor aCol)
    : myCol(aCol),
      hasC(true),
      hasW(false)
{
}

AIS_AttributeFilter::AIS_AttributeFilter(const double aWid)
    : myWid(aWid),
      hasC(false),
      hasW(true)
{
}

bool AIS_AttributeFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& anObj) const
{
  occ::handle<AIS_InteractiveObject> aSelectable(
    occ::down_cast<AIS_InteractiveObject>(anObj->Selectable()));
  if (aSelectable.IsNull())
    return false;

  bool okstat = true;
  if (hasC && aSelectable->HasColor())
  {
    Quantity_Color aColor;
    aSelectable->Color(aColor);
    okstat = (myCol == aColor.Name());
  }

  if (hasW && aSelectable->HasWidth())
    okstat = (myWid == aSelectable->Width()) && okstat;

  return okstat;
}
