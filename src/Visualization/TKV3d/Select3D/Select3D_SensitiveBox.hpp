#pragma once

#include <Select3D_SensitiveEntity.hpp>

class Select3D_SensitiveBox : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveBox, Select3D_SensitiveEntity)
public:
  Standard_EXPORT Select3D_SensitiveBox(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                        const Bnd_Box&                            theBox);

  Standard_EXPORT Select3D_SensitiveBox(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                        const double                              theXMin,
                                        const double                              theYMin,
                                        const double                              theZMin,
                                        const double                              theXMax,
                                        const double                              theYMax,
                                        const double                              theZMax);

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Bnd_Box Box() const
  {
    Bnd_Box aBox;
    aBox.Update(myBox.CornerMin().x(),
                myBox.CornerMin().y(),
                myBox.CornerMin().z(),
                myBox.CornerMax().x(),
                myBox.CornerMax().y(),
                myBox.CornerMax().z());

    return aBox;
  }

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  bool ToBuildBVH() const override { return false; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  Select3D_BndBox3d myBox;
  gp_Pnt            myCenter3d;
};
