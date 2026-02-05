#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaShellMembraneBendingCouplingStiffness.hpp>

//=================================================================================================

RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness::
  RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness() = default;

//=================================================================================================

void RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness::ReadStep(
  const occ::handle<StepData_StepReaderData>&                          data,
  const int                                                            num,
  occ::handle<Interface_Check>&                                        ach,
  const occ::handle<StepFEA_FeaShellMembraneBendingCouplingStiffness>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "fea_shell_membrane_bending_coupling_stiffness"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of FeaShellMembraneBendingCouplingStiffness

  StepFEA_SymmetricTensor42d aFeaConstants;
  data->ReadEntity(num, 2, "fea_constants", ach, aFeaConstants);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aFeaConstants);
}

//=================================================================================================

void RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness::WriteStep(
  StepData_StepWriter&                                                 SW,
  const occ::handle<StepFEA_FeaShellMembraneBendingCouplingStiffness>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of FeaShellMembraneBendingCouplingStiffness

  SW.Send(ent->FeaConstants().Value());
}

//=================================================================================================

void RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness::Share(
  const occ::handle<StepFEA_FeaShellMembraneBendingCouplingStiffness>& ent,
  Interface_EntityIterator&                                            iter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of FeaShellMembraneBendingCouplingStiffness

  iter.AddItem(ent->FeaConstants().Value());
}
