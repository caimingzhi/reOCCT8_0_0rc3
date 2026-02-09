

#include <StepVisual_PathOrCompositeCurve.hpp>
#include <StepGeom_CompositeCurve.hpp>
#include <StepShape_Path.hpp>

StepVisual_PathOrCompositeCurve::StepVisual_PathOrCompositeCurve() = default;

int StepVisual_PathOrCompositeCurve::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_CompositeCurve)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_Path)))
    return 2;
  return 0;
}

occ::handle<StepGeom_CompositeCurve> StepVisual_PathOrCompositeCurve::CompositeCurve() const
{
  return occ::down_cast<StepGeom_CompositeCurve>(Value());
}

occ::handle<StepShape_Path> StepVisual_PathOrCompositeCurve::Path() const
{
  return occ::down_cast<StepShape_Path>(Value());
}
