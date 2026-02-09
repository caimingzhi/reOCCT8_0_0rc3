#include <Bnd_OBB.hpp>
#include <Bnd_Tools.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_IteratorSI.hpp>
#include <BOPDS_Pair.hpp>
#include <BOPDS_ShapeInfo.hpp>
#include <BOPDS_Tools.hpp>
#include <BOPTools_BoxTree.hpp>
#include <BRep_Tool.hpp>
#include <IntTools_Context.hpp>
#include <TopAbs_ShapeEnum.hpp>

BOPDS_IteratorSI::BOPDS_IteratorSI()

  = default;

BOPDS_IteratorSI::BOPDS_IteratorSI(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPDS_Iterator(theAllocator)
{
}

BOPDS_IteratorSI::~BOPDS_IteratorSI() = default;

void BOPDS_IteratorSI::UpdateByLevelOfCheck(const int theLevel)
{
  int i, aNbInterfTypes;

  aNbInterfTypes = BOPDS_DS::NbInterfTypes();
  for (i = theLevel + 1; i < aNbInterfTypes; ++i)
  {
    myLists(i).Clear();
  }
}

void BOPDS_IteratorSI::Intersect(const occ::handle<IntTools_Context>& theCtx,
                                 const bool                           theCheckOBB,
                                 const double                         theFuzzyValue)
{
  const int aNbS = myDS->NbSourceShapes();

  BOPTools_BoxTree aBBTree;
  aBBTree.SetSize(aNbS);

  for (int i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (!aSI.IsInterfering())
      continue;

    const Bnd_Box& aBoxEx = aSI.Box();
    aBBTree.Add(i, Bnd_Tools::Bnd2BVH(aBoxEx));
  }

  aBBTree.Build();

  BOPTools_BoxPairSelector aPairSelector;
  aPairSelector.SetBVHSets(&aBBTree, &aBBTree);
  aPairSelector.SetSame(true);
  aPairSelector.Select();
  aPairSelector.Sort();

  const std::vector<BOPTools_BoxPairSelector::PairIDs>& aPairs   = aPairSelector.Pairs();
  const int                                             aNbPairs = static_cast<int>(aPairs.size());

  for (int iPair = 0; iPair < aNbPairs; ++iPair)
  {
    const BOPTools_BoxPairSelector::PairIDs& aPair = aPairs[iPair];

    const BOPDS_ShapeInfo& aSI1 = myDS->ShapeInfo(aPair.ID1);
    const BOPDS_ShapeInfo& aSI2 = myDS->ShapeInfo(aPair.ID2);

    const TopAbs_ShapeEnum aType1 = aSI1.ShapeType();
    const TopAbs_ShapeEnum aType2 = aSI2.ShapeType();

    int iType1 = BOPDS_Tools::TypeToInteger(aType1);
    int iType2 = BOPDS_Tools::TypeToInteger(aType2);

    if (((iType1 < iType2) && aSI1.HasSubShape(aPair.ID2))
        || ((iType1 > iType2) && aSI2.HasSubShape(aPair.ID1)))
      continue;

    if (theCheckOBB)
    {

      const Bnd_OBB& anOBB1 = theCtx->OBB(aSI1.Shape(), theFuzzyValue);
      const Bnd_OBB& anOBB2 = theCtx->OBB(aSI2.Shape(), theFuzzyValue);

      if (anOBB1.IsOut(anOBB2))
        continue;
    }

    int iX = BOPDS_Tools::TypeToInteger(aType1, aType2);
    myLists(iX).Append(BOPDS_Pair(std::min(aPair.ID1, aPair.ID2), std::max(aPair.ID1, aPair.ID2)));
  }
}
