#include <ShapeUpgrade_FaceDivide.hpp>
#include <ShapeUpgrade_ShapeDivideAngle.hpp>
#include <ShapeUpgrade_SplitSurfaceAngle.hpp>
#include <ShapeUpgrade_WireDivide.hpp>
#include <TopoDS_Shape.hpp>

ShapeUpgrade_ShapeDivideAngle::ShapeUpgrade_ShapeDivideAngle(const double MaxAngle)
{
  InitTool(MaxAngle);
}

ShapeUpgrade_ShapeDivideAngle::ShapeUpgrade_ShapeDivideAngle(const double        MaxAngle,
                                                             const TopoDS_Shape& S)
    : ShapeUpgrade_ShapeDivide(S)
{
  InitTool(MaxAngle);
}

void ShapeUpgrade_ShapeDivideAngle::InitTool(const double MaxAngle)
{
  occ::handle<ShapeUpgrade_FaceDivide> tool = GetSplitFaceTool();
  tool->SetSplitSurfaceTool(new ShapeUpgrade_SplitSurfaceAngle(MaxAngle));
  tool->SetWireDivideTool(nullptr);
  SetSplitFaceTool(tool);
}

void ShapeUpgrade_ShapeDivideAngle::SetMaxAngle(const double MaxAngle)
{
  InitTool(MaxAngle);
}

double ShapeUpgrade_ShapeDivideAngle::MaxAngle() const
{
  occ::handle<ShapeUpgrade_FaceDivide> faceTool = GetSplitFaceTool();
  if (faceTool.IsNull())
    return 0.;
  occ::handle<ShapeUpgrade_SplitSurfaceAngle> tool =
    occ::down_cast<ShapeUpgrade_SplitSurfaceAngle>(faceTool->GetSplitSurfaceTool());
  return (tool.IsNull() ? 0. : tool->MaxAngle());
}
