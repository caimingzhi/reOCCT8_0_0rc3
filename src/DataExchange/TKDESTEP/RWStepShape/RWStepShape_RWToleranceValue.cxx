

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWToleranceValue.hpp"
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_ToleranceValue.hpp>
#include <StepRepr_MeasureRepresentationItem.hpp>
#include <StepRepr_ReprItemAndMeasureWithUnit.hpp>

RWStepShape_RWToleranceValue::RWStepShape_RWToleranceValue() = default;

void RWStepShape_RWToleranceValue::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepShape_ToleranceValue>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "tolerance_value"))
    return;

  occ::handle<Standard_Transient> aLowerBound;
  data->ReadEntity(num, 1, "lower_bound", ach, STANDARD_TYPE(Standard_Transient), aLowerBound);

  occ::handle<Standard_Transient> anUpperBound;
  data->ReadEntity(num, 2, "upper_bound", ach, STANDARD_TYPE(Standard_Transient), anUpperBound);

  if (!aLowerBound.IsNull() && !anUpperBound.IsNull())
    ach->ClearFails();
  ent->Init(aLowerBound, anUpperBound);
}

void RWStepShape_RWToleranceValue::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepShape_ToleranceValue>& ent) const
{
  SW.Send(ent->LowerBound());
  SW.Send(ent->UpperBound());
}

void RWStepShape_RWToleranceValue::Share(const occ::handle<StepShape_ToleranceValue>& ent,
                                         Interface_EntityIterator&                    iter) const
{
  iter.AddItem(ent->LowerBound());
  iter.AddItem(ent->UpperBound());
}
