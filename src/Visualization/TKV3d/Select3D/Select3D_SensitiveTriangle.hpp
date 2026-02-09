#pragma once

#include <Select3D_TypeOfSensitivity.hpp>
#include <Select3D_SensitivePoly.hpp>
#include <SelectMgr_SelectingVolumeManager.hpp>

class Select3D_SensitiveTriangle : public Select3D_SensitiveEntity
{
public:
  Standard_EXPORT Select3D_SensitiveTriangle(
    const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
    const gp_Pnt&                             thePnt0,
    const gp_Pnt&                             thePnt1,
    const gp_Pnt&                             thePnt2,
    const Select3D_TypeOfSensitivity          theType = Select3D_TOS_INTERIOR);

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  void Points3D(gp_Pnt& thePnt0, gp_Pnt& thePnt1, gp_Pnt& thePnt2) const
  {
    thePnt0 = myPoints[0];
    thePnt1 = myPoints[1];
    thePnt2 = myPoints[2];
  }

  gp_Pnt Center3D() const { return myCentroid; }

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  bool ToBuildBVH() const override { return false; }

  int NbSubElements() const override { return 3; }

  gp_Pnt CenterOfGeometry() const override { return myCentroid; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveTriangle, Select3D_SensitiveEntity)

private:
  Select3D_TypeOfSensitivity mySensType;
  gp_Pnt                     myCentroid;
  gp_Pnt                     myPoints[3];
};
