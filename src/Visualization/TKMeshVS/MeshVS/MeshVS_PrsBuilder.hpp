#pragma once

class MeshVS_Mesh;
typedef MeshVS_Mesh* MeshVS_MeshPtr;

#include <PrsMgr_PresentationManager.hpp>
#include <Prs3d_Presentation.hpp>
#include <MeshVS_DisplayModeFlags.hpp>
#include <MeshVS_BuilderPriority.hpp>
#include <TColStd_PackedMapOfInteger.hpp>

class MeshVS_DataSource;
class MeshVS_Drawer;
class MeshVS_Mesh;
class Select3D_SensitiveEntity;
class SelectMgr_EntityOwner;

class MeshVS_PrsBuilder : public Standard_Transient
{
public:
  Standard_EXPORT virtual void Build(const occ::handle<Prs3d_Presentation>& Prs,
                                     const TColStd_PackedMapOfInteger&      IDs,
                                     TColStd_PackedMapOfInteger&            IDsToExclude,
                                     const bool                             IsElement,
                                     const int                              DisplayMode) const = 0;

  Standard_EXPORT virtual void CustomBuild(const occ::handle<Prs3d_Presentation>& Prs,
                                           const TColStd_PackedMapOfInteger&      IDs,
                                           TColStd_PackedMapOfInteger&            IDsToExclude,
                                           const int DisplayMode) const;

  Standard_EXPORT virtual occ::handle<Select3D_SensitiveEntity> CustomSensitiveEntity(
    const occ::handle<SelectMgr_EntityOwner>& Owner,
    const int                                 SelectMode) const;

  Standard_EXPORT int GetFlags() const;

  Standard_EXPORT virtual bool TestFlags(const int DisplayMode) const;

  Standard_EXPORT int GetId() const;

  Standard_EXPORT int GetPriority() const;

  Standard_EXPORT occ::handle<MeshVS_DataSource> GetDataSource() const;

  Standard_EXPORT void SetDataSource(const occ::handle<MeshVS_DataSource>& newDS);

  Standard_EXPORT occ::handle<MeshVS_Drawer> GetDrawer() const;

  Standard_EXPORT void SetDrawer(const occ::handle<MeshVS_Drawer>& newDr);

  Standard_EXPORT void SetExcluding(const bool state);

  Standard_EXPORT bool IsExcludingOn() const;

  Standard_EXPORT void SetPresentationManager(
    const occ::handle<PrsMgr_PresentationManager>& thePrsMgr);

  Standard_EXPORT occ::handle<PrsMgr_PresentationManager> GetPresentationManager() const;

  DEFINE_STANDARD_RTTIEXT(MeshVS_PrsBuilder, Standard_Transient)

protected:
  Standard_EXPORT MeshVS_PrsBuilder(const occ::handle<MeshVS_Mesh>&       Parent,
                                    const MeshVS_DisplayModeFlags&        Flags,
                                    const occ::handle<MeshVS_DataSource>& DS,
                                    const int                             Id,
                                    const MeshVS_BuilderPriority& Priority = MeshVS_BP_Default);

  Standard_EXPORT occ::handle<MeshVS_DataSource> DataSource() const;

  Standard_EXPORT occ::handle<MeshVS_Drawer> Drawer() const;

protected:
  MeshVS_MeshPtr myParentMesh;

private:
  bool                                    myIsExcluding;
  occ::handle<MeshVS_DataSource>          myDataSource;
  occ::handle<MeshVS_Drawer>              myDrawer;
  int                                     myFlags;
  int                                     myId;
  int                                     myPriority;
  occ::handle<PrsMgr_PresentationManager> myPrsMgr;
};
