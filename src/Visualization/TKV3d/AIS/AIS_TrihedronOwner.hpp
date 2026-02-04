#pragma once


#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <Prs3d_DatumParts.hpp>

//! Entity owner for selection management of AIS_Trihedron object.
class AIS_TrihedronOwner : public SelectMgr_EntityOwner
{
  DEFINE_STANDARD_RTTIEXT(AIS_TrihedronOwner, SelectMgr_EntityOwner)
public:
  //! Creates an owner of AIS_Trihedron object.
  Standard_EXPORT AIS_TrihedronOwner(const occ::handle<SelectMgr_SelectableObject>& theSelObject,
                                     const Prs3d_DatumParts                         theDatumPart,
                                     const int                                      thePriority);

  //! Returns the datum part identifier.
  Prs3d_DatumParts DatumPart() const { return myDatumPart; }

  //! Highlights selectable object's presentation.
  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  //! Returns true if the presentation manager thePM
  //! highlights selections corresponding to the selection mode aMode.
  Standard_EXPORT bool IsHilighted(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                   const int theMode) const override;

  //! Removes highlighting from the owner of a detected
  //! selectable object in the presentation manager thePM.
  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                 const int                                      theMode) override;

protected:
  Prs3d_DatumParts myDatumPart; //!< part of datum selected
};

