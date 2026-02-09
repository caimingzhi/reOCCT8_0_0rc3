

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWCompositeCurveSegment.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CompositeCurveSegment.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_TransitionCode.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepGeom_RWTransitionCode.hpp"

RWStepGeom_RWCompositeCurveSegment::RWStepGeom_RWCompositeCurveSegment() = default;

void RWStepGeom_RWCompositeCurveSegment::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepGeom_CompositeCurveSegment>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "composite_curve_segment"))
    return;

  StepGeom_TransitionCode aTransition = StepGeom_tcDiscontinuous;
  if (data->ParamType(num, 1) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 1);
    if (!RWStepGeom_RWTransitionCode::ConvertToEnum(text, aTransition))
    {
      ach->AddFail("Enumeration transition_code has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #1 (transition) is not an enumeration");

  bool aSameSense;

  data->ReadBoolean(num, 2, "same_sense", ach, aSameSense);

  occ::handle<StepGeom_Curve> aParentCurve;

  data->ReadEntity(num, 3, "parent_curve", ach, STANDARD_TYPE(StepGeom_Curve), aParentCurve);

  ent->Init(aTransition, aSameSense, aParentCurve);
}

void RWStepGeom_RWCompositeCurveSegment::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepGeom_CompositeCurveSegment>& ent) const
{

  SW.SendEnum(RWStepGeom_RWTransitionCode::ConvertToString(ent->Transition()));

  SW.SendBoolean(ent->SameSense());

  SW.Send(ent->ParentCurve());
}

void RWStepGeom_RWCompositeCurveSegment::Share(
  const occ::handle<StepGeom_CompositeCurveSegment>& ent,
  Interface_EntityIterator&                          iter) const
{

  iter.GetOneItem(ent->ParentCurve());
}
