#include <Interface_EntityIterator.hpp>
#include "RWStepDimTol_RWGeometricToleranceRelationship.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_GeometricTolerance.hpp>
#include <StepDimTol_GeometricToleranceRelationship.hpp>

RWStepDimTol_RWGeometricToleranceRelationship::RWStepDimTol_RWGeometricToleranceRelationship() =
  default;

void RWStepDimTol_RWGeometricToleranceRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepDimTol_GeometricToleranceRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "geometric_tolerance_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<StepDimTol_GeometricTolerance> aRelatingGeometricTolerance;
  data->ReadEntity(num,
                   3,
                   "relating_geometric_tolerance",
                   ach,
                   STANDARD_TYPE(StepDimTol_GeometricTolerance),
                   aRelatingGeometricTolerance);

  occ::handle<StepDimTol_GeometricTolerance> aRelatedGeometricTolerance;
  data->ReadEntity(num,
                   4,
                   "related_geometric_tolerance",
                   ach,
                   STANDARD_TYPE(StepDimTol_GeometricTolerance),
                   aRelatedGeometricTolerance);

  ent->Init(aName, aDescription, aRelatingGeometricTolerance, aRelatedGeometricTolerance);
}

void RWStepDimTol_RWGeometricToleranceRelationship::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepDimTol_GeometricToleranceRelationship>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->RelatingGeometricTolerance());

  SW.Send(ent->RelatedGeometricTolerance());
}

void RWStepDimTol_RWGeometricToleranceRelationship::Share(
  const occ::handle<StepDimTol_GeometricToleranceRelationship>& ent,
  Interface_EntityIterator&                                     iter) const
{

  iter.AddItem(ent->RelatingGeometricTolerance());

  iter.AddItem(ent->RelatedGeometricTolerance());
}
