

#include <Standard_Type.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_ReparametrisedCompositeCurveSegment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_ReparametrisedCompositeCurveSegment,
                           StepGeom_CompositeCurveSegment)

StepGeom_ReparametrisedCompositeCurveSegment::StepGeom_ReparametrisedCompositeCurveSegment() =
  default;

void StepGeom_ReparametrisedCompositeCurveSegment::Init(
  const StepGeom_TransitionCode      aTransition,
  const bool                         aSameSense,
  const occ::handle<StepGeom_Curve>& aParentCurve,
  const double                       aParamLength)
{

  paramLength = aParamLength;

  StepGeom_CompositeCurveSegment::Init(aTransition, aSameSense, aParentCurve);
}

void StepGeom_ReparametrisedCompositeCurveSegment::SetParamLength(const double aParamLength)
{
  paramLength = aParamLength;
}

double StepGeom_ReparametrisedCompositeCurveSegment::ParamLength() const
{
  return paramLength;
}
