#include <BOPAlgo_ToolsProvider.hpp>
#include <BOPAlgo_PaveFiller.hpp>

//=================================================================================================

BOPAlgo_ToolsProvider::BOPAlgo_ToolsProvider()
    : myTools(myAllocator),
      myMapTools(100, myAllocator)
{
}

//=================================================================================================

BOPAlgo_ToolsProvider::BOPAlgo_ToolsProvider(
  const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_Builder(theAllocator),
      myTools(myAllocator),
      myMapTools(100, myAllocator)
{
}

//=================================================================================================

void BOPAlgo_ToolsProvider::Clear()
{
  BOPAlgo_Builder::Clear();
  myTools.Clear();
  myMapTools.Clear();
}

//=================================================================================================

void BOPAlgo_ToolsProvider::AddTool(const TopoDS_Shape& theShape)
{
  if (myMapTools.Add(theShape))
    myTools.Append(theShape);
}

//=================================================================================================

void BOPAlgo_ToolsProvider::SetTools(const NCollection_List<TopoDS_Shape>& theShapes)
{
  myTools.Clear();
  NCollection_List<TopoDS_Shape>::Iterator aIt(theShapes);
  for (; aIt.More(); aIt.Next())
    AddTool(aIt.Value());
}
