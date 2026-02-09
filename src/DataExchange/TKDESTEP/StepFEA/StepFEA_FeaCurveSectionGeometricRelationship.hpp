#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepElement_CurveElementSectionDefinition;
class StepElement_AnalysisItemWithinRepresentation;

class StepFEA_FeaCurveSectionGeometricRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepFEA_FeaCurveSectionGeometricRelationship();

  Standard_EXPORT void Init(
    const occ::handle<StepElement_CurveElementSectionDefinition>&    aSectionRef,
    const occ::handle<StepElement_AnalysisItemWithinRepresentation>& aItem);

  Standard_EXPORT occ::handle<StepElement_CurveElementSectionDefinition> SectionRef() const;

  Standard_EXPORT void SetSectionRef(
    const occ::handle<StepElement_CurveElementSectionDefinition>& SectionRef);

  Standard_EXPORT occ::handle<StepElement_AnalysisItemWithinRepresentation> Item() const;

  Standard_EXPORT void SetItem(
    const occ::handle<StepElement_AnalysisItemWithinRepresentation>& Item);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaCurveSectionGeometricRelationship, Standard_Transient)

private:
  occ::handle<StepElement_CurveElementSectionDefinition>    theSectionRef;
  occ::handle<StepElement_AnalysisItemWithinRepresentation> theItem;
};
