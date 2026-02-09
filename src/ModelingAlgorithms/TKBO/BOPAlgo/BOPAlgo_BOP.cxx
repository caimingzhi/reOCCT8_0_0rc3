#include <BOPAlgo_BOP.hpp>
#include <BOPAlgo_BuilderSolid.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Tools.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPDS_DS.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_AlgoTools3D.hpp>
#include <BOPTools_Set.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Shape.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <NCollection_DataMap.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>

static TopAbs_ShapeEnum TypeToExplore(const int theDim);

static void CollectContainers(const TopoDS_Shape& theS, NCollection_List<TopoDS_Shape>& theLSC);

static void RemoveDuplicates(NCollection_List<TopoDS_Shape>& theContainers);

static void RemoveDuplicates(NCollection_List<TopoDS_Shape>& theContainers,
                             const TopAbs_ShapeEnum          theType);

static int NbCommonItemsInMap(const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theM1,
                              const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theM2);

static void MapFacesToBuildSolids(
  const TopoDS_Shape& theSol,
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    theMFS);

BOPAlgo_BOP::BOPAlgo_BOP()

{
  Clear();
}

BOPAlgo_BOP::BOPAlgo_BOP(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_ToolsProvider(theAllocator)
{
  Clear();
}

BOPAlgo_BOP::~BOPAlgo_BOP() = default;

void BOPAlgo_BOP::Clear()
{
  myOperation = BOPAlgo_UNKNOWN;
  myDims[0]   = -1;
  myDims[1]   = -1;

  BOPAlgo_ToolsProvider::Clear();
}

void BOPAlgo_BOP::SetOperation(const BOPAlgo_Operation theOperation)
{
  myOperation = theOperation;
}

BOPAlgo_Operation BOPAlgo_BOP::Operation() const
{
  return myOperation;
}

void BOPAlgo_BOP::CheckData()
{
  int                                      i, j, aNbArgs, aNbTools;
  bool                                     bFuse;
  NCollection_List<TopoDS_Shape>::Iterator aItLS;

  if (myOperation != BOPAlgo_COMMON && myOperation != BOPAlgo_FUSE && myOperation != BOPAlgo_CUT
      && myOperation != BOPAlgo_CUT21)
  {

    AddError(new BOPAlgo_AlertBOPNotSet);
    return;
  }

  aNbArgs = myArguments.Extent();
  if (!aNbArgs)
  {

    AddError(new BOPAlgo_AlertTooFewArguments);
    return;
  }

  aNbTools = myTools.Extent();
  if (!aNbTools)
  {

    AddError(new BOPAlgo_AlertTooFewArguments);
    return;
  }

  CheckFiller();
  if (HasErrors())
  {
    return;
  }

  bFuse = (myOperation == BOPAlgo_FUSE);

  int  iDimMin[2] = {3, 3}, iDimMax[2] = {0, 0};
  bool bHasValid[2] = {false, false};

  for (i = 0; i < 2; ++i)
  {
    const NCollection_List<TopoDS_Shape>& aLS = (!i) ? myArguments : myTools;
    aItLS.Initialize(aLS);
    for (j = 0; aItLS.More(); aItLS.Next(), ++j)
    {
      const TopoDS_Shape& aS       = aItLS.Value();
      bool                bIsEmpty = BOPTools_AlgoTools3D::IsEmptyShape(aS);
      if (bIsEmpty)
      {
        AddWarning(new BOPAlgo_AlertEmptyShape(aS));
        continue;
      }

      int iDMin, iDMax;
      BOPTools_AlgoTools::Dimensions(aS, iDMin, iDMax);

      if (iDMin < iDimMin[i])
        iDimMin[i] = iDMin;
      if (iDMax > iDimMax[i])
        iDimMax[i] = iDMax;

      if (bFuse && (iDimMin[i] != iDimMax[i]))
      {

        AddError(new BOPAlgo_AlertBOPNotAllowed);
        return;
      }
      bHasValid[i] = true;
    }
  }

  if (bHasValid[0] && bHasValid[1])
  {
    if (((myOperation == BOPAlgo_FUSE) && (iDimMax[0] != iDimMax[1]))
        || ((myOperation == BOPAlgo_CUT) && (iDimMax[0] > iDimMin[1]))
        || ((myOperation == BOPAlgo_CUT21) && (iDimMin[0] < iDimMax[1])))
    {

      AddError(new BOPAlgo_AlertBOPNotAllowed);
      return;
    }
  }

  if (bHasValid[0] || bHasValid[1])
  {

    myDims[0] = bHasValid[0] ? iDimMin[0] : iDimMin[1];
    myDims[1] = bHasValid[1] ? iDimMin[1] : iDimMin[0];
  }
}

bool BOPAlgo_BOP::TreatEmptyShape()
{
  if (!GetReport()->HasAlert(STANDARD_TYPE(BOPAlgo_AlertEmptyShape)))
  {
    return false;
  }

  NCollection_List<TopoDS_Shape>           aLValidObjs;
  NCollection_List<TopoDS_Shape>::Iterator aItLS(myArguments);
  for (; aItLS.More(); aItLS.Next())
  {
    if (!BOPTools_AlgoTools3D::IsEmptyShape(aItLS.Value()))
    {
      aLValidObjs.Append(aItLS.Value());
    }
  }

  NCollection_List<TopoDS_Shape> aLValidTools;
  aItLS.Initialize(myTools);
  for (; aItLS.More(); aItLS.Next())
  {
    if (!BOPTools_AlgoTools3D::IsEmptyShape(aItLS.Value()))
    {
      aLValidTools.Append(aItLS.Value());
    }
  }

  bool bHasValidObj  = (aLValidObjs.Extent() > 0);
  bool bHasValidTool = (aLValidTools.Extent() > 0);

  if (bHasValidObj && bHasValidTool)
  {

    return false;
  }

  if (!bHasValidObj && !bHasValidTool)
  {

    return true;
  }

  NCollection_List<TopoDS_Shape>* pLResult = nullptr;

  switch (myOperation)
  {
    case BOPAlgo_FUSE:
    {
      if (aLValidObjs.Extent() + aLValidTools.Extent() > 1)

        return false;

      pLResult = bHasValidObj ? &aLValidObjs : &aLValidTools;
      break;
    }
    case BOPAlgo_CUT:
    {
      if (aLValidObjs.Extent() > 1)

        return false;

      pLResult = &aLValidObjs;
      break;
    }
    case BOPAlgo_CUT21:
    {
      if (aLValidTools.Extent() > 1)

        return false;

      pLResult = &aLValidTools;
      break;
    }
    case BOPAlgo_COMMON:

      break;
    default:
      break;
  }

  if (pLResult)
  {
    aItLS.Initialize(*pLResult);
    for (; aItLS.More(); aItLS.Next())
    {
      BRep_Builder().Add(myShape, aItLS.Value());
    }
  }
  return true;
}

void BOPAlgo_BOP::BuildResult(const TopAbs_ShapeEnum theType)
{
  TopAbs_ShapeEnum                                       aType;
  BRep_Builder                                           aBB;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aM;
  NCollection_List<TopoDS_Shape>::Iterator               aIt, aItIm;

  const NCollection_List<TopoDS_Shape>& aLA = myDS->Arguments();
  aIt.Initialize(aLA);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aS = aIt.Value();
    aType                  = aS.ShapeType();
    if (aType == theType)
    {
      if (myImages.IsBound(aS))
      {
        const NCollection_List<TopoDS_Shape>& aLSIm = myImages.Find(aS);
        aItIm.Initialize(aLSIm);
        for (; aItIm.More(); aItIm.Next())
        {
          const TopoDS_Shape& aSIm = aItIm.Value();
          if (aM.Add(aSIm))
          {
            aBB.Add(myShape, aSIm);
          }
        }
      }
      else
      {
        if (aM.Add(aS))
        {
          aBB.Add(myShape, aS);
        }
      }
    }
  }
}

