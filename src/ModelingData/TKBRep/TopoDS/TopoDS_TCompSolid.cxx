#include <Standard_Type.hpp>
#include <TopoDS_TCompSolid.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_TCompSolid, TopoDS_TShape)

//=================================================================================================

TopAbs_ShapeEnum TopoDS_TCompSolid::ShapeType() const
{
  return TopAbs_COMPSOLID;
}

//=================================================================================================

occ::handle<TopoDS_TShape> TopoDS_TCompSolid::EmptyCopy() const
{
  return occ::handle<TopoDS_TCompSolid>(new TopoDS_TCompSolid());
}
