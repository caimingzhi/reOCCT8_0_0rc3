

#include <StepGeom_OffsetSurface.hpp>
#include <StepGeom_Surface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_OffsetSurface, StepGeom_Surface)

StepGeom_OffsetSurface::StepGeom_OffsetSurface() = default;

void StepGeom_OffsetSurface::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                  const occ::handle<StepGeom_Surface>&         aBasisSurface,
                                  const double                                 aDistance,
                                  const StepData_Logical                       aSelfIntersect)
{

  basisSurface  = aBasisSurface;
  distance      = aDistance;
  selfIntersect = aSelfIntersect;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_OffsetSurface::SetBasisSurface(const occ::handle<StepGeom_Surface>& aBasisSurface)
{
  basisSurface = aBasisSurface;
}

occ::handle<StepGeom_Surface> StepGeom_OffsetSurface::BasisSurface() const
{
  return basisSurface;
}

void StepGeom_OffsetSurface::SetDistance(const double aDistance)
{
  distance = aDistance;
}

double StepGeom_OffsetSurface::Distance() const
{
  return distance;
}

void StepGeom_OffsetSurface::SetSelfIntersect(const StepData_Logical aSelfIntersect)
{
  selfIntersect = aSelfIntersect;
}

StepData_Logical StepGeom_OffsetSurface::SelfIntersect() const
{
  return selfIntersect;
}
