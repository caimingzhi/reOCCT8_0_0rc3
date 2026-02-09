#pragma once

#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <Prs3d_DatumParts.hpp>

class AIS_TrihedronOwner : public SelectMgr_EntityOwner
{
  DEFINE_STANDARD_RTTIEXT(AIS_TrihedronOwner, SelectMgr_EntityOwner)
public:
  Standard_EXPORT AIS_TrihedronOwner(const occ::handle<SelectMgr_SelectableObject>& theSelObject,
                                     const Prs3d_DatumParts                         theDatumPart,
                                     const int                                      thePriority);

  Prs3d_DatumParts DatumPart() const { return myDatumPart; }

  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  Standard_EXPORT bool IsHilighted(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                   const int theMode) const override;

  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                 const int                                      theMode) override;

protected:
  Prs3d_DatumParts myDatumPart;
};
