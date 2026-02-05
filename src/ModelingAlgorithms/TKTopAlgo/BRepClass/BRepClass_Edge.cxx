#include <BRepClass_Edge.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Precision.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopExp.hpp>

//=================================================================================================

BRepClass_Edge::BRepClass_Edge()
    : myMaxTolerance(Precision::Infinite()),
      myUseBndBox(false)
{
}

//=================================================================================================

void BRepClass_Edge::SetNextEdge(
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& theMapVE)
{
  if (theMapVE.IsEmpty() || myEdge.IsNull())
  {
    return;
  }
  TopoDS_Vertex aVF, aVL;
  TopExp::Vertices(myEdge, aVF, aVL, true);

  if (aVL.IsNull() || aVL.IsSame(aVF))
  {
    return;
  }
  const NCollection_List<TopoDS_Shape>* aListE = theMapVE.Seek(aVL);
  if (aListE->Extent() == 2)
  {
    for (NCollection_List<TopoDS_Shape>::Iterator anIt(*aListE); anIt.More(); anIt.Next())
    {
      if ((!anIt.Value().IsNull()) && (!anIt.Value().IsSame(myEdge)))
      {
        myNextEdge = TopoDS::Edge(anIt.Value());
      }
    }
  }
}

//=================================================================================================

BRepClass_Edge::BRepClass_Edge(const TopoDS_Edge& E, const TopoDS_Face& F)
    : myEdge(E),
      myFace(F),
      myMaxTolerance(Precision::Infinite()),
      myUseBndBox(false)
{
}
