#include <Standard_Type.hpp>
#include <StepBasic_ConversionBasedUnitAndVolumeUnit.hpp>
#include <StepBasic_VolumeUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndVolumeUnit,
                           StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndVolumeUnit::StepBasic_ConversionBasedUnitAndVolumeUnit() = default;

void StepBasic_ConversionBasedUnitAndVolumeUnit::SetVolumeUnit(
  const occ::handle<StepBasic_VolumeUnit>& aVolumeUnit)
{
  volumeUnit = aVolumeUnit;
}

occ::handle<StepBasic_VolumeUnit> StepBasic_ConversionBasedUnitAndVolumeUnit::VolumeUnit() const
{
  return volumeUnit;
}
