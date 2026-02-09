#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepBuilderAPI_MakeShape.hpp>
class TopoDS_Shape;

class BRepPrimAPI_MakeSweep : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual TopoDS_Shape FirstShape() = 0;

  Standard_EXPORT virtual TopoDS_Shape LastShape() = 0;
};
