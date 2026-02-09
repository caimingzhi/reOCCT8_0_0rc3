#pragma once

#include <NCollection_Sequence.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Select3D_SensitiveSet.hpp>
#include <SelectMgr_SelectingVolumeManager.hpp>
class Select3D_SensitiveEntity;

class Select3D_SensitiveGroup : public Select3D_SensitiveSet
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveGroup, Select3D_SensitiveSet)
public:
  Standard_EXPORT Select3D_SensitiveGroup(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                          const bool theIsMustMatchAll = true);

  Standard_EXPORT Select3D_SensitiveGroup(
    const occ::handle<SelectMgr_EntityOwner>&                    theOwnerId,
    NCollection_Sequence<occ::handle<Select3D_SensitiveEntity>>& theEntities,
    const bool                                                   theIsMustMatchAll = true);

  const NCollection_IndexedMap<occ::handle<Select3D_SensitiveEntity>>& Entities() const
  {
    return myEntities;
  }

  const occ::handle<Select3D_SensitiveEntity>& SubEntity(const int theIndex) const
  {
    return myEntities.FindKey(theIndex);
  }

  occ::handle<Select3D_SensitiveEntity> LastDetectedEntity() const
  {
    const int anIndex = LastDetectedEntityIndex();
    return anIndex != -1 ? myEntities.FindKey(anIndex) : occ::handle<Select3D_SensitiveEntity>();
  }

  int LastDetectedEntityIndex() const
  {
    return myDetectedIdx != -1 ? myBVHPrimIndexes.Value(myDetectedIdx) : -1;
  }

  Standard_EXPORT void Add(
    NCollection_Sequence<occ::handle<Select3D_SensitiveEntity>>& theEntities);

  Standard_EXPORT void Add(const occ::handle<Select3D_SensitiveEntity>& theSensitive);

  Standard_EXPORT void Remove(const occ::handle<Select3D_SensitiveEntity>& theSensitive);

  Standard_EXPORT void Clear() override;

  Standard_EXPORT bool IsIn(const occ::handle<Select3D_SensitiveEntity>& theSensitive) const;

  void SetMatchType(const bool theIsMustMatchAll) { myMustMatchAll = theIsMustMatchAll; }

  bool MustMatchAll() const { return myMustMatchAll; }

  bool ToCheckOverlapAll() const { return myToCheckOverlapAll; }

  void SetCheckOverlapAll(bool theToCheckAll) { myToCheckOverlapAll = theToCheckAll; }

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT void Set(const occ::handle<SelectMgr_EntityOwner>& theOwnerId) override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT Select3D_BndBox3d Box(const int theIdx) const override;

  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  Standard_EXPORT int Size() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

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
  NCollection_IndexedMap<occ::handle<Select3D_SensitiveEntity>> myEntities;

  bool                      myMustMatchAll;
  bool                      myToCheckOverlapAll;
  gp_Pnt                    myCenter;
  mutable Select3D_BndBox3d myBndBox;
  NCollection_Vector<int>   myBVHPrimIndexes;
};
