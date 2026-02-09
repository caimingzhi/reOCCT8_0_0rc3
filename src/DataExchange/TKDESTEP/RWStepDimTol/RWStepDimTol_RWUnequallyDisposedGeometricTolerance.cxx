#include "RWStepDimTol_RWUnequallyDisposedGeometricTolerance.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_UnequallyDisposedGeometricTolerance.hpp>

RWStepDimTol_RWUnequallyDisposedGeometricTolerance::
  RWStepDimTol_RWUnequallyDisposedGeometricTolerance() = default;

void RWStepDimTol_RWUnequallyDisposedGeometricTolerance::ReadStep(
  const occ::handle<StepData_StepReaderData>&                        data,
  const int                                                          num,
  occ::handle<Interface_Check>&                                      ach,
  const occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "unequally_disposed_geometric_tolerance"))
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

  occ::handle<StepBasic_LengthMeasureWithUnit> aDisplacement;
  data->ReadEntity(num,
                   5,
                   "displacement",
                   ach,
                   STANDARD_TYPE(StepBasic_LengthMeasureWithUnit),
                   aDisplacement);

  ent->Init(aName, aDescription, aMagnitude, aTolerancedShapeAspect, aDisplacement);
}

void RWStepDimTol_RWUnequallyDisposedGeometricTolerance::WriteStep(
  StepData_StepWriter&                                               SW,
  const occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->Magnitude());

  SW.Send(ent->TolerancedShapeAspect().Value());

  SW.Send(ent->Displacement());
}

void RWStepDimTol_RWUnequallyDisposedGeometricTolerance::Share(
  const occ::handle<StepDimTol_UnequallyDisposedGeometricTolerance>& ent,
  Interface_EntityIterator&                                          iter) const
{

  iter.AddItem(ent->Magnitude());

  iter.AddItem(ent->TolerancedShapeAspect().Value());
}
