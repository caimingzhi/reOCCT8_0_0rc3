#pragma once

#include <Standard.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

class TopoDS_TEdge : public TopoDS_TShape
{
public:
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TEdge, TopoDS_TShape)

protected:
  TopoDS_TEdge() {}
};
