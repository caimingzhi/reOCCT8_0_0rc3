#include <Standard_Type.hpp>
#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepElement_CurveElementSectionDefinition.hpp>
#include <StepFEA_FeaCurveSectionGeometricRelationship.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaCurveSectionGeometricRelationship, Standard_Transient)

//=================================================================================================

StepFEA_FeaCurveSectionGeometricRelationship::StepFEA_FeaCurveSectionGeometricRelationship() =
  default;

//=================================================================================================

void StepFEA_FeaCurveSectionGeometricRelationship::Init(
  const occ::handle<StepElement_CurveElementSectionDefinition>&    aSectionRef,
  const occ::handle<StepElement_AnalysisItemWithinRepresentation>& aItem)
{

  theSectionRef = aSectionRef;

  theItem = aItem;
}

//=================================================================================================

occ::handle<StepElement_CurveElementSectionDefinition>
  StepFEA_FeaCurveSectionGeometricRelationship::SectionRef() const
{
  return theSectionRef;
}

//=================================================================================================

void StepFEA_FeaCurveSectionGeometricRelationship::SetSectionRef(
  const occ::handle<StepElement_CurveElementSectionDefinition>& aSectionRef)
{
  theSectionRef = aSectionRef;
}

//=================================================================================================

occ::handle<StepElement_AnalysisItemWithinRepresentation>
  StepFEA_FeaCurveSectionGeometricRelationship::Item() const
{
  return theItem;
}

//=================================================================================================

void StepFEA_FeaCurveSectionGeometricRelationship::SetItem(
  const occ::handle<StepElement_AnalysisItemWithinRepresentation>& aItem)
{
  theItem = aItem;
}
