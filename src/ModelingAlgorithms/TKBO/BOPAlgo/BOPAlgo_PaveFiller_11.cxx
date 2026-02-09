#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Alerts.hpp>

#include <BOPDS_DS.hpp>
#include <NCollection_Map.hpp>
#include <BOPDS_CommonBlock.hpp>

#include <BRep_Builder.hpp>

#include <TopoDS_Compound.hpp>

void BOPAlgo_PaveFiller::CheckSelfInterference()
{
  if (myArguments.Extent() == 1)
  {

    return;
  }

  BRep_Builder aBB;

  int i, aNbR = myDS->NbRanges();
  for (i = 0; i < aNbR; ++i)
  {
    const BOPDS_IndexRange& aR = myDS->Range(i);

    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>,
                               TopTools_ShapeMapHasher>
                                                    aMCSI;
    NCollection_Map<occ::handle<BOPDS_CommonBlock>> aMCBFence;

    int j = aR.First(), aRLast = aR.Last();
    for (; j <= aRLast; ++j)
    {
      const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(j);
      if (!aSI.HasReference())
      {

        continue;
      }

      const TopoDS_Shape& aS = aSI.Shape();

      if (aSI.ShapeType() == TopAbs_EDGE)
      {
        if (aSI.HasFlag())
        {
          continue;
        }

        NCollection_Map<int>            aMSubS;
        NCollection_List<int>::Iterator aItLI(aSI.SubShapes());
        for (; aItLI.More(); aItLI.Next())
        {
          int nV = aItLI.Value();
          myDS->HasShapeSD(nV, nV);
          aMSubS.Add(nV);
        }

        const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB      = myDS->PaveBlocks(j);
        bool                                                  bAnalyzeV = aLPB.Extent() > 1;

        NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aIt(aLPB);
        for (; aIt.More(); aIt.Next())
        {
          const occ::handle<BOPDS_PaveBlock>& aPB = aIt.Value();

          if (bAnalyzeV)
          {
            int nV[2];
            aPB->Indices(nV[0], nV[1]);
            for (int k = 0; k < 2; ++k)
            {
              if (!aR.Contains(nV[k]) && !aMSubS.Contains(nV[k]))
              {

                const TopoDS_Shape& aV = myDS->Shape(nV[k]);
                NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>* pMSOr =
                  aMCSI.ChangeSeek(aV);
                if (!pMSOr)
                {
                  pMSOr = &aMCSI(
                    aMCSI.Add(aV, NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>()));
                }
                pMSOr->Add(aS);
              }
            }
          }

          if (myDS->IsCommonBlock(aPB))
          {
            const occ::handle<BOPDS_CommonBlock>& aCB = myDS->CommonBlock(aPB);
            if (aMCBFence.Add(aCB))
            {
              const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPBCB = aCB->PaveBlocks();

              NCollection_List<int>                                    aLE;
              NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItCB(aLPBCB);
              for (; aItCB.More(); aItCB.Next())
              {
                const occ::handle<BOPDS_PaveBlock>& aPBCB = aItCB.Value();
                int                                 nEOr  = aPBCB->OriginalEdge();
                if (aR.Contains(nEOr))
                {
                  aLE.Append(nEOr);
                }
              }

              if (aLE.Extent() > 1)
              {

                TopoDS_Compound aWC;
                aBB.MakeCompound(aWC);

                NCollection_List<int>::Iterator aItLE(aLE);
                for (; aItLE.More(); aItLE.Next())
                {
                  const TopoDS_Shape& aE1 = myDS->Shape(aItLE.Value());
                  aBB.Add(aWC, aE1);
                }

                AddWarning(new BOPAlgo_AlertAcquiredSelfIntersection(aWC));
              }
            }
          }
        }
      }
      else if (aSI.ShapeType() == TopAbs_FACE)
      {

        const BOPDS_FaceInfo& aFI = myDS->FaceInfo(j);

        for (int k = 0; k < 2; ++k)
        {
          const NCollection_Map<int>&    aMVF = !k ? aFI.VerticesIn() : aFI.VerticesSc();
          NCollection_Map<int>::Iterator aItM(aMVF);
          for (; aItM.More(); aItM.Next())
          {
            const TopoDS_Shape& aV = myDS->Shape(aItM.Value());

            NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>* pMSOr =
              aMCSI.ChangeSeek(aV);
            if (!pMSOr)
            {
              pMSOr = &aMCSI(
                aMCSI.Add(aV, NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>()));
            }
            pMSOr->Add(aS);
          }
        }

        for (int k = 0; k < 2; ++k)
        {
          const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& aMPBF =
            !k ? aFI.PaveBlocksIn() : aFI.PaveBlocksSc();
          int iPB, aNbPB = aMPBF.Extent();
          for (iPB = 1; iPB <= aNbPB; ++iPB)
          {
            const occ::handle<BOPDS_PaveBlock>& aPB = aMPBF(iPB);
            Standard_ASSERT(aPB->HasEdge(), "Face information is not up to date", continue);
            const TopoDS_Shape& aE = myDS->Shape(aPB->Edge());

            NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>* pMSOr =
              aMCSI.ChangeSeek(aE);
            if (!pMSOr)
            {
              pMSOr = &aMCSI(
                aMCSI.Add(aE, NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>()));
            }
            pMSOr->Add(aS);
          }
        }
      }
    }

    int aNbC = aMCSI.Extent();
    for (j = 1; j <= aNbC; ++j)
    {
      const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMCS = aMCSI(j);
      if (aMCS.Extent() > 1)
      {

        TopoDS_Compound aWC;
        aBB.MakeCompound(aWC);

        int iS, aNbS = aMCS.Extent();
        for (iS = 1; iS <= aNbS; ++iS)
        {
          const TopoDS_Shape& aSx = aMCS(iS);
          aBB.Add(aWC, aSx);
        }
        AddWarning(new BOPAlgo_AlertAcquiredSelfIntersection(aWC));
      }
    }
  }
}
