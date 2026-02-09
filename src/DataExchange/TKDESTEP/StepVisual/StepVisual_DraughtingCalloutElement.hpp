#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_AnnotationCurveOccurrence;
class StepVisual_AnnotationFillAreaOccurrence;
class StepVisual_AnnotationTextOccurrence;
class StepVisual_TessellatedAnnotationOccurrence;

class StepVisual_DraughtingCalloutElement : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_DraughtingCalloutElement();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepVisual_AnnotationCurveOccurrence> AnnotationCurveOccurrence()
    const;

  Standard_EXPORT occ::handle<StepVisual_AnnotationTextOccurrence> AnnotationTextOccurrence() const;

  Standard_EXPORT occ::handle<StepVisual_TessellatedAnnotationOccurrence>
                  TessellatedAnnotationOccurrence() const;

  Standard_EXPORT occ::handle<StepVisual_AnnotationFillAreaOccurrence>
                  AnnotationFillAreaOccurrence() const;
};
