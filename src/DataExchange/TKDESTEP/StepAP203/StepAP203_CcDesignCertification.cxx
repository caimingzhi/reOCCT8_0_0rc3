#include <StepAP203_CcDesignCertification.hpp>
#include <StepBasic_Certification.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_CcDesignCertification, StepBasic_CertificationAssignment)

//=================================================================================================

StepAP203_CcDesignCertification::StepAP203_CcDesignCertification() = default;

//=================================================================================================

void StepAP203_CcDesignCertification::Init(
  const occ::handle<StepBasic_Certification>& aCertificationAssignment_AssignedCertification,
  const occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>>& aItems)
{
  StepBasic_CertificationAssignment::Init(aCertificationAssignment_AssignedCertification);

  theItems = aItems;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>> StepAP203_CcDesignCertification::Items()
  const
{
  return theItems;
}

//=================================================================================================

void StepAP203_CcDesignCertification::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>>& aItems)
{
  theItems = aItems;
}
