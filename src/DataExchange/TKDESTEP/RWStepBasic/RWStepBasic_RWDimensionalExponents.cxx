

#include "RWStepBasic_RWDimensionalExponents.hpp"
#include <StepBasic_DimensionalExponents.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDimensionalExponents::RWStepBasic_RWDimensionalExponents() = default;

void RWStepBasic_RWDimensionalExponents::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepBasic_DimensionalExponents>& ent) const
{

  if (!data->CheckNbParams(num, 7, ach, "dimensional_exponents"))
    return;

  double aLengthExponent;

  data->ReadReal(num, 1, "length_exponent", ach, aLengthExponent);

  double aMassExponent;

  data->ReadReal(num, 2, "mass_exponent", ach, aMassExponent);

  double aTimeExponent;

  data->ReadReal(num, 3, "time_exponent", ach, aTimeExponent);

  double aElectricCurrentExponent;

  data->ReadReal(num, 4, "electric_current_exponent", ach, aElectricCurrentExponent);

  double aThermodynamicTemperatureExponent;

  data->ReadReal(num,
                 5,
                 "thermodynamic_temperature_exponent",
                 ach,
                 aThermodynamicTemperatureExponent);

  double aAmountOfSubstanceExponent;

  data->ReadReal(num, 6, "amount_of_substance_exponent", ach, aAmountOfSubstanceExponent);

  double aLuminousIntensityExponent;

  data->ReadReal(num, 7, "luminous_intensity_exponent", ach, aLuminousIntensityExponent);

  ent->Init(aLengthExponent,
            aMassExponent,
            aTimeExponent,
            aElectricCurrentExponent,
            aThermodynamicTemperatureExponent,
            aAmountOfSubstanceExponent,
            aLuminousIntensityExponent);
}

void RWStepBasic_RWDimensionalExponents::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepBasic_DimensionalExponents>& ent) const
{

  SW.Send(ent->LengthExponent());

  SW.Send(ent->MassExponent());

  SW.Send(ent->TimeExponent());

  SW.Send(ent->ElectricCurrentExponent());

  SW.Send(ent->ThermodynamicTemperatureExponent());

  SW.Send(ent->AmountOfSubstanceExponent());

  SW.Send(ent->LuminousIntensityExponent());
}
