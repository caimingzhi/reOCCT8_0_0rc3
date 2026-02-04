#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

//! A Topological part of 3D space, bounded by shells,
//! edges and vertices.
class TopoDS_TSolid : public TopoDS_TShape
{
public:
  //! Creates an empty TSolid.
  TopoDS_TSolid() { Orientable(false); }

  //! returns SOLID.
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  //! Returns an empty TSolid.
  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TSolid, TopoDS_TShape)
};

