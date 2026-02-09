

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionContext.hpp"
#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductDefinitionContext::RWStepBasic_RWProductDefinitionContext() = default;

void RWStepBasic_RWProductDefinitionContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepBasic_ProductDefinitionContext>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "product_definition_context"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepBasic_ApplicationContext> aFrameOfReference;

  data->ReadEntity(num,
                   2,
                   "frame_of_reference",
                   ach,
                   STANDARD_TYPE(StepBasic_ApplicationContext),
                   aFrameOfReference);

  occ::handle<TCollection_HAsciiString> aLifeCycleStage;

  data->ReadString(num, 3, "life_cycle_stage", ach, aLifeCycleStage);

  ent->Init(aName, aFrameOfReference, aLifeCycleStage);
}

void RWStepBasic_RWProductDefinitionContext::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepBasic_ProductDefinitionContext>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->FrameOfReference());

  SW.Send(ent->LifeCycleStage());
}

void RWStepBasic_RWProductDefinitionContext::Share(
  const occ::handle<StepBasic_ProductDefinitionContext>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.GetOneItem(ent->FrameOfReference());
}
