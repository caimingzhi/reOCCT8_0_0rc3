#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthMaxTol.hpp>
#include <StepDimTol_GeometricToleranceWithModifiers.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthMaxTol, StepDimTol_GeoTolAndGeoTolWthMod)

StepDimTol_GeoTolAndGeoTolWthMaxTol::StepDimTol_GeoTolAndGeoTolWthMaxTol() = default;

void StepDimTol_GeoTolAndGeoTolWthMaxTol::Init(
  const occ::handle<TCollection_HAsciiString>&                   theName,
  const occ::handle<TCollection_HAsciiString>&                   theDescription,
  const occ::handle<Standard_Transient>&                         theMagnitude,
  const occ::handle<StepRepr_ShapeAspect>&                       theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithModifiers>& theGTWM,
  const occ::handle<StepBasic_LengthMeasureWithUnit>&            theMaxTol,
  const StepDimTol_GeometricToleranceType                        theType)
{
  StepDimTol_GeoTolAndGeoTolWthMod::Init(theName,
                                         theDescription,
                                         theMagnitude,
                                         theTolerancedShapeAspect,
                                         theGTWM,
                                         theType);
  myMaxTol = theMaxTol;
}

void StepDimTol_GeoTolAndGeoTolWthMaxTol::Init(
  const occ::handle<TCollection_HAsciiString>&                   theName,
  const occ::handle<TCollection_HAsciiString>&                   theDescription,
  const occ::handle<Standard_Transient>&                         theMagnitude,
  const StepDimTol_GeometricToleranceTarget&                     theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithModifiers>& theGTWM,
  const occ::handle<StepBasic_LengthMeasureWithUnit>&            theMaxTol,
  const StepDimTol_GeometricToleranceType                        theType)
{
  StepDimTol_GeoTolAndGeoTolWthMod::Init(theName,
                                         theDescription,
                                         theMagnitude,
                                         theTolerancedShapeAspect,
                                         theGTWM,
                                         theType);
  myMaxTol = theMaxTol;
}
