#pragma once

#include <SelectMgr_EntityOwner.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

class MeshVS_SensitiveQuad : public Select3D_SensitiveEntity
{
public:
  Standard_EXPORT MeshVS_SensitiveQuad(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                       const NCollection_Array1<gp_Pnt>&         theQuadVerts);

  Standard_EXPORT MeshVS_SensitiveQuad(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                       const gp_Pnt&                             thePnt1,
                                       const gp_Pnt&                             thePnt2,
                                       const gp_Pnt&                             thePnt3,
                                       const gp_Pnt&                             thePnt4);

  int NbSubElements() const override { return 1; };

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  DEFINE_STANDARD_RTTIEXT(MeshVS_SensitiveQuad, Select3D_SensitiveEntity)

private:
  gp_Pnt myVertices[4];
};
