#include <Bnd_Box.hpp>
#include <Bnd_Tools.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_Tools.hpp>
#include <BOPDS_CoupleOfPaveBlocks.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_Interf.hpp>
#include <BOPDS_Iterator.hpp>
#include <NCollection_Map.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <BOPDS_Pave.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_AlgoTools2D.hpp>
#include <BOPTools_Parallel.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <Standard_ErrorHandler.hpp>
#include <GeomAPI_ProjectPointOnSurf.hpp>
#include <gp_Pnt.hpp>
#include <IntTools_CommonPrt.hpp>
#include <IntTools_Context.hpp>
#include <IntTools_EdgeFace.hpp>
#include <IntTools_Range.hpp>
#include <NCollection_Sequence.hpp>
#include <IntTools_Tools.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_Vector.hpp>
#include <Precision.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

class BOPAlgo_EdgeFace : public IntTools_EdgeFace, public BOPAlgo_ParallelAlgo
{

public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_EdgeFace()
      : BOPAlgo_ParallelAlgo(),
        myIE(-1),
        myIF(-1) {};

  ~BOPAlgo_EdgeFace() override = default;

  void SetIndices(const int nE, const int nF)
  {
    myIE = nE;
    myIF = nF;
  }

  void Indices(int& nE, int& nF)
  {
    nE = myIE;
    nF = myIF;
  }

  void SetNewSR(const IntTools_Range& aR) { myNewSR = aR; }

  IntTools_Range& NewSR() { return myNewSR; }

  void SetPaveBlock(const occ::handle<BOPDS_PaveBlock>& aPB) { myPB = aPB; }

  occ::handle<BOPDS_PaveBlock>& PaveBlock() { return myPB; }

  void SetFuzzyValue(const double theFuzz) { IntTools_EdgeFace::SetFuzzyValue(theFuzz); }

  void SetBoxes(const Bnd_Box& theBox1, const Bnd_Box& theBox2)
  {
    myBox1 = theBox1;
    myBox2 = theBox2;
  }

  void Perform() override
  {
    Message_ProgressScope aPS(myProgressRange, nullptr, 1);
    if (UserBreak(aPS))
    {
      return;
    }
    TopoDS_Face aFace   = myFace;
    TopoDS_Edge anEdge  = myEdge;
    bool        hasTrsf = false;
    try
    {
      OCC_CATCH_SIGNALS

      gp_Trsf aTrsf;
      if (BOPAlgo_Tools::TrsfToPoint(myBox1, myBox2, aTrsf))
      {

        TopLoc_Location aLoc(aTrsf);
        myEdge.Move(aLoc);
        myFace.Move(aLoc);
        hasTrsf = true;
      }

      IntTools_EdgeFace::Perform();
    }
    catch (Standard_Failure const&)
    {
      AddError(new BOPAlgo_AlertIntersectionFailed);
    }
    myFace = aFace;
    myEdge = anEdge;

    if (hasTrsf)
    {
      for (int i = 1; i <= mySeqOfCommonPrts.Length(); ++i)
      {
        IntTools_CommonPrt& aCPart = mySeqOfCommonPrts(i);
        aCPart.SetEdge1(myEdge);
      }
    }
  }

protected:
  int                          myIE;
  int                          myIF;
  IntTools_Range               myNewSR;
  occ::handle<BOPDS_PaveBlock> myPB;
  Bnd_Box                      myBox1;
  Bnd_Box                      myBox2;
};

typedef NCollection_Vector<BOPAlgo_EdgeFace> BOPAlgo_VectorOfEdgeFace;

