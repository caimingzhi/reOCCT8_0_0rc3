

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWRightCircularCylinder.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepShape_RightCircularCylinder.hpp>

RWStepShape_RWRightCircularCylinder::RWStepShape_RWRightCircularCylinder() = default;

void RWStepShape_RWRightCircularCylinder::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepShape_RightCircularCylinder>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "right_circular_cylinder"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis1Placement> aPosition;

  data->ReadEntity(num, 2, "position", ach, STANDARD_TYPE(StepGeom_Axis1Placement), aPosition);

  double aHeight;

  data->ReadReal(num, 3, "height", ach, aHeight);

  double aRadius;

  data->ReadReal(num, 4, "radius", ach, aRadius);

  ent->Init(aName, aPosition, aHeight, aRadius);
}

void RWStepShape_RWRightCircularCylinder::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepShape_RightCircularCylinder>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position());

  SW.Send(ent->Height());

  SW.Send(ent->Radius());
}

void RWStepShape_RWRightCircularCylinder::Share(
  const occ::handle<StepShape_RightCircularCylinder>& ent,
  Interface_EntityIterator&                           iter) const
{

  iter.GetOneItem(ent->Position());
}
