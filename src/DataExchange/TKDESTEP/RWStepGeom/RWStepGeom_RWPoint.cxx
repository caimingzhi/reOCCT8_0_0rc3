

#include "RWStepGeom_RWPoint.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Point.hpp>

RWStepGeom_RWPoint::RWStepGeom_RWPoint() = default;

void RWStepGeom_RWPoint::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                  const int                                   num,
                                  occ::handle<Interface_Check>&               ach,
                                  const occ::handle<StepGeom_Point>&          ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "point"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepGeom_RWPoint::WriteStep(StepData_StepWriter&               SW,
                                   const occ::handle<StepGeom_Point>& ent) const
{

  SW.Send(ent->Name());
}
