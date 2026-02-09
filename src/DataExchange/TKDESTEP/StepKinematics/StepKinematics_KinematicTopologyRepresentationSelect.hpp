#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepKinematics_KinematicTopologyDirectedStructure;
class StepKinematics_KinematicTopologyNetworkStructure;
class StepKinematics_KinematicTopologyStructure;

class StepKinematics_KinematicTopologyRepresentationSelect : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepKinematics_KinematicTopologyRepresentationSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepKinematics_KinematicTopologyDirectedStructure>
                  KinematicTopologyDirectedStructure() const;

  Standard_EXPORT occ::handle<StepKinematics_KinematicTopologyNetworkStructure>
                  KinematicTopologyNetworkStructure() const;

  Standard_EXPORT occ::handle<StepKinematics_KinematicTopologyStructure>
                  KinematicTopologyStructure() const;
};
