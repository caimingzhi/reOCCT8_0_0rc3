#pragma once

#include <BVH_PrimitiveSet3d.hpp>
#include <Select3D_BVHBuilder3d.hpp>
#include <Select3D_SensitiveEntity.hpp>

class Select3D_SensitiveSet : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveSet, Select3D_SensitiveEntity)
public:
  Standard_EXPORT static const occ::handle<Select3D_BVHBuilder3d>& DefaultBVHBuilder();

  Standard_EXPORT static void SetDefaultBVHBuilder(
    const occ::handle<Select3D_BVHBuilder3d>& theBuilder);

public:
  Standard_EXPORT Select3D_SensitiveSet(const occ::handle<SelectMgr_EntityOwner>& theOwnerId);

public:
  virtual int Size() const = 0;

  virtual Select3D_BndBox3d Box(const int theIdx) const = 0;

  virtual double Center(const int theIdx, const int theAxis) const = 0;

  virtual void Swap(const int theIdx1, const int theIdx2) = 0;

  bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
               SelectBasics_PickResult&             thePickResult) override
  {
    return matches(theMgr, thePickResult, false);
  }

  Standard_EXPORT void BVH() override;

  bool ToBuildBVH() const override { return myContent.IsDirty(); }

  void SetBuilder(const occ::handle<Select3D_BVHBuilder3d>& theBuilder)
  {
    myContent.SetBuilder(theBuilder);
  }

  void MarkDirty() { myContent.MarkDirty(); }

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT void Clear() override;

  int GetLeafNodeSize() const { return myContent.Builder()->LeafNodeSize(); }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT bool matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult,
                               bool                                 theToCheckAllInside);

  virtual bool overlapsElement(SelectBasics_PickResult&             thePickResult,
                               SelectBasics_SelectingVolumeManager& theMgr,
                               int                                  theElemIdx,
                               bool                                 theIsFullInside) = 0;

  virtual bool elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                               int                                  theElemIdx,
                               bool                                 theIsFullInside) = 0;

  virtual double distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr) = 0;

  Standard_EXPORT bool processElements(SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theFirstElem,
                                       int                                  theLastElem,
                                       bool                                 theIsFullInside,
                                       bool                                 theToCheckAllInside,
                                       SelectBasics_PickResult&             thePickResult,
                                       int&                                 theMatchesNb);

protected:
  class BvhPrimitiveSet : public BVH_PrimitiveSet3d
  {
  public:
    BvhPrimitiveSet()
        : BVH_PrimitiveSet3d(occ::handle<Select3D_BVHBuilder3d>()),
          mySensitiveSet(nullptr)
    {
    }

    ~BvhPrimitiveSet() override = default;

    void SetSensitiveSet(Select3D_SensitiveSet* theSensitiveSet)
    {
      mySensitiveSet = theSensitiveSet;
      MarkDirty();
    }

    int Size() const override { return mySensitiveSet->Size(); }

    Select3D_BndBox3d Box(const int theIdx) const override { return mySensitiveSet->Box(theIdx); }

    using BVH_PrimitiveSet3d::Box;

    double Center(const int theIdx, const int theAxis) const override
    {
      return mySensitiveSet->Center(theIdx, theAxis);
    }

    void Swap(const int theIdx1, const int theIdx2) override
    {
      mySensitiveSet->Swap(theIdx1, theIdx2);
    }

    const opencascade::handle<BVH_Tree<double, 3>>& GetBVH() { return BVH(); }

    void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
    {
      (void)theOStream;
      (void)theDepth;
    }

  protected:
    Select3D_SensitiveSet* mySensitiveSet;
  };

protected:
  BvhPrimitiveSet myContent;
  int             myDetectedIdx;
};
