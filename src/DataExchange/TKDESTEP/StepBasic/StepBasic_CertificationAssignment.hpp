#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Certification;

class StepBasic_CertificationAssignment : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_CertificationAssignment();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Certification>& aAssignedCertification);

  Standard_EXPORT occ::handle<StepBasic_Certification> AssignedCertification() const;

  Standard_EXPORT void SetAssignedCertification(
    const occ::handle<StepBasic_Certification>& AssignedCertification);

  DEFINE_STANDARD_RTTIEXT(StepBasic_CertificationAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Certification> theAssignedCertification;
};
