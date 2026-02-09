

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWAxis2Placement2d.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement2d.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>

RWStepGeom_RWAxis2Placement2d::RWStepGeom_RWAxis2Placement2d() = default;

void RWStepGeom_RWAxis2Placement2d::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepGeom_Axis2Placement2d>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "axis2_placement_2d"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_CartesianPoint> aLocation;

  data->ReadEntity(num, 2, "location", ach, STANDARD_TYPE(StepGeom_CartesianPoint), aLocation);

  occ::handle<StepGeom_Direction> aRefDirection;
  bool                            hasArefDirection = true;
  if (data->IsParamDefined(num, 3))
  {

    data
      ->ReadEntity(num, 3, "ref_direction", ach, STANDARD_TYPE(StepGeom_Direction), aRefDirection);
  }
  else
  {
    hasArefDirection = false;
    aRefDirection.Nullify();
  }

  ent->Init(aName, aLocation, hasArefDirection, aRefDirection);
}

void RWStepGeom_RWAxis2Placement2d::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepGeom_Axis2Placement2d>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Location());

  bool hasArefDirection = ent->HasRefDirection();
  if (hasArefDirection)
  {
    SW.Send(ent->RefDirection());
  }
  else
  {
    SW.SendUndef();
  }
}

void RWStepGeom_RWAxis2Placement2d::Share(const occ::handle<StepGeom_Axis2Placement2d>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  iter.GetOneItem(ent->Location());

  if (ent->HasRefDirection())
  {
    iter.GetOneItem(ent->RefDirection());
  }
}
