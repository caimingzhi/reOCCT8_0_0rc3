#include <BRepAlgoAPI_BuilderAlgo.hpp>

#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPDS_DS.hpp>
#include <ShapeUpgrade_UnifySameDomain.hpp>
#include <TopoDS_Shape.hpp>

BRepAlgoAPI_BuilderAlgo::BRepAlgoAPI_BuilderAlgo()
    : myNonDestructive(false),
      myGlue(BOPAlgo_GlueOff),
      myCheckInverted(true),
      myFillHistory(true),
      myIsIntersectionNeeded(true),
      myDSFiller(nullptr),
      myBuilder(nullptr)
{
}

BRepAlgoAPI_BuilderAlgo::BRepAlgoAPI_BuilderAlgo(const BOPAlgo_PaveFiller& aPF)
    : myNonDestructive(false),
      myGlue(BOPAlgo_GlueOff),
      myCheckInverted(true),
      myFillHistory(true),
      myIsIntersectionNeeded(false),
      myBuilder(nullptr)
{
  myDSFiller = (BOPAlgo_PaveFiller*)&aPF;
}

BRepAlgoAPI_BuilderAlgo::~BRepAlgoAPI_BuilderAlgo()
{
  Clear();
}

void BRepAlgoAPI_BuilderAlgo::Clear()
{
  BRepAlgoAPI_Algo::Clear();
  if (myDSFiller && myIsIntersectionNeeded)
  {
    delete myDSFiller;
    myDSFiller = nullptr;
  }
  if (myBuilder)
  {
    delete myBuilder;
    myBuilder = nullptr;
  }
  if (myHistory)
    myHistory.Nullify();

  if (mySimplifierHistory)
    mySimplifierHistory.Nullify();
}

void BRepAlgoAPI_BuilderAlgo::Build(const Message_ProgressRange& theRange)
{

  NotDone();

  Clear();
  Message_ProgressScope aPS(theRange, "Performing General Fuse operation", 100);

  IntersectShapes(myArguments, aPS.Next(70));
  if (HasErrors())
    return;

  myBuilder = new BOPAlgo_Builder(myAllocator);

  myBuilder->SetArguments(myArguments);

  BuildResult(aPS.Next(30));
}

void BRepAlgoAPI_BuilderAlgo::IntersectShapes(const NCollection_List<TopoDS_Shape>& theArgs,
                                              const Message_ProgressRange&          theRange)
{
  if (!myIsIntersectionNeeded)
    return;

  if (myDSFiller)
    delete myDSFiller;

  myDSFiller = new BOPAlgo_PaveFiller(myAllocator);

  myDSFiller->SetArguments(theArgs);

  myDSFiller->SetRunParallel(myRunParallel);

  myDSFiller->SetFuzzyValue(myFuzzyValue);
  myDSFiller->SetNonDestructive(myNonDestructive);
  myDSFiller->SetGlue(myGlue);
  myDSFiller->SetUseOBB(myUseOBB);

  SetAttributes();

  myDSFiller->Perform(theRange);

  GetReport()->Merge(myDSFiller->GetReport());
}

void BRepAlgoAPI_BuilderAlgo::BuildResult(const Message_ProgressRange& theRange)
{

  myBuilder->SetRunParallel(myRunParallel);

  myBuilder->SetCheckInverted(myCheckInverted);
  myBuilder->SetToFillHistory(myFillHistory);

  myBuilder->PerformWithFiller(*myDSFiller, theRange);

  GetReport()->Merge(myBuilder->GetReport());

  if (myBuilder->HasErrors())
    return;

  Done();

  myShape = myBuilder->Shape();

  if (myFillHistory)
  {
    myHistory = new BRepTools_History;
    myHistory->Merge(myBuilder->History());
  }
}

