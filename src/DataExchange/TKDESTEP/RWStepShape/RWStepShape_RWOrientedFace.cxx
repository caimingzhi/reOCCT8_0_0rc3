

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWOrientedFace.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_OrientedFace.hpp>

RWStepShape_RWOrientedFace::RWStepShape_RWOrientedFace() = default;

void RWStepShape_RWOrientedFace::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepShape_OrientedFace>&  ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "oriented_face"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  data->CheckDerived(num, 2, "bounds", ach, false);

  occ::handle<StepShape_Face> aFaceElement;

  data->ReadEntity(num, 3, "face_element", ach, STANDARD_TYPE(StepShape_Face), aFaceElement);

  bool aOrientation;

  data->ReadBoolean(num, 4, "orientation", ach, aOrientation);

  ent->Init(aName, aFaceElement, aOrientation);
}

void RWStepShape_RWOrientedFace::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepShape_OrientedFace>& ent) const
{

  SW.Send(ent->Name());

  SW.SendDerived();

  SW.Send(ent->FaceElement());

  SW.SendBoolean(ent->Orientation());
}

void RWStepShape_RWOrientedFace::Share(const occ::handle<StepShape_OrientedFace>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.GetOneItem(ent->FaceElement());
}
