#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_BuilderSolid.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Tools.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_ShapeInfo.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BRep_Builder.hpp>
#include <IntTools_Context.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Solid.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Map.hpp>

BOPAlgo_Builder::BOPAlgo_Builder()
    : myArguments(myAllocator),
      myMapFence(100, myAllocator),
      myPaveFiller(nullptr),
      myDS(nullptr),
      myEntryPoint(0),
      myImages(100, myAllocator),
      myShapesSD(100, myAllocator),
      myOrigins(100, myAllocator),
      myInParts(100, myAllocator),
      myNonDestructive(false),
      myGlue(BOPAlgo_GlueOff),
      myCheckInverted(true)
{
}

BOPAlgo_Builder::BOPAlgo_Builder(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_BuilderShape(theAllocator),
      myArguments(myAllocator),
      myMapFence(100, myAllocator),
      myPaveFiller(nullptr),
      myDS(nullptr),
      myEntryPoint(0),
      myImages(100, myAllocator),
      myShapesSD(100, myAllocator),
      myOrigins(100, myAllocator),
      myInParts(100, myAllocator),
      myNonDestructive(false),
      myGlue(BOPAlgo_GlueOff),
      myCheckInverted(true)
{
}

BOPAlgo_Builder::~BOPAlgo_Builder()
{
  if (myEntryPoint == 1)
  {
    if (myPaveFiller)
    {
      delete myPaveFiller;
      myPaveFiller = nullptr;
    }
  }
}

void BOPAlgo_Builder::Clear()
{
  BOPAlgo_BuilderShape::Clear();
  myArguments.Clear();
  myMapFence.Clear();
  myImages.Clear();
  myShapesSD.Clear();
  myOrigins.Clear();
  myInParts.Clear();
}

void BOPAlgo_Builder::AddArgument(const TopoDS_Shape& theShape)
{
  if (myMapFence.Add(theShape))
  {
    myArguments.Append(theShape);
  }
}

void BOPAlgo_Builder::SetArguments(const NCollection_List<TopoDS_Shape>& theShapes)
{
  NCollection_List<TopoDS_Shape>::Iterator aIt;

  myArguments.Clear();

  aIt.Initialize(theShapes);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aS = aIt.Value();
    AddArgument(aS);
  }
}

void BOPAlgo_Builder::CheckData()
{
  int aNb = myArguments.Extent();
  if (aNb < 2)
  {
    AddError(new BOPAlgo_AlertTooFewArguments);
    return;
  }

  CheckFiller();
}

void BOPAlgo_Builder::CheckFiller()
{
  if (!myPaveFiller)
  {
    AddError(new BOPAlgo_AlertNoFiller);
    return;
  }
  GetReport()->Merge(myPaveFiller->GetReport());
}

void BOPAlgo_Builder::Prepare()
{
  BRep_Builder    aBB;
  TopoDS_Compound aC;

  aBB.MakeCompound(aC);
  myShape = aC;
}

void BOPAlgo_Builder::Perform(const Message_ProgressRange& theRange)
{
  GetReport()->Clear();

  if (myEntryPoint == 1)
  {
    if (myPaveFiller)
    {
      delete myPaveFiller;
      myPaveFiller = nullptr;
    }
  }

  occ::handle<NCollection_BaseAllocator> aAllocator =
    NCollection_BaseAllocator::CommonBaseAllocator();

  BOPAlgo_PaveFiller* pPF = new BOPAlgo_PaveFiller(aAllocator);

  pPF->SetArguments(myArguments);
  pPF->SetRunParallel(myRunParallel);
  Message_ProgressScope aPS(theRange, "Performing General Fuse operation", 10);
  pPF->SetFuzzyValue(myFuzzyValue);
  pPF->SetNonDestructive(myNonDestructive);
  pPF->SetGlue(myGlue);
  pPF->SetUseOBB(myUseOBB);

  pPF->Perform(aPS.Next(9));

  myEntryPoint = 1;
  PerformInternal(*pPF, aPS.Next(1));
}