void BRepAlgoAPI_BuilderAlgo::SimplifyResult(const bool   theUnifyEdges,
                                             const bool   theUnifyFaces,
                                             const double theAngularTol)
{
  if (HasErrors())
    return;

  if (!theUnifyEdges && !theUnifyFaces)
    return;

  ShapeUpgrade_UnifySameDomain anUnifier(myShape, theUnifyEdges, theUnifyFaces, true);

  anUnifier.SetLinearTolerance(myFuzzyValue);
  anUnifier.SetAngularTolerance(theAngularTol);
  anUnifier.SetSafeInputMode(myNonDestructive);
  anUnifier.AllowInternalEdges(false);

  anUnifier.Build();

  myShape = anUnifier.Shape();

  mySimplifierHistory = anUnifier.History();
  if (myFillHistory)

    myHistory->Merge(mySimplifierHistory);
}

const NCollection_List<TopoDS_Shape>& BRepAlgoAPI_BuilderAlgo::Modified(const TopoDS_Shape& theS)
{
  if (myFillHistory && myHistory)
    return myHistory->Modified(theS);
  myGenerated.Clear();
  return myGenerated;
}

const NCollection_List<TopoDS_Shape>& BRepAlgoAPI_BuilderAlgo::Generated(const TopoDS_Shape& theS)
{
  if (myFillHistory && myHistory)
    return myHistory->Generated(theS);
  myGenerated.Clear();
  return myGenerated;
}

bool BRepAlgoAPI_BuilderAlgo::IsDeleted(const TopoDS_Shape& theS)
{
  return (myFillHistory && myHistory ? myHistory->IsRemoved(theS) : false);
}

bool BRepAlgoAPI_BuilderAlgo::HasModified() const
{
  return (myFillHistory && myHistory ? myHistory->HasModified() : false);
}

bool BRepAlgoAPI_BuilderAlgo::HasGenerated() const
{
  return (myFillHistory && myHistory ? myHistory->HasGenerated() : false);
}

bool BRepAlgoAPI_BuilderAlgo::HasDeleted() const
{
  return (myFillHistory && myHistory ? myHistory->HasRemoved() : false);
}

const NCollection_List<TopoDS_Shape>& BRepAlgoAPI_BuilderAlgo::SectionEdges()
{
  myGenerated.Clear();
  if (myBuilder == nullptr)
    return myGenerated;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;

  const BOPDS_PDS& pDS = myDSFiller->PDS();

  NCollection_Vector<BOPDS_InterfFF>& aFFs  = pDS->InterfFF();
  const int                           aNbFF = aFFs.Length();
  for (int i = 0; i < aNbFF; ++i)
  {
    BOPDS_InterfFF& aFFi = aFFs(i);

    const NCollection_Vector<BOPDS_Curve>& aSectionCurves = aFFi.Curves();
    const int                              aNbC           = aSectionCurves.Length();
    for (int j = 0; j < aNbC; ++j)
    {
      const BOPDS_Curve& aCurve = aSectionCurves(j);

      const NCollection_List<occ::handle<BOPDS_PaveBlock>>&    aSectionEdges = aCurve.PaveBlocks();
      NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItPB(aSectionEdges);
      for (; aItPB.More(); aItPB.Next())
      {
        const occ::handle<BOPDS_PaveBlock>& aPB = aItPB.Value();
        const TopoDS_Shape&                 aSE = pDS->Shape(aPB->Edge());
        if (!aMFence.Add(aSE))
          continue;

        if (mySimplifierHistory)
        {
          if (mySimplifierHistory->IsRemoved(aSE))
            continue;

          const NCollection_List<TopoDS_Shape>& aLSEIm = mySimplifierHistory->Modified(aSE);
          if (!aLSEIm.IsEmpty())
          {
            NCollection_List<TopoDS_Shape>::Iterator aItLEIm(aLSEIm);
            for (; aItLEIm.More(); aItLEIm.Next())
            {
              if (aMFence.Add(aItLEIm.Value()))
                myGenerated.Append(aItLEIm.Value());
            }
          }
          else
            myGenerated.Append(aSE);
        }
        else
          myGenerated.Append(aSE);
      }
    }
  }
  return myGenerated;
}
