#pragma once

#include <Standard.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

#ifdef Convex
  #undef Convex
#endif

class TopoDS_TVertex : public TopoDS_TShape
{
public:
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TVertex, TopoDS_TShape)

protected:
  TopoDS_TVertex()

  {
    Closed(true);
    Convex(true);
  }
};
