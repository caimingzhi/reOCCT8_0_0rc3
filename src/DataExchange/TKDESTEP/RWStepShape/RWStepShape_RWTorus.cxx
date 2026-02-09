

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWTorus.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepShape_Torus.hpp>

RWStepShape_RWTorus::RWStepShape_RWTorus() = default;

void RWStepShape_RWTorus::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                   const int                                   num,
                                   occ::handle<Interface_Check>&               ach,
                                   const occ::handle<StepShape_Torus>&         ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "torus"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis1Placement> aPosition;

  data->ReadEntity(num, 2, "position", ach, STANDARD_TYPE(StepGeom_Axis1Placement), aPosition);

  double aMajorRadius;

  data->ReadReal(num, 3, "major_radius", ach, aMajorRadius);

  double aMinorRadius;

  data->ReadReal(num, 4, "minor_radius", ach, aMinorRadius);

  ent->Init(aName, aPosition, aMajorRadius, aMinorRadius);
}

void RWStepShape_RWTorus::WriteStep(StepData_StepWriter&                SW,
                                    const occ::handle<StepShape_Torus>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position());

  SW.Send(ent->MajorRadius());

  SW.Send(ent->MinorRadius());
}

void RWStepShape_RWTorus::Share(const occ::handle<StepShape_Torus>& ent,
                                Interface_EntityIterator&           iter) const
{

  iter.GetOneItem(ent->Position());
}
