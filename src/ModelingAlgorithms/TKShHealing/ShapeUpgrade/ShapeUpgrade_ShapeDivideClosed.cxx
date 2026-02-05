#include <ShapeUpgrade_ClosedFaceDivide.hpp>
#include <ShapeUpgrade_ShapeDivideClosed.hpp>
#include <ShapeUpgrade_WireDivide.hpp>
#include <TopoDS_Shape.hpp>

//=================================================================================================

ShapeUpgrade_ShapeDivideClosed::ShapeUpgrade_ShapeDivideClosed(const TopoDS_Shape& S)
    : ShapeUpgrade_ShapeDivide(S)
{
  SetNbSplitPoints(1);
}

//=================================================================================================

void ShapeUpgrade_ShapeDivideClosed::SetNbSplitPoints(const int num)
{
  occ::handle<ShapeUpgrade_ClosedFaceDivide> tool = new ShapeUpgrade_ClosedFaceDivide;
  tool->SetNbSplitPoints(num);
  tool->SetWireDivideTool(nullptr); // no splitting of wire
  SetSplitFaceTool(tool);
}
