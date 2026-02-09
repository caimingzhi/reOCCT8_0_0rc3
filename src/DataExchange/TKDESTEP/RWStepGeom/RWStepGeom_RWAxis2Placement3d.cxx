

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWAxis2Placement3d.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>

RWStepGeom_RWAxis2Placement3d::RWStepGeom_RWAxis2Placement3d() = default;

void RWStepGeom_RWAxis2Placement3d::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepGeom_Axis2Placement3d>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "axis2_placement_3d"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_CartesianPoint> aLocation;

  data->ReadEntity(num, 2, "location", ach, STANDARD_TYPE(StepGeom_CartesianPoint), aLocation);

  occ::handle<StepGeom_Direction> aAxis;
  bool                            hasAaxis = false;
  if (data->IsParamDefined(num, 3))
  {

    hasAaxis = data->ReadEntity(num, 3, "axis", ach, STANDARD_TYPE(StepGeom_Direction), aAxis);
  }
  else
  {
    aAxis.Nullify();
  }

  occ::handle<StepGeom_Direction> aRefDirection;
  bool                            hasArefDirection = false;
  if (data->IsParamDefined(num, 4))
  {

    hasArefDirection = data->ReadEntity(num,
                                        4,
                                        "ref_direction",
                                        ach,
                                        STANDARD_TYPE(StepGeom_Direction),
                                        aRefDirection);
  }
  else
  {
    aRefDirection.Nullify();
  }

  ent->Init(aName, aLocation, hasAaxis, aAxis, hasArefDirection, aRefDirection);
}

void RWStepGeom_RWAxis2Placement3d::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepGeom_Axis2Placement3d>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Location());

  bool hasAaxis = ent->HasAxis();
  if (hasAaxis)
  {
    SW.Send(ent->Axis());
  }
  else
  {
    SW.SendUndef();
  }

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

void RWStepGeom_RWAxis2Placement3d::Share(const occ::handle<StepGeom_Axis2Placement3d>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  iter.GetOneItem(ent->Location());

  if (ent->HasAxis())
  {
    iter.GetOneItem(ent->Axis());
  }

  if (ent->HasRefDirection())
  {
    iter.GetOneItem(ent->RefDirection());
  }
}
