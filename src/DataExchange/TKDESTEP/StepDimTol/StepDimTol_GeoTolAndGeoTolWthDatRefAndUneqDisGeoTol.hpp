#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepDimTol_GeoTolAndGeoTolWthDatRef.hpp>
class StepDimTol_GeometricToleranceTarget;
class StepDimTol_GeometricToleranceWithDatumReference;
class StepDimTol_UnequallyDisposedGeometricTolerance;
class TCollection_HAsciiString;
class StepRepr_ShapeAspect;

class StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol
    : public StepDimTol_GeoTolAndGeoTolWthDatRef
{

public:
  Standard_EXPORT StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        theName,
    const occ::handle<TCollection_HAsciiString>&                        theDescription,
    const occ::handle<Standard_Transient>&                              theMagnitude,
    const occ::handle<StepRepr_ShapeAspect>&                            theTolerancedShapeAspect,
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR,
    const StepDimTol_GeometricToleranceType                             theType,
    const occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance>&  theUDGT);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        aName,
    const occ::handle<TCollection_HAsciiString>&                        aDescription,
    const occ::handle<Standard_Transient>&                              aMagnitude,
    const StepDimTol_GeometricToleranceTarget&                          aTolerancedShapeAspect,
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& aGTWDR,
    const StepDimTol_GeometricToleranceType                             theType,
    const occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance>&  theUDGT);

  inline void SetUnequallyDisposedGeometricTolerance(
    const occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance>& theUDGT)
  {
    myUnequallyDisposedGeometricTolerance = theUDGT;
  }

  inline occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance>
    GetUnequallyDisposedGeometricTolerance() const
  {
    return myUnequallyDisposedGeometricTolerance;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol,
                          StepDimTol_GeoTolAndGeoTolWthDatRef)

private:
  occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance> myUnequallyDisposedGeometricTolerance;
};
