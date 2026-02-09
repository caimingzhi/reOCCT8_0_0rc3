#include <Bnd_OBB.hpp>
#include <Bnd_Tools.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_IndexRange.hpp>
#include <BOPDS_Iterator.hpp>
#include <BOPDS_Pair.hpp>
#include <NCollection_Map.hpp>
#include <BOPDS_Tools.hpp>
#include <BOPTools_BoxTree.hpp>
#include <BOPTools_Parallel.hpp>
#include <IntTools_Context.hpp>
#include <NCollection_Vector.hpp>
#include <algorithm>

class BOPDS_TSR : public BOPTools_BoxTreeSelector
{
public:
  BOPDS_TSR()
      : myHasBRep(false),
        myIndex(-1)
  {
  }

  ~BOPDS_TSR() override = default;

  void SetHasBRep(const bool bFlag) { myHasBRep = bFlag; }

  void SetIndex(const int theIndex) { myIndex = theIndex; }

  int Index() const { return myIndex; }

  void Perform()
  {
    if (myHasBRep)
    {
      Select();
    }
  }

protected:
  bool myHasBRep;
  int  myIndex;
};

typedef NCollection_Vector<BOPDS_TSR> BOPDS_VectorOfTSR;

BOPDS_Iterator::BOPDS_Iterator()
    : myAllocator(NCollection_BaseAllocator::CommonBaseAllocator()),
      myRunParallel(false),
      myUseExt(false)
{
  int i, aNb;

  myDS     = nullptr;
  myLength = 0;

  aNb = BOPDS_DS::NbInterfTypes();
  myLists.SetIncrement(aNb);
  for (i = 0; i < aNb; ++i)
  {
    myLists.Appended();
  }

  const int aNbExt = BOPDS_Iterator::NbExtInterfs();
  myExtLists.SetIncrement(aNbExt);
  for (i = 0; i < aNbExt; ++i)
  {
    myExtLists.Appended();
  }
}

