#include <Bnd_Box.hpp>
#include <BOPAlgo_BuilderSolid.hpp>
#include <BOPAlgo_MakerVolume.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Tools.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPDS_DS.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

static void AddFace(const TopoDS_Shape& theF, NCollection_List<TopoDS_Shape>& theLF);

//=================================================================================================

void BOPAlgo_MakerVolume::CheckData()
{
  if (myArguments.IsEmpty())
  {
    AddError(new BOPAlgo_AlertTooFewArguments); // no arguments to process
    return;
  }
  //
  CheckFiller();
}

//=================================================================================================

void BOPAlgo_MakerVolume::Perform(const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, "Performing MakeVolume operation", 10);
  double                anInterPart = myIntersect ? 9 : 0.5;
  double                aBuildPart  = 10. - anInterPart;

  GetReport()->Clear();
  //
  if (myEntryPoint == 1)
  {
    if (myPaveFiller)
    {
      delete myPaveFiller;
      myPaveFiller = nullptr;
    }
  }
  //
  occ::handle<NCollection_BaseAllocator> aAllocator =
    NCollection_BaseAllocator::CommonBaseAllocator();
  BOPAlgo_PaveFiller* pPF = new BOPAlgo_PaveFiller(aAllocator);
  //
  if (!myIntersect)
  {
    // if there is no need to intersect the arguments, then it is necessary
    // to create the compound of them and use it as one argument
    TopoDS_Compound                          anArgs;
    BRep_Builder                             aBB;
    NCollection_List<TopoDS_Shape>::Iterator aIt;
    NCollection_List<TopoDS_Shape>           aLS;
    //
    aBB.MakeCompound(anArgs);
    aIt.Initialize(myArguments);
    for (; aIt.More(); aIt.Next())
    {
      const TopoDS_Shape& aS = aIt.Value();
      aBB.Add(anArgs, aS);
    }
    aLS.Append(anArgs);
    //
    pPF->SetArguments(aLS);
  }
  else
  {
    pPF->SetArguments(myArguments);
  }
  //
  pPF->SetRunParallel(myRunParallel);
  pPF->SetFuzzyValue(myFuzzyValue);
  pPF->SetNonDestructive(myNonDestructive);
  pPF->SetGlue(myGlue);
  pPF->SetUseOBB(myUseOBB);
  pPF->Perform(aPS.Next(anInterPart));
  //
  myEntryPoint = 1;
  PerformInternal(*pPF, aPS.Next(aBuildPart));
}

//=================================================================================================

void BOPAlgo_MakerVolume::PerformInternal1(const BOPAlgo_PaveFiller&    theFiller,
                                           const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, "Building volumes", 100);
  myPaveFiller = (BOPAlgo_PaveFiller*)&theFiller;
  myDS         = myPaveFiller->PDS();
  myContext    = myPaveFiller->Context();
  //
  // 1. CheckData
  CheckData();
  if (HasErrors())
  {
    return;
  }
  //
  // 2. Prepare
  Prepare();
  if (HasErrors())
  {
    return;
  }
  //
  BOPAlgo_PISteps aSteps(PIOperation_Last);
  analyzeProgress(100., aSteps);

  // 3. Fill Images
  if (myIntersect)
  {
    // 3.1. Vertices
    FillImagesVertices(aPS.Next(aSteps.GetStep(PIOperation_TreatVertices)));
    if (HasErrors())
    {
      return;
    }
    // 3.2. Edges
    FillImagesEdges(aPS.Next(aSteps.GetStep(PIOperation_TreatEdges)));
    if (HasErrors())
    {
      return;
    }
    // 3.3. Wires
    FillImagesContainers(TopAbs_WIRE, aPS.Next(aSteps.GetStep(PIOperation_TreatWires)));
    if (HasErrors())
    {
      return;
    }
    // 3.4. Faces
    FillImagesFaces(aPS.Next(aSteps.GetStep(PIOperation_TreatFaces)));
    if (HasErrors())
    {
      return;
    }
  }
  //
  // 4. Collect faces
  CollectFaces();
  if (HasErrors())
  {
    return;
  }
  //
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aBoxFaces;
  NCollection_List<TopoDS_Shape>                         aLSR;
  //
  // 5. Create bounding box
  MakeBox(aBoxFaces);
  //
  // 6. Make volumes
  BuildSolids(aLSR, aPS.Next(aSteps.GetStep(PIOperation_BuildSolids)));
  if (HasErrors())
  {
    return;
  }
  //
  // 7. Treat the result
  RemoveBox(aLSR, aBoxFaces);
  //
  // 8. Fill internal shapes
  FillInternalShapes(aLSR);
  //
  // 9. Build Result
  BuildShape(aLSR);
  //
  // 10. History
  PrepareHistory(aPS.Next(aSteps.GetStep(PIOperation_FillHistory)));
  if (HasErrors())
  {
    return;
  }
  //
  // 11. Post-treatment
  PostTreat(aPS.Next(aSteps.GetStep(PIOperation_PostTreat)));
}

//=================================================================================================

void BOPAlgo_MakerVolume::fillPISteps(BOPAlgo_PISteps& theSteps) const
{
  NbShapes aNbShapes = getNbShapes();
  if (myIntersect)
  {
    theSteps.SetStep(PIOperation_TreatVertices, aNbShapes.NbVertices());
    theSteps.SetStep(PIOperation_TreatEdges, aNbShapes.NbEdges());
    theSteps.SetStep(PIOperation_TreatWires, aNbShapes.NbWires());
    theSteps.SetStep(PIOperation_TreatFaces, 50 * aNbShapes.NbFaces());
  }
  theSteps.SetStep(PIOperation_BuildSolids, 50 * aNbShapes.NbFaces());
}

