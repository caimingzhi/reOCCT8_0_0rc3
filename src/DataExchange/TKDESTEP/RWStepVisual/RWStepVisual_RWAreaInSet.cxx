

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWAreaInSet.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_AreaInSet.hpp>
#include <StepVisual_PresentationArea.hpp>
#include <StepVisual_PresentationSet.hpp>

RWStepVisual_RWAreaInSet::RWStepVisual_RWAreaInSet() = default;

void RWStepVisual_RWAreaInSet::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepVisual_AreaInSet>&    ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "area_in_set"))
    return;

  occ::handle<StepVisual_PresentationArea> aArea;

  data->ReadEntity(num, 1, "area", ach, STANDARD_TYPE(StepVisual_PresentationArea), aArea);

  occ::handle<StepVisual_PresentationSet> aInSet;

  data->ReadEntity(num, 2, "in_set", ach, STANDARD_TYPE(StepVisual_PresentationSet), aInSet);

  ent->Init(aArea, aInSet);
}

void RWStepVisual_RWAreaInSet::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepVisual_AreaInSet>& ent) const
{

  SW.Send(ent->Area());

  SW.Send(ent->InSet());
}

void RWStepVisual_RWAreaInSet::Share(const occ::handle<StepVisual_AreaInSet>& ent,
                                     Interface_EntityIterator&                iter) const
{

  iter.GetOneItem(ent->Area());

  iter.GetOneItem(ent->InSet());
}
