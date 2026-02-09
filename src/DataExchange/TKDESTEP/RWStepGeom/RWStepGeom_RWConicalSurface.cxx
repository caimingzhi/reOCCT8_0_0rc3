

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWConicalSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_ConicalSurface.hpp>

RWStepGeom_RWConicalSurface::RWStepGeom_RWConicalSurface() = default;

void RWStepGeom_RWConicalSurface::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepGeom_ConicalSurface>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "conical_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis2Placement3d> aPosition;

  data->ReadEntity(num, 2, "position", ach, STANDARD_TYPE(StepGeom_Axis2Placement3d), aPosition);

  double aRadius;

  data->ReadReal(num, 3, "radius", ach, aRadius);

  double aSemiAngle;

  data->ReadReal(num, 4, "semi_angle", ach, aSemiAngle);

  ent->Init(aName, aPosition, aRadius, aSemiAngle);
}

void RWStepGeom_RWConicalSurface::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepGeom_ConicalSurface>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position());

  SW.Send(ent->Radius());

  SW.Send(ent->SemiAngle());
}

void RWStepGeom_RWConicalSurface::Share(const occ::handle<StepGeom_ConicalSurface>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  iter.GetOneItem(ent->Position());
}
