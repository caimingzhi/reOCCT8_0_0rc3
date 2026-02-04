#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_SecurityClassification;

class StepBasic_SecurityClassificationAssignment : public Standard_Transient
{

public:
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_SecurityClassification>& aAssignedSecurityClassification);

  Standard_EXPORT void SetAssignedSecurityClassification(
    const occ::handle<StepBasic_SecurityClassification>& aAssignedSecurityClassification);

  Standard_EXPORT occ::handle<StepBasic_SecurityClassification> AssignedSecurityClassification()
    const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SecurityClassificationAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_SecurityClassification> assignedSecurityClassification;
};

