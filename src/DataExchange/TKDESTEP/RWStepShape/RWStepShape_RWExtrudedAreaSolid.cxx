

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWExtrudedAreaSolid.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepGeom_Direction.hpp>
#include <StepShape_ExtrudedAreaSolid.hpp>

RWStepShape_RWExtrudedAreaSolid::RWStepShape_RWExtrudedAreaSolid() = default;

void RWStepShape_RWExtrudedAreaSolid::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepShape_ExtrudedAreaSolid>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "extruded_area_solid"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_CurveBoundedSurface> aSweptArea;

  data->ReadEntity(num,
                   2,
                   "swept_area",
                   ach,
                   STANDARD_TYPE(StepGeom_CurveBoundedSurface),
                   aSweptArea);

  occ::handle<StepGeom_Direction> aExtrudedDirection;

  data->ReadEntity(num,
                   3,
                   "extruded_direction",
                   ach,
                   STANDARD_TYPE(StepGeom_Direction),
                   aExtrudedDirection);

  double aDepth;

  data->ReadReal(num, 4, "depth", ach, aDepth);

  ent->Init(aName, aSweptArea, aExtrudedDirection, aDepth);
}

void RWStepShape_RWExtrudedAreaSolid::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepShape_ExtrudedAreaSolid>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SweptArea());

  SW.Send(ent->ExtrudedDirection());

  SW.Send(ent->Depth());
}

void RWStepShape_RWExtrudedAreaSolid::Share(const occ::handle<StepShape_ExtrudedAreaSolid>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->SweptArea());

  iter.GetOneItem(ent->ExtrudedDirection());
}
