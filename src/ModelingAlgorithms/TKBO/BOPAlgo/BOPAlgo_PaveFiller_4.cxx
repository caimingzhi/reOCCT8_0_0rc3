#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_FaceInfo.hpp>
#include <BOPDS_Interf.hpp>
#include <BOPDS_Iterator.hpp>
#include <NCollection_Map.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <BOPDS_SubIterator.hpp>
#include <NCollection_Vector.hpp>
#include <BOPTools_Parallel.hpp>
#include <IntTools_Context.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

//=================================================================================================

class BOPAlgo_VertexFace : public BOPAlgo_ParallelAlgo
{
public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_VertexFace()
      : BOPAlgo_ParallelAlgo(),
        myIV(-1),
        myIF(-1),
        myFlag(-1),
        myT1(-1.),
        myT2(-1.),
        myTolVNew(-1.)
  {
  }

  //
  ~BOPAlgo_VertexFace() override = default;

  //
  void SetIndices(const int nV, const int nF)
  {
    myIV = nV;
    myIF = nF;
  }

  //
  void Indices(int& nV, int& nF) const
  {
    nV = myIV;
    nF = myIF;
  }

  //
  void SetVertex(const TopoDS_Vertex& aV) { myV = aV; }

  //
  const TopoDS_Vertex& Vertex() const { return myV; }

  //
  void SetFace(const TopoDS_Face& aF) { myF = aF; }

  //
  const TopoDS_Face& Face() const { return myF; }

  //
  int Flag() const { return myFlag; }

  //
  void Parameters(double& aT1, double& aT2) const
  {
    aT1 = myT1;
    aT2 = myT2;
  }

  //
  double VertexNewTolerance() const { return myTolVNew; }

  //
  void SetContext(const occ::handle<IntTools_Context>& aContext) { myContext = aContext; }

  //
  const occ::handle<IntTools_Context>& Context() const { return myContext; }

  //
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

      myFlag = myContext->ComputeVF(myV, myF, myT1, myT2, myTolVNew, myFuzzyValue);
    }
    catch (Standard_Failure const&)
    {
      AddError(new BOPAlgo_AlertIntersectionFailed);
    }
  }

  //
protected:
  int                           myIV;
  int                           myIF;
  int                           myFlag;
  double                        myT1;
  double                        myT2;
  double                        myTolVNew;
  TopoDS_Vertex                 myV;
  TopoDS_Face                   myF;
  occ::handle<IntTools_Context> myContext;
};

//=======================================================================
typedef NCollection_Vector<BOPAlgo_VertexFace> BOPAlgo_VectorOfVertexFace;

//=================================================================================================

void BOPAlgo_PaveFiller::PerformVF(const Message_ProgressRange& theRange)
{
  myIterator->Initialize(TopAbs_VERTEX, TopAbs_FACE);
  int iSize = myIterator->ExpectedLength();
  //
  int nV, nF;
  //
  Message_ProgressScope aPSOuter(theRange, nullptr, 10);
  if (myGlue == BOPAlgo_GlueFull)
  {
    // there is no need to intersect vertices with faces in this mode
    // just initialize FaceInfo for all faces
    for (; myIterator->More(); myIterator->Next())
    {
      myIterator->Value(nV, nF);
      if (!myDS->IsSubShape(nV, nF))
      {
        myDS->ChangeFaceInfo(nF);
      }
    }
    return;
  }
  //
  NCollection_Vector<BOPDS_InterfVF>& aVFs = myDS->InterfVF();
  if (!iSize)
  {
    iSize = 10;
    aVFs.SetIncrement(iSize);
    //
    TreatVerticesEE();
    return;
  }
  //
  int                        nVSD, iFlag, nVx, aNbVF, k;
  double                     aT1, aT2;
  BOPAlgo_VectorOfVertexFace aVVF;
  //
  aVFs.SetIncrement(iSize);
  //
  // Avoid repeated intersection of the same vertex with face in case
  // the group of vertices formed a single SD vertex
  NCollection_DataMap<BOPDS_Pair, NCollection_Map<int>> aMVFPairs;
  for (; myIterator->More(); myIterator->Next())
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    myIterator->Value(nV, nF);
    //
    if (myDS->IsSubShape(nV, nF))
    {
      continue;
    }
    //
    if (myDS->HasInterf(nV, nF))
    {
      continue;
    }
    //
    myDS->ChangeFaceInfo(nF);
    if (myDS->HasInterfShapeSubShapes(nV, nF))
    {
      continue;
    }
    //
    nVx = nV;
    if (myDS->HasShapeSD(nV, nVSD))
    {
      nVx = nVSD;
    }
    //
    BOPDS_Pair            aVFPair(nVx, nF);
    NCollection_Map<int>* pMV = aMVFPairs.ChangeSeek(aVFPair);
    if (pMV)
    {
      pMV->Add(nV);
      continue;
    }

    pMV = aMVFPairs.Bound(aVFPair, NCollection_Map<int>());
    pMV->Add(nV);

    const TopoDS_Vertex& aV = (*(TopoDS_Vertex*)(&myDS->Shape(nVx)));
    const TopoDS_Face&   aF = (*(TopoDS_Face*)(&myDS->Shape(nF)));
    //
    BOPAlgo_VertexFace& aVertexFace = aVVF.Appended();
    //
    aVertexFace.SetIndices(nVx, nF);
    aVertexFace.SetVertex(aV);
    aVertexFace.SetFace(aF);
    aVertexFace.SetFuzzyValue(myFuzzyValue);

  } // for (; myIterator->More(); myIterator->Next()) {
  //
  aNbVF = aVVF.Length();
  Message_ProgressScope aPS(aPSOuter.Next(9), "Performing Vertex-Face intersection", aNbVF);
  for (k = 0; k < aNbVF; k++)
  {
    BOPAlgo_VertexFace& aVertexFace = aVVF.ChangeValue(k);
    aVertexFace.SetProgressRange(aPS.Next());
  }
  //================================================================
  BOPTools_Parallel::Perform(myRunParallel, aVVF, myContext);
  //================================================================
  if (UserBreak(aPSOuter))
  {
    return;
  }
  //
  for (k = 0; k < aNbVF; ++k)
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    const BOPAlgo_VertexFace& aVertexFace = aVVF(k);
    //
    iFlag = aVertexFace.Flag();
    if (iFlag != 0)
    {
      if (aVertexFace.HasErrors())
      {
        // Warn about failed intersection of sub-shapes
        AddIntersectionFailedWarning(aVertexFace.Vertex(), aVertexFace.Face());
      }
      continue;
    }
    //
    aVertexFace.Indices(nVx, nF);
    aVertexFace.Parameters(aT1, aT2);
    double aTolVNew = aVertexFace.VertexNewTolerance();

    BOPDS_Pair                     aVFPair(nVx, nF);
    const NCollection_Map<int>&    aMV = aMVFPairs.Find(aVFPair);
    NCollection_Map<int>::Iterator itMV(aMV);
    for (; itMV.More(); itMV.Next())
    {
      nV = itMV.Value();
      // 1
      BOPDS_InterfVF& aVF = aVFs.Appended();
      aVF.SetIndices(nV, nF);
      aVF.SetUV(aT1, aT2);
      // 2
      myDS->AddInterf(nV, nF);
      //
      // 3 update vertex V/F if necessary
      nVx = UpdateVertex(nV, aTolVNew);
      //
      // 4
      if (myDS->IsNewShape(nVx))
      {
        aVF.SetIndexNew(nVx);
      }
    }
    // 5 update FaceInfo
    BOPDS_FaceInfo&       aFI   = myDS->ChangeFaceInfo(nF);
    NCollection_Map<int>& aMVIn = aFI.ChangeVerticesIn();
    aMVIn.Add(nVx);
  } // for (k=0; k < aNbVF; ++k) {
  //
  TreatVerticesEE();
}

