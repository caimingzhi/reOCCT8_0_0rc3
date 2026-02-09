#include <StepAP203_CcDesignSecurityClassification.hpp>
#include <StepBasic_SecurityClassification.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_CcDesignSecurityClassification,
                           StepBasic_SecurityClassificationAssignment)

StepAP203_CcDesignSecurityClassification::StepAP203_CcDesignSecurityClassification() = default;

void StepAP203_CcDesignSecurityClassification::Init(
  const occ::handle<StepBasic_SecurityClassification>&
    aSecurityClassificationAssignment_AssignedSecurityClassification,
  const occ::handle<NCollection_HArray1<StepAP203_ClassifiedItem>>& aItems)
{
  StepBasic_SecurityClassificationAssignment::Init(
    aSecurityClassificationAssignment_AssignedSecurityClassification);

  theItems = aItems;
}

occ::handle<NCollection_HArray1<StepAP203_ClassifiedItem>>
  StepAP203_CcDesignSecurityClassification::Items() const
{
  return theItems;
}

void StepAP203_CcDesignSecurityClassification::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_ClassifiedItem>>& aItems)
{
  theItems = aItems;
}
