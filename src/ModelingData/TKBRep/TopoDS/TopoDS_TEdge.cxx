#include <TopoDS_TEdge.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_TEdge, TopoDS_TShape)

//=================================================================================================

TopAbs_ShapeEnum TopoDS_TEdge::ShapeType() const
{
  return TopAbs_EDGE;
}
