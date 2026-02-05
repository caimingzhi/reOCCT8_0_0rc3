#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWCurveElementInterval.hpp"
#include <StepBasic_EulerAngles.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_CurveElementInterval.hpp>
#include <StepFEA_CurveElementLocation.hpp>

//=================================================================================================

RWStepFEA_RWCurveElementInterval::RWStepFEA_RWCurveElementInterval() = default;

//=================================================================================================

void RWStepFEA_RWCurveElementInterval::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepFEA_CurveElementInterval>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "curve_element_interval"))
    return;

  // Own fields of CurveElementInterval

  occ::handle<StepFEA_CurveElementLocation> aFinishPosition;
  data->ReadEntity(num,
                   1,
                   "finish_position",
                   ach,
                   STANDARD_TYPE(StepFEA_CurveElementLocation),
                   aFinishPosition);

  occ::handle<StepBasic_EulerAngles> aEuAngles;
  data->ReadEntity(num, 2, "eu_angles", ach, STANDARD_TYPE(StepBasic_EulerAngles), aEuAngles);

  // Initialize entity
  ent->Init(aFinishPosition, aEuAngles);
}

//=================================================================================================

void RWStepFEA_RWCurveElementInterval::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepFEA_CurveElementInterval>& ent) const
{

  // Own fields of CurveElementInterval

  SW.Send(ent->FinishPosition());

  SW.Send(ent->EuAngles());
}

//=================================================================================================

void RWStepFEA_RWCurveElementInterval::Share(const occ::handle<StepFEA_CurveElementInterval>& ent,
                                             Interface_EntityIterator& iter) const
{

  // Own fields of CurveElementInterval

  iter.AddItem(ent->FinishPosition());

  iter.AddItem(ent->EuAngles());
}
