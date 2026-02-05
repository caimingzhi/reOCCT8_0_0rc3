#include <TopoDS_TVertex.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_TVertex, TopoDS_TShape)

//=================================================================================================

TopAbs_ShapeEnum TopoDS_TVertex::ShapeType() const
{
  return TopAbs_VERTEX;
}
