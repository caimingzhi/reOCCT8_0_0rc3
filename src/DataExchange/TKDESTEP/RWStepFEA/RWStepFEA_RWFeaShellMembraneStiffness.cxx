#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaShellMembraneStiffness.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaShellMembraneStiffness.hpp>

RWStepFEA_RWFeaShellMembraneStiffness::RWStepFEA_RWFeaShellMembraneStiffness() = default;

void RWStepFEA_RWFeaShellMembraneStiffness::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepFEA_FeaShellMembraneStiffness>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "fea_shell_membrane_stiffness"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  StepFEA_SymmetricTensor42d aFeaConstants;
  data->ReadEntity(num, 2, "fea_constants", ach, aFeaConstants);

  ent->Init(aRepresentationItem_Name, aFeaConstants);
}

void RWStepFEA_RWFeaShellMembraneStiffness::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepFEA_FeaShellMembraneStiffness>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->FeaConstants().Value());
}

void RWStepFEA_RWFeaShellMembraneStiffness::Share(
  const occ::handle<StepFEA_FeaShellMembraneStiffness>& ent,
  Interface_EntityIterator&                             iter) const
{

  iter.AddItem(ent->FeaConstants().Value());
}
