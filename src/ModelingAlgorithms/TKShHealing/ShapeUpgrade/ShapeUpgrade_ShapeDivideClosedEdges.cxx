#include <ShapeUpgrade_ClosedEdgeDivide.hpp>
#include <ShapeUpgrade_FaceDivide.hpp>
#include <ShapeUpgrade_ShapeDivideClosedEdges.hpp>
#include <ShapeUpgrade_SplitSurface.hpp>
#include <ShapeUpgrade_WireDivide.hpp>
#include <TopoDS_Shape.hpp>

ShapeUpgrade_ShapeDivideClosedEdges::ShapeUpgrade_ShapeDivideClosedEdges(const TopoDS_Shape& S)
    : ShapeUpgrade_ShapeDivide(S)
{
  SetNbSplitPoints(1);
}

void ShapeUpgrade_ShapeDivideClosedEdges::SetNbSplitPoints(const int)
{
  occ::handle<ShapeUpgrade_ClosedEdgeDivide> tool  = new ShapeUpgrade_ClosedEdgeDivide;
  occ::handle<ShapeUpgrade_WireDivide>       wtool = new ShapeUpgrade_WireDivide;
  wtool->SetEdgeDivideTool(tool);
  occ::handle<ShapeUpgrade_FaceDivide> ftool = new ShapeUpgrade_FaceDivide;
  ftool->SetWireDivideTool(wtool);
  ftool->SetSplitSurfaceTool(nullptr);
  SetSplitFaceTool(ftool);
}
