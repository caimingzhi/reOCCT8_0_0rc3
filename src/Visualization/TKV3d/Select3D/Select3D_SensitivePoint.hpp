#pragma once

#include <Select3D_SensitiveEntity.hpp>
#include <SelectMgr_SelectingVolumeManager.hpp>

class Select3D_SensitivePoint : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitivePoint, Select3D_SensitiveEntity)
public:
  Standard_EXPORT Select3D_SensitivePoint(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                          const gp_Pnt&                             thePoint);

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  const gp_Pnt& Point() const { return myPoint; }

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  bool ToBuildBVH() const override { return false; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  gp_Pnt myPoint;
};
