#include <PrsDim_DimensionOwner.hpp>

#include <PrsDim_Dimension.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <Standard_Type.hpp>
#include <TopoDS.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_DimensionOwner, SelectMgr_EntityOwner)

namespace
{

  static PrsDim_Dimension::ComputeMode HighlightMode(const int theSelMode)
  {
    switch (theSelMode)
    {
      case PrsDim_DimensionSelectionMode_Line:
        return PrsDim_Dimension::ComputeMode_Line;
      case PrsDim_DimensionSelectionMode_Text:
        return PrsDim_Dimension::ComputeMode_Text;
      default:
        return PrsDim_Dimension::ComputeMode_All;
    }
  }
} // namespace

PrsDim_DimensionOwner::PrsDim_DimensionOwner(
  const occ::handle<SelectMgr_SelectableObject>& theSelObject,
  const PrsDim_DimensionSelectionMode            theMode,
  const int                                      thePriority)
    : SelectMgr_EntityOwner(theSelObject, thePriority),
      mySelectionMode(theMode)
{
}

bool PrsDim_DimensionOwner::IsHilighted(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const int) const
{
  if (!HasSelectable())
  {
    return false;
  }

  return thePM->IsHighlighted(Selectable(), HighlightMode(mySelectionMode));
}

void PrsDim_DimensionOwner::Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                      const int)
{
  if (!HasSelectable())
  {
    return;
  }

  thePM->Unhighlight(Selectable());
}

void PrsDim_DimensionOwner::HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                             const occ::handle<Prs3d_Drawer>& theStyle,
                                             const int)
{
  thePM->Color(Selectable(), theStyle, HighlightMode(mySelectionMode));
}
