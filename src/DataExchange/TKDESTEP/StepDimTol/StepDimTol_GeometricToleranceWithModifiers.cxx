#include <StepDimTol_GeometricToleranceWithModifiers.hpp>

#include <StepDimTol_GeometricToleranceTarget.hpp>
#include <StepDimTol_GeometricToleranceModifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithModifiers,
                           StepDimTol_GeometricTolerance)

StepDimTol_GeometricToleranceWithModifiers::StepDimTol_GeometricToleranceWithModifiers() = default;

void StepDimTol_GeometricToleranceWithModifiers::Init(
  const occ::handle<TCollection_HAsciiString>& theName,
  const occ::handle<TCollection_HAsciiString>& theDescription,
  const occ::handle<Standard_Transient>&       theMagnitude,
  const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect,
  const occ::handle<NCollection_HArray1<StepDimTol_GeometricToleranceModifier>>& theModifiers)
{
  StepDimTol_GeometricTolerance::Init(theName,
                                      theDescription,
                                      theMagnitude,
                                      theTolerancedShapeAspect);
  myModifiers = theModifiers;
}
