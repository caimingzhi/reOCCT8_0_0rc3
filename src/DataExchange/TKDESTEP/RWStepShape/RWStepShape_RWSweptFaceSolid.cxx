

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWSweptFaceSolid.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepShape_SweptFaceSolid.hpp>

RWStepShape_RWSweptFaceSolid::RWStepShape_RWSweptFaceSolid() = default;

void RWStepShape_RWSweptFaceSolid::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepShape_SweptFaceSolid>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "swept_face_solid"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_FaceSurface> aSweptFace;

  data->ReadEntity(num, 2, "swept_face", ach, STANDARD_TYPE(StepShape_FaceSurface), aSweptFace);

  ent->Init(aName, aSweptFace);
}

void RWStepShape_RWSweptFaceSolid::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepShape_SweptFaceSolid>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SweptFace());
}

void RWStepShape_RWSweptFaceSolid::Share(const occ::handle<StepShape_SweptFaceSolid>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->SweptFace());
}
