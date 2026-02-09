#pragma once

#include <TopoDS_Shape.hpp>

class TopoDS_Wire : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

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
