#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepDimTol_RWCircularRunoutTolerance.hpp"
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_CircularRunoutTolerance.hpp>
#include <StepDimTol_GeometricToleranceTarget.hpp>
#include <StepDimTol_DatumSystemOrReference.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//=================================================================================================

RWStepDimTol_RWCircularRunoutTolerance::RWStepDimTol_RWCircularRunoutTolerance() = default;

//=================================================================================================

void RWStepDimTol_RWCircularRunoutTolerance::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepDimTol_CircularRunoutTolerance>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 5, ach, "circular_runout_tolerance"))
    return;

  // Inherited fields of GeometricTolerance

  occ::handle<TCollection_HAsciiString> aGeometricTolerance_Name;
  data->ReadString(num, 1, "geometric_tolerance.name", ach, aGeometricTolerance_Name);

  occ::handle<TCollection_HAsciiString> aGeometricTolerance_Description;
  data->ReadString(num, 2, "geometric_tolerance.description", ach, aGeometricTolerance_Description);

  occ::handle<Standard_Transient> aGeometricTolerance_Magnitude;
  data->ReadEntity(num,
                   3,
                   "geometric_tolerance.magnitude",
                   ach,
                   STANDARD_TYPE(Standard_Transient),
                   aGeometricTolerance_Magnitude);

  StepDimTol_GeometricToleranceTarget aGeometricTolerance_TolerancedShapeAspect;
  data->ReadEntity(num,
                   4,
                   "geometric_tolerance.toleranced_shape_aspect",
                   ach,
                   aGeometricTolerance_TolerancedShapeAspect);

  // Inherited fields of GeometricToleranceWithDatumReference

  occ::handle<NCollection_HArray1<StepDimTol_DatumSystemOrReference>>
      aGeometricToleranceWithDatumReference_DatumSystem;
  int sub5 = 0;
  if (data->ReadSubList(num, 5, "geometric_tolerance_with_datum_reference.datum_system", ach, sub5))
  {
    int nb0 = data->NbParams(sub5);
    aGeometricToleranceWithDatumReference_DatumSystem =
      new NCollection_HArray1<StepDimTol_DatumSystemOrReference>(1, nb0);
    int num2 = sub5;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepDimTol_DatumSystemOrReference anIt0;
      data->ReadEntity(num2, i0, "datum_system_or_reference", ach, anIt0);
      aGeometricToleranceWithDatumReference_DatumSystem->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aGeometricTolerance_Name,
            aGeometricTolerance_Description,
            aGeometricTolerance_Magnitude,
            aGeometricTolerance_TolerancedShapeAspect,
            aGeometricToleranceWithDatumReference_DatumSystem);
}

//=================================================================================================

void RWStepDimTol_RWCircularRunoutTolerance::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepDimTol_CircularRunoutTolerance>& ent) const
{

  // Inherited fields of GeometricTolerance

  SW.Send(ent->StepDimTol_GeometricTolerance::Name());

  SW.Send(ent->StepDimTol_GeometricTolerance::Description());

  SW.Send(ent->StepDimTol_GeometricTolerance::Magnitude());

  SW.Send(ent->StepDimTol_GeometricTolerance::TolerancedShapeAspect().Value());

  // Inherited fields of GeometricToleranceWithDatumReference

  SW.OpenSub();
  for (int i4 = 1;
       i4 <= ent->StepDimTol_GeometricToleranceWithDatumReference::DatumSystemAP242()->Length();
       i4++)
  {
    StepDimTol_DatumSystemOrReference Var0 =
      ent->StepDimTol_GeometricToleranceWithDatumReference::DatumSystemAP242()->Value(i4);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepDimTol_RWCircularRunoutTolerance::Share(
  const occ::handle<StepDimTol_CircularRunoutTolerance>& ent,
  Interface_EntityIterator&                              iter) const
{

  // Inherited fields of GeometricTolerance

  iter.AddItem(ent->StepDimTol_GeometricTolerance::Magnitude());

  iter.AddItem(ent->StepDimTol_GeometricTolerance::TolerancedShapeAspect().Value());

  // Inherited fields of GeometricToleranceWithDatumReference

  for (int i3 = 1;
       i3 <= ent->StepDimTol_GeometricToleranceWithDatumReference::DatumSystemAP242()->Length();
       i3++)
  {
    StepDimTol_DatumSystemOrReference Var0 =
      ent->StepDimTol_GeometricToleranceWithDatumReference::DatumSystemAP242()->Value(i3);
    iter.AddItem(Var0.Value());
  }
}
