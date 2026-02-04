#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

class StepBasic_DimensionalExponents : public Standard_Transient
{

public:
  //! Returns a DimensionalExponents
  Standard_EXPORT StepBasic_DimensionalExponents();

  Standard_EXPORT void Init(const double aLengthExponent,
                            const double aMassExponent,
                            const double aTimeExponent,
                            const double aElectricCurrentExponent,
                            const double aThermodynamicTemperatureExponent,
                            const double aAmountOfSubstanceExponent,
                            const double aLuminousIntensityExponent);

  Standard_EXPORT void SetLengthExponent(const double aLengthExponent);

  Standard_EXPORT double LengthExponent() const;

  Standard_EXPORT void SetMassExponent(const double aMassExponent);

  Standard_EXPORT double MassExponent() const;

  Standard_EXPORT void SetTimeExponent(const double aTimeExponent);

  Standard_EXPORT double TimeExponent() const;

  Standard_EXPORT void SetElectricCurrentExponent(const double aElectricCurrentExponent);

  Standard_EXPORT double ElectricCurrentExponent() const;

  Standard_EXPORT void SetThermodynamicTemperatureExponent(
    const double aThermodynamicTemperatureExponent);

  Standard_EXPORT double ThermodynamicTemperatureExponent() const;

  Standard_EXPORT void SetAmountOfSubstanceExponent(const double aAmountOfSubstanceExponent);

  Standard_EXPORT double AmountOfSubstanceExponent() const;

  Standard_EXPORT void SetLuminousIntensityExponent(const double aLuminousIntensityExponent);

  Standard_EXPORT double LuminousIntensityExponent() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_DimensionalExponents, Standard_Transient)

private:
  double lengthExponent;
  double massExponent;
  double timeExponent;
  double electricCurrentExponent;
  double thermodynamicTemperatureExponent;
  double amountOfSubstanceExponent;
  double luminousIntensityExponent;
};

