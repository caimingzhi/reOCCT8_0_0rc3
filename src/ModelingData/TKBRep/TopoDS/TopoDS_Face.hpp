#pragma once


#include <TopoDS_Shape.hpp>

//! Describes a face which
//! - references an underlying face with the potential to
//! be given a location and an orientation
//! - has a location for the underlying face, giving its
//! placement in the local coordinate system
//! - has an orientation for the underlying face, in terms
//! of its geometry (as opposed to orientation in relation to other shapes).
class TopoDS_Face : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Undefined Face.
  TopoDS_Face() = default;
};

namespace std
{
template <>
struct hash<TopoDS_Face>
{
  size_t operator()(const TopoDS_Face& theShape) const
  {
    return std::hash<TopoDS_Shape>{}(theShape);
  }
};
} // namespace std

