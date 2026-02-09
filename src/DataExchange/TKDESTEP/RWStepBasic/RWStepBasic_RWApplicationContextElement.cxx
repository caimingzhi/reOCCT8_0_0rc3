

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWApplicationContextElement.hpp"
#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ApplicationContextElement.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApplicationContextElement::RWStepBasic_RWApplicationContextElement() = default;

void RWStepBasic_RWApplicationContextElement::ReadStep(
  const occ::handle<StepData_StepReaderData>&             data,
  const int                                               num,
  occ::handle<Interface_Check>&                           ach,
  const occ::handle<StepBasic_ApplicationContextElement>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "application_context_element"))
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

  ent->Init(aName, aFrameOfReference);
}

void RWStepBasic_RWApplicationContextElement::WriteStep(
  StepData_StepWriter&                                    SW,
  const occ::handle<StepBasic_ApplicationContextElement>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->FrameOfReference());
}

void RWStepBasic_RWApplicationContextElement::Share(
  const occ::handle<StepBasic_ApplicationContextElement>& ent,
  Interface_EntityIterator&                               iter) const
{

  iter.GetOneItem(ent->FrameOfReference());
}
