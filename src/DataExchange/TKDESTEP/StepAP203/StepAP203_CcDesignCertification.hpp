#pragma once

#include <Standard.hpp>

#include <StepAP203_CertifiedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_CertificationAssignment.hpp>
class StepBasic_Certification;

class StepAP203_CcDesignCertification : public StepBasic_CertificationAssignment
{

public:
  Standard_EXPORT StepAP203_CcDesignCertification();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Certification>& aCertificationAssignment_AssignedCertification,
    const occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>> Items() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignCertification, StepBasic_CertificationAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>> theItems;
};
