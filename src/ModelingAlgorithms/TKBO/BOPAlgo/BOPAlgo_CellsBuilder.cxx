#include <BOPAlgo_CellsBuilder.hpp>

#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_BuilderSolid.hpp>
#include <BOPDS_DS.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BRep_Builder.hpp>
#include <ShapeUpgrade_UnifySameDomain.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Compound.hpp>

static TopAbs_ShapeEnum TypeToExplore(const int theDim);

static void MakeTypedContainers(const TopoDS_Shape& theSC, TopoDS_Shape& theResult);

static void CollectMaterialBoundaries(
  const NCollection_List<TopoDS_Shape>&                   theLS,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapKeepBnd);

BOPAlgo_CellsBuilder::BOPAlgo_CellsBuilder()
    : myIndex(100, myAllocator),
      myMaterials(100, myAllocator),
      myShapeMaterial(100, myAllocator),
      myMapModified(100, myAllocator)
{
}

BOPAlgo_CellsBuilder::BOPAlgo_CellsBuilder(
  const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_Builder(theAllocator),
      myIndex(100, myAllocator),
      myMaterials(100, myAllocator),
      myShapeMaterial(100, myAllocator),
      myMapModified(100, myAllocator)
{
}

BOPAlgo_CellsBuilder::~BOPAlgo_CellsBuilder()
{
  Clear();
}

void BOPAlgo_CellsBuilder::Clear()
{
  BOPAlgo_Builder::Clear();
  myIndex.Clear();
  myMaterials.Clear();
  myShapeMaterial.Clear();
  myMapModified.Clear();
}

const TopoDS_Shape& BOPAlgo_CellsBuilder::GetAllParts() const
{
  return myAllParts;
}

void BOPAlgo_CellsBuilder::PerformInternal1(const BOPAlgo_PaveFiller&    theFiller,
                                            const Message_ProgressRange& theRange)
{

  bool isHistory = HasHistory();
  SetToFillHistory(false);

  Message_ProgressScope aPS(theRange, "Performing MakeCells operation", 1);
  BOPAlgo_Builder::PerformInternal1(theFiller, aPS.Next());
  if (HasErrors())
  {
    return;
  }

  IndexParts();

  RemoveAllFromResult();

  SetToFillHistory(isHistory);
}

void BOPAlgo_CellsBuilder::IndexParts()
{
  BRep_Builder aBB;

  TopoDS_Compound anAllParts;
  aBB.MakeCompound(anAllParts);

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;
  NCollection_Map<int>                                   aMDims;

  NCollection_List<TopoDS_Shape>::Iterator aIt(myArguments);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aS = aIt.Value();

    NCollection_List<TopoDS_Shape> aLSubS;
    BOPTools_AlgoTools::TreatCompound(aS, aLSubS);
    for (NCollection_List<TopoDS_Shape>::Iterator itSub(aLSubS); itSub.More(); itSub.Next())
    {
      const TopoDS_Shape& aSS  = itSub.Value();
      int                 iDim = BOPTools_AlgoTools::Dimension(aSS);
      aMDims.Add(iDim);
      TopAbs_ShapeEnum aType = TypeToExplore(iDim);
      TopExp_Explorer  aExp(aSS, aType);
      for (; aExp.More(); aExp.Next())
      {
        const TopoDS_Shape&                   aST   = aExp.Current();
        const NCollection_List<TopoDS_Shape>* pLSIm = myImages.Seek(aST);
        if (!pLSIm)
        {
          NCollection_List<TopoDS_Shape>* pLS = myIndex.ChangeSeek(aST);
          if (!pLS)
          {
            pLS = &myIndex(myIndex.Add(aST, NCollection_List<TopoDS_Shape>()));
          }
          pLS->Append(aS);

          if (aMFence.Add(aST))
          {
            aBB.Add(anAllParts, aST);
          }

          continue;
        }

        NCollection_List<TopoDS_Shape>::Iterator aItIm(*pLSIm);
        for (; aItIm.More(); aItIm.Next())
        {
          const TopoDS_Shape& aSTIm = aItIm.Value();

          NCollection_List<TopoDS_Shape>* pLS = myIndex.ChangeSeek(aSTIm);
          if (!pLS)
          {
            pLS = &myIndex(myIndex.Add(aSTIm, NCollection_List<TopoDS_Shape>()));
          }
          pLS->Append(aS);

          if (aMFence.Add(aSTIm))
          {
            aBB.Add(anAllParts, aSTIm);
          }
        }
      }
    }
  }

  myAllParts = anAllParts;

  if (aMDims.Extent() == 1)
  {
    return;
  }

  int i, aNbS = myIndex.Extent();
  for (i = 1; i <= aNbS; ++i)
  {
    const TopoDS_Shape&                   aSP   = myIndex.FindKey(i);
    const NCollection_List<TopoDS_Shape>& aLSOr = myIndex(i);

    int                            iType = BOPTools_AlgoTools::Dimension(aSP);
    NCollection_Map<int>::Iterator aItM(aMDims);
    for (; aItM.More(); aItM.Next())
    {
      int k = aItM.Value();
      if (k >= iType)
      {
        continue;
      }

      TopExp_Explorer aExp(aSP, TypeToExplore(k));
      for (; aExp.More(); aExp.Next())
      {
        const TopoDS_Shape&             aSS    = aExp.Current();
        NCollection_List<TopoDS_Shape>* pLSSOr = myIndex.ChangeSeek(aSS);
        if (!pLSSOr)
        {
          myIndex.Add(aSS, aLSOr);
          continue;
        }

        NCollection_List<TopoDS_Shape>::Iterator aItLS(aLSOr);
        for (; aItLS.More(); aItLS.Next())
        {
          const TopoDS_Shape& aSOr = aItLS.Value();

          NCollection_List<TopoDS_Shape>::Iterator aItLSS(*pLSSOr);
          for (; aItLSS.More(); aItLSS.Next())
          {
            if (aSOr.IsSame(aItLSS.Value()))
            {
              break;
            }
          }

          if (!aItLSS.More())
          {
            pLSSOr->Append(aSOr);
          }
        }
      }
    }
  }
}

