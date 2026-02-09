

#include "RWStepGeom_RWCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Curve.hpp>

RWStepGeom_RWCurve::RWStepGeom_RWCurve() = default;

void RWStepGeom_RWCurve::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                  const int                                   num,
                                  occ::handle<Interface_Check>&               ach,
                                  const occ::handle<StepGeom_Curve>&          ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "curve"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepGeom_RWCurve::WriteStep(StepData_StepWriter&               SW,
                                   const occ::handle<StepGeom_Curve>& ent) const
{

  SW.Send(ent->Name());
}
