#include <AIS_TrihedronOwner.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_TrihedronOwner, SelectMgr_EntityOwner)

AIS_TrihedronOwner::AIS_TrihedronOwner(const occ::handle<SelectMgr_SelectableObject>& theSelObject,
                                       const Prs3d_DatumParts                         thePart,
                                       const int                                      thePriority)
    : SelectMgr_EntityOwner(theSelObject, thePriority),
      myDatumPart(thePart)
{
}

void AIS_TrihedronOwner::HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                          const occ::handle<Prs3d_Drawer>&               theStyle,
                                          const int)
{
  Selectable()->HilightOwnerWithColor(thePM, theStyle, this);
}

bool AIS_TrihedronOwner::IsHilighted(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                     const int                                      theMode) const
{
  if (!HasSelectable())
  {
    return false;
  }

  return thePM->IsHighlighted(Selectable(), theMode);
}

void AIS_TrihedronOwner::Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                   const int                                      theMode)
{
  (void)theMode;
  if (!HasSelectable())
  {
    return;
  }

  thePM->Unhighlight(Selectable());
}
