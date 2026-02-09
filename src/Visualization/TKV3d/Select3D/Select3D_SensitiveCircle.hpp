#pragma once

#include <Select3D_SensitiveEntity.hpp>

#include <gp_Circ.hpp>

class Select3D_SensitiveCircle : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveCircle, Select3D_SensitiveEntity)
public:
  Standard_EXPORT Select3D_SensitiveCircle(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                           const gp_Circ&                            theCircle,
                                           const bool theIsFilled = false);

  Standard_DEPRECATED("Deprecated constructor, theNbPnts parameter will be ignored")

  Select3D_SensitiveCircle(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                           const gp_Circ&                            theCircle,
                           const bool                                theIsFilled,
                           const int)
      : Select3D_SensitiveCircle(theOwnerId, theCircle, theIsFilled)
  {
  }

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  bool ToBuildBVH() const override { return false; }

  int NbSubElements() const override { return 1; }

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  const gp_Trsf& Transformation() const { return myTrsf; }

  gp_Circ Circle() const { return gp_Circ(gp::XOY().Transformed(myTrsf), myRadius); }

  double Radius() const { return myRadius; }

private:
  Select3D_TypeOfSensitivity mySensType;
  gp_Trsf                    myTrsf;
  double                     myRadius;
};
