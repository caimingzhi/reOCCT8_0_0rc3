#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPDS_DS.hpp>
#include <Standard_Handle.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <BOPDS_ShapeInfo.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <IntTools_Context.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
class BOPDS_PaveBlock;

void BOPAlgo_Builder::FillImagesVertices(const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, "Filling splits of vertices", myDS->ShapesSD().Size());
  NCollection_DataMap<int, int>::Iterator aIt(myDS->ShapesSD());
  for (; aIt.More(); aIt.Next(), aPS.Next())
  {
    if (UserBreak(aPS))
    {
      return;
    }
    int nV   = aIt.Key();
    int nVSD = aIt.Value();

    const TopoDS_Shape& aV   = myDS->Shape(nV);
    const TopoDS_Shape& aVSD = myDS->Shape(nVSD);

    myImages.Bound(aV, NCollection_List<TopoDS_Shape>(myAllocator))->Append(aVSD);

    myShapesSD.Bind(aV, aVSD);

    NCollection_List<TopoDS_Shape>* pLOr = myOrigins.ChangeSeek(aVSD);
    if (!pLOr)
      pLOr = myOrigins.Bound(aVSD, NCollection_List<TopoDS_Shape>());
    pLOr->Append(aV);
  }
}

void BOPAlgo_Builder::FillImagesEdges(const Message_ProgressRange& theRange)
{
  int                   i, aNbS = myDS->NbSourceShapes();
  Message_ProgressScope aPS(theRange, "Filling splits of edges", aNbS);
  for (i = 0; i < aNbS; ++i, aPS.Next())
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_EDGE)
    {
      continue;
    }

    if (!aSI.HasReference())
    {
      continue;
    }

    const TopoDS_Shape&                                   aE   = aSI.Shape();
    const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = myDS->PaveBlocks(i);

    NCollection_List<TopoDS_Shape>* pLS = myImages.Bound(aE, NCollection_List<TopoDS_Shape>());

    NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItPB(aLPB);
    for (; aItPB.More(); aItPB.Next())
    {
      const occ::handle<BOPDS_PaveBlock>& aPB  = aItPB.Value();
      occ::handle<BOPDS_PaveBlock>        aPBR = myDS->RealPaveBlock(aPB);

      int                 nSpR = aPBR->Edge();
      const TopoDS_Shape& aSpR = myDS->Shape(nSpR);
      pLS->Append(aSpR);

      NCollection_List<TopoDS_Shape>* pLOr = myOrigins.ChangeSeek(aSpR);
      if (!pLOr)
      {
        pLOr = myOrigins.Bound(aSpR, NCollection_List<TopoDS_Shape>());
      }
      pLOr->Append(aE);

      if (myDS->IsCommonBlockOnEdge(aPB))
      {
        int                 nSp = aPB->Edge();
        const TopoDS_Shape& aSp = myDS->Shape(nSp);
        myShapesSD.Bind(aSp, aSpR);
      }
    }
    if (UserBreak(aPS))
    {
      return;
    }
  }
}

void BOPAlgo_Builder::BuildResult(const TopAbs_ShapeEnum theType)
{

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;

  NCollection_List<TopoDS_Shape>::Iterator aItA(myArguments);
  for (; aItA.More(); aItA.Next())
  {
    const TopoDS_Shape& aS = aItA.Value();
    if (aS.ShapeType() != theType)
      continue;

    const NCollection_List<TopoDS_Shape>* pLSIm = myImages.Seek(aS);
    if (!pLSIm)
    {

      if (aMFence.Add(aS))
        BRep_Builder().Add(myShape, aS);
    }
    else
    {

      NCollection_List<TopoDS_Shape>::Iterator aItIm(*pLSIm);
      for (; aItIm.More(); aItIm.Next())
      {
        const TopoDS_Shape& aSIm = aItIm.Value();
        if (aMFence.Add(aSIm))
          BRep_Builder().Add(myShape, aSIm);
      }
    }
  }
}

void BOPAlgo_Builder::FillImagesContainers(const TopAbs_ShapeEnum       theType,
                                           const Message_ProgressRange& theRange)
{
  int                                                    i, aNbS;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFP(100, myAllocator);

  aNbS = myDS->NbSourceShapes();
  Message_ProgressScope aPS(theRange, "Building splits of containers", 1);
  for (i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() == theType)
    {
      const TopoDS_Shape& aC = aSI.Shape();
      FillImagesContainer(aC, theType);
    }
    if (UserBreak(aPS))
    {
      return;
    }
  }
}

