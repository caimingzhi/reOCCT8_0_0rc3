

#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWRepresentationMap.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_RepresentationMap.hpp>

RWStepRepr_RWRepresentationMap::RWStepRepr_RWRepresentationMap() = default;

void RWStepRepr_RWRepresentationMap::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepRepr_RepresentationMap>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "representation_map"))
    return;

  occ::handle<StepRepr_RepresentationItem> aMappingOrigin;

  data->ReadEntity(num,
                   1,
                   "mapping_origin",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationItem),
                   aMappingOrigin);

  occ::handle<StepRepr_Representation> aMappedRepresentation;

  data->ReadEntity(num,
                   2,
                   "mapped_representation",
                   ach,
                   STANDARD_TYPE(StepRepr_Representation),
                   aMappedRepresentation);

  ent->Init(aMappingOrigin, aMappedRepresentation);
}

void RWStepRepr_RWRepresentationMap::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepRepr_RepresentationMap>& ent) const
{

  SW.Send(ent->MappingOrigin());

  SW.Send(ent->MappedRepresentation());
}

void RWStepRepr_RWRepresentationMap::Share(const occ::handle<StepRepr_RepresentationMap>& ent,
                                           Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->MappingOrigin());

  iter.GetOneItem(ent->MappedRepresentation());
}
