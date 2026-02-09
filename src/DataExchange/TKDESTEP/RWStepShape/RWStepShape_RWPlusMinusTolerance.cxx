

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWPlusMinusTolerance.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_PlusMinusTolerance.hpp>
#include <StepShape_ToleranceMethodDefinition.hpp>

RWStepShape_RWPlusMinusTolerance::RWStepShape_RWPlusMinusTolerance() = default;

void RWStepShape_RWPlusMinusTolerance::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepShape_PlusMinusTolerance>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "plus_minus_tolerance"))
    return;

  StepShape_ToleranceMethodDefinition aRange;
  data->ReadEntity(num, 1, "range", ach, aRange);

  StepShape_DimensionalCharacteristic aTD;
  data->ReadEntity(num, 2, "2dtolerance_dimensionrange", ach, aTD);

  ent->Init(aRange, aTD);
}

void RWStepShape_RWPlusMinusTolerance::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepShape_PlusMinusTolerance>& ent) const
{
  SW.Send(ent->Range().Value());
  SW.Send(ent->TolerancedDimension().Value());
}

void RWStepShape_RWPlusMinusTolerance::Share(const occ::handle<StepShape_PlusMinusTolerance>& ent,
                                             Interface_EntityIterator& iter) const
{
  iter.AddItem(ent->Range().Value());
  iter.AddItem(ent->TolerancedDimension().Value());
}
