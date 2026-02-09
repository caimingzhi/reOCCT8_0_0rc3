#include <StepBasic_MeasureWithUnit.hpp>
#include <StepDimTol_GeometricTolerance.hpp>
#include <StepDimTol_GeometricToleranceTarget.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeometricTolerance, Standard_Transient)

StepDimTol_GeometricTolerance::StepDimTol_GeometricTolerance() = default;

void StepDimTol_GeometricTolerance::Init(
  const occ::handle<TCollection_HAsciiString>& theName,
  const occ::handle<TCollection_HAsciiString>& theDescription,
  const occ::handle<Standard_Transient>&       theMagnitude,
  const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect)
{

  myName = theName;

  myDescription = theDescription;

  myMagnitude = theMagnitude;

  myTolerancedShapeAspect = theTolerancedShapeAspect;
}

void StepDimTol_GeometricTolerance::Init(
  const occ::handle<TCollection_HAsciiString>& theName,
  const occ::handle<TCollection_HAsciiString>& theDescription,
  const occ::handle<Standard_Transient>&       theMagnitude,
  const occ::handle<StepRepr_ShapeAspect>&     theTolerancedShapeAspect)
{

  myName = theName;

  myDescription = theDescription;

  myMagnitude = theMagnitude;

  myTolerancedShapeAspect.SetValue(theTolerancedShapeAspect);
}

occ::handle<TCollection_HAsciiString> StepDimTol_GeometricTolerance::Name() const
{
  return myName;
}

void StepDimTol_GeometricTolerance::SetName(const occ::handle<TCollection_HAsciiString>& theName)
{
  myName = theName;
}

occ::handle<TCollection_HAsciiString> StepDimTol_GeometricTolerance::Description() const
{
  return myDescription;
}

void StepDimTol_GeometricTolerance::SetDescription(
  const occ::handle<TCollection_HAsciiString>& theDescription)
{
  myDescription = theDescription;
}

occ::handle<Standard_Transient> StepDimTol_GeometricTolerance::Magnitude() const
{
  return myMagnitude;
}

void StepDimTol_GeometricTolerance::SetMagnitude(
  const occ::handle<Standard_Transient>& theMagnitude)
{
  myMagnitude = theMagnitude;
}

StepDimTol_GeometricToleranceTarget StepDimTol_GeometricTolerance::TolerancedShapeAspect() const
{
  return myTolerancedShapeAspect;
}

void StepDimTol_GeometricTolerance::SetTolerancedShapeAspect(
  const occ::handle<StepRepr_ShapeAspect>& theTolerancedShapeAspect)
{
  myTolerancedShapeAspect.SetValue(theTolerancedShapeAspect);
}

void StepDimTol_GeometricTolerance::SetTolerancedShapeAspect(
  const StepDimTol_GeometricToleranceTarget& theTolerancedShapeAspect)
{
  myTolerancedShapeAspect = theTolerancedShapeAspect;
}
