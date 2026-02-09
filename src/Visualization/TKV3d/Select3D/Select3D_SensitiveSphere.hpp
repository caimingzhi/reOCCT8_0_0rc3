#pragma once

#include <Select3D_SensitiveEntity.hpp>

class Select3D_SensitiveSphere : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveSphere, Select3D_SensitiveEntity)
public:
  Standard_EXPORT Select3D_SensitiveSphere(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                           const gp_Pnt&                             theCenter,
                                           const double                              theRadius);

  double Radius() const { return myRadius; }

public:
  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  bool ToBuildBVH() const override { return false; }

  int NbSubElements() const override { return 1; }

  gp_Pnt CenterOfGeometry() const override { return myCenter; };

  const gp_Pnt& LastDetectedPoint() const { return myLastDetectedPoint; }

  void ResetLastDetectedPoint()
  {
    myLastDetectedPoint = gp_Pnt(RealLast(), RealLast(), RealLast());
  }

protected:
  gp_Pnt myCenter;
  gp_Pnt myLastDetectedPoint;
  double myRadius;
};
