#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepDimTol_DatumReference.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepDimTol_DatumSystemOrReference.hpp>
#include <StepDimTol_GeometricTolerance.hpp>
class TCollection_HAsciiString;
class StepDimTol_GeometricToleranceTarget;
class StepRepr_ShapeAspect;

class StepDimTol_GeometricToleranceWithDatumReference : public StepDimTol_GeometricTolerance
{

public:
  Standard_EXPORT StepDimTol_GeometricToleranceWithDatumReference();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
    const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
    const occ::handle<StepRepr_ShapeAspect>&     theGeometricTolerance_TolerancedShapeAspect,
    const occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReference>>>& theDatumSystem);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
    const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
    const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
    const StepDimTol_GeometricToleranceTarget&   theGeometricTolerance_TolerancedShapeAspect,
    const occ::handle<NCollection_HArray1<StepDimTol_DatumSystemOrReference>>& theDatumSystem);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReference>>>
                  DatumSystem() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<StepDimTol_DatumSystemOrReference>>
                  DatumSystemAP242() const;

  Standard_EXPORT void SetDatumSystem(
    const occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReference>>>& theDatumSystem);

  Standard_EXPORT void SetDatumSystem(
    const occ::handle<NCollection_HArray1<StepDimTol_DatumSystemOrReference>>& theDatumSystem);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithDatumReference,
                          StepDimTol_GeometricTolerance)

private:
  occ::handle<NCollection_HArray1<StepDimTol_DatumSystemOrReference>> myDatumSystem;
};
