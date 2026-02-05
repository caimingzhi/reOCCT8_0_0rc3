// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_KinematicTopologyRepresentationSelect.hpp>

#include <StepKinematics_KinematicTopologyDirectedStructure.hpp>
#include <StepKinematics_KinematicTopologyNetworkStructure.hpp>
#include <StepKinematics_KinematicTopologyStructure.hpp>

//=================================================================================================

StepKinematics_KinematicTopologyRepresentationSelect::
  StepKinematics_KinematicTopologyRepresentationSelect() = default;

//=================================================================================================

int StepKinematics_KinematicTopologyRepresentationSelect::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepKinematics_KinematicTopologyDirectedStructure)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepKinematics_KinematicTopologyNetworkStructure)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepKinematics_KinematicTopologyStructure)))
    return 3;
  return 0;
}

//=================================================================================================

occ::handle<StepKinematics_KinematicTopologyDirectedStructure>
  StepKinematics_KinematicTopologyRepresentationSelect::KinematicTopologyDirectedStructure() const
{
  return occ::down_cast<StepKinematics_KinematicTopologyDirectedStructure>(Value());
}

//=================================================================================================

occ::handle<StepKinematics_KinematicTopologyNetworkStructure>
  StepKinematics_KinematicTopologyRepresentationSelect::KinematicTopologyNetworkStructure() const
{
  return occ::down_cast<StepKinematics_KinematicTopologyNetworkStructure>(Value());
}

//=================================================================================================

occ::handle<StepKinematics_KinematicTopologyStructure>
  StepKinematics_KinematicTopologyRepresentationSelect::KinematicTopologyStructure() const
{
  return occ::down_cast<StepKinematics_KinematicTopologyStructure>(Value());
}
