#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWMechanicalContext.hpp"
#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_MechanicalContext.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWMechanicalContext::RWStepBasic_RWMechanicalContext() = default;

void RWStepBasic_RWMechanicalContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepBasic_MechanicalContext>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "mechanical_context"))
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

  occ::handle<TCollection_HAsciiString> aDisciplineType;

  data->ReadString(num, 3, "discipline_type", ach, aDisciplineType);

  ent->Init(aName, aFrameOfReference, aDisciplineType);
}

void RWStepBasic_RWMechanicalContext::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepBasic_MechanicalContext>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->FrameOfReference());

  SW.Send(ent->DisciplineType());
}

void RWStepBasic_RWMechanicalContext::Share(const occ::handle<StepBasic_MechanicalContext>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->FrameOfReference());
}
