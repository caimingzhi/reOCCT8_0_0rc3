

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWRevolvedFaceSolid.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepShape_RevolvedFaceSolid.hpp>

RWStepShape_RWRevolvedFaceSolid::RWStepShape_RWRevolvedFaceSolid() = default;

void RWStepShape_RWRevolvedFaceSolid::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepShape_RevolvedFaceSolid>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "revolved_face_solid"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_FaceSurface> aSweptFace;

  data->ReadEntity(num, 2, "swept_face", ach, STANDARD_TYPE(StepShape_FaceSurface), aSweptFace);

  occ::handle<StepGeom_Axis1Placement> aAxis;

  data->ReadEntity(num, 3, "axis", ach, STANDARD_TYPE(StepGeom_Axis1Placement), aAxis);

  double aAngle;

  data->ReadReal(num, 4, "angle", ach, aAngle);

  ent->Init(aName, aSweptFace, aAxis, aAngle);
}

void RWStepShape_RWRevolvedFaceSolid::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepShape_RevolvedFaceSolid>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SweptFace());

  SW.Send(ent->Axis());

  SW.Send(ent->Angle());
}

void RWStepShape_RWRevolvedFaceSolid::Share(const occ::handle<StepShape_RevolvedFaceSolid>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->SweptFace());
  iter.GetOneItem(ent->Axis());
}