void BOPAlgo_PaveFiller::PerformEF(const Message_ProgressRange& theRange)
{
  FillShrunkData(TopAbs_EDGE, TopAbs_FACE);

  myIterator->Initialize(TopAbs_EDGE, TopAbs_FACE);
  Message_ProgressScope aPSOuter(theRange, nullptr, 10);
  int                   iSize = myIterator->ExpectedLength();
  if (!iSize)
  {
    return;
  }

  int nE, nF;

  if (myGlue == BOPAlgo_GlueFull)
  {

    for (; myIterator->More(); myIterator->Next())
    {
      myIterator->Value(nE, nF);
      if (!myDS->ShapeInfo(nE).HasFlag())
      {
        myDS->ChangeFaceInfo(nF);
      }
    }
    return;
  }

  bool                                                     bV[2], bIsPBSplittable;
  bool                                                     bV1, bV2, bExpressCompute;
  int                                                      nV1, nV2;
  int                                                      i, aNbCPrts, iX, nV[2];
  int                                                      aNbEdgeFace, k;
  double                                                   aTolE, aTolF, aTS1, aTS2, aT1, aT2;
  occ::handle<NCollection_BaseAllocator>                   aAllocator;
  TopAbs_ShapeEnum                                         aType;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aIt;
  BOPAlgo_VectorOfEdgeFace                                 aVEdgeFace;

  aAllocator = NCollection_BaseAllocator::CommonBaseAllocator();

  NCollection_Map<int> aMIEFC(100, aAllocator);
  NCollection_IndexedDataMap<TopoDS_Shape, BOPDS_CoupleOfPaveBlocks, TopTools_ShapeMapHasher>
    aMVCPB(100, aAllocator);
  NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>> aMPBLI(
    100,
    aAllocator);
  BOPAlgo_DataMapOfPaveBlockBndBox aDMPBBox(100, aAllocator);

  NCollection_Vector<BOPDS_InterfEF>& aEFs = myDS->InterfEF();
  aEFs.SetIncrement(iSize);

  for (; myIterator->More(); myIterator->Next())
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    myIterator->Value(nE, nF);

    const BOPDS_ShapeInfo& aSIE = myDS->ShapeInfo(nE);
    if (aSIE.HasFlag())
    {
      continue;
    }

    const TopoDS_Edge& aE   = (*(TopoDS_Edge*)(&aSIE.Shape()));
    const TopoDS_Face& aF   = (*(TopoDS_Face*)(&myDS->Shape(nF)));
    const Bnd_Box&     aBBF = myDS->ShapeInfo(nF).Box();

    BOPDS_FaceInfo&                                             aFI   = myDS->ChangeFaceInfo(nF);
    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& aMPBF = aFI.PaveBlocksOn();

    const NCollection_Map<int>& aMVIn = aFI.VerticesIn();
    const NCollection_Map<int>& aMVOn = aFI.VerticesOn();

    aTolE = BRep_Tool::Tolerance(aE);
    aTolF = BRep_Tool::Tolerance(aF);

    NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = myDS->ChangePaveBlocks(nE);
    aIt.Initialize(aLPB);
    for (; aIt.More(); aIt.Next())
    {
      if (UserBreak(aPSOuter))
      {
        return;
      }
      occ::handle<BOPDS_PaveBlock>& aPB = aIt.ChangeValue();

      const occ::handle<BOPDS_PaveBlock> aPBR = myDS->RealPaveBlock(aPB);
      if (aMPBF.Contains(aPBR))
      {
        continue;
      }

      Bnd_Box aBBE;
      if (!GetPBBox(aE, aPB, aDMPBBox, aT1, aT2, aTS1, aTS2, aBBE))
      {
        continue;
      }

      if (aBBF.IsOut(aBBE))
      {
        continue;
      }

      aPBR->Indices(nV1, nV2);
      bV1             = aMVIn.Contains(nV1) || aMVOn.Contains(nV1);
      bV2             = aMVIn.Contains(nV2) || aMVOn.Contains(nV2);
      bExpressCompute = bV1 && bV2;

      BOPAlgo_EdgeFace& aEdgeFace = aVEdgeFace.Appended();

      aEdgeFace.SetIndices(nE, nF);
      aEdgeFace.SetPaveBlock(aPB);

      aEdgeFace.SetEdge(aE);
      aEdgeFace.SetFace(aF);
      aEdgeFace.SetBoxes(myDS->ShapeInfo(nE).Box(), myDS->ShapeInfo(nF).Box());
      aEdgeFace.SetFuzzyValue(myFuzzyValue);
      aEdgeFace.UseQuickCoincidenceCheck(bExpressCompute);

      IntTools_Range aSR(aTS1, aTS2);
      IntTools_Range anewSR = aSR;
      BOPTools_AlgoTools::CorrectRange(aE, aF, aSR, anewSR);
      aEdgeFace.SetNewSR(anewSR);

      IntTools_Range aPBRange(aT1, aT2);
      aSR = aPBRange;
      BOPTools_AlgoTools::CorrectRange(aE, aF, aSR, aPBRange);
      aEdgeFace.SetRange(aPBRange);

      NCollection_Map<occ::handle<BOPDS_PaveBlock>>* pMPB = myFPBDone.ChangeSeek(nF);
      if (!pMPB)
        pMPB = myFPBDone.Bound(nF, NCollection_Map<occ::handle<BOPDS_PaveBlock>>());
      pMPB->Add(aPB);
    }
  }

  aNbEdgeFace = aVEdgeFace.Length();
  Message_ProgressScope aPS(aPSOuter.Next(9), "Performing Edge-Face intersection", aNbEdgeFace);
  for (int index = 0; index < aNbEdgeFace; index++)
  {
    BOPAlgo_EdgeFace& aEdgeFace = aVEdgeFace.ChangeValue(index);
    aEdgeFace.SetProgressRange(aPS.Next());
  }

  BOPTools_Parallel::Perform(myRunParallel, aVEdgeFace, myContext);

  if (UserBreak(aPSOuter))
  {
    return;
  }

  for (k = 0; k < aNbEdgeFace; ++k)
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    BOPAlgo_EdgeFace& aEdgeFace = aVEdgeFace(k);
    if (!aEdgeFace.IsDone() || aEdgeFace.HasErrors())
    {

      AddIntersectionFailedWarning(aEdgeFace.Edge(), aEdgeFace.Face());
      continue;
    }

    aEdgeFace.Indices(nE, nF);

    const TopoDS_Edge& aE = aEdgeFace.Edge();
    const TopoDS_Face& aF = aEdgeFace.Face();

    aTolE = BRep_Tool::Tolerance(aE);
    aTolF = BRep_Tool::Tolerance(aF);

    const NCollection_Sequence<IntTools_CommonPrt>& aCPrts = aEdgeFace.CommonParts();
    aNbCPrts                                               = aCPrts.Length();
    if (!aNbCPrts)
    {
      if (aEdgeFace.MinimalDistance() < RealLast() && aEdgeFace.MinimalDistance() > aTolE + aTolF)
      {
        const occ::handle<BOPDS_PaveBlock>& aPB = aEdgeFace.PaveBlock();
        aPB->Range(aT1, aT2);
        NCollection_List<EdgeRangeDistance>* pList = myDistances.ChangeSeek(BOPDS_Pair(nE, nF));
        if (!pList)
          pList = myDistances.Bound(BOPDS_Pair(nE, nF), NCollection_List<EdgeRangeDistance>());
        pList->Append(EdgeRangeDistance(aT1, aT2, aEdgeFace.MinimalDistance()));
      }
      continue;
    }

    const IntTools_Range&         anewSR = aEdgeFace.NewSR();
    occ::handle<BOPDS_PaveBlock>& aPB    = aEdgeFace.PaveBlock();

    aPB->Range(aT1, aT2);
    aPB->Indices(nV[0], nV[1]);
    bIsPBSplittable = aPB->IsSplittable();

    anewSR.Range(aTS1, aTS2);

    if (aCPrts(1).Type() == TopAbs_VERTEX)
    {

      ReduceIntersectionRange(nV[0], nV[1], nE, nF, aTS1, aTS2);
    }

    IntTools_Range aR1(aT1, aTS1), aR2(aTS2, aT2);

    BOPDS_FaceInfo&             aFI    = myDS->ChangeFaceInfo(nF);
    const NCollection_Map<int>& aMIFOn = aFI.VerticesOn();
    const NCollection_Map<int>& aMIFIn = aFI.VerticesIn();

    bool bLinePlane = false;
    if (aNbCPrts)
    {
      BRepAdaptor_Curve aBAC(aE);
      bLinePlane = (aBAC.GetType() == GeomAbs_Line
                    && myContext->SurfaceAdaptor(aF).GetType() == GeomAbs_Plane);
    }

    for (i = 1; i <= aNbCPrts; ++i)
    {
      if (UserBreak(aPSOuter))
      {
        return;
      }
      const IntTools_CommonPrt& aCPart = aCPrts(i);
      aType                            = aCPart.Type();
      switch (aType)
      {
        case TopAbs_VERTEX:
        {
          bool          bIsOnPave[2];
          int           j;
          double        aT, aTolToDecide;
          TopoDS_Vertex aVnew;

          IntTools_Tools::VertexParameter(aCPart, aT);
          BOPTools_AlgoTools::MakeNewVertex(aE, aT, aF, aVnew);

          const IntTools_Range& aR = aCPart.Range1();
          aTolToDecide             = 5.e-8;

          bIsOnPave[0] = IntTools_Tools::IsInRange(aR1, aR, aTolToDecide);
          bIsOnPave[1] = IntTools_Tools::IsInRange(aR2, aR, aTolToDecide);

          if ((bIsOnPave[0] && bIsOnPave[1]) || (bLinePlane && (bIsOnPave[0] || bIsOnPave[1])))
          {
            bV[0] = CheckFacePaves(nV[0], aMIFOn, aMIFIn);
            bV[1] = CheckFacePaves(nV[1], aMIFOn, aMIFIn);
            if (bV[0] && bV[1])
            {
              IntTools_CommonPrt aCP = aCPart;
              aCP.SetType(TopAbs_EDGE);
              BOPDS_InterfEF& aEF = aEFs.Appended();
              iX                  = aEFs.Length() - 1;
              aEF.SetIndices(nE, nF);
              aEF.SetCommonPart(aCP);
              myDS->AddInterf(nE, nF);

              aMIEFC.Add(nF);

              BOPAlgo_Tools::FillMap(aPB, nF, aMPBLI, aAllocator);
              break;
            }
          }

          if (!bIsPBSplittable)
          {
            continue;
          }

          for (j = 0; j < 2; ++j)
          {
            if (bIsOnPave[j])
            {
              bV[j] = CheckFacePaves(nV[j], aMIFOn, aMIFIn);
              if (!bV[j])
                bIsOnPave[j] = ForceInterfVF(nV[j], nF);
            }
          }

          if (bIsOnPave[0] || bIsOnPave[1])
          {

            GeomAPI_ProjectPointOnSurf& aProjPS = myContext->ProjPS(aF);
            const gp_Pnt                aPnew   = BRep_Tool::Pnt(aVnew);
            aProjPS.Perform(aPnew);
            double aMinDistEF = (aProjPS.IsDone() && aProjPS.NbPoints()) ? aProjPS.LowerDistance()
                                                                         : Precision::Infinite();
            bool   hasRealIntersection = aMinDistEF < Precision::Intersection();

            if (!hasRealIntersection)

              continue;

            for (j = 0; j < 2; ++j)
            {
              if (bIsOnPave[j])
              {
                const TopoDS_Vertex& aV       = TopoDS::Vertex(myDS->Shape(nV[j]));
                const gp_Pnt         aP       = BRep_Tool::Pnt(aV);
                double               aDistPP  = aP.Distance(aPnew);
                double               aTol     = BRep_Tool::Tolerance(aV);
                double               aMaxDist = 1.e4 * aTol;
                if (aTol < .01)
                {
                  aMaxDist = std::min(aMaxDist, 0.1);
                }
                if (aDistPP < aMaxDist)
                {
                  UpdateVertex(nV[j], aDistPP);
                  myVertsToAvoidExtension.Add(nV[j]);
                }
              }
            }
            continue;
          }

          if (CheckFacePaves(aVnew, aMIFOn))
          {
            continue;
          }

          double aTolVnew = BRep_Tool::Tolerance(aVnew);
          aTolVnew        = std::max(aTolVnew, std::max(aTolE, aTolF));
          BRep_Builder().UpdateVertex(aVnew, aTolVnew);
          if (bLinePlane)
          {

            IntTools_Range aCR = aCPart.Range1();
            aTolVnew           = std::max(aTolVnew, (aCR.Last() - aCR.First()) / 2.);
          }

          const gp_Pnt& aPnew = BRep_Tool::Pnt(aVnew);

          if (!myContext->IsPointInFace(aPnew, aF, aTolVnew))
          {
            continue;
          }

          aMIEFC.Add(nF);

          BOPDS_InterfEF& aEF = aEFs.Appended();
          iX                  = aEFs.Length() - 1;
          aEF.SetIndices(nE, nF);
          aEF.SetCommonPart(aCPart);

          myDS->AddInterf(nE, nF);

          BOPDS_CoupleOfPaveBlocks aCPB;

          aCPB.SetPaveBlocks(aPB, aPB);
          aCPB.SetIndexInterf(iX);
          aCPB.SetTolerance(aTolVnew);
          aMVCPB.Add(aVnew, aCPB);
        }
        break;
        case TopAbs_EDGE:
        {
          aMIEFC.Add(nF);

          BOPDS_InterfEF& aEF = aEFs.Appended();
          iX                  = aEFs.Length() - 1;
          aEF.SetIndices(nE, nF);

          bV[0] = CheckFacePaves(nV[0], aMIFOn, aMIFIn);
          bV[1] = CheckFacePaves(nV[1], aMIFOn, aMIFIn);
          if (!bV[0] || !bV[1])
          {
            myDS->AddInterf(nE, nF);
            break;
          }
          aEF.SetCommonPart(aCPart);

          myDS->AddInterf(nE, nF);

          BOPAlgo_Tools::FillMap(aPB, nF, aMPBLI, aAllocator);
        }
        break;
        default:
          break;
      }
    }
  }

  BOPAlgo_Tools::PerformCommonBlocks(aMPBLI, aAllocator, myDS, myContext);
  UpdateVerticesOfCB();
  PerformNewVertices(aMVCPB, aAllocator, aPSOuter.Next(1), false);
  if (HasErrors())
  {
    return;
  }

  myDS->UpdateFaceInfoIn(aMIEFC);

  aMIEFC.Clear();
  aMVCPB.Clear();
  aMPBLI.Clear();
}

