

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SiUnitAndTimeUnit.hpp>
#include <StepBasic_TimeUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnitAndTimeUnit, StepBasic_SiUnit)

StepBasic_SiUnitAndTimeUnit::StepBasic_SiUnitAndTimeUnit() = default;

void StepBasic_SiUnitAndTimeUnit::Init(const bool                 hasAprefix,
                                       const StepBasic_SiPrefix   aPrefix,
                                       const StepBasic_SiUnitName aName)
{

  StepBasic_SiUnit::Init(hasAprefix, aPrefix, aName);

  timeUnit = new StepBasic_TimeUnit();
  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  aDimensions.Nullify();
  timeUnit->Init(aDimensions);
}

void StepBasic_SiUnitAndTimeUnit::SetTimeUnit(const occ::handle<StepBasic_TimeUnit>& aTimeUnit)
{
  timeUnit = aTimeUnit;
}

occ::handle<StepBasic_TimeUnit> StepBasic_SiUnitAndTimeUnit::TimeUnit() const
{
  return timeUnit;
}
