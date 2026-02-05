#pragma once

#include <Standard.hpp>

#include <StepAP203_ContractedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ContractAssignment.hpp>
class StepBasic_Contract;

//! Representation of STEP entity CcDesignContract
class StepAP203_CcDesignContract : public StepBasic_ContractAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP203_CcDesignContract();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Contract>& aContractAssignment_AssignedContract,
    const occ::handle<NCollection_HArray1<StepAP203_ContractedItem>>& aItems);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_ContractedItem>> Items() const;

  //! Set field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_ContractedItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignContract, StepBasic_ContractAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_ContractedItem>> theItems;
};
