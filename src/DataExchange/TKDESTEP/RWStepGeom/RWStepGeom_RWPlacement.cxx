

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWPlacement.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Placement.hpp>

RWStepGeom_RWPlacement::RWStepGeom_RWPlacement() = default;

void RWStepGeom_RWPlacement::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepGeom_Placement>&      ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "placement"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_CartesianPoint> aLocation;

  data->ReadEntity(num, 2, "location", ach, STANDARD_TYPE(StepGeom_CartesianPoint), aLocation);

  ent->Init(aName, aLocation);
}

void RWStepGeom_RWPlacement::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepGeom_Placement>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Location());
}

void RWStepGeom_RWPlacement::Share(const occ::handle<StepGeom_Placement>& ent,
                                   Interface_EntityIterator&              iter) const
{

  iter.GetOneItem(ent->Location());
}
