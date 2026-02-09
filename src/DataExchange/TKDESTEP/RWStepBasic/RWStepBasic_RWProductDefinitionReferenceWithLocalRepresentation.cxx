#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation.hpp"
#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_ProductDefinitionReferenceWithLocalRepresentation.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation::
  RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation() = default;

void RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                     data,
  const int                                                                       num,
  occ::handle<Interface_Check>&                                                   ach,
  const occ::handle<StepBasic_ProductDefinitionReferenceWithLocalRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "product_definition_reference_with_local_representation"))
    return;

  occ::handle<StepBasic_ExternalSource> aSource;
  data->ReadEntity(num, 1, "source", ach, STANDARD_TYPE(StepBasic_ExternalSource), aSource);

  occ::handle<TCollection_HAsciiString> aId;
  data->ReadString(num, 2, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num, 3, "description", ach, aDescription);
  }

  occ::handle<StepBasic_ProductDefinitionFormation> aFormation;
  data->ReadEntity(num,
                   4,
                   "formation",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionFormation),
                   aFormation);

  occ::handle<StepBasic_ProductDefinitionContext> aFrameOfReference;
  data->ReadEntity(num,
                   5,
                   "frame_of_reference",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionContext),
                   aFrameOfReference);

  ent->Init(aSource, aId, aDescription, aFormation, aFrameOfReference);
}

void RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation::WriteStep(
  StepData_StepWriter&                                                            SW,
  const occ::handle<StepBasic_ProductDefinitionReferenceWithLocalRepresentation>& ent) const
{

  SW.Send(ent->Source());

  SW.Send(ent->Id());

  SW.Send(ent->Description());

  SW.Send(ent->Formation());

  SW.Send(ent->FrameOfReference());
}

void RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation::Share(
  const occ::handle<StepBasic_ProductDefinitionReferenceWithLocalRepresentation>& ent,
  Interface_EntityIterator&                                                       iter) const
{
  iter.GetOneItem(ent->Source());
  iter.GetOneItem(ent->Formation());
  iter.GetOneItem(ent->FrameOfReference());
}
