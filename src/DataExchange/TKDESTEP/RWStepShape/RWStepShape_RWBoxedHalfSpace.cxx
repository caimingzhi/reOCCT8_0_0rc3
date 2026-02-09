

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWBoxedHalfSpace.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Surface.hpp>
#include <StepShape_BoxDomain.hpp>
#include <StepShape_BoxedHalfSpace.hpp>

RWStepShape_RWBoxedHalfSpace::RWStepShape_RWBoxedHalfSpace() = default;

void RWStepShape_RWBoxedHalfSpace::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepShape_BoxedHalfSpace>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "boxed_half_space"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Surface> aBaseSurface;

  data->ReadEntity(num, 2, "base_surface", ach, STANDARD_TYPE(StepGeom_Surface), aBaseSurface);

  bool aAgreementFlag;

  data->ReadBoolean(num, 3, "agreement_flag", ach, aAgreementFlag);

  occ::handle<StepShape_BoxDomain> aEnclosure;

  data->ReadEntity(num, 4, "enclosure", ach, STANDARD_TYPE(StepShape_BoxDomain), aEnclosure);

  ent->Init(aName, aBaseSurface, aAgreementFlag, aEnclosure);
}

void RWStepShape_RWBoxedHalfSpace::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepShape_BoxedHalfSpace>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BaseSurface());

  SW.SendBoolean(ent->AgreementFlag());

  SW.Send(ent->Enclosure());
}

void RWStepShape_RWBoxedHalfSpace::Share(const occ::handle<StepShape_BoxedHalfSpace>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->BaseSurface());

  iter.GetOneItem(ent->Enclosure());
}