bool BOPAlgo_PaveFiller::CheckFacePaves(const int                   nVx,
                                        const NCollection_Map<int>& aMIFOn,
                                        const NCollection_Map<int>& aMIFIn)
{
  return aMIFOn.Contains(nVx) || aMIFIn.Contains(nVx);
}

bool BOPAlgo_PaveFiller::CheckFacePaves(const TopoDS_Vertex&        aVnew,
                                        const NCollection_Map<int>& aMIF)
{
  bool                           bRet;
  int                            nV, iFlag;
  NCollection_Map<int>::Iterator aIt;

  bRet = true;

  aIt.Initialize(aMIF);
  for (; aIt.More(); aIt.Next())
  {
    nV                      = aIt.Value();
    const TopoDS_Vertex& aV = (*(TopoDS_Vertex*)(&myDS->Shape(nV)));
    iFlag                   = BOPTools_AlgoTools::ComputeVV(aVnew, aV);
    if (!iFlag)
    {
      return bRet;
    }
  }

  return !bRet;
}

bool BOPAlgo_PaveFiller::ForceInterfVF(const int nV, const int nF)
{
  bool   bRet;
  int    iFlag, nVx;
  double U, V, aTolVNew;

  bRet                    = false;
  const TopoDS_Vertex& aV = *(TopoDS_Vertex*)&myDS->Shape(nV);
  const TopoDS_Face&   aF = *(TopoDS_Face*)&myDS->Shape(nF);

  iFlag = myContext->ComputeVF(aV, aF, U, V, aTolVNew, myFuzzyValue);
  if (iFlag == 0 || iFlag == -2)
  {
    bRet = !bRet;

    NCollection_Vector<BOPDS_InterfVF>& aVFs = myDS->InterfVF();
    aVFs.SetIncrement(10);

    BOPDS_InterfVF& aVF = aVFs.Appended();

    aVF.SetIndices(nV, nF);
    aVF.SetUV(U, V);

    myDS->AddInterf(nV, nF);

    nVx = UpdateVertex(nV, aTolVNew);

    if (myDS->IsNewShape(nVx))
    {
      aVF.SetIndexNew(nVx);
    }

    BOPDS_FaceInfo&       aFI   = myDS->ChangeFaceInfo(nF);
    NCollection_Map<int>& aMVIn = aFI.ChangeVerticesIn();
    aMVIn.Add(nVx);

    int iRV = myDS->Rank(nV);
    if (iRV >= 0 && iRV == myDS->Rank(nF))
    {

      TopoDS_Compound aWC;
      BRep_Builder().MakeCompound(aWC);
      BRep_Builder().Add(aWC, aV);
      BRep_Builder().Add(aWC, aF);
      AddWarning(new BOPAlgo_AlertSelfInterferingShape(aWC));
    }
  }
  return bRet;
}

