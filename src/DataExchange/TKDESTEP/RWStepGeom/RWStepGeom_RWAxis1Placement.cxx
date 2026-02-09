

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWAxis1Placement.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>

RWStepGeom_RWAxis1Placement::RWStepGeom_RWAxis1Placement() = default;

void RWStepGeom_RWAxis1Placement::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepGeom_Axis1Placement>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "axis1_placement"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_CartesianPoint> aLocation;

  data->ReadEntity(num, 2, "location", ach, STANDARD_TYPE(StepGeom_CartesianPoint), aLocation);

  occ::handle<StepGeom_Direction> aAxis;
  bool                            hasAaxis = true;
  if (data->IsParamDefined(num, 3))
  {

    data->ReadEntity(num, 3, "axis", ach, STANDARD_TYPE(StepGeom_Direction), aAxis);
  }
  else
  {
    hasAaxis = false;
    aAxis.Nullify();
  }

  ent->Init(aName, aLocation, hasAaxis, aAxis);
}

void RWStepGeom_RWAxis1Placement::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepGeom_Axis1Placement>& ent) const
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
}

void RWStepGeom_RWAxis1Placement::Share(const occ::handle<StepGeom_Axis1Placement>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  iter.GetOneItem(ent->Location());

  if (ent->HasAxis())
  {
    iter.GetOneItem(ent->Axis());
  }
}
