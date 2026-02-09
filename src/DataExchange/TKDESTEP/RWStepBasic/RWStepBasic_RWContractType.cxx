#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWContractType.hpp"
#include <StepBasic_ContractType.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWContractType::RWStepBasic_RWContractType() = default;

void RWStepBasic_RWContractType::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepBasic_ContractType>&  ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "contract_type"))
    return;

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 1, "description", ach, aDescription);

  ent->Init(aDescription);
}

void RWStepBasic_RWContractType::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepBasic_ContractType>& ent) const
{

  SW.Send(ent->Description());
}

void RWStepBasic_RWContractType::Share(const occ::handle<StepBasic_ContractType>&,
                                       Interface_EntityIterator&) const
{
}
