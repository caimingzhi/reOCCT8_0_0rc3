#include "RWStepDimTol_RWGeometricToleranceWithDefinedUnit.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_GeometricToleranceWithDefinedUnit.hpp>

RWStepDimTol_RWGeometricToleranceWithDefinedUnit::
  RWStepDimTol_RWGeometricToleranceWithDefinedUnit() = default;

void RWStepDimTol_RWGeometricToleranceWithDefinedUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&                      data,
  const int                                                        num,
  occ::handle<Interface_Check>&                                    ach,
  const occ::handle<StepDimTol_GeometricToleranceWithDefinedUnit>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "geometric_tolerance_with_defined_unit"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "geometric_tolerance.name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "geometric_tolerance.description", ach, aDescription);

  occ::handle<Standard_Transient> aMagnitude;
  data->ReadEntity(num,
                   3,
                   "geometric_tolerance.magnitude",
                   ach,
                   STANDARD_TYPE(Standard_Transient),
                   aMagnitude);

  StepDimTol_GeometricToleranceTarget aTolerancedShapeAspect;
  data->ReadEntity(num,
                   4,
                   "geometric_tolerance.toleranced_shape_aspect",
                   ach,
                   aTolerancedShapeAspect);

  occ::handle<StepBasic_LengthMeasureWithUnit> anUnitSize;
  data->ReadEntity(num,
                   5,
                   "unit_size",
                   ach,
                   STANDARD_TYPE(StepBasic_LengthMeasureWithUnit),
                   anUnitSize);

  ent->Init(aName, aDescription, aMagnitude, aTolerancedShapeAspect, anUnitSize);
}

void RWStepDimTol_RWGeometricToleranceWithDefinedUnit::WriteStep(
  StepData_StepWriter&                                             SW,
  const occ::handle<StepDimTol_GeometricToleranceWithDefinedUnit>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->Magnitude());

  SW.Send(ent->TolerancedShapeAspect().Value());

  SW.Send(ent->UnitSize());
}

void RWStepDimTol_RWGeometricToleranceWithDefinedUnit::Share(
  const occ::handle<StepDimTol_GeometricToleranceWithDefinedUnit>& ent,
  Interface_EntityIterator&                                        iter) const
{

  iter.AddItem(ent->Magnitude());

  iter.AddItem(ent->TolerancedShapeAspect().Value());
}
