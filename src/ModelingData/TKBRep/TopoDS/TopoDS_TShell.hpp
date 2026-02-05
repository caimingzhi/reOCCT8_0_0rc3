#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

//! A set of faces connected by their edges.
class TopoDS_TShell : public TopoDS_TShape
{
public:
  //! Creates an empty TShell.
  TopoDS_TShell()

    = default;

  //! Returns SHELL.
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  //! Returns an empty TShell.
  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TShell, TopoDS_TShape)
};
