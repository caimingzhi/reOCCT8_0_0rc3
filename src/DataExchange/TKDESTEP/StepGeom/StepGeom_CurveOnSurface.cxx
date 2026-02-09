

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepGeom_CompositeCurveOnSurface.hpp>
#include <StepGeom_CurveOnSurface.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepGeom_SurfaceCurve.hpp>

StepGeom_CurveOnSurface::StepGeom_CurveOnSurface() = default;

int StepGeom_CurveOnSurface::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Pcurve)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_SurfaceCurve)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_CompositeCurveOnSurface)))
    return 3;
  return 0;
}

occ::handle<StepGeom_Pcurve> StepGeom_CurveOnSurface::Pcurve() const
{
  return GetCasted(StepGeom_Pcurve, Value());
}

occ::handle<StepGeom_SurfaceCurve> StepGeom_CurveOnSurface::SurfaceCurve() const
{
  return GetCasted(StepGeom_SurfaceCurve, Value());
}

occ::handle<StepGeom_CompositeCurveOnSurface> StepGeom_CurveOnSurface::CompositeCurveOnSurface()
  const
{
  return GetCasted(StepGeom_CompositeCurveOnSurface, Value());
}
