#include <StepDimTol_GeometricToleranceWithMaximumTolerance.hpp>

#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepDimTol_GeometricToleranceTarget.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithMaximumTolerance,
                           StepDimTol_GeometricToleranceWithModifiers)

StepDimTol_GeometricToleranceWithMaximumTolerance::
  StepDimTol_GeometricToleranceWithMaximumTolerance() = default;

void StepDimTol_GeometricToleranceWithMaximumTolerance::Init(
  const occ::handle<TCollection_HAsciiString>& theName,
  const occ::handle<TCollection_HAsciiString>& theDescription,
  const occ::handle<Standard_Transient>&       theMagnitude,
  const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect,
  const occ::handle<NCollection_HArray1<StepDimTol_GeometricToleranceModifier>>& theModifiers,
  const occ::handle<StepBasic_LengthMeasureWithUnit>& theMaximumUpperTolerance)
{
  StepDimTol_GeometricToleranceWithModifiers::Init(theName,
                                                   theDescription,
                                                   theMagnitude,
                                                   theTolerancedShapeAspect,
                                                   theModifiers);
  myMaximumUpperTolerance = theMaximumUpperTolerance;
}
