#pragma once


#include <Standard.hpp>

#include <Select3D_SensitiveEntity.hpp>
#include <Select3D_BndBox3d.hpp>

//! This class provides custom mesh sensitive entity used in advanced mesh selection.
class MeshVS_SensitiveMesh : public Select3D_SensitiveEntity
{
public:
  Standard_EXPORT MeshVS_SensitiveMesh(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                       const int                                 theMode = 0);

  Standard_EXPORT int GetMode() const;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  //! Checks whether sensitive overlaps current selecting volume.
  bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
               SelectBasics_PickResult&             thePickResult) override
  {
    (void)theMgr;
    (void)thePickResult;
    return false;
  }

  //! Returns the amount of mesh nodes
  Standard_EXPORT int NbSubElements() const override;

  //! Returns bounding box of mesh
  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  //! Returns center of mesh
  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  DEFINE_STANDARD_RTTIEXT(MeshVS_SensitiveMesh, Select3D_SensitiveEntity)

private:
  int               myMode;
  Select3D_BndBox3d myBndBox;
};

