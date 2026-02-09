#pragma once

#include <TopoDS_Shape.hpp>

class TopoDS_Shell : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

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
