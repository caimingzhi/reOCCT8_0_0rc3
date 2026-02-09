#include <BOPAlgo_MakePeriodic.hpp>

#include <BOPAlgo_Alerts.hpp>

#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_PaveFiller.hpp>

#include <BRepAlgoAPI_Common.hpp>
#include <BRepAlgoAPI_Splitter.hpp>

#include <BRepBndLib.hpp>

#include <BRepBuilderAPI_Transform.hpp>

#include <BRepPrimAPI_MakeBox.hpp>

#include <gp_Pln.hpp>

#include <Precision.hpp>

#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

static const gp_Dir MY_DIRECTIONS[3] = {gp::DX(), gp::DY(), gp::DZ()};

void BOPAlgo_MakePeriodic::Perform()
{

  CheckData();
  if (HasErrors())
    return;

  Trim();
  if (HasErrors())
    return;

  MakeIdentical();
  if (HasErrors())
    return;
}

void BOPAlgo_MakePeriodic::CheckData()
{
  if ((!IsXPeriodic() || XPeriod() < Precision::Confusion())
      && (!IsYPeriodic() || YPeriod() < Precision::Confusion())
      && (!IsZPeriodic() || ZPeriod() < Precision::Confusion()))
  {

    AddError(new BOPAlgo_AlertNoPeriodicityRequired());
    return;
  }
}

static void AddToShape(const TopoDS_Shape& theWhat, TopoDS_Shape& theWhere)
{
  if (theWhere.IsNull())
    BRep_Builder().MakeCompound(TopoDS::Compound(theWhere));
  BRep_Builder().Add(theWhere, theWhat);
}

static void AddToShape(const NCollection_List<TopoDS_Shape>& theLWhat, TopoDS_Shape& theWhere)
{
  NCollection_List<TopoDS_Shape>::Iterator it(theLWhat);
  for (; it.More(); it.Next())
    AddToShape(it.Value(), theWhere);
}

void BOPAlgo_MakePeriodic::Trim()
{

  if (IsInputXTrimmed() && IsInputYTrimmed() && IsInputZTrimmed())
    return;

  Bnd_Box aBox;
  BRepBndLib::Add(myInputShape, aBox);

  aBox.Enlarge(0.1 * sqrt(aBox.SquareExtent()));

  gp_Pnt aPMin = aBox.CornerMin();
  gp_Pnt aPMax = aBox.CornerMax();

  for (int i = 0; i < 3; ++i)
  {
    if (IsInputTrimmed(i))
      continue;

    aPMin.SetCoord(i + 1, PeriodFirst(i));
    aPMax.SetCoord(i + 1, PeriodFirst(i) + Period(i));
  }

  BRepPrimAPI_MakeBox aMBox(aPMin, aPMax);
  const TopoDS_Shape& aTrimBox = aMBox.Solid();

  BRepAlgoAPI_Common aCommon;

  NCollection_List<TopoDS_Shape> anObj;
  anObj.Append(myInputShape);
  aCommon.SetArguments(anObj);

  NCollection_List<TopoDS_Shape> aTool;
  aTool.Append(aTrimBox);
  aCommon.SetTools(aTool);

  aCommon.SetRunParallel(myRunParallel);

  aCommon.Build();
  if (aCommon.HasErrors())
  {

    myReport->Merge(aCommon.GetReport());

    TopoDS_Compound aWS;
    AddToShape(myInputShape, aWS);
    AddToShape(aTrimBox, aWS);
    AddError(new BOPAlgo_AlertUnableToTrim(aWS));
    return;
  }

  myShape = aCommon.Shape();

  mySplitHistory = new BRepTools_History();
  mySplitHistory->Merge(anObj, aCommon);
}

void BOPAlgo_MakePeriodic::MakeIdentical()
{
  if (myShape.IsNull())
    myShape = myInputShape;

  if (mySplitHistory.IsNull())
    mySplitHistory = new BRepTools_History;

  SplitNegative();
  if (HasErrors())
    return;

  SplitPositive();

  myHistory = new BRepTools_History();
  myHistory->Merge(mySplitHistory);
}

void BOPAlgo_MakePeriodic::SplitNegative()
{

  for (int i = 0; i < 3; ++i)
  {
    if (!IsPeriodic(i))
      continue;

    gp_Trsf aNegTrsf;
    aNegTrsf.SetTranslationPart(Period(i) * MY_DIRECTIONS[i].Reversed());
    BRepBuilderAPI_Transform aNegT(myShape, aNegTrsf, false);

    NCollection_List<TopoDS_Shape> aTools;
    aTools.Append(aNegT.Shape());
    SplitShape(aTools, mySplitHistory);
  }
}

static void AddTwin(
  const TopoDS_Shape& theS,
  const TopoDS_Shape& theTwin,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    theMap)
{
  NCollection_List<TopoDS_Shape>* aTwins = theMap.ChangeSeek(theS);
  if (!aTwins)
  {
    theMap.Bound(theS, NCollection_List<TopoDS_Shape>())->Append(theTwin);
    return;
  }

  NCollection_List<TopoDS_Shape>::Iterator itLT(*aTwins);
  for (; itLT.More(); itLT.Next())
  {
    if (theTwin.IsSame(itLT.Value()))
      break;
  }

  if (!itLT.More())
    aTwins->Append(theTwin);
}

