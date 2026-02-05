#include <MeshVS_DummySensitiveEntity.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MeshVS_DummySensitiveEntity, Select3D_SensitiveEntity)

//=================================================================================================

MeshVS_DummySensitiveEntity::MeshVS_DummySensitiveEntity(
  const occ::handle<SelectMgr_EntityOwner>& theOwnerId)
    : Select3D_SensitiveEntity(theOwnerId)
{
}

//=================================================================================================

int MeshVS_DummySensitiveEntity::NbSubElements() const
{
  return -1;
}

//=================================================================================================

bool MeshVS_DummySensitiveEntity::Matches(SelectBasics_SelectingVolumeManager& /*theMgr*/,
                                          SelectBasics_PickResult& /*thePickResult*/)
{
  return false;
}

//=================================================================================================

Select3D_BndBox3d MeshVS_DummySensitiveEntity::BoundingBox()
{
  return Select3D_BndBox3d();
}

//=================================================================================================

void MeshVS_DummySensitiveEntity::BVH() {}

//=================================================================================================

void MeshVS_DummySensitiveEntity::Clear() {}

//=================================================================================================

bool MeshVS_DummySensitiveEntity::HasInitLocation() const
{
  return false;
}

//=================================================================================================

gp_GTrsf MeshVS_DummySensitiveEntity::InvInitLocation() const
{
  return gp_GTrsf();
}
