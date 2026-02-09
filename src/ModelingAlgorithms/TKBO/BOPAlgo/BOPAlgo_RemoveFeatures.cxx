#include <BOPAlgo_RemoveFeatures.hpp>

#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_BOP.hpp>
#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_BuilderSolid.hpp>
#include <BOPAlgo_MakerVolume.hpp>
#include <BOPAlgo_Tools.hpp>
#include <Standard_ErrorHandler.hpp>

#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_Parallel.hpp>
#include <BOPTools_Set.hpp>

#include <Bnd_Box.hpp>

#include <BRep_Builder.hpp>

#include <BRepBndLib.hpp>

#include <BRepLib.hpp>

#include <NCollection_Vector.hpp>

#include <ShapeUpgrade_UnifySameDomain.hpp>

#include <TopAbs_ShapeEnum.hpp>

#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>

#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

static void MakeRemoved(
  const NCollection_List<TopoDS_Shape>&                                theShapes,
  BRepTools_History&                                                   theHistory,
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theKeepShapes =
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>());

static void FindInternals(const TopoDS_Shape& theS, NCollection_List<TopoDS_Shape>& theLInt);

static void RemoveInternalWires(const NCollection_List<TopoDS_Shape>& theShapes,
                                NCollection_List<TopoDS_Shape>*       theRemoved = nullptr);

static void GetOriginalFaces(
  const TopoDS_Shape&                                                  theShape,
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theSolids,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&        theFeatureFacesMap,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&           theAdjFaces,
  const occ::handle<BRepTools_History>&                                theHistory,
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&       theFacesToBeKept,
  NCollection_List<TopoDS_Shape>&                                      theInternalShapes,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&              theFacesToCheckOri,
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&       theSolidsToRebuild,
  NCollection_List<TopoDS_Shape>&                                      theSharedFaces,
  NCollection_List<TopoDS_Shape>&                                      theUnTouchedSolids);

static void FindShape(const TopoDS_Shape& theSWhat,
                      const TopoDS_Shape& theSWhere,
                      TopoDS_Shape&       theSFound);

static void GetValidSolids(
  BOPAlgo_MakerVolume&                                          theMV,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theFacesToCheckOri,
  const NCollection_List<TopoDS_Shape>&                         aSharedFaces,
  const TopoDS_Shape&                                           theOrigFaces,
  const int                                                     theNbSol,
  NCollection_List<TopoDS_Shape>&                               theLSRes,
  NCollection_List<TopoDS_Shape>&                               theRemovedShapes);

static void FindExtraShapes(
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&    theConnectionMap,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theShapesToCheckOri,
  BOPAlgo_Builder&                                              theBuilder,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&       theShapesToAvoid,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>*       theValidShapes = nullptr);

static void AvoidExtraSharedFaces(NCollection_List<TopoDS_Shape>&       theLSolids,
                                  const NCollection_List<TopoDS_Shape>& theLFSharedToAvoid,
                                  BOPAlgo_Builder&                      theBuilder,
                                  NCollection_List<TopoDS_Shape>&       theExtraFaces);

static void FillSolidsHistory(
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theSolIn,
  NCollection_List<TopoDS_Shape>&                                      theSolidsRes,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&           theAdjFaces,
  BOPAlgo_Builder&                                                     theBuilder,
  BRepTools_History&                                                   theSolidsHistory);

static void TakeModified(const TopoDS_Shape&             theS,
                         BOPAlgo_Builder&                theBuilder,
                         NCollection_List<TopoDS_Shape>& theList);

static void TakeModified(const TopoDS_Shape&                                     theS,
                         BOPAlgo_Builder&                                        theBuilder,
                         NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMap);

static void FindSolid(const TopoDS_Shape&                                        theSolIn,
                      const NCollection_List<TopoDS_Shape>&                      theSolidsRes,
                      const NCollection_IndexedDataMap<TopoDS_Shape,
                                                       NCollection_List<TopoDS_Shape>,
                                                       TopTools_ShapeMapHasher>& theAdjFaces,
                      BOPAlgo_Builder&                                           theBuilder,
                      TopoDS_Shape&                                              theSolOut);

namespace
{

  enum BOPAlgo_PIOperation
  {
    PIOperation_PrepareFeatures = 0,
    PIOperation_RemoveFeatures,
    PIOperation_UpdateHistory,
    PIOperation_SimplifyResult,

    PIOperation_Last
  };
} // namespace

void BOPAlgo_RemoveFeatures::fillPIConstants(const double theWhole, BOPAlgo_PISteps& theSteps) const
{
  theSteps.SetStep(PIOperation_PrepareFeatures, 0.05 * theWhole);
  theSteps.SetStep(PIOperation_RemoveFeatures, 0.8 * theWhole);
  theSteps.SetStep(PIOperation_UpdateHistory, 0.05 * theWhole);
  theSteps.SetStep(PIOperation_SimplifyResult, 0.1 * theWhole);
}

void BOPAlgo_RemoveFeatures::Perform(const Message_ProgressRange& theRange)
{
  try
  {
    OCC_CATCH_SIGNALS

    if (HasHistory())
      myHistory = new BRepTools_History();

    CheckData();
    if (HasErrors())
      return;
    Message_ProgressScope aPS(theRange, "Removing features", 100);
    BOPAlgo_PISteps       aSteps(PIOperation_Last);
    analyzeProgress(100., aSteps);

    PrepareFeatures(aPS.Next(aSteps.GetStep(PIOperation_PrepareFeatures)));
    if (HasErrors())
    {
      return;
    }

    RemoveFeatures(aPS.Next(aSteps.GetStep(PIOperation_RemoveFeatures)));
    if (HasErrors())
    {
      return;
    }

    UpdateHistory(aPS.Next(aSteps.GetStep(PIOperation_UpdateHistory)));
    if (HasErrors())
    {
      return;
    }

    SimplifyResult(aPS.Next(aSteps.GetStep(PIOperation_SimplifyResult)));
    if (HasErrors())
    {
      return;
    }

    PostTreat();
  }
  catch (Standard_Failure const&)
  {
    AddError(new BOPAlgo_AlertRemoveFeaturesFailed());
  }
}

