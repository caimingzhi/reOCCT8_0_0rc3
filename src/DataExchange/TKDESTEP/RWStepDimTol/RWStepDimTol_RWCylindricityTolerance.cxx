#include <Interface_EntityIterator.hpp>
#include "RWStepDimTol_RWCylindricityTolerance.hpp"
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_CylindricityTolerance.hpp>
#include <StepDimTol_GeometricToleranceTarget.hpp>

RWStepDimTol_RWCylindricityTolerance::RWStepDimTol_RWCylindricityTolerance() = default;

void RWStepDimTol_RWCylindricityTolerance::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepDimTol_CylindricityTolerance>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "cylindricity_tolerance"))
    return;

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

  ent->Init(aGeometricTolerance_Name,
            aGeometricTolerance_Description,
            aGeometricTolerance_Magnitude,
            aGeometricTolerance_TolerancedShapeAspect);
}

void RWStepDimTol_RWCylindricityTolerance::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepDimTol_CylindricityTolerance>& ent) const
{

  SW.Send(ent->StepDimTol_GeometricTolerance::Name());

  SW.Send(ent->StepDimTol_GeometricTolerance::Description());

  SW.Send(ent->StepDimTol_GeometricTolerance::Magnitude());

  SW.Send(ent->StepDimTol_GeometricTolerance::TolerancedShapeAspect().Value());
}

void RWStepDimTol_RWCylindricityTolerance::Share(
  const occ::handle<StepDimTol_CylindricityTolerance>& ent,
  Interface_EntityIterator&                            iter) const
{

  iter.AddItem(ent->StepDimTol_GeometricTolerance::Magnitude());

  iter.AddItem(ent->StepDimTol_GeometricTolerance::TolerancedShapeAspect().Value());
}
