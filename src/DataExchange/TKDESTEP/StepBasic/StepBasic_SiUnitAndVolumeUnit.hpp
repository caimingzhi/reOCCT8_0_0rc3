#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiUnit.hpp>
class StepBasic_VolumeUnit;

class StepBasic_SiUnitAndVolumeUnit : public StepBasic_SiUnit
{

public:
  Standard_EXPORT StepBasic_SiUnitAndVolumeUnit();

  Standard_EXPORT void SetVolumeUnit(const occ::handle<StepBasic_VolumeUnit>& aVolumeUnit);

  Standard_EXPORT occ::handle<StepBasic_VolumeUnit> VolumeUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnitAndVolumeUnit, StepBasic_SiUnit)

private:
  occ::handle<StepBasic_VolumeUnit> volumeUnit;
};
