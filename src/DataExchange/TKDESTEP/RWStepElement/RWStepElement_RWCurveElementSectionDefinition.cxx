#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWCurveElementSectionDefinition.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_CurveElementSectionDefinition.hpp>

//=================================================================================================

RWStepElement_RWCurveElementSectionDefinition::RWStepElement_RWCurveElementSectionDefinition() =
  default;

//=================================================================================================

void RWStepElement_RWCurveElementSectionDefinition::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepElement_CurveElementSectionDefinition>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "curve_element_section_definition"))
    return;

  // Own fields of CurveElementSectionDefinition

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 1, "description", ach, aDescription);

  double aSectionAngle;
  data->ReadReal(num, 2, "section_angle", ach, aSectionAngle);

  // Initialize entity
  ent->Init(aDescription, aSectionAngle);
}

//=================================================================================================

void RWStepElement_RWCurveElementSectionDefinition::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepElement_CurveElementSectionDefinition>& ent) const
{

  // Own fields of CurveElementSectionDefinition

  SW.Send(ent->Description());

  SW.Send(ent->SectionAngle());
}

//=================================================================================================

void RWStepElement_RWCurveElementSectionDefinition::Share(
  const occ::handle<StepElement_CurveElementSectionDefinition>&,
  Interface_EntityIterator&) const
{
  // Own fields of CurveElementSectionDefinition
}
