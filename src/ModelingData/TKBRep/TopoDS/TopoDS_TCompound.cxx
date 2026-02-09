#include <Standard_Type.hpp>
#include <TopoDS_TCompound.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_TCompound, TopoDS_TShape)

TopAbs_ShapeEnum TopoDS_TCompound::ShapeType() const
{
  return TopAbs_COMPOUND;
}

occ::handle<TopoDS_TShape> TopoDS_TCompound::EmptyCopy() const
{
  return occ::handle<TopoDS_TCompound>(new TopoDS_TCompound());
}
