#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_CompositeCurveSegment.hpp>
#include <StepGeom_TransitionCode.hpp>
class StepGeom_Curve;

class StepGeom_ReparametrisedCompositeCurveSegment : public StepGeom_CompositeCurveSegment
{

public:
  Standard_EXPORT StepGeom_ReparametrisedCompositeCurveSegment();

  Standard_EXPORT void Init(const StepGeom_TransitionCode      aTransition,
                            const bool                         aSameSense,
                            const occ::handle<StepGeom_Curve>& aParentCurve,
                            const double                       aParamLength);

  Standard_EXPORT void SetParamLength(const double aParamLength);

  Standard_EXPORT double ParamLength() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_ReparametrisedCompositeCurveSegment,
                          StepGeom_CompositeCurveSegment)

private:
  double paramLength;
};