void BOPAlgo_PaveFiller::ReduceIntersectionRange(const int theV1,
                                                 const int theV2,
                                                 const int theE,
                                                 const int theF,
                                                 double&   theTS1,
                                                 double&   theTS2)
{
  if (!myDS->IsNewShape(theV1) && !myDS->IsNewShape(theV2))
  {
    return;
  }

  if (!myDS->HasInterfShapeSubShapes(theE, theF))
  {
    return;
  }

  NCollection_Vector<BOPDS_InterfEE>& aEEs   = myDS->InterfEE();
  int                                 aNbEEs = aEEs.Length();
  if (!aNbEEs)
  {
    return;
  }

  int    i, nV, nE1, nE2;
  double aTR1, aTR2;

  NCollection_Map<int>            aMFE;
  const NCollection_List<int>&    aLI = myDS->ShapeInfo(theF).SubShapes();
  NCollection_List<int>::Iterator aItLI(aLI);
  for (; aItLI.More(); aItLI.Next())
  {
    nE1 = aItLI.Value();
    if (myDS->ShapeInfo(nE1).ShapeType() == TopAbs_EDGE)
    {
      aMFE.Add(nE1);
    }
  }

  for (i = 0; i < aNbEEs; ++i)
  {
    BOPDS_InterfEE& aEE = aEEs(i);
    if (!aEE.HasIndexNew())
    {
      continue;
    }

    nV = aEE.IndexNew();
    if (nV != theV1 && nV != theV2)
    {
      continue;
    }

    aEE.Indices(nE1, nE2);
    if (((theE != nE1) && (theE != nE2)) || (!aMFE.Contains(nE1) && !aMFE.Contains(nE2)))
    {
      continue;
    }

    const IntTools_CommonPrt& aCPart  = aEE.CommonPart();
    const IntTools_Range&     aCRange = (theE == nE1) ? aCPart.Range1() : aCPart.Ranges2().First();
    aCRange.Range(aTR1, aTR2);

    if (nV == theV1)
    {
      if (theTS1 < aTR2)
      {
        theTS1 = aTR2;
      }
    }
    else
    {
      if (theTS2 > aTR1)
      {
        theTS2 = aTR1;
      }
    }
  }
}

