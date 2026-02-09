#include <StepBasic_MeasureWithUnit.hpp>
#include <StepDimTol_ModifiedGeometricTolerance.hpp>
#include <StepDimTol_GeometricToleranceTarget.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_ModifiedGeometricTolerance, StepDimTol_GeometricTolerance)

StepDimTol_ModifiedGeometricTolerance::StepDimTol_ModifiedGeometricTolerance() = default;

void StepDimTol_ModifiedGeometricTolerance::Init(
  const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
  const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
  const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
  const occ::handle<StepRepr_ShapeAspect>&     theGeometricTolerance_TolerancedShapeAspect,
  const StepDimTol_LimitCondition              theModifier)
{
  StepDimTol_GeometricTolerance::Init(theGeometricTolerance_Name,
                                      theGeometricTolerance_Description,
                                      theGeometricTolerance_Magnitude,
                                      theGeometricTolerance_TolerancedShapeAspect);

  myModifier = theModifier;
}

void StepDimTol_ModifiedGeometricTolerance::Init(
  const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
  const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
  const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
  const StepDimTol_GeometricToleranceTarget&   theGeometricTolerance_TolerancedShapeAspect,
  const StepDimTol_LimitCondition              theModifier)
{
  StepDimTol_GeometricTolerance::Init(theGeometricTolerance_Name,
                                      theGeometricTolerance_Description,
                                      theGeometricTolerance_Magnitude,
                                      theGeometricTolerance_TolerancedShapeAspect);

  myModifier = theModifier;
}

StepDimTol_LimitCondition StepDimTol_ModifiedGeometricTolerance::Modifier() const
{
  return myModifier;
}

void StepDimTol_ModifiedGeometricTolerance::SetModifier(const StepDimTol_LimitCondition theModifier)
{
  myModifier = theModifier;
}
