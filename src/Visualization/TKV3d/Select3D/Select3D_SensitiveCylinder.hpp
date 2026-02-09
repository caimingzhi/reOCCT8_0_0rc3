#pragma once

#include <Select3D_SensitiveEntity.hpp>

class Select3D_SensitiveCylinder : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveCylinder, Select3D_SensitiveEntity)

public:
  Standard_EXPORT Select3D_SensitiveCylinder(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                             const double                              theBottomRad,
                                             const double                              theTopRad,
                                             const double                              theHeight,
                                             const gp_Trsf&                            theTrsf,
                                             const bool theIsHollow = false);

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  bool ToBuildBVH() const override { return false; }

  int NbSubElements() const override { return 1; }

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  const gp_Trsf& Transformation() const { return myTrsf; }

  double TopRadius() const { return myTopRadius; }

  double BottomRadius() const { return myBottomRadius; }

  double Height() const { return myHeight; }

  bool IsHollow() const { return myIsHollow; }

protected:
  gp_Trsf myTrsf;
  double  myBottomRadius;
  double  myTopRadius;
  double  myHeight;
  bool    myIsHollow;
};
