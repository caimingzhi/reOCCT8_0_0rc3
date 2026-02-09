#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWAnalysisItemWithinRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>

RWStepElement_RWAnalysisItemWithinRepresentation::
  RWStepElement_RWAnalysisItemWithinRepresentation() = default;

void RWStepElement_RWAnalysisItemWithinRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                      data,
  const int                                                        num,
  occ::handle<Interface_Check>&                                    ach,
  const occ::handle<StepElement_AnalysisItemWithinRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "analysis_item_within_representation"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<StepRepr_RepresentationItem> aItem;
  data->ReadEntity(num, 3, "item", ach, STANDARD_TYPE(StepRepr_RepresentationItem), aItem);

  occ::handle<StepRepr_Representation> aRep;
  data->ReadEntity(num, 4, "rep", ach, STANDARD_TYPE(StepRepr_Representation), aRep);

  ent->Init(aName, aDescription, aItem, aRep);
}

void RWStepElement_RWAnalysisItemWithinRepresentation::WriteStep(
  StepData_StepWriter&                                             SW,
  const occ::handle<StepElement_AnalysisItemWithinRepresentation>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->Item());

  SW.Send(ent->Rep());
}

void RWStepElement_RWAnalysisItemWithinRepresentation::Share(
  const occ::handle<StepElement_AnalysisItemWithinRepresentation>& ent,
  Interface_EntityIterator&                                        iter) const
{

  iter.AddItem(ent->Item());

  iter.AddItem(ent->Rep());
}
