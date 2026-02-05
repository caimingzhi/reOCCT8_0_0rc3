#include <BOPDS_SubIterator.hpp>

#include <Bnd_Tools.hpp>

#include <BOPDS_DS.hpp>
#include <BOPDS_Pair.hpp>
#include <NCollection_Map.hpp>

#include <BOPTools_BoxTree.hpp>

#include <algorithm>

//=================================================================================================

BOPDS_SubIterator::BOPDS_SubIterator()
    : myAllocator(NCollection_BaseAllocator::CommonBaseAllocator()),
      myList(1, myAllocator)
{
  myDS = nullptr;
}

//=================================================================================================

BOPDS_SubIterator::BOPDS_SubIterator(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : myAllocator(theAllocator),
      myList(1, myAllocator)
{
  myDS = nullptr;
}

//=================================================================================================

BOPDS_SubIterator::~BOPDS_SubIterator() = default;

//=================================================================================================

void BOPDS_SubIterator::Initialize()
{
  // sort interfering pairs for constant order of intersection
  std::stable_sort(myList.begin(), myList.end());
  // initialize iterator to access the pairs
  myIterator.Init(myList);
}

//=================================================================================================

void BOPDS_SubIterator::Value(int& theI1, int& theI2) const
{
  int iT1, iT2, n1, n2;
  //
  const BOPDS_Pair& aPKB = myIterator.Value();
  aPKB.Indices(n1, n2);
  //
  iT1 = (int)(myDS->ShapeInfo(n1).ShapeType());
  iT2 = (int)(myDS->ShapeInfo(n2).ShapeType());
  //
  theI1 = n1;
  theI2 = n2;
  if (iT1 < iT2)
  {
    theI1 = n2;
    theI2 = n1;
  }
}

//=================================================================================================

void BOPDS_SubIterator::Prepare()
{
  myList.Clear();
  //
  if (!myDS)
  {
    return;
  }
  //
  if (!mySubSet1->Extent() || !mySubSet2->Extent())
  {
    return;
  }
  //
  myList.SetIncrement(2 * (mySubSet1->Extent() + mySubSet2->Extent()));
  //
  Intersect();
}

//=================================================================================================

void BOPDS_SubIterator::Intersect()
{
  if (!mySubSet1->Extent() || !mySubSet2->Extent())
    return;

  // Construct BVH tree for each sub-set
  BOPTools_BoxTree aBBTree[2];
  for (int i = 0; i < 2; ++i)
  {
    const NCollection_List<int>* aSubSet = !i ? mySubSet1 : mySubSet2;
    aBBTree[i].SetSize(aSubSet->Extent());
    for (NCollection_List<int>::Iterator it(*aSubSet); it.More(); it.Next())
    {
      const int              nS     = it.Value();
      const BOPDS_ShapeInfo& aSI    = myDS->ShapeInfo(nS);
      const Bnd_Box&         aBoxEx = aSI.Box();
      aBBTree[i].Add(nS, Bnd_Tools::Bnd2BVH(aBoxEx));
    }
    aBBTree[i].Build();
  }

  // Perform selection of the interfering pairs
  BOPTools_BoxPairSelector aPairSelector;
  aPairSelector.SetBVHSets(&aBBTree[0], &aBBTree[1]);
  aPairSelector.Select();
  aPairSelector.Sort();

  // Treat the selected pairs
  const std::vector<BOPTools_BoxPairSelector::PairIDs>& aPairs   = aPairSelector.Pairs();
  const int                                             aNbPairs = static_cast<int>(aPairs.size());

  // Fence map
  NCollection_Map<BOPDS_Pair> aMPKFence;

  for (int iPair = 0; iPair < aNbPairs; ++iPair)
  {
    const BOPTools_BoxPairSelector::PairIDs& aPair = aPairs[iPair];
    if (aPair.ID1 == aPair.ID2)
      continue;

    BOPDS_Pair aDSPair(std::min(aPair.ID1, aPair.ID2), std::max(aPair.ID1, aPair.ID2));
    if (!aMPKFence.Add(aDSPair))
      continue;

    const BOPDS_ShapeInfo& aSI1 = myDS->ShapeInfo(aPair.ID1);
    const BOPDS_ShapeInfo& aSI2 = myDS->ShapeInfo(aPair.ID2);

    const TopAbs_ShapeEnum aType1 = aSI1.ShapeType();
    const TopAbs_ShapeEnum aType2 = aSI2.ShapeType();

    int iType1 = BOPDS_Tools::TypeToInteger(aType1);
    int iType2 = BOPDS_Tools::TypeToInteger(aType2);

    // avoid interfering of the shape with its sub-shapes
    if (((iType1 < iType2) && aSI1.HasSubShape(aPair.ID2))
        || ((iType1 > iType2) && aSI2.HasSubShape(aPair.ID1)))
      continue;

    myList.Append(aDSPair);
  }
}
