#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_VersionedActionRequest;

class StepBasic_ActionRequestAssignment : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ActionRequestAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_VersionedActionRequest>& aAssignedActionRequest);

  Standard_EXPORT occ::handle<StepBasic_VersionedActionRequest> AssignedActionRequest() const;

  Standard_EXPORT void SetAssignedActionRequest(
    const occ::handle<StepBasic_VersionedActionRequest>& AssignedActionRequest);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ActionRequestAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_VersionedActionRequest> theAssignedActionRequest;
};
