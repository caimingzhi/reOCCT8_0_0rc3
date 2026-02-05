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

  //! Returns a DraughtingCalloutElement select type
  Standard_EXPORT StepVisual_DraughtingCalloutElement();

  //! Recognizes a IdAttributeSelect Kind Entity that is :
  //! 1 -> AnnotationCurveOccurrence
  //! 2 -> AnnotationTextOccurrence
  //! 3 -> TessellatedAnnotationOccurrence
  //! 4 -> AnnotationFillAreaOccurrence
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a AnnotationCurveOccurrence (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_AnnotationCurveOccurrence> AnnotationCurveOccurrence()
    const;

  //! returns Value as a AnnotationTextOccurrence
  Standard_EXPORT occ::handle<StepVisual_AnnotationTextOccurrence> AnnotationTextOccurrence() const;

  //! returns Value as a TessellatedAnnotationOccurrence
  Standard_EXPORT occ::handle<StepVisual_TessellatedAnnotationOccurrence>
                  TessellatedAnnotationOccurrence() const;

  //! returns Value as a AnnotationFillAreaOccurrence
  Standard_EXPORT occ::handle<StepVisual_AnnotationFillAreaOccurrence>
                  AnnotationFillAreaOccurrence() const;
};