void BOPAlgo_CellsBuilder::AddToResult(const NCollection_List<TopoDS_Shape>& theLSToTake,
                                       const NCollection_List<TopoDS_Shape>& theLSToAvoid,
                                       const int                             theMaterial,
                                       const bool                            theUpdate)
{

  NCollection_List<TopoDS_Shape> aParts;
  FindParts(theLSToTake, theLSToAvoid, aParts);
  if (aParts.IsEmpty())
  {
    return;
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aResParts;
  TopoDS_Iterator                                        aIt(myShape);
  for (; aIt.More(); aIt.Next())
  {
    aResParts.Add(aIt.Value());
  }

  bool bChanged = false;

  NCollection_List<TopoDS_Shape>::Iterator aItLP(aParts);
  for (; aItLP.More(); aItLP.Next())
  {
    const TopoDS_Shape& aPart = aItLP.Value();

    if (aResParts.Add(aPart) && !myShapeMaterial.IsBound(aPart))
    {
      BRep_Builder().Add(myShape, aPart);
      bChanged = true;
    }
  }

  if (theMaterial != 0)
  {
    NCollection_List<TopoDS_Shape> aLSP;
    aItLP.Initialize(aParts);
    for (; aItLP.More(); aItLP.Next())
    {
      const TopoDS_Shape& aPart = aItLP.Value();
      if (!myShapeMaterial.IsBound(aPart))
      {
        myShapeMaterial.Bind(aPart, theMaterial);
        aLSP.Append(aPart);
      }
    }

    if (aLSP.Extent())
    {
      NCollection_List<TopoDS_Shape>* pLS = myMaterials.ChangeSeek(theMaterial);
      if (!pLS)
      {
        pLS = myMaterials.Bound(theMaterial, NCollection_List<TopoDS_Shape>());
      }
      pLS->Append(aLSP);
    }
  }

  if (!theUpdate)
  {
    if (bChanged)
    {
      PrepareHistory(Message_ProgressRange());
    }
  }
  else
  {
    RemoveInternalBoundaries();
  }
}

void BOPAlgo_CellsBuilder::AddAllToResult(const int theMaterial, const bool theUpdate)
{
  myShapeMaterial.Clear();
  myMaterials.Clear();
  myMapModified.Clear();

  myShape = myAllParts;

  if (theMaterial != 0)
  {
    NCollection_List<TopoDS_Shape>* pLSM =
      myMaterials.Bound(theMaterial, NCollection_List<TopoDS_Shape>());

    TopoDS_Iterator aIt(myAllParts);
    for (; aIt.More(); aIt.Next())
    {
      const TopoDS_Shape& aPart = aIt.Value();
      myShapeMaterial.Bind(aPart, theMaterial);
      pLSM->Append(aPart);
    }
  }

  if (!theUpdate)
  {
    PrepareHistory(Message_ProgressRange());
  }
  else
  {
    RemoveInternalBoundaries();
  }
}

void BOPAlgo_CellsBuilder::RemoveFromResult(const NCollection_List<TopoDS_Shape>& theLSToTake,
                                            const NCollection_List<TopoDS_Shape>& theLSToAvoid)
{

  NCollection_List<TopoDS_Shape> aParts;
  FindParts(theLSToTake, theLSToAvoid, aParts);
  if (aParts.IsEmpty())
  {
    return;
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aPartsToRemove;
  NCollection_List<TopoDS_Shape>::Iterator               aItP(aParts);
  for (; aItP.More(); aItP.Next())
  {
    const TopoDS_Shape& aPart = aItP.Value();
    aPartsToRemove.Add(aPart);

    const int* pMaterial = myShapeMaterial.Seek(aPart);
    if (pMaterial)
    {
      NCollection_List<TopoDS_Shape>* pLSM = myMaterials.ChangeSeek(*pMaterial);
      if (pLSM)
      {
        NCollection_List<TopoDS_Shape>::Iterator aItM(*pLSM);
        for (; aItM.More(); aItM.Next())
        {
          if (aPart.IsSame(aItM.Value()))
          {
            pLSM->Remove(aItM);
            break;
          }
        }
      }
      myShapeMaterial.UnBind(aPart);
    }
  }

  BRep_Builder    aBB;
  TopoDS_Compound aResult;
  aBB.MakeCompound(aResult);
  bool bChanged = false;

  TopoDS_Iterator aIt(myShape);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aS    = aIt.Value();
    TopAbs_ShapeEnum    aType = aS.ShapeType();
    if (aType != TopAbs_WIRE && aType != TopAbs_SHELL && aType != TopAbs_COMPSOLID)
    {

      if (aPartsToRemove.Contains(aS))
      {
        bChanged = true;
        continue;
      }
      aBB.Add(aResult, aS);
    }
    else
    {

      TopoDS_Compound aSC;
      aBB.MakeCompound(aSC);
      bool bSCNotEmpty = false;

      TopoDS_Iterator aItSC(aS);
      for (; aItSC.More(); aItSC.Next())
      {
        const TopoDS_Shape& aSS = aItSC.Value();
        if (aPartsToRemove.Contains(aSS))
        {
          bChanged = true;
          continue;
        }

        bSCNotEmpty = true;
        aBB.Add(aSC, aSS);
      }

      if (bSCNotEmpty)
      {
        MakeTypedContainers(aSC, aResult);
      }
    }
  }

  if (bChanged)
  {
    myShape = aResult;

    PrepareHistory(Message_ProgressRange());
  }
}

void BOPAlgo_CellsBuilder::RemoveAllFromResult()
{

  TopoDS_Compound aC;
  BRep_Builder().MakeCompound(aC);
  myShape = aC;

  myMaterials.Clear();
  myShapeMaterial.Clear();
  myMapModified.Clear();

  PrepareHistory(Message_ProgressRange());
}

void BOPAlgo_CellsBuilder::RemoveInternalBoundaries()
{
  if (myMaterials.IsEmpty())
  {
    return;
  }

  BRep_Builder    aBB;
  TopoDS_Compound aResult;
  aBB.MakeCompound(aResult);

  bool bChanged = false;

  NCollection_DataMap<int, NCollection_List<TopoDS_Shape>>::Iterator aItM(myMaterials);
  NCollection_List<TopoDS_Shape>                                     aLSUnify[2];
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>             aKeepMap[2];
  for (; aItM.More(); aItM.Next())
  {
    int                             iMaterial = aItM.Key();
    NCollection_List<TopoDS_Shape>& aLS       = aItM.ChangeValue();

    if (aLS.IsEmpty())
    {
      continue;
    }

    if (aLS.Extent() == 1)
    {
      TopAbs_ShapeEnum aType = aLS.First().ShapeType();
      if (aType != TopAbs_WIRE && aType != TopAbs_SHELL && aType != TopAbs_COMPSOLID)
      {
        aBB.Add(aResult, aLS.First());
        continue;
      }
    }

    NCollection_List<TopoDS_Shape>::Iterator aItLS(aLS);
    TopAbs_ShapeEnum                         aType = aItLS.Value().ShapeType();
    for (aItLS.Next(); aItLS.More(); aItLS.Next())
    {
      if (aType != aItLS.Value().ShapeType())
      {
        break;
      }
    }

    if (aItLS.More())
    {

      TopoDS_Compound aMultiDimS;
      aBB.MakeCompound(aMultiDimS);
      aBB.Add(aMultiDimS, aLS.First());
      aBB.Add(aMultiDimS, aItLS.Value());
      AddWarning(new BOPAlgo_AlertRemovalOfIBForMDimShapes(aMultiDimS));
    }
    else
    {
      if (aType == TopAbs_EDGE || aType == TopAbs_FACE)
      {

        int iType = (aType == TopAbs_EDGE ? 0 : 1);
        CollectMaterialBoundaries(aLS, aKeepMap[iType]);

        NCollection_List<TopoDS_Shape> aCopy(aLS);
        aLSUnify[iType].Append(aCopy);
        continue;
      }
      else
      {

        NCollection_List<TopoDS_Shape> aLSNew;
        if (RemoveInternals(aLS, aLSNew))
        {
          bChanged = true;

          for (aItLS.Initialize(aLSNew); aItLS.More(); aItLS.Next())
          {
            const TopoDS_Shape& aS = aItLS.Value();
            myShapeMaterial.Bind(aS, iMaterial);
          }
          aLS.Assign(aLSNew);
        }
      }
    }

    for (aItLS.Initialize(aLS); aItLS.More(); aItLS.Next())
    {
      const TopoDS_Shape& aS = aItLS.Value();
      aBB.Add(aResult, aS);
    }
  }

  for (int iType = 0; iType < 2; ++iType)
  {
    if (aLSUnify[iType].IsEmpty())
      continue;
    NCollection_List<TopoDS_Shape> aLSN;
    if (RemoveInternals(aLSUnify[iType], aLSN, aKeepMap[iType]))
      bChanged = true;

    for (NCollection_List<TopoDS_Shape>::Iterator aItLS(aLSN); aItLS.More(); aItLS.Next())
    {
      const TopoDS_Shape& aS = aItLS.Value();
      aBB.Add(aResult, aS);
    }
  }

  if (bChanged)
  {

    TopoDS_Iterator aIt(myShape);
    for (; aIt.More(); aIt.Next())
    {
      const TopoDS_Shape& aS = aIt.Value();

      if (myShapeMaterial.IsBound(aS))
      {
        continue;
      }

      TopAbs_ShapeEnum aType = aS.ShapeType();
      if (aType != TopAbs_WIRE && aType != TopAbs_SHELL && aType != TopAbs_COMPSOLID)
      {
        aBB.Add(aResult, aS);
      }
      else
      {
        TopoDS_Compound aSC;
        aBB.MakeCompound(aSC);
        bool bSCEmpty(true), bSCChanged(false);

        TopoDS_Iterator aItSC(aS);
        for (; aItSC.More(); aItSC.Next())
        {
          const TopoDS_Shape& aSS = aItSC.Value();
          if (!myShapeMaterial.IsBound(aSS))
          {
            aBB.Add(aSC, aSS);
            bSCEmpty = false;
          }
          else
          {
            bSCChanged = true;
          }
        }

        if (bSCEmpty)
        {
          continue;
        }

        if (bSCChanged)
        {
          MakeTypedContainers(aSC, aResult);
        }
        else
        {
          aBB.Add(aResult, aS);
        }
      }
    }

    myShape = aResult;

    PrepareHistory(Message_ProgressRange());
  }
}

void BOPAlgo_CellsBuilder::FindParts(const NCollection_List<TopoDS_Shape>& theLSToTake,
                                     const NCollection_List<TopoDS_Shape>& theLSToAvoid,
                                     NCollection_List<TopoDS_Shape>&       theParts)
{
  if (theLSToTake.IsEmpty())
  {
    return;
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMSToAvoid;
  NCollection_List<TopoDS_Shape>::Iterator               aItArgs(theLSToAvoid);
  for (; aItArgs.More(); aItArgs.Next())
  {
    const TopoDS_Shape& aS = aItArgs.Value();
    aMSToAvoid.Add(aS);
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMSToTake;
  aItArgs.Initialize(theLSToTake);
  for (; aItArgs.More(); aItArgs.Next())
  {
    const TopoDS_Shape& aS = aItArgs.Value();
    aMSToTake.Add(aS);
  }

  int aNbS = aMSToTake.Extent();

  int          iDimMin = 10;
  TopoDS_Shape aSMin;

  aItArgs.Initialize(theLSToTake);
  for (; aItArgs.More(); aItArgs.Next())
  {
    const TopoDS_Shape& aS   = aItArgs.Value();
    int                 iDim = BOPTools_AlgoTools::Dimension(aS);
    if (iDim < iDimMin)
    {
      iDimMin = iDim;
      aSMin   = aS;
    }
  }

  TopAbs_ShapeEnum aType = TypeToExplore(iDimMin);
  TopExp_Explorer  aExp(aSMin, aType);
  for (; aExp.More(); aExp.Next())
  {
    const TopoDS_Shape& aST = aExp.Current();

    NCollection_List<TopoDS_Shape> aLSTIm;
    if (!myImages.IsBound(aST))
    {
      aLSTIm.Append(aST);
    }
    else
    {
      aLSTIm = myImages.Find(aST);
    }

    NCollection_List<TopoDS_Shape>::Iterator aItIm(aLSTIm);
    for (; aItIm.More(); aItIm.Next())
    {
      const TopoDS_Shape& aPart = aItIm.Value();

      if (!myIndex.Contains(aPart))
      {
        continue;
      }

      const NCollection_List<TopoDS_Shape>& aLS = myIndex.FindFromKey(aPart);
      if (aLS.Extent() < aNbS)
      {
        continue;
      }

      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMS;
      aItArgs.Initialize(aLS);
      for (; aItArgs.More(); aItArgs.Next())
      {
        const TopoDS_Shape& aS = aItArgs.Value();
        aMS.Add(aS);
        if (aMSToAvoid.Contains(aS))
        {
          break;
        }
      }

      if (aItArgs.More())
      {
        continue;
      }

      aItArgs.Initialize(theLSToTake);
      for (; aItArgs.More(); aItArgs.Next())
      {
        if (!aMS.Contains(aItArgs.Value()))
        {
          break;
        }
      }

      if (!aItArgs.More())
      {
        theParts.Append(aPart);
      }
    }
  }
}

void BOPAlgo_CellsBuilder::MakeContainers()
{
  BRep_Builder    aBB;
  TopoDS_Compound aResult;
  aBB.MakeCompound(aResult);

  NCollection_List<TopoDS_Shape> aLS[3];

  TopoDS_Iterator aIt(myShape);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aS = aIt.Value();

    int iDim = BOPTools_AlgoTools::Dimension(aS);
    if (iDim <= 0)
    {
      aBB.Add(aResult, aS);
      continue;
    }

    aLS[iDim - 1].Append(aS);
  }

  for (int i = 0; i < 3; ++i)
  {
    if (aLS[i].IsEmpty())
    {
      continue;
    }

    TopoDS_Compound aC;
    aBB.MakeCompound(aC);
    NCollection_List<TopoDS_Shape>::Iterator aItLS(aLS[i]);
    for (; aItLS.More(); aItLS.Next())
    {
      aBB.Add(aC, aItLS.Value());
    }

    MakeTypedContainers(aC, aResult);
  }
  myShape = aResult;
}

bool BOPAlgo_CellsBuilder::RemoveInternals(
  const NCollection_List<TopoDS_Shape>&                         theLS,
  NCollection_List<TopoDS_Shape>&                               theLSNew,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapKeepBnd)
{
  bool bRemoved = false;
  if (theLS.Extent() < 2)
  {
    theLSNew = theLS;
    return bRemoved;
  }

  TopAbs_ShapeEnum aType = theLS.First().ShapeType();

  if (aType == TopAbs_EDGE || aType == TopAbs_FACE)
  {

    BRep_Builder aBB;
    TopoDS_Shape aShape;

    BOPTools_AlgoTools::MakeContainer((aType == TopAbs_FACE) ? TopAbs_SHELL : TopAbs_WIRE, aShape);

    for (NCollection_List<TopoDS_Shape>::Iterator aIt(theLS); aIt.More(); aIt.Next())
    {
      const TopoDS_Shape& aS = aIt.Value();
      aBB.Add(aShape, aS);
    }

    bool bFaces, bEdges;

    bFaces = (aType == TopAbs_FACE);
    bEdges = (aType == TopAbs_EDGE);
    ShapeUpgrade_UnifySameDomain anUnify(aShape, bEdges, bFaces);
    anUnify.KeepShapes(theMapKeepBnd);
    anUnify.Build();
    const TopoDS_Shape& aSNew = anUnify.Shape();

    TopExp_Explorer aExp(aSNew, aType);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Shape& aSn = aExp.Current();
      theLSNew.Append(aSn);
    }

    if (theLSNew.IsEmpty())
    {

      if (bFaces)
        AddWarning(new BOPAlgo_AlertRemovalOfIBForFacesFailed(aShape));
      else
        AddWarning(new BOPAlgo_AlertRemovalOfIBForEdgesFailed(aShape));

      theLSNew.Assign(theLS);
      return bRemoved;
    }

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMG;
    int                                                           i, aNb;

    TopExp::MapShapes(aShape, TopAbs_VERTEX, aMG);
    TopExp::MapShapes(aShape, TopAbs_EDGE, aMG);
    TopExp::MapShapes(aShape, TopAbs_FACE, aMG);

    aNb = aMG.Extent();
    for (i = 1; i <= aNb; ++i)
    {
      const TopoDS_Shape&                      aSS       = aMG(i);
      const int*                               pMaterial = myShapeMaterial.Seek(aSS);
      const NCollection_List<TopoDS_Shape>&    aLSMod    = anUnify.History()->Modified(aSS);
      NCollection_List<TopoDS_Shape>::Iterator aIt(aLSMod);
      for (; aIt.More(); aIt.Next())
      {
        const TopoDS_Shape& aSU = aIt.Value();
        myMapModified.Bind(aSS, aSU);
        bRemoved = true;
        if (pMaterial && !myShapeMaterial.IsBound(aSU))
          myShapeMaterial.Bind(aSU, *pMaterial);
      }
    }
  }
  else if (aType == TopAbs_SOLID)
  {
    BRep_Builder    aBB;
    TopoDS_Compound aSolids;
    aBB.MakeCompound(aSolids);

    NCollection_List<TopoDS_Shape>::Iterator aItLS(theLS);
    for (; aItLS.More(); aItLS.Next())
    {
      const TopoDS_Shape& aSol = aItLS.Value();
      aBB.Add(aSolids, aSol);
    }

    NCollection_List<TopoDS_Shape> aLCB;
    BOPTools_AlgoTools::MakeConnexityBlocks(aSolids, TopAbs_FACE, TopAbs_SOLID, aLCB);

    NCollection_List<TopoDS_Shape>::Iterator aItLCB(aLCB);
    for (; aItLCB.More(); aItLCB.Next())
    {
      const TopoDS_Shape& aCB = aItLCB.Value();

      NCollection_IndexedDataMap<TopoDS_Shape,
                                 NCollection_List<TopoDS_Shape>,
                                 TopTools_ShapeMapHasher>
        aDMFS;

      NCollection_List<TopoDS_Shape> aLSInt;

      TopoDS_Iterator aItS(aCB);
      for (; aItS.More(); aItS.Next())
      {
        const TopoDS_Shape& aSol = aItS.Value();

        TopoDS_Iterator aItIS(aSol);
        for (; aItIS.More(); aItIS.Next())
        {
          const TopoDS_Shape& aSI = aItIS.Value();
          if (aSI.Orientation() == TopAbs_INTERNAL)
          {
            aLSInt.Append(aSI);
          }
          else
          {
            TopoDS_Iterator aItF(aSI);
            for (; aItF.More(); aItF.Next())
            {
              const TopoDS_Shape&             aF     = aItF.Value();
              NCollection_List<TopoDS_Shape>* pLSols = aDMFS.ChangeSeek(aF);
              if (!pLSols)
              {
                pLSols = &aDMFS(aDMFS.Add(aF, NCollection_List<TopoDS_Shape>()));
              }
              pLSols->Append(aSol);
            }
          }
        }
      }

      NCollection_List<TopoDS_Shape> aLFUnique;
      int                            i, aNb = aDMFS.Extent();
      for (i = 1; i <= aNb; ++i)
      {
        if (aDMFS(i).Extent() == 1)
        {
          aLFUnique.Append(aDMFS.FindKey(i));
        }
      }

      if (aNb == aLFUnique.Extent())
      {

        aItS.Initialize(aCB);
        for (; aItS.More(); aItS.Next())
        {
          theLSNew.Append(aItS.Value());
        }
        continue;
      }

      BOPAlgo_BuilderSolid aBS;
      aBS.SetShapes(aLFUnique);
      aBS.Perform();

      if (aBS.HasErrors() || aBS.Areas().Extent() != 1)
      {

        {
          TopoDS_Compound aUniqeFaces;
          aBB.MakeCompound(aUniqeFaces);
          NCollection_List<TopoDS_Shape>::Iterator aItLFUniqe(aLFUnique);
          for (; aItLFUniqe.More(); aItLFUniqe.Next())
          {
            aBB.Add(aUniqeFaces, aItLFUniqe.Value());
          }

          AddWarning(new BOPAlgo_AlertRemovalOfIBForSolidsFailed(aUniqeFaces));
        }

        aItS.Initialize(aCB);
        for (; aItS.More(); aItS.Next())
        {
          theLSNew.Append(aItS.Value());
        }
        continue;
      }

      myReport->Merge(aBS.GetReport());

      TopoDS_Solid& aSNew = *(TopoDS_Solid*)&aBS.Areas().First();

      aSNew.Free(true);
      NCollection_List<TopoDS_Shape>::Iterator aItLSI(aLSInt);
      for (; aItLSI.More(); aItLSI.Next())
      {
        aBB.Add(aSNew, aItLSI.Value());
      }
      aSNew.Free(false);

      theLSNew.Append(aSNew);
      bRemoved = true;

      aItS.Initialize(aCB);
      for (; aItS.More(); aItS.Next())
        myMapModified.Bind(aItS.Value(), aSNew);
    }
  }
  return bRemoved;
}

const NCollection_List<TopoDS_Shape>* BOPAlgo_CellsBuilder::LocModified(const TopoDS_Shape& theS)
{

  const NCollection_List<TopoDS_Shape>* pLSp = BOPAlgo_Builder::LocModified(theS);
  if (myMapModified.IsEmpty())

    return pLSp;

  myHistShapes.Clear();

  if (!pLSp)
  {

    const TopoDS_Shape* pSU = myMapModified.Seek(theS);
    if (!pSU)
      return nullptr;

    myHistShapes.Append(*pSU);
  }
  else
  {
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;

    NCollection_List<TopoDS_Shape>::Iterator aIt(*pLSp);
    for (; aIt.More(); aIt.Next())
    {
      const TopoDS_Shape* pSp = &aIt.Value();
      const TopoDS_Shape* pSU = myMapModified.Seek(*pSp);
      if (pSU)
        pSp = pSU;
      if (aMFence.Add(*pSp))
        myHistShapes.Append(*pSp);
    }
  }
  return &myHistShapes;
}

void MakeTypedContainers(const TopoDS_Shape& theSC, TopoDS_Shape& theResult)
{
  TopAbs_ShapeEnum aContainerType, aConnexityType, aPartType;

  aPartType = TypeToExplore(BOPTools_AlgoTools::Dimension(theSC));
  switch (aPartType)
  {
    case TopAbs_EDGE:
    {
      aContainerType = TopAbs_WIRE;
      aConnexityType = TopAbs_VERTEX;
      break;
    }
    case TopAbs_FACE:
    {
      aContainerType = TopAbs_SHELL;
      aConnexityType = TopAbs_EDGE;
      break;
    }
    case TopAbs_SOLID:
    {
      aContainerType = TopAbs_COMPSOLID;
      aConnexityType = TopAbs_FACE;
      break;
    }
    default:
      return;
  }

  NCollection_List<TopoDS_Shape> aLCB;
  BOPTools_AlgoTools::MakeConnexityBlocks(theSC, aConnexityType, aPartType, aLCB);
  if (aLCB.IsEmpty())
  {
    return;
  }

  BRep_Builder                             aBB;
  TopExp_Explorer                          aExp;
  NCollection_List<TopoDS_Shape>::Iterator aItCB;

  aItCB.Initialize(aLCB);
  for (; aItCB.More(); aItCB.Next())
  {
    TopoDS_Shape aRCB;
    BOPTools_AlgoTools::MakeContainer(aContainerType, aRCB);

    const TopoDS_Shape& aCB = aItCB.Value();
    aExp.Init(aCB, aPartType);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Shape& aCBS = aExp.Current();
      aBB.Add(aRCB, aCBS);
    }

    if (aContainerType == TopAbs_SHELL)
    {
      BOPTools_AlgoTools::OrientFacesOnShell(aRCB);
    }

    aBB.Add(theResult, aRCB);
  }
}

