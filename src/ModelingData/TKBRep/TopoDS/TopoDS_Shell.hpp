#pragma once

#include <TopoDS_Shape.hpp>

//! Describes a shell which
//! - references an underlying shell with the potential to
//! be given a location and an orientation
//! - has a location for the underlying shell, giving its
//! placement in the local coordinate system
//! - has an orientation for the underlying shell, in terms
//! of its geometry (as opposed to orientation in relation to other shapes).
class TopoDS_Shell : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an Undefined Shell.
  TopoDS_Shell() = default;
};

namespace std
{
  template <>
  struct hash<TopoDS_Shell>
  {
    size_t operator()(const TopoDS_Shell& theShape) const
    {
      return std::hash<TopoDS_Shape>{}(theShape);
    }
  };
} // namespace std
