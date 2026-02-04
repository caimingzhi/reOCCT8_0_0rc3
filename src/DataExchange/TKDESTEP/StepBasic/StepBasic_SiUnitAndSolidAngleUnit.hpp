#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiUnit.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>
class StepBasic_SolidAngleUnit;

class StepBasic_SiUnitAndSolidAngleUnit : public StepBasic_SiUnit
{

public:
  //! Returns a SiUnitAndSolidAngleUnit
  Standard_EXPORT StepBasic_SiUnitAndSolidAngleUnit();

  Standard_EXPORT void Init(const bool                 hasAprefix,
                            const StepBasic_SiPrefix   aPrefix,
                            const StepBasic_SiUnitName aName);

  Standard_EXPORT void SetSolidAngleUnit(
    const occ::handle<StepBasic_SolidAngleUnit>& aSolidAngleUnit);

  Standard_EXPORT occ::handle<StepBasic_SolidAngleUnit> SolidAngleUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnitAndSolidAngleUnit, StepBasic_SiUnit)

private:
  occ::handle<StepBasic_SolidAngleUnit> solidAngleUnit;
};

