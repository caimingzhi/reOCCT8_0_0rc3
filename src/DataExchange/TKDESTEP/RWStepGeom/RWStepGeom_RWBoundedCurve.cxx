

#include "RWStepGeom_RWBoundedCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_BoundedCurve.hpp>

RWStepGeom_RWBoundedCurve::RWStepGeom_RWBoundedCurve() = default;

void RWStepGeom_RWBoundedCurve::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepGeom_BoundedCurve>&   ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "bounded_curve"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepGeom_RWBoundedCurve::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepGeom_BoundedCurve>& ent) const
{

  SW.Send(ent->Name());
}
