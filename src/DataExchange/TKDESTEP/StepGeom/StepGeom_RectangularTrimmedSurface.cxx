

#include <StepGeom_RectangularTrimmedSurface.hpp>
#include <StepGeom_Surface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_RectangularTrimmedSurface, StepGeom_BoundedSurface)

StepGeom_RectangularTrimmedSurface::StepGeom_RectangularTrimmedSurface() = default;

void StepGeom_RectangularTrimmedSurface::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                              const occ::handle<StepGeom_Surface>& aBasisSurface,
                                              const double                         aU1,
                                              const double                         aU2,
                                              const double                         aV1,
                                              const double                         aV2,
                                              const bool                           aUsense,
                                              const bool                           aVsense)
{

  basisSurface = aBasisSurface;
  u1           = aU1;
  u2           = aU2;
  v1           = aV1;
  v2           = aV2;
  usense       = aUsense;
  vsense       = aVsense;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_RectangularTrimmedSurface::SetBasisSurface(
  const occ::handle<StepGeom_Surface>& aBasisSurface)
{
  basisSurface = aBasisSurface;
}

occ::handle<StepGeom_Surface> StepGeom_RectangularTrimmedSurface::BasisSurface() const
{
  return basisSurface;
}

void StepGeom_RectangularTrimmedSurface::SetU1(const double aU1)
{
  u1 = aU1;
}

double StepGeom_RectangularTrimmedSurface::U1() const
{
  return u1;
}

void StepGeom_RectangularTrimmedSurface::SetU2(const double aU2)
{
  u2 = aU2;
}

double StepGeom_RectangularTrimmedSurface::U2() const
{
  return u2;
}

void StepGeom_RectangularTrimmedSurface::SetV1(const double aV1)
{
  v1 = aV1;
}

double StepGeom_RectangularTrimmedSurface::V1() const
{
  return v1;
}

void StepGeom_RectangularTrimmedSurface::SetV2(const double aV2)
{
  v2 = aV2;
}

double StepGeom_RectangularTrimmedSurface::V2() const
{
  return v2;
}

void StepGeom_RectangularTrimmedSurface::SetUsense(const bool aUsense)
{
  usense = aUsense;
}

bool StepGeom_RectangularTrimmedSurface::Usense() const
{
  return usense;
}

void StepGeom_RectangularTrimmedSurface::SetVsense(const bool aVsense)
{
  vsense = aVsense;
}

bool StepGeom_RectangularTrimmedSurface::Vsense() const
{
  return vsense;
}
