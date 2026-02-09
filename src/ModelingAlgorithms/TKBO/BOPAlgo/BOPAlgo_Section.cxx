#include <BOPAlgo_Section.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_FaceInfo.hpp>
#include <Standard_Handle.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <NCollection_Vector.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BRep_Builder.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>
class BOPDS_PaveBlock;

BOPAlgo_Section::BOPAlgo_Section()

{
  Clear();
}

BOPAlgo_Section::BOPAlgo_Section(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_Builder(theAllocator)
{
  Clear();
}

BOPAlgo_Section::~BOPAlgo_Section() = default;

void BOPAlgo_Section::CheckData()
{
  int aNbArgs;

  aNbArgs = myArguments.Extent();
  if (!aNbArgs)
  {
    AddError(new BOPAlgo_AlertTooFewArguments);
    return;
  }

  CheckFiller();
}

void BOPAlgo_Section::fillPIConstants(const double theWhole, BOPAlgo_PISteps& theSteps) const
{

  if (myFillHistory)
  {

    theSteps.SetStep(PIOperation_FillHistory, 10. * theWhole / 100.);
  }

  theSteps.SetStep(PIOperation_PostTreat, 5. * theWhole / 100.);
}

void BOPAlgo_Section::fillPISteps(BOPAlgo_PISteps& theSteps) const
{

  NbShapes aNbShapes = getNbShapes();
  theSteps.SetStep(PIOperation_TreatVertices, aNbShapes.NbVertices());
  theSteps.SetStep(PIOperation_TreatEdges, aNbShapes.NbEdges());
  theSteps.SetStep(PIOperation_BuildSection, aNbShapes.NbEdges() + aNbShapes.NbFaces());
}

void BOPAlgo_Section::PerformInternal1(const BOPAlgo_PaveFiller&    theFiller,
                                       const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, "Building result of SECTION operation", 100);
  myPaveFiller = (BOPAlgo_PaveFiller*)&theFiller;
  myDS         = myPaveFiller->PDS();
  myContext    = myPaveFiller->Context();

  CheckData();
  if (HasErrors())
  {
    return;
  }

  Prepare();
  if (HasErrors())
  {
    return;
  }

  BOPAlgo_PISteps aSteps(PIOperation_Last);
  analyzeProgress(100., aSteps);

  FillImagesVertices(aPS.Next(aSteps.GetStep(PIOperation_TreatVertices)));
  if (HasErrors())
  {
    return;
  }

  BuildResult(TopAbs_VERTEX);
  if (HasErrors())
  {
    return;
  }

  FillImagesEdges(aPS.Next(aSteps.GetStep(PIOperation_TreatEdges)));
  if (HasErrors())
  {
    return;
  }

  BuildResult(TopAbs_EDGE);
  if (HasErrors())
  {
    return;
  }

  BuildSection(aPS.Next(aSteps.GetStep(PIOperation_BuildSection)));
  if (HasErrors())
  {
    return;
  }

  PrepareHistory(aPS.Next(aSteps.GetStep(PIOperation_FillHistory)));
  if (HasErrors())
  {
    return;
  }

  PostTreat(aPS.Next(aSteps.GetStep(PIOperation_PostTreat)));
}

