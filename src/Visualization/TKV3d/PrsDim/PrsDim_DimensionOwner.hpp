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

//! The owner is the entity which makes it possible to link
//! the sensitive primitives and the reference shapes that
//! you want to detect. It stocks the various pieces of
//! information which make it possible to find objects. An
//! owner has a priority which you can modulate, so as to
//! make one entity more selectable than another. You
//! might want to make edges more selectable than
//! faces, for example. In that case, you could attribute sa
//! higher priority to the one compared to the other. An
//! edge, could have priority 5, for example, and a face,
//! priority 4. The default priority is 5.
class PrsDim_DimensionOwner : public SelectMgr_EntityOwner
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_DimensionOwner, SelectMgr_EntityOwner)
public:
  //! Initializes the dimension owner, theSO, and attributes it
  //! the priority, thePriority.
  Standard_EXPORT PrsDim_DimensionOwner(const occ::handle<SelectMgr_SelectableObject>& theSelObject,
                                        const PrsDim_DimensionSelectionMode            theSelMode,
                                        const int thePriority = 0);

  PrsDim_DimensionSelectionMode SelectionMode() const { return mySelectionMode; }

  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  //! Returns true if an object with the selection mode
  //! aMode is highlighted in the presentation manager aPM.
  Standard_EXPORT bool IsHilighted(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                   const int theMode = 0) const override;

  //! Removes highlighting from the selected part of dimension.
  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                 const int theMode = 0) override;

private:
  PrsDim_DimensionSelectionMode mySelectionMode;
};
