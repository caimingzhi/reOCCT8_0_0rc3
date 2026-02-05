#include <Standard_Type.hpp>
#include <TopoDS_TSolid.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_TSolid, TopoDS_TShape)

//=================================================================================================

TopAbs_ShapeEnum TopoDS_TSolid::ShapeType() const
{
  return TopAbs_SOLID;
}

//=================================================================================================

occ::handle<TopoDS_TShape> TopoDS_TSolid::EmptyCopy() const
{
  return occ::handle<TopoDS_TSolid>(new TopoDS_TSolid());
}