void BOPAlgo_BOP::Perform(const Message_ProgressRange& theRange)
{
  occ::handle<NCollection_BaseAllocator>   aAllocator;
  BOPAlgo_PaveFiller*                      pPF;
  NCollection_List<TopoDS_Shape>::Iterator aItLS;

  GetReport()->Clear();

  if (myEntryPoint == 1)
  {
    if (myPaveFiller)
    {
      delete myPaveFiller;
      myPaveFiller = nullptr;
    }
  }

  aAllocator = NCollection_BaseAllocator::CommonBaseAllocator();
  NCollection_List<TopoDS_Shape> aLS(aAllocator);

  aItLS.Initialize(myArguments);
  for (; aItLS.More(); aItLS.Next())
  {
    const TopoDS_Shape& aS = aItLS.Value();
    aLS.Append(aS);
  }

  aItLS.Initialize(myTools);
  for (; aItLS.More(); aItLS.Next())
  {
    const TopoDS_Shape& aS = aItLS.Value();
    aLS.Append(aS);
  }

  pPF = new BOPAlgo_PaveFiller(aAllocator);
  pPF->SetArguments(aLS);
  pPF->SetRunParallel(myRunParallel);
  Message_ProgressScope aPS(theRange, "Performing Boolean operation", 10);

  pPF->SetFuzzyValue(myFuzzyValue);
  pPF->SetNonDestructive(myNonDestructive);
  pPF->SetGlue(myGlue);
  pPF->SetUseOBB(myUseOBB);

  pPF->Perform(aPS.Next(9));

  myEntryPoint = 1;
  PerformInternal(*pPF, aPS.Next());
}

void BOPAlgo_BOP::fillPIConstants(const double theWhole, BOPAlgo_PISteps& theSteps) const
{
  BOPAlgo_Builder::fillPIConstants(theWhole, theSteps);
  theSteps.SetStep(PIOperation_BuildShape,
                   (myOperation == BOPAlgo_FUSE ? 10. : 5.) * theWhole / 100.);
}

