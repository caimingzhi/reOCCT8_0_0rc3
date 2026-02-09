

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWRightCircularCone.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepShape_RightCircularCone.hpp>

RWStepShape_RWRightCircularCone::RWStepShape_RWRightCircularCone() = default;

void RWStepShape_RWRightCircularCone::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepShape_RightCircularCone>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "right_circular_cone"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis1Placement> aPosition;

  data->ReadEntity(num, 2, "position", ach, STANDARD_TYPE(StepGeom_Axis1Placement), aPosition);

  double aHeight;

  data->ReadReal(num, 3, "height", ach, aHeight);

  double aRadius;

  data->ReadReal(num, 4, "radius", ach, aRadius);

  double aSemiAngle;

  data->ReadReal(num, 5, "semi_angle", ach, aSemiAngle);

  ent->Init(aName, aPosition, aHeight, aRadius, aSemiAngle);
}

void RWStepShape_RWRightCircularCone::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepShape_RightCircularCone>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position());

  SW.Send(ent->Height());

  SW.Send(ent->Radius());

  SW.Send(ent->SemiAngle());
}

void RWStepShape_RWRightCircularCone::Share(const occ::handle<StepShape_RightCircularCone>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->Position());
}
