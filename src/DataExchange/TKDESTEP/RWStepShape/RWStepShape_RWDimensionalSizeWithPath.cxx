#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWDimensionalSizeWithPath.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepShape_DimensionalSizeWithPath.hpp>

RWStepShape_RWDimensionalSizeWithPath::RWStepShape_RWDimensionalSizeWithPath() = default;

void RWStepShape_RWDimensionalSizeWithPath::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepShape_DimensionalSizeWithPath>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "dimensional_size_with_path"))
    return;

  occ::handle<StepRepr_ShapeAspect> aDimensionalSize_AppliesTo;
  data->ReadEntity(num,
                   1,
                   "dimensional_size.applies_to",
                   ach,
                   STANDARD_TYPE(StepRepr_ShapeAspect),
                   aDimensionalSize_AppliesTo);

  occ::handle<TCollection_HAsciiString> aDimensionalSize_Name;
  data->ReadString(num, 2, "dimensional_size.name", ach, aDimensionalSize_Name);

  occ::handle<StepRepr_ShapeAspect> aPath;
  data->ReadEntity(num, 3, "path", ach, STANDARD_TYPE(StepRepr_ShapeAspect), aPath);

  ent->Init(aDimensionalSize_AppliesTo, aDimensionalSize_Name, aPath);
}

void RWStepShape_RWDimensionalSizeWithPath::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepShape_DimensionalSizeWithPath>& ent) const
{

  SW.Send(ent->StepShape_DimensionalSize::AppliesTo());

  SW.Send(ent->StepShape_DimensionalSize::Name());

  SW.Send(ent->Path());
}

void RWStepShape_RWDimensionalSizeWithPath::Share(
  const occ::handle<StepShape_DimensionalSizeWithPath>& ent,
  Interface_EntityIterator&                             iter) const
{

  iter.AddItem(ent->StepShape_DimensionalSize::AppliesTo());

  iter.AddItem(ent->Path());
}