void BOPAlgo_Builder::PerformWithFiller(const BOPAlgo_PaveFiller&    theFiller,
                                        const Message_ProgressRange& theRange)
{
  GetReport()->Clear();
  myEntryPoint     = 0;
  myNonDestructive = theFiller.NonDestructive();
  myFuzzyValue     = theFiller.FuzzyValue();
  myGlue           = theFiller.Glue();
  myUseOBB         = theFiller.UseOBB();
  PerformInternal(theFiller, theRange);
}

void BOPAlgo_Builder::PerformInternal(const BOPAlgo_PaveFiller&    theFiller,
                                      const Message_ProgressRange& theRange)
{
  GetReport()->Clear();

  try
  {
    OCC_CATCH_SIGNALS
    PerformInternal1(theFiller, theRange);
  }

  catch (Standard_Failure const&)
  {
    AddError(new BOPAlgo_AlertBuilderFailed);
  }
}

BOPAlgo_Builder::NbShapes BOPAlgo_Builder::getNbShapes() const
{
  NbShapes aCounter;
  aCounter.NbVertices() = myDS->ShapesSD().Size();
  for (int i = 0; i < myDS->NbSourceShapes(); ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    switch (aSI.ShapeType())
    {
      case TopAbs_EDGE:
      {
        if (myDS->HasPaveBlocks(i))
        {
          aCounter.NbEdges()++;
        }
        break;
      }
      case TopAbs_WIRE:
        aCounter.NbWires()++;
        break;
      case TopAbs_FACE:
      {
        if (myDS->HasFaceInfo(i))
        {
          aCounter.NbFaces()++;
        }
        break;
      }
      case TopAbs_SHELL:
        aCounter.NbShells()++;
        break;
      case TopAbs_SOLID:
        aCounter.NbSolids()++;
        break;
      case TopAbs_COMPSOLID:
        aCounter.NbCompsolids()++;
        break;
      case TopAbs_COMPOUND:
        aCounter.NbCompounds()++;
        break;
      default:
        break;
    }
  }
  return aCounter;
}

void BOPAlgo_Builder::fillPIConstants(const double theWhole, BOPAlgo_PISteps& theSteps) const
{

  if (myFillHistory)
  {

    theSteps.SetStep(PIOperation_FillHistory, 0.05 * theWhole);
  }

  theSteps.SetStep(PIOperation_PostTreat, 0.03 * theWhole);
}

void BOPAlgo_Builder::fillPISteps(BOPAlgo_PISteps& theSteps) const
{

  NbShapes aNbShapes = getNbShapes();

  theSteps.SetStep(PIOperation_TreatVertices, aNbShapes.NbVertices());
  theSteps.SetStep(PIOperation_TreatEdges, aNbShapes.NbEdges());
  theSteps.SetStep(PIOperation_TreatWires, aNbShapes.NbWires());
  theSteps.SetStep(PIOperation_TreatFaces, 20 * aNbShapes.NbFaces());
  theSteps.SetStep(PIOperation_TreatShells, aNbShapes.NbShells());
  theSteps.SetStep(PIOperation_TreatSolids, 50 * aNbShapes.NbSolids());
  theSteps.SetStep(PIOperation_TreatCompsolids, aNbShapes.NbCompsolids());
  theSteps.SetStep(PIOperation_TreatCompounds, aNbShapes.NbCompounds());
}

void BOPAlgo_Builder::PerformInternal1(const BOPAlgo_PaveFiller&    theFiller,
                                       const Message_ProgressRange& theRange)
{
  myPaveFiller     = (BOPAlgo_PaveFiller*)&theFiller;
  myDS             = myPaveFiller->PDS();
  myContext        = myPaveFiller->Context();
  myFuzzyValue     = myPaveFiller->FuzzyValue();
  myNonDestructive = myPaveFiller->NonDestructive();

  Message_ProgressScope aPS(theRange, "Building the result of General Fuse operation", 100);

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

  PrepareHistory(aPS.Next(aSteps.GetStep(PIOperation_FillHistory)));
  if (HasErrors())
  {
    return;
  }

  PostTreat(aPS.Next(aSteps.GetStep(PIOperation_PostTreat)));
}

