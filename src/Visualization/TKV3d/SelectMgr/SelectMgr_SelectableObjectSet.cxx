#include <SelectMgr_SelectableObjectSet.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Mat4.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>

#include <BVH_BinnedBuilder.hpp>
#include <BVH_LinearBuilder.hpp>

namespace
{

  typedef NCollection_IndexedMap<occ::handle<SelectMgr_SelectableObject>> ObjectsMap;

  class BVHBuilderAdaptorRegular : public BVH_Set<double, 3>
  {
  public:
    BVHBuilderAdaptorRegular(ObjectsMap& theObjects)
        : myObjects(theObjects) {};

    Select3D_BndBox3d Box(const int theIndex) const override
    {
      const occ::handle<SelectMgr_SelectableObject>& anObject = myObjects.FindKey(theIndex + 1);
      Bnd_Box                                        aBox;
      anObject->BoundingBox(aBox);
      if (aBox.IsVoid())
        return Select3D_BndBox3d();

      return Select3D_BndBox3d(
        NCollection_Vec3<double>(aBox.CornerMin().X(), aBox.CornerMin().Y(), aBox.CornerMin().Z()),
        NCollection_Vec3<double>(aBox.CornerMax().X(), aBox.CornerMax().Y(), aBox.CornerMax().Z()));
    }

    Select3D_BndBox3d Box() const override
    {
      if (!myBox.IsValid())
      {
        myBox = BVH_Set<double, 3>::Box();
      }
      return myBox;
    }

    using BVH_Set<double, 3>::Box;

    double Center(const int theIndex, const int theAxis) const override
    {
      const Select3D_BndBox3d aBndBox = Box(theIndex);

      return (aBndBox.CornerMin()[theAxis] + aBndBox.CornerMax()[theAxis]) * 0.5;
    }

    int Size() const override { return myObjects.Size(); }

    void Swap(const int theIndex1, const int theIndex2) override
    {
      myObjects.Swap(theIndex1 + 1, theIndex2 + 1);
    }

  private:
    BVHBuilderAdaptorRegular& operator=(const BVHBuilderAdaptorRegular&) { return *this; }

  private:
    ObjectsMap&               myObjects;
    mutable Select3D_BndBox3d myBox;
  };

  class BVHBuilderAdaptorPersistent : public BVH_Set<double, 3>
  {
  public:
    BVHBuilderAdaptorPersistent(ObjectsMap&                          theObjects,
                                const occ::handle<Graphic3d_Camera>& theCamera,
                                const NCollection_Mat4<double>&      theProjectionMat,
                                const NCollection_Mat4<double>&      theWorldViewMat,
                                const NCollection_Vec2<int>&         theWinSize)
        : myObjects(theObjects)
    {
      myBoundings.ReSize(myObjects.Size());
      for (int anI = 1; anI <= myObjects.Size(); ++anI)
      {
        const occ::handle<SelectMgr_SelectableObject>& anObject = myObjects(anI);

        Bnd_Box aBoundingBox;
        anObject->BoundingBox(aBoundingBox);
        if (!aBoundingBox.IsVoid() && !anObject->TransformPersistence().IsNull())
        {
          anObject->TransformPersistence()->Apply(theCamera,
                                                  theProjectionMat,
                                                  theWorldViewMat,
                                                  theWinSize.x(),
                                                  theWinSize.y(),
                                                  aBoundingBox);
        }

        for (NCollection_Sequence<occ::handle<PrsMgr_Presentation>>::Iterator aPrsIter(
               anObject->Presentations());
             aPrsIter.More();
             aPrsIter.Next())
        {
          const occ::handle<PrsMgr_Presentation>& aPrs3d = aPrsIter.Value();
          if (!aPrs3d->CStructure()->HasGroupTransformPersistence())
          {
            continue;
          }

          for (NCollection_Sequence<occ::handle<Graphic3d_Group>>::Iterator aGroupIter(
                 aPrs3d->Groups());
               aGroupIter.More();
               aGroupIter.Next())
          {
            const occ::handle<Graphic3d_Group>& aGroup  = aGroupIter.Value();
            const Graphic3d_BndBox4f&           aBndBox = aGroup->BoundingBox();
            if (aGroup->TransformPersistence().IsNull() || !aBndBox.IsValid())
            {
              continue;
            }

            Bnd_Box aGroupBox;
            aGroupBox.Update(aBndBox.CornerMin().x(),
                             aBndBox.CornerMin().y(),
                             aBndBox.CornerMin().z(),
                             aBndBox.CornerMax().x(),
                             aBndBox.CornerMax().y(),
                             aBndBox.CornerMax().z());
            aGroup->TransformPersistence()->Apply(theCamera,
                                                  theProjectionMat,
                                                  theWorldViewMat,
                                                  theWinSize.x(),
                                                  theWinSize.y(),
                                                  aGroupBox);
            aBoundingBox.Add(aGroupBox);
          }
        }

        if (aBoundingBox.IsVoid())
        {
          myBoundings.Add(new Select3D_HBndBox3d());
        }
        else
        {
          const gp_Pnt aMin = aBoundingBox.CornerMin();
          const gp_Pnt aMax = aBoundingBox.CornerMax();
          myBoundings.Add(
            new Select3D_HBndBox3d(NCollection_Vec3<double>(aMin.X(), aMin.Y(), aMin.Z()),
                                   NCollection_Vec3<double>(aMax.X(), aMax.Y(), aMax.Z())));
        }
      }
    }

