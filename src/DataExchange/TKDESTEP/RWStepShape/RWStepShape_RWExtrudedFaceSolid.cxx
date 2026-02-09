

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWExtrudedFaceSolid.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Direction.hpp>
#include <StepShape_ExtrudedFaceSolid.hpp>
#include <StepShape_FaceSurface.hpp>

RWStepShape_RWExtrudedFaceSolid::RWStepShape_RWExtrudedFaceSolid() = default;

void RWStepShape_RWExtrudedFaceSolid::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepShape_ExtrudedFaceSolid>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "extruded_face_solid"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_FaceSurface> aSweptFace;

  data->ReadEntity(num, 2, "swept_face", ach, STANDARD_TYPE(StepShape_FaceSurface), aSweptFace);

  occ::handle<StepGeom_Direction> aExtrudedDirection;

  data->ReadEntity(num,
                   3,
                   "extruded_direction",
                   ach,
                   STANDARD_TYPE(StepGeom_Direction),
                   aExtrudedDirection);

  double aDepth;

  data->ReadReal(num, 4, "depth", ach, aDepth);

  ent->Init(aName, aSweptFace, aExtrudedDirection, aDepth);
}

void RWStepShape_RWExtrudedFaceSolid::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepShape_ExtrudedFaceSolid>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SweptFace());

  SW.Send(ent->ExtrudedDirection());

  SW.Send(ent->Depth());
}

void RWStepShape_RWExtrudedFaceSolid::Share(const occ::handle<StepShape_ExtrudedFaceSolid>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->SweptFace());
  iter.GetOneItem(ent->ExtrudedDirection());
}
