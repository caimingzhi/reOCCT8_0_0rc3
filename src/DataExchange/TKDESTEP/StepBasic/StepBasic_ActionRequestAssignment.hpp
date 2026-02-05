#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_VersionedActionRequest;

//! Representation of STEP entity ActionRequestAssignment
class StepBasic_ActionRequestAssignment : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ActionRequestAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_VersionedActionRequest>& aAssignedActionRequest);

  //! Returns field AssignedActionRequest
  Standard_EXPORT occ::handle<StepBasic_VersionedActionRequest> AssignedActionRequest() const;

  //! Set field AssignedActionRequest
  Standard_EXPORT void SetAssignedActionRequest(
    const occ::handle<StepBasic_VersionedActionRequest>& AssignedActionRequest);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ActionRequestAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_VersionedActionRequest> theAssignedActionRequest;
};
