#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaShellShearStiffness.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaShellShearStiffness.hpp>

//=================================================================================================

RWStepFEA_RWFeaShellShearStiffness::RWStepFEA_RWFeaShellShearStiffness() = default;

//=================================================================================================

void RWStepFEA_RWFeaShellShearStiffness::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepFEA_FeaShellShearStiffness>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "fea_shell_shear_stiffness"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of FeaShellShearStiffness

  StepFEA_SymmetricTensor22d aFeaConstants;
  data->ReadEntity(num, 2, "fea_constants", ach, aFeaConstants);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aFeaConstants);
}

//=================================================================================================

void RWStepFEA_RWFeaShellShearStiffness::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepFEA_FeaShellShearStiffness>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of FeaShellShearStiffness

  SW.Send(ent->FeaConstants().Value());
}

//=================================================================================================

void RWStepFEA_RWFeaShellShearStiffness::Share(
  const occ::handle<StepFEA_FeaShellShearStiffness>& ent,
  Interface_EntityIterator&                          iter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of FeaShellShearStiffness

  iter.AddItem(ent->FeaConstants().Value());
}
