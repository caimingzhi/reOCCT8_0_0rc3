#include <StepAP203_CcDesignContract.hpp>
#include <StepBasic_Contract.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_CcDesignContract, StepBasic_ContractAssignment)

//=================================================================================================

StepAP203_CcDesignContract::StepAP203_CcDesignContract() = default;

//=================================================================================================

void StepAP203_CcDesignContract::Init(
  const occ::handle<StepBasic_Contract>& aContractAssignment_AssignedContract,
  const occ::handle<NCollection_HArray1<StepAP203_ContractedItem>>& aItems)
{
  StepBasic_ContractAssignment::Init(aContractAssignment_AssignedContract);

  theItems = aItems;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepAP203_ContractedItem>> StepAP203_CcDesignContract::Items() const
{
  return theItems;
}

//=================================================================================================

void StepAP203_CcDesignContract::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_ContractedItem>>& aItems)
{
  theItems = aItems;
}