void BOPAlgo_BOP::PerformInternal1(const BOPAlgo_PaveFiller&    theFiller,
                                   const Message_ProgressRange& theRange)
{
  myPaveFiller     = (BOPAlgo_PaveFiller*)&theFiller;
  myDS             = myPaveFiller->PDS();
  myContext        = myPaveFiller->Context();
  myFuzzyValue     = myPaveFiller->FuzzyValue();
  myNonDestructive = myPaveFiller->NonDestructive();

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

  if (GetReport()->HasAlert(STANDARD_TYPE(BOPAlgo_AlertEmptyShape)))
  {
    bool bDone = TreatEmptyShape();
    if (bDone)
    {
      PrepareHistory(theRange);
      return;
    }
  }
  Message_ProgressScope aPS(theRange, "Building the result of Boolean operation", 100);

  BOPAlgo_PISteps aSteps(PIOperation_Last);
  analyzeProgress(100, aSteps);

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

  FillImagesContainers(TopAbs_WIRE, aPS.Next(aSteps.GetStep(PIOperation_TreatWires)));
  if (HasErrors())
  {
    return;
  }

  BuildResult(TopAbs_WIRE);
  if (HasErrors())
  {
    return;
  }

  FillImagesFaces(aPS.Next(aSteps.GetStep(PIOperation_TreatFaces)));
  if (HasErrors())
  {
    return;
  }

  BuildResult(TopAbs_FACE);
  if (HasErrors())
  {
    return;
  }

  FillImagesContainers(TopAbs_SHELL, aPS.Next(aSteps.GetStep(PIOperation_TreatShells)));
  if (HasErrors())
  {
    return;
  }

  BuildResult(TopAbs_SHELL);
  if (HasErrors())
  {
    return;
  }

  FillImagesSolids(aPS.Next(aSteps.GetStep(PIOperation_TreatSolids)));
  if (HasErrors())
  {
    return;
  }

  BuildResult(TopAbs_SOLID);
  if (HasErrors())
  {
    return;
  }

  FillImagesContainers(TopAbs_COMPSOLID, aPS.Next(aSteps.GetStep(PIOperation_TreatCompsolids)));
  if (HasErrors())
  {
    return;
  }

  BuildResult(TopAbs_COMPSOLID);
  if (HasErrors())
  {
    return;
  }

  FillImagesCompounds(aPS.Next(aSteps.GetStep(PIOperation_TreatCompounds)));
  if (HasErrors())
  {
    return;
  }

  BuildResult(TopAbs_COMPOUND);
  if (HasErrors())
  {
    return;
  }

  BuildShape(aPS.Next(aSteps.GetStep(PIOperation_BuildShape)));
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

void BOPAlgo_BOP::BuildRC(const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, nullptr, 1);

  TopAbs_ShapeEnum aType;
  TopoDS_Compound  aC;
  BRep_Builder     aBB;

  aBB.MakeCompound(aC);

  if (myOperation == BOPAlgo_FUSE)
  {
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;
    aType = TypeToExplore(myDims[0]);
    TopExp_Explorer aExp(myShape, aType);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Shape& aS = aExp.Current();
      if (aMFence.Add(aS))
      {
        aBB.Add(aC, aS);
      }
    }
    myRC = aC;
    return;
  }

  if (UserBreak(aPS))
  {
    return;
  }

  int                                      i, j, aNb, iDim;
  bool                                     bCheckEdges, bContains, bCut21, bCommon;
  NCollection_List<TopoDS_Shape>::Iterator aItLS;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMArgs, aMTools;
  for (i = 0; i < 2; ++i)
  {
    const NCollection_List<TopoDS_Shape>&                          aLS = !i ? myArguments : myTools;
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMS = !i ? aMArgs : aMTools;
    aItLS.Initialize(aLS);
    for (; aItLS.More(); aItLS.Next())
    {
      const TopoDS_Shape&            aS = aItLS.Value();
      NCollection_List<TopoDS_Shape> aList;
      BOPTools_AlgoTools::TreatCompound(aS, aList);
      for (NCollection_List<TopoDS_Shape>::Iterator itList(aList); itList.More(); itList.Next())
      {
        const TopoDS_Shape& aSS = itList.Value();
        iDim                    = BOPTools_AlgoTools::Dimension(aSS);
        if (iDim < 0)
          continue;
        aType = TypeToExplore(iDim);
        TopExp::MapShapes(aSS, aType, aMS);
      }
    }
  }

  if (UserBreak(aPS))
  {
    return;
  }

  bCheckEdges = false;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMArgsIm, aMToolsIm;
  NCollection_IndexedDataMap<BOPTools_Set, TopoDS_Shape>        aMSetArgs, aMSetTools;

  for (i = 0; i < 2; ++i)
  {
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMS =
      !i ? aMArgs : aMTools;
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMSIm =
      !i ? aMArgsIm : aMToolsIm;
    NCollection_IndexedDataMap<BOPTools_Set, TopoDS_Shape>& aMSet = !i ? aMSetArgs : aMSetTools;

    aNb = aMS.Extent();
    for (j = 1; j <= aNb; ++j)
    {
      const TopoDS_Shape& aS = aMS(j);
      aType                  = aS.ShapeType();
      if (aType == TopAbs_EDGE)
      {
        const TopoDS_Edge& aE = *(TopoDS_Edge*)&aS;
        bCheckEdges           = true;
        if (BRep_Tool::Degenerated(aE))
        {
          continue;
        }
      }

      if (myImages.IsBound(aS))
      {
        const NCollection_List<TopoDS_Shape>& aLSIm = myImages.Find(aS);
        aItLS.Initialize(aLSIm);
        for (; aItLS.More(); aItLS.Next())
        {
          const TopoDS_Shape& aSIm = aItLS.Value();
          aMSIm.Add(aSIm);
        }
      }
      else
      {
        aMSIm.Add(aS);
        if (aS.ShapeType() == TopAbs_SOLID)
        {
          BOPTools_Set aST;
          aST.Add(aS, TopAbs_FACE);
          if (!aMSet.Contains(aST))
          {
            aMSet.Add(aST, aS);
          }
        }
      }
    }
  }

  int iDimMin, iDimMax;

  iDimMin = std::min(myDims[0], myDims[1]);
  bCommon = (myOperation == BOPAlgo_COMMON);
  bCut21  = (myOperation == BOPAlgo_CUT21);

  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMIt =
    bCut21 ? aMToolsIm : aMArgsIm;
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMCheck =
    bCut21 ? aMArgsIm : aMToolsIm;
  const NCollection_IndexedDataMap<BOPTools_Set, TopoDS_Shape>& aMSetCheck =
    bCut21 ? aMSetArgs : aMSetTools;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMCheckExp, aMItExp;

  if (bCommon)
  {
    aNb = aMIt.Extent();
    for (i = 1; i <= aNb; ++i)
    {
      const TopoDS_Shape& aS = aMIt(i);
      iDimMax                = BOPTools_AlgoTools::Dimension(aS);
      for (iDim = iDimMin; iDim < iDimMax; ++iDim)
      {
        aType = TypeToExplore(iDim);
        TopExp::MapShapes(aS, aType, aMItExp);
      }
      aMItExp.Add(aS);
    }
  }
  else
  {
    aMItExp = aMIt;
  }

  aNb = aMCheck.Extent();
  for (i = 1; i <= aNb; ++i)
  {
    const TopoDS_Shape& aS = aMCheck(i);
    iDimMax                = BOPTools_AlgoTools::Dimension(aS);
    for (iDim = iDimMin; iDim < iDimMax; ++iDim)
    {
      aType = TypeToExplore(iDim);
      TopExp::MapShapes(aS, aType, aMCheckExp);
    }
    aMCheckExp.Add(aS);
  }

  aNb = aMItExp.Extent();
  for (i = 1; i <= aNb; ++i)
  {
    const TopoDS_Shape& aS = aMItExp(i);

    bContains = aMCheckExp.Contains(aS);
    if (!bContains && aS.ShapeType() == TopAbs_SOLID)
    {
      BOPTools_Set aST;
      aST.Add(aS, TopAbs_FACE);
      bContains = aMSetCheck.Contains(aST);
    }

    if (bCommon)
    {
      if (bContains)
      {
        aBB.Add(aC, aS);
      }
    }
    else
    {
      if (!bContains)
      {
        aBB.Add(aC, aS);
      }
    }
  }

  if (bCommon)
  {
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;
    TopExp_Explorer                                        aExp;
    TopoDS_Compound                                        aCx;
    aBB.MakeCompound(aCx);

    for (iDim = 3; iDim >= iDimMin; --iDim)
    {
      aType = TypeToExplore(iDim);
      aExp.Init(aC, aType);
      for (; aExp.More(); aExp.Next())
      {
        const TopoDS_Shape& aS = aExp.Current();
        if (aMFence.Add(aS))
        {
          aBB.Add(aCx, aS);
          TopExp::MapShapes(aS, aMFence);
        }
      }
    }
    aC = aCx;
  }

  if (!bCheckEdges)
  {
    myRC = aC;
    return;
  }

  if (UserBreak(aPS))
  {
    return;
  }

  int                                                           nVD;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMVC;

  TopExp::MapShapes(aC, TopAbs_VERTEX, aMVC);

  aNb = myDS->NbSourceShapes();
  for (i = 0; i < aNb; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    aType                      = aSI.ShapeType();
    if (aType != TopAbs_EDGE)
    {
      continue;
    }

    const TopoDS_Edge& aE = *((TopoDS_Edge*)&aSI.Shape());
    if (!BRep_Tool::Degenerated(aE))
    {
      continue;
    }

    nVD                     = aSI.SubShapes().First();
    const TopoDS_Shape& aVD = myDS->Shape(nVD);

    if (!aMVC.Contains(aVD))
    {
      continue;
    }

    if (myDS->IsNewShape(nVD))
    {
      continue;
    }

    if (myDS->HasInterf(nVD))
    {
      continue;
    }

    aBB.Add(aC, aE);
  }

  myRC = aC;
}

