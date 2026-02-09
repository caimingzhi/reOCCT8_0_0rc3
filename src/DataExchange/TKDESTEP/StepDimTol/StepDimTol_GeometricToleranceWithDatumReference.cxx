#include <Standard_Type.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithDatumReference,
                           StepDimTol_GeometricTolerance)

StepDimTol_GeometricToleranceWithDatumReference::StepDimTol_GeometricToleranceWithDatumReference() =
  default;

void StepDimTol_GeometricToleranceWithDatumReference::Init(
  const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
  const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
  const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
  const occ::handle<StepRepr_ShapeAspect>&     theGeometricTolerance_TolerancedShapeAspect,
  const occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReference>>>& theDatumSystem)
{
  StepDimTol_GeometricTolerance::Init(theGeometricTolerance_Name,
                                      theGeometricTolerance_Description,
                                      theGeometricTolerance_Magnitude,
                                      theGeometricTolerance_TolerancedShapeAspect);

  myDatumSystem =
    new NCollection_HArray1<StepDimTol_DatumSystemOrReference>(theDatumSystem->Lower(),
                                                               theDatumSystem->Upper());
  StepDimTol_DatumSystemOrReference anAux;
  for (int i = theDatumSystem->Lower(); i <= theDatumSystem->Upper(); i++)
  {
    anAux.SetValue(theDatumSystem->Value(i));
    myDatumSystem->SetValue(i, anAux);
  }
}

void StepDimTol_GeometricToleranceWithDatumReference::Init(
  const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Name,
  const occ::handle<TCollection_HAsciiString>& theGeometricTolerance_Description,
  const occ::handle<Standard_Transient>&       theGeometricTolerance_Magnitude,
  const StepDimTol_GeometricToleranceTarget&   theGeometricTolerance_TolerancedShapeAspect,
  const occ::handle<NCollection_HArray1<StepDimTol_DatumSystemOrReference>>& theDatumSystem)
{
  StepDimTol_GeometricTolerance::Init(theGeometricTolerance_Name,
                                      theGeometricTolerance_Description,
                                      theGeometricTolerance_Magnitude,
                                      theGeometricTolerance_TolerancedShapeAspect);

  myDatumSystem = theDatumSystem;
}

occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReference>>>
  StepDimTol_GeometricToleranceWithDatumReference::DatumSystem() const
{
  occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReference>>> aDatumSystem;
  aDatumSystem =
    new NCollection_HArray1<occ::handle<StepDimTol_DatumReference>>(myDatumSystem->Lower(),
                                                                    myDatumSystem->Upper());
  for (int i = aDatumSystem->Lower(); i <= aDatumSystem->Upper(); i++)
  {
    aDatumSystem->SetValue(i, myDatumSystem->Value(i).DatumReference());
  }
  return aDatumSystem;
}

occ::handle<NCollection_HArray1<StepDimTol_DatumSystemOrReference>>
  StepDimTol_GeometricToleranceWithDatumReference::DatumSystemAP242() const
{
  return myDatumSystem;
}

void StepDimTol_GeometricToleranceWithDatumReference::SetDatumSystem(
  const occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReference>>>& theDatumSystem)
{
  myDatumSystem =
    new NCollection_HArray1<StepDimTol_DatumSystemOrReference>(theDatumSystem->Lower(),
                                                               theDatumSystem->Upper());
  StepDimTol_DatumSystemOrReference anAux;
  for (int i = theDatumSystem->Lower(); i <= theDatumSystem->Upper(); i++)
  {
    anAux.SetValue(theDatumSystem->Value(i));
    myDatumSystem->SetValue(i, anAux);
  }
}

void StepDimTol_GeometricToleranceWithDatumReference::SetDatumSystem(
  const occ::handle<NCollection_HArray1<StepDimTol_DatumSystemOrReference>>& theDatumSystem)
{
  myDatumSystem = theDatumSystem;
}
