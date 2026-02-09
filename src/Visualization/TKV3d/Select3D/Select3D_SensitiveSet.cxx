#include <Select3D_SensitiveSet.hpp>

#include <BVH_LinearBuilder.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitiveSet, Select3D_SensitiveEntity)

namespace
{

  static occ::handle<Select3D_BVHBuilder3d> THE_SENS_SET_BUILDER =
    new BVH_LinearBuilder<double, 3>(BVH_Constants_LeafNodeSizeSmall, BVH_Constants_MaxTreeDepth);
}

const occ::handle<Select3D_BVHBuilder3d>& Select3D_SensitiveSet::DefaultBVHBuilder()
{
  return THE_SENS_SET_BUILDER;
}

void Select3D_SensitiveSet::SetDefaultBVHBuilder(
  const occ::handle<Select3D_BVHBuilder3d>& theBuilder)
{
  THE_SENS_SET_BUILDER = theBuilder;
}

Select3D_SensitiveSet::Select3D_SensitiveSet(const occ::handle<SelectMgr_EntityOwner>& theOwnerId)
    : Select3D_SensitiveEntity(theOwnerId),
      myDetectedIdx(-1)
{
  myContent.SetSensitiveSet(this);
  myContent.SetBuilder(THE_SENS_SET_BUILDER);
  myContent.MarkDirty();
}

void Select3D_SensitiveSet::BVH()
{
  myContent.GetBVH();
}

namespace
{

  struct NodeInStack
  {
    NodeInStack(int theId = 0, bool theIsFullInside = false)
        : Id(theId),
          IsFullInside(theIsFullInside)
    {
    }

    int Id;

    bool IsFullInside;
  };
} // namespace

bool Select3D_SensitiveSet::processElements(SelectBasics_SelectingVolumeManager& theMgr,
                                            int                                  theFirstElem,
                                            int                                  theLastElem,
                                            bool                                 theIsFullInside,
                                            bool                     theToCheckAllInside,
                                            SelectBasics_PickResult& thePickResult,
                                            int&                     theMatchesNb)
{
  SelectBasics_PickResult aPickResult;
  for (int anIdx = theFirstElem; anIdx <= theLastElem; anIdx++)
  {
    if (!theMgr.IsOverlapAllowed())
    {
      if (!elementIsInside(theMgr, anIdx, theIsFullInside))
      {
        if (theToCheckAllInside)
        {
          continue;
        }
        return false;
      }
    }
    else
    {
      if (!overlapsElement(aPickResult, theMgr, anIdx, theIsFullInside))
      {
        continue;
      }

      if (thePickResult.Depth() > aPickResult.Depth())
      {
        thePickResult = aPickResult;
        myDetectedIdx = anIdx;
      }
    }
    ++theMatchesNb;
  }

  return true;
}

bool Select3D_SensitiveSet::matches(SelectBasics_SelectingVolumeManager& theMgr,
                                    SelectBasics_PickResult&             thePickResult,
                                    bool                                 theToCheckAllInside)
{
  myDetectedIdx = -1;

  if (myContent.Size() < 1)
  {
    return false;
  }

  const Select3D_BndBox3d& aGlobalBox   = myContent.Box();
  bool                     isFullInside = true;

  if (!theMgr.OverlapsBox(aGlobalBox.CornerMin(), aGlobalBox.CornerMax(), &isFullInside))
  {
    return false;
  }

  int aMatchesNb = -1;

  const bool toCheckFullInside = (theMgr.GetActiveSelectionType() != SelectMgr_SelectionType_Point);
  if (toCheckFullInside && isFullInside)
  {
    int aSize = myContent.Size();
    if (!processElements(theMgr,
                         0,
                         aSize - 1,
                         true,
                         theToCheckAllInside,
                         thePickResult,
                         aMatchesNb))
    {
      return false;
    }
  }
  else
  {
    const BVH_Tree<double, 3, BVH_BinaryTree>* aBVH = myContent.GetBVH().get();
    NodeInStack                                aStack[BVH_Constants_MaxTreeDepth];
    NodeInStack                                aNode;

    int aHead = -1;

    for (;;)
    {
      const BVH_Vec4i& aData = aBVH->NodeInfoBuffer()[aNode.Id];

      if (aData.x() == 0)
      {
        NodeInStack aLeft(aData.y(), toCheckFullInside), aRight(aData.z(), toCheckFullInside);
        bool        toCheckLft = true, toCheckRgh = true;
        if (!aNode.IsFullInside)
        {
          toCheckLft = theMgr.OverlapsBox(aBVH->MinPoint(aLeft.Id),
                                          aBVH->MaxPoint(aLeft.Id),
                                          toCheckFullInside ? &aLeft.IsFullInside : nullptr);
          if (!toCheckLft)
          {
            aLeft.IsFullInside = false;
          }

          toCheckRgh = theMgr.OverlapsBox(aBVH->MinPoint(aRight.Id),
                                          aBVH->MaxPoint(aRight.Id),
                                          toCheckFullInside ? &aRight.IsFullInside : nullptr);
          if (!toCheckRgh)
          {
            aRight.IsFullInside = false;
          }
        }

        if (!theMgr.IsOverlapAllowed())
        {
          if (!theToCheckAllInside)
          {
            if (!toCheckLft || !toCheckRgh)
            {
              return false;
            }

            toCheckLft &= !aLeft.IsFullInside;
            toCheckRgh &= !aRight.IsFullInside;
          }
        }

        if (toCheckLft || toCheckRgh)
        {
          aNode = toCheckLft ? aLeft : aRight;
          if (toCheckLft && toCheckRgh)
          {
            aStack[++aHead] = aRight;
          }
        }
        else
        {
          if (aHead < 0)
            break;

          aNode = aStack[aHead--];
        }
      }
      else
      {
        if (!processElements(theMgr,
                             aData.y(),
                             aData.z(),
                             aNode.IsFullInside,
                             theToCheckAllInside,
                             thePickResult,
                             aMatchesNb))
        {
          return false;
        }

        if (aHead < 0)
          break;

        aNode = aStack[aHead--];
      }
    }
  }

  if (aMatchesNb != -1)
  {
    thePickResult.SetDistToGeomCenter(distanceToCOG(theMgr));
  }

  return aMatchesNb != -1 || (!theToCheckAllInside && !theMgr.IsOverlapAllowed());
}

Select3D_BndBox3d Select3D_SensitiveSet::BoundingBox()
{
  return Select3D_BndBox3d(NCollection_Vec3<double>(RealLast()),
                           NCollection_Vec3<double>(RealFirst()));
}

gp_Pnt Select3D_SensitiveSet::CenterOfGeometry() const
{
  return gp_Pnt(RealLast(), RealLast(), RealLast());
}

void Select3D_SensitiveSet::Clear() {}

void Select3D_SensitiveSet::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Select3D_SensitiveEntity)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myContent)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDetectedIdx)

  Select3D_BndBox3d aBoundingBox = ((Select3D_SensitiveSet*)this)->BoundingBox();
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &aBoundingBox)
}
