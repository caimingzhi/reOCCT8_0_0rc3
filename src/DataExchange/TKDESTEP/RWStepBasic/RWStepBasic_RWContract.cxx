#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWContract.hpp"
#include <StepBasic_Contract.hpp>
#include <StepBasic_ContractType.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWContract::RWStepBasic_RWContract() = default;

//=================================================================================================

void RWStepBasic_RWContract::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepBasic_Contract>&      ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "contract"))
    return;

  // Own fields of Contract

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aPurpose;
  data->ReadString(num, 2, "purpose", ach, aPurpose);

  occ::handle<StepBasic_ContractType> aKind;
  data->ReadEntity(num, 3, "kind", ach, STANDARD_TYPE(StepBasic_ContractType), aKind);

  // Initialize entity
  ent->Init(aName, aPurpose, aKind);
}

//=================================================================================================

void RWStepBasic_RWContract::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepBasic_Contract>& ent) const
{

  // Own fields of Contract

  SW.Send(ent->Name());

  SW.Send(ent->Purpose());

  SW.Send(ent->Kind());
}

//=================================================================================================

void RWStepBasic_RWContract::Share(const occ::handle<StepBasic_Contract>& ent,
                                   Interface_EntityIterator&              iter) const
{

  // Own fields of Contract

  iter.AddItem(ent->Kind());
}
