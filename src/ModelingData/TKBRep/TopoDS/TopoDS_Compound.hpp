#pragma once

#include <TopoDS_Shape.hpp>

//! Describes a compound which
//! - references an underlying compound with the
//! potential to be given a location and an orientation
//! - has a location for the underlying compound, giving
//! its placement in the local coordinate system
//! - has an orientation for the underlying compound, in
//! terms of its geometry (as opposed to orientation in
//! relation to other shapes).
//! Casts shape S to the more specialized return type, Compound.
class TopoDS_Compound : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an Undefined Compound.
  TopoDS_Compound() = default;
};

namespace std
{
  template <>
  struct hash<TopoDS_Compound>
  {
    size_t operator()(const TopoDS_Compound& theShape) const
    {
      return std::hash<TopoDS_Shape>{}(theShape);
    }
  };
} // namespace std