void BOPAlgo_RemoveFeatures::CheckData()
{

  myShape = myInputShape;

  const TopAbs_ShapeEnum aType = myInputShape.ShapeType();

  if (aType == TopAbs_SOLID || aType == TopAbs_COMPSOLID)
    return;

  if (aType == TopAbs_COMPOUND)
  {
    NCollection_List<TopoDS_Shape>                         aShapes;
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;

    BOPTools_AlgoTools::TreatCompound(myInputShape, aShapes, &aMFence);
    if (aShapes.IsEmpty())
    {

      AddError(new BOPAlgo_AlertEmptyShape(myInputShape));
      return;
    }

    NCollection_List<TopoDS_Shape>           aSolids;
    NCollection_List<TopoDS_Shape>           anOtherShapes;
    NCollection_List<TopoDS_Shape>::Iterator aIt(aShapes);
    for (; aIt.More(); aIt.Next())
    {
      const TopoDS_Shape& aS = aIt.Value();
      if (aS.ShapeType() == TopAbs_SOLID || aS.ShapeType() == TopAbs_COMPSOLID)
        aSolids.Append(aS);
      else
        anOtherShapes.Append(aS);
    }

    if (aSolids.IsEmpty())
    {

      AddError(new BOPAlgo_AlertTooFewArguments());
    }
    else if (anOtherShapes.Extent() > 0)
    {

      for (aIt.Initialize(anOtherShapes); aIt.More(); aIt.Next())
      {
        AddWarning(new BOPAlgo_AlertUnsupportedType(aIt.Value()));
      }

      TopoDS_Compound aCS;
      BRep_Builder().MakeCompound(aCS);
      for (aIt.Initialize(aSolids); aIt.More(); aIt.Next())
        BRep_Builder().Add(aCS, aIt.Value());

      myShape = aCS;

      if (HasHistory())
      {

        MakeRemoved(anOtherShapes, *myHistory.get());
      }
    }
  }
  else
  {

    AddError(new BOPAlgo_AlertTooFewArguments());
  }
}

void BOPAlgo_RemoveFeatures::PrepareFeatures(const Message_ProgressRange& theRange)
{

  TopExp::MapShapes(myInputShape, myInputsMap);

  NCollection_List<TopoDS_Shape>           aFacesToRemove;
  NCollection_List<TopoDS_Shape>::Iterator aIt(myFacesToRemove);
  Message_ProgressScope                    aPSOuter(theRange, "Preparing features", 2);
  Message_ProgressScope                    aPS(aPSOuter.Next(),
                            "Preparing the faces to remove",
                            myFacesToRemove.Size());
  for (; aIt.More(); aIt.Next(), aPS.Next())
  {
    const TopoDS_Shape& aS = aIt.Value();
    TopExp_Explorer     anExpF(aS, TopAbs_FACE);
    for (; anExpF.More(); anExpF.Next())
    {
      if (UserBreak(aPS))
      {
        return;
      }
      const TopoDS_Shape& aF = anExpF.Current();
      if (myInputsMap.Contains(aF))
        aFacesToRemove.Append(aF);
    }
  }

  if (aFacesToRemove.IsEmpty())
  {

    AddError(new BOPAlgo_AlertNoFacesToRemove());
    return;
  }

  TopoDS_Compound aCFToRemove;
  BRep_Builder().MakeCompound(aCFToRemove);
  for (aIt.Initialize(aFacesToRemove); aIt.More(); aIt.Next())
    BRep_Builder().Add(aCFToRemove, aIt.Value());

  BOPTools_AlgoTools::MakeConnexityBlocks(aCFToRemove, TopAbs_EDGE, TopAbs_FACE, myFeatures);
}

class FillGap
{
public:
  FillGap()
      : myRunParallel(false),
        myHasAdjacentFaces(false)
  {
  }

public:
  void SetFeature(const TopoDS_Shape& theFeature) { myFeature = theFeature; }

  const TopoDS_Shape& Feature() const { return myFeature; }

  void SetEFConnectionMap(const NCollection_IndexedDataMap<TopoDS_Shape,
                                                           NCollection_List<TopoDS_Shape>,
                                                           TopTools_ShapeMapHasher>& theEFMap)
  {
    myEFMap = (NCollection_IndexedDataMap<TopoDS_Shape,
                                          NCollection_List<TopoDS_Shape>,
                                          TopTools_ShapeMapHasher>*)&theEFMap;
  }

  void SetFSConnectionMap(const NCollection_IndexedDataMap<TopoDS_Shape,
                                                           NCollection_List<TopoDS_Shape>,
                                                           TopTools_ShapeMapHasher>& theFSMap)
  {
    myFSMap = (NCollection_IndexedDataMap<TopoDS_Shape,
                                          NCollection_List<TopoDS_Shape>,
                                          TopTools_ShapeMapHasher>*)&theFSMap;
  }

  void SetRunParallel(const bool bRunParallel) { myRunParallel = bRunParallel; }

  const occ::handle<BRepTools_History>& History() { return myHistory; }

  void SetRange(const Message_ProgressRange& theRange) { myRange = theRange; }

public:
  void Perform()
  {
    OCC_CATCH_SIGNALS

    try
    {
      Message_ProgressScope aPS(myRange, nullptr, 3);

      myHistory = new BRepTools_History();

      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMFAdjacent;
      FindAdjacentFaces(aMFAdjacent, aPS.Next());
      if (!aPS.More())
      {
        return;
      }

      myHasAdjacentFaces = (aMFAdjacent.Extent() > 0);
      if (!myHasAdjacentFaces)
        return;

      NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>
        aFaceExtFaceMap;
      ExtendAdjacentFaces(aMFAdjacent, aFaceExtFaceMap, aPS.Next());
      if (!aPS.More())
      {
        return;
      }

      TrimExtendedFaces(aFaceExtFaceMap, aPS.Next());
    }
    catch (Standard_Failure const&)
    {

      myHasAdjacentFaces = true;
      myFaces.Clear();
    }
  }

public:
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& FeatureFacesMap() const
  {
    return myFeatureFacesMap;
  }

