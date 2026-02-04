#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ConversionBasedUnit.hpp>
class StepBasic_RatioUnit;
class StepBasic_DimensionalExponents;
class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;

class StepBasic_ConversionBasedUnitAndRatioUnit : public StepBasic_ConversionBasedUnit
{

public:
  //! Returns a ConversionBasedUnitAndRatioUnit
  Standard_EXPORT StepBasic_ConversionBasedUnitAndRatioUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
                            const occ::handle<TCollection_HAsciiString>&       aName,
                            const occ::handle<Standard_Transient>&             aConversionFactor);

  Standard_EXPORT void SetRatioUnit(const occ::handle<StepBasic_RatioUnit>& aRatioUnit);

  Standard_EXPORT occ::handle<StepBasic_RatioUnit> RatioUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndRatioUnit, StepBasic_ConversionBasedUnit)

private:
  occ::handle<StepBasic_RatioUnit> ratioUnit;
};

