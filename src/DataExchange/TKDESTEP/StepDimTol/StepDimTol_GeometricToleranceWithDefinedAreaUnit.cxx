#include <StepDimTol_GeometricToleranceWithDefinedAreaUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithDefinedAreaUnit,
                           StepDimTol_GeometricToleranceWithDefinedUnit)

StepDimTol_GeometricToleranceWithDefinedAreaUnit::
  StepDimTol_GeometricToleranceWithDefinedAreaUnit() = default;

void StepDimTol_GeometricToleranceWithDefinedAreaUnit::Init(
  const occ::handle<TCollection_HAsciiString>&        theName,
  const occ::handle<TCollection_HAsciiString>&        theDescription,
  const occ::handle<Standard_Transient>&              theMagnitude,
  const StepDimTol_GeometricToleranceTarget&          theTolerancedShapeAspect,
  const occ::handle<StepBasic_LengthMeasureWithUnit>& theUnitSize,
  const StepDimTol_AreaUnitType                       theUnitType,
  const bool                                          theHasSecondUnitSize,
  const occ::handle<StepBasic_LengthMeasureWithUnit>& theSecondUnitSize)
{
  StepDimTol_GeometricToleranceWithDefinedUnit::Init(theName,
                                                     theDescription,
                                                     theMagnitude,
                                                     theTolerancedShapeAspect,
                                                     theUnitSize);
  myAreaType = theUnitType;
  if (theHasSecondUnitSize)
    mySecondUnitSize = theSecondUnitSize;
  else
    mySecondUnitSize.Nullify();
}
