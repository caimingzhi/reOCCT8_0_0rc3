#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

class TopoDS_TSolid : public TopoDS_TShape
{
public:
  TopoDS_TSolid() { Orientable(false); }

  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TSolid, TopoDS_TShape)
};
