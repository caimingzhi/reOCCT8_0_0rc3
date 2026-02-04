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

//! Representation of STEP SELECT type KinematicTopologyRepresentationSelect
class StepKinematics_KinematicTopologyRepresentationSelect : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepKinematics_KinematicTopologyRepresentationSelect();

  //! Recognizes a kind of KinematicTopologyRepresentationSelect select type
  //! -- 1 -> KinematicTopologyDirectedStructure
  //! -- 2 -> KinematicTopologyNetworkStructure
  //! -- 3 -> KinematicTopologyStructure
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as KinematicTopologyDirectedStructure (or Null if another type)
  Standard_EXPORT occ::handle<StepKinematics_KinematicTopologyDirectedStructure>
                  KinematicTopologyDirectedStructure() const;

  //! Returns Value as KinematicTopologyNetworkStructure (or Null if another type)
  Standard_EXPORT occ::handle<StepKinematics_KinematicTopologyNetworkStructure>
                  KinematicTopologyNetworkStructure() const;

  //! Returns Value as KinematicTopologyStructure (or Null if another type)
  Standard_EXPORT occ::handle<StepKinematics_KinematicTopologyStructure>
                  KinematicTopologyStructure() const;
};
