

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepGeom_Point.hpp>
#include <StepGeom_Surface.hpp>
#include <StepShape_GeometricSetSelect.hpp>

StepShape_GeometricSetSelect::StepShape_GeometricSetSelect() = default;

int StepShape_GeometricSetSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Point)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Curve)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Surface)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_GeometricRepresentationItem)))
    return 4;
  return 0;
}

occ::handle<StepGeom_Point> StepShape_GeometricSetSelect::Point() const
{
  return GetCasted(StepGeom_Point, Value());
}

occ::handle<StepGeom_Curve> StepShape_GeometricSetSelect::Curve() const
{
  return GetCasted(StepGeom_Curve, Value());
}

occ::handle<StepGeom_Surface> StepShape_GeometricSetSelect::Surface() const
{
  return GetCasted(StepGeom_Surface, Value());
}
