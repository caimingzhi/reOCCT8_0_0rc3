#include <Standard_Type.hpp>
#include <TopoDS_TWire.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_TWire, TopoDS_TShape)

TopAbs_ShapeEnum TopoDS_TWire::ShapeType() const
{
  return TopAbs_WIRE;
}

occ::handle<TopoDS_TShape> TopoDS_TWire::EmptyCopy() const
{
  return occ::handle<TopoDS_TWire>(new TopoDS_TWire());
}
