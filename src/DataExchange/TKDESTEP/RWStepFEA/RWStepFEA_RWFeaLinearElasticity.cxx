#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaLinearElasticity.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaLinearElasticity.hpp>

//=================================================================================================

RWStepFEA_RWFeaLinearElasticity::RWStepFEA_RWFeaLinearElasticity() = default;

//=================================================================================================

void RWStepFEA_RWFeaLinearElasticity::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepFEA_FeaLinearElasticity>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "fea_linear_elasticity"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of FeaLinearElasticity

  StepFEA_SymmetricTensor43d aFeaConstants;
  data->ReadEntity(num, 2, "fea_constants", ach, aFeaConstants);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aFeaConstants);
}

//=================================================================================================

void RWStepFEA_RWFeaLinearElasticity::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepFEA_FeaLinearElasticity>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of FeaLinearElasticity

  SW.Send(ent->FeaConstants().Value());
}

//=================================================================================================

void RWStepFEA_RWFeaLinearElasticity::Share(const occ::handle<StepFEA_FeaLinearElasticity>& ent,
                                            Interface_EntityIterator& iter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of FeaLinearElasticity

  iter.AddItem(ent->FeaConstants().Value());
}
