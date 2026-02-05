#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWContractAssignment.hpp"
#include <StepBasic_Contract.hpp>
#include <StepBasic_ContractAssignment.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWContractAssignment::RWStepBasic_RWContractAssignment() = default;

//=================================================================================================

void RWStepBasic_RWContractAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepBasic_ContractAssignment>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "contract_assignment"))
    return;

  // Own fields of ContractAssignment

  occ::handle<StepBasic_Contract> aAssignedContract;
  data->ReadEntity(num,
                   1,
                   "assigned_contract",
                   ach,
                   STANDARD_TYPE(StepBasic_Contract),
                   aAssignedContract);

  // Initialize entity
  ent->Init(aAssignedContract);
}

//=================================================================================================

void RWStepBasic_RWContractAssignment::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepBasic_ContractAssignment>& ent) const
{

  // Own fields of ContractAssignment

  SW.Send(ent->AssignedContract());
}

//=================================================================================================

void RWStepBasic_RWContractAssignment::Share(const occ::handle<StepBasic_ContractAssignment>& ent,
                                             Interface_EntityIterator& iter) const
{

  // Own fields of ContractAssignment

  iter.AddItem(ent->AssignedContract());
}
