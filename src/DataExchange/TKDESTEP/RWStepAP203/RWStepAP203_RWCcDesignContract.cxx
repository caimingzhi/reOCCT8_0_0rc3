#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP203_RWCcDesignContract.hpp"
#include <StepAP203_CcDesignContract.hpp>
#include <StepAP203_ContractedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Contract.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepAP203_RWCcDesignContract::RWStepAP203_RWCcDesignContract() = default;

//=================================================================================================

void RWStepAP203_RWCcDesignContract::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepAP203_CcDesignContract>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "cc_design_contract"))
    return;

  // Inherited fields of ContractAssignment

  occ::handle<StepBasic_Contract> aContractAssignment_AssignedContract;
  data->ReadEntity(num,
                   1,
                   "contract_assignment.assigned_contract",
                   ach,
                   STANDARD_TYPE(StepBasic_Contract),
                   aContractAssignment_AssignedContract);

  // Own fields of CcDesignContract

  occ::handle<NCollection_HArray1<StepAP203_ContractedItem>> aItems;
  int                                                        sub2 = 0;
  if (data->ReadSubList(num, 2, "items", ach, sub2))
  {
    int num2 = sub2;
    int nb0  = data->NbParams(num2);
    aItems   = new NCollection_HArray1<StepAP203_ContractedItem>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepAP203_ContractedItem anIt0;
      data->ReadEntity(num2, i0, "items", ach, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aContractAssignment_AssignedContract, aItems);
}

//=================================================================================================

void RWStepAP203_RWCcDesignContract::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepAP203_CcDesignContract>& ent) const
{

  // Inherited fields of ContractAssignment

  SW.Send(ent->StepBasic_ContractAssignment::AssignedContract());

  // Own fields of CcDesignContract

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->Items()->Length(); i1++)
  {
    StepAP203_ContractedItem Var0 = ent->Items()->Value(i1);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepAP203_RWCcDesignContract::Share(const occ::handle<StepAP203_CcDesignContract>& ent,
                                           Interface_EntityIterator& iter) const
{

  // Inherited fields of ContractAssignment

  iter.AddItem(ent->StepBasic_ContractAssignment::AssignedContract());

  // Own fields of CcDesignContract

  for (int i2 = 1; i2 <= ent->Items()->Length(); i2++)
  {
    StepAP203_ContractedItem Var0 = ent->Items()->Value(i2);
    iter.AddItem(Var0.Value());
  }
}
