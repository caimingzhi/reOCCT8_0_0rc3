#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Certification;

//! Representation of STEP entity CertificationAssignment
class StepBasic_CertificationAssignment : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_CertificationAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepBasic_Certification>& aAssignedCertification);

  //! Returns field AssignedCertification
  Standard_EXPORT occ::handle<StepBasic_Certification> AssignedCertification() const;

  //! Set field AssignedCertification
  Standard_EXPORT void SetAssignedCertification(
    const occ::handle<StepBasic_Certification>& AssignedCertification);

  DEFINE_STANDARD_RTTIEXT(StepBasic_CertificationAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Certification> theAssignedCertification;
};
