#pragma once

#include <MeshVS_PrsBuilder.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <NCollection_DataMap.hpp>
#include <MeshVS_MeshSelectionMethod.hpp>
#include <AIS_InteractiveObject.hpp>

class MeshVS_PrsBuilder;
class TColStd_HPackedMapOfInteger;
class MeshVS_DataSource;
class MeshVS_Drawer;
class SelectMgr_EntityOwner;

class MeshVS_Mesh : public AIS_InteractiveObject
{

public:
  Standard_EXPORT MeshVS_Mesh(const bool theIsAllowOverlapped = false);

  Standard_EXPORT bool AcceptDisplayMode(const int theMode) const override;

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theDispMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int theSelMode) override;

  Standard_EXPORT void HilightSelected(
    const occ::handle<PrsMgr_PresentationManager>&                  thePrsMgr,
    const NCollection_Sequence<occ::handle<SelectMgr_EntityOwner>>& theOwners) override;

  Standard_EXPORT void HilightOwnerWithColor(
    const occ::handle<PrsMgr_PresentationManager>& thePM,
    const occ::handle<Prs3d_Drawer>&               theColor,
    const occ::handle<SelectMgr_EntityOwner>&      theOwner) override;

  Standard_EXPORT void ClearSelected() override;

  Standard_EXPORT int GetBuildersCount() const;

  Standard_EXPORT occ::handle<MeshVS_PrsBuilder> GetBuilder(const int Index) const;

  Standard_EXPORT occ::handle<MeshVS_PrsBuilder> GetBuilderById(const int Id) const;

  Standard_EXPORT int GetFreeId() const;

  Standard_EXPORT void AddBuilder(const occ::handle<MeshVS_PrsBuilder>& Builder,
                                  const bool                            TreatAsHilighter = false);

  Standard_EXPORT void SetHilighter(const occ::handle<MeshVS_PrsBuilder>& Builder);

  Standard_EXPORT bool SetHilighter(const int Index);

  Standard_EXPORT bool SetHilighterById(const int Id);

  Standard_EXPORT occ::handle<MeshVS_PrsBuilder> GetHilighter() const;

  Standard_EXPORT void RemoveBuilder(const int Index);

  Standard_EXPORT void RemoveBuilderById(const int Id);

  Standard_DEPRECATED("This method will be removed right after 7.9 release. \
Use FindBuilder(const occ::handle<Standard_Type>&) instead \
or directly iterate under sequence of builders.")
  Standard_EXPORT occ::handle<MeshVS_PrsBuilder> FindBuilder(const char* TypeString) const;

  Standard_EXPORT occ::handle<MeshVS_PrsBuilder> FindBuilder(
    const occ::handle<Standard_Type>& TypeString) const;

  Standard_EXPORT const NCollection_DataMap<int, occ::handle<SelectMgr_EntityOwner>>& GetOwnerMaps(
    const bool IsElement);

  Standard_EXPORT occ::handle<MeshVS_DataSource> GetDataSource() const;

  Standard_EXPORT void SetDataSource(const occ::handle<MeshVS_DataSource>& aDataSource);

  Standard_EXPORT occ::handle<MeshVS_Drawer> GetDrawer() const;

  Standard_EXPORT void SetDrawer(const occ::handle<MeshVS_Drawer>& aDrawer);

  Standard_EXPORT bool IsHiddenElem(const int ID) const;

  Standard_EXPORT bool IsHiddenNode(const int ID) const;

  Standard_EXPORT bool IsSelectableElem(const int ID) const;

  Standard_EXPORT bool IsSelectableNode(const int ID) const;

  Standard_EXPORT const occ::handle<TColStd_HPackedMapOfInteger>& GetHiddenNodes() const;

  Standard_EXPORT void SetHiddenNodes(const occ::handle<TColStd_HPackedMapOfInteger>& Ids);

  Standard_EXPORT const occ::handle<TColStd_HPackedMapOfInteger>& GetHiddenElems() const;

  Standard_EXPORT void SetHiddenElems(const occ::handle<TColStd_HPackedMapOfInteger>& Ids);

  Standard_EXPORT const occ::handle<TColStd_HPackedMapOfInteger>& GetSelectableNodes() const;

  Standard_EXPORT void SetSelectableNodes(const occ::handle<TColStd_HPackedMapOfInteger>& Ids);

  Standard_EXPORT void UpdateSelectableNodes();

  Standard_EXPORT MeshVS_MeshSelectionMethod GetMeshSelMethod() const;

  Standard_EXPORT void SetMeshSelMethod(const MeshVS_MeshSelectionMethod M);

  Standard_EXPORT virtual bool IsWholeMeshOwner(
    const occ::handle<SelectMgr_EntityOwner>& theOwner) const;

  friend class MeshVS_PrsBuilder;

  DEFINE_STANDARD_RTTIEXT(MeshVS_Mesh, AIS_InteractiveObject)

protected:
  Standard_EXPORT void scanFacesForSharedNodes(const TColStd_PackedMapOfInteger& theAllElements,
                                               const int                         theNbMaxFaceNodes,
                                               TColStd_PackedMapOfInteger& theSharedNodes) const;

protected:
  NCollection_DataMap<int, occ::handle<SelectMgr_EntityOwner>> myNodeOwners;
  NCollection_DataMap<int, occ::handle<SelectMgr_EntityOwner>> myElementOwners;
  NCollection_DataMap<int, occ::handle<SelectMgr_EntityOwner>> my0DOwners;
  NCollection_DataMap<int, occ::handle<SelectMgr_EntityOwner>> myLinkOwners;
  NCollection_DataMap<int, occ::handle<SelectMgr_EntityOwner>> myFaceOwners;
  NCollection_DataMap<int, occ::handle<SelectMgr_EntityOwner>> myVolumeOwners;
  NCollection_DataMap<int, occ::handle<SelectMgr_EntityOwner>> myGroupOwners;
  NCollection_DataMap<int, occ::handle<SelectMgr_EntityOwner>> myMeshOwners;
  occ::handle<MeshVS_Drawer>                                   myCurrentDrawer;
  occ::handle<MeshVS_Drawer>                                   mySelectionDrawer;
  occ::handle<MeshVS_Drawer>                                   myHilightDrawer;
  occ::handle<SelectMgr_EntityOwner>                           myWholeMeshOwner;

private:
  NCollection_Sequence<occ::handle<MeshVS_PrsBuilder>> myBuilders;
  occ::handle<MeshVS_PrsBuilder>                       myHilighter;
  occ::handle<TColStd_HPackedMapOfInteger>             myHiddenElements;
  occ::handle<TColStd_HPackedMapOfInteger>             myHiddenNodes;
  occ::handle<TColStd_HPackedMapOfInteger>             mySelectableNodes;
  occ::handle<MeshVS_DataSource>                       myDataSource;
  MeshVS_MeshSelectionMethod                           mySelectionMethod;
};
