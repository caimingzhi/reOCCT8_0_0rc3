#include <StepDimTol_GeometricToleranceWithDefinedUnit.hpp>

#include <StepDimTol_GeometricToleranceTarget.hpp>
#include <StepRepr_ShapeAspect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithDefinedUnit,
                           StepDimTol_GeometricTolerance)

StepDimTol_GeometricToleranceWithDefinedUnit::StepDimTol_GeometricToleranceWithDefinedUnit() =
  default;

void StepDimTol_GeometricToleranceWithDefinedUnit::Init(
  const occ::handle<TCollection_HAsciiString>&        theName,
  const occ::handle<TCollection_HAsciiString>&        theDescription,
  const occ::handle<Standard_Transient>&              theMagnitude,
  const occ::handle<StepRepr_ShapeAspect>&            theTolerancedShapeAspect,
  const occ::handle<StepBasic_LengthMeasureWithUnit>& theUnitSize)
{
  StepDimTol_GeometricTolerance::Init(theName,
                                      theDescription,
                                      theMagnitude,
                                      theTolerancedShapeAspect);
  myUnitSize = theUnitSize;
}

void StepDimTol_GeometricToleranceWithDefinedUnit::Init(
  const occ::handle<TCollection_HAsciiString>&        theName,
  const occ::handle<TCollection_HAsciiString>&        theDescription,
  const occ::handle<Standard_Transient>&              theMagnitude,
  const StepDimTol_GeometricToleranceTarget&          theTolerancedShapeAspect,
  const occ::handle<StepBasic_LengthMeasureWithUnit>& theUnitSize)
{
  StepDimTol_GeometricTolerance::Init(theName,
                                      theDescription,
                                      theMagnitude,
                                      theTolerancedShapeAspect);
  myUnitSize = theUnitSize;
}
