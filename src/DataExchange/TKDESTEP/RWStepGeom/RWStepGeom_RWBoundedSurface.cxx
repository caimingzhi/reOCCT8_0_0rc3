

#include "RWStepGeom_RWBoundedSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_BoundedSurface.hpp>

RWStepGeom_RWBoundedSurface::RWStepGeom_RWBoundedSurface() = default;

void RWStepGeom_RWBoundedSurface::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepGeom_BoundedSurface>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "bounded_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepGeom_RWBoundedSurface::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepGeom_BoundedSurface>& ent) const
{

  SW.Send(ent->Name());
}