  bool HasAdjacentFaces() const { return myHasAdjacentFaces; }

  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&
    Faces() const
  {
    return myFaces;
  }

  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& Solids() const
  {
    return mySolids;
  }

private:
  void FindAdjacentFaces(
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMFAdjacent,
    const Message_ProgressRange&                                   theRange)
  {

    TopoDS_Iterator aIt(myFeature);
    for (; aIt.More(); aIt.Next())
      myFeatureFacesMap.Add(aIt.Value());
    Message_ProgressScope aPSOuter(theRange, nullptr, 2);

    aIt.Initialize(myFeature);
    Message_ProgressScope aPSF(aPSOuter.Next(), "Looking for adjacent faces", 1, true);
    for (; aIt.More(); aIt.Next(), aPSF.Next())
    {
      if (!aPSF.More())
      {
        return;
      }
      const TopoDS_Shape& aF = aIt.Value();
      TopExp_Explorer     anExpE(aF, TopAbs_EDGE);
      for (; anExpE.More(); anExpE.Next())
      {
        const TopoDS_Shape&                   aE             = anExpE.Current();
        const NCollection_List<TopoDS_Shape>* pAdjacentFaces = myEFMap->Seek(aE);
        if (pAdjacentFaces)
        {
          NCollection_List<TopoDS_Shape>::Iterator itLFA(*pAdjacentFaces);
          for (; itLFA.More(); itLFA.Next())
          {
            const TopoDS_Shape& anAF = itLFA.Value();
            if (!myFeatureFacesMap.Contains(anAF))
              theMFAdjacent.Add(anAF);
          }
        }
      }

      const NCollection_List<TopoDS_Shape>* pLS = myFSMap->Seek(aF);
      if (pLS)
      {
        NCollection_List<TopoDS_Shape>::Iterator itLS(*pLS);
        for (; itLS.More(); itLS.Next())
          mySolids.Add(itLS.Value());
      }
    }

    const int             aNbFA = theMFAdjacent.Extent();
    Message_ProgressScope aPSS(aPSOuter.Next(), "Looking for adjacent solids", aNbFA);
    for (int i = 1; i <= aNbFA; ++i, aPSS.Next())
    {
      if (!aPSS.More())
      {
        return;
      }
      TopExp_Explorer anExpEA(theMFAdjacent(i), TopAbs_EDGE);
      for (; anExpEA.More(); anExpEA.Next())
      {

        const NCollection_List<TopoDS_Shape>* pLFAA = myEFMap->Seek(anExpEA.Current());
        if (pLFAA)
        {
          NCollection_List<TopoDS_Shape>::Iterator itLFAA(*pLFAA);
          for (; itLFAA.More(); itLFAA.Next())
          {

            const NCollection_List<TopoDS_Shape>* pLS = myFSMap->Seek(itLFAA.Value());
            if (pLS)
            {
              NCollection_List<TopoDS_Shape>::Iterator itLS(*pLS);
              for (; itLS.More(); itLS.Next())
                mySolids.Add(itLS.Value());
            }
          }
        }
      }
    }
  }

  void ExtendAdjacentFaces(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMFAdjacent,
    NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                                 theFaceExtFaceMap,
    const Message_ProgressRange& theRange)
  {

    Bnd_Box aFeatureBox;
    BRepBndLib::Add(myFeature, aFeatureBox);

    const double anExtLength = sqrt(aFeatureBox.SquareExtent());

    const int             aNbFA = theMFAdjacent.Extent();
    Message_ProgressScope aPS(theRange, "Extending adjacent faces", aNbFA);
    for (int i = 1; i <= aNbFA && aPS.More(); ++i, aPS.Next())
    {
      const TopoDS_Face& aF = TopoDS::Face(theMFAdjacent(i));

      TopoDS_Face aFExt;
      BRepLib::ExtendFace(aF, anExtLength, true, true, true, true, aFExt);
      theFaceExtFaceMap.Add(aF, aFExt);
      myHistory->AddModified(aF, aFExt);
    }
  }

  void TrimExtendedFaces(
    const NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                                 theFaceExtFaceMap,
    const Message_ProgressRange& theRange)
  {

    BOPAlgo_Builder aGFInter;

    const int aNbF = theFaceExtFaceMap.Extent();
    for (int i = 1; i <= aNbF; ++i)
      aGFInter.AddArgument(theFaceExtFaceMap(i));

    aGFInter.SetRunParallel(myRunParallel);

    TopoDS_Shape          anIntResult;
    Message_ProgressScope aPSOuter(theRange, nullptr, (aGFInter.Arguments().Extent() > 1) ? 2 : 1);
    if (aGFInter.Arguments().Extent() > 1)
    {
      aGFInter.Perform(aPSOuter.Next());
      if (aGFInter.HasErrors())
        return;

      anIntResult = aGFInter.Shape();

      myHistory->Merge(aGFInter.History());
    }
    else
      anIntResult = aGFInter.Arguments().First();

    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>
      anEFExtMap;
    TopExp::MapShapesAndAncestors(anIntResult, TopAbs_EDGE, TopAbs_FACE, anEFExtMap);

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aFeatureEdgesMap;
    TopExp::MapShapes(myFeature, TopAbs_EDGE, aFeatureEdgesMap);

    Message_ProgressScope aPS(aPSOuter.Next(), "Trimming faces", aNbF);
    for (int i = 1; i <= aNbF && aPS.More(); ++i, aPS.Next())
    {
      const TopoDS_Face& aFOriginal = TopoDS::Face(theFaceExtFaceMap.FindKey(i));
      const TopoDS_Face& aFExt      = TopoDS::Face(theFaceExtFaceMap(i));
      TrimFace(aFExt, aFOriginal, aFeatureEdgesMap, anEFExtMap, aGFInter);
    }
  }

