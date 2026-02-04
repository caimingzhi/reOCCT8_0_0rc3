#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiUnit.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>
class StepBasic_RatioUnit;

class StepBasic_SiUnitAndRatioUnit : public StepBasic_SiUnit
{

public:
  //! Returns a SiUnitAndRatioUnit
  Standard_EXPORT StepBasic_SiUnitAndRatioUnit();

  Standard_EXPORT void Init(const bool                 hasAprefix,
                            const StepBasic_SiPrefix   aPrefix,
                            const StepBasic_SiUnitName aName);

  Standard_EXPORT void SetRatioUnit(const occ::handle<StepBasic_RatioUnit>& aRatioUnit);

  Standard_EXPORT occ::handle<StepBasic_RatioUnit> RatioUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnitAndRatioUnit, StepBasic_SiUnit)

private:
  occ::handle<StepBasic_RatioUnit> ratioUnit;
};

