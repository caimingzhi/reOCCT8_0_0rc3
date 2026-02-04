#pragma once


#include <TopoDS_Shape.hpp>

//! Describes a vertex which
//! - references an underlying vertex with the potential
//! to be given a location and an orientation
//! - has a location for the underlying vertex, giving its
//! placement in the local coordinate system
//! - has an orientation for the underlying vertex, in
//! terms of its geometry (as opposed to orientation in
//! relation to other shapes).
class TopoDS_Vertex : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Undefined Vertex.
  TopoDS_Vertex() = default;
};

namespace std
{
template <>
struct hash<TopoDS_Vertex>
{
  size_t operator()(const TopoDS_Vertex& theShape) const
  {
    return std::hash<TopoDS_Shape>{}(theShape);
  }
};
} // namespace std

