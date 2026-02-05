#include <Standard_Transient.hpp>
#include <StepGeom_BoundaryCurve.hpp>
#include <StepGeom_DegeneratePcurve.hpp>
#include <StepGeom_SurfaceBoundary.hpp>

//=================================================================================================

StepGeom_SurfaceBoundary::StepGeom_SurfaceBoundary() = default;

//=================================================================================================

int StepGeom_SurfaceBoundary::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_BoundaryCurve)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_DegeneratePcurve)))
    return 2;
  return 0;
}

//=================================================================================================

occ::handle<StepGeom_BoundaryCurve> StepGeom_SurfaceBoundary::BoundaryCurve() const
{
  return occ::down_cast<StepGeom_BoundaryCurve>(Value());
}

//=================================================================================================

occ::handle<StepGeom_DegeneratePcurve> StepGeom_SurfaceBoundary::DegeneratePcurve() const
{
  return occ::down_cast<StepGeom_DegeneratePcurve>(Value());
}