    Select3D_BndBox3d Box(const int theIndex) const override { return *myBoundings(theIndex + 1); }

    Select3D_BndBox3d Box() const override
    {
      if (!myBox.IsValid())
      {
        myBox = BVH_Set<double, 3>::Box();
      }
      return myBox;
    }

    using BVH_Set<double, 3>::Box;

    double Center(const int theIndex, const int theAxis) const override
    {
      const Select3D_BndBox3d& aBoundingBox = *myBoundings(theIndex + 1);

      return (aBoundingBox.CornerMin()[theAxis] + aBoundingBox.CornerMax()[theAxis]) * 0.5;
    }

    int Size() const override { return myObjects.Size(); }

    void Swap(const int theIndex1, const int theIndex2) override
    {
      const int aStructIdx1 = theIndex1 + 1;
      const int aStructIdx2 = theIndex2 + 1;

      myObjects.Swap(aStructIdx1, aStructIdx2);
      myBoundings.Swap(aStructIdx1, aStructIdx2);
    }

  private:
    BVHBuilderAdaptorPersistent& operator=(const BVHBuilderAdaptorPersistent&) { return *this; }

  private:
    ObjectsMap&                                             myObjects;
    mutable Select3D_BndBox3d                               myBox;
    typedef NCollection_Shared<Select3D_BndBox3d>           Select3D_HBndBox3d;
    NCollection_IndexedMap<occ::handle<Select3D_HBndBox3d>> myBoundings;
  };

  static const NCollection_Mat4<double> SelectMgr_SelectableObjectSet_THE_IDENTITY_MAT;
} // namespace

SelectMgr_SelectableObjectSet::SelectMgr_SelectableObjectSet()
{
  myBVH[BVHSubset_ortho2dPersistent] = new BVH_Tree<double, 3>();
  myBVH[BVHSubset_ortho3dPersistent] = new BVH_Tree<double, 3>();
  myBVH[BVHSubset_2dPersistent]      = new BVH_Tree<double, 3>();
  myBVH[BVHSubset_3dPersistent]      = new BVH_Tree<double, 3>();
  myBVH[BVHSubset_3d]                = new BVH_Tree<double, 3>();

  myBuilder[BVHSubset_ortho2dPersistent] =
    new BVH_LinearBuilder<double, 3>(BVH_Constants_LeafNodeSizeSingle, BVH_Constants_MaxTreeDepth);
  myBuilder[BVHSubset_ortho3dPersistent] =
    new BVH_LinearBuilder<double, 3>(BVH_Constants_LeafNodeSizeSingle, BVH_Constants_MaxTreeDepth);
  myBuilder[BVHSubset_2dPersistent] =
    new BVH_LinearBuilder<double, 3>(BVH_Constants_LeafNodeSizeSingle, BVH_Constants_MaxTreeDepth);
  myBuilder[BVHSubset_3dPersistent] =
    new BVH_LinearBuilder<double, 3>(BVH_Constants_LeafNodeSizeSingle, BVH_Constants_MaxTreeDepth);
  myBuilder[BVHSubset_3d] = new BVH_BinnedBuilder<double, 3, 4>(BVH_Constants_LeafNodeSizeSingle,
                                                                BVH_Constants_MaxTreeDepth,
                                                                true);

  myIsDirty[BVHSubset_ortho2dPersistent] = false;
  myIsDirty[BVHSubset_ortho3dPersistent] = false;
  myIsDirty[BVHSubset_2dPersistent]      = false;
  myIsDirty[BVHSubset_3dPersistent]      = false;
  myIsDirty[BVHSubset_3d]                = false;
}

