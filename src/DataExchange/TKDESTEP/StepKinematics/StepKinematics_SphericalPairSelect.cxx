

#include <StepKinematics_SphericalPairSelect.hpp>
#include <StepKinematics_SphericalPair.hpp>
#include <StepKinematics_SphericalPairWithPin.hpp>

StepKinematics_SphericalPairSelect::StepKinematics_SphericalPairSelect() = default;

int StepKinematics_SphericalPairSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepKinematics_SphericalPair)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepKinematics_SphericalPairWithPin)))
    return 2;
  return 0;
}

occ::handle<StepKinematics_SphericalPair> StepKinematics_SphericalPairSelect::SphericalPair() const
{
  return occ::down_cast<StepKinematics_SphericalPair>(Value());
}

occ::handle<StepKinematics_SphericalPairWithPin> StepKinematics_SphericalPairSelect::
  SphericalPairWithPin() const
{
  return occ::down_cast<StepKinematics_SphericalPairWithPin>(Value());
}
