#pragma once


#include <Standard.hpp>

#include <Select3D_SensitiveEntity.hpp>
#include <SelectBasics_SelectingVolumeManager.hpp>

//! This class allows to create owners to all elements or nodes,
//! both hidden and shown, but these owners user cannot select "by hands"
//! in viewer. They means for internal application tasks, for example, receiving
//! all owners, both for hidden and shown entities.
class MeshVS_DummySensitiveEntity : public Select3D_SensitiveEntity
{
public:
  Standard_EXPORT MeshVS_DummySensitiveEntity(const occ::handle<SelectMgr_EntityOwner>& theOwnerId);

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT void BVH() override;

  bool ToBuildBVH() const override { return false; }

  Standard_EXPORT void Clear() override;

  Standard_EXPORT bool HasInitLocation() const override;

  Standard_EXPORT gp_GTrsf InvInitLocation() const override;

  gp_Pnt CenterOfGeometry() const override { return gp_Pnt(); }

  DEFINE_STANDARD_RTTIEXT(MeshVS_DummySensitiveEntity, Select3D_SensitiveEntity)
};

