#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiUnit.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>
class StepBasic_LengthUnit;

class StepBasic_SiUnitAndLengthUnit : public StepBasic_SiUnit
{

public:
  //! Returns a SiUnitAndLengthUnit
  Standard_EXPORT StepBasic_SiUnitAndLengthUnit();

  Standard_EXPORT void Init(const bool                 hasAprefix,
                            const StepBasic_SiPrefix   aPrefix,
                            const StepBasic_SiUnitName aName);

  Standard_EXPORT void SetLengthUnit(const occ::handle<StepBasic_LengthUnit>& aLengthUnit);

  Standard_EXPORT occ::handle<StepBasic_LengthUnit> LengthUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnitAndLengthUnit, StepBasic_SiUnit)

private:
  occ::handle<StepBasic_LengthUnit> lengthUnit;
};

