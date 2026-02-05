#include <BRepAlgoAPI_Defeaturing.hpp>

//=================================================================================================

void BRepAlgoAPI_Defeaturing::Build(const Message_ProgressRange& theRange)
{
  // Set not done state for the operation
  NotDone();

  // Clear the tools performing the operation
  Clear();

  // Set the inputs to BOPAlgo_RemoveFeatures algorithm
  myFeatureRemovalTool.SetShape(myInputShape);
  myFeatureRemovalTool.AddFacesToRemove(myFacesToRemove);
  myFeatureRemovalTool.SetToFillHistory(myFillHistory);
  myFeatureRemovalTool.SetRunParallel(myRunParallel);

  // Perform the features removal
  myFeatureRemovalTool.Perform(theRange);

  // Merge the Errors/Warnings from the features removal tool
  GetReport()->Merge(myFeatureRemovalTool.GetReport());

  if (HasErrors())
    return;

  // Set done state
  Done();

  // Get the result shape
  myShape = myFeatureRemovalTool.Shape();
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepAlgoAPI_Defeaturing::Modified(const TopoDS_Shape& theS)
{
  return myFeatureRemovalTool.Modified(theS);
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepAlgoAPI_Defeaturing::Generated(const TopoDS_Shape& theS)
{
  return myFeatureRemovalTool.Generated(theS);
}

//=================================================================================================

bool BRepAlgoAPI_Defeaturing::IsDeleted(const TopoDS_Shape& theS)
{
  return myFeatureRemovalTool.IsDeleted(theS);
}

//=================================================================================================

bool BRepAlgoAPI_Defeaturing::HasModified() const
{
  return myFeatureRemovalTool.HasModified();
}

//=================================================================================================

bool BRepAlgoAPI_Defeaturing::HasGenerated() const
{
  return myFeatureRemovalTool.HasGenerated();
}

//=================================================================================================

bool BRepAlgoAPI_Defeaturing::HasDeleted() const
{
  return myFeatureRemovalTool.HasDeleted();
}
