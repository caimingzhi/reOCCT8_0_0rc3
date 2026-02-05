#pragma once

#include <SelectMgr_EntityOwner.hpp>
#include <PrsMgr_PresentationManager.hpp>

class MeshVS_DataSource;
class TColStd_HPackedMapOfInteger;
class PrsMgr_PresentationManager;

//! The custom mesh owner used for advanced mesh selection. This class provides methods to store
//! information: 1) IDs of hilighted mesh nodes and elements 2) IDs of mesh nodes and elements
//! selected on the mesh
class MeshVS_MeshOwner : public SelectMgr_EntityOwner
{

public:
  Standard_EXPORT MeshVS_MeshOwner(const SelectMgr_SelectableObject*     theSelObj,
                                   const occ::handle<MeshVS_DataSource>& theDS,
                                   const int                             thePriority = 0);

  Standard_EXPORT const occ::handle<MeshVS_DataSource>& GetDataSource() const;

  //! Returns ids of selected mesh nodes
  Standard_EXPORT const occ::handle<TColStd_HPackedMapOfInteger>& GetSelectedNodes() const;

  //! Returns ids of selected mesh elements
  Standard_EXPORT const occ::handle<TColStd_HPackedMapOfInteger>& GetSelectedElements() const;

  //! Saves ids of selected mesh entities
  Standard_EXPORT virtual void AddSelectedEntities(
    const occ::handle<TColStd_HPackedMapOfInteger>& Nodes,
    const occ::handle<TColStd_HPackedMapOfInteger>& Elems);

  //! Clears ids of selected mesh entities
  Standard_EXPORT virtual void ClearSelectedEntities();

  //! Returns ids of hilighted mesh nodes
  Standard_EXPORT const occ::handle<TColStd_HPackedMapOfInteger>& GetDetectedNodes() const;

  //! Returns ids of hilighted mesh elements
  Standard_EXPORT const occ::handle<TColStd_HPackedMapOfInteger>& GetDetectedElements() const;

  //! Saves ids of hilighted mesh entities
  Standard_EXPORT void SetDetectedEntities(const occ::handle<TColStd_HPackedMapOfInteger>& Nodes,
                                           const occ::handle<TColStd_HPackedMapOfInteger>& Elems);

  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const occ::handle<Prs3d_Drawer>&               theColor,
                                        const int theMode) override;

  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& PM,
                                 const int                                      Mode = 0) override;

  Standard_EXPORT bool IsForcedHilight() const override;

  DEFINE_STANDARD_RTTIEXT(MeshVS_MeshOwner, SelectMgr_EntityOwner)

protected:
  occ::handle<TColStd_HPackedMapOfInteger> mySelectedNodes;
  occ::handle<TColStd_HPackedMapOfInteger> mySelectedElems;

private:
  occ::handle<MeshVS_DataSource>           myDataSource;
  occ::handle<TColStd_HPackedMapOfInteger> myDetectedNodes;
  occ::handle<TColStd_HPackedMapOfInteger> myDetectedElems;
  int                                      myLastID;
};
