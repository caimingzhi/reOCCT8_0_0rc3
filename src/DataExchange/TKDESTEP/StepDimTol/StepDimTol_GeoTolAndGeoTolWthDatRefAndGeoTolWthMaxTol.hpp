#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod.hpp>
#include <StepDimTol_GeometricToleranceType.hpp>
class StepDimTol_GeometricToleranceTarget;
class StepDimTol_GeometricToleranceWithDatumReference;
class StepDimTol_GeometricToleranceWithModifiers;
class TCollection_HAsciiString;
class StepBasic_LengthMeasureWithUnit;
class StepRepr_ShapeAspect;

class StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol
    : public StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod
{

public:
  Standard_EXPORT StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        theName,
    const occ::handle<TCollection_HAsciiString>&                        theDescription,
    const occ::handle<Standard_Transient>&                              theMagnitude,
    const occ::handle<StepRepr_ShapeAspect>&                            theTolerancedShapeAspect,
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR,
    const occ::handle<StepDimTol_GeometricToleranceWithModifiers>&      theGTWM,
    const occ::handle<StepBasic_LengthMeasureWithUnit>&                 theMaxTol,
    const StepDimTol_GeometricToleranceType                             theType);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        aName,
    const occ::handle<TCollection_HAsciiString>&                        aDescription,
    const occ::handle<Standard_Transient>&                              aMagnitude,
    const StepDimTol_GeometricToleranceTarget&                          aTolerancedShapeAspect,
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& aGTWDR,
    const occ::handle<StepDimTol_GeometricToleranceWithModifiers>&      aGTWM,
    const occ::handle<StepBasic_LengthMeasureWithUnit>&                 theMaxTol,
    const StepDimTol_GeometricToleranceType                             theType);

  inline void SetMaxTolerance(occ::handle<StepBasic_LengthMeasureWithUnit>& theMaxTol)
  {
    myMaxTol = theMaxTol;
  }

  inline occ::handle<StepBasic_LengthMeasureWithUnit> GetMaxTolerance() { return myMaxTol; }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol,
                          StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod)

private:
  occ::handle<StepBasic_LengthMeasureWithUnit> myMaxTol;
};
