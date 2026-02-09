

#include <StepVisual_EdgeOrCurve.hpp>
#include <StepGeom_Curve.hpp>
#include <StepShape_Edge.hpp>

StepVisual_EdgeOrCurve::StepVisual_EdgeOrCurve() = default;

int StepVisual_EdgeOrCurve::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Curve)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_Edge)))
    return 2;
  return 0;
}

occ::handle<StepGeom_Curve> StepVisual_EdgeOrCurve::Curve() const
{
  return occ::down_cast<StepGeom_Curve>(Value());
}

occ::handle<StepShape_Edge> StepVisual_EdgeOrCurve::Edge() const
{
  return occ::down_cast<StepShape_Edge>(Value());
}
