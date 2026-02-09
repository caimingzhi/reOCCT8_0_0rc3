#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_Tools.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_Interf.hpp>
#include <BOPDS_Iterator.hpp>
#include <BOPDS_Pair.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <NCollection_Vector.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_Parallel.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <IntTools_Context.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <Standard_ErrorHandler.hpp>
#include <TopoDS_Vertex.hpp>

class BOPAlgo_VertexEdge : public BOPAlgo_ParallelAlgo
{

public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_VertexEdge()
      : BOPAlgo_ParallelAlgo(),
        myIV(-1),
        myIE(-1),
        myFlag(-1),
        myT(-1.),
        myTolVNew(-1.) {};

  ~BOPAlgo_VertexEdge() override = default;

  void SetIndices(const int nV, const int nE)
  {
    myIV = nV;
    myIE = nE;
  }

  void Indices(int& nV, int& nE) const
  {
    nV = myIV;
    nE = myIE;
  }

  void SetVertex(const TopoDS_Vertex& aV) { myV = aV; }

  void SetEdge(const TopoDS_Edge& aE) { myE = aE; }

  const TopoDS_Vertex& Vertex() const { return myV; }

  const TopoDS_Edge& Edge() const { return myE; }

  int Flag() const { return myFlag; }

  double Parameter() const { return myT; }

  double VertexNewTolerance() const { return myTolVNew; }

  void SetContext(const occ::handle<IntTools_Context>& aContext) { myContext = aContext; }

  const occ::handle<IntTools_Context>& Context() const { return myContext; }

  void SetPaveBlock(const occ::handle<BOPDS_PaveBlock>& thePB) { myPB = thePB; }

  const occ::handle<BOPDS_PaveBlock>& PaveBlock() const { return myPB; }

  void Perform() override
  {
    Message_ProgressScope aPS(myProgressRange, nullptr, 1);
    if (UserBreak(aPS))
    {
      return;
    }
    try
    {
      OCC_CATCH_SIGNALS

      myFlag = myContext->ComputeVE(myV, myE, myT, myTolVNew, myFuzzyValue);
    }
    catch (Standard_Failure const&)
    {
      AddError(new BOPAlgo_AlertIntersectionFailed);
    }
  };

protected:
  int                           myIV;
  int                           myIE;
  int                           myFlag;
  double                        myT;
  double                        myTolVNew;
  TopoDS_Vertex                 myV;
  TopoDS_Edge                   myE;
  occ::handle<IntTools_Context> myContext;
  occ::handle<BOPDS_PaveBlock>  myPB;
};

typedef NCollection_Vector<BOPAlgo_VertexEdge> BOPAlgo_VectorOfVertexEdge;

void BOPAlgo_PaveFiller::PerformVE(const Message_ProgressRange& theRange)
{
  FillShrunkData(TopAbs_VERTEX, TopAbs_EDGE);

  myIterator->Initialize(TopAbs_VERTEX, TopAbs_EDGE);
  Message_ProgressScope aPS(theRange, nullptr, 1);

  int iSize = myIterator->ExpectedLength();
  if (!iSize)
  {
    return;
  }

  NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>> aMVEPairs;
  for (; myIterator->More(); myIterator->Next())
  {
    if (UserBreak(aPS))
    {
      return;
    }
    int nV, nE;
    myIterator->Value(nV, nE);

    const BOPDS_ShapeInfo& aSIE = myDS->ShapeInfo(nE);
    if (aSIE.HasSubShape(nV))
    {
      continue;
    }

    if (aSIE.HasFlag())
    {
      continue;
    }

    if (myDS->HasInterf(nV, nE))
    {
      continue;
    }

    if (myDS->HasInterfShapeSubShapes(nV, nE))
    {
      continue;
    }

    const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = myDS->PaveBlocks(nE);
    if (aLPB.IsEmpty())
    {
      continue;
    }

    const occ::handle<BOPDS_PaveBlock>& aPB = aLPB.First();
    if (!aPB->IsSplittable())
    {

      continue;
    }

    NCollection_List<int>* pLV = aMVEPairs.ChangeSeek(aPB);
    if (!pLV)
      pLV = &aMVEPairs(aMVEPairs.Add(aPB, NCollection_List<int>()));
    pLV->Append(nV);
  }

  IntersectVE(aMVEPairs, aPS.Next());
}

