#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWDimensionalSize.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepShape_DimensionalSize.hpp>

//=================================================================================================

RWStepShape_RWDimensionalSize::RWStepShape_RWDimensionalSize() = default;

//=================================================================================================

void RWStepShape_RWDimensionalSize::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepShape_DimensionalSize>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "dimensional_size"))
    return;

  // Own fields of DimensionalSize

  occ::handle<StepRepr_ShapeAspect> aAppliesTo;
  data->ReadEntity(num, 1, "applies_to", ach, STANDARD_TYPE(StepRepr_ShapeAspect), aAppliesTo);

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 2, "name", ach, aName);

  // Initialize entity
  ent->Init(aAppliesTo, aName);
}

//=================================================================================================

void RWStepShape_RWDimensionalSize::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepShape_DimensionalSize>& ent) const
{

  // Own fields of DimensionalSize

  SW.Send(ent->AppliesTo());

  SW.Send(ent->Name());
}

//=================================================================================================

void RWStepShape_RWDimensionalSize::Share(const occ::handle<StepShape_DimensionalSize>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  // Own fields of DimensionalSize

  iter.AddItem(ent->AppliesTo());
}
