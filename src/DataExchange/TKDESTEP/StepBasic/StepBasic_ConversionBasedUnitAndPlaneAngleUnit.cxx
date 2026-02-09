

#include <Standard_Type.hpp>
#include <StepBasic_ConversionBasedUnitAndPlaneAngleUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_PlaneAngleUnit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndPlaneAngleUnit,
                           StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndPlaneAngleUnit::StepBasic_ConversionBasedUnitAndPlaneAngleUnit() =
  default;

void StepBasic_ConversionBasedUnitAndPlaneAngleUnit::Init(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
  const occ::handle<TCollection_HAsciiString>&       aName,
  const occ::handle<Standard_Transient>&             aConversionFactor)
{

  StepBasic_ConversionBasedUnit::Init(aDimensions, aName, aConversionFactor);

  planeAngleUnit = new StepBasic_PlaneAngleUnit();
  planeAngleUnit->Init(aDimensions);
}

void StepBasic_ConversionBasedUnitAndPlaneAngleUnit::SetPlaneAngleUnit(
  const occ::handle<StepBasic_PlaneAngleUnit>& aPlaneAngleUnit)
{
  planeAngleUnit = aPlaneAngleUnit;
}

occ::handle<StepBasic_PlaneAngleUnit> StepBasic_ConversionBasedUnitAndPlaneAngleUnit::
  PlaneAngleUnit() const
{
  return planeAngleUnit;
}
