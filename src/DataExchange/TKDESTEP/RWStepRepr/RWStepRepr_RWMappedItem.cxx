

#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWMappedItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_MappedItem.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_RepresentationMap.hpp>

RWStepRepr_RWMappedItem::RWStepRepr_RWMappedItem() = default;

void RWStepRepr_RWMappedItem::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                       const int                                   num,
                                       occ::handle<Interface_Check>&               ach,
                                       const occ::handle<StepRepr_MappedItem>&     ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "mapped_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepRepr_RepresentationMap> aMappingSource;

  data->ReadEntity(num,
                   2,
                   "mapping_source",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationMap),
                   aMappingSource);

  occ::handle<StepRepr_RepresentationItem> aMappingTarget;

  data->ReadEntity(num,
                   3,
                   "mapping_target",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationItem),
                   aMappingTarget);

  ent->Init(aName, aMappingSource, aMappingTarget);
}

void RWStepRepr_RWMappedItem::WriteStep(StepData_StepWriter&                    SW,
                                        const occ::handle<StepRepr_MappedItem>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->MappingSource());

  SW.Send(ent->MappingTarget());
}

void RWStepRepr_RWMappedItem::Share(const occ::handle<StepRepr_MappedItem>& ent,
                                    Interface_EntityIterator&               iter) const
{

  iter.GetOneItem(ent->MappingSource());

  iter.GetOneItem(ent->MappingTarget());
}
