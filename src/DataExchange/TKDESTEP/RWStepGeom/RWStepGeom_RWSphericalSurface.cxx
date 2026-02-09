

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWSphericalSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_SphericalSurface.hpp>

RWStepGeom_RWSphericalSurface::RWStepGeom_RWSphericalSurface() = default;

void RWStepGeom_RWSphericalSurface::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepGeom_SphericalSurface>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "spherical_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis2Placement3d> aPosition;

  data->ReadEntity(num, 2, "position", ach, STANDARD_TYPE(StepGeom_Axis2Placement3d), aPosition);

  double aRadius;

  data->ReadReal(num, 3, "radius", ach, aRadius);

  ent->Init(aName, aPosition, aRadius);
}

void RWStepGeom_RWSphericalSurface::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepGeom_SphericalSurface>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position());

  SW.Send(ent->Radius());
}

void RWStepGeom_RWSphericalSurface::Share(const occ::handle<StepGeom_SphericalSurface>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  iter.GetOneItem(ent->Position());
}
