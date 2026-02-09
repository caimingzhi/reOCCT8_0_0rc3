#pragma once

#include <NCollection_Handle.hpp>
#include <Select3D_BVHBuilder3d.hpp>
#include <SelectMgr_SelectableObject.hpp>

class SelectMgr_SelectableObjectSet
{
public:
  enum BVHSubset
  {
    BVHSubset_3d,
    BVHSubset_3dPersistent,
    BVHSubset_2dPersistent,
    BVHSubset_ortho3dPersistent,
    BVHSubset_ortho2dPersistent,
    BVHSubsetNb
  };

public:
  class Iterator
  {

    typedef NCollection_IndexedMap<occ::handle<SelectMgr_SelectableObject>>::Iterator
      ObjectMapIterator;

  public:
    Iterator()
        : mySet(nullptr),
          mySubsetIdx(BVHSubsetNb)
    {
    }

    Iterator(const SelectMgr_SelectableObjectSet& theSet) { Init(theSet); }

    void Init(const SelectMgr_SelectableObjectSet& theSet)
    {
      mySet       = &theSet;
      mySubsetIdx = 0;
      mySubsetIt  = ObjectMapIterator(theSet.myObjects[mySubsetIdx]);
      More();
    }

    bool More()
    {
      if (mySubsetIt.More())
      {
        return true;
      }
      else if ((mySubsetIdx == BVHSubsetNb - 1) || mySet == nullptr)
      {
        return false;
      }
      mySubsetIt = ObjectMapIterator(mySet->myObjects[++mySubsetIdx]);
      return More();
    }

    void Next() { mySubsetIt.Next(); }

    const occ::handle<SelectMgr_SelectableObject>& Value() const { return mySubsetIt.Value(); }

  private:
    const SelectMgr_SelectableObjectSet* mySet;
    int                                  mySubsetIdx;
    ObjectMapIterator                    mySubsetIt;
  };

public:
  Standard_EXPORT SelectMgr_SelectableObjectSet();

  virtual ~SelectMgr_SelectableObjectSet() = default;

  Standard_EXPORT bool Append(const occ::handle<SelectMgr_SelectableObject>& theObject);

  Standard_EXPORT bool Remove(const occ::handle<SelectMgr_SelectableObject>& theObject);

  Standard_EXPORT void ChangeSubset(const occ::handle<SelectMgr_SelectableObject>& theObject);

  Standard_EXPORT void UpdateBVH(const occ::handle<Graphic3d_Camera>& theCam,
                                 const NCollection_Vec2<int>&         theWinSize);

  Standard_EXPORT void MarkDirty();

  bool Contains(const occ::handle<SelectMgr_SelectableObject>& theObject) const
  {
    return myObjects[BVHSubset_3d].Contains(theObject)
           || myObjects[BVHSubset_3dPersistent].Contains(theObject)
           || myObjects[BVHSubset_2dPersistent].Contains(theObject)
           || myObjects[BVHSubset_ortho3dPersistent].Contains(theObject)
           || myObjects[BVHSubset_ortho2dPersistent].Contains(theObject);
  }

  bool IsEmpty() const
  {
    return myObjects[BVHSubset_3d].IsEmpty() && myObjects[BVHSubset_3dPersistent].IsEmpty()
           && myObjects[BVHSubset_2dPersistent].IsEmpty()
           && myObjects[BVHSubset_ortho3dPersistent].IsEmpty()
           && myObjects[BVHSubset_ortho2dPersistent].IsEmpty();
  }

  bool IsEmpty(const BVHSubset theSubset) const { return myObjects[theSubset].IsEmpty(); }

  const occ::handle<SelectMgr_SelectableObject>& GetObjectById(const BVHSubset theSubset,
                                                               const int       theIndex) const
  {
    return myObjects[theSubset].FindKey(theIndex + 1);
  }

  const opencascade::handle<BVH_Tree<double, 3>>& BVH(const BVHSubset theSubset) const
  {
    return myBVH[theSubset];
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  int appropriateSubset(const occ::handle<SelectMgr_SelectableObject>& theObject)
  {
    if (theObject->TransformPersistence().IsNull())
    {
      const NCollection_Sequence<occ::handle<PrsMgr_Presentation>>& aPresentations =
        theObject->Presentations();
      for (NCollection_Sequence<occ::handle<PrsMgr_Presentation>>::Iterator aPrsIter(
             aPresentations);
           aPrsIter.More();
           aPrsIter.Next())
      {
        const occ::handle<PrsMgr_Presentation>& aPrs3d = aPrsIter.ChangeValue();
        if (aPrs3d->CStructure()->HasGroupTransformPersistence())
        {
          return SelectMgr_SelectableObjectSet::BVHSubset_3dPersistent;
        }
      }
      return SelectMgr_SelectableObjectSet::BVHSubset_3d;
    }
    else if ((theObject->TransformPersistence()->Mode() & Graphic3d_TMF_2d) != 0)
    {
      if (theObject->TransformPersistence()->IsOrthoPers())
      {
        return SelectMgr_SelectableObjectSet::BVHSubset_ortho2dPersistent;
      }
      return SelectMgr_SelectableObjectSet::BVHSubset_2dPersistent;
    }
    else if (theObject->TransformPersistence()->IsOrthoPers())
    {
      return SelectMgr_SelectableObjectSet::BVHSubset_ortho3dPersistent;
    }
    else
    {
      return SelectMgr_SelectableObjectSet::BVHSubset_3dPersistent;
    }
  }

  int currentSubset(const occ::handle<SelectMgr_SelectableObject>& theObject)
  {
    for (int aSubsetIdx = 0; aSubsetIdx < BVHSubsetNb; ++aSubsetIdx)
    {
      if (myObjects[aSubsetIdx].Contains(theObject))
      {
        return aSubsetIdx;
      }
    }
    return -1;
  }

private:
  NCollection_IndexedMap<occ::handle<SelectMgr_SelectableObject>> myObjects[BVHSubsetNb];
  opencascade::handle<BVH_Tree<double, 3>>                        myBVH[BVHSubsetNb];
  occ::handle<Select3D_BVHBuilder3d>                              myBuilder[BVHSubsetNb];
  bool                                                            myIsDirty[BVHSubsetNb];
  Graphic3d_WorldViewProjState                                    myLastViewState;
  NCollection_Vec2<int>                                           myLastWinSize;

  friend class Iterator;
};