void BOPAlgo_PaveFiller::IntersectVE(
  const NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>>& theVEPairs,
  const Message_ProgressRange&                                                           theRange,
  const bool theAddInterfs)
{
  int i, aNbVE = theVEPairs.Extent();
  if (!aNbVE)
  {
    return;
  }

  NCollection_Vector<BOPDS_InterfVE>& aVEs = myDS->InterfVE();
  if (theAddInterfs)
  {
    aVEs.SetIncrement(aNbVE);
  }

  BOPAlgo_VectorOfVertexEdge aVVE;

  NCollection_DataMap<BOPDS_Pair, NCollection_List<int>> aDMVSD;

  Message_ProgressScope aPSOuter(theRange, nullptr, 10);
  for (i = 1; i <= aNbVE; ++i)
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    const occ::handle<BOPDS_PaveBlock>& aPB = theVEPairs.FindKey(i);
    int                                 nE  = aPB->OriginalEdge();

    NCollection_Map<int>                                  aMVPB;
    const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = myDS->PaveBlocks(nE);
    for (NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator itPB(aLPB); itPB.More();
         itPB.Next())
    {
      aMVPB.Add(itPB.Value()->Pave1().Index());
      aMVPB.Add(itPB.Value()->Pave2().Index());
    }

    const NCollection_List<int>&    aLV = theVEPairs(i);
    NCollection_List<int>::Iterator aItLV(aLV);
    for (; aItLV.More(); aItLV.Next())
    {
      int nV = aItLV.Value();

      int nVSD = nV;
      myDS->HasShapeSD(nV, nVSD);

      if (aMVPB.Contains(nVSD))
        continue;

      BOPDS_Pair             aPair(nVSD, nE);
      NCollection_List<int>* pLI = aDMVSD.ChangeSeek(aPair);
      if (pLI)
      {

        pLI->Append(nV);
        continue;
      }

      pLI = aDMVSD.Bound(aPair, NCollection_List<int>());
      pLI->Append(nV);

      const TopoDS_Vertex& aV = TopoDS::Vertex(myDS->Shape(nVSD));
      const TopoDS_Edge&   aE = TopoDS::Edge(myDS->Shape(nE));

      BOPAlgo_VertexEdge& aVESolver = aVVE.Appended();
      aVESolver.SetIndices(nVSD, nE);
      aVESolver.SetVertex(aV);
      aVESolver.SetEdge(aE);
      aVESolver.SetPaveBlock(aPB);
      aVESolver.SetFuzzyValue(myFuzzyValue);
    }
  }

  aNbVE = aVVE.Length();

  Message_ProgressScope aPS(aPSOuter.Next(9), "Performing Vertex-Edge intersection", aNbVE);
  for (i = 0; i < aNbVE; i++)
  {
    BOPAlgo_VertexEdge& aVESolver = aVVE.ChangeValue(i);
    aVESolver.SetProgressRange(aPS.Next());
  }

  BOPTools_Parallel::Perform(myRunParallel, aVVE, myContext);

  if (UserBreak(aPSOuter))
  {
    return;
  }

  NCollection_Map<int> aMEdges;

  for (i = 0; i < aNbVE; ++i)
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    const BOPAlgo_VertexEdge& aVESolver = aVVE(i);
    if (aVESolver.Flag() != 0)
    {
      if (aVESolver.HasErrors())
      {

        AddIntersectionFailedWarning(aVESolver.Vertex(), aVESolver.Edge());
      }
      continue;
    }

    int nV, nE;
    aVESolver.Indices(nV, nE);

    double aT = aVESolver.Parameter();

    double aTolVNew = aVESolver.VertexNewTolerance();
    int    nVx      = UpdateVertex(nV, aTolVNew);

    const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = myDS->PaveBlocks(nE);

    occ::handle<BOPDS_PaveBlock>                             aPB;
    NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator itPB(aLPB);
    for (; itPB.More(); itPB.Next())
    {
      aPB = itPB.Value();
      double aT1, aT2;
      aPB->Range(aT1, aT2);
      if (aT > aT1 && aT < aT2)
        break;
    }
    if (!itPB.More())
      continue;

    BOPDS_Pave aPave;
    aPave.SetIndex(nVx);
    aPave.SetParameter(aT);
    aPB->AppendExtPave(aPave);
    aMEdges.Add(nE);

    if (theAddInterfs)
    {

      BOPDS_Pair                      aPair(nV, nE);
      const NCollection_List<int>&    aLI = aDMVSD.Find(aPair);
      NCollection_List<int>::Iterator aItLI(aLI);
      for (; aItLI.More(); aItLI.Next())
      {
        const int nVOld = aItLI.Value();

        BOPDS_InterfVE& aVE = aVEs.Appended();
        aVE.SetIndices(nVOld, nE);
        aVE.SetParameter(aT);

        myDS->AddInterf(nVOld, nE);

        if (myDS->IsNewShape(nVx))
        {
          aVE.SetIndexNew(nVx);
        }
      }
    }
  }

  SplitPaveBlocks(aMEdges, theAddInterfs);
}

