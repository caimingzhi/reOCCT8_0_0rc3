#pragma once


#include <Standard.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

// resolve name collisions with X11 headers
#ifdef Convex
  #undef Convex
#endif

//! A Vertex is a topological point in two or three dimensions.
class TopoDS_TVertex : public TopoDS_TShape
{
public:
  //! Returns VERTEX.
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TVertex, TopoDS_TShape)

protected:
  //! Construct a vertex.
  TopoDS_TVertex()

  {
    Closed(true);
    Convex(true);
  }
};

