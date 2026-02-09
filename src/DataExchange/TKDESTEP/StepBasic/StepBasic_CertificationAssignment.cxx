#include <Standard_Type.hpp>
#include <StepBasic_Certification.hpp>
#include <StepBasic_CertificationAssignment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_CertificationAssignment, Standard_Transient)

StepBasic_CertificationAssignment::StepBasic_CertificationAssignment() = default;

void StepBasic_CertificationAssignment::Init(
  const occ::handle<StepBasic_Certification>& aAssignedCertification)
{

  theAssignedCertification = aAssignedCertification;
}

occ::handle<StepBasic_Certification> StepBasic_CertificationAssignment::AssignedCertification()
  const
{
  return theAssignedCertification;
}

void StepBasic_CertificationAssignment::SetAssignedCertification(
  const occ::handle<StepBasic_Certification>& aAssignedCertification)
{
  theAssignedCertification = aAssignedCertification;
}
