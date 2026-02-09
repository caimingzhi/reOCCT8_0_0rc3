

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepGeom_PcurveOrSurface.hpp>
#include <StepGeom_Surface.hpp>

StepGeom_PcurveOrSurface::StepGeom_PcurveOrSurface() = default;

int StepGeom_PcurveOrSurface::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Pcurve)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Surface)))
    return 2;
  return 0;
}

occ::handle<StepGeom_Pcurve> StepGeom_PcurveOrSurface::Pcurve() const
{
  return GetCasted(StepGeom_Pcurve, Value());
}

occ::handle<StepGeom_Surface> StepGeom_PcurveOrSurface::Surface() const
{
  return GetCasted(StepGeom_Surface, Value());
}
