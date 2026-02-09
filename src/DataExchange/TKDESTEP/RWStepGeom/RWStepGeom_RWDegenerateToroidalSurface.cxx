

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWDegenerateToroidalSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_DegenerateToroidalSurface.hpp>

RWStepGeom_RWDegenerateToroidalSurface::RWStepGeom_RWDegenerateToroidalSurface() = default;

void RWStepGeom_RWDegenerateToroidalSurface::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepGeom_DegenerateToroidalSurface>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "degenerate_toroidal_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis2Placement3d> aPosition;

  data->ReadEntity(num, 2, "position", ach, STANDARD_TYPE(StepGeom_Axis2Placement3d), aPosition);

  double aMajorRadius;

  data->ReadReal(num, 3, "major_radius", ach, aMajorRadius);

  double aMinorRadius;

  data->ReadReal(num, 4, "minor_radius", ach, aMinorRadius);

  bool aSelectOuter;

  data->ReadBoolean(num, 5, "select_outer", ach, aSelectOuter);

  ent->Init(aName, aPosition, aMajorRadius, aMinorRadius, aSelectOuter);
}

void RWStepGeom_RWDegenerateToroidalSurface::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepGeom_DegenerateToroidalSurface>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position());

  SW.Send(ent->MajorRadius());

  SW.Send(ent->MinorRadius());

  SW.SendBoolean(ent->SelectOuter());
}

void RWStepGeom_RWDegenerateToroidalSurface::Share(
  const occ::handle<StepGeom_DegenerateToroidalSurface>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.GetOneItem(ent->Position());
}
