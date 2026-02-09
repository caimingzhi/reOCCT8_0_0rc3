#include <SelectMgr_SensitiveEntitySet.hpp>

#include <Graphic3d_TransformPers.hpp>
#include <Select3D_SensitiveEntity.hpp>
#include <SelectMgr_SensitiveEntity.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_SensitiveEntitySet, BVH_PrimitiveSet3d)

SelectMgr_SensitiveEntitySet::SelectMgr_SensitiveEntitySet(
  const occ::handle<Select3D_BVHBuilder3d>& theBuilder)
    : BVH_PrimitiveSet3d(theBuilder)
{
  myNbEntityWithPersistence = 0;
}

void SelectMgr_SensitiveEntitySet::Append(const occ::handle<SelectMgr_SensitiveEntity>& theEntity)
{
  if (!theEntity->BaseSensitive()->IsKind(STANDARD_TYPE(Select3D_SensitiveEntity)))
  {
    theEntity->ResetSelectionActiveStatus();
    return;
  }
  const int anExtent = mySensitives.Extent();
  if (mySensitives.Add(theEntity) > anExtent)
  {
    addOwner(theEntity->BaseSensitive()->OwnerId());
  }
  if (!theEntity->BaseSensitive()->TransformPersistence().IsNull())
  {
    ++myNbEntityWithPersistence;
  }
  MarkDirty();
}

void SelectMgr_SensitiveEntitySet::Append(const occ::handle<SelectMgr_Selection>& theSelection)
{
  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator aSelEntIter(
         theSelection->Entities());
       aSelEntIter.More();
       aSelEntIter.Next())
  {
    const occ::handle<SelectMgr_SensitiveEntity>& aSensEnt = aSelEntIter.Value();
    if (!aSensEnt->BaseSensitive()->IsKind(STANDARD_TYPE(Select3D_SensitiveEntity)))
    {
      aSensEnt->ResetSelectionActiveStatus();
      continue;
    }

    const int anExtent = mySensitives.Extent();
    if (mySensitives.Add(aSensEnt) > anExtent)
    {
      addOwner(aSensEnt->BaseSensitive()->OwnerId());
    }
    if (!aSensEnt->BaseSensitive()->TransformPersistence().IsNull())
    {
      ++myNbEntityWithPersistence;
    }
  }
  MarkDirty();
}

void SelectMgr_SensitiveEntitySet::Remove(const occ::handle<SelectMgr_Selection>& theSelection)
{
  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator aSelEntIter(
         theSelection->Entities());
       aSelEntIter.More();
       aSelEntIter.Next())
  {
    const occ::handle<SelectMgr_SensitiveEntity>& aSensEnt = aSelEntIter.Value();
    const int                                     anEntIdx = mySensitives.FindIndex(aSensEnt);
    if (anEntIdx == 0)
    {
      continue;
    }

    if (anEntIdx != mySensitives.Size())
    {
      Swap(anEntIdx - 1, mySensitives.Size() - 1);
    }
    if (!aSensEnt->BaseSensitive()->TransformPersistence().IsNull())
    {
      --myNbEntityWithPersistence;
    }

    mySensitives.RemoveLast();
    removeOwner(aSensEnt->BaseSensitive()->OwnerId());
  }

  MarkDirty();
}

Select3D_BndBox3d SelectMgr_SensitiveEntitySet::Box(const int theIndex) const
{
  const occ::handle<Select3D_SensitiveEntity>& aSensitive =
    GetSensitiveById(theIndex)->BaseSensitive();
  if (!aSensitive->TransformPersistence().IsNull())
  {
    return Select3D_BndBox3d();
  }

  return aSensitive->BoundingBox();
}

double SelectMgr_SensitiveEntitySet::Center(const int theIndex, const int theAxis) const
{
  const occ::handle<Select3D_SensitiveEntity>& aSensitive =
    GetSensitiveById(theIndex)->BaseSensitive();
  const gp_Pnt aCenter      = aSensitive->CenterOfGeometry();
  double       aCenterCoord = 0.0;
  aCenterCoord = theAxis == 0 ? aCenter.X() : (theAxis == 1 ? aCenter.Y() : aCenter.Z());

  return aCenterCoord;
}

void SelectMgr_SensitiveEntitySet::Swap(const int theIndex1, const int theIndex2)
{
  mySensitives.Swap(theIndex1 + 1, theIndex2 + 1);
}

int SelectMgr_SensitiveEntitySet::Size() const
{
  return mySensitives.Size();
}

const occ::handle<SelectMgr_SensitiveEntity>& SelectMgr_SensitiveEntitySet::GetSensitiveById(
  const int theIndex) const
{
  return mySensitives.FindKey(theIndex + 1);
}

void SelectMgr_SensitiveEntitySet::addOwner(const occ::handle<SelectMgr_EntityOwner>& theOwner)
{
  if (!theOwner.IsNull())
  {
    if (int* aNumber = myOwnersMap.ChangeSeek(theOwner))
    {
      ++(*aNumber);
    }
    else
    {
      myOwnersMap.Bind(theOwner, 1);
    }
  }
}

void SelectMgr_SensitiveEntitySet::removeOwner(const occ::handle<SelectMgr_EntityOwner>& theOwner)
{
  if (int* aNumber = !theOwner.IsNull() ? myOwnersMap.ChangeSeek(theOwner) : nullptr)
  {
    if (--(*aNumber) == 0)
    {
      myOwnersMap.UnBind(theOwner);
    }
  }
}
