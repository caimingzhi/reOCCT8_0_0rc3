#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ConversionBasedUnit.hpp>
class StepBasic_PlaneAngleUnit;
class StepBasic_DimensionalExponents;
class TCollection_HAsciiString;
class StepBasic_MeasureWithUnit;

class StepBasic_ConversionBasedUnitAndPlaneAngleUnit : public StepBasic_ConversionBasedUnit
{

public:
  Standard_EXPORT StepBasic_ConversionBasedUnitAndPlaneAngleUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
                            const occ::handle<TCollection_HAsciiString>&       aName,
                            const occ::handle<Standard_Transient>&             aConversionFactor);

  Standard_EXPORT void SetPlaneAngleUnit(
    const occ::handle<StepBasic_PlaneAngleUnit>& aPlaneAngleUnit);

  Standard_EXPORT occ::handle<StepBasic_PlaneAngleUnit> PlaneAngleUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndPlaneAngleUnit,
                          StepBasic_ConversionBasedUnit)

private:
  occ::handle<StepBasic_PlaneAngleUnit> planeAngleUnit;
};
