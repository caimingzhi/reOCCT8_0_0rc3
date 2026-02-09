#pragma once

#include <Standard.hpp>

enum PrsDim_DimensionSelectionMode
{
  PrsDim_DimensionSelectionMode_All,
  PrsDim_DimensionSelectionMode_Line,
  PrsDim_DimensionSelectionMode_Text
};

#include <SelectMgr_EntityOwner.hpp>
#include <Standard_Integer.hpp>
#include <PrsMgr_PresentationManager.hpp>

class SelectMgr_SelectableObject;
class PrsMgr_PresentationManager;

class PrsDim_DimensionOwner : public SelectMgr_EntityOwner
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_DimensionOwner, SelectMgr_EntityOwner)
public:
  Standard_EXPORT PrsDim_DimensionOwner(const occ::handle<SelectMgr_SelectableObject>& theSelObject,
                                        const PrsDim_DimensionSelectionMode            theSelMode,
                                        const int thePriority = 0);

  PrsDim_DimensionSelectionMode SelectionMode() const { return mySelectionMode; }

  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  Standard_EXPORT bool IsHilighted(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                   const int theMode = 0) const override;

  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                 const int theMode = 0) override;

private:
  PrsDim_DimensionSelectionMode mySelectionMode;
};
