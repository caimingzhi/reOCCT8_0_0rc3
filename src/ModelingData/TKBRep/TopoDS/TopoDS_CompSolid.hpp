#pragma once

#include <TopoDS_Shape.hpp>

//! Describes a composite solid which
//! - references an underlying composite solid with the
//! potential to be given a location and an orientation
//! - has a location for the underlying composite solid,
//! giving its placement in the local coordinate system
//! - has an orientation for the underlying composite
//! solid, in terms of its geometry (as opposed to
//! orientation in relation to other shapes).
//! Casts shape S to the more specialized return type, CompSolid.
class TopoDS_CompSolid : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an Undefined CompSolid.
  TopoDS_CompSolid() = default;
};

namespace std
{
  template <>
  struct hash<TopoDS_CompSolid>
  {
    size_t operator()(const TopoDS_CompSolid& theShape) const
    {
      return std::hash<TopoDS_Shape>{}(theShape);
    }
  };
} // namespace std
