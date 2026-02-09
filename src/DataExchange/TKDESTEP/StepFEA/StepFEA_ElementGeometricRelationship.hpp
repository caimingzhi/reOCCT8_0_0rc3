#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_ElementOrElementGroup.hpp>
#include <StepElement_ElementAspect.hpp>
#include <Standard_Transient.hpp>
class StepElement_AnalysisItemWithinRepresentation;

class StepFEA_ElementGeometricRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepFEA_ElementGeometricRelationship();

  Standard_EXPORT void Init(const StepFEA_ElementOrElementGroup& aElementRef,
                            const occ::handle<StepElement_AnalysisItemWithinRepresentation>& aItem,
                            const StepElement_ElementAspect& aAspect);

  Standard_EXPORT StepFEA_ElementOrElementGroup ElementRef() const;

  Standard_EXPORT void SetElementRef(const StepFEA_ElementOrElementGroup& ElementRef);

  Standard_EXPORT occ::handle<StepElement_AnalysisItemWithinRepresentation> Item() const;

  Standard_EXPORT void SetItem(
    const occ::handle<StepElement_AnalysisItemWithinRepresentation>& Item);

  Standard_EXPORT StepElement_ElementAspect Aspect() const;

  Standard_EXPORT void SetAspect(const StepElement_ElementAspect& Aspect);

  DEFINE_STANDARD_RTTIEXT(StepFEA_ElementGeometricRelationship, Standard_Transient)

private:
  StepFEA_ElementOrElementGroup                             theElementRef;
  occ::handle<StepElement_AnalysisItemWithinRepresentation> theItem;
  StepElement_ElementAspect                                 theAspect;
};
