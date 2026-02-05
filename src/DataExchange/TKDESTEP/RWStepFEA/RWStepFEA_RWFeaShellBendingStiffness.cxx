#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaShellBendingStiffness.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaShellBendingStiffness.hpp>

//=================================================================================================

RWStepFEA_RWFeaShellBendingStiffness::RWStepFEA_RWFeaShellBendingStiffness() = default;

//=================================================================================================

void RWStepFEA_RWFeaShellBendingStiffness::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepFEA_FeaShellBendingStiffness>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "fea_shell_bending_stiffness"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of FeaShellBendingStiffness

  StepFEA_SymmetricTensor42d aFeaConstants;
  data->ReadEntity(num, 2, "fea_constants", ach, aFeaConstants);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aFeaConstants);
}

//=================================================================================================

void RWStepFEA_RWFeaShellBendingStiffness::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepFEA_FeaShellBendingStiffness>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of FeaShellBendingStiffness

  SW.Send(ent->FeaConstants().Value());
}

//=================================================================================================

void RWStepFEA_RWFeaShellBendingStiffness::Share(
  const occ::handle<StepFEA_FeaShellBendingStiffness>& ent,
  Interface_EntityIterator&                            iter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of FeaShellBendingStiffness

  iter.AddItem(ent->FeaConstants().Value());
}
