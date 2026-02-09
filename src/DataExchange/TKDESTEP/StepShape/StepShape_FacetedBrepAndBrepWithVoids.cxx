

#include <Standard_Type.hpp>
#include <StepShape_BrepWithVoids.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_FacetedBrep.hpp>
#include <StepShape_FacetedBrepAndBrepWithVoids.hpp>
#include <StepShape_OrientedClosedShell.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_FacetedBrepAndBrepWithVoids, StepShape_ManifoldSolidBrep)

StepShape_FacetedBrepAndBrepWithVoids::StepShape_FacetedBrepAndBrepWithVoids() = default;

void StepShape_FacetedBrepAndBrepWithVoids::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<StepShape_ClosedShell>&    aOuter,
  const occ::handle<StepShape_FacetedBrep>&    aFacetedBrep,
  const occ::handle<StepShape_BrepWithVoids>&  aBrepWithVoids)
{

  facetedBrep   = aFacetedBrep;
  brepWithVoids = aBrepWithVoids;

  StepShape_ManifoldSolidBrep::Init(aName, aOuter);
}

void StepShape_FacetedBrepAndBrepWithVoids::Init(
  const occ::handle<TCollection_HAsciiString>&                                        aName,
  const occ::handle<StepShape_ClosedShell>&                                           aOuter,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>>& aVoids)
{

  StepShape_ManifoldSolidBrep::Init(aName, aOuter);

  brepWithVoids = new StepShape_BrepWithVoids();
  brepWithVoids->Init(aName, aOuter, aVoids);

  facetedBrep = new StepShape_FacetedBrep();
  facetedBrep->Init(aName, aOuter);
}

void StepShape_FacetedBrepAndBrepWithVoids::SetFacetedBrep(
  const occ::handle<StepShape_FacetedBrep>& aFacetedBrep)
{
  facetedBrep = aFacetedBrep;
}

occ::handle<StepShape_FacetedBrep> StepShape_FacetedBrepAndBrepWithVoids::FacetedBrep() const
{
  return facetedBrep;
}

void StepShape_FacetedBrepAndBrepWithVoids::SetBrepWithVoids(
  const occ::handle<StepShape_BrepWithVoids>& aBrepWithVoids)
{
  brepWithVoids = aBrepWithVoids;
}

occ::handle<StepShape_BrepWithVoids> StepShape_FacetedBrepAndBrepWithVoids::BrepWithVoids() const
{
  return brepWithVoids;
}

void StepShape_FacetedBrepAndBrepWithVoids::SetVoids(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>>& aVoids)
{
  brepWithVoids->SetVoids(aVoids);
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>>
  StepShape_FacetedBrepAndBrepWithVoids::Voids() const
{
  return brepWithVoids->Voids();
}

occ::handle<StepShape_OrientedClosedShell> StepShape_FacetedBrepAndBrepWithVoids::VoidsValue(
  const int num) const
{
  return brepWithVoids->VoidsValue(num);
}

int StepShape_FacetedBrepAndBrepWithVoids::NbVoids() const
{
  return brepWithVoids->NbVoids();
}
