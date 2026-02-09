#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_List.hpp>
#include <Select3D_SensitiveEntity.hpp>
#include <Select3D_BndBox3d.hpp>

class MeshVS_SensitivePolyhedron : public Select3D_SensitiveEntity
{
public:
  Standard_EXPORT MeshVS_SensitivePolyhedron(
    const occ::handle<SelectMgr_EntityOwner>&                          theOwner,
    const NCollection_Array1<gp_Pnt>&                                  theNodes,
    const occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& theTopo);

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  DEFINE_STANDARD_RTTIEXT(MeshVS_SensitivePolyhedron, Select3D_SensitiveEntity)

private:
  NCollection_List<occ::handle<NCollection_HArray1<gp_Pnt>>>  myTopology;
  gp_XYZ                                                      myCenter;
  Select3D_BndBox3d                                           myBndBox;
  occ::handle<NCollection_HArray1<gp_Pnt>>                    myNodes;
  occ::handle<NCollection_HArray1<NCollection_Sequence<int>>> myTopo;
};
