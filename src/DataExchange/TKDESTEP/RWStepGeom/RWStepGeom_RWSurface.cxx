

#include "RWStepGeom_RWSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Surface.hpp>

RWStepGeom_RWSurface::RWStepGeom_RWSurface() = default;

void RWStepGeom_RWSurface::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                    const int                                   num,
                                    occ::handle<Interface_Check>&               ach,
                                    const occ::handle<StepGeom_Surface>&        ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepGeom_RWSurface::WriteStep(StepData_StepWriter&                 SW,
                                     const occ::handle<StepGeom_Surface>& ent) const
{

  SW.Send(ent->Name());
}
