

#include <RWMesh_EdgeIterator.hpp>

#include <BRep_Tool.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XCAFPrs.hpp>

RWMesh_EdgeIterator::RWMesh_EdgeIterator(const TDF_Label&       theLabel,
                                         const TopLoc_Location& theLocation,
                                         const bool             theToMapColors,
                                         const XCAFPrs_Style&   theStyle)
    : RWMesh_ShapeIterator(theLabel,
                           theLocation,
                           TopAbs_EDGE,
                           TopAbs_FACE,
                           theToMapColors,
                           theStyle)
{
  Next();
}

RWMesh_EdgeIterator::RWMesh_EdgeIterator(const TopoDS_Shape&  theShape,
                                         const XCAFPrs_Style& theStyle)
    : RWMesh_ShapeIterator(theShape, TopAbs_EDGE, TopAbs_FACE, theStyle)
{
  Next();
}

void RWMesh_EdgeIterator::Next()
{
  for (; myIter.More(); myIter.Next())
  {
    myEdge      = TopoDS::Edge(myIter.Current());
    myPolygon3D = BRep_Tool::Polygon3D(myEdge, myLocation);
    myTrsf      = myLocation.Transformation();
    if (myPolygon3D.IsNull() || myPolygon3D->NbNodes() == 0)
    {
      resetEdge();
      continue;
    }

    initEdge();
    myIter.Next();
    return;
  }

  resetEdge();
}

void RWMesh_EdgeIterator::initEdge()
{
  initShape();
}
