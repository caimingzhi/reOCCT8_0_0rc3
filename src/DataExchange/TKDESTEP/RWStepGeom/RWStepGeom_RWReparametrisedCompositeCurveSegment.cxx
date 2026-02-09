

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWReparametrisedCompositeCurveSegment.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_ReparametrisedCompositeCurveSegment.hpp>
#include <StepGeom_TransitionCode.hpp>

#include "RWStepGeom_RWTransitionCode.hpp"

RWStepGeom_RWReparametrisedCompositeCurveSegment::
  RWStepGeom_RWReparametrisedCompositeCurveSegment() = default;

void RWStepGeom_RWReparametrisedCompositeCurveSegment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                      data,
  const int                                                        num,
  occ::handle<Interface_Check>&                                    ach,
  const occ::handle<StepGeom_ReparametrisedCompositeCurveSegment>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "reparametrised_composite_curve_segment"))
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

  double aParamLength;

  data->ReadReal(num, 4, "param_length", ach, aParamLength);

  ent->Init(aTransition, aSameSense, aParentCurve, aParamLength);
}

void RWStepGeom_RWReparametrisedCompositeCurveSegment::WriteStep(
  StepData_StepWriter&                                             SW,
  const occ::handle<StepGeom_ReparametrisedCompositeCurveSegment>& ent) const
{

  SW.SendEnum(RWStepGeom_RWTransitionCode::ConvertToString(ent->Transition()));

  SW.SendBoolean(ent->SameSense());

  SW.Send(ent->ParentCurve());

  SW.Send(ent->ParamLength());
}

void RWStepGeom_RWReparametrisedCompositeCurveSegment::Share(
  const occ::handle<StepGeom_ReparametrisedCompositeCurveSegment>& ent,
  Interface_EntityIterator&                                        iter) const
{

  iter.GetOneItem(ent->ParentCurve());
}
