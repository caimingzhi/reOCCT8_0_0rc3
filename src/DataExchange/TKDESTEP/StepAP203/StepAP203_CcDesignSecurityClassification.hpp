#pragma once

#include <Standard.hpp>

#include <StepAP203_ClassifiedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_SecurityClassificationAssignment.hpp>
class StepBasic_SecurityClassification;

//! Representation of STEP entity CcDesignSecurityClassification
class StepAP203_CcDesignSecurityClassification : public StepBasic_SecurityClassificationAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP203_CcDesignSecurityClassification();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_SecurityClassification>&
      aSecurityClassificationAssignment_AssignedSecurityClassification,
    const occ::handle<NCollection_HArray1<StepAP203_ClassifiedItem>>& aItems);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_ClassifiedItem>> Items() const;

  //! Set field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_ClassifiedItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignSecurityClassification,
                          StepBasic_SecurityClassificationAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_ClassifiedItem>> theItems;
};
