#include <Standard_Type.hpp>
#include <StepBasic_Contract.hpp>
#include <StepBasic_ContractAssignment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ContractAssignment, Standard_Transient)

StepBasic_ContractAssignment::StepBasic_ContractAssignment() = default;

void StepBasic_ContractAssignment::Init(const occ::handle<StepBasic_Contract>& aAssignedContract)
{

  theAssignedContract = aAssignedContract;
}

occ::handle<StepBasic_Contract> StepBasic_ContractAssignment::AssignedContract() const
{
  return theAssignedContract;
}

void StepBasic_ContractAssignment::SetAssignedContract(
  const occ::handle<StepBasic_Contract>& aAssignedContract)
{
  theAssignedContract = aAssignedContract;
}