bool SelectMgr_SelectableObjectSet::Append(const occ::handle<SelectMgr_SelectableObject>& theObject)
{

  const int aSubsetIdx = appropriateSubset(theObject);

  if (currentSubset(theObject) != -1)
  {
    return false;
  }

  const int aSize = myObjects[aSubsetIdx].Size();

  if (aSize < myObjects[aSubsetIdx].Add(theObject))
  {
    myIsDirty[aSubsetIdx] = true;

    return true;
  }

  return false;
}

bool SelectMgr_SelectableObjectSet::Remove(const occ::handle<SelectMgr_SelectableObject>& theObject)
{

  for (int aSubsetIdx = 0; aSubsetIdx < BVHSubsetNb; ++aSubsetIdx)
  {
    const int anIndex = myObjects[aSubsetIdx].FindIndex(theObject);

    if (anIndex != 0)
    {
      const int aSize = myObjects[aSubsetIdx].Size();

      if (anIndex != aSize)
      {
        myObjects[aSubsetIdx].Swap(anIndex, aSize);
      }

      myObjects[aSubsetIdx].RemoveLast();
      myIsDirty[aSubsetIdx] = true;

      return true;
    }
  }

  return false;
}

void SelectMgr_SelectableObjectSet::ChangeSubset(
  const occ::handle<SelectMgr_SelectableObject>& theObject)
{

  const int aCurrSubsetIdx = currentSubset(theObject);

  if (aCurrSubsetIdx < 0)
  {
    return;
  }

  const int aSubsetIdx = appropriateSubset(theObject);

  if (aCurrSubsetIdx == aSubsetIdx)
  {
    return;
  }

  Remove(theObject);
  Append(theObject);
}

