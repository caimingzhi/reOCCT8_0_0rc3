#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SiUnitAndVolumeUnit.hpp>
#include <StepBasic_VolumeUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnitAndVolumeUnit, StepBasic_SiUnit)

StepBasic_SiUnitAndVolumeUnit::StepBasic_SiUnitAndVolumeUnit() = default;

void StepBasic_SiUnitAndVolumeUnit::SetVolumeUnit(
  const occ::handle<StepBasic_VolumeUnit>& aVolumeUnit)
{
  volumeUnit = aVolumeUnit;
}

occ::handle<StepBasic_VolumeUnit> StepBasic_SiUnitAndVolumeUnit::VolumeUnit() const
{
  return volumeUnit;
}
