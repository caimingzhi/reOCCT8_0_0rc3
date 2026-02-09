#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaMaterialPropertyRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>

RWStepFEA_RWFeaMaterialPropertyRepresentationItem::
  RWStepFEA_RWFeaMaterialPropertyRepresentationItem() = default;

void RWStepFEA_RWFeaMaterialPropertyRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                       data,
  const int                                                         num,
  occ::handle<Interface_Check>&                                     ach,
  const occ::handle<StepFEA_FeaMaterialPropertyRepresentationItem>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "fea_material_property_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  ent->Init(aRepresentationItem_Name);
}

void RWStepFEA_RWFeaMaterialPropertyRepresentationItem::WriteStep(
  StepData_StepWriter&                                              SW,
  const occ::handle<StepFEA_FeaMaterialPropertyRepresentationItem>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());
}

void RWStepFEA_RWFeaMaterialPropertyRepresentationItem::Share(
  const occ::handle<StepFEA_FeaMaterialPropertyRepresentationItem>&,
  Interface_EntityIterator&) const
{
}
