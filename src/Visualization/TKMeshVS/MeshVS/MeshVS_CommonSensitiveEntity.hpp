#pragma once

#include <MeshVS_DataSource.hpp>
#include <MeshVS_Mesh.hpp>
#include <MeshVS_MeshSelectionMethod.hpp>
#include <Select3D_SensitiveSet.hpp>

class MeshVS_CommonSensitiveEntity : public Select3D_SensitiveSet
{
  DEFINE_STANDARD_RTTIEXT(MeshVS_CommonSensitiveEntity, Select3D_SensitiveSet)
public:
  Standard_EXPORT MeshVS_CommonSensitiveEntity(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                               const occ::handle<MeshVS_Mesh>&  theParentMesh,
                                               const MeshVS_MeshSelectionMethod theSelMethod);

  Standard_EXPORT ~MeshVS_CommonSensitiveEntity() override;

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT int Size() const override;

  Standard_EXPORT Select3D_BndBox3d Box(const int theIdx) const override;

  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  occ::handle<Select3D_SensitiveEntity> GetConnected() override
  {
    return new MeshVS_CommonSensitiveEntity(*this);
  }

protected:
  Standard_EXPORT bool overlapsElement(SelectBasics_PickResult&             thePickResult,
                                       SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  Standard_EXPORT bool elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  Standard_EXPORT double distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr) override;

  Standard_EXPORT MeshVS_CommonSensitiveEntity(const MeshVS_CommonSensitiveEntity& theOther);

private:
  gp_Pnt getVertexByIndex(const int theNodeIdx) const;

private:
  occ::handle<MeshVS_DataSource> myDataSource;
  NCollection_Vector<int>        myItemIndexes;
  MeshVS_MeshSelectionMethod     mySelMethod;

  int myMaxFaceNodes;

  gp_Pnt            myCOG;
  Select3D_BndBox3d myBndBox;
};