//=================================================================================================

void BOPAlgo_PaveFiller::TreatVerticesEE()
{
  int                                    i, aNbS, aNbEEs, nF, nV, iFlag;
  double                                 aT1, aT2, dummy;
  NCollection_List<int>::Iterator        aItLI;
  occ::handle<NCollection_BaseAllocator> aAllocator;
  //
  aAllocator = NCollection_BaseAllocator::CommonBaseAllocator();
  NCollection_List<int>                         aLIV(aAllocator), aLIF(aAllocator);
  NCollection_Map<int>                          aMI(100, aAllocator);
  NCollection_Map<occ::handle<BOPDS_PaveBlock>> aMPBF(100, aAllocator);
  //
  aNbS = myDS->NbSourceShapes();
  //
  NCollection_Vector<BOPDS_InterfEE>& aEEs = myDS->InterfEE();
  aNbEEs                                   = aEEs.Length();
  for (i = 0; i < aNbEEs; ++i)
  {
    BOPDS_InterfEE& aEE = aEEs(i);
    if (aEE.HasIndexNew())
    {
      nV = aEE.IndexNew();
      if (aMI.Add(nV))
      {
        aLIV.Append(nV);
      }
    }
  }
  if (!aLIV.Extent())
  {
    aAllocator.Nullify();
    return;
  }
  //
  aNbS = myDS->NbSourceShapes();
  for (nF = 0; nF < aNbS; ++nF)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(nF);
    if (aSI.ShapeType() == TopAbs_FACE)
    {
      aLIF.Append(nF);
    }
  }
  if (!aLIF.Extent())
  {
    aAllocator.Nullify();
    return;
  }
  //-------------------------------------------------------------
  NCollection_Vector<BOPDS_InterfVF>& aVFs = myDS->InterfVF();
  //
  BOPDS_SubIterator aIt(aAllocator);
  //
  aIt.SetDS(myDS);
  aIt.SetSubSet1(aLIF);
  aIt.SetSubSet2(aLIV);
  aIt.Prepare();
  aIt.Initialize();
  for (; aIt.More(); aIt.Next())
  {
    aIt.Value(nV, nF);
    //
    BOPDS_FaceInfo&             aFI   = myDS->ChangeFaceInfo(nF);
    const NCollection_Map<int>& aMVOn = aFI.VerticesOn();
    //
    if (!aMVOn.Contains(nV))
    {
      const TopoDS_Vertex& aV = (*(TopoDS_Vertex*)(&myDS->Shape(nV)));
      const TopoDS_Face&   aF = (*(TopoDS_Face*)(&myDS->Shape(nF)));
      iFlag                   = myContext->ComputeVF(aV, aF, aT1, aT2, dummy, myFuzzyValue);
      if (!iFlag)
      {
        // 1
        BOPDS_InterfVF& aVF = aVFs.Appended();
        i                   = aVFs.Length() - 1;
        aVF.SetIndices(nV, nF);
        aVF.SetUV(aT1, aT2);
        // 2
        myDS->AddInterf(nV, nF);
        //
        NCollection_Map<int>& aMVIn = aFI.ChangeVerticesIn();
        aMVIn.Add(nV);
      }
    }
  }
}
