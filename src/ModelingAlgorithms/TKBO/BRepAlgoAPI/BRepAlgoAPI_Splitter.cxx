#include <BRepAlgoAPI_Splitter.hpp>

#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_Splitter.hpp>

BRepAlgoAPI_Splitter::BRepAlgoAPI_Splitter()

  = default;

BRepAlgoAPI_Splitter::BRepAlgoAPI_Splitter(const BOPAlgo_PaveFiller& thePF)
    : BRepAlgoAPI_BuilderAlgo(thePF)
{
}

void BRepAlgoAPI_Splitter::Build(const Message_ProgressRange& theRange)
{

  NotDone();

  Clear();

  if (myArguments.IsEmpty() || (myArguments.Extent() + myTools.Extent()) < 2)
  {
    AddError(new BOPAlgo_AlertTooFewArguments);
    return;
  }

  Message_ProgressScope aPS(theRange,
                            "Performing Split operation",
                            myIsIntersectionNeeded ? 100 : 30);
  if (myIsIntersectionNeeded)
  {

    NCollection_List<TopoDS_Shape> aLArgs = myArguments;
    for (NCollection_List<TopoDS_Shape>::Iterator it(myTools); it.More(); it.Next())
      aLArgs.Append(it.Value());

    IntersectShapes(aLArgs, aPS.Next(70));
    if (HasErrors())
      return;
  }

  myBuilder = new BOPAlgo_Splitter(myAllocator);
  myBuilder->SetArguments(myArguments);
  ((BOPAlgo_Splitter*)myBuilder)->SetTools(myTools);

  BuildResult(aPS.Next(30));
}