void BOPAlgo_Builder::FillImagesCompounds(const Message_ProgressRange& theRange)
{
  int                                                    i, aNbS;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFP(100, myAllocator);

  aNbS = myDS->NbSourceShapes();
  Message_ProgressScope aPS(theRange, "Building splits of compounds", aNbS);
  for (i = 0; i < aNbS; ++i, aPS.Next())
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() == TopAbs_COMPOUND)
    {
      const TopoDS_Shape& aC = aSI.Shape();
      FillImagesCompound(aC, aMFP);
    }
    if (UserBreak(aPS))
    {
      return;
    }
  }
}

void BOPAlgo_Builder::FillImagesContainer(const TopoDS_Shape& theS, const TopAbs_ShapeEnum theType)
{

  TopoDS_Iterator aIt(theS);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape&                   aSS   = aIt.Value();
    const NCollection_List<TopoDS_Shape>* pLFIm = myImages.Seek(aSS);
    if (pLFIm && ((pLFIm->Extent() != 1) || !pLFIm->First().IsSame(aSS)))
      break;
  }

  if (!aIt.More())
  {

    return;
  }

  BRep_Builder aBB;

  TopoDS_Shape aCIm;
  BOPTools_AlgoTools::MakeContainer(theType, aCIm);

  aIt.Initialize(theS);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape&                   aSS    = aIt.Value();
    const NCollection_List<TopoDS_Shape>* pLSSIm = myImages.Seek(aSS);

    if (!pLSSIm)
    {

      aBB.Add(aCIm, aSS);
      continue;
    }

    NCollection_List<TopoDS_Shape>::Iterator aItIm(*pLSSIm);
    for (; aItIm.More(); aItIm.Next())
    {
      TopoDS_Shape aSSIm = aItIm.Value();
      if (!aSSIm.IsEqual(aSS)
          && BOPTools_AlgoTools::IsSplitToReverseWithWarn(aSSIm, aSS, myContext, myReport))
      {
        aSSIm.Reverse();
      }
      aBB.Add(aCIm, aSSIm);
    }
  }

  aCIm.Closed(BRep_Tool::IsClosed(aCIm));
  myImages.Bound(theS, NCollection_List<TopoDS_Shape>(myAllocator))->Append(aCIm);
}

void BOPAlgo_Builder::FillImagesCompound(
  const TopoDS_Shape&                                     theS,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMFP)
{
  bool                                     bInterferred;
  TopAbs_Orientation                       aOrX;
  TopoDS_Iterator                          aIt;
  BRep_Builder                             aBB;
  NCollection_List<TopoDS_Shape>::Iterator aItIm;

  if (!theMFP.Add(theS))
  {
    return;
  }

  bInterferred = false;
  aIt.Initialize(theS);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aSx = aIt.Value();
    if (aSx.ShapeType() == TopAbs_COMPOUND)
    {
      FillImagesCompound(aSx, theMFP);
    }
    if (myImages.IsBound(aSx))
    {
      bInterferred = true;
    }
  }
  if (!bInterferred)
  {
    return;
  }

  TopoDS_Shape aCIm;
  BOPTools_AlgoTools::MakeContainer(TopAbs_COMPOUND, aCIm);

  aIt.Initialize(theS);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aSX = aIt.Value();
    aOrX                    = aSX.Orientation();
    if (myImages.IsBound(aSX))
    {
      const NCollection_List<TopoDS_Shape>& aLFIm = myImages.Find(aSX);
      aItIm.Initialize(aLFIm);
      for (; aItIm.More(); aItIm.Next())
      {
        TopoDS_Shape aSXIm = aItIm.Value();
        aSXIm.Orientation(aOrX);
        aBB.Add(aCIm, aSXIm);
      }
    }
    else
    {
      aBB.Add(aCIm, aSX);
    }
  }

  NCollection_List<TopoDS_Shape> aLSIm(myAllocator);
  aLSIm.Append(aCIm);
  myImages.Bind(theS, aLSIm);
}
