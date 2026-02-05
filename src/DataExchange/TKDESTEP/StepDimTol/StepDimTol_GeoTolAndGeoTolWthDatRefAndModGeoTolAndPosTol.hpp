#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepDimTol_GeometricTolerance.hpp>
class StepDimTol_GeometricToleranceTarget;
class StepDimTol_GeometricToleranceWithDatumReference;
class StepDimTol_ModifiedGeometricTolerance;
class StepDimTol_PositionTolerance;
class TCollection_HAsciiString;
class StepRepr_ShapeAspect;

class StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol
    : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        aName,
    const occ::handle<TCollection_HAsciiString>&                        aDescription,
    const occ::handle<Standard_Transient>&                              aMagnitude,
    const occ::handle<StepRepr_ShapeAspect>&                            aTolerancedShapeAspect,
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& aGTWDR,
    const occ::handle<StepDimTol_ModifiedGeometricTolerance>&           aMGT);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        aName,
    const occ::handle<TCollection_HAsciiString>&                        aDescription,
    const occ::handle<Standard_Transient>&                              aMagnitude,
    const StepDimTol_GeometricToleranceTarget&                          aTolerancedShapeAspect,
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& aGTWDR,
    const occ::handle<StepDimTol_ModifiedGeometricTolerance>&           aMGT);

  Standard_EXPORT void SetGeometricToleranceWithDatumReference(
    const occ::handle<StepDimTol_GeometricToleranceWithDatumReference>& aGTWDR);

  Standard_EXPORT occ::handle<StepDimTol_GeometricToleranceWithDatumReference>
                  GetGeometricToleranceWithDatumReference() const;

  Standard_EXPORT void SetModifiedGeometricTolerance(
    const occ::handle<StepDimTol_ModifiedGeometricTolerance>& aMGT);

  Standard_EXPORT occ::handle<StepDimTol_ModifiedGeometricTolerance> GetModifiedGeometricTolerance()
    const;

  Standard_EXPORT void SetPositionTolerance(const occ::handle<StepDimTol_PositionTolerance>& aPT);

  Standard_EXPORT occ::handle<StepDimTol_PositionTolerance> GetPositionTolerance() const;

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol,
                          StepDimTol_GeometricTolerance)

private:
  occ::handle<StepDimTol_GeometricToleranceWithDatumReference>
                                                     myGeometricToleranceWithDatumReference;
  occ::handle<StepDimTol_ModifiedGeometricTolerance> myModifiedGeometricTolerance;
  occ::handle<StepDimTol_PositionTolerance>          myPositionTolerance;
};
