

#include <RWMesh_VertexIterator.hpp>

#include <BRep_Tool.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XCAFPrs.hpp>

RWMesh_VertexIterator::RWMesh_VertexIterator(const TDF_Label&       theLabel,
                                             const TopLoc_Location& theLocation,
                                             const bool             theToMapColors,
                                             const XCAFPrs_Style&   theStyle)
    : RWMesh_ShapeIterator(theLabel,
                           theLocation,
                           TopAbs_VERTEX,
                           TopAbs_EDGE,
                           theToMapColors,
                           theStyle)
{
  Next();
}

RWMesh_VertexIterator::RWMesh_VertexIterator(const TopoDS_Shape&  theShape,
                                             const XCAFPrs_Style& theStyle)
    : RWMesh_ShapeIterator(theShape, TopAbs_VERTEX, TopAbs_EDGE, theStyle)
{
  Next();
}

void RWMesh_VertexIterator::Next()
{
  for (; myIter.More(); myIter.Next())
  {
    myVertex = TopoDS::Vertex(myIter.Current());
    myPoint  = BRep_Tool::Pnt(myVertex);
    myTrsf   = myLocation.Transformation();
    if (myVertex.IsNull())
    {
      resetVertex();
      continue;
    }

    initVertex();
    myIter.Next();
    return;
  }

  resetVertex();
}

void RWMesh_VertexIterator::initVertex()
{
  initShape();
}
