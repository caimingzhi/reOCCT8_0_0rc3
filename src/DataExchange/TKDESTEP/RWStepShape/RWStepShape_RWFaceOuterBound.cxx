

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWFaceOuterBound.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_FaceOuterBound.hpp>
#include <StepShape_Loop.hpp>

RWStepShape_RWFaceOuterBound::RWStepShape_RWFaceOuterBound() = default;

void RWStepShape_RWFaceOuterBound::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepShape_FaceOuterBound>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "face_outer_bound"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_Loop> aBound;

  data->ReadEntity(num, 2, "bound", ach, STANDARD_TYPE(StepShape_Loop), aBound);

  bool aOrientation;

  data->ReadBoolean(num, 3, "orientation", ach, aOrientation);

  ent->Init(aName, aBound, aOrientation);
}

void RWStepShape_RWFaceOuterBound::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepShape_FaceOuterBound>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Bound());

  SW.SendBoolean(ent->Orientation());
}

void RWStepShape_RWFaceOuterBound::Share(const occ::handle<StepShape_FaceOuterBound>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->Bound());
}
