#pragma once

#include <TopoDS_Shape.hpp>

class TopoDS_Compound : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

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
