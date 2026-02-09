

#include <StepKinematics_RigidPlacement.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_SuParameters.hpp>

StepKinematics_RigidPlacement::StepKinematics_RigidPlacement() = default;

int StepKinematics_RigidPlacement::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Axis2Placement3d)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_SuParameters)))
    return 2;
  return 0;
}

occ::handle<StepGeom_Axis2Placement3d> StepKinematics_RigidPlacement::Axis2Placement3d() const
{
  return occ::down_cast<StepGeom_Axis2Placement3d>(Value());
}

occ::handle<StepGeom_SuParameters> StepKinematics_RigidPlacement::SuParameters() const
{
  return occ::down_cast<StepGeom_SuParameters>(Value());
}
