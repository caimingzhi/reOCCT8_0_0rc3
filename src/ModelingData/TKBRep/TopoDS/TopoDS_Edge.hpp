#pragma once

#include <TopoDS_Shape.hpp>

//! Describes an edge which
//! - references an underlying edge with the potential to
//! be given a location and an orientation
//! - has a location for the underlying edge, giving its
//! placement in the local coordinate system
//! - has an orientation for the underlying edge, in terms
//! of its geometry (as opposed to orientation in
//! relation to other shapes).
class TopoDS_Edge : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Undefined Edge.
  TopoDS_Edge() = default;
};

namespace std
{
  template <>
  struct hash<TopoDS_Edge>
  {
    size_t operator()(const TopoDS_Edge& theShape) const
    {
      return std::hash<TopoDS_Shape>{}(theShape);
    }
  };
} // namespace std
