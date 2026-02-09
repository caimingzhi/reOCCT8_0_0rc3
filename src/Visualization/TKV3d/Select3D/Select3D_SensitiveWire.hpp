#pragma once

#include <Select3D_SensitiveSet.hpp>

class Select3D_SensitiveWire : public Select3D_SensitiveSet
{
public:
  Standard_EXPORT Select3D_SensitiveWire(const occ::handle<SelectMgr_EntityOwner>& theOwnerId);

  Standard_EXPORT void Add(const occ::handle<Select3D_SensitiveEntity>& theSensitive);

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT const NCollection_Vector<occ::handle<Select3D_SensitiveEntity>>& GetEdges();

  Standard_EXPORT void Set(const occ::handle<SelectMgr_EntityOwner>& theOwnerId) override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetLastDetected() const;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT int Size() const override;

  Standard_EXPORT Select3D_BndBox3d Box(const int theIdx) const override;

  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveWire, Select3D_SensitiveSet)

protected:
  Standard_EXPORT bool overlapsElement(SelectBasics_PickResult&             thePickResult,
                                       SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  Standard_EXPORT bool elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  Standard_EXPORT double distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr) override;

private:
  NCollection_Vector<occ::handle<Select3D_SensitiveEntity>> myEntities;
  NCollection_Vector<int>                                   myEntityIndexes;
  gp_Pnt                                                    myCenter;
  mutable Select3D_BndBox3d                                 myBndBox;
};
