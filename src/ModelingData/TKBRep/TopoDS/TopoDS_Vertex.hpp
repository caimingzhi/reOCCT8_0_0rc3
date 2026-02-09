#pragma once

#include <TopoDS_Shape.hpp>

class TopoDS_Vertex : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

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
