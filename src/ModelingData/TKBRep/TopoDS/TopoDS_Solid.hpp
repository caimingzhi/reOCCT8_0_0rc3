#pragma once

#include <TopoDS_Shape.hpp>

//! Describes a solid shape which
//! - references an underlying solid shape with the
//! potential to be given a location and an orientation
//! - has a location for the underlying shape, giving its
//! placement in the local coordinate system
//! - has an orientation for the underlying shape, in
//! terms of its geometry (as opposed to orientation in
//! relation to other shapes).
class TopoDS_Solid : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an Undefined Solid.
  TopoDS_Solid() = default;
};

namespace std
{
  template <>
  struct hash<TopoDS_Solid>
  {
    size_t operator()(const TopoDS_Solid& theShape) const
    {
      return std::hash<TopoDS_Shape>{}(theShape);
    }
  };
} // namespace std
