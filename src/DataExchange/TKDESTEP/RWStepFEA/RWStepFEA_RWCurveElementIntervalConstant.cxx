#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWCurveElementIntervalConstant.hpp"
#include <StepBasic_EulerAngles.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_CurveElementSectionDefinition.hpp>
#include <StepFEA_CurveElementIntervalConstant.hpp>
#include <StepFEA_CurveElementLocation.hpp>

//=================================================================================================

RWStepFEA_RWCurveElementIntervalConstant::RWStepFEA_RWCurveElementIntervalConstant() = default;

//=================================================================================================

void RWStepFEA_RWCurveElementIntervalConstant::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepFEA_CurveElementIntervalConstant>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "curve_element_interval_constant"))
    return;

  // Inherited fields of CurveElementInterval

  occ::handle<StepFEA_CurveElementLocation> aCurveElementInterval_FinishPosition;
  data->ReadEntity(num,
                   1,
                   "curve_element_interval.finish_position",
                   ach,
                   STANDARD_TYPE(StepFEA_CurveElementLocation),
                   aCurveElementInterval_FinishPosition);

  occ::handle<StepBasic_EulerAngles> aCurveElementInterval_EuAngles;
  data->ReadEntity(num,
                   2,
                   "curve_element_interval.eu_angles",
                   ach,
                   STANDARD_TYPE(StepBasic_EulerAngles),
                   aCurveElementInterval_EuAngles);

  // Own fields of CurveElementIntervalConstant

  occ::handle<StepElement_CurveElementSectionDefinition> aSection;
  data->ReadEntity(num,
                   3,
                   "section",
                   ach,
                   STANDARD_TYPE(StepElement_CurveElementSectionDefinition),
                   aSection);

  // Initialize entity
  ent->Init(aCurveElementInterval_FinishPosition, aCurveElementInterval_EuAngles, aSection);
}

//=================================================================================================

void RWStepFEA_RWCurveElementIntervalConstant::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepFEA_CurveElementIntervalConstant>& ent) const
{

  // Inherited fields of CurveElementInterval

  SW.Send(ent->StepFEA_CurveElementInterval::FinishPosition());

  SW.Send(ent->StepFEA_CurveElementInterval::EuAngles());

  // Own fields of CurveElementIntervalConstant

  SW.Send(ent->Section());
}

//=================================================================================================

void RWStepFEA_RWCurveElementIntervalConstant::Share(
  const occ::handle<StepFEA_CurveElementIntervalConstant>& ent,
  Interface_EntityIterator&                                iter) const
{

  // Inherited fields of CurveElementInterval

  iter.AddItem(ent->StepFEA_CurveElementInterval::FinishPosition());

  iter.AddItem(ent->StepFEA_CurveElementInterval::EuAngles());

  // Own fields of CurveElementIntervalConstant

  iter.AddItem(ent->Section());
}