void BOPAlgo_BOP::BuildShape(const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, nullptr, 10.);

  if (myDims[0] == 3 && myDims[1] == 3)
  {

    bool hasNotClosedSolids = CheckArgsForOpenSolid();
    if (hasNotClosedSolids)
    {
      occ::handle<Message_Report> aReport = new Message_Report();
      BuildBOP(myArguments, myTools, myOperation, Message_ProgressRange(), aReport);
      if (aReport->GetAlerts(Message_Fail).IsEmpty())
      {

        myReport->Merge(aReport);
        return;
      }
    }
  }

  BuildRC(aPS.Next(2.));

  if ((myOperation == BOPAlgo_FUSE) && (myDims[0] == 3))
  {
    BuildSolid(aPS.Next(8.));
    return;
  }

  if (UserBreak(aPS))
  {
    return;
  }

  int                                      i;
  TopAbs_ShapeEnum                         aType, aT1, aT2;
  NCollection_List<TopoDS_Shape>           aLSC, aLCB;
  NCollection_List<TopoDS_Shape>::Iterator aItLS, aItLSIm, aItLCB;
  TopoDS_Iterator                          aIt;
  BRep_Builder                             aBB;
  TopoDS_Shape                             aRC, aRCB;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMSRC;
  TopExp::MapShapes(myRC, aMSRC);

  for (i = 0; i < 2; ++i)
  {
    const NCollection_List<TopoDS_Shape>& aLS = !i ? myArguments : myTools;

    aItLS.Initialize(aLS);
    for (; aItLS.More(); aItLS.Next())
    {
      const TopoDS_Shape& aS = aItLS.Value();

      CollectContainers(aS, aLSC);
    }
  }

  if (UserBreak(aPS))
  {
    return;
  }

  NCollection_List<TopoDS_Shape>                         aLCRes;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMInpFence;
  aItLS.Initialize(aLSC);
  for (; aItLS.More(); aItLS.Next())
  {
    const TopoDS_Shape& aSC = aItLS.Value();
    aMInpFence.Add(aSC);

    BOPTools_AlgoTools::MakeContainer(TopAbs_COMPOUND, aRC);

    aIt.Initialize(aSC);
    for (; aIt.More(); aIt.Next())
    {
      const TopoDS_Shape& aS = aIt.Value();
      if (myImages.IsBound(aS))
      {
        const NCollection_List<TopoDS_Shape>& aLSIm = myImages.Find(aS);

        aItLSIm.Initialize(aLSIm);
        for (; aItLSIm.More(); aItLSIm.Next())
        {
          const TopoDS_Shape& aSIm = aItLSIm.Value();
          if (aMSRC.Contains(aSIm))
          {
            aBB.Add(aRC, aSIm);
          }
        }
      }
      else if (aMSRC.Contains(aS))
      {
        aBB.Add(aRC, aS);
      }
    }

    aType = aSC.ShapeType();
    switch (aType)
    {
      case TopAbs_WIRE:
      {
        aT1 = TopAbs_VERTEX;
        aT2 = TopAbs_EDGE;
        break;
      }
      case TopAbs_SHELL:
      {
        aT1 = TopAbs_EDGE;
        aT2 = TopAbs_FACE;
        break;
      }
      default:
      {
        aT1 = TopAbs_FACE;
        aT2 = TopAbs_SOLID;
      }
    }

    aLCB.Clear();
    BOPTools_AlgoTools::MakeConnexityBlocks(aRC, aT1, aT2, aLCB);
    if (aLCB.IsEmpty())
    {
      continue;
    }

    aItLCB.Initialize(aLCB);
    for (; aItLCB.More(); aItLCB.Next())
    {
      BOPTools_AlgoTools::MakeContainer(aType, aRCB);

      const TopoDS_Shape& aCB = aItLCB.Value();
      aIt.Initialize(aCB);
      for (; aIt.More(); aIt.Next())
      {
        const TopoDS_Shape& aCBS = aIt.Value();
        aBB.Add(aRCB, aCBS);
      }

      if (aType == TopAbs_WIRE)
      {

        BOPTools_AlgoTools::OrientEdgesOnWire(aRCB);
      }
      else if (aType == TopAbs_SHELL)
      {
        BOPTools_AlgoTools::OrientFacesOnShell(aRCB);
      }

      aRCB.Orientation(aSC.Orientation());

      aLCRes.Append(aRCB);
    }
  }

  RemoveDuplicates(aLCRes);

  if (UserBreak(aPS))
  {
    return;
  }

  TopoDS_Compound aResult;
  aBB.MakeCompound(aResult);

  aItLS.Initialize(aLCRes);
  for (; aItLS.More(); aItLS.Next())
  {
    aBB.Add(aResult, aItLS.Value());
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMSResult;
  TopExp::MapShapes(aResult, aMSResult);

  NCollection_List<TopoDS_Shape> aLSNonCont;
  for (i = 0; i < 2; ++i)
  {
    const NCollection_List<TopoDS_Shape>& aLS = !i ? myArguments : myTools;
    aItLS.Initialize(aLS);
    for (; aItLS.More(); aItLS.Next())
    {
      const TopoDS_Shape& aS = aItLS.Value();
      BOPTools_AlgoTools::TreatCompound(aS, aLSNonCont, &aMInpFence);
    }
  }

  aItLS.Initialize(aLSNonCont);
  for (; aItLS.More(); aItLS.Next())
  {
    const TopoDS_Shape& aS = aItLS.Value();
    if (myImages.IsBound(aS))
    {
      const NCollection_List<TopoDS_Shape>& aLSIm = myImages.Find(aS);
      aItLSIm.Initialize(aLSIm);
      for (; aItLSIm.More(); aItLSIm.Next())
      {
        const TopoDS_Shape& aSIm = aItLSIm.Value();
        if (aMSRC.Contains(aSIm) && aMSResult.Add(aSIm))
          aBB.Add(aResult, aSIm);
      }
    }
    else if (aMSRC.Contains(aS) && aMSResult.Add(aS))
      aBB.Add(aResult, aS);
  }

  myShape = aResult;
}

