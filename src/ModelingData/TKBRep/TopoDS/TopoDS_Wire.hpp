#pragma once

#include <TopoDS_Shape.hpp>

//! Describes a wire which
//! - references an underlying wire with the potential to
//! be given a location and an orientation
//! - has a location for the underlying wire, giving its
//! placement in the local coordinate system
//! - has an orientation for the underlying wire, in terms
//! of its geometry (as opposed to orientation in relation to other shapes).
class TopoDS_Wire : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Undefined Wire.
  TopoDS_Wire() = default;
};

namespace std
{
  template <>
  struct hash<TopoDS_Wire>
  {
    size_t operator()(const TopoDS_Wire& theShape) const
    {
      return std::hash<TopoDS_Shape>{}(theShape);
    }
  };
} // namespace std
