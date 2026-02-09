

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWRevolvedAreaSolid.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepShape_RevolvedAreaSolid.hpp>

RWStepShape_RWRevolvedAreaSolid::RWStepShape_RWRevolvedAreaSolid() = default;

void RWStepShape_RWRevolvedAreaSolid::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepShape_RevolvedAreaSolid>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "revolved_area_solid"))
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

  occ::handle<StepGeom_Axis1Placement> aAxis;

  data->ReadEntity(num, 3, "axis", ach, STANDARD_TYPE(StepGeom_Axis1Placement), aAxis);

  double aAngle;

  data->ReadReal(num, 4, "angle", ach, aAngle);

  ent->Init(aName, aSweptArea, aAxis, aAngle);
}

void RWStepShape_RWRevolvedAreaSolid::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepShape_RevolvedAreaSolid>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SweptArea());

  SW.Send(ent->Axis());

  SW.Send(ent->Angle());
}

void RWStepShape_RWRevolvedAreaSolid::Share(const occ::handle<StepShape_RevolvedAreaSolid>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->SweptArea());

  iter.GetOneItem(ent->Axis());
}
