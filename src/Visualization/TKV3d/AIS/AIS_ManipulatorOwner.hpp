#pragma once


#include <AIS_Manipulator.hpp>

#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_SelectableObject.hpp>

//! Entity owner for selection management of AIS_Manipulator object.
class AIS_ManipulatorOwner : public SelectMgr_EntityOwner
{
public:
  DEFINE_STANDARD_RTTIEXT(AIS_ManipulatorOwner, SelectMgr_EntityOwner)

  Standard_EXPORT AIS_ManipulatorOwner(const occ::handle<SelectMgr_SelectableObject>& theSelObject,
                                       const int                                      theIndex,
                                       const AIS_ManipulatorMode                      theMode,
                                       const int thePriority = 0);

  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  Standard_EXPORT bool IsHilighted(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                   const int theMode) const override;

  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                 const int                                      theMode) override;

  AIS_ManipulatorMode Mode() const { return myMode; }

  //! @return index of manipulator axis.
  int Index() const { return myIndex; }

protected:
  int                 myIndex; //!< index of manipulator axis.
  AIS_ManipulatorMode myMode;  //!< manipulation (highlight) mode.
};

