#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaMoistureAbsorption.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaMoistureAbsorption.hpp>

RWStepFEA_RWFeaMoistureAbsorption::RWStepFEA_RWFeaMoistureAbsorption() = default;

void RWStepFEA_RWFeaMoistureAbsorption::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepFEA_FeaMoistureAbsorption>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "fea_moisture_absorption"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  StepFEA_SymmetricTensor23d aFeaConstants;
  data->ReadEntity(num, 2, "fea_constants", ach, aFeaConstants);

  ent->Init(aRepresentationItem_Name, aFeaConstants);
}

void RWStepFEA_RWFeaMoistureAbsorption::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepFEA_FeaMoistureAbsorption>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->FeaConstants().Value());
}

void RWStepFEA_RWFeaMoistureAbsorption::Share(const occ::handle<StepFEA_FeaMoistureAbsorption>& ent,
                                              Interface_EntityIterator& iter) const
{

  iter.AddItem(ent->FeaConstants().Value());
}