void SelectMgr_SelectableObjectSet::UpdateBVH(const occ::handle<Graphic3d_Camera>& theCam,
                                              const NCollection_Vec2<int>&         theWinSize)
{

  if (!IsEmpty(BVHSubset_3d) && myIsDirty[BVHSubset_3d])
  {

    BVHBuilderAdaptorRegular anAdaptor(myObjects[BVHSubset_3d]);

    myBuilder[BVHSubset_3d]->Build(&anAdaptor, myBVH[BVHSubset_3d].get(), anAdaptor.Box());

    myIsDirty[BVHSubset_3d] = false;
  }

  if (!theCam.IsNull())
  {
    const bool                          isWinSizeChanged = myLastWinSize != theWinSize;
    const NCollection_Mat4<double>&     aProjMat         = theCam->ProjectionMatrix();
    const NCollection_Mat4<double>&     aWorldViewMat    = theCam->OrientationMatrix();
    const Graphic3d_WorldViewProjState& aViewState       = theCam->WorldViewProjState();

    if (!IsEmpty(BVHSubset_3dPersistent)
        && (myIsDirty[BVHSubset_3dPersistent] || myLastViewState.IsChanged(aViewState)
            || isWinSizeChanged))
    {

      BVHBuilderAdaptorPersistent anAdaptor(myObjects[BVHSubset_3dPersistent],
                                            theCam,
                                            aProjMat,
                                            aWorldViewMat,
                                            theWinSize);

      myBuilder[BVHSubset_3dPersistent]->Build(&anAdaptor,
                                               myBVH[BVHSubset_3dPersistent].get(),
                                               anAdaptor.Box());
    }

    if (!IsEmpty(BVHSubset_2dPersistent)
        && (myIsDirty[BVHSubset_2dPersistent] || myLastViewState.IsProjectionChanged(aViewState)
            || isWinSizeChanged))
    {

      BVHBuilderAdaptorPersistent anAdaptor(myObjects[BVHSubset_2dPersistent],
                                            theCam,
                                            aProjMat,
                                            SelectMgr_SelectableObjectSet_THE_IDENTITY_MAT,
                                            theWinSize);

      myBuilder[BVHSubset_2dPersistent]->Build(&anAdaptor,
                                               myBVH[BVHSubset_2dPersistent].get(),
                                               anAdaptor.Box());
    }

    if (!IsEmpty(BVHSubset_ortho3dPersistent)
        && (myIsDirty[BVHSubset_ortho3dPersistent] || myLastViewState.IsChanged(aViewState)
            || isWinSizeChanged))
    {

      occ::handle<Graphic3d_Camera> aNewOrthoCam = new Graphic3d_Camera(*theCam);

      aNewOrthoCam->SetProjectionType(Graphic3d_Camera::Projection_Orthographic);

      BVHBuilderAdaptorPersistent anAdaptor(myObjects[BVHSubset_ortho3dPersistent],
                                            aNewOrthoCam,
                                            aNewOrthoCam->ProjectionMatrix(),
                                            aNewOrthoCam->OrientationMatrix(),
                                            theWinSize);

      myBuilder[BVHSubset_ortho3dPersistent]->Build(&anAdaptor,
                                                    myBVH[BVHSubset_ortho3dPersistent].get(),
                                                    anAdaptor.Box());
    }

    if (!IsEmpty(BVHSubset_ortho2dPersistent)
        && (myIsDirty[BVHSubset_ortho2dPersistent]
            || myLastViewState.IsProjectionChanged(aViewState) || isWinSizeChanged))
    {

      occ::handle<Graphic3d_Camera> aNewOrthoCam = new Graphic3d_Camera(*theCam);

      aNewOrthoCam->SetProjectionType(Graphic3d_Camera::Projection_Orthographic);

      BVHBuilderAdaptorPersistent anAdaptor(myObjects[BVHSubset_ortho2dPersistent],
                                            aNewOrthoCam,
                                            aNewOrthoCam->ProjectionMatrix(),
                                            SelectMgr_SelectableObjectSet_THE_IDENTITY_MAT,
                                            theWinSize);

      myBuilder[BVHSubset_ortho2dPersistent]->Build(&anAdaptor,
                                                    myBVH[BVHSubset_ortho2dPersistent].get(),
                                                    anAdaptor.Box());
    }

    myIsDirty[BVHSubset_3dPersistent]      = false;
    myIsDirty[BVHSubset_2dPersistent]      = false;
    myIsDirty[BVHSubset_ortho3dPersistent] = false;
    myIsDirty[BVHSubset_ortho2dPersistent] = false;

    myLastViewState = aViewState;
  }

  myLastWinSize = theWinSize;
}

void SelectMgr_SelectableObjectSet::MarkDirty()
{
  myIsDirty[BVHSubset_3d]                = true;
  myIsDirty[BVHSubset_3dPersistent]      = true;
  myIsDirty[BVHSubset_2dPersistent]      = true;
  myIsDirty[BVHSubset_ortho3dPersistent] = true;
  myIsDirty[BVHSubset_ortho2dPersistent] = true;
}

void SelectMgr_SelectableObjectSet::DumpJson(Standard_OStream& theOStream, int) const
{
  for (int aSubsetIdx = 0; aSubsetIdx < BVHSubsetNb; ++aSubsetIdx)
  {
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, aSubsetIdx)

    bool IsDirty = myIsDirty[aSubsetIdx];
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsDirty)

    for (NCollection_IndexedMap<occ::handle<SelectMgr_SelectableObject>>::Iterator anObjectIt(
           myObjects[aSubsetIdx]);
         anObjectIt.More();
         anObjectIt.Next())
    {
      const occ::handle<SelectMgr_SelectableObject>& SelectableObject = anObjectIt.Value();
      OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, SelectableObject.get())
    }

    TCollection_AsciiString separator;
    OCCT_DUMP_FIELD_VALUE_STRING(theOStream, separator)
  }
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myLastWinSize.x())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myLastWinSize.y())
}
