#pragma once

#include <TopoDS_Shape.hpp>

class TopoDS_CompSolid : public TopoDS_Shape
{
public:
  DEFINE_STANDARD_ALLOC

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
