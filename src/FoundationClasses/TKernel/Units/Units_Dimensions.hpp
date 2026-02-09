#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

class Units_Dimensions : public Standard_Transient
{

public:
  Standard_EXPORT Units_Dimensions(const double amass,
                                   const double alength,
                                   const double atime,
                                   const double anelectriccurrent,
                                   const double athermodynamictemperature,
                                   const double anamountofsubstance,
                                   const double aluminousintensity,
                                   const double aplaneangle,
                                   const double asolidangle);

  double Mass() const;

  double Length() const;

  double Time() const;

  double ElectricCurrent() const;

  double ThermodynamicTemperature() const;

  double AmountOfSubstance() const;

  double LuminousIntensity() const;

  double PlaneAngle() const;

  double SolidAngle() const;

  Standard_EXPORT const char* Quantity() const;

  Standard_EXPORT occ::handle<Units_Dimensions> Multiply(
    const occ::handle<Units_Dimensions>& adimensions) const;

  Standard_EXPORT occ::handle<Units_Dimensions> Divide(
    const occ::handle<Units_Dimensions>& adimensions) const;

  Standard_EXPORT occ::handle<Units_Dimensions> Power(const double anexponent) const;

  Standard_EXPORT bool IsEqual(const occ::handle<Units_Dimensions>& adimensions) const;

  Standard_EXPORT bool IsNotEqual(const occ::handle<Units_Dimensions>& adimensions) const;

  Standard_EXPORT void Dump(const int ashift) const;

  Standard_EXPORT static occ::handle<Units_Dimensions> ALess();

  Standard_EXPORT static occ::handle<Units_Dimensions> AMass();

  Standard_EXPORT static occ::handle<Units_Dimensions> ALength();

  Standard_EXPORT static occ::handle<Units_Dimensions> ATime();

  Standard_EXPORT static occ::handle<Units_Dimensions> AElectricCurrent();

  Standard_EXPORT static occ::handle<Units_Dimensions> AThermodynamicTemperature();

  Standard_EXPORT static occ::handle<Units_Dimensions> AAmountOfSubstance();

  Standard_EXPORT static occ::handle<Units_Dimensions> ALuminousIntensity();

  Standard_EXPORT static occ::handle<Units_Dimensions> APlaneAngle();

  Standard_EXPORT static occ::handle<Units_Dimensions> ASolidAngle();

  DEFINE_STANDARD_RTTIEXT(Units_Dimensions, Standard_Transient)

private:
  double themass;
  double thelength;
  double thetime;
  double theelectriccurrent;
  double thethermodynamictemperature;
  double theamountofsubstance;
  double theluminousintensity;
  double theplaneangle;
  double thesolidangle;
};

inline double Units_Dimensions::Mass() const
{
  return themass;
}

inline double Units_Dimensions::Length() const
{
  return thelength;
}

inline double Units_Dimensions::Time() const
{
  return thetime;
}

inline double Units_Dimensions::ElectricCurrent() const
{
  return theelectriccurrent;
}

inline double Units_Dimensions::ThermodynamicTemperature() const
{
  return thethermodynamictemperature;
}

inline double Units_Dimensions::AmountOfSubstance() const
{
  return theamountofsubstance;
}

inline double Units_Dimensions::LuminousIntensity() const
{
  return theluminousintensity;
}

inline double Units_Dimensions::PlaneAngle() const
{
  return theplaneangle;
}

inline double Units_Dimensions::SolidAngle() const
{
  return thesolidangle;
}