void BOPAlgo_Section::BuildSection(const Message_ProgressRange& theRange)
{
  Message_ProgressScope          aPS(theRange, "Building the result of Section operation", 1);
  int                            i, aNbMS, aNbLE;
  int                            j, nE, nV, aNb, aNbF, aNbPBSc;
  TopoDS_Shape                   aRC, aRC1;
  BRep_Builder                   aBB;
  TopExp_Explorer                aExp;
  NCollection_List<TopoDS_Shape> aLSA, aLS;
  NCollection_List<TopoDS_Shape>::Iterator                               aIt, aItIm, aItLS;
  NCollection_IndexedDataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher> aMSI(100, myAllocator);
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>          aMS(100, myAllocator);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                 aMFence(100, myAllocator);
  NCollection_Map<int>::Iterator                                         aItMI;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator               aItPB;

  GetReport()->Clear();

  BOPTools_AlgoTools::MakeContainer(TopAbs_COMPOUND, aRC1);

  aNb = myDS->NbSourceShapes();
  for (i = 0; i < aNb; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_FACE)
    {
      continue;
    }
    if (UserBreak(aPS))
    {
      return;
    }

    const BOPDS_FaceInfo& aFI = myDS->FaceInfo(i);

    const NCollection_Map<int>& aMVSc = aFI.VerticesSc();
    aItMI.Initialize(aMVSc);
    for (; aItMI.More(); aItMI.Next())
    {
      nV                     = aItMI.Key();
      const TopoDS_Shape& aV = myDS->Shape(nV);
      aBB.Add(aRC1, aV);
    }

    const NCollection_Map<int>& aMI = aFI.VerticesIn();
    aItMI.Initialize(aMI);
    for (; aItMI.More(); aItMI.Next())
    {
      nV = aItMI.Key();
      if (nV < 0)
      {
        continue;
      }
      if (myDS->IsNewShape(nV) || myDS->HasInterf(nV))
      {
        const TopoDS_Shape& aV = myDS->Shape(nV);
        aBB.Add(aRC1, aV);
      }
    }

    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& aMPBSc = aFI.PaveBlocksSc();

    aNbPBSc = aMPBSc.Extent();
    for (j = 1; j <= aNbPBSc; ++j)
    {
      const occ::handle<BOPDS_PaveBlock>& aPB = aMPBSc(j);
      nE                                      = aPB->Edge();
      const TopoDS_Shape& aE                  = myDS->Shape(nE);
      aBB.Add(aRC1, aE);
    }
  }

  const NCollection_Vector<NCollection_List<occ::handle<BOPDS_PaveBlock>>>& aPBP =
    myDS->PaveBlocksPool();

  aNb = aPBP.Size();
  for (i = 0; i < aNb; ++i)
  {
    const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = aPBP(i);
    aItPB.Initialize(aLPB);
    for (; aItPB.More(); aItPB.Next())
    {
      const occ::handle<BOPDS_PaveBlock>& aPB = aItPB.Value();
      occ::handle<BOPDS_CommonBlock>      aCB = myDS->CommonBlock(aPB);
      if (!aCB.IsNull())
      {
        const NCollection_List<int>& aLF = aCB->Faces();
        aNbF                             = aLF.Extent();
        if (aNbF)
        {
          const occ::handle<BOPDS_PaveBlock>& aPBR = aCB->PaveBlock1();
          nE                                       = aPBR->Edge();
          const TopoDS_Shape& aE                   = myDS->Shape(nE);
          aBB.Add(aRC1, aE);
        }
      }
    }
  }

  aIt.Initialize(myArguments);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aSA = aIt.Value();
    if (aMFence.Add(aSA))
    {
      aLSA.Append(aSA);
    }
  }

  aMFence.Clear();

  aIt.Initialize(aLSA);
  for (; aIt.More(); aIt.Next())
  {
    if (UserBreak(aPS))
    {
      return;
    }
    const TopoDS_Shape& aSA = aIt.Value();

    aLS.Clear();
    aMS.Clear();
    aMFence.Clear();

    aExp.Init(aSA, TopAbs_EDGE);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Shape& aE = aExp.Current();
      if (aMFence.Add(aE))
      {
        aLS.Append(aE);
      }
    }
    aExp.Init(aSA, TopAbs_VERTEX);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Shape& aE = aExp.Current();
      if (aMFence.Add(aE))
      {
        aLS.Append(aE);
      }
    }

    aItLS.Initialize(aLS);
    for (; aItLS.More(); aItLS.Next())
    {
      const TopoDS_Shape& aS = aItLS.Value();

      if (myImages.IsBound(aS))
      {
        const NCollection_List<TopoDS_Shape>& aLSIm = myImages.Find(aS);
        aItIm.Initialize(aLSIm);
        for (; aItIm.More(); aItIm.Next())
        {
          const TopoDS_Shape& aSIm = aItIm.Value();
          TopExp::MapShapes(aSIm, TopAbs_VERTEX, aMS);
          TopExp::MapShapes(aSIm, TopAbs_EDGE, aMS);
        }
      }
      else
      {
        TopExp::MapShapes(aS, TopAbs_VERTEX, aMS);
        TopExp::MapShapes(aS, TopAbs_EDGE, aMS);
      }
    }

    aNbMS = aMS.Extent();
    for (i = 1; i <= aNbMS; ++i)
    {
      const TopoDS_Shape& aS = aMS(i);
      if (aMSI.Contains(aS))
      {
        int& iCnt = aMSI.ChangeFromKey(aS);
        ++iCnt;
      }
      else
      {
        aMSI.Add(aS, 1);
      }
    }
  }

  aMS.Clear();
  aMFence.Clear();

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMVE(100, myAllocator);

  TopExp::MapShapesAndAncestors(aRC1, TopAbs_VERTEX, TopAbs_EDGE, aMVE);

  aNbMS = aMSI.Extent();
  for (i = 1; i <= aNbMS; ++i)
  {
    const TopoDS_Shape& aV   = aMSI.FindKey(i);
    const int&          iCnt = aMSI.FindFromIndex(i);
    if (iCnt > 1)
    {
      TopExp::MapShapesAndAncestors(aV, TopAbs_VERTEX, TopAbs_EDGE, aMVE);
    }
  }

  BOPTools_AlgoTools::MakeContainer(TopAbs_COMPOUND, aRC);

  aNbMS = aMVE.Extent();
  for (i = 1; i <= aNbMS; ++i)
  {
    if (UserBreak(aPS))
    {
      return;
    }
    const TopoDS_Shape&                   aV  = aMVE.FindKey(i);
    const NCollection_List<TopoDS_Shape>& aLE = aMVE.FindFromIndex(i);
    aNbLE                                     = aLE.Extent();
    if (!aNbLE)
    {

      if (aMFence.Add(aV))
      {
        aBB.Add(aRC, aV);
      }
    }
    else
    {

      aIt.Initialize(aLE);
      for (; aIt.More(); aIt.Next())
      {
        const TopoDS_Shape& aE = aIt.Value();
        if (aMFence.Add(aE))
        {
          aBB.Add(aRC, aE);
        }
      }
    }
  }

  myShape = aRC;
}
