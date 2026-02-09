

#include <Standard_Type.hpp>
#include <StepGeom_CompositeCurveSegment.hpp>
#include <StepGeom_Curve.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_CompositeCurveSegment, Standard_Transient)

StepGeom_CompositeCurveSegment::StepGeom_CompositeCurveSegment() = default;

void StepGeom_CompositeCurveSegment::Init(const StepGeom_TransitionCode      aTransition,
                                          const bool                         aSameSense,
                                          const occ::handle<StepGeom_Curve>& aParentCurve)
{

  transition  = aTransition;
  sameSense   = aSameSense;
  parentCurve = aParentCurve;
}

void StepGeom_CompositeCurveSegment::SetTransition(const StepGeom_TransitionCode aTransition)
{
  transition = aTransition;
}

StepGeom_TransitionCode StepGeom_CompositeCurveSegment::Transition() const
{
  return transition;
}

void StepGeom_CompositeCurveSegment::SetSameSense(const bool aSameSense)
{
  sameSense = aSameSense;
}

bool StepGeom_CompositeCurveSegment::SameSense() const
{
  return sameSense;
}

void StepGeom_CompositeCurveSegment::SetParentCurve(const occ::handle<StepGeom_Curve>& aParentCurve)
{
  parentCurve = aParentCurve;
}

occ::handle<StepGeom_Curve> StepGeom_CompositeCurveSegment::ParentCurve() const
{
  return parentCurve;
}
