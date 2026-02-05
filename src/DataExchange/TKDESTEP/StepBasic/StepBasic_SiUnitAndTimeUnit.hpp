#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiUnit.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>
class StepBasic_TimeUnit;

class StepBasic_SiUnitAndTimeUnit : public StepBasic_SiUnit
{

public:
  //! Returns a SiUnitAndTimeUnit
  Standard_EXPORT StepBasic_SiUnitAndTimeUnit();

  Standard_EXPORT void Init(const bool                 hasAprefix,
                            const StepBasic_SiPrefix   aPrefix,
                            const StepBasic_SiUnitName aName);

  Standard_EXPORT void SetTimeUnit(const occ::handle<StepBasic_TimeUnit>& aTimeUnit);

  Standard_EXPORT occ::handle<StepBasic_TimeUnit> TimeUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnitAndTimeUnit, StepBasic_SiUnit)

private:
  occ::handle<StepBasic_TimeUnit> timeUnit;
};
