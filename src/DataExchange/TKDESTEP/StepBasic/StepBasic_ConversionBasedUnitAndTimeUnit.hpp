#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ConversionBasedUnit.hpp>
class StepBasic_TimeUnit;
class StepBasic_DimensionalExponents;
class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;

class StepBasic_ConversionBasedUnitAndTimeUnit : public StepBasic_ConversionBasedUnit
{

public:
  Standard_EXPORT StepBasic_ConversionBasedUnitAndTimeUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
                            const occ::handle<TCollection_HAsciiString>&       aName,
                            const occ::handle<Standard_Transient>&             aConversionFactor);

  Standard_EXPORT void SetTimeUnit(const occ::handle<StepBasic_TimeUnit>& aTimeUnit);

  Standard_EXPORT occ::handle<StepBasic_TimeUnit> TimeUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndTimeUnit, StepBasic_ConversionBasedUnit)

private:
  occ::handle<StepBasic_TimeUnit> timeUnit;
};
