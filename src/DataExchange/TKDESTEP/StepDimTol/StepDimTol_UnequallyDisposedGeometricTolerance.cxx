#include <StepDimTol_UnequallyDisposedGeometricTolerance.hpp>

#include <StepDimTol_GeometricToleranceTarget.hpp>
#include <StepBasic_LengthMeasureWithUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_UnequallyDisposedGeometricTolerance,
                           StepDimTol_GeometricTolerance)

StepDimTol_UnequallyDisposedGeometricTolerance::StepDimTol_UnequallyDisposedGeometricTolerance() =
  default;

void StepDimTol_UnequallyDisposedGeometricTolerance::Init(
  const occ::handle<TCollection_HAsciiString>&        theName,
  const occ::handle<TCollection_HAsciiString>&        theDescription,
  const occ::handle<Standard_Transient>&              theMagnitude,
  const StepDimTol_GeometricToleranceTarget&          theTolerancedShapeAspect,
  const occ::handle<StepBasic_LengthMeasureWithUnit>& theDisplacement)
{
  StepDimTol_GeometricTolerance::Init(theName,
                                      theDescription,
                                      theMagnitude,
                                      theTolerancedShapeAspect);
  myDisplacement = theDisplacement;
}