void BOPAlgo_BOP::BuildSolid(const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, nullptr, 10.);

  NCollection_List<TopoDS_Shape> aLSC;

  NCollection_List<TopoDS_Shape>::Iterator aItLS;
  TopExp_Explorer                          aExp;
  BRep_Builder                             aBB;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMSA;

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMFS;
  for (int i = 0; i < 2; ++i)
  {
    const NCollection_List<TopoDS_Shape>& aLSA = (i) ? myArguments : myTools;
    aItLS.Initialize(aLSA);
    for (; aItLS.More(); aItLS.Next())
    {
      const TopoDS_Shape& aSA = aItLS.Value();
      aExp.Init(aSA, TopAbs_SOLID);
      for (; aExp.More(); aExp.Next())
      {
        const TopoDS_Shape& aSol = aExp.Current();
        aMSA.Add(aSol);
        TopExp::MapShapesAndAncestors(aSol, TopAbs_FACE, TopAbs_SOLID, aMFS);
      }

      CollectContainers(aSA, aLSC);
    }
  }

  if (UserBreak(aPS))
  {
    return;
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMTSols;
  int                                                    i, aNb = aMFS.Extent();
  for (i = 1; i < aNb; ++i)
  {
    const NCollection_List<TopoDS_Shape>& aLSols = aMFS(i);
    if (aLSols.Extent() > 1)
    {
      aItLS.Initialize(aLSols);
      for (; aItLS.More(); aItLS.Next())
      {
        aMTSols.Add(aItLS.Value());
      }
    }
  }

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMUSols;

  aMFS.Clear();

  TopoDS_Iterator aIt(myRC);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aSx = aIt.Value();
    if (aMSA.Contains(aSx))
    {
      if (!aMTSols.Contains(aSx))
      {
        aMUSols.Add(aSx);
        continue;
      }
    }

    MapFacesToBuildSolids(aSx, aMFS);
  }

  NCollection_IndexedDataMap<BOPTools_Set, TopoDS_Shape> aDMSTS;

  aNb = aMUSols.Extent();
  for (i = 1; i <= aNb; ++i)
  {
    const TopoDS_Shape& aSx = aMUSols(i);

    aExp.Init(aSx, TopAbs_FACE);
    for (; aExp.More(); aExp.Next())
    {
      if (aMFS.Contains(aExp.Current()))
      {
        break;
      }
    }

    if (aExp.More())
    {
      MapFacesToBuildSolids(aSx, aMFS);
    }
    else
    {
      BOPTools_Set aST;
      aST.Add(aSx, TopAbs_FACE);
      if (!aDMSTS.Contains(aST))
      {
        aDMSTS.Add(aST, aSx);
      }
    }
  }

  if (UserBreak(aPS))
  {
    return;
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMEF;

  NCollection_List<TopoDS_Shape> aSFS;
  aNb = aMFS.Extent();
  for (i = 1; i <= aNb; ++i)
  {
    const NCollection_List<TopoDS_Shape>& aLSx = aMFS(i);
    if (aLSx.Extent() == 1)
    {
      const TopoDS_Shape& aFx = aMFS.FindKey(i);
      TopExp::MapShapesAndAncestors(aFx, TopAbs_EDGE, TopAbs_FACE, aMEF);
      aSFS.Append(aFx);
    }
  }

  TopoDS_Shape aRC;
  BOPTools_AlgoTools::MakeContainer(TopAbs_COMPOUND, aRC);
  if (aSFS.Extent())
  {

    BOPAlgo_BuilderSolid aBS;
    aBS.SetContext(myContext);
    aBS.SetShapes(aSFS);
    aBS.SetAvoidInternalShapes(true);
    aBS.Perform(aPS.Next(8.));
    if (aBS.HasErrors())
    {
      AddError(new BOPAlgo_AlertSolidBuilderFailed);
      return;
    }

    myReport->Merge(aBS.GetReport());

    const NCollection_List<TopoDS_Shape>& aLSR = aBS.Areas();

    aItLS.Initialize(aLSR);
    for (; aItLS.More(); aItLS.Next())
    {
      const TopoDS_Shape& aSR = aItLS.Value();
      aBB.Add(aRC, aSR);
    }
  }

  aNb = aDMSTS.Extent();
  for (i = 1; i <= aNb; ++i)
  {
    const TopoDS_Shape& aSx = aDMSTS(i);
    aBB.Add(aRC, aSx);
  }

  if (aLSC.IsEmpty())
  {

    myShape = aRC;
    return;
  }

  TopoDS_Shape aResult;
  BOPTools_AlgoTools::MakeContainer(TopAbs_COMPOUND, aResult);

  aIt.Initialize(aRC);
  if (!aIt.More())
  {

    myShape = aRC;
    return;
  }

  const TopoDS_Shape& aSol1 = aIt.Value();
  aIt.Next();

  if (!aIt.More())
  {
    TopoDS_Shape aCS;
    BOPTools_AlgoTools::MakeContainer(TopAbs_COMPSOLID, aCS);
    aBB.Add(aCS, aSol1);

    aBB.Add(aResult, aCS);
    myShape = aResult;
    return;
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFCs;
  aItLS.Initialize(aLSC);
  for (; aItLS.More(); aItLS.Next())
  {
    const TopoDS_Shape& aCs = aItLS.Value();
    aExp.Init(aCs, TopAbs_FACE);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Shape&                   aF    = aExp.Current();
      const NCollection_List<TopoDS_Shape>* pLFIm = myImages.Seek(aF);
      if (!pLFIm)
      {
        aMFCs.Add(aF);
      }
      else
      {
        NCollection_List<TopoDS_Shape>::Iterator aItLFIm(*pLFIm);
        for (; aItLFIm.More(); aItLFIm.Next())
        {
          aMFCs.Add(aItLFIm.Value());
        }
      }
    }
  }

  if (UserBreak(aPS))
  {
    return;
  }

  NCollection_List<TopoDS_Shape> aLCBS;
  BOPTools_AlgoTools::MakeConnexityBlocks(aRC, TopAbs_FACE, TopAbs_SOLID, aLCBS);

  aItLS.Initialize(aLCBS);
  for (; aItLS.More(); aItLS.Next())
  {
    const TopoDS_Shape& aCB = aItLS.Value();

    aExp.Init(aCB, TopAbs_FACE);
    for (; aExp.More(); aExp.Next())
    {
      if (aMFCs.Contains(aExp.Current()))
      {
        break;
      }
    }

    if (!aExp.More())
    {

      for (aIt.Initialize(aCB); aIt.More(); aIt.Next())
      {
        aBB.Add(aResult, aIt.Value());
      }
      continue;
    }

    TopoDS_Shape aCS;
    BOPTools_AlgoTools::MakeContainer(TopAbs_COMPSOLID, aCS);

    aIt.Initialize(aCB);
    for (; aIt.More(); aIt.Next())
    {
      aBB.Add(aCS, aIt.Value());
    }

    aBB.Add(aResult, aCS);
  }

  myShape = aResult;
}

