#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepDimTol_GeometricTolerance.hpp>
#include <StepDimTol_GeometricToleranceType.hpp>
class StepDimTol_GeometricToleranceTarget;
class StepDimTol_GeometricToleranceWithDatumReference;
class StepDimTol_GeometricToleranceWithModifiers;
class TCollection_HAsciiString;
class StepRepr_ShapeAspect;

class StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        theName,
    const occ::handle<TCollection_HAsciiString>&                        theDescription,
    const occ::handle<Standard_Transient>&                              theMagnitude,
    const occ::handle<StepRepr_ShapeAspect>&                            theTolerancedShapeAspect,
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR,
    const occ::handle<StepDimTol_GeometricToleranceWithModifiers>&      theGTWM,
    const StepDimTol_GeometricToleranceType                             theType);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        aName,
    const occ::handle<TCollection_HAsciiString>&                        aDescription,
    const occ::handle<Standard_Transient>&                              aMagnitude,
    const StepDimTol_GeometricToleranceTarget&                          aTolerancedShapeAspect,
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& aGTWDR,
    const occ::handle<StepDimTol_GeometricToleranceWithModifiers>&      aGTWM,
    const StepDimTol_GeometricToleranceType                             theType);

  inline void SetGeometricToleranceWithDatumReference(
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& theGTWDR)
  {
    myGeometricToleranceWithDatumReference = theGTWDR;
  }

  inline occ::handle<StepDimTol_GeometricToleranceWithDatumReference>
    GetGeometricToleranceWithDatumReference() const
  {
    return myGeometricToleranceWithDatumReference;
  }

  inline void SetGeometricToleranceWithModifiers(
    const occ::handle<StepDimTol_GeometricToleranceWithModifiers>& theGTWM)
  {
    myGeometricToleranceWithModifiers = theGTWM;
  }

  inline occ::handle<StepDimTol_GeometricToleranceWithModifiers>
    GetGeometricToleranceWithModifiers() const
  {
    return myGeometricToleranceWithModifiers;
  }

  inline void SetGeometricToleranceType(const StepDimTol_GeometricToleranceType theType)
  {
    myToleranceType = theType;
  }

  StepDimTol_GeometricToleranceType GetToleranceType() const { return myToleranceType; }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod,
                          StepDimTol_GeometricTolerance)

private:
  occ::handle<StepDimTol_GeometricToleranceWithDatumReference>
                                                          myGeometricToleranceWithDatumReference;
  occ::handle<StepDimTol_GeometricToleranceWithModifiers> myGeometricToleranceWithModifiers;
  StepDimTol_GeometricToleranceType                       myToleranceType;
};
