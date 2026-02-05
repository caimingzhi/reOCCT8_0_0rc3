#include <StepVisual_AnnotationFillAreaOccurrence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_AnnotationFillAreaOccurrence, StepVisual_AnnotationOccurrence)

//=================================================================================================

StepVisual_AnnotationFillAreaOccurrence::StepVisual_AnnotationFillAreaOccurrence() = default;

//=================================================================================================

void StepVisual_AnnotationFillAreaOccurrence::Init(
  const occ::handle<TCollection_HAsciiString>& theName,
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                                           theStyles,
  const occ::handle<Standard_Transient>&                   theItem,
  const occ::handle<StepGeom_GeometricRepresentationItem>& theFillStyleTarget)
{
  StepVisual_AnnotationOccurrence::Init(theName, theStyles, theItem);
  myFillStyleTarget = theFillStyleTarget;
}
