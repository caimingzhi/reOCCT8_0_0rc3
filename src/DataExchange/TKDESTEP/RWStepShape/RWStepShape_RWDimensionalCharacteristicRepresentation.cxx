#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWDimensionalCharacteristicRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_DimensionalCharacteristicRepresentation.hpp>
#include <StepShape_ShapeDimensionRepresentation.hpp>

RWStepShape_RWDimensionalCharacteristicRepresentation::
  RWStepShape_RWDimensionalCharacteristicRepresentation() = default;

void RWStepShape_RWDimensionalCharacteristicRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                           data,
  const int                                                             num,
  occ::handle<Interface_Check>&                                         ach,
  const occ::handle<StepShape_DimensionalCharacteristicRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "dimensional_characteristic_representation"))
    return;

  StepShape_DimensionalCharacteristic aDimension;
  data->ReadEntity(num, 1, "dimension", ach, aDimension);

  occ::handle<StepShape_ShapeDimensionRepresentation> aRepresentation;
  data->ReadEntity(num,
                   2,
                   "representation",
                   ach,
                   STANDARD_TYPE(StepShape_ShapeDimensionRepresentation),
                   aRepresentation);

  ent->Init(aDimension, aRepresentation);
}

void RWStepShape_RWDimensionalCharacteristicRepresentation::WriteStep(
  StepData_StepWriter&                                                  SW,
  const occ::handle<StepShape_DimensionalCharacteristicRepresentation>& ent) const
{

  SW.Send(ent->Dimension().Value());

  SW.Send(ent->Representation());
}

void RWStepShape_RWDimensionalCharacteristicRepresentation::Share(
  const occ::handle<StepShape_DimensionalCharacteristicRepresentation>& ent,
  Interface_EntityIterator&                                             iter) const
{

  iter.AddItem(ent->Dimension().Value());

  iter.AddItem(ent->Representation());
}