static void MakeNewCommonBlock(const NCollection_List<occ::handle<BOPDS_PaveBlock>>& theLPB,
                               const NCollection_List<int>&                          theLFaces,
                               BOPDS_PDS&                                            theDS)
{

  occ::handle<BOPDS_CommonBlock> aCBNew = new BOPDS_CommonBlock;
  aCBNew->SetPaveBlocks(theLPB);
  aCBNew->SetFaces(theLFaces);

  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItLPB(theLPB);
  for (; aItLPB.More(); aItLPB.Next())
  {
    theDS->SetCommonBlock(aItLPB.ChangeValue(), aCBNew);
  }
}

void BOPAlgo_PaveFiller::SplitPaveBlocks(const NCollection_Map<int>& theMEdges,
                                         const bool                  theAddInterfs)
{

  NCollection_Map<BOPDS_Pair> aMPairs;

  NCollection_IndexedDataMap<occ::handle<BOPDS_CommonBlock>,
                             NCollection_List<occ::handle<BOPDS_PaveBlock>>>
    aMCBNewPB;

  NCollection_Map<int> aMVerticesToInitPB;

  NCollection_Map<int>::Iterator aItM(theMEdges);
  for (; aItM.More(); aItM.Next())
  {
    int                                             nE   = aItM.Value();
    NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = myDS->ChangePaveBlocks(nE);

    NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItLPB(aLPB);
    for (; aItLPB.More();)
    {
      occ::handle<BOPDS_PaveBlock>& aPB = aItLPB.ChangeValue();

      if (!aPB->IsToUpdate())
      {
        aItLPB.Next();
        continue;
      }

      const occ::handle<BOPDS_CommonBlock>& aCB = myDS->CommonBlock(aPB);

      NCollection_List<occ::handle<BOPDS_PaveBlock>> aLPBN;
      aPB->Update(aLPBN);

      NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItLPBN(aLPBN);
      for (; aItLPBN.More(); aItLPBN.Next())
      {
        occ::handle<BOPDS_PaveBlock>& aPBN = aItLPBN.ChangeValue();
        myDS->UpdatePaveBlockWithSDVertices(aPBN);
        FillShrunkData(aPBN);

        bool bHasValidRange = aPBN->HasShrunkData();

        bool bCheckDist = (bHasValidRange && !aPBN->IsSplittable());
        if (!bHasValidRange || bCheckDist)
        {
          int nV1, nV2;
          aPBN->Indices(nV1, nV2);
          if (nV1 == nV2)

            continue;

          if (bCheckDist)
          {
            const TopoDS_Vertex& aV1 = TopoDS::Vertex(myDS->Shape(nV1));
            const TopoDS_Vertex& aV2 = TopoDS::Vertex(myDS->Shape(nV2));
            if (BOPTools_AlgoTools::ComputeVV(aV1, aV2, myFuzzyValue) == 0)

              bHasValidRange = false;
          }

          if (!bHasValidRange)
          {
            BOPDS_Pair aPair;
            aPair.SetIndices(nV1, nV2);
            if (aMPairs.Add(aPair))
            {
              NCollection_List<int> aLV;
              aLV.Append(nV1);
              aLV.Append(nV2);
              MakeSDVertices(aLV, theAddInterfs);

              aMVerticesToInitPB.Add(nV1);
              aMVerticesToInitPB.Add(nV2);
            }
            continue;
          }
        }

        aLPB.Append(aPBN);

        if (!aCB.IsNull())
        {

          NCollection_List<occ::handle<BOPDS_PaveBlock>>* pLPBCB = aMCBNewPB.ChangeSeek(aCB);
          if (!pLPBCB)
          {
            pLPBCB =
              &aMCBNewPB(aMCBNewPB.Add(aCB, NCollection_List<occ::handle<BOPDS_PaveBlock>>()));
          }
          pLPBCB->Append(aPBN);
        }
      }

      aLPB.Remove(aItLPB);
    }
  }

  int i, aNbCB = aMCBNewPB.Extent();
  for (i = 1; i <= aNbCB; ++i)
  {
    const occ::handle<BOPDS_CommonBlock>&                 aCB   = aMCBNewPB.FindKey(i);
    const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPBN = aMCBNewPB(i);

    NCollection_IndexedDataMap<BOPDS_Pair, NCollection_List<occ::handle<BOPDS_PaveBlock>>> aMInds;
    NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItLPB(aLPBN);
    for (; aItLPB.More(); aItLPB.Next())
    {
      const occ::handle<BOPDS_PaveBlock>& aPB = aItLPB.Value();

      BOPDS_Pair aPair;
      aPair.SetIndices(aPB->Pave1().Index(), aPB->Pave2().Index());

      NCollection_List<occ::handle<BOPDS_PaveBlock>>* pLPBx = aMInds.ChangeSeek(aPair);
      if (!pLPBx)
      {
        pLPBx = &aMInds(aMInds.Add(aPair, NCollection_List<occ::handle<BOPDS_PaveBlock>>()));
      }
      pLPBx->Append(aPB);
    }

    int nV1, nV2;
    aCB->PaveBlock1()->Indices(nV1, nV2);
    bool bIsClosed = (nV1 == nV2);

    int j, aNbPairs = aMInds.Extent();
    for (j = 1; j <= aNbPairs; ++j)
    {
      NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = aMInds(j);

      if (!bIsClosed)
      {

        MakeNewCommonBlock(aLPB, aCB->Faces(), myDS);
        continue;
      }

      while (aLPB.Extent())
      {

        NCollection_List<occ::handle<BOPDS_PaveBlock>> aLPBCB;

        gp_Pnt aPMFirst(0., 0., 0.);

        double aTolEFirst = 0.;

        aItLPB.Initialize(aLPB);
        for (; aItLPB.More();)
        {
          const occ::handle<BOPDS_PaveBlock>& aPB = aItLPB.Value();
          if (aLPBCB.IsEmpty())
          {
            aLPBCB.Append(aPB);
            const TopoDS_Edge& aEFirst = TopoDS::Edge(myDS->Shape(aPB->OriginalEdge()));
            aTolEFirst                 = BRep_Tool::MaxTolerance(aEFirst, TopAbs_VERTEX);

            double aTmFirst = (aPB->Pave1().Parameter() + aPB->Pave2().Parameter()) / 2.;
            BOPTools_AlgoTools::PointOnEdge(aEFirst, aTmFirst, aPMFirst);

            aLPB.Remove(aItLPB);
            continue;
          }

          const TopoDS_Edge& aE    = TopoDS::Edge(myDS->Shape(aPB->OriginalEdge()));
          double             aTolE = BRep_Tool::MaxTolerance(aE, TopAbs_VERTEX);

          double aTOut, aDist;
          int    iErr =
            myContext->ComputePE(aPMFirst, aTolEFirst + aTolE + myFuzzyValue, aE, aTOut, aDist);
          if (!iErr && ((aTOut > aPB->Pave1().Parameter()) && (aTOut < aPB->Pave2().Parameter())))
          {
            aLPBCB.Append(aPB);
            aLPB.Remove(aItLPB);
            continue;
          }
          aItLPB.Next();
        }

        MakeNewCommonBlock(aLPBCB, aCB->Faces(), myDS);
      }
    }
  }

  aItM.Initialize(aMVerticesToInitPB);
  for (; aItM.More(); aItM.Next())
    myDS->InitPaveBlocksForVertex(aItM.Value());
}

void BOPAlgo_PaveFiller::AddIntersectionFailedWarning(const TopoDS_Shape& theS1,
                                                      const TopoDS_Shape& theS2)
{

  TopoDS_Compound aWC;
  BRep_Builder().MakeCompound(aWC);
  BRep_Builder().Add(aWC, theS1);
  BRep_Builder().Add(aWC, theS2);

  AddWarning(new BOPAlgo_AlertIntersectionOfPairOfShapesFailed(aWC));
}
