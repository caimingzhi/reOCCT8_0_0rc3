#pragma once


#include <Standard.hpp>

#include <StepAP203_CertifiedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_CertificationAssignment.hpp>
class StepBasic_Certification;

//! Representation of STEP entity CcDesignCertification
class StepAP203_CcDesignCertification : public StepBasic_CertificationAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP203_CcDesignCertification();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Certification>& aCertificationAssignment_AssignedCertification,
    const occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>>& aItems);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>> Items() const;

  //! Set field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignCertification, StepBasic_CertificationAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_CertifiedItem>> theItems;
};

