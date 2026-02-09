

#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWToroidalSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_ToroidalSurface.hpp>

RWStepGeom_RWToroidalSurface::RWStepGeom_RWToroidalSurface() = default;

void RWStepGeom_RWToroidalSurface::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepGeom_ToroidalSurface>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "toroidal_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis2Placement3d> aPosition;

  data->ReadEntity(num, 2, "position", ach, STANDARD_TYPE(StepGeom_Axis2Placement3d), aPosition);

  double aMajorRadius;

  data->ReadReal(num, 3, "major_radius", ach, aMajorRadius);

  double aMinorRadius;

  data->ReadReal(num, 4, "minor_radius", ach, aMinorRadius);

  ent->Init(aName, aPosition, aMajorRadius, aMinorRadius);
}

void RWStepGeom_RWToroidalSurface::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepGeom_ToroidalSurface>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position());

  SW.Send(ent->MajorRadius());

  SW.Send(ent->MinorRadius());
}

void RWStepGeom_RWToroidalSurface::Share(const occ::handle<StepGeom_ToroidalSurface>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->Position());
}

void RWStepGeom_RWToroidalSurface::Check(const occ::handle<StepGeom_ToroidalSurface>& ent,
                                         const Interface_ShareTool&,
                                         occ::handle<Interface_Check>& ach) const
{

  if (ent->MajorRadius() < 0.0)
    ach->AddFail("ERROR: ToroidalSurface: MajorRadius < 0.0");
  if (ent->MinorRadius() < 0.0)
    ach->AddFail("ERROR: ToroidalSurface: MinorRadius < 0.0");
  if (ent->MajorRadius() < ent->MinorRadius())
    ach->AddWarning("ToroidalSurface: MajorRadius smaller than MinorRadius");
}
