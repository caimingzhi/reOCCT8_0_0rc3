#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiUnit.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>
class StepBasic_MassUnit;

class StepBasic_SiUnitAndMassUnit : public StepBasic_SiUnit
{

public:
  Standard_EXPORT StepBasic_SiUnitAndMassUnit();

  Standard_EXPORT void Init(const bool                 hasAprefix,
                            const StepBasic_SiPrefix   aPrefix,
                            const StepBasic_SiUnitName aName);

  Standard_EXPORT void SetMassUnit(const occ::handle<StepBasic_MassUnit>& aMassUnit);

  Standard_EXPORT occ::handle<StepBasic_MassUnit> MassUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnitAndMassUnit, StepBasic_SiUnit)

private:
  occ::handle<StepBasic_MassUnit> massUnit;
};