void BOPAlgo_MakePeriodic::SplitPositive()
{

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aSubShapesMap;
  TopExp::MapShapes(myShape, aSubShapesMap);
  const int aNbS = aSubShapesMap.Extent();

  NCollection_List<TopoDS_Shape> aTools;

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aTranslationHistMap;

  for (int i = 0; i < 3; ++i)
  {
    if (!IsPeriodic(i))
      continue;

    gp_Trsf aPosTrsf;
    aPosTrsf.SetTranslationPart(Period(i) * MY_DIRECTIONS[i]);
    BRepBuilderAPI_Transform aTranslator(myShape, aPosTrsf, false);
    aTools.Append(aTranslator.Shape());

    for (int j = 1; j <= aNbS; ++j)
    {
      const TopoDS_Shape& aS = aSubShapesMap(j);
      if (BRepTools_History::IsSupportedType(aS))
      {
        const NCollection_List<TopoDS_Shape>& aSM = aTranslator.Modified(aS);
        NCollection_List<TopoDS_Shape>*       pTS = aTranslationHistMap.ChangeSeek(aS);
        if (!pTS)
          pTS = &aTranslationHistMap(aTranslationHistMap.Add(aS, NCollection_List<TopoDS_Shape>()));
        pTS->Append(aSM.First());
      }
    }
  }

  occ::handle<BRepTools_History> aSplitShapeHist = new BRepTools_History,
                                 aSplitToolsHist = new BRepTools_History;

  SplitShape(aTools, aSplitShapeHist, aSplitToolsHist);
  if (HasErrors())
    return;

  mySplitHistory->Merge(aSplitShapeHist);

  const int aNbSH = aTranslationHistMap.Extent();
  for (int i = 1; i <= aNbSH; ++i)
  {
    const TopoDS_Shape*                   pS   = &aTranslationHistMap.FindKey(i);
    const NCollection_List<TopoDS_Shape>& aSIm = aSplitShapeHist->Modified(*pS);
    if (aSIm.Extent() == 1)
      pS = &aSIm.First();
    else if (aSIm.Extent() > 1)
      continue;

    const NCollection_List<TopoDS_Shape>& aLTranslated = aTranslationHistMap(i);

    NCollection_List<TopoDS_Shape>::Iterator itLT(aLTranslated);
    for (; itLT.More(); itLT.Next())
    {
      const TopoDS_Shape& aT = itLT.Value();

      const NCollection_List<TopoDS_Shape>& aTSplits = aSplitToolsHist->Modified(aT);

      NCollection_List<TopoDS_Shape>::Iterator itSp(aTSplits);
      for (; itSp.More(); itSp.Next())
      {
        const TopoDS_Shape& aSp = itSp.Value();
        AddTwin(*pS, aSp, myTwins);
        AddTwin(aSp, *pS, myTwins);
      }
    }
  }
}

void BOPAlgo_MakePeriodic::SplitShape(const NCollection_List<TopoDS_Shape>& theTools,
                                      const occ::handle<BRepTools_History>& theSplitShapeHistory,
                                      const occ::handle<BRepTools_History>& theSplitToolsHistory)
{

  BOPAlgo_PaveFiller anIntersector;
  anIntersector.SetArguments(theTools);

  anIntersector.AddArgument(myShape);

  anIntersector.SetGlue(BOPAlgo_GlueShift);

  anIntersector.SetNonDestructive(true);

  anIntersector.SetRunParallel(myRunParallel);

  anIntersector.Perform();

  if (anIntersector.HasErrors())
  {

    myReport->Merge(anIntersector.GetReport());

    TopoDS_Compound aWS;
    AddToShape(theTools, aWS);
    AddToShape(myShape, aWS);
    AddError(new BOPAlgo_AlertUnableToMakeIdentical(aWS));
    return;
  }

  BRepAlgoAPI_Splitter aSplitter(anIntersector);

  NCollection_List<TopoDS_Shape> anObj;
  anObj.Append(myShape);
  aSplitter.SetArguments(anObj);

  aSplitter.SetTools(theTools);

  aSplitter.SetGlue(BOPAlgo_GlueShift);

  aSplitter.SetRunParallel(myRunParallel);

  aSplitter.Build();

  if (aSplitter.HasErrors())
  {

    myReport->Merge(aSplitter.GetReport());

    TopoDS_Compound aWS;
    AddToShape(theTools, aWS);
    AddToShape(myShape, aWS);
    AddError(new BOPAlgo_AlertUnableToMakeIdentical(aWS));
    return;
  }

  myShape = aSplitter.Shape();

  if (!theSplitShapeHistory.IsNull())
    theSplitShapeHistory->Merge(anObj, aSplitter);
  if (!theSplitToolsHistory.IsNull())
    theSplitToolsHistory->Merge(theTools, aSplitter);
}

