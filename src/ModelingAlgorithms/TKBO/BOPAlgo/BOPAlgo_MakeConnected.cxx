#include <BOPAlgo_MakeConnected.hpp>

#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_Tools.hpp>

#include <BOPTools_AlgoTools.hpp>

#include <BRep_Builder.hpp>

#include <TopExp_Explorer.hpp>

void BOPAlgo_MakeConnected::Perform()
{

  CheckData();
  if (HasErrors())
    return;

  if (myHistory.IsNull())
    myHistory = new BRepTools_History;

  MakeConnected();
  if (HasErrors())
    return;

  AssociateMaterials();
  if (HasErrors())
    return;
}

void BOPAlgo_MakeConnected::CheckData()
{

  if (myArguments.IsEmpty())
  {

    AddError(new BOPAlgo_AlertTooFewArguments());
    return;
  }

  NCollection_List<TopoDS_Shape> aLA;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;

  NCollection_List<TopoDS_Shape>::Iterator itLA(myArguments);
  for (; itLA.More(); itLA.Next())
    BOPTools_AlgoTools::TreatCompound(itLA.Value(), aLA, &aMFence);

  if (aLA.IsEmpty())
  {

    AddError(new BOPAlgo_AlertTooFewArguments());
    return;
  }

  itLA.Initialize(aLA);
  int iDim = BOPTools_AlgoTools::Dimension(itLA.Value());
  for (itLA.Next(); itLA.More(); itLA.Next())
  {
    if (iDim != BOPTools_AlgoTools::Dimension(itLA.Value()))
    {

      AddError(new BOPAlgo_AlertMultiDimensionalArguments());
      return;
    }
  }
}

void BOPAlgo_MakeConnected::MakeConnected()
{

  if (myGlueHistory.IsNull())
    myGlueHistory = new BRepTools_History;

  if (myArguments.Extent() == 1)
  {

    myShape = myArguments.First();
  }
  else
  {

    BOPAlgo_Builder aGluer;
    aGluer.SetArguments(myArguments);
    aGluer.SetGlue(BOPAlgo_GlueShift);
    aGluer.SetRunParallel(myRunParallel);
    aGluer.SetNonDestructive(true);
    aGluer.Perform();
    if (aGluer.HasErrors())
    {

      TopoDS_Compound aCW;
      BRep_Builder().MakeCompound(aCW);
      for (NCollection_List<TopoDS_Shape>::Iterator it(myArguments); it.More(); it.Next())
        BRep_Builder().Add(aCW, it.Value());
      AddError(new BOPAlgo_AlertUnableToGlue(aCW));
      return;
    }
    myShape = aGluer.Shape();

    myGlueHistory->Merge(aGluer.Arguments(), aGluer);
    myHistory->Merge(myGlueHistory);
  }

  myGlued = myShape;

  FillOrigins();
}

void BOPAlgo_MakeConnected::FillOrigins()
{
  myOrigins.Clear();

  if (myAllInputsMap.IsEmpty())
  {
    NCollection_List<TopoDS_Shape>::Iterator itLA(myArguments);
    for (; itLA.More(); itLA.Next())
      TopExp::MapShapes(itLA.Value(), myAllInputsMap);
  }

  const int aNbS = myAllInputsMap.Extent();
  for (int i = 1; i <= aNbS; ++i)
  {
    const TopoDS_Shape& aS = myAllInputsMap(i);
    if (!BRepTools_History::IsSupportedType(aS))
      continue;

    for (int j = 0; j < 2; ++j)
    {
      const NCollection_List<TopoDS_Shape>& aLH =
        !j ? myHistory->Modified(aS) : myHistory->Generated(aS);
      NCollection_List<TopoDS_Shape>::Iterator itLH(aLH);
      for (; itLH.More(); itLH.Next())
      {
        const TopoDS_Shape&             aHS  = itLH.Value();
        NCollection_List<TopoDS_Shape>* pLOr = myOrigins.ChangeSeek(aHS);
        if (!pLOr)
          pLOr = myOrigins.Bound(aHS, NCollection_List<TopoDS_Shape>());
        if (!pLOr->Contains(aS))
          pLOr->Append(aS);
      }
    }
  }
}

