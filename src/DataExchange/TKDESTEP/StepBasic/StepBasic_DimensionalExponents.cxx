

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DimensionalExponents, Standard_Transient)

StepBasic_DimensionalExponents::StepBasic_DimensionalExponents() = default;

void StepBasic_DimensionalExponents::Init(const double aLengthExponent,
                                          const double aMassExponent,
                                          const double aTimeExponent,
                                          const double aElectricCurrentExponent,
                                          const double aThermodynamicTemperatureExponent,
                                          const double aAmountOfSubstanceExponent,
                                          const double aLuminousIntensityExponent)
{

  lengthExponent                   = aLengthExponent;
  massExponent                     = aMassExponent;
  timeExponent                     = aTimeExponent;
  electricCurrentExponent          = aElectricCurrentExponent;
  thermodynamicTemperatureExponent = aThermodynamicTemperatureExponent;
  amountOfSubstanceExponent        = aAmountOfSubstanceExponent;
  luminousIntensityExponent        = aLuminousIntensityExponent;
}

void StepBasic_DimensionalExponents::SetLengthExponent(const double aLengthExponent)
{
  lengthExponent = aLengthExponent;
}

double StepBasic_DimensionalExponents::LengthExponent() const
{
  return lengthExponent;
}

void StepBasic_DimensionalExponents::SetMassExponent(const double aMassExponent)
{
  massExponent = aMassExponent;
}

double StepBasic_DimensionalExponents::MassExponent() const
{
  return massExponent;
}

void StepBasic_DimensionalExponents::SetTimeExponent(const double aTimeExponent)
{
  timeExponent = aTimeExponent;
}

double StepBasic_DimensionalExponents::TimeExponent() const
{
  return timeExponent;
}

void StepBasic_DimensionalExponents::SetElectricCurrentExponent(
  const double aElectricCurrentExponent)
{
  electricCurrentExponent = aElectricCurrentExponent;
}

double StepBasic_DimensionalExponents::ElectricCurrentExponent() const
{
  return electricCurrentExponent;
}

void StepBasic_DimensionalExponents::SetThermodynamicTemperatureExponent(
  const double aThermodynamicTemperatureExponent)
{
  thermodynamicTemperatureExponent = aThermodynamicTemperatureExponent;
}

double StepBasic_DimensionalExponents::ThermodynamicTemperatureExponent() const
{
  return thermodynamicTemperatureExponent;
}

void StepBasic_DimensionalExponents::SetAmountOfSubstanceExponent(
  const double aAmountOfSubstanceExponent)
{
  amountOfSubstanceExponent = aAmountOfSubstanceExponent;
}

double StepBasic_DimensionalExponents::AmountOfSubstanceExponent() const
{
  return amountOfSubstanceExponent;
}

void StepBasic_DimensionalExponents::SetLuminousIntensityExponent(
  const double aLuminousIntensityExponent)
{
  luminousIntensityExponent = aLuminousIntensityExponent;
}

double StepBasic_DimensionalExponents::LuminousIntensityExponent() const
{
  return luminousIntensityExponent;
}
