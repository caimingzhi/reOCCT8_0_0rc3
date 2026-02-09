

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWHalfSpaceSolid.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Surface.hpp>
#include <StepShape_HalfSpaceSolid.hpp>

RWStepShape_RWHalfSpaceSolid::RWStepShape_RWHalfSpaceSolid() = default;

void RWStepShape_RWHalfSpaceSolid::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepShape_HalfSpaceSolid>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "half_space_solid"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Surface> aBaseSurface;

  data->ReadEntity(num, 2, "base_surface", ach, STANDARD_TYPE(StepGeom_Surface), aBaseSurface);

  bool aAgreementFlag;

  data->ReadBoolean(num, 3, "agreement_flag", ach, aAgreementFlag);

  ent->Init(aName, aBaseSurface, aAgreementFlag);
}

void RWStepShape_RWHalfSpaceSolid::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepShape_HalfSpaceSolid>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BaseSurface());

  SW.SendBoolean(ent->AgreementFlag());
}

void RWStepShape_RWHalfSpaceSolid::Share(const occ::handle<StepShape_HalfSpaceSolid>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->BaseSurface());
}
