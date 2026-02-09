#include <Precision.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeUpgrade_Tool.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_Tool, Standard_Transient)

ShapeUpgrade_Tool::ShapeUpgrade_Tool()
{
  myPrecision = myMinTol = Precision::Confusion();
  myMaxTol               = 1;
}

void ShapeUpgrade_Tool::Set(const occ::handle<ShapeUpgrade_Tool>& tool)
{
  myContext   = tool->myContext;
  myPrecision = tool->myPrecision;
  myMinTol    = tool->myMinTol;
  myMaxTol    = tool->myMaxTol;
}
