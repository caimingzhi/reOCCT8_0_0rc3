#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ConversionBasedUnit.hpp>
class StepBasic_VolumeUnit;

class StepBasic_ConversionBasedUnitAndVolumeUnit : public StepBasic_ConversionBasedUnit
{

public:
  Standard_EXPORT StepBasic_ConversionBasedUnitAndVolumeUnit();

  Standard_EXPORT void SetVolumeUnit(const occ::handle<StepBasic_VolumeUnit>& aVolumeUnit);

  Standard_EXPORT occ::handle<StepBasic_VolumeUnit> VolumeUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndVolumeUnit, StepBasic_ConversionBasedUnit)

private:
  occ::handle<StepBasic_VolumeUnit> volumeUnit;
};
