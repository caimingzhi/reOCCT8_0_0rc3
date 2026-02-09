

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWElementarySurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_ElementarySurface.hpp>

RWStepGeom_RWElementarySurface::RWStepGeom_RWElementarySurface() = default;

void RWStepGeom_RWElementarySurface::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepGeom_ElementarySurface>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "elementary_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis2Placement3d> aPosition;

  data->ReadEntity(num, 2, "position", ach, STANDARD_TYPE(StepGeom_Axis2Placement3d), aPosition);

  ent->Init(aName, aPosition);
}

void RWStepGeom_RWElementarySurface::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepGeom_ElementarySurface>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position());
}

void RWStepGeom_RWElementarySurface::Share(const occ::handle<StepGeom_ElementarySurface>& ent,
                                           Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->Position());
}
