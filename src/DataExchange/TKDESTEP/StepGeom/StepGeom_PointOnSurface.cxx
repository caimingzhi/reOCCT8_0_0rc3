

#include <StepGeom_PointOnSurface.hpp>
#include <StepGeom_Surface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_PointOnSurface, StepGeom_Point)

StepGeom_PointOnSurface::StepGeom_PointOnSurface() = default;

void StepGeom_PointOnSurface::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                   const occ::handle<StepGeom_Surface>&         aBasisSurface,
                                   const double                                 aPointParameterU,
                                   const double                                 aPointParameterV)
{

  basisSurface    = aBasisSurface;
  pointParameterU = aPointParameterU;
  pointParameterV = aPointParameterV;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_PointOnSurface::SetBasisSurface(const occ::handle<StepGeom_Surface>& aBasisSurface)
{
  basisSurface = aBasisSurface;
}

occ::handle<StepGeom_Surface> StepGeom_PointOnSurface::BasisSurface() const
{
  return basisSurface;
}

void StepGeom_PointOnSurface::SetPointParameterU(const double aPointParameterU)
{
  pointParameterU = aPointParameterU;
}

double StepGeom_PointOnSurface::PointParameterU() const
{
  return pointParameterU;
}

void StepGeom_PointOnSurface::SetPointParameterV(const double aPointParameterV)
{
  pointParameterV = aPointParameterV;
}

double StepGeom_PointOnSurface::PointParameterV() const
{
  return pointParameterV;
}
