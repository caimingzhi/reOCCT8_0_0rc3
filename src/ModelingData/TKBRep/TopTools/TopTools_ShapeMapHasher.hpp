#pragma once


#include <TopoDS_Shape.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

//! Hash tool, used for generating maps of shapes in topology.
class TopTools_ShapeMapHasher
{
public:
  DEFINE_STANDARD_ALLOC;

  size_t operator()(const TopoDS_Shape& theShape) const noexcept
  {
    return std::hash<TopoDS_Shape>{}(theShape);
  }

  bool operator()(const TopoDS_Shape& S1, const TopoDS_Shape& S2) const noexcept
  {
    return S1.IsSame(S2);
  }
};

