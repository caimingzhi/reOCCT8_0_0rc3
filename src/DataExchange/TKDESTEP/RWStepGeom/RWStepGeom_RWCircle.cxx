

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWCircle.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Circle.hpp>

RWStepGeom_RWCircle::RWStepGeom_RWCircle() = default;

void RWStepGeom_RWCircle::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                   const int                                   num,
                                   occ::handle<Interface_Check>&               ach,
                                   const occ::handle<StepGeom_Circle>&         ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "circle"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  StepGeom_Axis2Placement aPosition;

  data->ReadEntity(num, 2, "position", ach, aPosition);

  double aRadius;

  data->ReadReal(num, 3, "radius", ach, aRadius);

  ent->Init(aName, aPosition, aRadius);
}

void RWStepGeom_RWCircle::WriteStep(StepData_StepWriter&                SW,
                                    const occ::handle<StepGeom_Circle>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position().Value());

  SW.Send(ent->Radius());
}

void RWStepGeom_RWCircle::Share(const occ::handle<StepGeom_Circle>& ent,
                                Interface_EntityIterator&           iter) const
{

  iter.GetOneItem(ent->Position().Value());
}