static void CollectMaterialBoundaries(
  const NCollection_List<TopoDS_Shape>&                   theLS,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapKeepBnd)
{
  TopAbs_ShapeEnum aType      = theLS.First().ShapeType();
  TopAbs_ShapeEnum aTypeSubsh = (aType == TopAbs_FACE ? TopAbs_EDGE : TopAbs_VERTEX);
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                           aMapSubSh;
  NCollection_List<TopoDS_Shape>::Iterator anIt(theLS);
  for (; anIt.More(); anIt.Next())
  {
    const TopoDS_Shape& aS = anIt.Value();
    TopExp::MapShapesAndAncestors(aS, aTypeSubsh, aType, aMapSubSh);
  }
  for (int i = 1; i <= aMapSubSh.Extent(); i++)
  {

    if (aMapSubSh(i).Extent() == 1)
    {

      theMapKeepBnd.Add(aMapSubSh.FindKey(i));
    }
  }
}

TopAbs_ShapeEnum TypeToExplore(const int theDim)
{
  TopAbs_ShapeEnum aRet;

  switch (theDim)
  {
    case 0:
      aRet = TopAbs_VERTEX;
      break;
    case 1:
      aRet = TopAbs_EDGE;
      break;
    case 2:
      aRet = TopAbs_FACE;
      break;
    case 3:
      aRet = TopAbs_SOLID;
      break;
    default:
      aRet = TopAbs_SHAPE;
      break;
  }
  return aRet;
}
