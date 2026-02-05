#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepElement_SurfaceSection.hpp>
#include <StepFEA_FeaSurfaceSectionGeometricRelationship.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaSurfaceSectionGeometricRelationship, Standard_Transient)

//=================================================================================================

StepFEA_FeaSurfaceSectionGeometricRelationship::StepFEA_FeaSurfaceSectionGeometricRelationship() =
  default;

//=================================================================================================

void StepFEA_FeaSurfaceSectionGeometricRelationship::Init(
  const occ::handle<StepElement_SurfaceSection>&                   aSectionRef,
  const occ::handle<StepElement_AnalysisItemWithinRepresentation>& aItem)
{

  theSectionRef = aSectionRef;

  theItem = aItem;
}

//=================================================================================================

occ::handle<StepElement_SurfaceSection> StepFEA_FeaSurfaceSectionGeometricRelationship::SectionRef()
  const
{
  return theSectionRef;
}

//=================================================================================================

void StepFEA_FeaSurfaceSectionGeometricRelationship::SetSectionRef(
  const occ::handle<StepElement_SurfaceSection>& aSectionRef)
{
  theSectionRef = aSectionRef;
}

//=================================================================================================

occ::handle<StepElement_AnalysisItemWithinRepresentation>
  StepFEA_FeaSurfaceSectionGeometricRelationship::Item() const
{
  return theItem;
}

//=================================================================================================

void StepFEA_FeaSurfaceSectionGeometricRelationship::SetItem(
  const occ::handle<StepElement_AnalysisItemWithinRepresentation>& aItem)
{
  theItem = aItem;
}
