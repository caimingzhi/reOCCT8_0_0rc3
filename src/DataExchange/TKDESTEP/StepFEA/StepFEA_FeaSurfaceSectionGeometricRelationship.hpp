#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepElement_SurfaceSection;
class StepElement_AnalysisItemWithinRepresentation;

class StepFEA_FeaSurfaceSectionGeometricRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepFEA_FeaSurfaceSectionGeometricRelationship();

  Standard_EXPORT void Init(const occ::handle<StepElement_SurfaceSection>& aSectionRef,
                            const occ::handle<StepElement_AnalysisItemWithinRepresentation>& aItem);

  Standard_EXPORT occ::handle<StepElement_SurfaceSection> SectionRef() const;

  Standard_EXPORT void SetSectionRef(const occ::handle<StepElement_SurfaceSection>& SectionRef);

  Standard_EXPORT occ::handle<StepElement_AnalysisItemWithinRepresentation> Item() const;

  Standard_EXPORT void SetItem(
    const occ::handle<StepElement_AnalysisItemWithinRepresentation>& Item);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaSurfaceSectionGeometricRelationship, Standard_Transient)

private:
  occ::handle<StepElement_SurfaceSection>                   theSectionRef;
  occ::handle<StepElement_AnalysisItemWithinRepresentation> theItem;
};
