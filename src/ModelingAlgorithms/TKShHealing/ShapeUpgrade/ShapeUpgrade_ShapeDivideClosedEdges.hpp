#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <ShapeUpgrade_ShapeDivide.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;

class ShapeUpgrade_ShapeDivideClosedEdges : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeUpgrade_ShapeDivideClosedEdges(const TopoDS_Shape& S);

  Standard_EXPORT void SetNbSplitPoints(const int num);
};
