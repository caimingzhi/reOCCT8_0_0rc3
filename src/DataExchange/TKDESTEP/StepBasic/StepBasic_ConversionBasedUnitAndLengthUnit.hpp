#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ConversionBasedUnit.hpp>
class StepBasic_LengthUnit;
class StepBasic_DimensionalExponents;
class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;

class StepBasic_ConversionBasedUnitAndLengthUnit : public StepBasic_ConversionBasedUnit
{

public:
  //! Returns a ConversionBasedUnitAndLengthUnit
  Standard_EXPORT StepBasic_ConversionBasedUnitAndLengthUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
                            const occ::handle<TCollection_HAsciiString>&       aName,
                            const occ::handle<Standard_Transient>&             aConversionFactor);

  Standard_EXPORT void SetLengthUnit(const occ::handle<StepBasic_LengthUnit>& aLengthUnit);

  Standard_EXPORT occ::handle<StepBasic_LengthUnit> LengthUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndLengthUnit, StepBasic_ConversionBasedUnit)

private:
  occ::handle<StepBasic_LengthUnit> lengthUnit;
};
