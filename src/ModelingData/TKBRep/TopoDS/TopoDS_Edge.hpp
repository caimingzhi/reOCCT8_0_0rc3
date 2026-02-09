#pragma once

#include <TopoDS_Shape.hpp>

class TopoDS_Edge : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

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
