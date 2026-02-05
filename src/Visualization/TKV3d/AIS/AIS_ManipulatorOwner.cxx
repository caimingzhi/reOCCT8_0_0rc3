#include <AIS_ManipulatorOwner.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_ManipulatorOwner, SelectMgr_EntityOwner)

//=================================================================================================

AIS_ManipulatorOwner::AIS_ManipulatorOwner(
  const occ::handle<SelectMgr_SelectableObject>& theSelObject,
  const int                                      theIndex,
  const AIS_ManipulatorMode                      theMode,
  const int                                      thePriority)
    : SelectMgr_EntityOwner(theSelObject, thePriority),
      myIndex(theIndex),
      myMode(theMode)
{
}

//=================================================================================================

void AIS_ManipulatorOwner::HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                            const occ::handle<Prs3d_Drawer>&               theStyle,
                                            const int                                      theMode)
{
  if (theMode == 0)
  {
    SelectMgr_EntityOwner::HilightWithColor(thePM, theStyle, theMode);
    return;
  }

  Selectable()->HilightOwnerWithColor(thePM, theStyle, this);
}

//=================================================================================================

bool AIS_ManipulatorOwner::IsHilighted(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                       const int /*theMode*/) const
{
  if (!HasSelectable())
  {
    return false;
  }

  return thePM->IsHighlighted(Selectable(), myMode);
}

//=================================================================================================

void AIS_ManipulatorOwner::Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                     const int /*theMode*/)
{
  if (!HasSelectable())
  {
    return;
  }

  thePM->Unhighlight(Selectable());
}