void BOPAlgo_MakeConnected::AssociateMaterials()
{
  myMaterials.Clear();

  NCollection_List<TopoDS_Shape>                         aLShapes;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;
  BOPTools_AlgoTools::TreatCompound(myShape, aLShapes, &aMFence);

  if (aLShapes.IsEmpty())
    return;

  TopAbs_ShapeEnum       anElemType;
  const TopAbs_ShapeEnum aMaterialType = aLShapes.First().ShapeType();
  if (aMaterialType == TopAbs_SOLID || aMaterialType == TopAbs_COMPSOLID)
    anElemType = TopAbs_FACE;
  else if (aMaterialType == TopAbs_FACE || aMaterialType == TopAbs_SHELL)
    anElemType = TopAbs_EDGE;
  else if (aMaterialType == TopAbs_EDGE || aMaterialType == TopAbs_WIRE)
    anElemType = TopAbs_VERTEX;
  else
    return;

  NCollection_List<TopoDS_Shape>::Iterator itLS(aLShapes);
  for (; itLS.More(); itLS.Next())
  {
    const TopoDS_Shape&                   aS   = itLS.Value();
    const NCollection_List<TopoDS_Shape>& aLOr = GetOrigins(aS);
    const TopoDS_Shape&                   aSOr = aLOr.IsEmpty() ? aS : aLOr.First();

    TopExp_Explorer anExp(aS, anElemType);
    for (; anExp.More(); anExp.Next())
    {
      const TopoDS_Shape&             anElement = anExp.Current();
      NCollection_List<TopoDS_Shape>* pLM       = myMaterials.ChangeSeek(anElement);
      if (!pLM)
        pLM = myMaterials.Bound(anElement, NCollection_List<TopoDS_Shape>());
      pLM->Append(aSOr);
    }
  }
}

void BOPAlgo_MakeConnected::Update()
{

  myHistory->Clear();
  if (!myGlueHistory.IsNull())
    myHistory->Merge(myGlueHistory);
  if (!myPeriodicityMaker.History().IsNull())
    myHistory->Merge(myPeriodicityMaker.History());

  FillOrigins();

  AssociateMaterials();
}

void BOPAlgo_MakeConnected::MakePeriodic(const BOPAlgo_MakePeriodic::PeriodicityParams& theParams)
{
  if (HasErrors())
    return;

  myPeriodicityMaker.Clear();
  myPeriodicityMaker.SetShape(myGlued);
  myPeriodicityMaker.SetPeriodicityParameters(theParams);
  myPeriodicityMaker.SetRunParallel(myRunParallel);
  myPeriodicityMaker.Perform();
  if (myPeriodicityMaker.HasErrors())
  {

    AddWarning(new BOPAlgo_AlertUnableToMakePeriodic(myShape));
    return;
  }

  myShape = myPeriodicityMaker.Shape();

  Update();
}

void BOPAlgo_MakeConnected::RepeatShape(const int theDirectionID, const int theTimes)
{
  if (HasErrors())
    return;

  if (myPeriodicityMaker.Shape().IsNull() || myPeriodicityMaker.HasErrors())
  {

    AddWarning(new BOPAlgo_AlertShapeIsNotPeriodic(myShape));
    return;
  }

  myShape = myPeriodicityMaker.RepeatShape(theDirectionID, theTimes);

  Update();
}

void BOPAlgo_MakeConnected::ClearRepetitions()
{
  if (HasErrors())
    return;

  if (myPeriodicityMaker.Shape().IsNull() || myPeriodicityMaker.HasErrors())
  {

    AddWarning(new BOPAlgo_AlertShapeIsNotPeriodic(myShape));
    return;
  }

  myPeriodicityMaker.ClearRepetitions();
  myShape = myPeriodicityMaker.Shape();

  Update();
}
