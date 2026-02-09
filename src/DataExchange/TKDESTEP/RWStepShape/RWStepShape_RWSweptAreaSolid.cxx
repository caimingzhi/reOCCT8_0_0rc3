

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWSweptAreaSolid.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepShape_SweptAreaSolid.hpp>

RWStepShape_RWSweptAreaSolid::RWStepShape_RWSweptAreaSolid() = default;

void RWStepShape_RWSweptAreaSolid::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepShape_SweptAreaSolid>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "swept_area_solid"))
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

  ent->Init(aName, aSweptArea);
}

void RWStepShape_RWSweptAreaSolid::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepShape_SweptAreaSolid>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SweptArea());
}

void RWStepShape_RWSweptAreaSolid::Share(const occ::handle<StepShape_SweptAreaSolid>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->SweptArea());
}
