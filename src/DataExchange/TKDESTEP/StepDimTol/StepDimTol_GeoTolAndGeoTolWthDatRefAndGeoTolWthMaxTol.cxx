#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol.hpp>
#include <StepDimTol_GeometricToleranceWithModifiers.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol,
                           StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod)

//=================================================================================================

StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol::
  StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol() = default;

//=================================================================================================

void StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol::Init(
  const occ::handle<TCollection_HAsciiString>&                        theName,
  const occ::handle<TCollection_HAsciiString>&                        theDescription,
  const occ::handle<Standard_Transient>&                              theMagnitude,
  const occ::handle<StepRepr_ShapeAspect>&                            theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR,
  const occ::handle<StepDimTol_GeometricToleranceWithModifiers>&      theGTWM,
  const occ::handle<StepBasic_LengthMeasureWithUnit>&                 theMaxTol,
  const StepDimTol_GeometricToleranceType                             theType)
{
  StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod::Init(theName,
                                                           theDescription,
                                                           theMagnitude,
                                                           theTolerancedShapeAspect,
                                                           theGTWDR,
                                                           theGTWM,
                                                           theType);
  myMaxTol = theMaxTol;
}

//=================================================================================================

void StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol::Init(
  const occ::handle<TCollection_HAsciiString>&                        theName,
  const occ::handle<TCollection_HAsciiString>&                        theDescription,
  const occ::handle<Standard_Transient>&                              theMagnitude,
  const StepDimTol_GeometricToleranceTarget&                          theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR,
  const occ::handle<StepDimTol_GeometricToleranceWithModifiers>&      theGTWM,
  const occ::handle<StepBasic_LengthMeasureWithUnit>&                 theMaxTol,
  const StepDimTol_GeometricToleranceType                             theType)
{
  StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod::Init(theName,
                                                           theDescription,
                                                           theMagnitude,
                                                           theTolerancedShapeAspect,
                                                           theGTWDR,
                                                           theGTWM,
                                                           theType);
  myMaxTol = theMaxTol;
}
