

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinition.hpp"
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductDefinition::RWStepBasic_RWProductDefinition() = default;

void RWStepBasic_RWProductDefinition::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepBasic_ProductDefinition>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "product_definition"))
    return;

  occ::handle<TCollection_HAsciiString> aId;

  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "description", ach, aDescription);
  }

  occ::handle<StepBasic_ProductDefinitionFormation> aFormation;

  data->ReadEntity(num,
                   3,
                   "formation",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionFormation),
                   aFormation);

  occ::handle<StepBasic_ProductDefinitionContext> aFrameOfReference;

  data->ReadEntity(num,
                   4,
                   "frame_of_reference",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionContext),
                   aFrameOfReference);

  ent->Init(aId, aDescription, aFormation, aFrameOfReference);
}

void RWStepBasic_RWProductDefinition::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepBasic_ProductDefinition>& ent) const
{

  SW.Send(ent->Id());

  if (!ent->Description().IsNull())
  {
    SW.Send(ent->Description());
  }
  else
  {
    SW.SendUndef();
  }

  SW.Send(ent->Formation());

  SW.Send(ent->FrameOfReference());
}

void RWStepBasic_RWProductDefinition::Share(const occ::handle<StepBasic_ProductDefinition>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->Formation());

  iter.GetOneItem(ent->FrameOfReference());
}
