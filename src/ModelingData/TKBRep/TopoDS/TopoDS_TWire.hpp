#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

//! A set of edges connected by their vertices.
class TopoDS_TWire : public TopoDS_TShape
{
public:
  //! Creates an empty TWire.
  TopoDS_TWire()

    = default;

  //! Returns WIRE.
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  //! Returns an empty TWire.
  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TWire, TopoDS_TShape)
};
