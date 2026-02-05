#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation.hpp"
#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_ProductDefinitionReferenceWithLocalRepresentation.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation::
  RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation() = default;

//=================================================================================================

void RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                     data,
  const int                                                                       num,
  occ::handle<Interface_Check>&                                                   ach,
  const occ::handle<StepBasic_ProductDefinitionReferenceWithLocalRepresentation>& ent) const
{
  // Number of Parameter Control
  if (!data->CheckNbParams(num, 5, ach, "product_definition_reference_with_local_representation"))
    return;

  // Own field source
  occ::handle<StepBasic_ExternalSource> aSource;
  data->ReadEntity(num, 1, "source", ach, STANDARD_TYPE(StepBasic_ExternalSource), aSource);

  // Inherited field : id
  occ::handle<TCollection_HAsciiString> aId;
  data->ReadString(num, 2, "id", ach, aId);

  // Inherited field : description
  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num, 3, "description", ach, aDescription);
  }

  // Inherited field : formation
  occ::handle<StepBasic_ProductDefinitionFormation> aFormation;
  data->ReadEntity(num,
                   4,
                   "formation",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionFormation),
                   aFormation);

  // Inherited : frame_of_reference
  occ::handle<StepBasic_ProductDefinitionContext> aFrameOfReference;
  data->ReadEntity(num,
                   5,
                   "frame_of_reference",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionContext),
                   aFrameOfReference);

  //  Initialisation of the read entity
  ent->Init(aSource, aId, aDescription, aFormation, aFrameOfReference);
}

//=================================================================================================

void RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation::WriteStep(
  StepData_StepWriter&                                                            SW,
  const occ::handle<StepBasic_ProductDefinitionReferenceWithLocalRepresentation>& ent) const
{
  // Own field : source
  SW.Send(ent->Source());

  // Inherited field : id
  SW.Send(ent->Id());

  // Inherited field : description
  SW.Send(ent->Description());

  // Inherited field : formation
  SW.Send(ent->Formation());

  // Inherited field : frame_of_reference
  SW.Send(ent->FrameOfReference());
}

//=================================================================================================

void RWStepBasic_RWProductDefinitionReferenceWithLocalRepresentation::Share(
  const occ::handle<StepBasic_ProductDefinitionReferenceWithLocalRepresentation>& ent,
  Interface_EntityIterator&                                                       iter) const
{
  iter.GetOneItem(ent->Source());
  iter.GetOneItem(ent->Formation());
  iter.GetOneItem(ent->FrameOfReference());
}
