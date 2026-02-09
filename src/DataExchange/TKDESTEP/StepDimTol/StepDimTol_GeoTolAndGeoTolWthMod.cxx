#include <StepBasic_MeasureWithUnit.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthMod.hpp>
#include <StepDimTol_GeometricToleranceWithModifiers.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthMod, StepDimTol_GeometricTolerance)

StepDimTol_GeoTolAndGeoTolWthMod::StepDimTol_GeoTolAndGeoTolWthMod() = default;

void StepDimTol_GeoTolAndGeoTolWthMod::Init(
  const occ::handle<TCollection_HAsciiString>&                   theName,
  const occ::handle<TCollection_HAsciiString>&                   theDescription,
  const occ::handle<Standard_Transient>&                         theMagnitude,
  const occ::handle<StepRepr_ShapeAspect>&                       theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithModifiers>& theGTWM,
  const StepDimTol_GeometricToleranceType                        theType)
{
  SetName(theName);
  SetDescription(theDescription);
  SetMagnitude(theMagnitude);
  SetTolerancedShapeAspect(theTolerancedShapeAspect);
  myGeometricToleranceWithModifiers = theGTWM;
  myToleranceType                   = theType;
}

void StepDimTol_GeoTolAndGeoTolWthMod::Init(
  const occ::handle<TCollection_HAsciiString>&                   theName,
  const occ::handle<TCollection_HAsciiString>&                   theDescription,
  const occ::handle<Standard_Transient>&                         theMagnitude,
  const StepDimTol_GeometricToleranceTarget&                     theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithModifiers>& theGTWM,
  const StepDimTol_GeometricToleranceType                        theType)
{
  SetName(theName);
  SetDescription(theDescription);
  SetMagnitude(theMagnitude);
  SetTolerancedShapeAspect(theTolerancedShapeAspect);
  myGeometricToleranceWithModifiers = theGTWM;
  myToleranceType                   = theType;
}
