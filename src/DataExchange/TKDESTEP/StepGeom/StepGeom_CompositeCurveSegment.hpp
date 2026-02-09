#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_TransitionCode.hpp>
#include <Standard_Transient.hpp>
class StepGeom_Curve;

class StepGeom_CompositeCurveSegment : public Standard_Transient
{

public:
  Standard_EXPORT StepGeom_CompositeCurveSegment();

  Standard_EXPORT void Init(const StepGeom_TransitionCode      aTransition,
                            const bool                         aSameSense,
                            const occ::handle<StepGeom_Curve>& aParentCurve);

  Standard_EXPORT void SetTransition(const StepGeom_TransitionCode aTransition);

  Standard_EXPORT StepGeom_TransitionCode Transition() const;

  Standard_EXPORT void SetSameSense(const bool aSameSense);

  Standard_EXPORT bool SameSense() const;

  Standard_EXPORT void SetParentCurve(const occ::handle<StepGeom_Curve>& aParentCurve);

  Standard_EXPORT occ::handle<StepGeom_Curve> ParentCurve() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_CompositeCurveSegment, Standard_Transient)

private:
  StepGeom_TransitionCode     transition;
  bool                        sameSense;
  occ::handle<StepGeom_Curve> parentCurve;
};
