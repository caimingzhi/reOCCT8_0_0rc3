#pragma once

#include <TopoDS_Shape.hpp>

class TopoDS_Solid : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

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
