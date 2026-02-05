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

//! This class is parent for all builders using in MeshVS_Mesh.
//! It provides base fields and methods all buildes need.
class MeshVS_PrsBuilder : public Standard_Transient
{
public:
  //! Builds presentation of certain type of data.
  //! Prs is presentation object which this method constructs.
  //! IDs is set of numeric identificators forming object appearance.
  //! IDsToExclude is set of IDs to exclude from processing. If some entity
  //! has been excluded, it is not processed by other builders.
  //! IsElement indicates, IDs is identificators of nodes or elements.
  //! DisplayMode is numeric constant describing display mode (see MeshVS_DisplayModeFlags.hpp)
  Standard_EXPORT virtual void Build(const occ::handle<Prs3d_Presentation>& Prs,
                                     const TColStd_PackedMapOfInteger&      IDs,
                                     TColStd_PackedMapOfInteger&            IDsToExclude,
                                     const bool                             IsElement,
                                     const int                              DisplayMode) const = 0;

  //! This method is called to build presentation of custom elements (they have MeshVS_ET_0D type).
  //! IDs is set of numeric identificators of elements for custom building.
  //! IDsToExclude is set of IDs to exclude from processing. If some entity
  //! has been excluded, it is not processed by other builders.
  //! DisplayMode is numeric constant describing display mode (see MeshVS_DisplayModeFlags.hpp)
  Standard_EXPORT virtual void CustomBuild(const occ::handle<Prs3d_Presentation>& Prs,
                                           const TColStd_PackedMapOfInteger&      IDs,
                                           TColStd_PackedMapOfInteger&            IDsToExclude,
                                           const int DisplayMode) const;

  //! This method is called to build sensitive of custom elements ( they have MeshVS_ET_0D type )
  Standard_EXPORT virtual occ::handle<Select3D_SensitiveEntity> CustomSensitiveEntity(
    const occ::handle<SelectMgr_EntityOwner>& Owner,
    const int                                 SelectMode) const;

  //! Returns flags, assigned with builder during creation
  Standard_EXPORT int GetFlags() const;

  //! Test whether display mode has flags assigned with this builder.
  //! This method has default implementation and can be redefined for advance behavior
  //! Returns true only if display mode is appropriate for this builder
  Standard_EXPORT virtual bool TestFlags(const int DisplayMode) const;

  //! Returns builder ID
  Standard_EXPORT int GetId() const;

  //! Returns priority; as priority bigger, as soon builder will be called.
  Standard_EXPORT int GetPriority() const;

  //! Returns custom data source or default ( from MeshVS_Mesh ) if custom is NULL
  Standard_EXPORT occ::handle<MeshVS_DataSource> GetDataSource() const;

  //! Change custom data source
  Standard_EXPORT void SetDataSource(const occ::handle<MeshVS_DataSource>& newDS);

  //! Returns custom drawer or default ( from MeshVS_Mesh ) if custom is NULL
  Standard_EXPORT occ::handle<MeshVS_Drawer> GetDrawer() const;

  //! Change custom drawer
  Standard_EXPORT void SetDrawer(const occ::handle<MeshVS_Drawer>& newDr);

  //! Set excluding state. If it is true, the nodes or elements, processed by current
  //! builder will be noted and next builder won't process its.
  Standard_EXPORT void SetExcluding(const bool state);

  //! Read excluding state
  Standard_EXPORT bool IsExcludingOn() const;

  //! Set presentation manager for builder
  Standard_EXPORT void SetPresentationManager(
    const occ::handle<PrsMgr_PresentationManager>& thePrsMgr);

  //! Get presentation manager of builder
  Standard_EXPORT occ::handle<PrsMgr_PresentationManager> GetPresentationManager() const;

  DEFINE_STANDARD_RTTIEXT(MeshVS_PrsBuilder, Standard_Transient)

protected:
  //! Constructor
  //! Parent is pointer to MeshVS_Mesh object
  //! Flags is set of display modes corresponding to this builder
  //! DS is data source object, from which builder will pick geometry and topological information
  //! Id is numeric identificator of builder. You must set it to positive integer, but if
  //! you set it to -1, constructor will select the smallest integer, not occupied by other builders
  //! Priority is numerical priority constant. As priority bigger, as sooner builder starts during
  //! presentation construction
  Standard_EXPORT MeshVS_PrsBuilder(const occ::handle<MeshVS_Mesh>&       Parent,
                                    const MeshVS_DisplayModeFlags&        Flags,
                                    const occ::handle<MeshVS_DataSource>& DS,
                                    const int                             Id,
                                    const MeshVS_BuilderPriority& Priority = MeshVS_BP_Default);

  //! Returns only custom data source
  Standard_EXPORT occ::handle<MeshVS_DataSource> DataSource() const;

  //! Returns only custom drawer
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