void BOPAlgo_Builder::PostTreat(const Message_ProgressRange& theRange)
{
  int                                                           i, aNbS;
  TopAbs_ShapeEnum                                              aType;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMA;
  if (myPaveFiller->NonDestructive())
  {

    aNbS = myDS->NbSourceShapes();
    for (i = 0; i < aNbS; ++i)
    {
      const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
      aType                      = aSI.ShapeType();
      if (aType == TopAbs_VERTEX || aType == TopAbs_EDGE || aType == TopAbs_FACE)
      {
        const TopoDS_Shape& aS = aSI.Shape();
        aMA.Add(aS);
      }
    }
  }

  Message_ProgressScope aPS(theRange, "Post treatment of result shape", 2);
  BOPTools_AlgoTools::CorrectTolerances(myShape, aMA, 0.05, myRunParallel);
  aPS.Next();
  BOPTools_AlgoTools::CorrectShapeTolerances(myShape, aMA, myRunParallel);
}

void BOPAlgo_Builder::BuildBOP(const NCollection_List<TopoDS_Shape>& theObjects,
                               const TopAbs_State                    theObjState,
                               const NCollection_List<TopoDS_Shape>& theTools,
                               const TopAbs_State                    theToolsState,
                               const Message_ProgressRange&          theRange,
                               occ::handle<Message_Report>           theReport)
{
  if (HasErrors())
    return;

  occ::handle<Message_Report> aReport = theReport.IsNull() ? myReport : theReport;

  if (myArguments.IsEmpty() || myShape.IsNull())
  {
    aReport->AddAlert(Message_Fail, new BOPAlgo_AlertBuilderFailed());
    return;
  }

  if ((theObjState != TopAbs_IN && theObjState != TopAbs_OUT)
      || (theToolsState != TopAbs_IN && theToolsState != TopAbs_OUT))
  {
    aReport->AddAlert(Message_Fail, new BOPAlgo_AlertBOPNotSet());
    return;
  }

  bool hasObjects = !theObjects.IsEmpty();
  bool hasTools   = !theTools.IsEmpty();
  if (!hasObjects && !hasTools)
  {
    aReport->AddAlert(Message_Fail, new BOPAlgo_AlertTooFewArguments());
    return;
  }

  for (int i = 0; i < 2; ++i)
  {
    const NCollection_List<TopoDS_Shape>&    aList = !i ? theObjects : theTools;
    NCollection_List<TopoDS_Shape>::Iterator itLS(aList);
    for (; itLS.More(); itLS.Next())
    {
      const TopoDS_Shape& aS = itLS.Value();

      if (myDS->Index(aS) < 0)
      {
        aReport->AddAlert(Message_Fail, new BOPAlgo_AlertUnknownShape(aS));
        return;
      }

      if (aS.ShapeType() != TopAbs_SOLID)
      {
        NCollection_List<TopoDS_Shape>                         aLS;
        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;
        BOPTools_AlgoTools::TreatCompound(aS, aLS, &aMFence);

        NCollection_List<TopoDS_Shape>::Iterator it(aLS);
        for (; it.More(); it.Next())
        {
          const TopoDS_Shape& aSx = it.Value();
          if (aSx.ShapeType() != TopAbs_SOLID && aSx.ShapeType() != TopAbs_COMPSOLID)
          {
            aReport->AddAlert(Message_Fail, new BOPAlgo_AlertUnsupportedType(aS));
            return;
          }
        }
      }
    }
  }

  NCollection_IndexedMap<TopoDS_Shape> aMObjFacesOri, aMToolFacesOri;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMObjFaces, aMToolFaces;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> anINObjects, anINTools;

  for (int i = 0; i < 2; ++i)
  {
    const NCollection_List<TopoDS_Shape>& aList   = !i ? theObjects : theTools;
    NCollection_IndexedMap<TopoDS_Shape>& aMapOri = !i ? aMObjFacesOri : aMToolFacesOri;
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMap =
      !i ? aMObjFaces : aMToolFaces;
    NCollection_List<TopoDS_Shape>::Iterator itLS(aList);
    for (; itLS.More(); itLS.Next())
    {
      const TopoDS_Shape& aShape = itLS.Value();
      TopExp_Explorer     expS(aShape, TopAbs_SOLID);
      for (; expS.More(); expS.Next())
      {
        const TopoDS_Shape& aS = expS.Current();
        TopExp_Explorer     expF(aS, TopAbs_FACE);
        for (; expF.More(); expF.Next())
        {
          const TopoDS_Shape& aF = expF.Current();
          if (aF.Orientation() != TopAbs_FORWARD && aF.Orientation() != TopAbs_REVERSED)
            continue;
          const NCollection_List<TopoDS_Shape>* pLFIm = myImages.Seek(aF);
          if (pLFIm)
          {
            NCollection_List<TopoDS_Shape>::Iterator itLFIm(*pLFIm);
            for (; itLFIm.More(); itLFIm.Next())
            {
              TopoDS_Face aFIm = TopoDS::Face(itLFIm.Value());
              if (BOPTools_AlgoTools::IsSplitToReverse(aFIm, aF, myContext))
                aFIm.Reverse();
              aMapOri.Add(aFIm);
              aMap.Add(aFIm);
            }
          }
          else
          {
            aMapOri.Add(aF);
            aMap.Add(aF);
          }
        }

        const NCollection_List<TopoDS_Shape>* pLFIN = myInParts.Seek(aS);
        if (pLFIN)
        {
          NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& anINMap =
            !i ? anINObjects : anINTools;
          NCollection_List<TopoDS_Shape>::Iterator itLFIn(*pLFIN);
          for (; itLFIn.More(); itLFIn.Next())
            anINMap.Add(itLFIn.Value());
        }
      }
    }
  }

  bool isObjectsIN = (theObjState == TopAbs_IN), isToolsIN = (theToolsState == TopAbs_IN);

  bool bAvoidIN = (!isObjectsIN && !isToolsIN), bAvoidINforBoth = (isObjectsIN != isToolsIN);

  bool isSameOriNeeded = (theObjState == theToolsState);

  NCollection_IndexedMap<TopoDS_Shape>                   aMResFacesOri;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMResFacesFence;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence, aMFToAvoid;

  NCollection_Map<TopoDS_Shape> aMFenceOri;

  for (int i = 0; i < 2; ++i)
  {
    const NCollection_IndexedMap<TopoDS_Shape>& aMap = !i ? aMObjFacesOri : aMToolFacesOri;
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& anOppositeMap =
      !i ? aMToolFaces : aMObjFaces;
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& anINMap =
      !i ? anINObjects : anINTools;
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& anOppositeINMap =
      !i ? anINTools : anINObjects;
    const bool bTakeIN = !i ? isObjectsIN : isToolsIN;

    const int aNbF = aMap.Extent();
    for (int j = 1; j <= aNbF; ++j)
    {
      TopoDS_Shape aFIm = aMap(j);

      bool isIN         = anINMap.Contains(aFIm);
      bool isINOpposite = anOppositeINMap.Contains(aFIm);

      if (bAvoidIN && (isIN || isINOpposite))
        continue;

      if (bAvoidINforBoth && isIN && isINOpposite)
        continue;

      if (!aMFence.Add(aFIm))
      {
        if (!anOppositeMap.Contains(aFIm))
        {

          if (bTakeIN != isSameOriNeeded)
            aMFToAvoid.Add(aFIm);
        }
        else
        {

          bool isSameOri = !aMFenceOri.Add(aFIm);
          if (isSameOriNeeded == isSameOri)
          {

            if (aMResFacesFence.Add(aFIm))
              aMResFacesOri.Add(aFIm);
          }
          else

            aMFToAvoid.Add(aFIm);

          continue;
        }
      }
      if (!aMFenceOri.Add(aFIm))
        continue;

      if (bTakeIN == isINOpposite)
      {
        if (isIN)
        {
          aMResFacesOri.Add(aFIm);
          aMResFacesOri.Add(aFIm.Reversed());
        }
        else if (bTakeIN && !isSameOriNeeded)
          aMResFacesOri.Add(aFIm.Reversed());
        else
          aMResFacesOri.Add(aFIm);
        aMResFacesFence.Add(aFIm);
      }
    }
  }

  NCollection_List<TopoDS_Shape> aResFaces;
  const int                      aNbRF = aMResFacesOri.Extent();
  for (int i = 1; i <= aNbRF; ++i)
  {
    const TopoDS_Shape& aRF = aMResFacesOri(i);
    if (!aMFToAvoid.Contains(aRF))
      aResFaces.Append(aRF);
  }
  Message_ProgressScope aPS(theRange, nullptr, 2);
  BRep_Builder          aBB;

  BOPAlgo_BuilderSolid aBS;
  aBS.SetShapes(aResFaces);
  aBS.SetRunParallel(myRunParallel);
  aBS.SetContext(myContext);
  aBS.SetFuzzyValue(myFuzzyValue);
  aBS.Perform(aPS.Next());

  NCollection_List<TopoDS_Shape> aResSolids;

  aMFence.Clear();
  if (!aBS.HasErrors())
  {

    NCollection_List<TopoDS_Shape>::Iterator itA(aBS.Areas());
    for (; itA.More(); itA.Next())
    {
      const TopoDS_Shape& aSolid = itA.Value();

      TopExp_Explorer expF(aSolid, TopAbs_FACE);
      for (; expF.More(); expF.Next())
      {
        const TopoDS_Shape& aF = expF.Current();
        if (aMObjFacesOri.Contains(aF) || aMToolFacesOri.Contains(aF))
          break;
      }
      if (expF.More())
      {
        aResSolids.Append(aSolid);
        TopExp::MapShapes(aSolid, aMFence);
      }
    }
  }
  else
  {
    return;
  }

  TopoDS_Compound anUnUsedFaces;
  aBB.MakeCompound(anUnUsedFaces);

  NCollection_List<TopoDS_Shape>::Iterator itLF(aResFaces);
  for (; itLF.More(); itLF.Next())
  {
    if (aMFence.Add(itLF.Value()))
      aBB.Add(anUnUsedFaces, itLF.Value());
  }

  NCollection_List<TopoDS_Shape> aLCB;
  BOPTools_AlgoTools::MakeConnexityBlocks(anUnUsedFaces, TopAbs_EDGE, TopAbs_FACE, aLCB);

  NCollection_List<TopoDS_Shape>::Iterator itCB(aLCB);
  for (; itCB.More(); itCB.Next())
  {
    const TopoDS_Shape& aCB = itCB.Value();
    TopoDS_Shell        aShell;
    aBB.MakeShell(aShell);

    TopExp_Explorer anExpF(aCB, TopAbs_FACE);
    for (; anExpF.More(); anExpF.Next())
      aBB.Add(aShell, TopoDS::Face(anExpF.Current()));

    BOPTools_AlgoTools::OrientFacesOnShell(aShell);

    TopoDS_Solid aSolid;
    aBB.MakeSolid(aSolid);
    aBB.Add(aSolid, aShell);

    aResSolids.Append(aSolid);
  }

  if (!bAvoidIN)
  {

    NCollection_List<TopoDS_Shape> anInParts;
    for (int i = 0; i < 2; ++i)
    {
      const NCollection_List<TopoDS_Shape>&    aList = !i ? theObjects : theTools;
      NCollection_List<TopoDS_Shape>::Iterator itLS(aList);
      for (; itLS.More(); itLS.Next())
      {
        TopExp_Explorer expS(itLS.Value(), TopAbs_SOLID);
        for (; expS.More(); expS.Next())
        {
          const TopoDS_Shape& aS = expS.Current();
          for (TopoDS_Iterator it(aS); it.More(); it.Next())
          {
            const TopoDS_Shape& aSInt = it.Value();
            if (aSInt.Orientation() == TopAbs_INTERNAL)
              anInParts.Append(aSInt);
            else
            {

              TopoDS_Iterator itInt(aSInt);
              if (itInt.More() && itInt.Value().Orientation() == TopAbs_INTERNAL)
                anInParts.Append(aSInt);
            }
          }
        }
      }
    }

    BOPAlgo_Tools::FillInternals(aResSolids, anInParts, myImages, myContext);
  }

  TopoDS_Shape aResult;
  aBB.MakeCompound(TopoDS::Compound(aResult));

  NCollection_List<TopoDS_Shape>::Iterator itLS(aResSolids);
  for (; itLS.More(); itLS.Next())
    aBB.Add(aResult, itLS.Value());

  myShape = aResult;
  PrepareHistory(aPS.Next());
}
