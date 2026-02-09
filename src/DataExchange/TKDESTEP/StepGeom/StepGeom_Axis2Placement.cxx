

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepGeom_Axis2Placement.hpp>
#include <StepGeom_Axis2Placement2d.hpp>
#include <StepGeom_Axis2Placement3d.hpp>

StepGeom_Axis2Placement::StepGeom_Axis2Placement() = default;

int StepGeom_Axis2Placement::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Axis2Placement2d)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Axis2Placement3d)))
    return 2;
  return 0;
}

occ::handle<StepGeom_Axis2Placement2d> StepGeom_Axis2Placement::Axis2Placement2d() const
{
  return GetCasted(StepGeom_Axis2Placement2d, Value());
}

occ::handle<StepGeom_Axis2Placement3d> StepGeom_Axis2Placement::Axis2Placement3d() const
{
  return GetCasted(StepGeom_Axis2Placement3d, Value());
}
