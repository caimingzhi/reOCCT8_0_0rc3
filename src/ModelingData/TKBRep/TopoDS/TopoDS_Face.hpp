#pragma once

#include <TopoDS_Shape.hpp>

class TopoDS_Face : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

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
