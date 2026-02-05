#pragma once

#include <Standard.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

//! A topological part of a curve in 2D or 3D, the
//! boundary is a set of oriented Vertices.
class TopoDS_TEdge : public TopoDS_TShape
{
public:
  //! Returns EDGE.
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TEdge, TopoDS_TShape)

protected:
  //! Construct an edge.
  TopoDS_TEdge() {}
};
