#pragma once

#include <SelectMgr_ViewerSelector.hpp>
#include <SelectMgr_TypeOfUpdate.hpp>

class SelectMgr_SelectableObject;

class SelectMgr_SelectionManager : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(SelectMgr_SelectionManager, Standard_Transient)
public:
  Standard_EXPORT SelectMgr_SelectionManager(
    const occ::handle<SelectMgr_ViewerSelector>& theSelector);

  const occ::handle<SelectMgr_ViewerSelector>& Selector() const { return mySelector; }

  Standard_EXPORT bool Contains(const occ::handle<SelectMgr_SelectableObject>& theObject) const;

  Standard_EXPORT void Load(const occ::handle<SelectMgr_SelectableObject>& theObject,
                            const int                                      theMode = -1);

  Standard_EXPORT void Remove(const occ::handle<SelectMgr_SelectableObject>& theObject);

  Standard_EXPORT void Activate(const occ::handle<SelectMgr_SelectableObject>& theObject,
                                const int                                      theMode = 0);

  Standard_EXPORT void Deactivate(const occ::handle<SelectMgr_SelectableObject>& theObject,
                                  const int                                      theMode = -1);

  Standard_EXPORT bool IsActivated(const occ::handle<SelectMgr_SelectableObject>& theObject,
                                   const int theMode = -1) const;

  Standard_EXPORT void ClearSelectionStructures(
    const occ::handle<SelectMgr_SelectableObject>& theObj,
    const int                                      theMode = -1);

  Standard_EXPORT void RestoreSelectionStructures(
    const occ::handle<SelectMgr_SelectableObject>& theObj,
    const int                                      theMode = -1);

  Standard_EXPORT void RecomputeSelection(const occ::handle<SelectMgr_SelectableObject>& theObject,
                                          const bool theIsForce = false,
                                          const int  theMode    = -1);

  Standard_EXPORT void Update(const occ::handle<SelectMgr_SelectableObject>& theObject,
                              const bool                                     theIsForce = true);

  Standard_EXPORT void SetUpdateMode(const occ::handle<SelectMgr_SelectableObject>& theObject,
                                     const SelectMgr_TypeOfUpdate                   theType);

  Standard_EXPORT void SetUpdateMode(const occ::handle<SelectMgr_SelectableObject>& theObject,
                                     const int                                      theMode,
                                     const SelectMgr_TypeOfUpdate                   theType);

  Standard_EXPORT void SetSelectionSensitivity(
    const occ::handle<SelectMgr_SelectableObject>& theObject,
    const int                                      theMode,
    const int                                      theNewSens);

  Standard_EXPORT void UpdateSelection(const occ::handle<SelectMgr_SelectableObject>& theObj);

protected:
  Standard_EXPORT void recomputeSelectionMode(
    const occ::handle<SelectMgr_SelectableObject>& theObject,
    const occ::handle<SelectMgr_Selection>&        theSelection,
    const int                                      theMode);

private:
  Standard_EXPORT void loadMode(const occ::handle<SelectMgr_SelectableObject>& theObject,
                                const int                                      theMode);

  Standard_EXPORT void buildBVH(const occ::handle<SelectMgr_Selection>& theSelection);

private:
  occ::handle<SelectMgr_ViewerSelector>                    mySelector;
  NCollection_Map<occ::handle<SelectMgr_SelectableObject>> myGlobal;
};
