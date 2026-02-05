#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ConversionBasedUnit.hpp>
class StepBasic_AreaUnit;

class StepBasic_ConversionBasedUnitAndAreaUnit : public StepBasic_ConversionBasedUnit
{

public:
  //! Returns a ConversionBasedUnitAndAreaUnit
  Standard_EXPORT StepBasic_ConversionBasedUnitAndAreaUnit();

  Standard_EXPORT void SetAreaUnit(const occ::handle<StepBasic_AreaUnit>& anAreaUnit);

  Standard_EXPORT occ::handle<StepBasic_AreaUnit> AreaUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndAreaUnit, StepBasic_ConversionBasedUnit)

private:
  occ::handle<StepBasic_AreaUnit> areaUnit;
};
