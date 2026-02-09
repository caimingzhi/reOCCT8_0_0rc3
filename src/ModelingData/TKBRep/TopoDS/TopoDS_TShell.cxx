#include <Standard_Type.hpp>
#include <TopoDS_TShell.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_TShell, TopoDS_TShape)

TopAbs_ShapeEnum TopoDS_TShell::ShapeType() const
{
  return TopAbs_SHELL;
}

occ::handle<TopoDS_TShape> TopoDS_TShell::EmptyCopy() const
{
  return occ::handle<TopoDS_TShell>(new TopoDS_TShell());
}
