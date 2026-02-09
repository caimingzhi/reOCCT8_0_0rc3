#pragma once

#include <Standard.hpp>

#include <StepVisual_AnnotationOccurrence.hpp>

class StepVisual_AnnotationFillAreaOccurrence : public StepVisual_AnnotationOccurrence
{
public:
  Standard_EXPORT StepVisual_AnnotationFillAreaOccurrence();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theName,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                                             theStyles,
    const occ::handle<Standard_Transient>&                   theItem,
    const occ::handle<StepGeom_GeometricRepresentationItem>& theFillStyleTarget);

  occ::handle<StepGeom_GeometricRepresentationItem> FillStyleTarget() const
  {
    return myFillStyleTarget;
  }

  void SetFillStyleTarget(const occ::handle<StepGeom_GeometricRepresentationItem>& theTarget)
  {
    myFillStyleTarget = theTarget;
  }

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationFillAreaOccurrence, StepVisual_AnnotationOccurrence)

private:
  occ::handle<StepGeom_GeometricRepresentationItem> myFillStyleTarget;
};
