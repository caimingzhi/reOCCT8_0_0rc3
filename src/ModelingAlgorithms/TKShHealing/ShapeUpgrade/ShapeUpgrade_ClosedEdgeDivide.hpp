#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ShapeUpgrade_EdgeDivide.hpp>
class TopoDS_Edge;

class ShapeUpgrade_ClosedEdgeDivide : public ShapeUpgrade_EdgeDivide
{

public:
  Standard_EXPORT ShapeUpgrade_ClosedEdgeDivide();

  Standard_EXPORT bool Compute(const TopoDS_Edge& anEdge) override;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_ClosedEdgeDivide, ShapeUpgrade_EdgeDivide)
};
