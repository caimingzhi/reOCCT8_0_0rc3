#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWThermodynamicTemperatureUnit.hpp"
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_ThermodynamicTemperatureUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWThermodynamicTemperatureUnit::RWStepBasic_RWThermodynamicTemperatureUnit() = default;

void RWStepBasic_RWThermodynamicTemperatureUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&                data,
  const int                                                  num,
  occ::handle<Interface_Check>&                              ach,
  const occ::handle<StepBasic_ThermodynamicTemperatureUnit>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "thermodynamic_temperature_unit"))
    return;

  occ::handle<StepBasic_DimensionalExponents> aNamedUnit_Dimensions;
  data->ReadEntity(num,
                   1,
                   "named_unit.dimensions",
                   ach,
                   STANDARD_TYPE(StepBasic_DimensionalExponents),
                   aNamedUnit_Dimensions);

  ent->Init(aNamedUnit_Dimensions);
}

void RWStepBasic_RWThermodynamicTemperatureUnit::WriteStep(
  StepData_StepWriter&                                       SW,
  const occ::handle<StepBasic_ThermodynamicTemperatureUnit>& ent) const
{

  SW.Send(ent->StepBasic_NamedUnit::Dimensions());
}

void RWStepBasic_RWThermodynamicTemperatureUnit::Share(
  const occ::handle<StepBasic_ThermodynamicTemperatureUnit>& ent,
  Interface_EntityIterator&                                  iter) const
{

  iter.AddItem(ent->StepBasic_NamedUnit::Dimensions());
}