//=================================================================================================

void BOPAlgo_MakerVolume::CollectFaces()
{
  //
  int                                                    i, aNbShapes;
  NCollection_List<TopoDS_Shape>::Iterator               aIt;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;
  //
  aNbShapes = myDS->NbSourceShapes();
  for (i = 0; i < aNbShapes; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_FACE)
    {
      continue;
    }
    //
    const Bnd_Box& aB = aSI.Box();
    myBBox.Add(aB);
    //
    const TopoDS_Shape& aF = aSI.Shape();
    if (myImages.IsBound(aF))
    {
      const NCollection_List<TopoDS_Shape>& aLFIm = myImages.Find(aF);
      aIt.Initialize(aLFIm);
      for (; aIt.More(); aIt.Next())
      {
        const TopoDS_Shape& aFIm = aIt.Value();
        if (aMFence.Add(aFIm))
        {
          AddFace(aFIm, myFaces);
        }
      }
    }
    else
    {
      AddFace(aF, myFaces);
    }
  }
}

//=================================================================================================

void BOPAlgo_MakerVolume::MakeBox(
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theBoxFaces)
{
  //
  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax, anExt;
  //
  anExt = sqrt(myBBox.SquareExtent()) * 0.5;
  myBBox.Enlarge(anExt);
  myBBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
  //
  gp_Pnt aPMin(aXmin, aYmin, aZmin), aPMax(aXmax, aYmax, aZmax);
  //
  mySBox = BRepPrimAPI_MakeBox(aPMin, aPMax).Solid();
  //
  TopExp_Explorer aExp(mySBox, TopAbs_FACE);
  for (; aExp.More(); aExp.Next())
  {
    const TopoDS_Shape& aF = aExp.Current();
    myFaces.Append(aF);
    theBoxFaces.Add(aF);
  }
}

//=================================================================================================

void BOPAlgo_MakerVolume::BuildSolids(NCollection_List<TopoDS_Shape>& theLSR,
                                      const Message_ProgressRange&    theRange)
{
  BOPAlgo_BuilderSolid aBS;
  //
  aBS.SetShapes(myFaces);
  aBS.SetRunParallel(myRunParallel);
  aBS.SetAvoidInternalShapes(myAvoidInternalShapes);
  aBS.Perform(theRange);
  if (aBS.HasErrors())
  {
    AddError(new BOPAlgo_AlertSolidBuilderFailed); // SolidBuilder failed
    return;
  }
  //
  myReport->Merge(aBS.GetReport());
  //
  theLSR = aBS.Areas();
}

//=================================================================================================

void BOPAlgo_MakerVolume::RemoveBox(
  NCollection_List<TopoDS_Shape>&                               theLSR,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theBoxFaces)
{
  //
  NCollection_List<TopoDS_Shape>::Iterator aIt;
  TopExp_Explorer                          aExp;
  bool                                     bFound;
  //
  bFound = false;
  aIt.Initialize(theLSR);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aSR = aIt.Value();
    //
    aExp.Init(aSR, TopAbs_FACE);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Shape& aF = aExp.Current();
      if (theBoxFaces.Contains(aF))
      {
        bFound = true;
        theLSR.Remove(aIt);
        break;
      }
    }
    if (bFound)
    {
      break;
    }
  }
}

//=================================================================================================

void BOPAlgo_MakerVolume::BuildShape(const NCollection_List<TopoDS_Shape>& theLSR)
{
  if (theLSR.Extent() == 1)
  {
    myShape = theLSR.First();
  }
  else
  {
    BRep_Builder                             aBB;
    NCollection_List<TopoDS_Shape>::Iterator aIt;
    //
    aIt.Initialize(theLSR);
    for (; aIt.More(); aIt.Next())
    {
      const TopoDS_Shape& aSol = aIt.Value();
      aBB.Add(myShape, aSol);
    }
  }
}

//=================================================================================================

void BOPAlgo_MakerVolume::FillInternalShapes(const NCollection_List<TopoDS_Shape>& theLSR)
{
  if (myAvoidInternalShapes)
  {
    return;
  }

  // Get all non-compound shapes
  NCollection_List<TopoDS_Shape> aLSC;
  // Fence map
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;

  NCollection_List<TopoDS_Shape>::Iterator itLA(myDS->Arguments());
  for (; itLA.More(); itLA.Next())
    BOPTools_AlgoTools::TreatCompound(itLA.Value(), aLSC, &aMFence);

  // Get only edges and vertices from arguments
  NCollection_List<TopoDS_Shape> aLVE;

  itLA.Initialize(aLSC);
  for (; itLA.More(); itLA.Next())
  {
    const TopoDS_Shape& aS    = itLA.Value();
    TopAbs_ShapeEnum    aType = aS.ShapeType();
    if (aType == TopAbs_WIRE)
    {
      for (TopoDS_Iterator it(aS); it.More(); it.Next())
      {
        const TopoDS_Shape& aSS = it.Value();
        if (aMFence.Add(aSS))
          aLVE.Append(aSS);
      }
    }
    else if (aType == TopAbs_VERTEX || aType == TopAbs_EDGE)
      aLVE.Append(aS);
  }

  BOPAlgo_Tools::FillInternals(theLSR, aLVE, myImages, myContext);
}

//=================================================================================================

void AddFace(const TopoDS_Shape& theF, NCollection_List<TopoDS_Shape>& theLF)
{
  TopoDS_Shape aFF = theF;
  aFF.Orientation(TopAbs_FORWARD);
  theLF.Append(aFF);
  aFF.Orientation(TopAbs_REVERSED);
  theLF.Append(aFF);
}
