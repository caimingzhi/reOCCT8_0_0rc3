#include "RWStepDimTol_RWRunoutZoneOrientation.hpp"

#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_RunoutZoneOrientation.hpp>

RWStepDimTol_RWRunoutZoneOrientation::RWStepDimTol_RWRunoutZoneOrientation() = default;

void RWStepDimTol_RWRunoutZoneOrientation::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepDimTol_RunoutZoneOrientation>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "runout_zone_orientation"))
    return;

  occ::handle<StepBasic_PlaneAngleMeasureWithUnit> anAngle;
  data
    ->ReadEntity(num, 1, "angle", ach, STANDARD_TYPE(StepBasic_PlaneAngleMeasureWithUnit), anAngle);

  ent->Init(anAngle);
}

void RWStepDimTol_RWRunoutZoneOrientation::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepDimTol_RunoutZoneOrientation>& ent) const
{
  SW.Send(ent->Angle());
}