BOPDS_Iterator::BOPDS_Iterator(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : myAllocator(theAllocator),
      myLists(0, theAllocator),
      myRunParallel(false),
      myExtLists(0, theAllocator),
      myUseExt(false)
{
  int i, aNb;

  myDS     = nullptr;
  myLength = 0;

  aNb = BOPDS_DS::NbInterfTypes();
  myLists.SetIncrement(aNb);
  for (i = 0; i < aNb; ++i)
  {
    myLists.Appended();
  }

  const int aNbExt = BOPDS_Iterator::NbExtInterfs();
  myExtLists.SetIncrement(aNbExt);
  for (i = 0; i < aNbExt; ++i)
  {
    myExtLists.Appended();
  }
}

BOPDS_Iterator::~BOPDS_Iterator() = default;

void BOPDS_Iterator::SetRunParallel(const bool theFlag)
{
  myRunParallel = theFlag;
}

bool BOPDS_Iterator::RunParallel() const
{
  return myRunParallel;
}

void BOPDS_Iterator::SetDS(const BOPDS_PDS& aDS)
{
  myDS = aDS;
}

const BOPDS_DS& BOPDS_Iterator::DS() const
{
  return *myDS;
}

int BOPDS_Iterator::ExpectedLength() const
{
  return myLength;
}

int BOPDS_Iterator::BlockLength() const
{
  int    aNbIIs;
  double aCfPredict = .5;

  aNbIIs = ExpectedLength();

  if (aNbIIs <= 1)
  {
    return 1;
  }

  aNbIIs = (int)(aCfPredict * (double)aNbIIs);
  return aNbIIs;
}

void BOPDS_Iterator::Initialize(const TopAbs_ShapeEnum aType1, const TopAbs_ShapeEnum aType2)
{
  int iX;

  myLength = 0;
  iX       = BOPDS_Tools::TypeToInteger(aType1, aType2);
  if (iX >= 0)
  {
    NCollection_Vector<BOPDS_Pair>& aPairs =
      (myUseExt && iX < BOPDS_Iterator::NbExtInterfs()) ? myExtLists(iX) : myLists(iX);

    std::stable_sort(aPairs.begin(), aPairs.end());

    myIterator.Init(aPairs);
    myLength = aPairs.Length();
  }
}

bool BOPDS_Iterator::More() const
{
  return myIterator.More();
}

void BOPDS_Iterator::Next()
{
  myIterator.Next();
}

void BOPDS_Iterator::Value(int& theI1, int& theI2) const
{
  int iT1, iT2, n1, n2;

  const BOPDS_Pair& aPair = myIterator.Value();
  aPair.Indices(n1, n2);

  iT1 = (int)(myDS->ShapeInfo(n1).ShapeType());
  iT2 = (int)(myDS->ShapeInfo(n2).ShapeType());

  theI1 = n1;
  theI2 = n2;
  if (iT1 < iT2)
  {
    theI1 = n2;
    theI2 = n1;
  }
}

void BOPDS_Iterator::Prepare(const occ::handle<IntTools_Context>& theCtx,
                             const bool                           theCheckOBB,
                             const double                         theFuzzyValue)
{
  int i, aNbInterfTypes;

  aNbInterfTypes = BOPDS_DS::NbInterfTypes();
  myLength       = 0;
  for (i = 0; i < aNbInterfTypes; ++i)
  {
    myLists(i).Clear();
  }

  if (myDS == nullptr)
  {
    return;
  }
  Intersect(theCtx, theCheckOBB, theFuzzyValue);
}

void BOPDS_Iterator::Intersect(const occ::handle<IntTools_Context>& theCtx,
                               const bool                           theCheckOBB,
                               const double                         theFuzzyValue)
{
  const int aNb = myDS->NbSourceShapes();

  BOPTools_BoxTree aBoxTree;
  aBoxTree.SetSize(aNb);
  for (int i = 0; i < aNb; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (!aSI.HasBRep())
      continue;
    const Bnd_Box& aBox = aSI.Box();
    aBoxTree.Add(i, Bnd_Tools::Bnd2BVH(aBox));
  }

  aBoxTree.Build();

  BOPTools_BoxPairSelector aPairSelector;
  aPairSelector.SetBVHSets(&aBoxTree, &aBoxTree);
  aPairSelector.SetSame(true);
  aPairSelector.Select();
  aPairSelector.Sort();

  const std::vector<BOPTools_BoxPairSelector::PairIDs>& aPairs   = aPairSelector.Pairs();
  const int                                             aNbPairs = static_cast<int>(aPairs.size());

  int iPair = 0;

  const int aNbR = myDS->NbRanges();
  for (int iR = 0; iR < aNbR; ++iR)
  {
    const BOPDS_IndexRange& aRange = myDS->Range(iR);

    for (; iPair < aNbPairs; ++iPair)
    {
      const BOPTools_BoxPairSelector::PairIDs& aPair = aPairs[iPair];
      if (!aRange.Contains(aPair.ID1))

        break;

      if (aRange.Contains(aPair.ID2))

        continue;

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
      myLists(iX).Append(
        BOPDS_Pair(std::min(aPair.ID1, aPair.ID2), std::max(aPair.ID1, aPair.ID2)));
    }
  }
}

void BOPDS_Iterator::IntersectExt(const NCollection_Map<int>& theIndices)
{
  if (!myDS)
    return;

  const int aNb = myDS->NbSourceShapes();

  BOPTools_BoxTree aBoxTree;
  aBoxTree.SetSize(aNb);
  BOPDS_VectorOfTSR aVTSR(theIndices.Extent());

  for (int i = 0; i < aNb; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (!aSI.IsInterfering() || (aSI.ShapeType() == TopAbs_SOLID))
      continue;

    if (theIndices.Contains(i))
    {
      int nVSD = i;
      myDS->HasShapeSD(i, nVSD);
      const BOPDS_ShapeInfo& aSISD = myDS->ShapeInfo(nVSD);
      const Bnd_Box&         aBox  = aSISD.Box();
      aBoxTree.Add(i, Bnd_Tools::Bnd2BVH(aBox));

      BOPDS_TSR& aTSR = aVTSR.Appended();
      aTSR.SetHasBRep(true);
      aTSR.SetBVHSet(&aBoxTree);
      aTSR.SetBox(Bnd_Tools::Bnd2BVH(aBox));
      aTSR.SetIndex(i);
    }
    else
    {
      aBoxTree.Add(i, Bnd_Tools::Bnd2BVH(aSI.Box()));
    }
  }

  aBoxTree.Build();

  BOPTools_Parallel::Perform(myRunParallel, aVTSR);

  NCollection_Map<BOPDS_Pair> aMPFence;

  const int aNbV = aVTSR.Length();
  for (int k = 0; k < aNbV; ++k)
  {
    BOPDS_TSR&                   aTSRi = aVTSR(k);
    const NCollection_List<int>& aLI   = aTSRi.Indices();
    if (aLI.IsEmpty())
      continue;

    const int              i      = aTSRi.Index();
    const BOPDS_ShapeInfo& aSI    = myDS->ShapeInfo(i);
    const int              iRankI = myDS->Rank(i);
    const TopAbs_ShapeEnum aTI    = aSI.ShapeType();
    const int              iTI    = BOPDS_Tools::TypeToInteger(aTI);

    NCollection_List<int>::Iterator itLI(aLI);
    for (; itLI.More(); itLI.Next())
    {
      const int j      = itLI.Value();
      const int iRankJ = myDS->Rank(j);
      if (iRankI == iRankJ)
        continue;

      const BOPDS_ShapeInfo& aSJ = myDS->ShapeInfo(j);
      const TopAbs_ShapeEnum aTJ = aSJ.ShapeType();
      const int              iTJ = BOPDS_Tools::TypeToInteger(aTJ);

      if (((iTI < iTJ) && aSI.HasSubShape(j)) || ((iTI > iTJ) && aSJ.HasSubShape(i)))
        continue;

      BOPDS_Pair aPair(i, j);
      if (aMPFence.Add(aPair))
      {
        const int iX = BOPDS_Tools::TypeToInteger(aTI, aTJ);
        if (iX < BOPDS_Iterator::NbExtInterfs())
          myExtLists(iX).Append(aPair);
      }
    }
  }

  myUseExt = true;
}
