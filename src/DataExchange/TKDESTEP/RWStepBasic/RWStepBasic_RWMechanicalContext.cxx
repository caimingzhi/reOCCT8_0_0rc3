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

  // --- Number of Parameter Control ---

  if (!data->CheckNbParams(num, 3, ach, "mechanical_context"))
    return;

  // --- inherited field : name ---

  occ::handle<TCollection_HAsciiString> aName;
  // szv#4:S4163:12Mar99 `bool stat1 =` not needed
  data->ReadString(num, 1, "name", ach, aName);

  // --- inherited field : frameOfReference ---

  occ::handle<StepBasic_ApplicationContext> aFrameOfReference;
  // szv#4:S4163:12Mar99 `bool stat2 =` not needed
  data->ReadEntity(num,
                   2,
                   "frame_of_reference",
                   ach,
                   STANDARD_TYPE(StepBasic_ApplicationContext),
                   aFrameOfReference);

  // --- own field : disciplineType ---

  occ::handle<TCollection_HAsciiString> aDisciplineType;
  // szv#4:S4163:12Mar99 `bool stat3 =` not needed
  data->ReadString(num, 3, "discipline_type", ach, aDisciplineType);

  //--- Initialisation of the read entity ---

  ent->Init(aName, aFrameOfReference, aDisciplineType);
}

void RWStepBasic_RWMechanicalContext::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepBasic_MechanicalContext>& ent) const
{

  // --- inherited field name ---

  SW.Send(ent->Name());

  // --- inherited field frameOfReference ---

  SW.Send(ent->FrameOfReference());

  // --- own field : disciplineType ---

  SW.Send(ent->DisciplineType());
}

void RWStepBasic_RWMechanicalContext::Share(const occ::handle<StepBasic_MechanicalContext>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->FrameOfReference());
}
