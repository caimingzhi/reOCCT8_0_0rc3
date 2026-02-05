#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepFEA_ElementGeometricRelationship.hpp>
#include <StepFEA_ElementOrElementGroup.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_ElementGeometricRelationship, Standard_Transient)

//=================================================================================================

StepFEA_ElementGeometricRelationship::StepFEA_ElementGeometricRelationship() = default;

//=================================================================================================

void StepFEA_ElementGeometricRelationship::Init(
  const StepFEA_ElementOrElementGroup&                             aElementRef,
  const occ::handle<StepElement_AnalysisItemWithinRepresentation>& aItem,
  const StepElement_ElementAspect&                                 aAspect)
{

  theElementRef = aElementRef;

  theItem = aItem;

  theAspect = aAspect;
}

//=================================================================================================

StepFEA_ElementOrElementGroup StepFEA_ElementGeometricRelationship::ElementRef() const
{
  return theElementRef;
}

//=================================================================================================

void StepFEA_ElementGeometricRelationship::SetElementRef(
  const StepFEA_ElementOrElementGroup& aElementRef)
{
  theElementRef = aElementRef;
}

//=================================================================================================

occ::handle<StepElement_AnalysisItemWithinRepresentation> StepFEA_ElementGeometricRelationship::
  Item() const
{
  return theItem;
}

//=================================================================================================

void StepFEA_ElementGeometricRelationship::SetItem(
  const occ::handle<StepElement_AnalysisItemWithinRepresentation>& aItem)
{
  theItem = aItem;
}

//=================================================================================================

StepElement_ElementAspect StepFEA_ElementGeometricRelationship::Aspect() const
{
  return theAspect;
}

//=================================================================================================

void StepFEA_ElementGeometricRelationship::SetAspect(const StepElement_ElementAspect& aAspect)
{
  theAspect = aAspect;
}