bool BOPAlgo_BOP::CheckArgsForOpenSolid()
{

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aFailedSolids;
  {
    const NCollection_List<occ::handle<Message_Alert>>& aList =
      myReport->GetAlerts(Message_Warning);
    for (NCollection_List<occ::handle<Message_Alert>>::Iterator aIt(aList); aIt.More(); aIt.Next())
    {
      const occ::handle<Standard_Type>& aType = aIt.Value()->DynamicType();
      if (aType != STANDARD_TYPE(BOPAlgo_AlertSolidBuilderUnusedFaces))
        continue;

      occ::handle<TopoDS_AlertWithShape> aShapeAlert =
        occ::down_cast<TopoDS_AlertWithShape>(aIt.Value());
      if (!aShapeAlert.IsNull())
      {
        const TopoDS_Shape& aWarnShape = aShapeAlert->GetShape();
        if (!aWarnShape.IsNull())
        {
          TopExp_Explorer expS(aWarnShape, TopAbs_SOLID);
          for (; expS.More(); expS.Next())
            aFailedSolids.Add(expS.Current());
        }
      }
    }
  }

  const int aNbS = myDS->NbSourceShapes();
  for (int i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_SOLID)
      continue;

    const TopoDS_Shape& aSolid = aSI.Shape();

    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>
      aMEF;

    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFInternal;

    for (TopoDS_Iterator itSh(aSolid); itSh.More(); itSh.Next())
    {
      const TopoDS_Shape& aSh = itSh.Value();
      if (aSh.ShapeType() != TopAbs_SHELL)
        continue;

      for (TopoDS_Iterator itF(aSh); itF.More(); itF.Next())
      {
        const TopoDS_Shape& aF = itF.Value();
        if (aF.Orientation() == TopAbs_INTERNAL)
        {
          const NCollection_List<TopoDS_Shape>* pLFIm = myImages.Seek(aF);
          if (pLFIm)
          {
            NCollection_List<TopoDS_Shape>::Iterator itLFIm(*pLFIm);
            for (; itLFIm.More(); itLFIm.Next())
              aMFInternal.Add(itLFIm.Value());
          }
          else
            aMFInternal.Add(aF);
        }
        else
          TopExp::MapShapesAndAncestors(aF, TopAbs_EDGE, TopAbs_FACE, aMEF);
      }
    }

    bool      isClosed = true;
    const int aNbE     = aMEF.Extent();
    for (int j = 1; j <= aNbE && isClosed; ++j)
    {
      const TopoDS_Edge& aE = TopoDS::Edge(aMEF.FindKey(j));
      if (BRep_Tool::Degenerated(aE))

        continue;

      isClosed = (aMEF(j).Extent() > 1);
      if (!isClosed)
      {
        const TopoDS_Face& aF = TopoDS::Face(aMEF(j).First());
        isClosed              = BRep_Tool::IsClosed(aE, aF);
        if (!isClosed)
        {

          TopExp_Explorer expE(aF, TopAbs_EDGE);
          for (; expE.More(); expE.Next())
          {
            if (expE.Current().IsSame(aE))
            {
              isClosed = (expE.Current().Orientation() == TopAbs_INTERNAL);
              break;
            }
          }
        }
      }
    }

    if (isClosed)
      continue;

    if (aFailedSolids.Contains(aSolid))

      return true;

    const NCollection_List<TopoDS_Shape>* pLSIm = myImages.Seek(aSolid);
    if (!pLSIm)
      continue;

    NCollection_List<TopoDS_Shape>::Iterator itLSIm(*pLSIm);
    for (; itLSIm.More(); itLSIm.Next())
    {
      const TopoDS_Shape& aSIm = itLSIm.Value();
      for (TopoDS_Iterator itSh(aSIm); itSh.More(); itSh.Next())
      {
        const TopoDS_Shape& aSh = itSh.Value();
        if (aSh.ShapeType() != TopAbs_SHELL)
          continue;

        for (TopoDS_Iterator itF(aSh); itF.More(); itF.Next())
        {
          const TopoDS_Shape& aF = itF.Value();
          if (aF.Orientation() == TopAbs_INTERNAL)
          {
            if (!aMFInternal.Contains(aF))

              return true;
          }
        }
      }
    }
  }

  return false;
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

