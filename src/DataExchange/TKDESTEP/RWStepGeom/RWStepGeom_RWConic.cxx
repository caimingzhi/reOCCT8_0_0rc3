

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWConic.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Conic.hpp>

RWStepGeom_RWConic::RWStepGeom_RWConic() = default;

void RWStepGeom_RWConic::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                  const int                                   num,
                                  occ::handle<Interface_Check>&               ach,
                                  const occ::handle<StepGeom_Conic>&          ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "conic"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  StepGeom_Axis2Placement aPosition;

  data->ReadEntity(num, 2, "position", ach, aPosition);

  ent->Init(aName, aPosition);
}

void RWStepGeom_RWConic::WriteStep(StepData_StepWriter&               SW,
                                   const occ::handle<StepGeom_Conic>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position().Value());
}

void RWStepGeom_RWConic::Share(const occ::handle<StepGeom_Conic>& ent,
                               Interface_EntityIterator&          iter) const
{

  iter.GetOneItem(ent->Position().Value());
}