void BOPAlgo_PaveFiller::ForceInterfEF(const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, nullptr, 1);
  if (!myIsPrimary)
    return;

  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>> aMPB;
  const int                                            aNbS = myDS->NbSourceShapes();
  for (int nE = 0; nE < aNbS; ++nE)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(nE);
    if (aSI.ShapeType() != TopAbs_EDGE)

      continue;

    if (!aSI.HasReference())

      continue;

    if (aSI.HasFlag())

      continue;

    if (UserBreak(aPS))
    {
      return;
    }
    const NCollection_List<occ::handle<BOPDS_PaveBlock>>&    aLPB = myDS->PaveBlocks(nE);
    NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItLPB(aLPB);
    for (; aItLPB.More(); aItLPB.Next())
    {
      const occ::handle<BOPDS_PaveBlock>& aPB  = aItLPB.Value();
      const occ::handle<BOPDS_PaveBlock>& aPBR = myDS->RealPaveBlock(aPB);
      aMPB.Add(aPBR);
    }
  }

  ForceInterfEF(aMPB, aPS.Next(), true);
}

void BOPAlgo_PaveFiller::ForceInterfEF(
  const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& theMPB,
  const Message_ProgressRange&                                theRange,
  const bool                                                  theAddInterf)
{

  Message_ProgressScope aPSOuter(theRange, nullptr, 10);
  if (theMPB.IsEmpty())
    return;

  BOPTools_BoxTree aBBTree;

  occ::handle<NCollection_IncAllocator>                anAlloc = new NCollection_IncAllocator;
  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>> aPBMap(1, anAlloc);

  int aNbPB = theMPB.Extent();
  for (int iPB = 1; iPB <= aNbPB; ++iPB)
  {
    occ::handle<BOPDS_PaveBlock> aPB = theMPB(iPB);
    if (!aPB->HasShrunkData() || !myDS->IsValidShrunkData(aPB))
    {
      FillShrunkData(aPB);
      if (!aPB->HasShrunkData())
        continue;
    }
    if (UserBreak(aPSOuter))
    {
      return;
    }

    double  f, l;
    Bnd_Box aPBBox;
    bool    isSplit;
    aPB->ShrunkData(f, l, aPBBox, isSplit);

    aBBTree.Add(aPBMap.Add(aPB), Bnd_Tools::Bnd2BVH(aPBBox));
  }

  aBBTree.Build();

  const bool bSICheckMode = (myArguments.Extent() == 1);

  BOPAlgo_VectorOfEdgeFace aVEdgeFace;

  const int aNbS = myDS->NbSourceShapes();
  for (int nF = 0; nF < aNbS; ++nF)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(nF);
    if (aSI.ShapeType() != TopAbs_FACE)

      continue;

    if (!aSI.HasReference())

      continue;

    if (UserBreak(aPSOuter))
    {
      return;
    }

    const Bnd_Box&           aBoxF = aSI.Box();
    BOPTools_BoxTreeSelector aSelector;
    aSelector.SetBox(Bnd_Tools::Bnd2BVH(aBoxF));
    aSelector.SetBVHSet(&aBBTree);
    if (!aSelector.Select())
      continue;

    const TopoDS_Face&    aF  = TopoDS::Face(aSI.Shape());
    const BOPDS_FaceInfo& aFI = myDS->FaceInfo(nF);

    NCollection_Map<int>        aMVF;
    const NCollection_Map<int>* pMVF[] = {&aFI.VerticesOn(), &aFI.VerticesIn(), &aFI.VerticesSc()};
    for (int iM = 0; iM < 3; ++iM)
    {
      NCollection_Map<int>::Iterator itM(*pMVF[iM]);
      for (; itM.More(); itM.Next())
        aMVF.Add(itM.Value());
    }

    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>* pMPBF[] = {&aFI.PaveBlocksOn(),
                                                                           &aFI.PaveBlocksIn(),
                                                                           &aFI.PaveBlocksSc()};
    for (int iM = 0; iM < 3; ++iM)
    {
      const int aNb = pMPBF[iM]->Extent();
      for (int iPB = 1; iPB <= aNb; ++iPB)
      {
        const occ::handle<BOPDS_PaveBlock>& aPB = pMPBF[iM]->FindKey(iPB);
        aMVF.Add(aPB->Pave1().Index());
        aMVF.Add(aPB->Pave2().Index());
      }
    }

    GeomAPI_ProjectPointOnSurf& aProjPS      = myContext->ProjPS(aF);
    BRepAdaptor_Surface&        aSurfAdaptor = myContext->SurfaceAdaptor(aF);

    const NCollection_List<int>&    aLIPB = aSelector.Indices();
    NCollection_List<int>::Iterator itLIPB(aLIPB);
    for (; itLIPB.More(); itLIPB.Next())
    {
      const occ::handle<BOPDS_PaveBlock>& aPB = aPBMap(itLIPB.Value());
      if (pMPBF[0]->Contains(aPB) || pMPBF[1]->Contains(aPB) || pMPBF[2]->Contains(aPB))
        continue;

      int nV1, nV2;
      aPB->Indices(nV1, nV2);
      if (!aMVF.Contains(nV1) || !aMVF.Contains(nV2))

        continue;

      int nE;
      if (!aPB->HasEdge(nE))
      {
        nE = aPB->OriginalEdge();
        if (nE < 0)
          continue;

        if (myDS->Rank(nF) == myDS->Rank(nE))
          continue;
      }

      const TopoDS_Edge& aE = TopoDS::Edge(myDS->Shape(nE));
      BRepAdaptor_Curve  aBAC(aE);

      bool bUseAddTol = true;

      double  aTS[2];
      Bnd_Box aPBBox;
      bool    isSplit;
      aPB->ShrunkData(aTS[0], aTS[1], aPBBox, isSplit);

      gp_Pnt aPOnE;

      gp_Vec aVETgt;
      aBAC.D1(BOPTools_AlgoTools2D::IntermediatePoint(aTS[0], aTS[1]), aPOnE, aVETgt);
      if (aVETgt.SquareMagnitude() < gp::Resolution())
        continue;

      aProjPS.Perform(aPOnE);
      if (!aProjPS.NbPoints())
        continue;

      const TopoDS_Vertex& aV1 = TopoDS::Vertex(myDS->Shape(nV1));
      const TopoDS_Vertex& aV2 = TopoDS::Vertex(myDS->Shape(nV2));

      double aTolCheck =
        (bSICheckMode ? myFuzzyValue
                      : 2 * std::max(BRep_Tool::Tolerance(aV1), BRep_Tool::Tolerance(aV2)));

      if (aProjPS.LowerDistance() > aTolCheck + myFuzzyValue)
        continue;

      double U, V;
      aProjPS.LowerDistanceParameters(U, V);
      if (!myContext->IsPointInFace(aF, gp_Pnt2d(U, V)))
        continue;

      if (aSurfAdaptor.GetType() != GeomAbs_Plane || aBAC.GetType() != GeomAbs_Line)
      {
        gp_Pnt aPOnS = aProjPS.NearestPoint();
        gp_Vec aVFNorm(aPOnS, aPOnE);
        if (aVFNorm.SquareMagnitude() > gp::Resolution())
        {

          double aCos = aVFNorm.Normalized().Dot(aVETgt.Normalized());
          if (std::abs(aCos) > 0.4226)
            bUseAddTol = false;
        }
      }

      double aTolAdd = 0.0;
      if (bUseAddTol)
      {

        for (int iP = 0; iP < 2; ++iP)
        {
          gp_Pnt aP = aBAC.Value(aTS[iP]);
          aProjPS.Perform(aP);
          if (aProjPS.NbPoints())
          {
            double aDistEF = aProjPS.LowerDistance();
            if (aDistEF < aTolCheck && aDistEF > aTolAdd)
              aTolAdd = aDistEF;
          }
        }
        if (aTolAdd > 0.)
        {
          aTolAdd -= (BRep_Tool::Tolerance(aE) + BRep_Tool::Tolerance(aF));
          if (aTolAdd < 0.)
            aTolAdd = 0.;
        }
      }

      bool bIntersect = aTolAdd > 0;
      if (!bIntersect)
      {
        const NCollection_Map<occ::handle<BOPDS_PaveBlock>>* pMPB = myFPBDone.Seek(nF);
        bIntersect                                                = !pMPB || !(pMPB->Contains(aPB));
      }

      if (bIntersect)
      {

        BOPAlgo_EdgeFace& aEdgeFace = aVEdgeFace.Appended();
        aEdgeFace.SetIndices(nE, nF);
        aEdgeFace.SetPaveBlock(aPB);
        aEdgeFace.SetEdge(aE);
        aEdgeFace.SetFace(aF);
        aEdgeFace.SetBoxes(myDS->ShapeInfo(nE).Box(), myDS->ShapeInfo(nF).Box());
        aEdgeFace.SetFuzzyValue(myFuzzyValue + aTolAdd);
        aEdgeFace.UseQuickCoincidenceCheck(true);
        aEdgeFace.SetRange(IntTools_Range(aPB->Pave1().Parameter(), aPB->Pave2().Parameter()));
      }
    }
  }

  int aNbEFs = aVEdgeFace.Length();
  if (!aNbEFs)
  {
    return;
  }

  aPSOuter.Next(0.7);

  aPBMap.Clear();
  anAlloc->Reset(false);

  Message_ProgressScope aPS(aPSOuter.Next(9), "Checking for edges coinciding with faces", aNbEFs);
  for (int i = 0; i < aNbEFs; i++)
  {
    BOPAlgo_EdgeFace& aEdgeFace = aVEdgeFace.ChangeValue(i);
    aEdgeFace.SetProgressRange(aPS.Next());
  }

  BOPTools_Parallel::Perform(myRunParallel, aVEdgeFace, myContext);
  if (UserBreak(aPSOuter))
  {
    return;
  }

  NCollection_Vector<BOPDS_InterfEF>& aEFs = myDS->InterfEF();
  if (theAddInterf && aEFs.IsEmpty())
    aEFs.SetIncrement(10);

  NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>> aMPBLI(1,
                                                                                         anAlloc);
  for (int i = 0; i < aNbEFs; ++i)
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    BOPAlgo_EdgeFace& anEdgeFace = aVEdgeFace(i);
    if (!anEdgeFace.IsDone() || anEdgeFace.HasErrors())
    {

      AddIntersectionFailedWarning(anEdgeFace.Edge(), anEdgeFace.Face());
      continue;
    }

    const NCollection_Sequence<IntTools_CommonPrt>& aCParts = anEdgeFace.CommonParts();
    if (aCParts.Length() != 1)
      continue;

    const IntTools_CommonPrt& aCP = aCParts(1);
    if (aCP.Type() != TopAbs_EDGE)
      continue;

    int nE, nF;
    anEdgeFace.Indices(nE, nF);
    if (theAddInterf)
    {

      BOPDS_InterfEF& aEF = aEFs.Appended();
      aEF.SetIndices(nE, nF);
      aEF.SetCommonPart(aCP);
      myDS->AddInterf(nE, nF);
    }

    const occ::handle<BOPDS_PaveBlock>& aPB = anEdgeFace.PaveBlock();

    myDS->ChangeFaceInfo(nF).ChangePaveBlocksIn().Add(aPB);
    if (theAddInterf)

      BOPAlgo_Tools::FillMap(aPB, nF, aMPBLI, anAlloc);
  }

  if (aMPBLI.Extent())

    BOPAlgo_Tools::PerformCommonBlocks(aMPBLI, anAlloc, myDS);
}
