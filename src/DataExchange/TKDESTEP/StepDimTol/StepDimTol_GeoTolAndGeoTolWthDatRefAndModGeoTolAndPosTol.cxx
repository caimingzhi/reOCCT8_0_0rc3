

#include <StepBasic_MeasureWithUnit.hpp>
#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.hpp>
#include <StepDimTol_ModifiedGeometricTolerance.hpp>
#include <StepDimTol_PositionTolerance.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol,
                           StepDimTol_GeometricTolerance)

StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol::
  StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol() = default;

void StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol::Init(
  const occ::handle<TCollection_HAsciiString>&                        aName,
  const occ::handle<TCollection_HAsciiString>&                        aDescription,
  const occ::handle<Standard_Transient>&                              aMagnitude,
  const occ::handle<StepRepr_ShapeAspect>&                            aTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& aGTWDR,
  const occ::handle<StepDimTol_ModifiedGeometricTolerance>&           aMGT)
{
  SetName(aName);
  SetDescription(aDescription);
  SetMagnitude(aMagnitude);
  SetTolerancedShapeAspect(aTolerancedShapeAspect);
  myGeometricToleranceWithDatumReference = aGTWDR;
  myModifiedGeometricTolerance           = aMGT;
}

void StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol::Init(
  const occ::handle<TCollection_HAsciiString>&                        aName,
  const occ::handle<TCollection_HAsciiString>&                        aDescription,
  const occ::handle<Standard_Transient>&                              aMagnitude,
  const StepDimTol_GeometricToleranceTarget&                          aTolerancedShapeAspect,
  const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& aGTWDR,
  const occ::handle<StepDimTol_ModifiedGeometricTolerance>&           aMGT)
{
  SetName(aName);
  SetDescription(aDescription);
  SetMagnitude(aMagnitude);
  SetTolerancedShapeAspect(aTolerancedShapeAspect);
  myGeometricToleranceWithDatumReference = aGTWDR;
  myModifiedGeometricTolerance           = aMGT;
}

void StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol::
  SetGeometricToleranceWithDatumReference(
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& aGTWDR)
{
  myGeometricToleranceWithDatumReference = aGTWDR;
}

occ::handle<StepDimTol_GeometricToleranceWithDatumReference>
  StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol::
    GetGeometricToleranceWithDatumReference() const
{
  return myGeometricToleranceWithDatumReference;
}

void StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol::SetModifiedGeometricTolerance(
  const occ::handle<StepDimTol_ModifiedGeometricTolerance>& aMGT)
{
  myModifiedGeometricTolerance = aMGT;
}

occ::handle<StepDimTol_ModifiedGeometricTolerance>
  StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol::GetModifiedGeometricTolerance() const
{
  return myModifiedGeometricTolerance;
}

void StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol::SetPositionTolerance(
  const occ::handle<StepDimTol_PositionTolerance>& aPT)
{
  myPositionTolerance = aPT;
}

occ::handle<StepDimTol_PositionTolerance> StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol::
  GetPositionTolerance() const
{
  return myPositionTolerance;
}