const TopoDS_Shape& BOPAlgo_MakePeriodic::RepeatShape(const int theDir, const int theTimes)
{
  if (myRepeatedShape.IsNull())
    myRepeatedShape = myShape;

  if (!IsPeriodic(theDir))
    return myRepeatedShape;

  if (theTimes == 0)
    return myRepeatedShape;

  const int id = BOPAlgo_MakePeriodic::ToDirectionID(theDir);
  if (myRepeatPeriod[id] < Precision::Confusion())
    myRepeatPeriod[id] = Period(id);
  const double aPeriod = myRepeatPeriod[id];

  const int iDir = theTimes > 0 ? 1 : -1;

  BRepTools_History                                             aTranslationHistory;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aSubShapesMap;
  TopExp::MapShapes(myRepeatedShape, aSubShapesMap);
  const int aNbS = aSubShapesMap.Extent();

  NCollection_List<TopoDS_Shape> aShapes;

  aShapes.Append(myRepeatedShape);
  for (int i = 1; i <= aNbS; ++i)
  {
    const TopoDS_Shape& aS = aSubShapesMap(i);
    if (BRepTools_History::IsSupportedType(aS))
      aTranslationHistory.AddGenerated(aS, aS);
  }

  for (int i = 1; i <= std::abs(theTimes); ++i)
  {
    gp_Trsf aTrsf;
    aTrsf.SetTranslationPart(iDir * i * aPeriod * MY_DIRECTIONS[id]);
    BRepBuilderAPI_Transform aTranslator(myRepeatedShape, aTrsf, false);
    aShapes.Append(aTranslator.Shape());

    for (int j = 1; j <= aNbS; ++j)
    {
      const TopoDS_Shape& aS = aSubShapesMap(j);
      if (BRepTools_History::IsSupportedType(aS))
      {
        const NCollection_List<TopoDS_Shape>& aLT = aTranslator.Modified(aS);
        aTranslationHistory.AddGenerated(aS, aLT.First());
      }
    }
  }

  myHistory->Merge(aTranslationHistory);

  BOPAlgo_Builder aGluer;
  aGluer.SetArguments(aShapes);

  aGluer.SetGlue(BOPAlgo_GlueFull);

  aGluer.SetRunParallel(myRunParallel);

  aGluer.Perform();
  if (aGluer.HasErrors())
  {

    TopoDS_Compound aWS;
    AddToShape(aShapes, aWS);
    AddWarning(new BOPAlgo_AlertUnableToRepeat(aWS));
    return myRepeatedShape;
  }

  myRepeatedShape = aGluer.Shape();

  myRepeatPeriod[id] += std::abs(theTimes) * myRepeatPeriod[id];

  BRepTools_History aGluingHistory(aShapes, aGluer);
  myHistory->Merge(aGluingHistory);

  UpdateTwins(aTranslationHistory, aGluingHistory);

  return myRepeatedShape;
}

void BOPAlgo_MakePeriodic::UpdateTwins(const BRepTools_History& theTranslationHistory,
                                       const BRepTools_History& theGluingHistory)
{
  if (myTwins.IsEmpty())
    return;

  if (myRepeatedTwins.IsEmpty())
    myRepeatedTwins = myTwins;

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aNewTwinsMap;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMTwinsDone;

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator itDMap(myRepeatedTwins);
  for (; itDMap.More(); itDMap.Next())
  {
    const TopoDS_Shape& aS = itDMap.Key();
    aMTwinsDone.Add(aS);

    const NCollection_List<TopoDS_Shape>& aLTwins = itDMap.Value();

    NCollection_List<TopoDS_Shape>::Iterator itLT(aLTwins);
    for (; itLT.More(); itLT.Next())
    {
      if (aMTwinsDone.Contains(itLT.Value()))
        break;
    }
    if (itLT.More())

      continue;

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aNewGroup;
    itLT.Initialize(aLTwins);

    for (bool bShape = true; itLT.More();)
    {
      const TopoDS_Shape&                      aTwin = bShape ? aS : itLT.Value();
      const NCollection_List<TopoDS_Shape>&    aLG   = theTranslationHistory.Generated(aTwin);
      NCollection_List<TopoDS_Shape>::Iterator itLG(aLG);
      for (; itLG.More(); itLG.Next())
      {
        const TopoDS_Shape&                   aG  = itLG.Value();
        const NCollection_List<TopoDS_Shape>& aLM = theGluingHistory.Modified(aG);
        if (aLM.IsEmpty())
          aNewGroup.Add(aG);
        else
        {
          NCollection_List<TopoDS_Shape>::Iterator itLM(aLM);
          for (; itLM.More(); itLM.Next())
            aNewGroup.Add(itLM.Value());
        }
      }

      if (bShape)
        bShape = false;
      else
        itLT.Next();
    }

    const int aNbTwins = aNewGroup.Extent();
    for (int i = 1; i <= aNbTwins; ++i)
    {
      NCollection_List<TopoDS_Shape>* pTwins =
        aNewTwinsMap.Bound(aNewGroup(i), NCollection_List<TopoDS_Shape>());
      for (int j = 1; j <= aNbTwins; ++j)
        if (i != j)
          pTwins->Append(aNewGroup(j));
    }
  }

  myRepeatedTwins = aNewTwinsMap;
}
