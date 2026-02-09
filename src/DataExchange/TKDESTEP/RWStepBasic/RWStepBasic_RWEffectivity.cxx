

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWEffectivity.hpp"
#include <StepBasic_Effectivity.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepBasic_RWEffectivity::RWStepBasic_RWEffectivity() = default;

void RWStepBasic_RWEffectivity::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepBasic_Effectivity>&   ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "effectivity"))
    return;

  occ::handle<TCollection_HAsciiString> aId;

  data->ReadString(num, 1, "id", ach, aId);

  ent->Init(aId);
}

void RWStepBasic_RWEffectivity::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepBasic_Effectivity>& ent) const
{

  SW.Send(ent->Id());
}

void RWStepBasic_RWEffectivity::Share(const occ::handle<StepBasic_Effectivity>&,
                                      Interface_EntityIterator&) const
{
}
