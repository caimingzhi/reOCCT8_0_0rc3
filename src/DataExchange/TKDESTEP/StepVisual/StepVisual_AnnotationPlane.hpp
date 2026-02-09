#pragma once

#include <Standard.hpp>

#include <StepVisual_AnnotationOccurrence.hpp>
#include <StepVisual_AnnotationPlaneElement.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepVisual_AnnotationPlane : public StepVisual_AnnotationOccurrence
{
public:
  Standard_EXPORT StepVisual_AnnotationPlane();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theName,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                                                               theStyles,
    const occ::handle<Standard_Transient>&                                     theItem,
    const occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>>& theElements);

  inline occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>> Elements() const
  {
    return myElements;
  }

  inline void SetElements(
    const occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>>& theElements)
  {
    myElements = theElements;
  }

  inline int NbElements() const { return (myElements.IsNull() ? 0 : myElements->Length()); }

  inline StepVisual_AnnotationPlaneElement ElementsValue(const int theNum) const
  {
    return myElements->Value(theNum);
  }

  inline void SetElementsValue(const int theNum, const StepVisual_AnnotationPlaneElement& theItem)
  {
    myElements->SetValue(theNum, theItem);
  }

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationPlane, StepVisual_AnnotationOccurrence)

private:
  occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>> myElements;
};
