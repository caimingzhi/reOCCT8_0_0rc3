#include <StepBasic_MeasureWithUnit.hpp>
#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthDatRef.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthDatRef, StepDimTol_GeometricTolerance)

StepDimTol_GeoTolAndGeoTolWthDatRef::StepDimTol_GeoTolAndGeoTolWthDatRef() = default;

void StepDimTol_GeoTolAndGeoTolWthDatRef::Init(
  const occ::handle<TCollection_HAsciiString>&                        theName,
  const occ::handle<TCollection_HAsciiString>&                        theDescription,
  const occ::handle<Standard_Transient>&                              theMagnitude,
  const occ::handle<StepRepr_ShapeAspect>&                            theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR,
  const StepDimTol_GeometricToleranceType                             theType)
{
  SetName(theName);
  SetDescription(theDescription);
  SetMagnitude(theMagnitude);
  SetTolerancedShapeAspect(theTolerancedShapeAspect);
  myGeometricToleranceWithDatumReference = theGTWDR;
  myToleranceType                        = theType;
}

void StepDimTol_GeoTolAndGeoTolWthDatRef::Init(
  const occ::handle<TCollection_HAsciiString>&                        theName,
  const occ::handle<TCollection_HAsciiString>&                        theDescription,
  const occ::handle<Standard_Transient>&                              theMagnitude,
  const StepDimTol_GeometricToleranceTarget&                          theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR,
  const StepDimTol_GeometricToleranceType                             theType)
{
  SetName(theName);
  SetDescription(theDescription);
  SetMagnitude(theMagnitude);
  SetTolerancedShapeAspect(theTolerancedShapeAspect);
  myGeometricToleranceWithDatumReference = theGTWDR;
  myToleranceType                        = theType;
}
