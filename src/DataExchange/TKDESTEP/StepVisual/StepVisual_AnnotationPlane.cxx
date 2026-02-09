#include <StepVisual_AnnotationPlane.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_AnnotationPlane, StepVisual_AnnotationOccurrence)

StepVisual_AnnotationPlane::StepVisual_AnnotationPlane() = default;

void StepVisual_AnnotationPlane::Init(
  const occ::handle<TCollection_HAsciiString>& theName,
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                                                             theStyles,
  const occ::handle<Standard_Transient>&                                     theItem,
  const occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>>& theElements)
{
  StepVisual_AnnotationOccurrence::Init(theName, theStyles, theItem);
  myElements = theElements;
}
