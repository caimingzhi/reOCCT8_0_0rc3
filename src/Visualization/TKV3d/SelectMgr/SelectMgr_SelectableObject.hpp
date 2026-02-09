#pragma once

#include <PrsMgr_PresentableObject.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Shared.hpp>
#include <NCollection_Sequence.hpp>
#include <SelectMgr_Selection.hpp>

class SelectMgr_EntityOwner;

class SelectMgr_SelectableObject : public PrsMgr_PresentableObject
{
  DEFINE_STANDARD_RTTIEXT(SelectMgr_SelectableObject, PrsMgr_PresentableObject)
  friend class SelectMgr_SelectionManager;

public:
  Standard_EXPORT ~SelectMgr_SelectableObject() override;

  virtual void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                const int                               theMode) = 0;

  virtual bool AcceptShapeDecomposition() const { return false; }

  Standard_EXPORT void RecomputePrimitives();

  Standard_EXPORT void RecomputePrimitives(const int theMode);

  Standard_EXPORT void AddSelection(const occ::handle<SelectMgr_Selection>& aSelection,
                                    const int                               aMode);

  Standard_EXPORT void ClearSelections(const bool update = false);

  Standard_EXPORT const occ::handle<SelectMgr_Selection>& Selection(const int theMode) const;

  bool HasSelection(const int theMode) const { return !Selection(theMode).IsNull(); }

  const NCollection_Sequence<occ::handle<SelectMgr_Selection>>& Selections() const
  {
    return myselections;
  }

  Standard_EXPORT void ResetTransformation() override;

  Standard_EXPORT void UpdateTransformation() override;

  Standard_EXPORT virtual void UpdateTransformations(
    const occ::handle<SelectMgr_Selection>& aSelection);

  Standard_EXPORT virtual void HilightSelected(
    const occ::handle<PrsMgr_PresentationManager>&                  thePrsMgr,
    const NCollection_Sequence<occ::handle<SelectMgr_EntityOwner>>& theSeq);

  Standard_EXPORT virtual void ClearSelected();

  Standard_EXPORT virtual void ClearDynamicHighlight(
    const occ::handle<PrsMgr_PresentationManager>& theMgr);

  Standard_EXPORT virtual void HilightOwnerWithColor(
    const occ::handle<PrsMgr_PresentationManager>& thePM,
    const occ::handle<Prs3d_Drawer>&               theStyle,
    const occ::handle<SelectMgr_EntityOwner>&      theOwner);

  virtual bool IsAutoHilight() const { return myAutoHilight; }

  virtual void SetAutoHilight(const bool theAutoHilight) { myAutoHilight = theAutoHilight; }

  Standard_EXPORT occ::handle<Prs3d_Presentation> GetHilightPresentation(
    const occ::handle<PrsMgr_PresentationManager>& thePrsMgr);

  Standard_EXPORT occ::handle<Prs3d_Presentation> GetSelectPresentation(
    const occ::handle<PrsMgr_PresentationManager>& thePrsMgr);

  Standard_EXPORT virtual void ErasePresentations(bool theToRemove);

  Standard_EXPORT void SetZLayer(const Graphic3d_ZLayerId theLayerId) override;

  void UpdateSelection(const int theMode = -1) { updateSelection(theMode); }

  Standard_EXPORT void SetAssemblyOwner(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                        const int                                 theMode = -1);

  Standard_EXPORT Bnd_Box BndBoxOfSelected(
    const occ::handle<
      NCollection_Shared<NCollection_IndexedMap<occ::handle<SelectMgr_EntityOwner>>>>& theOwners);

  int GlobalSelectionMode() const { return myGlobalSelMode; }

  Standard_EXPORT virtual occ::handle<SelectMgr_EntityOwner> GlobalSelOwner() const;

  Standard_EXPORT virtual const occ::handle<SelectMgr_EntityOwner>& GetAssemblyOwner() const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT SelectMgr_SelectableObject(
    const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d = PrsMgr_TOP_AllView);

  void setGlobalSelMode(const int theMode) { myGlobalSelMode = theMode > 0 ? theMode : 0; }

  Standard_EXPORT void UpdateClipping() override;

  Standard_EXPORT virtual void updateSelection(const int theMode);

protected:
  NCollection_Sequence<occ::handle<SelectMgr_Selection>> myselections;

  occ::handle<Prs3d_Presentation> mySelectionPrs;
  occ::handle<Prs3d_Presentation> myHilightPrs;

  int  myGlobalSelMode;
  bool myAutoHilight;
};