  void TrimFace(
    const TopoDS_Face&                                                   theFExt,
    const TopoDS_Face&                                                   theFOriginal,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theFeatureEdgesMap,
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>&           theEFExtMap,
    BOPAlgo_Builder&                                                     theGFInter)
  {

    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMExtEdges;
    TopExp_Explorer                                        anExpE(theFExt, TopAbs_EDGE);
    for (; anExpE.More(); anExpE.Next())
    {
      const TopoDS_Edge& aE = TopoDS::Edge(anExpE.Current());

      if (BRep_Tool::Degenerated(aE) || BRep_Tool::IsClosed(aE, theFExt))
        continue;
      NCollection_List<TopoDS_Shape> aLEIm;
      TakeModified(aE, theGFInter, aLEIm);
      NCollection_List<TopoDS_Shape>::Iterator itLEIm(aLEIm);
      for (; itLEIm.More(); itLEIm.Next())
      {
        const TopoDS_Shape& aEIm = itLEIm.Value();
        if (theEFExtMap.FindFromKey(aEIm).Extent() == 1)
          aMExtEdges.Add(aEIm);
      }
    }

    BOPAlgo_Builder aGFTrim;

    NCollection_List<TopoDS_Shape> anExtSplits;
    TakeModified(theFExt, theGFInter, anExtSplits);
    aGFTrim.SetArguments(anExtSplits);

    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMEdgesToCheckOri;
    anExpE.Init(theFOriginal, TopAbs_EDGE);
    for (; anExpE.More(); anExpE.Next())
    {
      const TopoDS_Edge& aE = TopoDS::Edge(anExpE.Current());
      if (!theFeatureEdgesMap.Contains(aE))
      {
        aGFTrim.AddArgument(aE);
        if (!BRep_Tool::Degenerated(aE) && !BRep_Tool::IsClosed(aE, theFOriginal))
        {
          if (!aMEdgesToCheckOri.Add(aE))
            aMEdgesToCheckOri.Remove(aE);
        }
      }
    }

    aGFTrim.SetGlue(BOPAlgo_GlueShift);
    aGFTrim.SetRunParallel(myRunParallel);
    aGFTrim.SetNonDestructive(true);

    aGFTrim.Perform();
    if (aGFTrim.HasErrors())
      return;

    const TopoDS_Shape& aSplits = aGFTrim.Shape();

    NCollection_List<TopoDS_Shape> aLFTrimmed;

    TopExp_Explorer anExpF(aSplits, TopAbs_FACE);
    for (; anExpF.More(); anExpF.Next())
    {
      const TopoDS_Shape& aSp = anExpF.Current();
      anExpE.Init(aSp, TopAbs_EDGE);
      for (; anExpE.More(); anExpE.Next())
      {
        if (aMExtEdges.Contains(anExpE.Current()))
          break;
      }
      if (!anExpE.More())
        aLFTrimmed.Append(aSp);
    }

    if (aLFTrimmed.Extent() > 1)
    {

      NCollection_IndexedDataMap<TopoDS_Shape,
                                 NCollection_List<TopoDS_Shape>,
                                 TopTools_ShapeMapHasher>
                                               anEFMap;
      NCollection_List<TopoDS_Shape>::Iterator itLF(aLFTrimmed);
      for (; itLF.More(); itLF.Next())
        TopExp::MapShapesAndAncestors(itLF.Value(), TopAbs_EDGE, TopAbs_FACE, anEFMap);

      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aFacesToAvoid, aValidFaces;
      FindExtraShapes(anEFMap, aMEdgesToCheckOri, aGFTrim, aFacesToAvoid, &aValidFaces);

      if (aLFTrimmed.Extent() - aFacesToAvoid.Extent() > 1)
      {

        TopoDS_Compound aCF;
        BRep_Builder().MakeCompound(aCF);
        itLF.Initialize(aLFTrimmed);
        for (; itLF.More(); itLF.Next())
        {
          if (!aFacesToAvoid.Contains(itLF.Value()))
            BRep_Builder().Add(aCF, itLF.Value());
        }

        NCollection_List<TopoDS_Shape> aLCB;
        BOPTools_AlgoTools::MakeConnexityBlocks(aCF, TopAbs_EDGE, TopAbs_FACE, aLCB);
        if (aLCB.Extent() > 1)
        {
          NCollection_List<TopoDS_Shape>::Iterator itLCB(aLCB);
          for (; itLCB.More(); itLCB.Next())
          {

            const TopoDS_Shape& aCB = itLCB.Value();
            TopoDS_Iterator     itF(aCB);
            for (; itF.More(); itF.Next())
            {
              if (aValidFaces.Contains(itF.Value()))
                break;
            }
            if (!itF.More())
            {

              for (itF.Initialize(aCB); itF.More(); itF.Next())
                aFacesToAvoid.Add(itF.Value());
            }
          }
        }
      }

      itLF.Initialize(aLFTrimmed);
      for (; itLF.More();)
      {
        if (aFacesToAvoid.Contains(itLF.Value()))
          aLFTrimmed.Remove(itLF);
        else
          itLF.Next();
      }
    }
    else if (aLFTrimmed.IsEmpty())
    {

      anExpF.ReInit();
      for (; anExpF.More(); anExpF.Next())
        aLFTrimmed.Append(anExpF.Current());
    }

    if (aLFTrimmed.Extent())
    {

      RemoveInternalWires(aLFTrimmed);

      myFaces.Add(theFOriginal, aLFTrimmed);
    }

    myHistory->Merge(aGFTrim.History());

    BRepTools_History aHistRem;

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aResMap;
    NCollection_List<TopoDS_Shape>::Iterator                      itLF(aLFTrimmed);
    for (; itLF.More(); itLF.Next())
      TopExp::MapShapes(itLF.Value(), aResMap);

    NCollection_List<TopoDS_Shape> aLSplits;
    aLSplits.Append(aSplits);

    MakeRemoved(aLSplits, aHistRem, aResMap);
    myHistory->Merge(aHistRem);
  }

private:
  bool         myRunParallel;
  TopoDS_Shape myFeature;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>*
    myEFMap;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>*
                        myFSMap;
  Message_ProgressRange myRange;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>        myFeatureFacesMap;
  bool                                                          myHasAdjacentFaces;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mySolids;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                 myFaces;
  occ::handle<BRepTools_History> myHistory;
};

typedef NCollection_Vector<FillGap> VectorOfFillGap;

void BOPAlgo_RemoveFeatures::RemoveFeatures(const Message_ProgressRange& theRange)
{

  Message_ProgressScope aPSOuter(theRange, "Removing features", 2);

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    anEFMap;
  TopExp::MapShapesAndAncestors(myInputShape, TopAbs_EDGE, TopAbs_FACE, anEFMap);

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    anFSMap;
  TopExp::MapShapesAndAncestors(myInputShape, TopAbs_FACE, TopAbs_SOLID, anFSMap);

  VectorOfFillGap aVFG;

  NCollection_List<TopoDS_Shape>::Iterator itF(myFeatures);
  for (; itF.More(); itF.Next())
  {
    const TopoDS_Shape& aFeature = itF.Value();
    FillGap&            aFG      = aVFG.Appended();
    aFG.SetFeature(aFeature);
    aFG.SetEFConnectionMap(anEFMap);
    aFG.SetFSConnectionMap(anFSMap);
    aFG.SetRunParallel(myRunParallel);
  }

  const int             aNbF = aVFG.Length();
  Message_ProgressScope aPS(aPSOuter.Next(), "Filling gaps", aNbF);
  for (int i = 0; i < aNbF; ++i)
  {
    FillGap& aFG = aVFG.ChangeValue(i);
    aFG.SetRange(aPS.Next());
  }

  BOPTools_Parallel::Perform(myRunParallel, aVFG);
  if (UserBreak(aPSOuter))
  {
    return;
  }

  if (myHistory.IsNull())
    myHistory = new BRepTools_History();

  Message_ProgressScope aPSLoop(aPSOuter.Next(), "Removing features one by one", aNbF);
  for (int i = 0; i < aNbF; ++i)
  {
    if (UserBreak(aPSLoop))
    {
      return;
    }
    FillGap& aFG = aVFG(i);

    bool isSolidsHistoryNeeded = HasHistory() || (i < (aNbF - 1));

    RemoveFeature(aFG.Feature(),
                  aFG.Solids(),
                  aFG.FeatureFacesMap(),
                  aFG.HasAdjacentFaces(),
                  aFG.Faces(),
                  aFG.History(),
                  isSolidsHistoryNeeded,
                  aPSLoop.Next());
  }
}

