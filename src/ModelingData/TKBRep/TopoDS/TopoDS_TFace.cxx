#include <Standard_Type.hpp>
#include <TopoDS_TFace.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_TFace, TopoDS_TShape)

//=================================================================================================

TopAbs_ShapeEnum TopoDS_TFace::ShapeType() const
{
  return TopAbs_FACE;
}

//=================================================================================================

occ::handle<TopoDS_TShape> TopoDS_TFace::EmptyCopy() const
{
  return occ::handle<TopoDS_TFace>(new TopoDS_TFace());
}
