#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaRepresentationItem.hpp>

//=================================================================================================

RWStepFEA_RWFeaRepresentationItem::RWStepFEA_RWFeaRepresentationItem() = default;

//=================================================================================================

void RWStepFEA_RWFeaRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepFEA_FeaRepresentationItem>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "fea_representation_item"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Initialize entity
  ent->Init(aRepresentationItem_Name);
}

//=================================================================================================

void RWStepFEA_RWFeaRepresentationItem::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepFEA_FeaRepresentationItem>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());
}

//=================================================================================================

void RWStepFEA_RWFeaRepresentationItem::Share(const occ::handle<StepFEA_FeaRepresentationItem>&,
                                              Interface_EntityIterator&) const
{
  // Inherited fields of RepresentationItem
}