void CollectContainers(const TopoDS_Shape& theS, NCollection_List<TopoDS_Shape>& theLSC)
{
  TopAbs_ShapeEnum aType = theS.ShapeType();
  if (aType == TopAbs_WIRE || aType == TopAbs_SHELL || aType == TopAbs_COMPSOLID)
  {
    theLSC.Append(theS);
    return;
  }

  if (aType != TopAbs_COMPOUND)
  {
    return;
  }

  TopoDS_Iterator aIt(theS);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aS = aIt.Value();
    CollectContainers(aS, theLSC);
  }
}

void RemoveDuplicates(NCollection_List<TopoDS_Shape>& theContainers)
{
  RemoveDuplicates(theContainers, TopAbs_WIRE);
  RemoveDuplicates(theContainers, TopAbs_SHELL);
  RemoveDuplicates(theContainers, TopAbs_COMPSOLID);
}

void RemoveDuplicates(NCollection_List<TopoDS_Shape>& theContainers, const TopAbs_ShapeEnum theType)
{

  NCollection_List<TopoDS_Shape>           aLC;
  NCollection_List<TopoDS_Shape>::Iterator aItLC(theContainers);
  for (; aItLC.More(); aItLC.Next())
  {
    const TopoDS_Shape& aC = aItLC.Value();
    if (aC.ShapeType() == theType)
    {
      aLC.Append(aC);
    }
  }

  if (aLC.IsEmpty())
  {
    return;
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>>
    aContents;

  aItLC.Initialize(aLC);
  for (; aItLC.More(); aItLC.Next())
  {
    const TopoDS_Shape& aC = aItLC.Value();

    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& aMC =
      aContents(aContents.Add(aC, NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>()));

    TopoDS_Iterator aIt(aC);
    for (; aIt.More(); aIt.Next())
    {
      aMC.Add(aIt.Value());
    }
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aDuplicates;

  int i, j, aNb = aContents.Extent();
  for (i = 1; i <= aNb; ++i)
  {
    const TopoDS_Shape& aCi = aContents.FindKey(i);
    if (aDuplicates.Contains(aCi))
    {
      continue;
    }
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& aMi  = aContents(i);
    int                                                           aNbi = aMi.Extent();

    for (j = i + 1; j <= aNb; ++j)
    {
      const TopoDS_Shape& aCj = aContents.FindKey(j);
      if (aDuplicates.Contains(aCj))
      {
        continue;
      }
      const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& aMj  = aContents(j);
      int                                                           aNbj = aMj.Extent();

      int aNbCommon = NbCommonItemsInMap(aMi, aMj);

      if (aNbj == aNbCommon)
      {
        aDuplicates.Add(aCj);
        continue;
      }

      if (aNbi == aNbCommon)
      {
        aDuplicates.Add(aCi);
        break;
      }
    }
  }

  if (aDuplicates.IsEmpty())
  {
    return;
  }

  aItLC.Initialize(theContainers);
  for (; aItLC.More();)
  {
    const TopoDS_Shape& aC = aItLC.Value();
    if (aDuplicates.Contains(aC))
    {
      theContainers.Remove(aItLC);
      continue;
    }
    aItLC.Next();
  }
}

int NbCommonItemsInMap(const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theM1,
                       const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theM2)
{
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>* aMap1 = &theM1;
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>* aMap2 = &theM2;

  if (theM2.Extent() < theM1.Extent())
  {
    aMap1 = &theM2;
    aMap2 = &theM1;
  }

  int iCommon = 0;
  for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aIt(*aMap1); aIt.More();
       aIt.Next())
  {
    if (aMap2->Contains(aIt.Value()))
    {
      ++iCommon;
    }
  }
  return iCommon;
}

void MapFacesToBuildSolids(
  const TopoDS_Shape& theSol,
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    theMFS)
{
  TopExp_Explorer aExp(theSol, TopAbs_FACE);
  for (; aExp.More(); aExp.Next())
  {
    const TopoDS_Shape& aF = aExp.Current();

    if (aF.Orientation() == TopAbs_INTERNAL)
    {
      continue;
    }

    NCollection_List<TopoDS_Shape>* pLSol = theMFS.ChangeSeek(aF);
    if (!pLSol)
    {
      pLSol = &theMFS(theMFS.Add(aF, NCollection_List<TopoDS_Shape>()));
      pLSol->Append(theSol);
    }
    else
    {
      const TopoDS_Shape& aF1 = theMFS.FindKey(theMFS.FindIndex(aF));
      if (aF1.Orientation() != aF.Orientation())
      {
        pLSol->Append(theSol);
      }
    }
  }
}