void BOPAlgo_RemoveFeatures::RemoveFeature(
  const TopoDS_Shape&                                                  theFeature,
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theSolids,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&        theFeatureFacesMap,
  const bool                                                           theHasAdjacentFaces,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&           theAdjFaces,
  const occ::handle<BRepTools_History>&                                theAdjFacesHistory,
  const bool                                                           theSolidsHistoryNeeded,
  const Message_ProgressRange&                                         theRange)
{
  bool      bFuseShapes = true;
  const int aNbAF       = theAdjFaces.Extent();
  if (aNbAF == 0)
  {
    if (theHasAdjacentFaces)
    {

      AddWarning(new BOPAlgo_AlertUnableToRemoveTheFeature(theFeature));
      return;
    }

    bFuseShapes = false;
  }

  Message_ProgressScope aPS(theRange, nullptr, 100);

  BRep_Builder aBB;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aFacesToBeKept;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aFacesToCheckOri;

  NCollection_List<TopoDS_Shape> anInternalShapes;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aSolidsToRebuild;

  NCollection_List<TopoDS_Shape> aSharedFaces;

  NCollection_List<TopoDS_Shape> anUnTouchedSolids;

  GetOriginalFaces(myShape,
                   theSolids,
                   theFeatureFacesMap,
                   theAdjFaces,
                   myHistory,
                   aFacesToBeKept,
                   anInternalShapes,
                   aFacesToCheckOri,
                   aSolidsToRebuild,
                   aSharedFaces,
                   anUnTouchedSolids);

  aPS.Next(3);

  TopoDS_Compound anOrigF;
  aBB.MakeCompound(anOrigF);
  int aNbFK = aFacesToBeKept.Extent();
  for (int i = 1; i <= aNbFK; ++i)
    aBB.Add(anOrigF, aFacesToBeKept(i));

  BOPAlgo_MakerVolume aMV;
  aMV.SetRunParallel(myRunParallel);
  aMV.SetAvoidInternalShapes(true);
  aMV.SetIntersect(bFuseShapes);
  aMV.SetNonDestructive(true);

  aMV.AddArgument(anOrigF);

  for (int i = 1; i <= aNbAF; ++i)
  {
    const NCollection_List<TopoDS_Shape>& aLFA = theAdjFaces(i);
    if (aLFA.Extent() == 1)
    {
      const TopoDS_Shape& aFA = aLFA.First();
      aMV.AddArgument(aFA);
      aFacesToBeKept.Add(aFA);
    }
    else
    {

      TopoDS_Compound anAdjF;
      aBB.MakeCompound(anAdjF);
      NCollection_List<TopoDS_Shape>::Iterator itLFA(aLFA);
      for (; itLFA.More(); itLFA.Next())
        aBB.Add(anAdjF, itLFA.Value());

      aMV.AddArgument(anAdjF);
      aFacesToBeKept.Add(anAdjF);
    }

    if (HasHistory())
    {

      const TopoDS_Shape& aFOr = theAdjFaces.FindKey(i);
      FindInternals(aFOr, anInternalShapes);
    }
  }

  aMV.Perform(aPS.Next(90));
  if (aMV.HasErrors())
  {

    AddWarning(new BOPAlgo_AlertUnableToRemoveTheFeature(theFeature));
    return;
  }

  const TopoDS_Shape& aSolids = aMV.Shape();
  TopExp_Explorer     anExpS(aSolids, TopAbs_SOLID);
  if (!anExpS.More())
  {

    AddWarning(new BOPAlgo_AlertUnableToRemoveTheFeature(theFeature));
    return;
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> anAdjFacesSplits;
  for (int i = 1; i <= aNbAF; ++i)
  {
    if (!aPS.More())
    {
      return;
    }
    const TopoDS_Shape&                   aF    = theAdjFaces.FindKey(i);
    const NCollection_List<TopoDS_Shape>& aLFIm = myHistory->Modified(aF);
    if (aLFIm.IsEmpty())
      anAdjFacesSplits.Add(aF);
    else
    {
      NCollection_List<TopoDS_Shape>::Iterator itLFIm(aLFIm);
      for (; itLFIm.More(); itLFIm.Next())
        anAdjFacesSplits.Add(itLFIm.Value());
    }
  }

  bool bValid = true;
  aNbFK       = aFacesToBeKept.Extent();
  for (int i = 1; i <= aNbFK && bValid; ++i)
  {

    const TopoDS_Shape& aS = aFacesToBeKept(i);
    if (anAdjFacesSplits.Contains(aS))
      continue;
    if (!aPS.More())
    {
      return;
    }
    TopExp_Explorer anExpF(aS, TopAbs_FACE);
    for (; anExpF.More(); anExpF.Next())
    {
      const TopoDS_Shape& aF = anExpF.Current();
      if (!aMV.IsDeleted(aF))
        break;
    }
    bValid = anExpF.More();
  }

  if (!bValid)
  {

    AddWarning(new BOPAlgo_AlertUnableToRemoveTheFeature(theFeature));
    return;
  }

  NCollection_List<TopoDS_Shape> aLSRes;

  NCollection_List<TopoDS_Shape> aRemovedShapes;
  GetValidSolids(aMV,
                 aFacesToCheckOri,
                 aSharedFaces,
                 anOrigF,
                 theSolids.Extent(),
                 aLSRes,
                 aRemovedShapes);

  if (aLSRes.Extent() != theSolids.Extent())
  {

    AddWarning(new BOPAlgo_AlertUnableToRemoveTheFeature(theFeature));
    return;
  }
  aPS.Next(3);

  RemoveInternalWires(aLSRes, &anInternalShapes);

  myHistory->Merge(theAdjFacesHistory);

  myHistory->Merge(aMV.History());

  if (HasHistory())
  {

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMSRes;
    NCollection_List<TopoDS_Shape>::Iterator                      itLS(aLSRes);
    for (; itLS.More(); itLS.Next())
      TopExp::MapShapes(itLS.Value(), aMSRes);

    BRepTools_History aRemHist;
    anInternalShapes.Append(aRemovedShapes);
    MakeRemoved(anInternalShapes, aRemHist, aMSRes);
    myHistory->Merge(aRemHist);
  }
  aPS.Next(3);

  if (theSolidsHistoryNeeded)
  {
    BRepTools_History aSolidsHistory;
    FillSolidsHistory(aSolidsToRebuild, aLSRes, theAdjFaces, aMV, aSolidsHistory);
    myHistory->Merge(aSolidsHistory);
  }

  TopoDS_Compound aCRes;
  aBB.MakeCompound(aCRes);

  NCollection_List<TopoDS_Shape>::Iterator itLS(aLSRes);
  for (; itLS.More(); itLS.Next())
    aBB.Add(aCRes, itLS.Value());

  itLS.Initialize(anUnTouchedSolids);
  for (; itLS.More(); itLS.Next())
    aBB.Add(aCRes, itLS.Value());

  myShape = aCRes;
}

void BOPAlgo_RemoveFeatures::UpdateHistory(const Message_ProgressRange& theRange)
{
  if (!HasHistory())
    return;

  myMapShape.Clear();
  TopExp::MapShapes(myShape, myMapShape);

  BRepTools_History aHistory;

  const int             aNbS = myInputsMap.Extent();
  Message_ProgressScope aPS(theRange, "Updating history", aNbS);
  for (int i = 1; i <= aNbS; ++i, aPS.Next())
  {
    const TopoDS_Shape& aS = myInputsMap(i);
    if (!BRepTools_History::IsSupportedType(aS))
      continue;

    if (myHistory->IsRemoved(aS))
      continue;

    if (UserBreak(aPS))
    {
      return;
    }

    const NCollection_List<TopoDS_Shape>& aLSIm = myHistory->Modified(aS);
    if (aLSIm.IsEmpty())
    {
      if (!myMapShape.Contains(aS))
        aHistory.Remove(aS);
    }

    NCollection_List<TopoDS_Shape>::Iterator itLSIm(aLSIm);
    for (; itLSIm.More(); itLSIm.Next())
    {
      if (!myMapShape.Contains(itLSIm.Value()))
        aHistory.Remove(itLSIm.Value());
    }
  }

  myHistory->Merge(aHistory);
}

void BOPAlgo_RemoveFeatures::SimplifyResult(const Message_ProgressRange& theRange)
{
  if (myShape.IsSame(myInputShape))
    return;
  Message_ProgressScope        aPSOuter(theRange, "Simplifyingthe result", 2);
  ShapeUpgrade_UnifySameDomain aSDTool;
  aSDTool.Initialize(myShape, true, true);

  aSDTool.AllowInternalEdges(false);

  if (myMapShape.IsEmpty())
    TopExp::MapShapes(myShape, myMapShape);

  const int             aNbS = myInputsMap.Extent();
  Message_ProgressScope aPS(aPSOuter.Next(), nullptr, aNbS);
  for (int i = 1; i <= aNbS; ++i, aPS.Next())
  {
    if (UserBreak(aPS))
    {
      return;
    }
    if (myMapShape.Contains(myInputsMap(i)))
      aSDTool.KeepShape(myInputsMap(i));
  }

  aSDTool.Build();
  aPSOuter.Next();
  myShape = aSDTool.Shape();
  if (HasHistory())
    myHistory->Merge(aSDTool.History());
}

void BOPAlgo_RemoveFeatures::PostTreat()
{
  const TopAbs_ShapeEnum anInputType = myInputShape.ShapeType();
  const TopAbs_ShapeEnum aResType    = myShape.ShapeType();
  if (aResType == anInputType)
    return;

  TopExp_Explorer anExpS(myShape, TopAbs_SOLID);

  if (anInputType == TopAbs_SOLID)
  {
    myShape = anExpS.Current();
    return;
  }

  TopoDS_Shape aRes;
  if (anInputType == TopAbs_COMPOUND)
    BRep_Builder().MakeCompound(TopoDS::Compound(aRes));
  else
    BRep_Builder().MakeCompSolid(TopoDS::CompSolid(aRes));

  for (; anExpS.More(); anExpS.Next())
    BRep_Builder().Add(aRes, anExpS.Current());

  myShape = aRes;
}

void MakeRemoved(const NCollection_List<TopoDS_Shape>&                                theShapes,
                 BRepTools_History&                                                   theHistory,
                 const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theKeepShapes)
{
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aShapesMap;
  NCollection_List<TopoDS_Shape>::Iterator                      it(theShapes);
  for (; it.More(); it.Next())
    TopExp::MapShapes(it.Value(), aShapesMap);

  const int aNbS = aShapesMap.Extent();
  for (int i = 1; i <= aNbS; ++i)
  {
    const TopoDS_Shape& aS = aShapesMap(i);
    if (!theKeepShapes.Contains(aS) && BRepTools_History::IsSupportedType(aS))
    {
      theHistory.Remove(aS);
    }
  }
}

void FindInternals(const TopoDS_Shape& theS, NCollection_List<TopoDS_Shape>& theLInt)
{
  TopoDS_Iterator itS(theS);
  for (; itS.More(); itS.Next())
  {
    const TopoDS_Shape& aSS = itS.Value();
    if (aSS.Orientation() == TopAbs_INTERNAL)
      theLInt.Append(aSS);
    else
    {
      TopoDS_Iterator itSS(aSS);
      for (; itSS.More(); itSS.Next())
      {
        if (itSS.Value().Orientation() == TopAbs_INTERNAL)
        {
          theLInt.Append(aSS);
          break;
        }
      }
    }
  }
}

void RemoveInternalWires(const NCollection_List<TopoDS_Shape>& theShapes,
                         NCollection_List<TopoDS_Shape>*       theRemoved)
{
  NCollection_List<TopoDS_Shape>::Iterator itLS(theShapes);
  for (; itLS.More(); itLS.Next())
  {
    const TopoDS_Shape& aShape = itLS.Value();
    TopExp_Explorer     anExpF(aShape, TopAbs_FACE);
    for (; anExpF.More(); anExpF.Next())
    {
      TopoDS_Face&                   aF = *(TopoDS_Face*)&anExpF.Current();
      NCollection_List<TopoDS_Shape> aLWToRemove;
      FindInternals(aF, aLWToRemove);
      if (aLWToRemove.Extent())
      {
        aF.Free(true);
        NCollection_List<TopoDS_Shape>::Iterator itR(aLWToRemove);
        for (; itR.More(); itR.Next())
        {
          if (theRemoved)
            theRemoved->Append(itR.Value());
          BRep_Builder().Remove(aF, itR.Value());
        }
        aF.Free(false);
      }
    }
  }
}

void GetOriginalFaces(
  const TopoDS_Shape&                                                  theShape,
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theSolids,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&        theFeatureFacesMap,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&           theAdjFaces,
  const occ::handle<BRepTools_History>&                                theHistory,
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&       theFacesToBeKept,
  NCollection_List<TopoDS_Shape>&                                      theInternalShapes,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&              theFacesToCheckOri,
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&       theSolidsToRebuild,
  NCollection_List<TopoDS_Shape>&                                      theSharedFaces,
  NCollection_List<TopoDS_Shape>&                                      theUnTouchedSolids)
{

  const int aNbSols = theSolids.Extent();
  for (int i = 1; i <= aNbSols; ++i)
  {
    const TopoDS_Shape&                   aSol  = theSolids(i);
    const NCollection_List<TopoDS_Shape>& aLFIm = theHistory->Modified(aSol);
    if (aLFIm.IsEmpty())
      theSolidsToRebuild.Add(aSol);
    else
      theSolidsToRebuild.Add(aLFIm.First());
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>           aFeatureFacesSplits;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itM(theFeatureFacesMap);
  for (; itM.More(); itM.Next())
  {
    const TopoDS_Shape&                   aF    = itM.Value();
    const NCollection_List<TopoDS_Shape>& aLFIm = theHistory->Modified(aF);
    if (aLFIm.IsEmpty())
      aFeatureFacesSplits.Add(aF);
    else
    {
      NCollection_List<TopoDS_Shape>::Iterator itLFIm(aLFIm);
      for (; itLFIm.More(); itLFIm.Next())
        aFeatureFacesSplits.Add(itLFIm.Value());
    }
  }

  TopExp_Explorer anExpS(theShape, TopAbs_SOLID);
  for (; anExpS.More(); anExpS.Next())
  {
    const TopoDS_Shape& aSol = anExpS.Current();

    if (!theSolidsToRebuild.Contains(aSol))
    {

      theUnTouchedSolids.Append(aSol);
      continue;
    }

    TopoDS_Iterator itSh(aSol);
    for (; itSh.More(); itSh.Next())
    {
      const TopoDS_Shape& aSh = itSh.Value();
      if (aSh.ShapeType() != TopAbs_SHELL)
      {
        theInternalShapes.Append(aSh);
        continue;
      }

      TopoDS_Iterator itF(aSh);
      for (; itF.More(); itF.Next())
      {
        const TopoDS_Shape& aF = itF.Value();

        if (aFeatureFacesSplits.Contains(aF))
          continue;

        if (theAdjFaces.Contains(aF))
          continue;

        if (aF.Orientation() != TopAbs_INTERNAL)
        {
          theFacesToBeKept.Add(aF);

          if (!theFacesToCheckOri.Add(aF))
          {
            theFacesToCheckOri.Remove(aF);
            theSharedFaces.Append(aF);
          }
        }
        else
          theInternalShapes.Append(aSh);
      }
    }
  }
}

void FindShape(const TopoDS_Shape& theSWhat, const TopoDS_Shape& theSWhere, TopoDS_Shape& theSFound)
{
  TopExp_Explorer anExp(theSWhere, theSWhat.ShapeType());
  for (; anExp.More(); anExp.Next())
  {
    const TopoDS_Shape& aS = anExp.Current();
    if (aS.IsSame(theSWhat))
    {
      theSFound = aS;
      break;
    }
  }
}

void GetValidSolids(
  BOPAlgo_MakerVolume&                                          theMV,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theFacesToCheckOri,
  const NCollection_List<TopoDS_Shape>&                         aSharedFaces,
  const TopoDS_Shape&                                           theOrigFaces,
  const int                                                     theNbSol,
  NCollection_List<TopoDS_Shape>&                               theLSRes,
  NCollection_List<TopoDS_Shape>&                               theRemovedShapes)
{
  TopExp_Explorer anExpS(theMV.Shape(), TopAbs_SOLID);
  for (; anExpS.More(); anExpS.Next())
    theLSRes.Append(anExpS.Current());

  if (theLSRes.Extent() > theNbSol)
  {

    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aSolidsToAvoid;
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>
      aFSMap;
    TopExp::MapShapesAndAncestors(theMV.Shape(), TopAbs_FACE, TopAbs_SOLID, aFSMap);
    FindExtraShapes(aFSMap, theFacesToCheckOri, theMV, aSolidsToAvoid);

    NCollection_List<TopoDS_Shape>::Iterator itLS(theLSRes);
    for (; itLS.More();)
    {
      if (aSolidsToAvoid.Contains(itLS.Value()))
        theLSRes.Remove(itLS);
      else
        itLS.Next();
    }
  }

  if (theLSRes.Extent() > theNbSol)
  {

    AvoidExtraSharedFaces(theLSRes, aSharedFaces, theMV, theRemovedShapes);
  }

  if (theLSRes.Extent() > theNbSol)
  {

    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> anOrigFacesRes;
    TopExp_Explorer                                        anExpF(theOrigFaces, TopAbs_FACE);
    for (; anExpF.More(); anExpF.Next())
      TakeModified(anExpF.Current(), theMV, anOrigFacesRes);

    NCollection_List<TopoDS_Shape>::Iterator itLS(theLSRes);
    for (; itLS.More();)
    {
      anExpF.Init(itLS.Value(), TopAbs_FACE);
      for (; anExpF.More(); anExpF.Next())
      {
        if (anOrigFacesRes.Contains(anExpF.Current()))
          break;
      }
      if (!anExpF.More())
      {
        theRemovedShapes.Append(itLS.Value());
        theLSRes.Remove(itLS);
      }
      else
        itLS.Next();
    }
  }
}

void FindExtraShapes(
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&    theConnectionMap,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theShapesToCheckOri,
  BOPAlgo_Builder&                                              theBuilder,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&       theShapesToAvoid,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>*       theValidShapes)
{
  occ::handle<IntTools_Context>                           aCtx = theBuilder.Context();
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>  aValidShapes;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>* pValidShapes =
    theValidShapes ? theValidShapes : &aValidShapes;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itM(theShapesToCheckOri);
  for (; itM.More(); itM.Next())
  {
    const TopoDS_Shape& aSToCheckOri = itM.Value();

    NCollection_List<TopoDS_Shape> aLSIm;
    TakeModified(aSToCheckOri, theBuilder, aLSIm);

    NCollection_List<TopoDS_Shape>::Iterator itLSIm(aLSIm);
    for (; itLSIm.More(); itLSIm.Next())
    {
      const TopoDS_Shape& aSIm = itLSIm.Value();

      const NCollection_List<TopoDS_Shape>* pShapesToValidate = theConnectionMap.Seek(aSIm);
      if (!pShapesToValidate)
        continue;

      NCollection_List<TopoDS_Shape>::Iterator itSV(*pShapesToValidate);
      for (; itSV.More(); itSV.Next())
      {
        const TopoDS_Shape& aShapeToValidate = itSV.Value();
        if (pValidShapes->Contains(aShapeToValidate))
          continue;

        TopoDS_Face aSInShape;
        FindShape(aSIm, aShapeToValidate, aSInShape);

        bool bSameOri = !BOPTools_AlgoTools::IsSplitToReverse(aSInShape, aSToCheckOri, aCtx);

        if (bSameOri)
          pValidShapes->Add(aShapeToValidate);
        else
          theShapesToAvoid.Add(aShapeToValidate);
      }
    }
  }

  itM.Initialize(*pValidShapes);
  for (; itM.More(); itM.Next())
    theShapesToAvoid.Remove(itM.Value());
}

void AvoidExtraSharedFaces(NCollection_List<TopoDS_Shape>&       theLSolids,
                           const NCollection_List<TopoDS_Shape>& theLFSharedToAvoid,
                           BOPAlgo_Builder&                      theBuilder,
                           NCollection_List<TopoDS_Shape>&       theExtraFaces)
{

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFSharedSp;
  {
    NCollection_List<TopoDS_Shape>           aLFSharedSp;
    NCollection_List<TopoDS_Shape>::Iterator itLFS(theLFSharedToAvoid);
    for (; itLFS.More(); itLFS.Next())
      TakeModified(itLFS.Value(), theBuilder, aMFSharedSp);
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                           aFSMap;
  NCollection_List<TopoDS_Shape>::Iterator itLS(theLSolids);
  for (; itLS.More(); itLS.Next())
    TopExp::MapShapesAndAncestors(itLS.Value(), TopAbs_FACE, TopAbs_SOLID, aFSMap);

  NCollection_List<TopoDS_Shape> anExtraFaces;
  NCollection_List<TopoDS_Shape> aLFArguments;
  itLS.Initialize(theLSolids);
  for (; itLS.More(); itLS.Next())
  {
    const TopoDS_Shape& aSol = itLS.Value();
    TopExp_Explorer     anExpF(aSol, TopAbs_FACE);
    for (; anExpF.More(); anExpF.Next())
    {
      const TopoDS_Shape&                   aF    = anExpF.Current();
      const NCollection_List<TopoDS_Shape>& aLSol = aFSMap.FindFromKey(aF);
      if (aLSol.Extent() != 2 || aMFSharedSp.Contains(aF))
        aLFArguments.Append(aF);
      else
        anExtraFaces.Append(aF);
    }
  }

  if (anExtraFaces.IsEmpty())
    return;

  BOPAlgo_BuilderSolid aBS;
  aBS.SetAvoidInternalShapes(true);
  aBS.SetShapes(aLFArguments);
  aBS.Perform();
  if (aBS.HasErrors())
    return;

  theLSolids = aBS.Areas();
  theExtraFaces.Append(anExtraFaces);
}

void FillSolidsHistory(
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theSolIn,
  NCollection_List<TopoDS_Shape>&                                      theSolidsOut,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&           theAdjFaces,
  BOPAlgo_Builder&                                                     theBuilder,
  BRepTools_History&                                                   theSolidsHistory)
{
  const int aNbS = theSolIn.Extent();
  for (int i = 1; i <= aNbS; ++i)
  {
    const TopoDS_Shape& aSolIn = theSolIn(i);

    TopoDS_Shape aSolOut;
    FindSolid(aSolIn, theSolidsOut, theAdjFaces, theBuilder, aSolOut);

    if (aSolOut.IsNull())
    {
      theSolidsHistory.Remove(aSolIn);
      continue;
    }

    BOPTools_Set aSTIn, aSTOut;
    aSTIn.Add(aSolIn, TopAbs_FACE);
    aSTOut.Add(aSolOut, TopAbs_FACE);
    if (aSTIn.IsEqual(aSTOut))
    {

      NCollection_List<TopoDS_Shape>::Iterator itLS(theSolidsOut);
      for (; itLS.More(); itLS.Next())
      {
        if (itLS.Value().IsSame(aSolOut))
        {
          theSolidsOut.InsertBefore(aSolIn, itLS);
          theSolidsOut.Remove(itLS);
          break;
        }
      }
    }
    else
    {
      theSolidsHistory.AddModified(aSolIn, aSolOut);
    }
  }
}

void TakeModified(const TopoDS_Shape&             theS,
                  BOPAlgo_Builder&                theBuilder,
                  NCollection_List<TopoDS_Shape>& theList)
{
  const NCollection_List<TopoDS_Shape>& aModified = theBuilder.Modified(theS);
  if (aModified.IsEmpty() && !theBuilder.IsDeleted(theS))
    theList.Append(theS);
  else
  {
    NCollection_List<TopoDS_Shape>::Iterator itM(aModified);
    for (; itM.More(); itM.Next())
      theList.Append(itM.Value());
  }
}

void TakeModified(const TopoDS_Shape&                                     theS,
                  BOPAlgo_Builder&                                        theBuilder,
                  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMap)
{
  const NCollection_List<TopoDS_Shape>& aModified = theBuilder.Modified(theS);
  if (aModified.IsEmpty() && !theBuilder.IsDeleted(theS))
    theMap.Add(theS);
  else
  {
    NCollection_List<TopoDS_Shape>::Iterator itM(aModified);
    for (; itM.More(); itM.Next())
      theMap.Add(itM.Value());
  }
}

void FindSolid(const TopoDS_Shape&                                        theSolIn,
               const NCollection_List<TopoDS_Shape>&                      theSolidsRes,
               const NCollection_IndexedDataMap<TopoDS_Shape,
                                                NCollection_List<TopoDS_Shape>,
                                                TopTools_ShapeMapHasher>& theAdjFaces,
               BOPAlgo_Builder&                                           theBuilder,
               TopoDS_Shape&                                              theSolOut)
{
  occ::handle<IntTools_Context> aCtx = theBuilder.Context();

  TopExp_Explorer anExpF(theSolIn, TopAbs_FACE);
  for (; anExpF.More(); anExpF.Next())
  {
    const TopoDS_Shape& aFS = anExpF.Current();

    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFSIm;
    const NCollection_List<TopoDS_Shape>*                  pLFA = theAdjFaces.Seek(aFS);
    if (pLFA)
    {
      NCollection_List<TopoDS_Shape>::Iterator itLFA(*pLFA);
      for (; itLFA.More(); itLFA.Next())
        TakeModified(itLFA.Value(), theBuilder, aMFSIm);
    }
    else
    {
      TakeModified(aFS, theBuilder, aMFSIm);
    }

    NCollection_List<TopoDS_Shape>::Iterator itLS(theSolidsRes);
    for (; itLS.More(); itLS.Next())
    {
      const TopoDS_Shape& aSol = itLS.Value();
      TopExp_Explorer     anExpFOut(aSol, TopAbs_FACE);
      for (; anExpFOut.More(); anExpFOut.Next())
      {
        const TopoDS_Shape& aF = anExpFOut.Current();
        if (aMFSIm.Contains(aF))
        {

          if (!BOPTools_AlgoTools::IsSplitToReverse(aF, aFS, aCtx))
          {
            theSolOut = aSol;
            return;
          }
        }
      }
    }
  }
}
