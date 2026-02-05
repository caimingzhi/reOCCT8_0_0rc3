#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol.hpp>
#include <StepDimTol_UnequallyDisposedGeometricTolerance.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol,
                           StepDimTol_GeoTolAndGeoTolWthDatRef)

//=================================================================================================

StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol::
  StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol() = default;

//=================================================================================================

void StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol::Init(
  const occ::handle<TCollection_HAsciiString>&                        theName,
  const occ::handle<TCollection_HAsciiString>&                        theDescription,
  const occ::handle<Standard_Transient>&                              theMagnitude,
  const occ::handle<StepRepr_ShapeAspect>&                            theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR,
  const StepDimTol_GeometricToleranceType                             theType,
  const occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance>&  theUDGT)
{
  StepDimTol_GeoTolAndGeoTolWthDatRef::Init(theName,
                                            theDescription,
                                            theMagnitude,
                                            theTolerancedShapeAspect,
                                            theGTWDR,
                                            theType);
  myUnequallyDisposedGeometricTolerance = theUDGT;
}

//=================================================================================================

void StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol::Init(
  const occ::handle<TCollection_HAsciiString>&                        theName,
  const occ::handle<TCollection_HAsciiString>&                        theDescription,
  const occ::handle<Standard_Transient>&                              theMagnitude,
  const StepDimTol_GeometricToleranceTarget&                          theTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR,
  const StepDimTol_GeometricToleranceType                             theType,
  const occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance>&  theUDGT)
{
  StepDimTol_GeoTolAndGeoTolWthDatRef::Init(theName,
                                            theDescription,
                                            theMagnitude,
                                            theTolerancedShapeAspect,
                                            theGTWDR,
                                            theType);
  myUnequallyDisposedGeometricTolerance = theUDGT;
}
