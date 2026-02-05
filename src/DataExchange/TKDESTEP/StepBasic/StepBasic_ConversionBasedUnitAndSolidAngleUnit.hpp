#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ConversionBasedUnit.hpp>
class StepBasic_SolidAngleUnit;
class StepBasic_DimensionalExponents;
class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;

class StepBasic_ConversionBasedUnitAndSolidAngleUnit : public StepBasic_ConversionBasedUnit
{

public:
  //! Returns a ConversionBasedUnitAndSolidAngleUnit
  Standard_EXPORT StepBasic_ConversionBasedUnitAndSolidAngleUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
                            const occ::handle<TCollection_HAsciiString>&       aName,
                            const occ::handle<Standard_Transient>&             aConversionFactor);

  Standard_EXPORT void SetSolidAngleUnit(
    const occ::handle<StepBasic_SolidAngleUnit>& aSolidAngleUnit);

  Standard_EXPORT occ::handle<StepBasic_SolidAngleUnit> SolidAngleUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndSolidAngleUnit,
                          StepBasic_ConversionBasedUnit)

private:
  occ::handle<StepBasic_SolidAngleUnit> solidAngleUnit;
};
