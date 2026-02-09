#pragma once

#include <BVH_PrimitiveSet3d.hpp>
#include <Select3D_BVHBuilder3d.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_SensitiveEntity.hpp>
#include <SelectMgr_Selection.hpp>

class SelectMgr_SensitiveEntitySet : public BVH_PrimitiveSet3d
{
  DEFINE_STANDARD_RTTIEXT(SelectMgr_SensitiveEntitySet, BVH_PrimitiveSet3d)
public:
  Standard_EXPORT SelectMgr_SensitiveEntitySet(
    const occ::handle<Select3D_BVHBuilder3d>& theBuilder);

  ~SelectMgr_SensitiveEntitySet() override = default;

  Standard_EXPORT void Append(const occ::handle<SelectMgr_SensitiveEntity>& theEntity);

  Standard_EXPORT void Append(const occ::handle<SelectMgr_Selection>& theSelection);

  Standard_EXPORT void Remove(const occ::handle<SelectMgr_Selection>& theSelection);

  Standard_EXPORT Select3D_BndBox3d Box(const int theIndex) const override;

  using BVH_PrimitiveSet3d::Box;

  Standard_EXPORT double Center(const int theIndex, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIndex1, const int theIndex2) override;

  Standard_EXPORT int Size() const override;

  Standard_EXPORT const occ::handle<SelectMgr_SensitiveEntity>& GetSensitiveById(
    const int theIndex) const;

  const NCollection_IndexedMap<occ::handle<SelectMgr_SensitiveEntity>>& Sensitives() const
  {
    return mySensitives;
  }

  const NCollection_DataMap<occ::handle<SelectMgr_EntityOwner>, int>& Owners() const
  {
    return myOwnersMap;
  }

  bool HasEntityWithPersistence() const { return myNbEntityWithPersistence > 0; }

protected:
  Standard_EXPORT void addOwner(const occ::handle<SelectMgr_EntityOwner>& theOwner);

  Standard_EXPORT void removeOwner(const occ::handle<SelectMgr_EntityOwner>& theOwner);

private:
  NCollection_IndexedMap<occ::handle<SelectMgr_SensitiveEntity>> mySensitives;
  NCollection_DataMap<occ::handle<SelectMgr_EntityOwner>, int>   myOwnersMap;
  int                                                            myNbEntityWithPersistence;
};
