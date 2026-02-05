#include <BRepAlgoAPI_Splitter.hpp>

#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_Splitter.hpp>

//=================================================================================================

BRepAlgoAPI_Splitter::BRepAlgoAPI_Splitter()

  = default;

//=================================================================================================

BRepAlgoAPI_Splitter::BRepAlgoAPI_Splitter(const BOPAlgo_PaveFiller& thePF)
    : BRepAlgoAPI_BuilderAlgo(thePF)
{
}

//=================================================================================================

void BRepAlgoAPI_Splitter::Build(const Message_ProgressRange& theRange)
{
  // Set Not Done status by default
  NotDone();
  // Clear the contents
  Clear();
  // Check for availability of arguments and tools
  if (myArguments.IsEmpty() || (myArguments.Extent() + myTools.Extent()) < 2)
  {
    AddError(new BOPAlgo_AlertTooFewArguments);
    return;
  }

  // If necessary perform intersection of the argument shapes
  Message_ProgressScope aPS(theRange,
                            "Performing Split operation",
                            myIsIntersectionNeeded ? 100 : 30);
  if (myIsIntersectionNeeded)
  {
    // Combine Arguments and Tools for intersection into a single list
    NCollection_List<TopoDS_Shape> aLArgs = myArguments;
    for (NCollection_List<TopoDS_Shape>::Iterator it(myTools); it.More(); it.Next())
      aLArgs.Append(it.Value());

    // Perform intersection
    IntersectShapes(aLArgs, aPS.Next(70));
    if (HasErrors())
      return;
  }

  // Initialization of the building tool
  myBuilder = new BOPAlgo_Splitter(myAllocator);
  myBuilder->SetArguments(myArguments);
  ((BOPAlgo_Splitter*)myBuilder)->SetTools(myTools);

  // Build result shape basing on the intersection results
  BuildResult(aPS.Next(30));
}
