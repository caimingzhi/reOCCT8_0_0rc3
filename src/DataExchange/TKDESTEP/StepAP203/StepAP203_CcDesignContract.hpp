#pragma once

#include <Standard.hpp>

#include <StepAP203_ContractedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ContractAssignment.hpp>
class StepBasic_Contract;

class StepAP203_CcDesignContract : public StepBasic_ContractAssignment
{

public:
  Standard_EXPORT StepAP203_CcDesignContract();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Contract>& aContractAssignment_AssignedContract,
    const occ::handle<NCollection_HArray1<StepAP203_ContractedItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_ContractedItem>> Items() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_ContractedItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignContract, StepBasic_ContractAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_ContractedItem>> theItems;
};
