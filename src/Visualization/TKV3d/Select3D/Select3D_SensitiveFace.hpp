#pragma once

#include <Select3D_TypeOfSensitivity.hpp>
#include <Select3D_SensitiveSet.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <SelectBasics_SelectingVolumeManager.hpp>

class Select3D_SensitiveFace : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveFace, Select3D_SensitiveEntity)
public:
  Standard_EXPORT Select3D_SensitiveFace(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                         const NCollection_Array1<gp_Pnt>&         thePoints,
                                         const Select3D_TypeOfSensitivity          theType);

  Standard_EXPORT Select3D_SensitiveFace(const occ::handle<SelectMgr_EntityOwner>&       theOwnerId,
                                         const occ::handle<NCollection_HArray1<gp_Pnt>>& thePoints,
                                         const Select3D_TypeOfSensitivity                theType);

  Standard_EXPORT void GetPoints(occ::handle<NCollection_HArray1<gp_Pnt>>& theHArrayOfPnt);

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT void BVH() override;

  bool ToBuildBVH() const override { return myFacePoints->ToBuildBVH(); }

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  Select3D_TypeOfSensitivity mySensType;

  occ::handle<Select3D_SensitiveSet> myFacePoints;
};
