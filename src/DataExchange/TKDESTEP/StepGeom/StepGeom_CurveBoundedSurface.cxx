#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepGeom_Surface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_CurveBoundedSurface, StepGeom_BoundedSurface)

//=================================================================================================

StepGeom_CurveBoundedSurface::StepGeom_CurveBoundedSurface() = default;

//=================================================================================================

void StepGeom_CurveBoundedSurface::Init(
  const occ::handle<TCollection_HAsciiString>&                      aRepresentationItem_Name,
  const occ::handle<StepGeom_Surface>&                              aBasisSurface,
  const occ::handle<NCollection_HArray1<StepGeom_SurfaceBoundary>>& aBoundaries,
  const bool                                                        aImplicitOuter)
{
  StepGeom_BoundedSurface::Init(aRepresentationItem_Name);

  theBasisSurface = aBasisSurface;

  theBoundaries = aBoundaries;

  theImplicitOuter = aImplicitOuter;
}

//=================================================================================================

occ::handle<StepGeom_Surface> StepGeom_CurveBoundedSurface::BasisSurface() const
{
  return theBasisSurface;
}

//=================================================================================================

void StepGeom_CurveBoundedSurface::SetBasisSurface(
  const occ::handle<StepGeom_Surface>& aBasisSurface)
{
  theBasisSurface = aBasisSurface;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepGeom_SurfaceBoundary>> StepGeom_CurveBoundedSurface::
  Boundaries() const
{
  return theBoundaries;
}

//=================================================================================================

void StepGeom_CurveBoundedSurface::SetBoundaries(
  const occ::handle<NCollection_HArray1<StepGeom_SurfaceBoundary>>& aBoundaries)
{
  theBoundaries = aBoundaries;
}

//=================================================================================================

bool StepGeom_CurveBoundedSurface::ImplicitOuter() const
{
  return theImplicitOuter;
}

//=================================================================================================

void StepGeom_CurveBoundedSurface::SetImplicitOuter(const bool aImplicitOuter)
{
  theImplicitOuter = aImplicitOuter;
}
