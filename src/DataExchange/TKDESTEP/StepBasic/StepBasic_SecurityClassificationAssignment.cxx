

#include <Standard_Type.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepBasic_SecurityClassificationAssignment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SecurityClassificationAssignment, Standard_Transient)

void StepBasic_SecurityClassificationAssignment::Init(
  const occ::handle<StepBasic_SecurityClassification>& aAssignedSecurityClassification)
{

  assignedSecurityClassification = aAssignedSecurityClassification;
}

void StepBasic_SecurityClassificationAssignment::SetAssignedSecurityClassification(
  const occ::handle<StepBasic_SecurityClassification>& aAssignedSecurityClassification)
{
  assignedSecurityClassification = aAssignedSecurityClassification;
}

occ::handle<StepBasic_SecurityClassification> StepBasic_SecurityClassificationAssignment::
  AssignedSecurityClassification() const
{
  return assignedSecurityClassification;
}
