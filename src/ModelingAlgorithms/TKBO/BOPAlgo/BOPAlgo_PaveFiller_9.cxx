#include <BOPAlgo_PaveFiller.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_Iterator.hpp>
#include <NCollection_List.hpp>
#include <Standard_Handle.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <BOPDS_ShapeInfo.hpp>
#include <BOPTools_Parallel.hpp>
#include <IntTools_Context.hpp>
#include <IntTools_ShrunkRange.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
class BOPDS_PaveBlock;

//
//=================================================================================================

class BOPAlgo_ShrunkRange : public IntTools_ShrunkRange
{
public:
  BOPAlgo_ShrunkRange()

    = default;

  //
  ~BOPAlgo_ShrunkRange() override = default;

  //
  void SetPaveBlock(const occ::handle<BOPDS_PaveBlock>& aPB) { myPB = aPB; }

  //
  occ::handle<BOPDS_PaveBlock>& PaveBlock() { return myPB; }

  //
  virtual void Perform() { IntTools_ShrunkRange::Perform(); }

  //
protected:
  occ::handle<BOPDS_PaveBlock> myPB;
};

//
//=======================================================================
typedef NCollection_Vector<BOPAlgo_ShrunkRange> BOPAlgo_VectorOfShrunkRange;

//=================================================================================================

void BOPAlgo_PaveFiller::FillShrunkData(const TopAbs_ShapeEnum aType1,
                                        const TopAbs_ShapeEnum aType2)
{
  myIterator->Initialize(aType1, aType2);
  int iSize = myIterator->ExpectedLength();
  if (!iSize)
  {
    return;
  }
  //
  int                                                      i, nS[2], nE, nV1, nV2, aNbVSD, k;
  double                                                   aT1, aT2;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItLPB;
  NCollection_Map<int>                                     aMI;
  BOPAlgo_VectorOfShrunkRange                              aVSD;
  TopAbs_ShapeEnum                                         aType[2] = {aType1, aType2};
  //
  for (; myIterator->More(); myIterator->Next())
  {
    myIterator->Value(nS[0], nS[1]);
    //
    for (i = 0; i < 2; ++i)
    {
      nE = nS[i];
      if (aType[i] != TopAbs_EDGE || !aMI.Add(nE))
      {
        continue;
      }
      //
      const BOPDS_ShapeInfo& aSIE = myDS->ShapeInfo(nE);
      if (aSIE.HasFlag())
      {
        continue;
      }
      //
      NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = myDS->ChangePaveBlocks(nE);
      aItLPB.Initialize(aLPB);
      for (; aItLPB.More(); aItLPB.Next())
      {
        const occ::handle<BOPDS_PaveBlock>& aPB = aItLPB.ChangeValue();
        if (aPB->HasShrunkData() && myDS->IsValidShrunkData(aPB))
        {
          continue;
        }
        //
        // FillShrunkData(aPB);
        aPB->Indices(nV1, nV2);
        aPB->Range(aT1, aT2);
        //
        const TopoDS_Edge& aE = (*(TopoDS_Edge*)(&aSIE.Shape()));
        //
        const TopoDS_Vertex& aV1 = (*(TopoDS_Vertex*)(&myDS->Shape(nV1)));
        //
        const TopoDS_Vertex& aV2 = (*(TopoDS_Vertex*)(&myDS->Shape(nV2)));
        //
        BOPAlgo_ShrunkRange& aSD = aVSD.Appended();
        //
        aSD.SetPaveBlock(aPB);
        aSD.SetData(aE, aT1, aT2, aV1, aV2);
      }
    }
  }
  //
  aNbVSD = aVSD.Length();
  //=============================================================
  BOPTools_Parallel::Perform(myRunParallel, aVSD, myContext);
  //=============================================================
  //
  for (k = 0; k < aNbVSD; ++k)
  {
    BOPAlgo_ShrunkRange& aSD = aVSD(k);
    AnalyzeShrunkData(aSD.PaveBlock(), aSD);
  }
}
