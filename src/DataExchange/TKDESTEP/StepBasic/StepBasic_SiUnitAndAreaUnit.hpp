#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiUnit.hpp>
class StepBasic_AreaUnit;

class StepBasic_SiUnitAndAreaUnit : public StepBasic_SiUnit
{

public:
  Standard_EXPORT StepBasic_SiUnitAndAreaUnit();

  Standard_EXPORT void SetAreaUnit(const occ::handle<StepBasic_AreaUnit>& anAreaUnit);

  Standard_EXPORT occ::handle<StepBasic_AreaUnit> AreaUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnitAndAreaUnit, StepBasic_SiUnit)

private:
  occ::handle<StepBasic_AreaUnit> areaUnit;
};
