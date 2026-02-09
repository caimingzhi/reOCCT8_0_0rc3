

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWParabola.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Parabola.hpp>

RWStepGeom_RWParabola::RWStepGeom_RWParabola() = default;

void RWStepGeom_RWParabola::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                     const int                                   num,
                                     occ::handle<Interface_Check>&               ach,
                                     const occ::handle<StepGeom_Parabola>&       ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "parabola"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  StepGeom_Axis2Placement aPosition;

  data->ReadEntity(num, 2, "position", ach, aPosition);

  double aFocalDist;

  data->ReadReal(num, 3, "focal_dist", ach, aFocalDist);

  ent->Init(aName, aPosition, aFocalDist);
}

void RWStepGeom_RWParabola::WriteStep(StepData_StepWriter&                  SW,
                                      const occ::handle<StepGeom_Parabola>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position().Value());

  SW.Send(ent->FocalDist());
}

void RWStepGeom_RWParabola::Share(const occ::handle<StepGeom_Parabola>& ent,
                                  Interface_EntityIterator&             iter) const
{

  iter.GetOneItem(ent->Position().Value());
}
